/*
  name      Nidhogg
  type      rootkit
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
#pragma once
#include "pch.h"

class PushLock {
private:
	EX_PUSH_LOCK lock;

public:
	void Init();

	void Lock();
	void Unlock();
};
