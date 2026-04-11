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

INT ShlwapiWCharStringToCharString(_In_ PWCHAR InString, _Inout_ PCHAR OutString, _In_ INT BufferSize)
{
	return SHUnicodeToAnsi(InString, OutString, BufferSize);
}