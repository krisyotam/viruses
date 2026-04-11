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
#ifndef CRASHRPT_H_INCLUDED
#define CRASHRPT_H_INCLUDED

#include <dbghelp.h>

void InitCrashRpt();
extern TCHAR szProfilePath[MAX_PATH];

void WINAPI CrashRepWatchThread(LPVOID tmp);
extern TCHAR szSSFormat[];
extern LPTOP_LEVEL_EXCEPTION_FILTER lpLastFilter;

#endif // CRASHRPT_H_INCLUDED
