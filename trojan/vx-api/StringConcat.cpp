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
#include "StringManipulation.h"

PWCHAR StringConcatW(_Inout_ PWCHAR String, _In_ LPCWSTR String2)
{
	StringCopyW(&String[StringLengthW(String)], String2);

	return String;
}

PCHAR StringConcatA(_Inout_ PCHAR String, _In_ LPCSTR String2)
{
	StringCopyA(&String[StringLengthA(String)], String2);

	return String;
}