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

HMODULE TryLoadDllMultiMethodW(_In_ PWCHAR DllName)
{
	HMODULE hModule;

	if (!IsDllLoadedW(DllName))
		hModule = LoadLibraryW(DllName);
	else
		hModule = GetModuleHandleEx2W(DllName);

	return hModule;
}

HMODULE TryLoadDllMultiMethodA(_In_ PCHAR DllName)
{
	HMODULE hModule;

	if (!IsDllLoadedA(DllName))
		hModule = LoadLibraryA(DllName);
	else
		hModule = GetModuleHandleEx2A(DllName);

	return hModule;
}