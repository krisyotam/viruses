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
  ������ � GUI.
*/
#pragma once

namespace Gui
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
    ������� ��� _enumWindows().

    IN window - ����.
    IN param  - ��������.
    
    Return    - true  - ���������� �����,
                false - �������� �����.
  */
  typedef bool (ENUMWINDOWSPROC)(HWND window, void *param);

  /*
    ������������ �������� ����.

    IN owner     - ��������, ����� ���� NULL.
    IN topToDown - true - ����������� � ����� ����, false - ����� �����.
    IN proc      - ������.
    IN param     - �������� ��� �������.
  */
  void _enumWindows(HWND owner, bool topToDown, ENUMWINDOWSPROC proc, void *param);

  /*
    ������ ������� �������� �������� ��� WindowFromPoint(), ������� ���������� HTTRANSPARENT.
    ������ ���������� ������� ������, �� ��� �� ������� ����� ����� ����������� �������.

    IN point    - ���������� ��� ������ ����.
    IN timeout  - ������� ��� WM_NCHITTEST.
    OUT hitTest - HitTest ����. ����� ���� NULL.

    Return      - ����� ����, ��� NULL.
  */
  HWND _windowFromPoint(POINT point, DWORD timeout, DWORD *hitTest);

  /*
    ��������� ����� �� ����� ���� ������� � ���������� �������.

    IN style - ����� ����.

    Return   - true - ����� ����� �������,
               false - �� �����.
  */
  bool _styleHaveSizeBorders(DWORD style);

  /*
    �������� ������ ��� shared (�� ������� ��������).

    IN module - ������.
    IN id     - ID.
  */
  HICON _loadSharedIcon(HMODULE module, const LPWSTR id);
  
  /*
    ��������� ������ ���� � ���������� ������.

    IN window - ����.
    OUT size  - ������ ������ ��� �������� ��������. ����� ���� NULL.

    Return    - ����� ���� (����� ���������� ����� NULL), ��� NULL � ������ ������.
  */
  LPWSTR _getWindowText(HWND window, LPDWORD size);

  /*
    �������� ������� ��� shared (�� ������� ��������).

    IN module - ������.
    IN id     - ID.
  */
  HCURSOR _loadSharedCursor(HMODULE module, const LPWSTR id);

  /*
    �������� ������ FONT_DIALOG.

    IN pointSize - ������ ������ � �������, ������������� �������� 8.

    Return       - ����� ������, ��� NULL � ������ ������.
  */
  HFONT _createDialogFont(BYTE pointSize);

  /*
    ������ ������� ������ �����.

    IN owner          - ����� ��������
    IN initialDir     - ���������� ������������ ������� ����������� ������. ����� ���� NULL.
    IN OUT fileBuffer - �� ����� - ����������������� ����/����,
                        �� ������ - ��������� ����.

    Return            - true - � ������ ������,
                        false - � ������ �������.
  */
  bool _browseForFile(HWND owner, LPWSTR initialDir, LPWSTR fileBuffer);

  /*
    ������ ������� ���������� �����.

    IN owner            - ����� ��������
    IN initialDir       - ���������� ������������ ������� ����������� ������. ����� ���� NULL.
    IN OUT fileBuffer   - �� ����� - ����������������� ����/����,
                          �� ������ - ��������� ����.
    IN defaultExtension - ���������� �� ��������� (��� �����). ����� ���� NULL.
    IN filter           - ������. ��. OPENFILENAME.lpstrFilter.
    IN filterIndex      - ��������� ������ �������� � filter.

    Return              - true - � ������ ������,
                          false - � ������ �������.
  */
  bool _browseForSaveFile(HWND owner, LPWSTR initialDir, LPWSTR fileBuffer, LPWSTR defaultExtension, LPWSTR filter, DWORD filterIndex);

  /*    Initialize common controls (front-end for InitCommonControlsEx ()).

    IN classes - ICC_ *.

    Return - true - if successful,
                 false - if an error occurs.
  */
  bool _loadCommonControl(DWORD classes);
};
