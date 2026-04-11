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
  ����.
*/
#pragma once

//Structure for storing basic data processes.
typedef struct
{
  DWORD exitCode;           //Output Code
  struct
  {
    int argsCount;          //The number of arguments on the command line.
    LPWSTR *args;           //An array of command line.
  }commandLine;
  WCHAR fileName[MAX_PATH]; //Current file name.
}COREDATA;
extern COREDATA coreData;

namespace Core
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*    Display of the logo.
  */
  void showLogo(void);
};
