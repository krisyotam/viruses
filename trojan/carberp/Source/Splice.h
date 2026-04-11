/*
  name      Carberp
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#include <windows.h>

PVOID HookApi( DWORD DllNum, DWORD FuncHash, DWORD ReplacementFunc );
PVOID HookApi2( DWORD Dll, DWORD FuncVA, DWORD ReplacementFunc );
