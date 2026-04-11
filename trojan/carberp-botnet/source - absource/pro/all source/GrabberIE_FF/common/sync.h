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
    �������� �������, � ��������� ���� ������� ��������� ������.

    IN count        - ���. ��������.
    IN handles      - �������.
    IN waitAll      - ����� ���� �������.
    IN milliseconds - ����� �������� � ��, INFINITE ��� ������������ ��������.

    Return          - �������� WaitForMultipleObjects().
  */
  DWORD _waitForMultipleObjectsAndDispatchMessages(DWORD count, const HANDLE* handles, bool waitAll, DWORD milliseconds);

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
};