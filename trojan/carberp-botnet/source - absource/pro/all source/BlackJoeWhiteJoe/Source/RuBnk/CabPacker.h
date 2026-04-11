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
#include "Modules.h"

//#ifdef RuBnkH
#include <windows.h>
#include <fci.h>
#include <io.h>
#include <fcntl.h>

typedef void* HCAB;



HCAB CreateCab( const char *szCabName );
bool AddFileToCab( HCAB handle, const char *szFileName, const char *szInternalName );
void CloseCab( HCAB handle );
bool AddDirToCab( HCAB handle, const char *szDirName, const char *szInternalName );
void Test();
//#endif