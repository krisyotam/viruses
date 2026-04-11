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
#ifndef __SecretCode_H_
#define __SecretCode_H_

#include <e32base.h>

const TInt KMaxSecretCodeLength = 30;

class TSecretCode
	{
public:
	/**
	* Secret key
	*
	*/
	TBuf8<KMaxSecretCodeLength> iCode;
	};

typedef TPckg<TSecretCode>  TSecretCodePkg;
	
#endif