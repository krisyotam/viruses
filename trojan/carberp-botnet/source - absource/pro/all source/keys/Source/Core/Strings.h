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

#ifndef StringsH
#define StringsH
//-----------------------------------------------------------------------------

//int WINAPI URLEncode( char *pszDestiny, char *pszSource );

void DbgMsg(char *file, int line, char *msg, ...);
void DbgMsgW(WCHAR *file, int line, WCHAR *msg, ...);

int m_atoi( const char *nptr );

void   WINAPI m_lstrcat( char *szBuf, const char *szStr );
void   WINAPI m_lstrcpy( char *szBuf, const char *szStr );
void   WINAPI m_lstrlwr( char *str );

void WINAPI m_lwcscat( WCHAR *szBuf, const WCHAR *szStr );

char * WINAPI m_strstr( const char * _Str, const char * _SubStr );
char * WINAPI m_strstrmask( const char * _Str, const char * _SubStr );
char * WINAPI m_strtok_s( char *String, const char *Control, char **Context );

//char * WINAPI ToAnsi( LPCWSTR String );
//char * WINAPI ToAnsiEx( LPCWSTR String, DWORD dwSize );

bool   WINAPI m_lstrncpy( char *pString_src, const char *pString_dst, DWORD len );
bool   WINAPI SearchByMask( char *mask, char *name );

int  WINAPI m_istrstr( const char * _Str, const char * _SubStr );
DWORD  WINAPI m_lstrcmp( const char *szStr1, const char *szStr2 );
DWORD  WINAPI m_lstrncmp( const char *szstr1, const char *szstr2, int nlen );
DWORD  WINAPI m_lstrlen( char *szPointer );

DWORD WINAPI m_wcslen( const wchar_t *String );

wchar_t *m_wcsncpy( wchar_t *dest, wchar_t *src, unsigned long n );
wchar_t *m_wcslwr( wchar_t *Str );
bool m_wcsncmp( WCHAR *s1, WCHAR *s2, size_t iMaxLen );


bool WildCmp(char *Buffer, char *Mask, LPDWORD dwStart, LPDWORD dwEnd, LPDWORD dwLen );
bool WildCmp(PCHAR Buffer, PCHAR Mask);

bool CompareUrl( char *MaskUrl, char *Url );

WCHAR * AnsiToUnicode( char *AnsiString, DWORD dwStrLen );
void AlertError( LPTSTR lpszFunction ) ;



// ----------------------------------------------------------------------------
//  ����� ������� ��� ������ �� ��������
//
//  ���� ������������ ������ ������� ��� ������ �� ��������, ��? � ���������
//  �������, ����� ������� �������� ��������������. ��������, �������
//  StrLength �����������  ��������� �� �������������� ������� �������
//  ������������ ����� ������ �������� � �� �������� �������, � ��� ������
//  ������ ��� ������ ������� � ��������������
// ----------------------------------------------------------------------------

// �������� ������ ������ ������
// �����!!! ������� �������� �� �������� ������� ������� �������� StrNew
void StrSetLength(PCHAR &Str, DWORD NewLength);


// ������� ����������� ����� ������ �������� �� � ������� ������������ ����
DWORD StrCalcLength(PCHAR Source);


//  ������� StrConcat ���������� ��� � ����� ������.
//  ���� ������ ������ ������ Str1 ������ ������������,
//  �� ������ Str1 ����� ��������������
//  Count ���������� ������� ����� ����� ��������� � Str1
void StrConcat(PCHAR &Str1, PCHAR Str2);
void StrConcat(PCHAR &Str1, DWORD Count, PCHAR Str2...);

// ������� �������� ������ Source � ������ Dest
// ���� UpdateLen ������������ ������ ���� Dest ������� ���������
// StrAlloc, StrNew
// ���������� ������ ���� ���������� ����-�� ���� ����
bool StrCopy(PCHAR Dest, PCHAR Source, bool UpdateLen = false);

// �������� ��� ������
int StrCompare(PCHAR Str1, PCHAR Str2);

// ������� �� �������������� ����� � ����� � ��������
int StrToInt(PCHAR Str);
PCHAR StrLongToString(DWORD num);

// ������� �������� ������ � ������� ��������
void StrLowerCase(PCHAR Str);

// ������� ���� ������� ������ � ������� ����� �mo
int StrIndexOf(PCHAR Str, bool CaseSensetive, DWORD Count, PCHAR Cmp...);

// ������� ���������� ������ Str �� ������� ToSame.
// CaseSensetive ���������� ���������������� � ��������
// ���� StrEndPosrition �� ����� ����, �� ���������
// �������������� StrEndPosrition ���������
bool StrSame(PCHAR Str, PCHAR ToSame, bool CaseSensetive = true, DWORD StrEndPosition = 0);

// ������� ���������� ����� ������������  ����� ������� Before � After
// ����� ��������� ��������� Buffer  ����� ��������� �� ����� ������ After
// ��������� ���������� �������� StrFree
PCHAR GetTextBetween(PCHAR &Buffer, PCHAR Before, PCHAR After );

//----------------------------------------------------------------------------
//  STR - ������ ��� ������ �� ��������
//----------------------------------------------------------------------------
namespace STR
{
	// ������ � ������ ������ ������ ������� ��� �� ����� �������� StrLen + 1
	PCHAR Alloc(DWORD StrLen);

	// ������� ������ ������, ����� Source.
	// Len - ���������� ���������� ��������
	//       ���� ����� 0, �� ����� ����������� ��� ������
	PCHAR New(PCHAR Source, DWORD Len = 0);

	// ������� ������ ������ ��������� ��������� �����
	PCHAR New(DWORD Count, PCHAR Str...);

	// ���������� ������.
	// �����!!! ������ ������ ���� ������� � ������� ������� StrNew
	void Free(PCHAR Str);
	void Free2(PCHAR &Str);

	// ������� ���������� ����� ������.
	DWORD Length(PCHAR Str);

	// ��������� �������� ����� ������ � � ����������.
	// !!!!������ ��� ����� ��������� ����� STR::Alloc (STR::New)
	// ���� �������� RealLength �� ������� �� ����� �����
	// ������������� �� �������� �������
	void UpdateLength(PCHAR Str, DWORD RealLength = 0);

	// ������� ������� ������ SubStr  � ������ Str
	// ���� �������� StrLen �� ����� ����� ������� ��
	// �������� �������
	int Pos(PCHAR Str, PCHAR SubStr, DWORD StrLen = 0);

	// �������� � ������� Position ������ Source Count �������� �
	// ������ Destination
    void Copy(PCHAR Source, PCHAR Destination, DWORD Position, DWORD Count);

	// ������� Count �������� � ������� Position ������ Str
	void Delete(PCHAR Str, DWORD Position, DWORD Count, DWORD StrLength = 0);

	//  Replace - ������� �������� � ������ Str ������ SrcStr ��
	//  ������ DstStr.
	//  � ������ ������ ������� ���������� ����� ������
	PCHAR Replace(PCHAR Str, PCHAR SrcStr, PCHAR DstStr, DWORD StrLen = 0);

	// ������� ���������� ��������� �� ������ �
	PCHAR Scan(PCHAR Str, char C);

	// ������� ���������� ��������� �� ��������� ������ �
	PCHAR ScanEnd(PCHAR Str, char C);

	// ������� ���������� ����� �����, ������ ��������������
	// ������������ ������ SubStr
	PCHAR GetLeftStr(PCHAR Str, PCHAR SubStr, bool IncludeSubStr = false);
	PCHAR GetRightStr(PCHAR Str, PCHAR SubStr, bool IncludeSubStr = false);


	// ������� ���������� �������. ������� �� �������� ������, ���
	// ���������� ��������� �� ������ ������, ���� �� ����� ������
	PCHAR IgnoreSpaces(PCHAR Str);

	// ���������� ��������� �� ����� ������
	PCHAR End(PCHAR Str);

	// ������� ����������� ������ �� ������ �������
//	PCHAR Format(PCHAR Str, ...);
	PCHAR Format(PCHAR Str, va_list Arguments);

	// ������� ���������� ������� ����� � ������.
	// ����� �������������� ��������� 10, 13 ���� ������ ������
	// ����� ������ �������������� ������� �������� ���� �������� �������
	PCHAR GetLine(PCHAR Str, DWORD StrSize = 0);

	// ������� ���������� ��������� �� ������ ������ ��������� ����� � ������
	// ���� �� ����� ������
	PCHAR GotoNextLine(PCHAR Str, DWORD StrSize = 0);

    // ������� ��������������� ����������������� ����� � ������������
	DWORD HexToDWORD(PCHAR Str);


	// ������� ���������� ������ ���� �� ����� ������� ��������� ����
	// ������ ������
	bool IsEmpty(PCHAR Str);

	// ������� ����������� ��� ������
	// Str - �������� ������
	// Len - ����� ������, ���� ����� 0, �� ������������� �� ��������� ����
	// LowerCase - ��������� ������� � ������ ������� ����� ��������� ����
	DWORD GetHash(PCHAR Str, DWORD Len, bool LowerCase);

	// ������� ����������� ����� ������ ��������� �� ���������� �����
	// ��������� ���� �� ����� ������� �������� � ����� ������� �����
	// ������� ������� ������
	// ��������: str0str0str00
	DWORD CalcDoubleZeroStrLength(PCHAR Str);

	// ������� �������� ������� � ������ �������. ������� �� �������������
	// � ��������� ��������
	void AnsiLowerCase(PCHAR Str);
}

namespace WSTR
{
	// �������� ������ �� ������ ������ StrLen
	PWCHAR Alloc(DWORD StrLen);

	// ������� ������ ������, ����� Source.
	// Len - ���������� ���������� ��������
	//       ���� ����� 0, �� ����� ����������� ��� ������
    PWCHAR New(PWCHAR Source, DWORD Len = 0);

	// ���������� ������ ���������� ��� ������
	void Free(PWCHAR Str);

	// ������� ����������� ����� ������
	DWORD CalcLength(PWCHAR Str);

	// ������� ���������� ������ ���� ������ ������
	bool IsEmpty(PWCHAR Str);

	// ��������� ����� ������
	DWORD CalcLength(PWCHAR Str);

	// ������� ��������������� WideString � ANSI String
	PCHAR ToAnsi(PWCHAR Str, DWORD Len);

	// ���������� ��������� �� ����� ������
	PWCHAR End(PWCHAR Str);

	// ������� ���������� ��������� �� ��������� ������ �
	PWCHAR ScanEnd(PWCHAR Str, WCHAR C);

	// ������� ����������� ��� ������
	// Str - �������� ������
	// Len - ����� ������, ���� ����� 0, �� ������������� �� ��������� ����
	// LowerCase - ��������� ������� � ������ ������� ����� ��������� ����
	DWORD GetHash(PWCHAR Str, DWORD Len, bool LowerCase);
}


#define CalcHash(Str) (STR::GetHash(Str, 0, false))
#define CalcHashA(Str) (STR::GetHash(Str, 0, false))
#define CalcHashW(Str) (WSTR::GetHash(Str, 0, false))


// ----------------------------------------------------------------------------
//  Strings - ����� ������� ��� ������ �� �������� �����
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

#endif
