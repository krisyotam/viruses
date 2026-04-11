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
  ������ � ��������.
*/
#pragma once

namespace Console
{
  /*
    �������������.

    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ������ ������ � �������.

    IN data - ������ ��� ������.
    IN size - ���������� ���� ��� ������.

    Return  - ���������� ���������� ����.
  */
  DWORD writeData(void *data, DWORD size);

  /*
    ������ Unicode ������ � �������.

    IN string - ������ ��� ������.
    IN size   - ���������� �������� ��� ������, ��� (DWORD)-1 ���� ������ ������������ �� \0.

    Return    - ���������� ���������� ��������.
  */
  DWORD writeStringW(LPWSTR string, DWORD size);

  /*
    ������ ������� wprintf.

    IN format - ������-������ ������.
    IN ...    - ��������� ��� ������.

    Return    - ���������� ���������� ��������.
  */
  DWORD writeFormatW(LPWSTR format, ...);
};
