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



extern"C"  int  WINAPI Start(char* URL, DWORD Threads, DWORD AttemptsPerSecond, DWORD Flags);

extern"C"  void WINAPI Stop();

extern"C"  BOOL WINAPI Busy();

