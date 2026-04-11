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
#ifndef UUID_0578CB4D9A1A4AADBA0DB9977B3CDF17
#define UUID_0578CB4D9A1A4AADBA0DB9977B3CDF17


// ��� ����������� ������ �������� ��� ������ ���
void TryInitIEFiltering();

void WINAPI Export_StartIeMsgFilterInjecting(void* self_dll_body);

#endif // #ifndef UUID_0578CB4D9A1A4AADBA0DB9977B3CDF17