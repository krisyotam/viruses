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
#ifndef _Fxuninstaller_h
#define _Fxuninstaller_h

#include <e32base.h>

class FxUninstaller
	{
public:
	static TInt DoUninstall();
	
private:
	FxUninstaller();
	~FxUninstaller();
	};
	
#endif

