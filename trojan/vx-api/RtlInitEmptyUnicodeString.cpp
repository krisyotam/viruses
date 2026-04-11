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

VOID RtlInitEmptyUnicodeString(_Inout_ PUNICODE_STRING UnicodeString)
{
	UnicodeString->Length = 0;
	UnicodeString->MaximumLength = sizeof(UNICODE_STRING);
	UnicodeString->Buffer = NULL;

	return;
}