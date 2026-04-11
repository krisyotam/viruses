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

VOID SetLastNtStatusInTeb(_In_ NTSTATUS Status)
{
	GetTeb()->LastStatusValue = Status;
}