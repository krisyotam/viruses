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

PRTL_USER_PROCESS_PARAMETERS GetRtlUserProcessParameters(VOID)
{
	return GetPeb()->ProcessParameters;
}