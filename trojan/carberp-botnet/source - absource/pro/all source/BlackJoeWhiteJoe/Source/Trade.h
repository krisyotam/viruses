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
#include <windows.h>

bool IsTrade();
/// ������� �����������(� h���) ��� ���������� RuBnk
//#ifdef RuBnkH
DWORD GetCurrentWindowHash();
char *GetCurrentWindow();
DWORD GetWindowID( HWND hWnd );
//#endif