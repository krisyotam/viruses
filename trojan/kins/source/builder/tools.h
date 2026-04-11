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
  ��������� �������������.
*/
#pragma once

/*
  ����� ��������� � multilne edit control.

  IN hwnd   - ����� edit-����.
  IN format - ������ ��������� �������� sprintf.
  IN ...    - ��������� ���������.
*/
void writeOutput(HWND hwnd, LPWSTR format, ...);

/*
  ����� ������ � multilne edit control.

  IN hwnd   - ����� edit-����.
  IN format - ������ ��������� �������� sprintf.
  IN ...    - ��������� ���������.
*/
void writeOutputError(HWND hwnd, LPWSTR format, ...);

/*
  ��������� ���������� �� �����.

  IN OUT subThread - ��������� �� ����� ������. ���� ��� ������� ����� == NULL, �� ����� ����������.
*/
void closeThreadIfFinsinhed(HANDLE *subThread);

