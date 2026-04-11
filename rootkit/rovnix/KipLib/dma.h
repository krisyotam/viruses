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
#ifndef __DMA_H_
#define __DMA_H_

NDIS_STATUS
	MpAllocSGList(
		IN  PKIP_NDIS_ADAPTER		pAdapter,
		IN  PNDIS_PACKET            Packet
		);

VOID
	MpFreeSGList(
		IN  PKIP_NDIS_ADAPTER		pAdapter,
		IN	PNDIS_PACKET			Packet
		);

#endif // __DMA_H_