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
#pragma once
/*
  ����� ������� ��� ������������� ����� ������ � ����������.
*/

namespace Sync
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
    �������� ������������ ������� � ��� ������.

    IN mutexAttributes - SECURITY_ATTRIBUTES ��� ������� ��� NULL.
    IN name            - ��� �������.

    Return             - ����� �������.

    ����������: ��� ������������ ������� ���������� ������� _freeMutex().
  */
  HANDLE _waitForMutex(SECURITY_ATTRIBUTES *mutexAttributes, LPWSTR name);


  /*
    ������������ ������� ������������ ����� WaitForMutex.

    IN mutex - ����� �������.
  */
  void _freeMutex(HANDLE mutex);

  /*
    �������� ����������� �������.

    IN mutexAttributes - SECURITY_ATTRIBUTES ��� ������� ��� NULL.
    IN name            - ��� �������.

    Return             - ����� �������, ��� NULL � ������ ������ ��� ���� ������ ��� ����������.
  */
  HANDLE _createUniqueMutex(SECURITY_ATTRIBUTES *mutexAttributes, LPWSTR name);

  /*
    ���������, ���������� �� ������.

    IN name - ��� �������.

    Return  - true - ����������,
              false - �� ���������.
  */
  bool _mutexExists(LPWSTR name);

  DWORD _waitForMultipleObjectsAndDispatchMessages(DWORD count, const HANDLE* handles, bool waitAll, DWORD milliseconds);
};