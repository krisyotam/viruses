/*
  name      Trochilus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#pragma once

namespace SelfDestruction
{
	BOOL CleanFile(LPCTSTR filepath);

	BOOL RemoveReadonlyAttr(LPCTSTR filepath);

	BOOL DeleteFileIgnoreReadonly(LPCTSTR localFilepath);

	BOOL ExitAndDeleteSelfDll(HMODULE hDll);

	void DeleteRunItem();
}
