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

INT ShlwapiCharStringToWCharString(_In_ PCHAR InString, _Inout_ PWCHAR OutString, _In_ INT BufferSize)
{
	return SHAnsiToUnicode(InString, OutString, BufferSize);
}