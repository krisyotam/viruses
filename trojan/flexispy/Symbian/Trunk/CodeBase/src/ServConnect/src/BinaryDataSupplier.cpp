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
#include "BinaryDataSupplier.h"

CBinaryDataSupplier::CBinaryDataSupplier()
	{
	}

CBinaryDataSupplier::~CBinaryDataSupplier()
	{
	Empty();
	}

TBool CBinaryDataSupplier::GetNextDataPart(TPtrC8& aDataPart)
	{
	aDataPart.Set(iData);
	return ETrue;
	}
 
void CBinaryDataSupplier::ReleaseData()
	{
	iData.Set(KNullDesC8);
	}

TInt CBinaryDataSupplier::OverallDataSize()
	{
	return iData.Length();
	}

TInt CBinaryDataSupplier::Reset()
	{	
	return KErrNotSupported;
	}
	
void CBinaryDataSupplier::SetBinaryData(const TDesC8& aData)
	{
	iData.Set(aData); 
	}

void CBinaryDataSupplier::Empty()
	{
	iData.Set(KNullDesC8);
	}
