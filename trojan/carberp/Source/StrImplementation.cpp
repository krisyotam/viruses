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

#ifndef StringsH
	#error ��������� ���� �� �������
#endif


#include "Memory.h"


//*****************************************************************************
//                               STRUTILS
//*****************************************************************************

#define CHARAPI(Result_Type) template<class TChar> Result_Type STRUTILS<TChar>


// ������� ���������� ������ ���� ������ ������
CHARAPI(bool)::IsEmpty(const TChar* Str)
{
	return Str == NULL || *Str == 0;
}
//-----------------------------------------------------------------------------


CHARAPI(DWORD)::Length(const TChar* Str)
{
	// ������� ����������� ����� ������
	DWORD Len = 0;
	if (Str != NULL)
		while (*Str++) Len++;

	return Len;
}
//-----------------------------------------------------------------------------


// ������� ���� ��������� ��������� � ������
CHARAPI(int)::Pos(const TChar* Str, const TChar *SubStr)
{
	if (IsEmpty(Str) || IsEmpty(SubStr))
		return -1;

    const TChar* Temp = Str;
	while (*Temp)
	{
		if (*Temp == *SubStr)
		{
			// ���������� ������� �������, ��������� ������ ����������
			const TChar* S1 = Temp;
			const TChar* S2 = SubStr;
			while (*S1 && *S2 && *S1 == *S2) {S1++; S2++;}
			if (*S2 == 0) return Temp - Str;
		}
		Temp++;
    }
    return -1;
}
//-----------------------------------------------------------------------------


CHARAPI(bool)::Equal(const TChar* Str1, const TChar* Str2)
{
	// ������� ���������� ������ ���� ������ ���������
	if (Str1 == Str2 || (IsEmpty(Str1) && IsEmpty(Str2)))
		return true;
	else
    	return Compare(Str1, Str2) == 0;
}
//-----------------------------------------------------------------------------

CHARAPI(int)::Compare(const TChar* Str1, const TChar* Str2)
{
	// ������� ���������� ��� ������

	if (Str1 == NULL || Str2 == NULL)
		return -1;

	const TChar* S1 = Str1;
	const TChar* S2 = Str2;

	while(1)
	{
		if (*S1 != *S2)
		{
			if (*S1 > *S2)
				return 1;
			else
            	return -1;
		}

		if (*S1 == 0) return 0;

		S1++;
		S2++;
    }
}
//-----------------------------------------------------------------------------

template<class TChar>
void _Str_MoveChars(const TChar *Str, DWORD StrLen, DWORD Position, int Count)
{
	// ������� �������� ������� � ����� �����������
	const TChar *StartPtr = Str + Position;
	const TChar *EndPtr   = Str + StrLen;

	if (Count > 0)
	{
    	// �������� � �����
		TChar *ToCopy   = (TChar*)(Str + (StrLen + Count));
		while (EndPtr >= StartPtr)
		{
			*ToCopy = *EndPtr;
			ToCopy--;
			EndPtr--;
		}
	}
	else
	{
    	// �������� �����
		TChar *ToCopy   = (TChar*)(Str + (Position + Count));
		if (ToCopy < Str) ToCopy = (TChar*)Str;
		while (StartPtr <= EndPtr)
		{
			*ToCopy = *StartPtr;
			ToCopy++;
			StartPtr++;
		}
    }
}
//-----------------------------------------------------------------------------

template<class TChar>
void _Str_Insert(const TChar *Str, DWORD StrLen, DWORD Position, const TChar *SubStr, DWORD SubStrLen)
{
	_Str_MoveChars<TChar>(Str, StrLen, Position, SubStrLen);
	m_memcpy((void*)(Str + Position), (void*)SubStr, SubStrLen * sizeof(TChar));
}
//-----------------------------------------------------------------------------

template<class TChar>
struct TStrReplaceData
{
	DWORD  StartPosition;
	TChar* Str;
	DWORD  StrLen;
	TChar* SubStr;
	DWORD  SubStrLen;
	TChar* NewStr;
	DWORD  NewStrLen;
	DWORD  Count;
	PDWORD Positions;
};

// ������� �������������� ������ ��� ������ ��������
template<class TChar>
bool _Str_Replace_Initialize(TStrReplaceData<TChar> *Data)
{

	// ���������� �������� ���������
	int P = STRUTILS<TChar>::Pos(Data->Str + Data->StartPosition, Data->SubStr);
	if (P  < 0) return false;

	Data->Count++;
	Data->StartPosition += P + Data->SubStrLen;
	DWORD Index = Data->Count - 1;
	// ���������� �����
	_Str_Replace_Initialize<TChar>(Data);

	// ��������� ������� � ������
	if (Data->Positions == NULL)
		Data->Positions = (PDWORD)HEAP::Alloc(Data->Count * sizeof(DWORD));

	Data->Positions[Index] = P;

	return Data->Count > 0;
}

template<class TChar>
void _Str_Replace(TStrReplaceData<TChar> *Data)
{
	// ������� ��������� ������� ����� ������ �� ���������� ������
	// �������� ������������� �����
	int Delta = Data->NewStrLen - Data->SubStrLen;

	TChar *Str = Data->Str;
	DWORD StrLen = Data->StrLen;

	for (DWORD i = 0; i < Data->Count; i++)
	{
    	// ���������� ������� �����
		int P = Data->Positions[i];
		Str += P;
		StrLen -= P;

		// ������� ������
		_Str_MoveChars(Str, StrLen, Data->SubStrLen, Delta);

		// �������� ������
		m_memcpy(Str, Data->NewStr, Data->NewStrLen * sizeof(TChar));

		Str += Data->NewStrLen;
		StrLen -= (Data->NewStrLen - Delta);
	}
}

//-----------------------------------------------------------------------------
CHARAPI(void)::Expand(const TChar *Str, DWORD Position, int Count)
{
	// ������� ��������� ������ Str � ������� Position ��
	// Count ��������
	if (IsEmpty(Str) || Count == 0)
		return;

	DWORD StrLen = Length(Str);
    _Str_MoveChars<TChar>(Str, StrLen, Position, Count);
}
//-----------------------------------------------------------------------------

//  ������� ��������� ��������� � ������
CHARAPI(void)::Insert(const TChar *Str, const TChar *SubStr, DWORD Position)
{
	if (IsEmpty(Str) || IsEmpty(SubStr))
		return;
	DWORD StrLen    = Length(Str);
	DWORD SubStrLen = Length(SubStr);

	if (Position <= StrLen)
        _Str_Insert(Str, StrLen, Position, SubStr, SubStrLen);
}
//-----------------------------------------------------------------------------

// ������� �������� ��� ������ SubStr � ������ Str �� ������ NewStr
CHARAPI(void)::Replace(const TChar *Str, const TChar *SubStr, const TChar *NewStr)
{
	if (IsEmpty(Str) || IsEmpty(SubStr))
		return;

	// ���������� �������
	TStrReplaceData<TChar> Data;
	ClearStruct(Data);

	Data.Str       = (TChar*)Str;
	Data.StrLen    = Length(Str);
	Data.SubStr    = (TChar*)SubStr;
	Data.SubStrLen = Length(SubStr);
	Data.NewStr    = (TChar*)NewStr;
	Data.NewStrLen = Length(NewStr);

	_Str_Replace_Initialize(&Data);
	if (Data.Count == 0) return;

	// �������� ������
    _Str_Replace<TChar>(&Data);

	//��������� ������
    HEAP::Free(Data.Positions);

}
//-----------------------------------------------------------------------------

// ������� ����������� ��� ������
CHARAPI(DWORD)::Hash(const TChar* Str, DWORD Len, bool LowerCase)
{
	// ������� ����������� ��� ������
	// Str - �������� ������
	// Len - ����� ������, ���� ����� 0, �� ������������� �� ��������� ����
	// LowerCase - ��������� ������� � ������ ������� ����� ��������� ����

	if (Str == NULL) return (DWORD)-1; // �������� �����

	DWORD H = 0;

	for (DWORD i = 0; *Str != 0 && (Len == 0 || i < Len); Str++, i++)
	{
		TChar Ch = *Str;
		if (LowerCase) LowerChar(Ch);
		H = (( H << 7 ) & (DWORD)( -1 ) ) | ( H >> ( 32 - 7 ));
		H = H ^ Ch;
	}

	return H;
}


CHARAPI(DWORD)::Hash(const TChar* Str)
{
    return Hash(Str, 0, false);
}
//-----------------------------------------------------------------------------

// ������� ���� ������ ��������� ������� � ������
CHARAPI(TChar*)::Scan(const TChar *Str, TChar Char)
{
	if (Str != NULL)
		while (*Str != 0)
		{
			if (*Str == Char) return (TChar*)Str;
			Str++;
		}
	return NULL;
}


// ������� ���������� ��������� �� ����� ������
CHARAPI(TChar*)::End(const TChar *Str)
{
	if (Str)
		while (*Str) Str++;
	return (TChar*)Str;
}



// ������� ����������� ����� ����� � ������.
// ������� �� ������ ������.
// � ��������� n ���������� ���������� ��������
// ���� ������� ������� � ������� ������� �� �������
// ��������� ����������� ������ ������
CHARAPI(void)::LongToString(DWORD num, TChar* Str, int &n)
{
	// ����������� ��������� ��������
	// ���� n �� ����� ���� ������ ��� ������ ���������
	// � ������� � ����� ��� ��������
	if (!n)
	{
		if (!num)
			n = 1;
		else
			for (int j = 1; num/j !=0; j *= 10) n++;
    }

    // ���� ���� ������� �� ��� ������ ���������� ��������
	if (!Str) return;

	// ���������������
	int i = 1;
	int d = 0;
	do
	{
		d = num % 10;
		num /= 10;
		Str[n-i]=(char)(d+48);
		i++;
	}
	while(num != 0);
}



//*****************************************************************************
//                               STRBUF
//*****************************************************************************

STRBUFAPI(TChar*) STRBUF::Alloc(DWORD Size)
{
	// ������� ������ ������ �������� Size ��������
	// ����� ������ ��������������� �������
	if (Size == 0) return NULL;

	#ifdef USE_BLOCKS_STRINGS
        Size = ((Size / STRING_BLOCK_SIZE) + 1) * STRING_BLOCK_SIZE;
	#endif

	DWORD BufSize = (Size + 1) * sizeof(TChar) + sizeof(TStrRec);
	TStrRec* Buf = (TStrRec*)HEAP::Alloc(BufSize);
	if (Buf == NULL) return NULL;

	Buf->Size     = Size;
	Buf->Length   = 0;
	Buf->RefCount = 1;

	Buf++;
	return (TChar*)Buf;
}
//----------------------------------------------------------------------------

STRBUFAPI(void) STRBUF::Release(TChar* &Str)
{
	// ������� ��������� ������� ������ �, ��� �������������, ���������� ������
	if (Str)
	{
		TStrRec &R = GetRec(Str);
		R.RefCount--;
		if (R.RefCount == 0)
            HEAP::Free(&R);
        Str = NULL;
    }
}

//----------------------------------------------------------------------------

STRBUFAPI(TChar*) STRBUF::AddRef(TChar* Str)
{
	// ������� ����������� ������� ������ ������ � ���������� ��������� �� ��
	if (Str)
		GetRec(Str).RefCount++;
	return Str;
}
//----------------------------------------------------------------------------

STRBUFAPI(void) STRBUF::Unique(TChar* &Str)
{
	// ������� ������������� ������
	if (Str)
	{
		TStrRec &R = GetRec<TChar>(Str);
		if (R.RefCount > 1)
		{
			R.RefCount--;
            Str = CreateFromStr(Str, R.Length, 0);
        }
    }
}
//----------------------------------------------------------------------------


STRBUFAPI(STRBUF::TStrRec&) STRBUF::GetRec(TChar* Str)
{
	// ������� ���������� ���������� ��������� ������
	TStrRec* R = (TStrRec*)Str;
    return R[-1];
}
//----------------------------------------------------------------------------

// ������� ���������� ����� ������
STRBUFAPI(DWORD) STRBUF::Length(TChar *Str)
{
	return (Str)? GetRec(Str).Length : 0;
}
//----------------------------------------------------------------------------


STRBUFAPI(TChar*) STRBUF::CreateFromStr(const TChar* Str, DWORD StrLen, DWORD ResultStrSize)
{
	// ������ ������ �� ������ �������� ������
	if (STRUTILS<TChar>::IsEmpty(Str))
		return NULL;

	if (StrLen == 0)
		StrLen = STRUTILS<TChar>::Length(Str);

    DWORD ResSize = Max(StrLen, ResultStrSize);
	TChar* Result = Alloc<TChar>(ResSize);
	if (Result)
	{
		// �������� ������ ������
		m_memcpy(Result, Str, StrLen * sizeof(TChar));
		GetRec(Result).Length = StrLen;
	}
	return Result;
}
//----------------------------------------------------------------------------


STRBUFAPI(void) STRBUF::Append(TChar* &Dst, const TChar* Src, DWORD SrcLen)
{
	// ������� ��������� � ������ Dst ������ Src
	if (STRUTILS<TChar>::IsEmpty(Src))
		return;


	if (SrcLen == 0)
		SrcLen = STRUTILS<TChar>::Length(Src);

	if (Dst == NULL)
	{
    	// ������ ������ �� ������ �������� ������
		Dst = CreateFromStr<TChar>(Src, SrcLen, 0);
	}
	else
	{
		// ���������� ��� ������
		TStrRec &R = GetRec(Dst);
		TChar* Tmp = NULL;
		DWORD DstLen = R.Length;
		DWORD TotalLen = SrcLen + DstLen;
		if (R.Size < TotalLen || R.RefCount > 1)
		{
        	Tmp = Dst;
			Dst = CreateFromStr<TChar>(Tmp, DstLen, TotalLen);
        }
		m_memcpy(Dst + DstLen, Src, SrcLen);
		GetRec(Dst).Length = TotalLen;

		if (Tmp)
			Release<TChar>(Tmp);
    }
}
//----------------------------------------------------------------------------

STRBUFAPI(void) STRBUF::Copy(TChar* &Dst, const TChar* Src, DWORD Pos, DWORD Count)
{
	// ������� �������� ���������� �������� Count � ������� Pos
	if (STRUTILS<TCHAR>::IsEmpty(Src) || Count == 0)
		return;

	if (Dst == NULL)
	{
		// ������ ����� ������
        Dst = CreateFromStr(Src + Pos, Count, 0);
	}
	else
	{
		TStrRec &R = GetRec(Dst);

		// � ������ ��� ����� ��� ������ ��������� ��� �������
		// - ���������� �����. ���� ������ ������� �� ������ ����� ������
		// - ����� ������. ���� ����� ������� � ������ ������ ��������� �����������
		//                 ������ ���������� �������� �� ������, ��� ������ ������
		//				   ���������� ���������� � ������ ������ ��������

		if (R.RefCount == 1 && R.Length == 0 && R.Size >= Count)
		{
			m_memcpy(Dst, Src + Pos, Count * sizeof(TChar));
			R.Length = Count;
            *(Dst + Count) = 0;
		}
		else
		{
			// �� ������ ���� ����������� ���������� �� ����� ����
			// ��������� ������ ����� �����������
			TCHAR* Tmp = Dst;
			Dst = CreateFromStr(Src + Pos, Count, 0);
			Release<TChar>(Tmp);
		}
	}
}
//----------------------------------------------------------------------------

STRBUFAPI(void) STRBUF::Insert(TChar* &Buf, const TChar* Str, DWORD Position, DWORD StrLen)
{
	// ������� ��������� ������ Str � �����
	if (STRUTILS<TChar>::IsEmpty(Str))
		return;


	if (Buf == NULL)
	{
		// ����� ������, ���� ������� ������� ����� ����, �� ������ ������
		// �� ������ ����������� ������
		if (Position == 0)
        	Buf = CreateFromStr(Str, 0, 0);
        return;
    }

	// ��������� ������
	if (StrLen == 0)
		StrLen = STRUTILS<TChar>::Length(Str);

	TStrRec &R = GetRec<TChar>(Buf);

	// ��������� �������
	if (Position > R.Length)
		return;

	// ���������� ������ ������
	DWORD Len = R.Length;
	DWORD TotalLen = Len + StrLen;
	if (R.Size < TotalLen || R.RefCount > 1)
	{
		// ������ ����� ������
		TChar *Tmp = Buf;
        Buf = CreateFromStr<TChar>(Tmp, Len, TotalLen);
		Release<TChar>(Tmp);
	}

   	_Str_Insert(Buf, Len, Position, Str, StrLen);

	// ��������� ������
	GetRec(Buf).Length = TotalLen;
}

//----------------------------------------------------------------------------


// ������� �������� ��������� � ������
STRBUFAPI(void) STRBUF::Replace(TChar* &Str, const TChar* SubStr, DWORD SBLen, const TChar* NewStr, DWORD NSLen)
{
	if (Str == NULL || STRUTILS<TChar>::IsEmpty(SubStr))
		return;

	TStrRec &R = GetRec<TChar>(Str);


	TStrReplaceData<TChar> D;
	ClearStruct(D);

	D.Str       = Str;
	D.StrLen    = R.Length;
	D.SubStr    = (TChar*)SubStr;
    D.SubStrLen = (SBLen)? SBLen : STRUTILS<TChar>::Length(SubStr);
	D.NewStr    = (TChar*)NewStr;
	D.NewStrLen = (NSLen)? NSLen : STRUTILS<TChar>::Length(NewStr);

	// �������������� ������
	if (!_Str_Replace_Initialize<TChar>(&D)) return;

	// ����������� ����� ����� ������
	int Delta = D.NewStrLen - D.SubStrLen;
    DWORD TotalLen = R.Length + (D.Count * Delta);


	// �������� ������
	if (R.RefCount > 1 || R.Size < TotalLen)
	{
		TChar *Tmp = Str;
		Str = CreateFromStr(Tmp, R.Length, TotalLen);
		Release<TChar>(Tmp);
		D.Str = Str;
    }


    _Str_Replace<TChar>(&D);

    GetRec<TChar>(Str).Length = TotalLen;

	//��������� ������
    HEAP::Free(D.Positions);
}
//----------------------------------------------------------------------------



//*********************************************************************
//   							TString
//*********************************************************************

#define STRFUNC(Result_Type) template<class TChar> Result_Type TString<TChar>
#define STRCONSTRUCTOR() template<class TChar> TString<TChar>

STRCONSTRUCTOR()::TString(unsigned long StrBufSize)
{
	Data = STRBUF::Alloc<TChar>(StrBufSize);
}

STRCONSTRUCTOR()::TString(const TString& src)
{
	Data = STRBUF::AddRef<TChar>(src.Data);
}


STRCONSTRUCTOR()::TString(const TChar* Src)
{
	Data = STRBUF::CreateFromStr<TChar>(Src, 0, 0);
}


STRCONSTRUCTOR()::TString(const TChar* src, DWORD copylen)
{
	Data = STRBUF::CreateFromStr<TChar>(src, copylen, 0);
}

STRCONSTRUCTOR()::~TString()
{
	STRBUF::Release<TChar>(Data);
}


STRFUNC(DWORD)::Length() const
{
	return  STRBUF::Length<TChar>(Data);
}

STRFUNC(DWORD)::CalcLength()
{
	if (Data)
		STRBUF::GetRec<TChar>(Data).Length = STRUTILS<TChar>::Length(Data);
	return Length();
}

STRFUNC(bool)::IsEmpty() const
{
	return STRUTILS<TChar>::IsEmpty(Data);
}


STRFUNC(TChar*)::t_str() const
{
	// ������� ���������� ��������� �� ������
	// � ������ ���������� ������ ������� ����������
	// ��������� �� ������ ������
	return (Data)? Data : (TChar*)L"";
}

STRFUNC(void)::Clear()
{
	STRBUF::Release<TChar>(Data);
}


STRFUNC(void)::Copy(const TChar* Source, DWORD Position, DWORD Count)
{
	STRBUF::Copy<TChar>(Data, Source, Position, Count);
}


STRFUNC(void)::Copy(const TString &Source, DWORD Position, DWORD Count)
{
	STRBUF::Copy<TChar>(Data, Source.Data, Position, Count);
}

STRFUNC(void)::Insert(const TChar* Str, DWORD Position)
{
    STRBUF::Insert<TChar>(Data, Str, Position, 0);
}


STRFUNC(void)::Insert(const TString &Str, DWORD Position)
{
	STRBUF::Insert<TChar>(Buf, Str.Data, Position, Str.Length());
}


STRFUNC(void)::Replace(const TChar* Str, const TChar* NewStr)
{
	STRBUF::Replace<TChar>(Data, Str, 0, NewStr, 0);
}

STRFUNC(void)::Replace(const TString &Str, const TString &NewStr)
{
	STRBUF::Replace<TChar>(Data, Str, Str.Length(), NewStr, NewStr.Length());
}


STRFUNC(DWORD)::Hash()
{
	return STRUTILS<TChar>::Hash(Data);
}

STRFUNC(DWORD)::Hash(DWORD Len, bool LowerChar)
{
	return STRUTILS<TChar>::Hash(Data, Len, LowerChar);
}

STRFUNC(void)::Unique()
{
    STRBUF::Unique<TChar>(Data);
}


STRFUNC(void)::ConvertToLinuxFormat()
{
	// ������� ��������������� ������ � ������� Linux
	if (Data)
	{
		// ��������� ��������� �������
		TChar *Start = STRUTILS<TChar>::Scan(Data, '\r');
		if (Start)
		{
			// ��������� ������� � ������������� ������
			DWORD Pos = Start - Data;
			Unique();

			// �������� ��� ��������
			TChar *Str   = Data + Pos;
			TChar *ToCopy = Str;
			while (*Str != 0)
			{
				if (*Str != '\r')
				{
					*ToCopy = *Str;
					ToCopy++;
				}
                Str++;
			}

			*ToCopy = 0;
			STRBUF::GetRec<TChar>(Data).Length = ToCopy - Data;
		}

	}


}


STRFUNC(void)::SetLength(DWORD NewLength)
{
	// ������� ������������� ����� ������
	if (NewLength == 0)
		STRBUF::Release<TCHAR>(Data);
	else
	{
		if (Data)
		{
			STRBUF::TStrRec &Rec = STRBUF::GetRec<TCHAR>(Data);

			if (Rec.RefCount > 1 || Rec.Size < NewLength)
			{
				TCHAR* Tmp = Data;
				Data = STRBUF::CreateFromStr<TCHAR>(Tmp, Rec.Length, NewLength);
				STRBUF::Release<TCHAR>(Tmp);
			}
			*(Data + NewLength) = 0;
		}
		else
			Data = STRBUF::Alloc<TCHAR>(NewLength);

        STRBUF::GetRec<TCHAR>(Data).Length = NewLength;
	}
}


STRFUNC(int)::Pos(const TChar* SubStr) const
{
	return STRUTILS<TCHAR>::Pos(Data, SubStr);
}

STRFUNC(int)::Pos(const TString &SubStr) const
{
	return STRUTILS<TCHAR>::Pos(Data, SubStr.Data);
}


STRFUNC(TString<TChar>&)::Format(const TChar *FormatLine, ...)
{
	// ������� ����������� ������
	STRBUF::Release<TCHAR>(Data);

	// ��� ��� ���������� �� ���������� ����������
	// �������������� ������ ������ ����������� ������
	// � ������������� �����

	// �������� ����������� �������������� ������ ������
	TString<TChar> Tmp(1024);

	va_list paramList;
	va_start(paramList, FormatLine);

	int Sz = (sizeof(TChar) == 1) ? (int)pwvsprintfA(Tmp.t_str(), FormatLine, paramList) :
                                    (int)pwvsprintfW(Tmp.t_str(), FormatLine, paramList);
	va_end(paramList);

	Data = STRBUF::CreateFromStr<TCHAR>(Tmp.t_str(), Sz, 0);

	return *this;
}


STRFUNC(TString<TChar>&)::LongToStr(DWORD num)
{
	STRBUF::Release<TCHAR>(Data);
	int n = 0;
	STRUTILS<TChar>::LongToString(num, NULL, n);
	SetLength(n);
	STRUTILS<TChar>::LongToString(num, Data, n);
	return *this;
}



STRFUNC(TString<TChar>&)::operator=(const TString &Source)
{
	if (Data != Source.Data)
	{
		STRBUF::Release<TChar>(Data);
		Data = STRBUF::AddRef<TChar>(Source.Data);
    }
	return *this;
}

STRFUNC(TString<TChar>&)::operator=(const TChar* Source)
{
	STRBUF::Release<TChar>(Data);
	Data = STRBUF::CreateFromStr<TChar>(Source, 0, 0);
	return *this;
}

STRFUNC(TString<TChar>&)::operator+=(const TString &Source)
{
	if (Source.Data)
		STRBUF::Append<TChar>(Data, Source.Data, Source.Length());
	return *this;
}

STRFUNC(TString<TChar>&)::operator+=(const TChar* Source)
{
	if (Source)
    	STRBUF::Append<TChar>(Data, Source, 0);
	return *this;
}

STRFUNC(TString<TChar>)::operator+(const TString &Source)
{
	TString<TChar> Temp(*this);
	Temp += Source;
	return Temp;
}

STRFUNC(TString<TChar>)::operator+(const TChar* Source)
{
	TString<TChar> Temp(*this);
	Temp += Source;
	return Temp;
}

STRFUNC(bool)::operator ==(const TString &Str)
{
	return STRUTILS<TChar>::Equal(Data, Str.Data);
}

STRFUNC(bool)::operator ==(const TChar* Str)
{
	return STRUTILS<TChar>::Equal(Data, Str);
}

STRFUNC(bool)::operator !=(const TString &Str)
{
	return !STRUTILS<TChar>::Equal(Data, Str.Data);
}

STRFUNC(bool)::operator !=(const TChar* Str)
{
	return !STRUTILS<TChar>::Equal(Data, Str);
}

STRFUNC(TChar)::operator[](const DWORD Index) const
{
	if (Index < Length())
		return Data[Index];
	else
    	return 0;
}



STRFUNC(TChar&)::operator[](const DWORD Index)
{
	// � ���������� ��������  � ������ ���������� �������
	// ����� ������������� ����������, �� ��� �� ����������
	// ����������. ���� ������������� ���������� � ������
	// ���� ������ ������ �� ������� ������

	Unique();
	return Data[Index];
}

