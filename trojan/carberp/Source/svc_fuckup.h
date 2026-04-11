/*
  name      Carberp
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#ifndef SVC_FUCKUP_H_INCLUDED
#define SVC_FUCKUP_H_INCLUDED

typedef void (*ServiceMainFunction)();

bool SvcFuckupRun();
void SvcFuckupRunAsService(ServiceMainFunction service_main);

#endif // SVC_FUCKUP_H_INCLUDED
