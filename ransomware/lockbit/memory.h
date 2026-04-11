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
#include "common.h"

namespace memory {

	LPVOID Alloc(SIZE_T Size);
	VOID Free(LPVOID Memory);
	VOID Copy(PVOID pDst, CONST PVOID pSrc, size_t size);

}