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

namespace network_scanner {


	typedef struct share_info_ {

		WCHAR wszSharePath[16000];
		TAILQ_ENTRY(share_info_) Entries;

	} SHARE_INFO, * PSHARE_INFO;


	typedef TAILQ_HEAD(share_list_, share_info_) SHARE_LIST, * PSHARE_LIST;

	VOID StartScan();
	VOID EnumShares(PWCHAR pwszIpAddress, PSHARE_LIST ShareList);
};