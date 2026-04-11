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
  ����� �����, � ������� ������.
*/
#pragma once

/*
  ��������� ����������� ��������, � ����������� ������� ���������� ������.

  Return - true - ���������� ����� �������,
           false - ���������� ������ �������.
*/
#define WM_CANCLOSE (WM_USER + 1)

//���������� ����������.
extern HMODULE currentModule;       //����� �������� ������.
extern WCHAR homePath[MAX_PATH];    //�������� ����������.
extern WCHAR settingsFile[MAX_PATH]; //���� �����.
