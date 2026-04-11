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

#ifndef RuBnkH
#define RuBnkH
//----------------------------------------------------------------------------
#include <windows.h>
#include <wininet.h>
#include "Ibank.h"

void IsBank( HINTERNET hRequest );
bool IbankHooksMain();
bool HookCyberplatPCMain();


//----------------------------------------------------------------------------
#endif
