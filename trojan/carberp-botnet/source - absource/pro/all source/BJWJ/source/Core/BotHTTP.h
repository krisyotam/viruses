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
//  �������������: ���� 2012
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


#ifndef BotHTTPH
#define BotHTTPH

#include <windows.h>
#include <WinSock.h>

#include "GetApi.h"
#include "Strings.h"
#include "BotClasses.h"
#include "BotSocket.h"

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

const PCHAR HTTPNoCache = "no-cashe";

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
const PCHAR ParamPragma = "Pragma";
const PCHAR ParamRange = "Range";
const PCHAR ParamTransferEncoding = "Transfer-Encoding";
const PCHAR ParamConnection = "Connection";
const PCHAR ParamLocation = "Location";
const PCHAR ParamAcceptRanges = "Accept-Ranges";
const PCHAR ParamContentRange = "Content-Range";
const PCHAR ParamLastModified = "Last-Modified";
const PCHAR ParamIfModifiedSince = "If-Modified-Since";
const PCHAR ParamIfNoneMatch = "If-None-Match";
const PCHAR ParamCacheControl = "Cache-Control";
const PCHAR ParamContentMD5   = "Content-MD5";



// ����������� �����
const PCHAR HTTPSpace = " ";
const PCHAR LineBreak = "\r\n";
const PCHAR LineBreak2 = "\r\n\r\n";
const PCHAR ValueDelimeter = ": ";
const PCHAR ValueChunked = "chunked";
const PCHAR ValueNoCacheDocument = "no-store, no-cache, must-revalidate";
const PCHAR URLValueDelimeter = "&";

const PCHAR FormDataURLEncoded = "application/x-www-form-urlencoded";
const PCHAR FormDataMultiPart = "multipart/form-data; boundary=";

const static PCHAR ContentDispositionName = "Content-Disposition: form-data; name=\"";
const static PCHAR FileNameHeader = "; filename=\"";

#define HTTP_CODE_OK 200


// ������� �������� ����������
const PCHAR DefaultPath = "/";
const PCHAR DefaultAccept = "*/*";
const PCHAR DefaultAcceptLanguage = "ru";


const PCHAR HTTPConnectionClose     = "close";
const PCHAR HTTPConnectionKeepAlive = "Keep-Alive";

// ���� HTTP ��������
enum THTTPMethod {hmUnknown, hmGET, hmPOST, hmHEAD};

// ������ HTTP ���������
enum THTTPProtocol {HTTP_1_0, HTTP_1_1};

// �������� ��������� Connection
enum THTTPConnection {hcKeepAlive, hcClose};

enum TPostDataType {pdtUrlEncoded, pdtMultipartFormData};




// �������� HTTP �������
typedef struct THTTPRequestRec
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
} *PHTTPRequestRec;


// �������� ������ HTTP �������
typedef struct THTTPResponseRec
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
	PStrings Headers;      // ������ ���� ����������
	PCHAR ResponseText;    // ����� ������ �������
} *PHTTPResponseRec;


// �������� URL ������
typedef struct TURLREC
{
    PCHAR Protocol;
	PCHAR Host;
	PCHAR Path;
	PCHAR Document;
	PCHAR Arguments;
	PCHAR UserName;
	PCHAR Password;
	WORD Port;
} *PURLREC;



#define HTONS(x) (((x) << 8) | ((x) >> 8))


//--------------------------------------------------------------
//  InitializeWSA - ������� ������������� ���������� WinSocket
//--------------------------------------------------------------
bool InitializeWSA();




//----------------------------------------------------------------------------
//  ������� ��� ������ � ���������
//----------------------------------------------------------------------------

// ������� ��������� �������
PHTTPRequestRec HTTPCreateRequest(PCHAR URL);

// ������� ��������� �������
void HTTPFreeRequest(PHTTPRequestRec Request);

// ������� ������� ��������� HTTP �������
void HTTPClearRequest(PHTTPRequestRec Request);

// ������� ��������� �� ��������� ���� ��������� ������� ������������ �������
void HTTPInitializeRequest(PHTTPRequestRec Request);

// ������� ��������� HTTP ������ � ���������
bool ParseHTTPRequest(PCHAR Buf, PHTTPRequestRec Request);

// ���������  ��������� ������� ������� �� ������
void HTTPSetRequestURL(PHTTPRequestRec Request, PCHAR URL);

namespace HTTPRequest
{

	// ������� �������� ������ �������
	PCHAR Build(PHTTPRequestRec Request);
};


//*****************************************************************************
//  HTTPResponse - ������� ��� ������ � �������� HTTP �������
//*****************************************************************************
namespace HTTPResponse
{
	//  Create - ������� ��������� ������
	PHTTPResponseRec Create();

	//  Clear - �������� ��������� ������
	void Clear(PHTTPResponseRec Response);

	//  Free - ���������� ��������� ������
	void Free(PHTTPResponseRec Response);

	//  Parse - ������� ����� �������
	bool Parse(PCHAR Buf, PHTTPResponseRec Response);
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

void AddURLParam(PStrings S, PCHAR Name, PCHAR Value, DWORD ValueSize = 0); // �������� �������� � ��������� ���� � ������

bool ParseURL(PCHAR URL, PURLREC Rec, bool FullPars = false); // ���������� URL
void ClearURL(PURLREC URL);


PCHAR URLEncode(PCHAR URL, DWORD URLSize = 0); // ���������� URL ������

//------------------------------------------------
//  URLDecode - ������� ���������� URL
//              ������������ ������
//------------------------------------------------
string URLDecode(const char *URL);


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

	// ���������� �������� ���������
	bool SetHeaderValue(PCHAR Buf, DWORD BufSize, DWORD MaxBufSize, PCHAR Header, PCHAR Value, DWORD *NewBufSize);

	// ������� ��������� �� HTML ���������. �������� ������ ���������
	// ����� HTTP �������
	//	������� ���������� ����� ������ ������
    DWORD DeleteHeader(PCHAR Header, PCHAR HTML, DWORD HTMLSize);
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


typedef struct TMultiPartDataRec
{
	PList Items;
	PCHAR Boundary;

    DWORD ReadIndex;  // ������� ��������� ��������
} *PMultiPartData;


enum TMultiItemReadState {mprsUnknown, mprsHeader, mprsData, mprsBoundary, mprsCompleted};

typedef struct TMultiPartItem
{
	PCHAR  Name;        // ��� ����
	PCHAR  FileName;    // ��� �����
	LPVOID Data;        // ����� ������
	DWORD  Size;        // ������ ������
	PCHAR  ContentType; // ��� �������� �����

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

	// �������� ������� ����� ��� ������
	PMultiPartItem AddLongAsStr(PMultiPartData Data, PCHAR Name, DWORD Value);

	// ������� ������ ��������� ���� ������.
	// ��������� - ���������� ����������� ����
	// ���������� - ���� �� ���� �������� ������� �����, ��
	// ������� ������ ����� ������ ���� ������
	DWORD Read(PMultiPartData Data, LPBYTE Buffer, DWORD BufferSize);

	// �������� ������ � ���� ������
	LPBYTE BuildToBuf(PMultiPartData Data, DWORD &ResultSize);
}

//---------------------------------------------------------------
//  ConnectToHost - ������� ������������ � ���������� �����
//---------------------------------------------------------------
SOCKET ConnectToHost(PCHAR Host, int Port);
SOCKET ConnectToHostEx(const char* Host, int Port, DWORD TimeoutSec);


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
        THTTPResponseRec Response; // ��������� ������
	}*PResponseData;

	//********************************************************
	//  ExecuteMethod - ��������� HTTP ������ � �������
	//********************************************************
	bool ExecuteMethod(PHTTPRequestRec Request, PResponseData Response);


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
	bool Get(PCHAR URL, PCHAR *Buf, PHTTPResponseRec Response);


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
	bool Post(PCHAR URL, PStrings Fields, PCHAR *Buf, PHTTPResponseRec Response);
	bool Post(PCHAR URL, PMultiPartData Fields, PCHAR *Buf, PHTTPResponseRec Response);
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


// ***************************************************************************
// ***************************************************************************


class TURL;
class THTTP;


//----------------------------------------------------------------
//   TURL  - ����� ��� ������ ��������� ��������
//----------------------------------------------------------------
class TURL : public TBotObject
{
private:
	bool DoParse(const char *URL);
    void NormalizePath();
public:
	string Protocol;
	string Host;
	string Path;
	string Document;
	string Params;
	WORD Port;

	TURL(const char *URL = NULL);
	~TURL() {};

	void   Clear();
	bool   Parse(const char *URL);
	string GetPathAndDocument();
	string URL(); // ������� �������� ������ �����
};




//----------------------------------------------------------------
//  THTTPRequest - ����� ������������ ��������� ������� � HTTP
//  			   �������
//----------------------------------------------------------------

class THTTPRequest : public TBotObject
{
private:
	friend class THTTP;
	string MakeHeaders();
	void   AddHeader(string &Buf, const char *Name, const char *Value, bool CheckValue = true);
	void   AddHeader(string &Buf, const char *Name, const string &Value, bool CheckValue = true);
	string GetUserAgent();
public:
	THTTPProtocol   Protocol;
	THTTPMethod     Method;
	bool   CloseConnection;  // ����� ������� ������� ����������
	string ProtocolStr;
	string Host;
	string Path;
	WORD   Port;
	string Accept;         // �������������� ���� ������
	string AcceptEncoding; // �������������� ��������� ������
	string UserAgent;      // ��� ������
	string Referer;        // ����� � �������� ����������� �������
	DWORD  ContentLength;  // ������ ���� ������
	string ContentType;    // ��� ���� ������

	THTTPRequest();
	~THTTPRequest() {};

	void SetURL(const char* aURL);
	string MakeRequestHeaders();
};


//----------------------------------------------------------------
//  THTTPResponse - ����� ��������� ��������� ������ HTTP �������
//----------------------------------------------------------------
class THTTPResponse : public TBotObject
{
private:
	string        FHTTPData;
	THTTPRequest* FRequest;

	void Parse();
	bool ParseFirstLine(const char* Line);

	friend class THTTP;
public:
	// �������� ������
	WORD   Code;             // ��� ������
	string Protocol;         // ���������� � ���������
	string StatusLine;       // ���������� � ���� ������
	string ContentType;      // ��� ��������
	int    ContentLength;    // ������ ������. (-1 ��������, ��� ��������� �� �����������)
	string CacheControl;     // ���������� ������������
	string Location;         // ����� �������� ��� ���������
	string Pragma;           // ������ ����� ����������
	string TransferEncoding; // �������� �������� ������
	string MD5;              // MD5 ��� �����������

	bool Chunked;        // ������� ����, ��� ������ ���������� ��������. �� TransferEncoding
	TBotStrings Headers; // ��� ��������� ������

	// ������ ������
	THTTPResponse();
	~THTTPResponse();

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
	bool AddData(PCHAR &Buf, int &BufSize);

	void Clear();
};


//----------------------------------------------------------------
//  THTTPChunks - ����� ��������� �������� ��������� ��������
//                ������  HTTP ��������
//----------------------------------------------------------------
class THTTPChunks : public TBotObject
{
private:
    enum TState {Unknown, IgnoreSizeEnd, IgnoreBlockEnd, WriteData};

    THTTP*      FOwner;
	TBotStream* FStream;
	int    FSize;
	TState FState;
	string FSizeBuf;
	int    FIgnoreSize;
	bool   FLastBlock;
	bool   FCompleted;
	bool GetSize(PCHAR &Buf, int &Size);
	bool Ignore(PCHAR &Buf, int &Size);
	void WriteChunk(PCHAR &Buf, int &Size);
public:
    THTTPChunks(THTTP* Owner, TBotStream* Stream);
	void Initialize(TBotStream* Stream);
	void Write(PCHAR Buf, int BufSize);
    bool Completed();
};



//----------------------------------------------------------------
//  TMultiPartDataItem - ����� �������� ���������� � ����� ������
//                       ������������ �� ������
//----------------------------------------------------------------
class TMultiPartDataItem : public TBotCollectionItem
{
private:
	LPVOID FData;          // ������ ����
	DWORD  FSize;          // ������ ������
	string FName;          // ��� ����
	string FFileName;      // ��� �����
	string FContentType;   // ��� ��������, ��� ������
	string FBlockHeader;   // ��������� �����, ������������ ��� ��������
	TBotStream *FFile;     // ���� ������ ������ �����

	void SetData(LPVOID Data, DWORD DataSize);
	void MakeHeader();
    bool WriteDataToBuf(LPBYTE Buf, DWORD BufSize, DWORD Offset, DWORD &Writen);
	friend class TMultiPartData;
public:
	TMultiPartDataItem(TBotCollection* Owner);
	TMultiPartDataItem(TBotCollection* Owner, LPVOID Data, DWORD DataSize);
	~TMultiPartDataItem();

	LPVOID inline Data() { return FData; }
	DWORD  inline Size() { return FSize; }
};


//----------------------------------------------------------------
//  TMultiPartData - ����� ��� ������ � ������� HTML ����� �
//                   ������� multipart/form-data
//----------------------------------------------------------------
class TMultiPartData : public TBotStream
{
private:
	TBotCollection FItems;
	string FBoundary;

	DWORD FPosition;
	int   FCurrentItem;
	int   FReadOffset;

	enum TReadPart {rpBoundaryStart, rpBoundary, rpBoundaryLB, rpHeader,
					rpData, rpDataLB, rpBoundaryEnd, rpCompleted};

	TReadPart FCurrentPart;

    friend class THTTP;
public:
	TMultiPartData();

	DWORD Size();
	DWORD Read(void* Buf, DWORD BufSize);

	// ������� ���������� ������
	void        Add(const char*   Name, LPVOID Data, DWORD Size);
	void inline Add(const char*   Name, const char* Data)        { Add(Name, (LPVOID)Data, STRA::Length(Data)); }
	void inline Add(const string& Name, LPVOID Data, DWORD Size) { Add(Name.t_str(), Data, Size); };
	void inline Add(const string& Name, const char* Data)        { Add(Name.t_str(), Data); }
	void inline Add(const char*   Name, const string& Data)      { Add(Name, Data.t_str(), Data.Length()); }
	void inline Add(const string& Name, const string& Data)      { Add(Name.t_str(), Data.t_str(), Data.Length()); }

	// ������� ���������� ������
	void AddFile(const char* Name, const char* FileName, const char* CotentType, const char* SendName);
	void AddBlobAsFile(const char* Name, const char* FileName, LPVOID Data, DWORD DataSize, const char* CotentType);

};


//----------------------------------------------------------------
//   THTTP  - ����� ��� ��������-����� ������ �� HTTP ���������
//----------------------------------------------------------------
class THTTP : public TBotObject
{
private:
	TBotSocket  *FSocket;
	THTTPChunks *FChunks;
	bool FSocketCreated;
	bool FDocumentCompleted;
	int  FDocumentSize;

	void Initialize();
	bool Execute(THTTPMethod Method, const char *URL, TBotStream *PostData, TBotStream *ResponseStream);
	bool SendPostData(TBotStream* Data);
	bool ExecuteToStr(THTTPMethod Method, const char *URL, TBotStream *PostData, string &Document);
	bool ReceiveData(TBotStream *ResponseStream);
	void WriteReceivedData(TBotStream* Stream, PCHAR Buf, int BufLen);
	void WriteStringsToStream(TBotStream* Stream, TBotStrings* Strings);

    friend class THTTPChunks;
protected:
	void virtual DoBeforePostData(TBotStream* PostData);
    void virtual DoDownloadCompleted(TBotStream* ResponseData);
public:
	THTTPRequest  Request;
	THTTPResponse Response;
	bool   CheckOkCode;

	// StatusText - ���� CheckOkCode == true �� � ��� ���� �����
	// ������� ����� � ������ ���� ��������� �� 200
	string StatusText;

	// ������ ������
	THTTP();
	THTTP(TBotSocket* Socket);
	virtual ~THTTP();

    int DocumentSize();

	// ��������� ������ ��������� ������� � HTTP �������.
	//
	// �����!!!!!
	// ��� �������, ������� ���������� true ���� ������
	// ������ �������, ������� ������, ���, �� ���������,
	// true ������������ ������ � ��� ������ ����
	// ������� ��������� ������ � �������� ����� � ����� 200!!!
	// ��� ����, ����� �������� ������ ������ � ������ �������� ��������
	// � ��������� ������, �� ������� �������� �� ��� ������,
	// ������� ����������
	// CheckOkCode = false;

	bool   Get(const char *URL, string &Document);
	string Get(const char *URL);
	bool   Get(const char *URL, TBotStream *ResponseData);

	bool   Post(const char *URL, TBotStrings *Fields, string &Document);
	string Post(const char *URL, TBotStrings *Fields);
	bool   Post(const char *URL, TMultiPartData *Fields, string &Document);
	string Post(const char *URL, TMultiPartData *Fields);
};


//-----------------------------------------------
//  DownloadFile - ������� ��������� �������� �
//                 ����
//-----------------------------------------------
bool DownloadFile(const char* URL, const char* FileName);


//---------------------------------------------------------------------------
#endif
