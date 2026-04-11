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

#ifndef BssSendFileH
#define BssSendFileH

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//  ��������� ���, ������� ���������� ��� ����� ��������������� ����� ���
//----------------------------------------------------------------------------

void AddBSSFile(PCHAR URL, LPVOID Data, DWORD DataSize);
bool IsBSSDocument(PCHAR URL);


//----------------------------------------------------------------------------
#endif
