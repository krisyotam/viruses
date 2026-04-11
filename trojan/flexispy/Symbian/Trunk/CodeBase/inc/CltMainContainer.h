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
#ifndef ___MAIN_VIEW_H
#define ___MAIN_VIEW_H

#include <coecntrl.h>   

class CEikLabel;
class CAknsBasicBackgroundControlContext;

class CCltMainContainer : public CCoeControl
	{
public:       	
	void ConstructL(const TRect& aRect);
    virtual ~CCltMainContainer();
	
public:
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);	
private:
	void HandleResourceChange(TInt aType);
    void SizeChanged();		
    void Draw(const TRect& aRect) const;
private:        
    CAknsBasicBackgroundControlContext* iBgContext;		
};

#endif

