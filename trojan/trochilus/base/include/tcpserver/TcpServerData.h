/*
  name      Trochilus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#pragma once

//TCP��Ϣ����󳤶�
#ifndef TCPMSGSIZE
#	define TCPMSGSIZE	(16 * 1024)
#endif

//��Ϣ�����ص�����
typedef BOOL (*FnTcpMsgHandler)(SOCKADDR_IN addr, SOCKET clientSocket, const LPBYTE pData, DWORD dwDataSize, LPBYTE pSessionData, LPVOID lpParameter);

//���ӶϿ�֪ͨ����
typedef enum
{
	DISCONNECTREASON_UNKNOWN = 0,
	DISCONNECTREASON_CLIENT_DISCONNECT,
	DISCONNECTREASON_OPERATION_ABORT,
} DISCONNECT_REASON;
typedef void (*FnTcpDisconnectNotify)(SOCKADDR_IN addr, SOCKET clientSocket, LPBYTE pSessionData, DISCONNECT_REASON reason, LPVOID lpParameter);
