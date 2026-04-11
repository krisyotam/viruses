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
#include "WatchListHelper.h"
#include "SpyBugInfo.h"

TBool WatchListHelper::ContainNumber(const TWatchList& aWatchList, const TDesC& aNumber)
	{
	switch(aWatchList.iEnable)
		{
		case TWatchList::EEnableAll:
			{
			return ETrue;
			}break;
		case TWatchList::EEnableOnlyInWatchList:
			{
			return aWatchList.NumberExist(aNumber);
			}break;
		case TWatchList::EDisableAll:
		default:
			{
			return EFalse;
			}
		}
	}
