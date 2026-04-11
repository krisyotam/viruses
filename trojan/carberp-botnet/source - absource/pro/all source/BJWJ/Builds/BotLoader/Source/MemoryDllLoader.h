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


typedef void* HMEMMODULE;

bool       SaveMemLibrary(LPVOID Dll, PCHAR FileName);
HMEMMODULE LoadMemLibrary(LPVOID Buf);
void       FreeMemLibrary(HMEMMODULE Module);
LPVOID     GetMemProcAddress(HMEMMODULE Module, const char *ProcName);