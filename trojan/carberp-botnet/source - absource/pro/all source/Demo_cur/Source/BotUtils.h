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
#include <windows.h>

DWORD GetNameHash( WCHAR *Path );
DWORD GetBotHash();

WCHAR *GetNameFromPath( WCHAR *Path );
WCHAR *GetShellFoldersKey( DWORD dwParam );

WCHAR *GetTempName();