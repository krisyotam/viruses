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
#ifndef COMPRESS_WRAP_H_INCLUDED
#define COMPRESS_WRAP_H_INCLUDED

typedef struct
{
    byte bHandleType;
    zipFile hZip;
    int dwCompLevel;

    bool bEncrypted;
    char szPassword[260];

    bool bInMem;
    byte *lpMem;
    int dwSize;
} ZIPCOMPRESSION;

typedef struct
{
    ZIPCOMPRESSION *lpZipData;
    void *zip;
    DWORD filesCount;
    DWORD cabPathOffset;
} CFFSTRUCT;

#endif // COMPRESS_WRAP_H_INCLUDED
