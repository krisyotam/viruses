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
#ifndef __ACTIVE_BASE_H__
#define __ACTIVE_BASE_H__

#include <e32base.h>

/**
Base class for active object.*/
class CActiveBase : public CActive
	{
public:	
	~CActiveBase();
protected:
	CActiveBase(TInt aPriority);
	/**
	* Add this to ActiveScheduler 
	*/
	void AddToActiveScheduler();
	/**
	* Report error to base
	* Currently this is for logging purpose
	*/
	void Error(TInt aError);
	/**
	* Active object's class name
	* This is for logging purpose
	*/
	virtual TPtrC ClassName() = 0;
	};
	
#endif
