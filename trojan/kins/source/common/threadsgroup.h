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
  ���������� ������� �������.

  ����������: ������� �� �������� ��� ������ �� ������ �������.
              � ������ �� ����� ���� ����� MAXIMUM_WAIT_OBJECTS �������.

*/
#pragma once

namespace ThreadsGroup
{
  typedef struct
  {
    BYTE count;                           //���������� �����.
    HANDLE handles[MAXIMUM_WAIT_OBJECTS]; //������ �����.
  }GROUP;
  
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    �������� ����� ������.
    
    OUT group - ������ �����.
  */
  void _createGroup(GROUP *group);

  /*
    �������� ������� ����������� ��������� �� ������.

    IN OUT group - ������ ��� ���������.
  */
  void _closeTerminatedHandles(GROUP *group);

  /*
    ��������� ���. �������� �������.

    IN group - ������ ��� ���������.

    Return   - ���. �������� �������.
  */
  DWORD _numberOfActiveThreads(GROUP *group);

  /*
    �������� ����� ����.
    
    IN group         - ������ �����.
    IN stackSize     - ������ �����, 0 - ������������ �� ���������.
    IN startAddress  - ����� ����� ����, ��� NULL ���� ��������� ������ ����������� ������.
    IN parameter     - �������� ����� �����.
    OUT threadId     - ID ����, ��� NULL ���� �� �����.
    OUT threadHandle - ����� ����, ��� NULL ���� �� �����. �� � ���� ������ ������ ��������� ����
                        ����� �� ���.

    Return           - true - � ������ ������,
                       false - � ������ ������.
  */
  bool _createThread(GROUP *group, SIZE_T stackSize, LPTHREAD_START_ROUTINE startAddress, LPVOID parameter, LPDWORD threadId, HANDLE *threadHandle);

  /*
    �������� ���������� ���� �����.

    IN group   - ������ �����.
    IN timeout - ����� �������� � �������������, ��� INFINITE ��� ������������ ��������.     
    
    Return     - true - � ������ ������,
                 false - � ������ ������ ��� ��������.

  */
  bool _waitForAllExit(GROUP *group, DWORD timeout);

  /*
    �������� �������� ������ ����� (�� ���������� �����).

    IN group - ������ �����.
  */
  void _closeGroup(GROUP *group);
};
