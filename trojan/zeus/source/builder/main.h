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
  ����� �����, � ������� ������.
*/
#pragma once

/*  Message sent by the tabs on the possibility to close the application now.

  Return - true - the application can be closed
           false - the application can not be closed.*/
#define WM_CANCLOSE (WM_USER + 1)

//Global variables.
extern HMODULE currentModule;       //Tekusheyu handle to the module.
extern WCHAR homePath[MAX_PATH];    //Home directory.
extern WCHAR settingsFile[MAX_PATH]; //Options file.
