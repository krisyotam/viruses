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
#ifndef __CltApplication_H__
#define __CltApplication_H__

#include <aknapp.h>	// CAknApplication
#include "AppInfoConst.h"

class CCltApplication : public CAknApplication
	{
public: // from CApaApplication
	TUid AppDllUid() const;
	
protected:
	CApaDocument* CreateDocumentL();
	};

#endif
