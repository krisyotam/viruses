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
#ifndef __SIM_Status_H__
#define __SIM_Status_H__

#include <e32base.h>

class SimStatus
	{
public:
	static TBool Changed();
	static TBool Present();
	};
	
#endif

