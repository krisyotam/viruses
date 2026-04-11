/*
  name      KINS
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#include <windows.h>

#include "defines.h"
#include "dllfile32.h"
#include "dllfile64.h"
#include "languages.h"
#include "main.h"

#include "..\common\config.h"
#include "..\common\str.h"

//���������� ����.
static const LPWSTR languageEn[] =
{
  L"Not enough memory",
  L"Failed to write output file.",
  L"\r\nERROR: %s",

  BOT_NAME L" Builder",

  L"Builder",
  L"Settings",

  L"Version: %u.%u.%u.%u\r\nBuild time: %s\r\n",

  L"Bot\'s source configuartion file:",
  L"Browse...",
  L"Edit...",
  
  L"Actions",
  L"Build dll",
  L"Build Dropper",
  L"-- file not selected --",
  L"Failed to execute external editor.",
  L"Failed to read configuration file.",

  L"Building the dll...",
  L"Loading configuration...",
  L"Creating dll file...",
  L"Size of output file is %u bytes.",
  L"\r\nBUILD SUCCEEDED!",

  L"Source executable file corrupted.",
  L"Failed to find \"DllConfig\".",
  L"Failed to find \"DropperConfig\".",
  L"Error found in \"DllConfig/notify_server\".",
  L"Error found in \"DllConfig/url_server\".",
  L"Failed to find \"DllConfig/encryption_key\".",
  L"Error found in \"DllConfig/WebFilters\".",
  L"Error found in \"DllConfig/CaptchaList\".",
  L"Error found in \"DropperConfig/url1\".",
  L"Error found in \"DropperConfig/url2\".",
  L"Error found in \"DropperConfig/url3\".",
  L"Error found in \"DropperConfig/delay\".",
  L"Error found in \"DropperConfig/retry\".",
  L"Error found in \"DropperConfig/buildid\".",
  L"Dropper successfuly builded.",
  L"Error when building dropper.",
  
  L"Error found in \"DllConfig/file_webinjects\".",
  L"Building the HTTP injects...",
  L"Failed to open HTTP injects file.",
  L"Bad HTTP-inject found.",

  L"Language:",
  L"Apply",
  L"For language to change you should restart application.",
  L"Failed to save all settings.",
};

//������� ����.
static const LPWSTR languageRu[] =
{
  L"������������ ������.",
  L"�� ������� ��������� ����.",
  L"\r\n������: %s",

  BOT_NAME L" Builder",

  L"������",
  L"�����",

  L"������: %u.%u.%u.%u\r\n����� ������: %s",

  L"�������� ���� ������������ ����:",
  L"�����...",
  L"������...",
  
  L"��������",
  L"������� ���",
  L"������� �������",
  L"-- ���� �� ������ --",
  L"�� ������� ��������� ������� ��������.",
  L"�� ������� ��������� ���� ������������.",

  L"������ ���...",
  L"�������� ������������...",
  L"�������� DLL-�����...",
  L"������ ����� %u ����.",
  L"\r\n������ ������� ���������!",

  L"�������� PE-���� ���������.",
  L"�� ������� ����� \"DllConfig\".",
  L"�� ������� ����� \"DropperConfig\".",
  L"���������� ������ � \"DllConfig/notify_server\".",
  L"���������� ������ � \"DllConfig/url_server\".",
  L"�� ������� ����� \"DllConfig/encryption_key\".",
  L"���������� ������ � \"DllConfig/WebFilters\".",
  L"���������� ������ � \"DllConfig/CaptchaList\".",
  L"���������� ������ � \"DropperConfig/url1\".",
  L"���������� ������ � \"DropperConfig/url2\".",
  L"���������� ������ � \"DropperConfig/url3\".",
  L"���������� ������ � \"DropperConfig/delay\".",
  L"���������� ������ � \"DropperConfig/retry\".",
  L"���������� ������ � \"DropperConfig/buildid\".",
  L"������� ������� ������.",
  L"���������� ������ ��� �������� ��������.",
  
  L"���������� ������ � \"DllConfig/file_webinjects\".",
  L"������ HTTP-��������...",
  L"�� ������� ������� ���� � HTTP-���������.",
  L"��������� HTTP-������ � �������.",

  L"���� ����������:",
  L"���������",
  L"��� ���������� ����� ���������� ������������� ����������.",
  L"�� ������� ��������� ��� ���������.",
};

//������ ��������� ������.
static const Languages::LANGINFO languages[] =
{
  {L"English",           languageEn, sizeof(languageEn) / sizeof(LPWSTR), 1033},
  {L"������� (Russian)", languageRu, sizeof(languageRu) / sizeof(LPWSTR), 1049}
};

//������ �������� �����.
static const Languages::LANGINFO *languageCur;

void Languages::init(void)
{
  //���� �� ���������.
  languageCur = &languages[0];
  
  //�������� ���� �� �������.
  WORD langId = CWA(kernel32, GetUserDefaultUILanguage)();
  for(BYTE i = 0; i < sizeof(languages) / sizeof(Languages::LANGINFO); i++)
	  if(langId == languages[i].id)
	  {
		  languageCur = &languages[i]; 
		  break;
	  }
  
  //������� ���� �� �������.
  langId = CWA(kernel32, GetPrivateProfileIntW)(L"settings", L"language", langId, settingsFile);
  for(BYTE i = 0; i < sizeof(languages) / sizeof(Languages::LANGINFO); i++)
	  if(langId == languages[i].id)
	  {
		  languageCur = &languages[i]; 
		  break;
	  }
}

void Languages::uninit(void)
{

}

LPWSTR Languages::get(DWORD id)
{
  return (id < languageCur->stringsCount) ? languageCur->strings[id] : NULL;
}

bool Languages::setDefaultLangId(WORD langId)
{
  WCHAR str[10];
  Str::_FromInt32W(langId, str, 10, false);
  return CWA(kernel32, WritePrivateProfileStringW)(L"settings", L"language", str, settingsFile) == FALSE ? false : true;
}

const Languages::LANGINFO *Languages::getLangInfo(WORD index)
{
  if(index < sizeof(languages) / sizeof(Languages::LANGINFO))
	  return &languages[index];
  return NULL;
}

const Languages::LANGINFO *Languages::getCurLangInfo(void)
{
  return languageCur;
}
