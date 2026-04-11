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
#ifndef __DbMemoryMan_H_
#define __DbMemoryMan_H_

#include <e32base.h>

const TInt KMaxDbSize 1024 * 1024 * 3; //3 MB
const TInt KMaxAvailableDisk 1024 * 500; //500 KB

class CCltDbMemMan : public CBase
{	

public:
	CCltDbMemMan(CCltDbEngine& aDb);
	~CCltDbMemMan();
private:	
	
};
#endif