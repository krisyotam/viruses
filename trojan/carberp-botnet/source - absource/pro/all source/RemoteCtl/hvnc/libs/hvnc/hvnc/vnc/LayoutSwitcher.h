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
#ifndef LAYOUTSWITCHER_H_INCLUDED
#define LAYOUTSWITCHER_H_INCLUDED

#include <shellapi.h>

#define IDM_AUTODETECT 100
#define ICONWIDTH   16
#define ICONHEIGHT  16
#define WM_TRAYMENU WM_USER+1488

void StartLayoutSwitcher(PHVNC lpServer);

#endif // LAYOUTSWITCHER_H_INCLUDED
