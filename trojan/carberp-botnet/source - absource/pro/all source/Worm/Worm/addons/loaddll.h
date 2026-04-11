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

char* LoadFileFromAdminka( const char* nameFile, int* size );
char* LoadFileFromRequest( HINTERNET request, int* size );
char* LoadFileFromInet( const char* host, const char* url, int* size, const char* postData = 0, int szPostData = 0 );

