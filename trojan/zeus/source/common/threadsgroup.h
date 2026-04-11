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
  ���������� ������� �������.

  ����������: ������� �� �������� ��� ������ �� ������ �������.
              � ������ �� ����� ���� ����� MAXIMUM_WAIT_OBJECTS �������.

*/
#pragma once

namespace ThreadsGroup
{
  typedef struct
  {
    BYTE count;                           //Kolichetsvo threads.
    HANDLE handles[MAXIMUM_WAIT_OBJECTS]; //Handles threads.
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

  /*    Closure of the Handel group of threads (not the end of threads).

    IN group - a group of threads.
  */
  void _closeGroup(GROUP *group);
};
