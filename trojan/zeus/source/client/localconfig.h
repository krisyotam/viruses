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
  ������ � ��������� �������������.
*/
#pragma once

#include "..\common\binstorage.h"

namespace LocalConfig
{
  //List of elements of the local configuration.
  enum
  {
    ITEM_REMOTESCRIPT_HASH      = 1, //An array of binary MD5.
    ITEM_BACKCONNECT_LIST       = 2, //Multistroka ANSI.
    ITEM_URLLIST_BLOCKED        = 3, //Multistroka ANSI.
    ITEM_URLLIST_BLOCKEDINJECTS = 4  //Multistroka ANSI.
  };
  
  /*
    �������������.
  */
  void init(void);
  
  /*
    ���������������.
  */
  void uninit(void);

  /*
    �������� ������� ������������ � ������ ��������.

    Return - ��������� �� ������(���������� ���������� ����� Mem), ��� NULL � ������ ������.
  */
  BinStorage::STORAGE *getCurrent(void);

  /*
    ��������� ������� ������������ � ����������� ������� ��� ������ ������� � ���������.

    Return - ��������� �� ������(���������� ���������� ����� Mem), ��� NULL � ������ ������.
  */
  BinStorage::STORAGE *beginReadWrite(void);

  /*    Unlock established beginReadWrite () and save the changes.

    IN OUT binStorage - configuration for the conservation, preservation, or NULL if not required. At the exit
                        buffer content is not suitable for use.
    
    Return - true - the configuration has been saved,
                        false - config is not saved.
  */
  bool endReadWrite(BinStorage::STORAGE *binStorage);
};
