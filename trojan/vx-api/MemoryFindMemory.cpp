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

PVOID MemoryFindMemory(_In_ PVOID Haystack, _In_ SIZE_T HaystackLength, _In_ PVOID Needle, _In_ SIZE_T NeedleLength)
{
	if (!Haystack || !HaystackLength || !Needle || !NeedleLength)
		return NULL;

	for (PCHAR pChar = (PCHAR)Haystack; HaystackLength >= NeedleLength; ++pChar, --HaystackLength)
	{
		if (!memcmp(pChar, Needle, NeedleLength))
			return pChar;
	}

	return NULL;
}