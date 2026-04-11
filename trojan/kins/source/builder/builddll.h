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
  ������ ����.
*/
#pragma once

#include "..\common\config0.h"

namespace BuildDll
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
    ������ ������ ����.

    IN owner      - �������� ����.
    IN output     - ���� ��� ������ �������.
    IN config     - ������������.
    IN destFolder - ����� ���������� ��� ��������� �����.

    Return        - true - � ������ ������,
                    false - � ������ ������.
  */
  bool _run(HWND owner, HWND output, Config0::CFGDATA *config, LPWSTR destFolder);
};
