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
#include "CommData.h"

typedef BOOL (*FnMsgHandler)(MSGID msgid, const CommData& commData, LPVOID lpParameter);
