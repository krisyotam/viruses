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
#ifndef __S9PromptsSettingContainer_H__
#define __S9PromptsSettingContainer_H__

#include <coecntrl.h> // CCoeControl
#include <akntabobserver.h>
#include <aknsettingitemlist.h>

class TS9Settings;
class CAknSettingItem;
class CAknsBasicBackgroundControlContext;

//
class CS9PromptsSettingItem : public CAknSettingItemList
	{
public:
	CS9PromptsSettingItem(TS9Settings& aS9Settings);
	~CS9PromptsSettingItem();
	
public:
	void ChangeSelectedItemL ();
	TInt CurrentIndex();
	void SizeChanged();
private:
	void EditItemL (TInt aIndex, TBool aCalledFromMenu);	
	CAknSettingItem* CreateSettingItemL(TInt aIdentifier);
private:
	TS9Settings& iS9Settings;
	};

#endif
