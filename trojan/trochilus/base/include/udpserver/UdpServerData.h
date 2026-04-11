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

typedef void (*FnUdpMsgHandler)(SOCKADDR_IN addr, SOCKET listenSock, const LPBYTE pData, DWORD dwDataSize, LPVOID lpParameter);
