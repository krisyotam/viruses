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

DWORD GetCurrentProcessIdFromTeb(VOID)
{
	return HandleToUlong(GetTeb()->ClientId.UniqueProcess);
}