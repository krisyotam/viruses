/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
#include <windows.h>
#include <time.h>
#include <stdio.h>

#include "dprint.h"


#ifdef ENABLE_DPRINTF

//------------------------------------------------------------------------------
void logoutputv(const char *message, va_list ptr)
{
	char logTextBuffer[1024];
	wvsprintfA( logTextBuffer, message, ptr );
	OutputDebugStringA(logTextBuffer);
}
//------------------------------------------------------------------------------
void LogOutput( const char* message, ...)
{
  va_list ptr;
  va_start(ptr, message);
  logoutputv(message, ptr);  
  va_end(ptr);
}
//------------------------------------------------------------------------------
#endif

