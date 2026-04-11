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
#ifndef MemoryH
#define MemoryH

#include <windows.h>
//-----------------------------------------------------------------------------

void *m_memset(void *szBuffer, DWORD dwSym, DWORD dwLen);
void *m_memcpy(void *szBuf, const void *szStr, int nLen);
int   m_memcmp(const void *buf1, const void *buf2, size_t count);


/*---------------------------------------------------------------------------*/
// ��������� ������� ��� ��������� ������ ���������� VirtualAlloc
// ������� ����� ������ ������� � ���, ��� ������ ���������� �����������,
// ��� �������� � �������� �������� ������ ��� ������������� ���������
// ��������, ���� ��������� ������ ������.
//
// ��� ������������ ���������� ������� ������ ����������� ������� ����������
// ������ �� ���� ��������. ������� ���������� � MemHeap...
/*---------------------------------------------------------------------------*/

// ������ ������ ���������� ������
DWORD  GetMemSize(LPVOID lpAddr);

// ���������� ������
VOID   MemFree(LPVOID lpAddr);

// �������� ������ ���������� �������
LPVOID MemAlloc(DWORD dwSize);

// �������� � �������� ������ ���������� �������
LPVOID MemAllocAndClear(DWORD Size);

// ������������ ������
LPVOID MemRealloc(LPVOID lpAddr, DWORD dwSize );


/*---------------------------------------------------------------------------*/
//  ������� ��� ������ � ������� �� ���� ��������
//  ������ ������� �������� ��������� ��� WINAPI ��������� ��� ������
//  � ������� ����.
//  ������� ���������, ������������� ������ �������� � ������ ��������������
//  ������� ���������� ������
/*---------------------------------------------------------------------------*/

namespace HEAP
{
	LPVOID Alloc(DWORD Size);

	LPVOID ReAlloc(LPVOID Buf, DWORD Size);
	bool ReAlloc2(LPVOID &Buf, DWORD Size);

	void Free(LPVOID Buf);
	void Free2(LPVOID &Buf);

	DWORD Size(LPVOID Buf);
}

/*---------------------------------------------------------------------------*/
//  ����� �������� ����������� �����
/*---------------------------------------------------------------------------*/

// ��������� ���������� ������
#define ClearStruct(S) m_memset(&S, 0, sizeof(S))

// �������� ������ ��� ���������� ���� � ���������� ���������
#define CreateStruct(T) (T*)HEAP::Alloc(sizeof(T))

// �������� ������ ��� ���������� ���� � ���������� ���������
#define FreeStruct(S) HEAP::Free(S);

//-----------------------------------------------------------------------------
#endif

