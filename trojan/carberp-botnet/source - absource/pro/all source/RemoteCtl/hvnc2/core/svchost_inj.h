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
#ifndef SVCHOST_INJ_H_INCLUDED
#define SVCHOST_INJ_H_INCLUDED

bool InjectSVCHost(LPVOID lpAddr);
extern TCHAR szEvent[40];

#endif // SVCHOST_INJ_H_INCLUDED
