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
#ifndef __CCltMainView_H__
#define __CCltMainView_H__

#include <aknview.h>

class CCltMainContainer;

class CCltMainView: public CAknView
{
public:	
	static CCltMainView* NewL();
	~CCltMainView();

private: // from CAknView
	TUid Id() const;	
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId, const TDesC8& aCustomMessage);
	void DoDeactivate();
	void HandleCommandL(TInt aCommand);
	
private: 
	CCltMainView();
	void ConstructL();
	void SetTitleL();	
protected:
	CCltMainContainer*      iContainer;	
};


#endif
