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
  ������ � ������������� ������������ Windows.
*/
#pragma once

namespace WinSecurity
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
    �������� SECURITY_ATTRIBUTES � SECURITY_DESCRIPTOR � ������ ��������.

    OUT sa - ��������� SECURITY_ATTRIBUTES, ����� ���� NULL, ���� �������� �� �����.
    OUT sd - ��������� SECURITY_DESCRIPTOR.

    Return - � ������ ������: ����� ������ ������� ����� ���������� ����� LocalFree, ���  (void *)-1.
             � ������ ������: NULL.

    ����������: sa � sd ������� ����� �����.
  */
  void *_getFullAccessDescriptors(SECURITY_ATTRIBUTES *sa, SECURITY_DESCRIPTOR *sd);

  /*
    ��������� �� ������ ���� �� ������ ����� ��� Low Integrity ���������.

    IN name       - ��� �������.
    IN objectType - ��� ������� SE_OBJECT.
    IN inherit    - ������� ������������ �������� ��������.
    
    Return        - true - � ������ ������,
                    false - � ������ ������.
  */
  bool _setLowIntegrityLevelLabel(LPWSTR name, DWORD objectType, bool inherit);

  /*    Getting TOKEN_USER of the token.

    IN token - the token, you need the right TOKEN_QUERY.

    Return - NULL - in case of error,
               address of the structure in case of success, must be released through the Mem.
  */
  TOKEN_USER *_getUserByToken(HANDLE token);
};
