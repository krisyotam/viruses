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

  /*
    ������ ���������� ������� ��������� ������. ���� �� ������ ����������� ��
    Process::INTEGRITY_LOW ���������.

    IN script - ������ ��� ����������. 
    
    Return    - true - � ������ ��������� ������� ���������� ������� (script ����� ����������
                �������������),
                false - � ������ ������ (script ����� ���������� ��������������).
  */
  bool _exec(BinStorage::STORAGE *script);
};
