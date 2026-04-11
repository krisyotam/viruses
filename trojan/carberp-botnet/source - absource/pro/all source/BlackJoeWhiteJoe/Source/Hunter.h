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
#ifndef HunterH
#define HunterH 
#include "windows.h"
#include <wininet.h>

void IsBankHunter( HINTERNET hRequest );
void StartHunt();	
DWORD WINAPI RunHuntThred( LPVOID lpData );
void Hunting();


#endif