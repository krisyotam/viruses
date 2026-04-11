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
#ifndef __MsvReadyObserver_H__
#define __MsvReadyObserver_H__

class MMsvServerObserver
	{
public:
	virtual void MsvServerReadyL() = 0;
	};

#endif
