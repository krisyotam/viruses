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
#ifndef AI_STR_APPENDER
#define AI_LIST_APPENDER

#include <stddef.h>

typedef struct AiStrAppender AiStrAppender;

struct AiStrAppender
{
   char  *str;
   size_t strSize;
   size_t allocSize;
};

int AiStrAppenderInit(AiStrAppender *strAppender);
int AiStrAppenderWork(AiStrAppender *strAppender, char *toAppend);
int AiStrAppenderWorkChar(AiStrAppender *strAppender, char toAppend);

#endif