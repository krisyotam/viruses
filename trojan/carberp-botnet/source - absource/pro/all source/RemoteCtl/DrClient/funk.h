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
#pragma once

bool IsJavaWindow(HWND hWnd);
HANDLE WINAPI StartThread( LPVOID lpStartAddress, LPVOID param );
bool SaveToFileW( LPCWSTR lpName, LPVOID lpBuffer, DWORD dwSize );
bool FileCreateInFolder(int FlagFolderDest, WCHAR*Path,LPVOID Data,int count);
