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

LCID GetCurrentLocaleFromTeb(VOID)
{
	PTEB Teb = (PTEB)GetTeb();

	return (LCID)Teb->CurrentLocale;
}
