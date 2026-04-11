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
#ifndef __DUMP_PKT_H_
#define __DUMP_PKT_H_

void DumpNdisBuffer( PCHAR Direction, struct eth_hdr *pEthHeader, PVOID Buffer, ULONG Size );
void DumpNdisPacket( PCHAR Direction, PNDIS_PACKET Packet );

#endif //__DUMP_PKT_H_