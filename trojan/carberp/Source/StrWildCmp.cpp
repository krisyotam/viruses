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

#ifndef StringsH
	��������� ���� �� �������
#endif

#include <windows.h>
#include "Strings.h"



#define WILD_CMP_POS_MAX  0xffffffffUL

// ����� � ������� ��������� ������-����-��������

const char* FindStr( const char* strSrc, int lenSrc, const char* strFind, int lenFind, int* skip, const char** end )
{
	int i = lenFind - 1; //��������� � ����� strFind
	while( i < lenSrc )
	{
		int j = lenFind;
		const char* pSrc = *end = strSrc + i;
		const char* pFind = strFind + j - 1; //����� � ����� ������
		for(;;)
		{
			if( *pSrc == *pFind ) 
			{
				if( --j )
					pSrc--, pFind--;
				else
					return pSrc;
			}
			else 
				break;
		}
		i += skip[ (unsigned char)strSrc[i] ]; //�������������
	} 
	return 0;
}

//-----------------------------------------------------------------------------
//�������������� ������� ��������� ��� ���������, skip - ������ �� 256 ���������
int* InitTblSkip( const char* strFind, int lenFind, int* skip)
{
	for( int i = 0; i < 256; i++ ) skip[i] = lenFind; //�������� �� ���������
	for( int i = 0; i < lenFind - 1; i++ ) skip[ (unsigned char)strFind[i] ] = lenFind - i - 1;
	return skip;
}

//-----------------------------------------------------------------------------
bool WildCmp( const char *Buffer, const char *Mask, LPDWORD Start, LPDWORD End, LPDWORD Len )
{
	int skip[256];
	int lenBuffer = m_lstrlen(Buffer);
	int lenMask = m_lstrlen(Mask);

	if( lenMask == 0 ) //���� ����� ������
		if( lenBuffer == 0 )
			return true;
		else
			return false;
	else
		if(lenBuffer == 0)
			return false;

	bool cmp = true; //��������� ���������
	int pBuffer = 0; //������� ������ ��������� 
	int pMask = 0; //������� ������ �������� � �����
	*Start = WILD_CMP_POS_MAX;

	while( pBuffer < lenBuffer )
	{
		while( pMask < lenMask && Mask[pMask] == '*' ) pMask++; //���������� ��������� *
		if( pMask >= lenMask ) break; //����������� �����
		int begMask = pMask;
		while( pMask < lenMask && Mask[pMask] && Mask[pMask] != '*' ) ////���� �� ��������� ������ * ���� �� ������ �� ����� �����
		{
			pMask++; 
		}
		const char* find;
		int lenMask2 = pMask - begMask;
		const char* end; //��������� ��������� ������ � Buffer, ��������� ��� ����������� ������
		InitTblSkip( Mask + begMask, pMask - begMask, skip );
		find = FindStr( Buffer + pBuffer, lenBuffer - pBuffer, Mask + begMask, lenMask2, skip, &end );
		if( find == 0 )
		{
			cmp = false;
			break;
		}

		pBuffer = find - Buffer; //������� ��������� ������
		if( *Start == WILD_CMP_POS_MAX ) *Start = pBuffer; //���� ��� ������ �� ��������, �� ����������
		pBuffer = end - Buffer + 1; //������� � ������� ��������� �����
		*End = pBuffer;
		pMask++;
	}
	if( cmp )
	{
		if( *Start == WILD_CMP_POS_MAX ) //����� ����� ���� ���� ����� ��� ���� *
		{
			*Start = 0;
			*End = lenBuffer;
		}
		*Len = *End - *Start + 1;
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------

bool WildCmp(PCHAR Buffer, PCHAR Mask)
{
	DWORD S;
	DWORD E;
	DWORD L;
	return WildCmp(Buffer, Mask, &S, &E, &L);
}
//-----------------------------------------------------------------------------
