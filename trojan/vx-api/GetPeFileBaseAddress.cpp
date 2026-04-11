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

HMODULE GetPeFileBaseAddress(VOID)
{
	PPEB Peb = GetPebFromTeb();
	PLDR_MODULE Module = NULL;

	Module = (PLDR_MODULE)((PBYTE)Peb->LoaderData->InMemoryOrderModuleList.Flink - 16);

	if (!Module)
		return NULL;

	return (HMODULE)(Module->BaseAddress ? Module->BaseAddress : NULL);
}