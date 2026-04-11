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
//---------------------------------------------------------------------------
#include <windows.h>
#ifndef bootkitH
#define bootkitH
//---------------------------------------------------------------------------

void IsBootkitInstaled();
DWORD WINAPI IsBootkitInstaledThread( LPVOID lpData );

//---------------------------------------------------------------------------
#endif
