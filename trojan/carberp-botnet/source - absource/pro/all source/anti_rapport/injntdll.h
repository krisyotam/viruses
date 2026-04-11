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
#ifndef _INJNTDLL_H_
#define _INJNTDLL_H_

BOOL InjnProcDllHook(LPCSTR lpProcessName, LPCSTR lpDllPath, PDWORD pdwInj);
VOID InjnProcDllUnhook();

#endif