/*
  name      Zeus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
/*
  ���������� �������� ����.
*/
#pragma once

#include "..\common\binstorage.h"

namespace RemoteScript
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*    Run the script execution votdelnom flow. Flow should not be run from
    Process:: INTEGRITY_LOW processes.

    IN script - a script for execution.
    
    Return - true - in the cases of the successful launch ispolenniya script (script will be released
                automatically)
                false - if an error (script to release its own).
  */
  bool _exec(BinStorage::STORAGE *script);
};
