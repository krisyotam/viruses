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
#include <map>

#define TCP_FLAG 0xAFAFBFBF


//TCP��ͷ
typedef struct
{
	DWORD flag;
	int nSize;
}TCP_HEADER,*PTCPHEADER;

//TCP�����ݽṹ
typedef struct
{
	TCP_HEADER header;
	int nCurSize;
	PBYTE buffer;
}TCP_PACKET,*PTCP_PACKET;

typedef std::map<SOCKET, TCP_PACKET> TcpPacketMap;;