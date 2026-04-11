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
#ifndef WND_WATCHER_H_INCLUDED
#define WND_WATCHER_H_INCLUDED

void StartWatcher(PHVNC lpServer);
bool IsItMsgBox(PHVNC lpServer,HWND hWnd);
void StopWatcher(PHVNC lpServer);

#endif // WND_WATCHER_H_INCLUDED
