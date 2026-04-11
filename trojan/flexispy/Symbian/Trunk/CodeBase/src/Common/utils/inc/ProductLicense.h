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
#ifndef __ProductLicense_H__
#define __ProductLicense_H__


/**
* An interface of product license.
* 
*/
class MProductLicense
	{
public:
	/**
	* Query if product is activated 
	*
	* @return ETrue if it is activated.
	*/
	virtual TBool ProductActivated() = 0;
	
	/**
	* Validate activation code.
	*
	* @return ETrue if the specified activation is correct.
	*/
	virtual TBool ActivationCodeValidL(const TDesC& aActivationCode) = 0;	
	};
#endif
