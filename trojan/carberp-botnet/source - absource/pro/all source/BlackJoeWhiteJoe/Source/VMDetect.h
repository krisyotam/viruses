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
#ifndef		VMDetectH
#define		VMDetectH

//----------------------------------------------------------------------------

#include <windows.h>


bool IsVMWare();
bool IsVPC();

// ������� ���������� ������ ���� ��������� �������� �� ����������� ������
bool DetectVM();

//----------------------------------------------------------------------------
#endif