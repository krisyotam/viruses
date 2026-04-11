/*
  name      KINS
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

  /*
    ������� ��� CreateDIBSection, ������ ��������� ����� ������ ������� DIBSection.

    IN dc            - DC.
    IN width         - ������ �������.
    IN height        - ������ �������.
    OUT bitmapInfo   - ���������� � �������, ������ ���� ����������� ����� Mem. ����� ���� NULL.
    OUT bitmapBits   - ����� ������ �������.
    IN fileMap       - ������ Map-����, ��� NULL.
    IN fileMapOffset - ������ � fileMap.

    Return           - ������, ��� NULL.

    ����������: ������ ������ ����� � ������� BI_RGB � ������� 8/16/32.
  */
  HBITMAP _createDibSection(HDC dc, int width, int height, BITMAPINFO **bitmapInfo, void **bitmapBits, HANDLE fileMap, DWORD fileMapOffset);
};
