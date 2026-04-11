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
#ifndef UUID_67CC7598B46343D4B3E09E57633401CB
#define UUID_67CC7598B46343D4B3E09E57633401CB

struct ScopedDebugPrivilege
{
  ScopedDebugPrivilege();
  ~ScopedDebugPrivilege();

  bool Enabled();

private:
  bool m_enabled;
};

#endif