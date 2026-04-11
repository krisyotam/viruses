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
#ifndef __SettingChangeObserver_h__
#define __SettingChangeObserver_h__

#include <e32base.h>

#include "CltSettings.h"

class MSettingChangeObserver
	{
public:
	/**
	* 
	*/
	virtual void OnSettingChangedL(CFxsSettings& aSetting) = 0;
	};
	
#endif
