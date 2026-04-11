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

template<typename TLock>
struct AutoLock {
	AutoLock(TLock& lock) : _lock(lock) {
		_lock.Lock();
	}

	~AutoLock() {
		_lock.Unlock();
	}

private:
	TLock& _lock;
};