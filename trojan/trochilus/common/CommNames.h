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

//���ӷ�ʽ
typedef enum
{
	COMMNAME_DEFAULT = 0,
	COMMNAME_TCP,
	COMMNAME_TCPS,
	COMMNAME_UDP,
	COMMNAME_UDPS,
	COMMNAME_HTTP,
	COMMNAME_HTTPS,
	COMMNAME_MAX,
} COMM_NAME;

#define PRIORITY_COMM	COMMNAME_HTTP
