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

DWORD HashStringLoseLoseA(_In_ LPCSTR String)
{
	ULONG Hash = 0;
	INT c;

	while (c = *String++)
		Hash += c;

	return Hash;
}

DWORD HashStringLoseLoseW(_In_ LPCWSTR String)
{
	ULONG Hash = 0;
	INT c;

	while (c = *String++)
		Hash += c;

	return Hash;
}