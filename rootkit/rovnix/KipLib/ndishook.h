/*
  name      Rovnix
  type      rootkit
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#ifndef __NDIS_HOOK_H_
#define __NDIS_HOOK_H_

// public functions

NTSTATUS	NdisSetHooks(VOID);

VOID
	NdisReinstallMiniportHook(
		IN PKIP_NDIS_ADAPTER pAdapter
		);

#endif //__NDIS_HOOK_H_