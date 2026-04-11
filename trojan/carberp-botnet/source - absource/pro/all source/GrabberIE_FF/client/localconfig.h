/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
/*
  ������ � ��������� �������������.
*/
#pragma once

#include "..\common\binstorage.h"

namespace LocalConfig
{
  //������ ��������� ��������� ������������.
  enum
  {
    ITEM_REMOTESCRIPT_HASH      = 1, //������ �������� MD5.
    ITEM_BACKCONNECT_LIST       = 2, //������������ ANSI.
    ITEM_URLLIST_BLOCKED        = 3, //������������ ANSI.
    ITEM_URLLIST_BLOCKEDINJECTS = 4  //������������ ANSI.
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

  /*
    ������ ���������� ��������� beginReadWrite() � ���������� ���������.

    IN OUT binStorage - ������ ��� ����������, ��� NULL ���� ���������� �� ���������. �� ������
                        ���������� ������ �� �������� ��� �������������.
    
    Return            - true - ������ ������� ��������,
                        false - ������ �� ��������.
  */
  bool endReadWrite(BinStorage::STORAGE *binStorage);
};
