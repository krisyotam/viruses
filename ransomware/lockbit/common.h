/*
  name      LockBit 3.0 (Black)
  type      ransomware
  cve       —
  year      2022
  os        windows
  authors   LockBit Group
  source    https://github.com/Zzutiky666/LockBit (leaked source)
  archived  krisyotam
  notes     leaked by disgruntled affiliate Sept 2022; most prolific RaaS 2022-2024
 */

#pragma once
#include <WinSock2.h>
#include <string>
#include <iostream>
#include "MetaString.h"

//#define DEBUG
#define STATIC static

inline PVOID m_malloc(SIZE_T Size) 
{
	PVOID buf = malloc(Size);
	if (buf) {
		memset(buf, 0, Size);
	}

	return buf;
}

inline VOID m_free(PVOID Memory)
{
	free(Memory);
}
	