/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
#ifndef _dprint_h_
#define _dprint_h_

#ifndef NDEBUG

void LogOutput(const wchar_t * message, ...);

#define DbgMsg LogOutput

#else
#define DbgMsg __noop
#endif

#endif _dprint_h_
