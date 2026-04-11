/*
  name      Trochilus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#pragma once

class CShareRestrictedSD  
{
public:
	CShareRestrictedSD();
	virtual ~CShareRestrictedSD();
	SECURITY_ATTRIBUTES* GetSA();

protected:
	PACL					pAcl;
	SECURITY_ATTRIBUTES		sa;
	PSECURITY_DESCRIPTOR	pSD;
	
private:
	BOOL BuildRestrictedSD();
};

