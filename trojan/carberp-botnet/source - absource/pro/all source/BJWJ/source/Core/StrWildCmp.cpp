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

#ifndef StringsH
	#error ��������� ���� �� �������
#endif

#include <windows.h>
#include "Strings.h"



/*
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

*/

// ��������� ����������� ��������� �����
typedef struct WILD_CMP_REC
{
	PCHAR Mask;            // �����
	PCHAR Buffer;          // ������������ ������
	PCHAR Start;           // ������ ���������� �����
	PCHAR End;             // ��������� ���������� �����
	bool  LastCharIsMask;  // ���������� ������ ��� ������
	int   Result;          // ��������� ���������
} TWCR;



//----------------------------------------------------
bool inline WC_IsMask(const char* Mask)
{
	// ������� ���������� ������ ���� ������� ������ ��������
	// ������������� ��������
	return *Mask == '*';
}
//----------------------------------------------------

void WC_ProcessMask(TWCR &WCR)
{
	// ������� ������������ ������ �����
	WCR.LastCharIsMask = true;

	// ��������� ������� ������ �����
	if (!WCR.Start) WCR.Start = WCR.Buffer;

	// �������� ������� ��������� �����, ��� �����
	// ����������� ��� �����, ������� ����� ���� �����
	// "������������" ��������
	// ��������: "test_test*"
	WCR.End = NULL;

	// ���� ��� ��������� ������ �����, �� �������� ������ ���
	// ������� ����������
	if (*(WCR.Mask + 1) == 0)
		WCR.Result = 1;

	WCR.Mask++;
}
//----------------------------------------------------


bool WC_IsLB(PCHAR S, BYTE &Size)
{
	Size = 0;
	bool r = false;
	bool n = false;

	for (; *S != 0; S++)
	{
		if (*S == '\r')
		{
			if (r) break;
			r = true;
            Size++;
		}
		else
		if (*S == '\n')
		{
			if (n) break;
			n = true;
			Size++;
        }
		else
			break;
	}

	return Size != 0;
}

//--------------------------------------------
//  ������� ���������� ������� ������
//--------------------------------------------
bool WC_CompareChars(PCHAR &S1, PCHAR &S2)
{
	// ��� ��������� �������� ������� �������� ��,
	// ��� ������� �������� ����� ������ ���������
	// �������������� ��� ��� Windows ��� � ���
	// Linux �������
	// �.�. \r\n � \n ������ �������������� ��������� �
	// ������������� �� �� ��������� � ������������������

	bool Result = false;
	BYTE CS1 = 0;
	BYTE CS2 = 0;

	if (WC_IsLB(S1, CS1))
		Result = WC_IsLB(S2, CS2); // ������������ �������� �����
	else
		Result = *S1 == *S2;       // ���������� ������ �������

	if (Result)
	{
		S1 += (CS1) ? CS1 : 1;
		S2 += (CS2) ? CS2 : 1;
    }

	return Result;
}
//----------------------------------------------------


void WC_CompareLine(TWCR &WCR)
{
	// ������� ���������� ������� ������ ����� � �������

	// ������������� ����� ��������� ������.
	// ���� ���������� ������ ��� ������ �� �����������
	// ��������� � ����� ������ ������, � ��������� ������ ����������
	// ������ � ������� �������
	bool SM = true;//WCR.LastCharIsMask;

	WCR.LastCharIsMask = false;

	bool EOL  = false;

	while(*WCR.Buffer)
	{
		// ���������� ������� �����
		PCHAR M = WCR.Mask;
		PCHAR B = WCR.Buffer;

		while (1)
		{
			// ���������� ����� ������������ ������
			EOL = (*M == 0 || WC_IsMask(M));

			// �������� ����� ������ � ���� ����� ������� ������, ���
			// �������� �������� ����� ����� ������ ������� � ������
			// �����
			if (*B == 0 || EOL || !WC_CompareChars(B, M))
				break;
		}

		// �������� ��������� ������� ������ � ��� ������ ���
		// ����� �� ����� ������� ������ � �����
		if (EOL)
		{
			// ��������� ����� ������ � �����
			if(!WCR.Start) WCR.Start = WCR.Buffer;
			WCR.Buffer = B;
			WCR.End    = B;
			WCR.Mask   = M;
			break;
        }

		// ������� ��������� ������ ��� � ������ ��������� � �������
		// �������, ���������� ������
		if (!SM || *B == 0) break;

		// ��������� � ��������� ������� ������
		WCR.Buffer++;
    }

	// ��������� ���������. ��� ������� ������ �������
	// ����� �� ����� �� ����� ������� ������ � �����
	if (!EOL)
		WCR.Result = -1;
}
//----------------------------------------------------



bool WildCmp( const char *Buffer, const char *Mask, LPDWORD StartPos, LPDWORD EndPos, LPDWORD SubStrLen)
{
	// �������� ���������� ���������
	if (StartPos)  *StartPos  = 0;
	if (EndPos)    *EndPos    = 0;
	if (SubStrLen) *SubStrLen = 0;

	if(STRA::IsEmpty(Mask))
		return STRA::IsEmpty(Buffer);

	if(STRA::IsEmpty(Buffer))
		return false;


	// �������������� ���������
	TWCR WCR;
	ClearStruct(WCR);

	WCR.Mask   = (PCHAR)Mask;
    WCR.Buffer = (PCHAR)Buffer;


	// ���������� ��� �����
	while (*WCR.Mask != 0 && WCR.Result == 0)
	{
		// ���������� ������� ������
		if (WC_IsMask(WCR.Mask))
			WC_ProcessMask(WCR);
		else
			WC_CompareLine(WCR);
	}

	// ���� ����� �� ����� �����, ��
	// ��������� ����� ������
	if (*WCR.Mask == 0)
		WCR.Result = 1;

	// ��������� ������� ���������
	if (WCR.Result == 1)
	{
		if (!WCR.End && (EndPos || SubStrLen))
			WCR.End = STRA::End(Buffer);

		if (StartPos)  *StartPos  = WCR.Start - Buffer;
		if (EndPos)    *EndPos    = WCR.End - Buffer;
		if (SubStrLen) *SubStrLen = WCR.End - WCR.Start;
	}

	return WCR.Result == 1;
}
//----------------------------------------------------------------------------


bool WildCmp(const char* Buffer, const char* Mask)
{
	DWORD S;
	DWORD E;
	DWORD L;
	return WildCmp(Buffer, Mask, &S, &E, &L);
}
//-----------------------------------------------------------------------------
