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
#include <map>

#define UDP_FLAG 0xAFAFBFBA


//TCP��ͷ
typedef struct
{
	DWORD flag;
	int nSize;
}UDP_HEADER,*PUDPHEADER;
