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

PTEB GetTeb(VOID)
{
#if defined(_WIN64)
	return (PTEB)__readgsqword(0x30);
#elif defined(_WIN32)
	return (PTEB)__readfsdword(0x18);
#endif
}
