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
//---------------------------------------------------------------------------

#ifndef MD5_2H
#define MD5_2H
//---------------------------------------------------------------------------

#include <Windows.h>
#include "Strings.h"


#define MD5_HASH_SIZE 16

typedef struct
{
  ULONG i[2];
  ULONG buf[4];
  BYTE  in[64];
  BYTE  digest[16];
} TMD5Context, *PMD5Context;

typedef struct
{
	BYTE Data[MD5_HASH_SIZE];

} TMD5, *PMD5;


void MD5Init2(PMD5Context Context);
void MD5Update2(PMD5Context Context, LPVOID Buf, DWORD BufSize);
void MD5Final2(PMD5Context Context);

//-------------------------------------------------
// MD5FromBuf - ������� ����������� MD5 ��� ������
//-------------------------------------------------
void MD5FromBuf(LPVOID Buf, DWORD BufSize, TMD5 &Hash);

//-------------------------------------------------
// MD5FromFile - ������� ����������� md5 ��� �����
//-------------------------------------------------
bool MD5FromFileA(const char* FileName, TMD5 &Hash);
bool MD5FromFileW(const wchar_t* FileName, TMD5 &Hash);

//-------------------------------------------------
//  �������������� ������� ������������ MD5 ��� �
//  ���� cnhjrb
//-------------------------------------------------
string MD5StrFromBuf(LPVOID Buf, DWORD BufSize);
string MD5StrFromFileA(const char* FileName);
string MD5StrFromFileW(const wchar_t* FileName);


//-------------------------------------------------
// MD5ToStr - ������� ������������ MD5 ��� � ������
//-------------------------------------------------
string MD5ToStr(TMD5 &Hash);
string MD5ToStr(TMD5Context &Content);


//-------------------------------------------------
// ������� ��������� �������� �����
//-------------------------------------------------
bool MD5Compare(LPBYTE Hash1, LPBYTE Hash52);




#endif
