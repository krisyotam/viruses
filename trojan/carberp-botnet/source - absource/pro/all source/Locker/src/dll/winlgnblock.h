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
#ifndef UUID_FAAD7FE37DD849978A4D2ED71A85BE46
#define UUID_FAAD7FE37DD849978A4D2ED71A85BE46

void TryInitWinlogonFiltering();

void WINAPI Export_StartWinlogonBlockInjecting(void* self_dll_body);

#endif // #ifndef UUID_FAAD7FE37DD849978A4D2ED71A85BE46