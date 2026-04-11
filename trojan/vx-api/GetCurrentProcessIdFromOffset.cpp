/*
  name      Vx Api
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
#include "Win32Helper.h"

DWORD GetCurrentProcessIdFromOffset(VOID)
{
#if defined(_WIN64)
    return (UINT32)__readgsqword(0x40);
#elif define(_WIN32)
    return (UINT32)__readfsdword(0x20);
#endif
}
