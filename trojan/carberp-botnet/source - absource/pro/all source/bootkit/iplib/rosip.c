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
#include "lwip/sys.h"
#include "lwip/tcpip.h"

#include "rosip.h"

#include <debug.h>

void
LibIPInitialize(void)
{
    /* This completes asynchronously */
    tcpip_init(NULL, NULL);
}

void
LibIPShutdown(void)
{
    /* This is synchronous */
    sys_shutdown();
}