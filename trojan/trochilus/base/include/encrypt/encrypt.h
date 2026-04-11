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

#include "md5/md5.h"
#include <tstring.h>

#define MD5_READ_BUFFER_LENGTH 4096

void Byte2HEX(const LPBYTE bytes, DWORD dwSize, std::wstring* pHexString);
BOOL GetFileMD5(LPCTSTR filepath, std::wstring* pMd5String);