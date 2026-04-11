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
#ifndef _INJECT_H_
#define _INJECT_H_

BOOL InjectProcess(LPCSTR lpProcessName,PVOID pvImageBase,DWORD dwImageSize,BOOL bCurrentSession);
BOOL LoadImageFromMemory(PVOID pBuffer);

#endif