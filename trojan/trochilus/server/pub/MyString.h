/*
  name      Trochilus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#pragma once

//ģ��䴫���ַ����õĽṹ
template <class CharType>
struct _MyString
{
public:
	_MyString()
		: m_pStr(NULL)
		, m_dwLength(0)
	{
	}

	_MyString(const _MyString& another)
		: m_pStr(NULL)
		, m_dwLength(0)
	{
		*this = another;
	}

	_MyString(const CharType* str)
		: m_pStr(NULL)
		, m_dwLength(0)
	{
		*this = str;
	}

	~_MyString()
	{
		Clean();
	}

	_MyString& operator= (const CharType* str)
	{
		Clean();
		size_t tempSize = (sizeof(CharType) == 2) ? wcslen((LPCWSTR)str) : strlen((LPCSTR)str);
		m_dwLength = (DWORD) tempSize;
		m_pStr = (CharType*) malloc((m_dwLength + 1) * sizeof(CharType));
		memcpy(m_pStr, str, m_dwLength * sizeof(CharType));

		return *this;
	}

	_MyString& operator=(const _MyString<CharType>& another)
	{
		Clean();
		m_dwLength = another.m_dwLength;
		m_pStr = (LPTSTR) MY_ALLOC((m_dwLength + 1) * sizeof(CharType));
		memcpy(m_pStr, another.m_pStr, m_dwLength * sizeof(CharType));
		return *this;
	}

	bool operator==(const CharType* pStr) const
	{
		DWORD dwStrLen = (DWORD) (sizeof(CharType) == 2) ? wcslen((LPCWSTR)pStr) : strlen((LPCSTR)pStr);
		if (dwStrLen != m_dwLength) return false;
		if (m_dwLength == 0) return true;
		return (0 == memcmp(m_pStr, pStr, m_dwLength * sizeof(CharType)));
	}

	operator const CharType*()
	{
		return m_pStr;
	}

	void Clean()
	{
		if (NULL != m_pStr)
		{
			free(m_pStr);
		}
		m_pStr = NULL;
		m_dwLength = 0;
	}

	DWORD Size()
	{
		return m_dwLength;
	}

private:
	CharType*	m_pStr;
	DWORD		m_dwLength;
};

typedef _MyString<WCHAR> MyStringW, *PMyStringW;
typedef _MyString<CHAR> MyStringA, *PMyStringA;
#define MyString MyStringW
#define PMyString PMyStringW
