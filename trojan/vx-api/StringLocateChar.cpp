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

PCHAR StringLocateCharA(_Inout_ PCHAR String, _In_ INT Character)
{
	do
	{
		if (*String == Character)
			return (PCHAR)String;

	} while (*String++);

	return NULL;
}

PWCHAR StringLocateCharW(_Inout_ PWCHAR String, _In_ INT Character)
{
	do
	{
		if (*String == Character)
			return (PWCHAR)String;

	} while (*String++);

	return NULL;
}