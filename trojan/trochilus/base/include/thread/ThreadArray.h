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
#include <list>

typedef std::list<Thread*> ThreadList;

class ThreadArray
{
public:
	ThreadArray(void);
	~ThreadArray(void);
public:
	BOOL AddThreadTask(LPTHREAD_START_ROUTINE pThreadRoutinue,LPVOID lpParameter);
	BOOL WaitAllTaskEnd();
	void TerminalAllTask();
private:
	 ThreadList m_TList;
	 CriticalSection m_csThreadList;
};

