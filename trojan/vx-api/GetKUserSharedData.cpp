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

PKUSER_SHARED_DATA GetKUserSharedData(VOID)
{
	return (KUSER_SHARED_DATA*)0x7FFE0000;
}