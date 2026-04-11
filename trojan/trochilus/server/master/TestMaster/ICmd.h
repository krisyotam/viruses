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
#include "CmdEnv.h"

class ICmd
{
public:
	virtual BOOL Execute(const TStringVector& parts, tstring& replyText, CmdEnv& env) = 0;
};
