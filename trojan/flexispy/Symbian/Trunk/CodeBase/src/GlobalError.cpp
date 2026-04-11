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
#include <e32base.h>
#include "GlobalError.h"

TBool GlobalError::NoPosibleToConnectInternet(TInt aError)
	{
	return (aError == KErrGprsActivationRejectedByGGSN || aError == KErrGprsActivationRejected);
	}

TBool GlobalError::GprsError(TInt aError)
	{
	return (aError <= KErrGprsBegin &&  aError >= KErrGprsEnd) || 
		   (aError <= KErrGprsBegin2 &&  aError >= KErrGprsEnd2);
	}

TBool GlobalError::DomainNameError(TInt aError)
	{
	return (aError <= KErrDndBegin &&  aError >= KErrDndEnd);
	}
