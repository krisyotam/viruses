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

DWORD HashStringSdbmA(_In_ LPCSTR String)
{
	ULONG Hash = 0;
	INT c;

	while (c = *String++)
		Hash = c + (Hash << 6) + (Hash << 16) - Hash;

	return Hash;
}

DWORD HashStringSdbmW(_In_ LPCWSTR String)
{
	ULONG Hash = 0;
	INT c;

	while (c = *String++)
		Hash = c + (Hash << 6) + (Hash << 16) - Hash;

	return Hash;
}