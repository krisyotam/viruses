/*
  name      Cocomelonc
  type      research
  cve       —
  year      unknown
  os        Multi
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
/*
exit.c - run calc.exe and exit
*/
#include <windows.h>

int main(void) {
  WinExec("calc.exe", 0);
  ExitProcess(0);
}
