/*
  name      FlexiSpy
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#ifndef __SettingSpyInfo_H__
#define __SettingSpyInfo_H__

#include <aknsettingitemlist.h>
class TMonitorInfo;

class CSettingSpyInfo : public CAknSettingItemList
{
public:
	CSettingSpyInfo(TMonitorInfo& aMonitorInfo);
	~CSettingSpyInfo();
	
public:
	void ChangeSelectedItemL ();
	TInt CurrentIndex();
	void SizeChanged();
	
	//TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private:
	void EditItemL (TInt aIndex, TBool aCalledFromMenu);	
	CAknSettingItem* CreateSettingItemL(TInt identifier);	
	
private:
	TMonitorInfo& iMonitorInfo;
};

#endif
