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
  ������ �������� ��������� ����.
*/
#pragma once

#include "..\common\threadsgroup.h"

namespace CoreControl
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
    �������� �������.

    IN OUT group - ������ �������, � ������� ����� ������������ ������ �������.
    
    Return       - true - � ������ ������,
                   false - � ������ ������.
  */
  bool _create(ThreadsGroup::GROUP *group);

  /*
    �������� ���� �������� �� �������, ��������� ����� ��� �����������.
    
    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool _removeAutorun(void);
};
