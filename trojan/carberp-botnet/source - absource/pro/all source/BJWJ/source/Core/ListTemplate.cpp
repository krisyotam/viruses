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

//*****************************************************************************
//
//     ��� ���������� ������ ������������� ������ � ��������� ������� ������
//     ���������� ������� ������� � ��������� ����
//
//*****************************************************************************


#ifndef BotClassesH
	#error Exclude module from project
#endif


#define LISTFUNC(Result_Type) template<class TItem> Result_Type TListTemplate<TItem>
#define LISTCONSTRUCT() template<class TItem> TListTemplate<TItem>


LISTCONSTRUCT()::TListTemplate()
{
	// ����������� ������
	FCount    = 0;
	FCapacity = 0;
	FItems    = NULL;

	// ��-�� ����, ��� ��� ��������� ������� �� ��������
	// � � �������� ��������� ��������� �� �� ����� �������������
	// ����������� �� ��������� ���������, ������������ ������
	// �������, ������� ����� ���������� � ������ ������
	// ������������� ��� ��������.
	m_memset(&FEmptyItem, 0, sizeof(TItem));
}
//-------------------------------------------------------------------

LISTCONSTRUCT()::~TListTemplate()
{
	// ���������� ������
	Clear();
}

//-------------------------------------------------------------------

LISTFUNC(int)::Add(TItem Item)
{
	// ��������� ������� � ������

	if (FCount == FCapacity)
	{
		if (!UpdateCapacity())
			return -1;
    }

	int Index = FCount;
	FItems[FCount] = Item;
	FCount++;

	return Index;
}
//-------------------------------------------------------------------

LISTFUNC(int)::Count()
{
    return FCount;
}
//-------------------------------------------------------------------

LISTFUNC(void)::Clear()
{
	// ������� ������� ������

	if (!FItems) return;

	// �������� ��� �������� �������� �� ������ ���������� ����������
	// �������������� ��������, �� ����� �������� ��������� ���������
	// ������� � �����
	while (FCount)
	{
		FCount--;
		if (FItems[FCount])
			DoDelete(FItems[FCount]);
    }

    // �������� ����
	FCapacity = 0;

	HEAP::Free(FItems);
	FItems = NULL;
}
//-------------------------------------------------------------------

LISTFUNC(void)::Delete(int Index)
{
	// ������� ������� �� ������
	if (!CheckIndex(Index)) return;

	TItem Temp = FItems[Index];

	FCount--;
	if (Index < FCount)
	{
		// ��������� ���� ������ ����������� �� �������� ���������
		TItem* Dest = FItems;
		Dest += Index;
		TItem* Source = Dest;
		Source++;
        m_memcpy(Dest, Source, (FCount - Index) * sizeof(TItem));
	}

	// ��� ������������� ���������� �������
	DoDelete(Temp);
}
//-------------------------------------------------------------------

LISTFUNC(void)::DoDelete(TItem Item)
{
	// ��������������� ��� �������������� �������� ��� ����������
	// ��� �� �������� �� ������
}
//-------------------------------------------------------------------

LISTFUNC(int)::IndexOf(TItem Item)
{
	// ������� ���������� ������� �������� � ������

	for (int i = 0; i < FCount; i++)
	{
		if (FItems[i] == Item) return i;
	}

	return -1;
}
//-------------------------------------------------------------------

LISTFUNC(int)::Remove(TItem Item)
{
	// ������� ������� ��������� ������� �� ������
	int Index = IndexOf(Item);

	if (Index >= 0)
        Delete(Index);

	return Index;
}
//-------------------------------------------------------------------

LISTFUNC(bool)::SetCapacity(int Value)
{
	// ������ ����������� ������
	if (Value > FCount && Value != FCapacity)
	{
        // ������ ����� �����
		if (HEAP::ReAlloc2((LPVOID &)FItems, Value * sizeof(TItem)))
		{
			FCapacity = Value;
			return true;
        }
	}
	return false;
}
//-------------------------------------------------------------------

LISTFUNC(bool)::UpdateCapacity()
{
	// ������� ��������� ���� ������
	DWORD Delta;
	if (FCapacity > 64)
		Delta = FCapacity / 4;
	else
	if (FCapacity > 8)
		Delta = 16;
	else
		Delta = 4;

	return SetCapacity(FCapacity + Delta);
}
//-------------------------------------------------------------------

LISTFUNC(bool)::CheckIndex(int Index)
{
	// ������� ��������� ������������ �������
	return Index >= 0 && Index < FCount;
}
//-------------------------------------------------------------------

LISTFUNC(TItem)::GetItem(int Index)
{
	// ������� ���������� ������� � ��������� ��������
    return (CheckIndex(Index)) ? FItems[Index] : FEmptyItem;
}
//-------------------------------------------------------------------

LISTFUNC(void)::SetItem(int Index, TItem Item)
{
	// ������� ������������� ������� � ��������� ��������
	if (CheckIndex(Index))
		FItems[Index] = Item;
}
//-------------------------------------------------------------------

LISTFUNC(TItem)::operator[](int Index)
{
    return GetItem(Index);
}
//-------------------------------------------------------------------
