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


#ifndef TradeH
#define TradeH
//----------------------------------------------------------

#include <windows.h>

bool IsTrade();
/// ������� �����������(� h���) ��� ���������� RuBnk
//#ifdef RuBnkH
DWORD GetCurrentWindowHash();
char *GetCurrentWindow();
DWORD TradeGetWindowID(HWND hWnd );



#endif


