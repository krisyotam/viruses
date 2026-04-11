/*
  name      Trochilus
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
#include "MessageDefines.h"

typedef BOOL (*FnExecuteRCCommand)(MSGID msgid, const LPBYTE pData, DWORD dwSize, LPVOID lpParameter);
