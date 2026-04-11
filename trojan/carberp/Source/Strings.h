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

#ifndef StringsH
#define StringsH
//-----------------------------------------------------------------------------

#include "Memory.h"
#include "GetApi.h"

//int WINAPI URLEncode( char *pszDestiny, char *pszSource );

//void DbgMsg(char *file, int line, char *msg, ...);
//void DbgMsgW(WCHAR *file, int line, WCHAR *msg, ...);

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
DWORD  WINAPI m_lstrlen(const char *szPointer );

DWORD WINAPI m_wcslen(const wchar_t *String );

wchar_t *m_wcsncpy( wchar_t *dest, wchar_t *src, unsigned long n );
wchar_t *m_wcslwr( wchar_t *Str );
bool m_wcsncmp( WCHAR *s1, WCHAR *s2, size_t iMaxLen );
const wchar_t * WINAPI m_wcsstr( const wchar_t * _Str, const wchar_t * _SubStr );

bool WildCmp(const char *Buffer, const char *Mask, LPDWORD Start, LPDWORD End, LPDWORD Len );
bool WildCmp(PCHAR Buffer, PCHAR Mask);

bool CompareUrl(const char *MaskUrl, const char *Url );

WCHAR * AnsiToUnicode( char *AnsiString, DWORD dwStrLen );
wchar_t* UTF8ToUnicode( const char* utf8String );
char*    UTF8ToAnsi( const char* utf8String );



//void AlertError( LPTSTR lpszFunction ) ;

//������� � ������ � ����� ������� c, ���������� ��������� �� s, ������ ������ ��� ������������ ������
char* trimall( char* s, char c = ' ' );


// ----------------------------------------------------------------------------
//  ����� ������� ��� ������ �� ��������
//
//  ���� ������������ ������ ������� ��� ������ �� ��������, ��? � ���������
//  �������, ����� ������� �������� ��������������. ��������, �������
//  StrLength �����������  ��������� �� �������������� ������� �������
//  ������������ ����� ������ �������� � �� �������� �������, � ��� ������
//  ������ ��� ������ ������� � ��������������
// ----------------------------------------------------------------------------


// ������� ����������� ����� ������ �������� �� � ������� ������������ ����
DWORD StrCalcLength(const char* Buf);
DWORD StrCalcLengthW(const wchar_t* Buf);


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
int StrCompare(const char* Str1, const char* Str2);

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
	int Pos(const char* Str, const char* SubStr, DWORD StrLen = 0, bool CaseSensetive = true);

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
	PCHAR Scan(const char* Str, char C);

	// ������� ���������� ��������� �� ��������� ������ �
	PCHAR ScanEnd(PCHAR Str, char C);

	// ������� ���������� ����� �����, ������ ��������������
	// ������������ ������ SubStr
	PCHAR GetLeftStr(PCHAR Str, PCHAR SubStr, bool IncludeSubStr = false);
	PCHAR GetRightStr(PCHAR Str, PCHAR SubStr, bool IncludeSubStr = false);


	// ������� ���������� �������. ������� �� �������� ������, ���
	// ���������� ��������� �� ������ ������, ���� �� ����� ������
	PCHAR IgnoreSpaces( const PCHAR Str );

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
	//�������������� ������ � ��������������� �����
	DWORD ToDWORD( const char* s );


	// ������� ���������� ������ ���� �� ����� ������� ��������� ����
	// ������ ������
	bool IsEmpty( const PCHAR Str);

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

    // ������� ���������� ������ ��� ������ � ������ �������
    bool IsLinuxStr(PCHAR S);

	// ������� �������� ������ � ������� Linux
	PCHAR ConvertToLinuxFormat(PCHAR S);
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
	PCHAR ToAnsi(LPCWSTR Str, DWORD Len);

	// ���������� ��������� �� ����� ������
	PWCHAR End(PWCHAR Str);

	// ������� ���������� ��������� �� ��������� ������ �
	PWCHAR ScanEnd(PWCHAR Str, WCHAR C);

	// ������� ����������� ��� ������
	// Str - �������� ������
	// Len - ����� ������, ���� ����� 0, �� ������������� �� ��������� ����
	// LowerCase - ��������� ������� � ������ ������� ����� ��������� ����
	DWORD GetHash(const PWCHAR Str, DWORD Len, bool LowerCase);
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


#define CharIsDigit(C)  ((C >= '0') && (C <= '9'))
#define LowerChar(C) if (C >= 'A' && C <= 'Z') {C = C + ('a'-'A');}


//*********************************************************************
//  ��������� ���� � ������� ������� ��� ������ �� ���������� ���������
//  ��� ���� ���-�� �� ������ ��������� ��������� ������� ���
//  ����������
//
//  �����:
//  ������ � ������ ���� ������ ������ ��������� � ������ ���
//  ����������� �� ��, ��� ������ ������ ������������� �����������
//  �����������
//*********************************************************************
template <class TChar>
class STRUTILS : TBotObject
{
public:
	// ������� ���������� ������ ���� ������ ������
	static bool  IsEmpty(const TChar* Str);

	// ������� ����������� ����� ������
	static DWORD  Length(const TChar* Str);

	// ������� ���� ��������� ��������� � ������
	static int Pos(const TChar* Str, const TChar *SubStr);

	// ������� ���������� ������ ���� ������ ���������
	static bool Equal(const TChar* Str1, const TChar* Str2);

	// ������� ���������� ��� ������
	static int Compare(const TChar* Str1, const TChar* Str2);

	// ������� ��������� ������ Str � ������� Position ��
	// Count ��������
	static void Expand(const TChar *Str, DWORD Position, int Count);

	//  ������� ��������� ��������� � ������
	static void Insert(const TChar *Str, const TChar *SubStr, DWORD Position);

	// ������� �������� ��� ������ SubStr � ������ Str �� ������ NewStr
	static void Replace(const TChar *Str, const TChar *SubStr, const TChar *NewStr);

	// ������� ����������� ��� ������
	static DWORD Hash(const TChar* Str, DWORD Len, bool LowerCase);
	static DWORD Hash(const TChar* Str);

	// ������� ���� ������ ��������� ������� � ������
	static TChar* Scan(const TChar *Str, TChar Char);

	// ������� ���������� ��������� �� ����� ������
	static TChar* End(const TChar *Str);

	// ������� ����������� ����� ����� � ������.
	// ������� �� ������ ������.
	// � ��������� n ���������� ���������� ��������
	// ���� ������� ������� � ������� ������� �� �������
	// ��������� ����������� ������ ������
	static void LongToString(DWORD num, TChar* Str, int &n);
};


typedef STRUTILS<char> STRA, AnsiStr;
typedef STRUTILS<wchar_t> STRW, UnicodeStr;



//*********************************************************************
//  ������ ��� ������ �� ������������������ ������� �����
//  ��� �������� ������ ���������� ��������������, ���������
//  ��������� TStrRec. ��������� ��������� �� ��������������
//  �������� Str - sizeof(TStrRec)
//*********************************************************************

// ���������� ����� ����� �������� ������� ������������ ������ �����
// ������ ����� ���������� ������ STRING_BLOCK_SIZE

#define USE_BLOCKS_STRINGS

// ������ ������ ������
#define STRING_BLOCK_SIZE 32


// ���������� ��������� �������
#define STRBUFAPI(Result_Type) template<class TChar> Result_Type

namespace STRBUF
{
	// ��������� ������
	struct TStrRec
	{
		DWORD Size;      // ������ ������ (��������)
		DWORD Length;    // �������� ������ ������
		DWORD RefCount;  // ���������� ������
    };


	// ������� ������ ������ �������� Size ��������
	// ����� ������ ��������������� �������
	STRBUFAPI(TChar*) Alloc(DWORD Size);

	// ������� ��������� ������� ������ �, ��� �������������, ���������� ������
	STRBUFAPI(void) Release(TChar* &Str);

	// ������� ����������� ������� ������ ������ � ���������� ��������� �� ��
	STRBUFAPI(TChar*) AddRef(TChar* Str);

	// ������� ������������� ������
	STRBUFAPI(void) Unique(TChar* &Str);

	// ������� ���������� ���������� ��������� ������
	STRBUFAPI(TStrRec&) GetRec(TChar* Str);

	// ������� ���������� ����� ������
	STRBUFAPI(DWORD) Length(TChar *Str);

	// ������� ������ ������ ������� ResultStrSize � �������� �� �� StrLen ��������
	// ������ � �����, ��� �������������, ����� ��������� ��� ����������� �������
	STRBUFAPI(TChar*) CreateFromStr(const TChar* Str, DWORD StrLen, DWORD ResultStrSize);

	// ������� ��������� � ������ Dst ������ Src
	STRBUFAPI(void) Append(TChar* &Dst, const TChar* Src, DWORD SrcLen);

	// ������� �������� ���������� �������� Count � ������� Pos
	STRBUFAPI(void) Copy(TChar* &Dst, const TChar* Src, DWORD Pos, DWORD Count);

	// ������� ��������� ������ Str � �����
	STRBUFAPI(void) Insert(TChar* &Buf, const TChar* Str, DWORD Position, DWORD StrLen);

	// ������� �������� ��������� � ������
	STRBUFAPI(void) Replace(TChar* &Str, const TChar* SubStr, DWORD SBLen, const TChar* NewStr, DWORD NSLen);
}


//*********************************************************************
//  ��������� ���� ������
//*********************************************************************
template <class TChar>
class TString : public TBotObject
{
public:
	TString() : Data(0) {};
	TString(unsigned long StrBufSize);
	TString(const TString& src);
	TString(const TChar* src);
	TString(const TChar* src, DWORD copylen);

	~TString();

	DWORD Length() const;
	DWORD CalcLength();
	void  SetLength(DWORD NewLength);
	bool  IsEmpty() const;
	void  Clear();

	void Copy(const TChar* Source, DWORD Position, DWORD Count);
	void Copy(const TString &Source, DWORD Position, DWORD Count);
	void Insert(const TChar* Str, DWORD Position);
	void Insert(const TString &Str, DWORD Position);
	void Replace(const TChar *Str, const TChar *NewStr);
	void Replace(const TString &Str, const TString &NewStr);

	int Pos(const TChar* SubStr) const;
	int Pos(const TString &SubStr) const;

	TString& Format(const TChar *FormatLine, ...); // return this

    TString& LongToStr(DWORD num); // return this

	DWORD Hash();
	DWORD Hash(DWORD Len, bool LowerChar);

	void Unique();

	void ConvertToLinuxFormat();

	TChar* t_str() const;

	TString& operator =(const TString &Source);
	TString& operator =(const TChar* Source);
	TString& operator +=(const TString &Source);
	TString& operator +=(const TChar* Source);
	TString operator +(const TString &Source);
	TString operator +(const TChar* Source);
	bool operator ==(const TString &Str);
	bool operator ==(const TChar* Str);
	bool operator !=(const TString &Str);
	bool operator !=(const TChar* Str);
	TChar operator [](const DWORD Index) const;
	TChar& operator [](const DWORD Index);
private:
    TChar* Data;
};




typedef TString<char> string;
typedef TString<wchar_t> wstring;


#include "StrImplementation.cpp"



// ��� �������
string LongToStr(DWORD num);


//****************************************************
//  ������ �������� ��� ���������� ���������������
//  ����������:
//
//  if (true)
//		return NULL;
//
//  ��������������� ���������� �������� ����������
//  ����
//
//  if (true)
//		return (DWORD)NULL;
//  ����
//  if (true)
//		return string();
//
//  ��� ���������� ������ ���������� ������
//  ������� ��� �� ����� ������ �������, �� �
//  ������ ������ ������� �� ��������
//****************************************************
#define NULLSTR (char*)NULL
#define NULLWSTR (wchar_t*)NULL




//****************************************************
//  ����� �������� ������� ����� ���������  ���� ��
//  ������, ���������� ������� �������� � ����������-
//  ����� ������ �������
//  ������_1 \0 ������_2 \0 ������_3 \0\0
//****************************************************
class TStrEnum : public TBotObject
{
private:
	PCHAR  FBuf;
	bool   FEncrypted;
	PCHAR  FCurrent;
	string FLine;
	void Initialize(const char *Buffer, bool Encrypted, DWORD EmptyBufHash);
public:
	//---------------------------------------------------
	//  ��������� ������������:
	//  Buffer - ��������� �� �������� �����
	//  Encrypted - �������� ����, ��� ������ �����������
	//  EmptyBufHash - ��� "������" ������. ���� �������
	//				   �� ������� �������� � ��� ������
	//		           ����� ��������� � ���������, ��
	//                 ����� ����� �������, ��� ������
	//				   ������
	//---------------------------------------------------
	TStrEnum(const char *Buffer, bool Encrypted, DWORD EmptyBufHash);
	TStrEnum(const char *Buffer);
	bool Next();
	inline string& Line() { return FLine; }
	bool IsEmpty();
};


//----------------------------------------------------------------------------
#endif
