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
#include "stdafx.h"
#include <tlhelp32.h>

PROCESSENTRY32W* GetProcesses(DWORD* COUNT);

