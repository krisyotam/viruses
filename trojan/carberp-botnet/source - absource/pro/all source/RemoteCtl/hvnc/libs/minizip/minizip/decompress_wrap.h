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
#ifndef DECOMPRESS_WRAP_H_INCLUDED
#define DECOMPRESS_WRAP_H_INCLUDED

typedef struct
{
    byte bHandleType;
    unzFile hZip;
    bool bInMem;

    WCHAR strOutputDir[MAX_PATH];
    WCHAR strZipFile[MAX_PATH];

    bool bEncrypted;
    char szPassword[260];

    bool bOnlyEnum;
    bool bEnumAnsi;
    ARCHENUMNAMESCALLBACKW *lpEnumProc;

    bool bExctractToMem;
    LPVOID lpMem;
    int dwSize;
} ZIPDECOMPRESSION;

#endif // DECOMPRESS_WRAP_H_INCLUDED
