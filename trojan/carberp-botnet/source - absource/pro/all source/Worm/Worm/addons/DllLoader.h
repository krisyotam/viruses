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
#ifndef _DLLLOADER_H_
#define _DLLLOADER_H_

#include <windows.h>

typedef void *HMEMORYMODULE;

HMEMORYMODULE MemoryLoadLibrary(const void *);
FARPROC MemoryGetProcAddress(HMEMORYMODULE, const char *);
void MemoryFreeLibrary(HMEMORYMODULE);

#endif //_DLLLOADER_H_
