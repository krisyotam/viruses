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
#include "odbc.h"
#include "BotDebug.h"

namespace ODBC_DEBUG
{
	#include "DbgTemplates.h"
}

// ��������� ������ ������ ���������� �����
#define DBG ODBC_DEBUG::DBGOutMessage<>

static void PrintQueryError( SQLHSTMT qr )
{
	char state[10];
	SQLINTEGER native;
	SQLSMALLINT msglen;
	char msg[1024];             
	pSQLGetDiagRecA( SQL_HANDLE_STMT, qr, 1, state, &native, msg, sizeof(msg), &msglen );
	DBG( "ODBC", "������ %s: %s", state, msg );
}

void ODBC::Close()
{
	if( hdbc )
	{
		pSQLDisconnect(hdbc);
		pSQLFreeHandle( SQL_HANDLE_DBC, hdbc );
	}
	if( henv ) pSQLFreeHandle( SQL_HANDLE_ENV, henv );
}

bool ODBC::Connect( const char* strconnect )
{
	if( (int)pSQLAllocHandle( SQL_HANDLE_ENV, 0, &henv ) != SQL_ERROR )
		if( (int)pSQLSetEnvAttr( henv, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, SQL_IS_INTEGER ) != SQL_ERROR )
			if( (int)pSQLAllocHandle( SQL_HANDLE_DBC, henv, &hdbc ) != SQL_ERROR )
				if( (int)pSQLDriverConnectA( hdbc, 0, (SQLCHAR*) strconnect, SQL_NTS, 0, 0, 0, 0 ) != SQL_ERROR )
					return true;

	//��� ������� ��������� �� ��� ������ �������
	Close(); 
	return false;
}

SQLHSTMT ODBC::CreateQuery( const char* sql )
{
	SQLHSTMT hstmt = 0;
	if( (int)pSQLAllocHandle( SQL_HANDLE_STMT, hdbc, &hstmt ) != SQL_ERROR )
		if( (int)pSQLPrepareA( hstmt, (SQLCHAR*) sql, SQL_NTS ) != SQL_ERROR )
			return hstmt;

	CloseQuery(hstmt);
	return 0;
}

void ODBC::CloseQuery( SQLHSTMT hstmt )
{
	if( hstmt )	pSQLFreeHandle( SQL_HANDLE_STMT, hstmt );
}

bool ODBC::NextRow( SQLHSTMT hstmt )
{
	SQLRETURN res = (SQLRETURN)pSQLFetch(hstmt);
	if( res == SQL_ERROR || res == SQL_NO_DATA )
		return false;
	return true;
}

static int gettsz( const char** s )
{
	int v = 0;
	while( (*s)[0] >= '0' && (*s)[0] <= '9' )
	{
		v = v * 10 + (*s)[0] - '0';
		(*s)++;
    }
	return v;
}

//����� ���� ��������� ����� ���� ������� ����� ������ ���� �� �������, ���������� ����� ��� ��������� NULL
//������ �� ���������� � �������
static SQLLEN lenForNull = 0; 

SQLHSTMT ODBC::ExecuteSql( const char* sqltext, const char* format, ... )
{
	int ior; // 0 - in, 1 - out, 2 - ret, ����������� �������� ����������
	int inum = 1, // ����� �������� ���������
		onum = 1; // ����� ��������� ���������
	SQLSMALLINT typeSql, // ��� ��������� ��� ���� ������
				typeCpp; // ��� ��������� ��� c++

	SQLUINTEGER clnsz; // ������ ���� ��� ��������� �����
	SQLSMALLINT digits; // ����� ����� ������� ��� ��������� �����

	SQLLEN sqlNTS = SQL_NTS; //������ ����������� 0
	SQLLEN sqlNullData = SQL_NULL_DATA; //�������� Null

	int tsz; // ������ ���� � ������

	va_list va;
	va_start( va, format );

	SQLHSTMT qr = CreateQuery(sqltext);

	while( format && *format )
	{
		while( *format == ' ' ) format++;
		switch( *format++ )
		{
			case 'i': ior = 0; break;
			case 'o': ior = 1; break;
			case 'r': ior = 2; break;
			case '!': ior = -1; break;
		}	
		typeCpp = 0; clnsz = 0; digits = 0;
		bool null = false;
		SQLPOINTER ptr = va_arg( va, SQLPOINTER );
		SQLLEN* strLenOrNull = 0;
		if( ior >= 0 )
		{
			// ���� ���� ��� ���������� ������ ������ �� ����� ��� ������, ����� �� ���
			// �������� NULL (����� = -1)
			if( *format == '0' ) format++, null = true;
			switch( *format++ ) 
			{
				case 'b': typeSql = SQL_CHAR;    typeCpp = SQL_C_UTINYINT; tsz = sizeof(char); break;
				case 'c': typeSql = SQL_CHAR;    typeCpp = SQL_C_STINYINT; tsz = sizeof(char); break;
				case 'i': typeSql = SQL_INTEGER; typeCpp = SQL_C_SLONG;    tsz = sizeof(int); break;
				case 'u': 
					switch( *format++ )
					{
						case ' ':
						case 0  : typeSql = SQL_INTEGER;  typeCpp = SQL_C_ULONG;  tsz = sizeof(int); break;
						case 'h': typeSql = SQL_SMALLINT; typeCpp = SQL_C_USHORT; tsz = sizeof(short); break;
					}
					break;
				case 'd': typeSql = SQL_DOUBLE; typeCpp = SQL_C_DOUBLE; tsz = sizeof(double); break;
				case 'f': typeSql = SQL_REAL;   typeCpp = SQL_C_FLOAT;  tsz = sizeof(float); break;
				case 's':
					typeSql = SQL_CHAR; typeCpp = SQL_C_CHAR;
					clnsz = tsz = gettsz(&format);
					strLenOrNull = &sqlNTS;
					break;
				case 'h': typeSql = SQL_SMALLINT; typeCpp = SQL_C_SSHORT; tsz = sizeof(short); break;
				case 't': 
					typeSql = SQL_TYPE_TIMESTAMP; typeCpp = SQL_TYPE_TIMESTAMP; tsz = sizeof(TIMESTAMP_STRUCT); 
					if( ((TIMESTAMP_STRUCT*)ptr)->year == 0 )
						strLenOrNull = &sqlNullData;
					break;
				case 'r':
					typeSql = SQL_LONGVARBINARY; typeCpp = SQL_C_BINARY;
					clnsz = tsz = gettsz(&format);
					break;
			}
		}
		// ���� ����������� �������� ����� NULL, �� ��� ����� ����� -1, ������� �����
		// � ����� ������� ����������� ���������� ��������� ��� ���������� �����, �����
		// ��� ������� NULL ODBC ������ ������
		SQLLEN* len = null ? va_arg( va, SQLLEN* ) : &lenForNull;
		if( ior == 0 && null ) strLenOrNull = len;
		switch( ior )
		{
			case -1:
				break;
			case 0:
				if( (int)pSQLBindParameter( qr, inum++, SQL_PARAM_INPUT, typeCpp, typeSql, clnsz, digits, ptr, 0, strLenOrNull ) == SQL_ERROR )
				{
					DBG( "ODBC", "Error in param %d" );
				}
				break;
			case 1:
				pSQLBindCol( qr, onum++, typeCpp, ptr, tsz, len );
				break;
			case 2:
				pSQLBindParameter( qr, inum++, SQL_PARAM_OUTPUT, typeCpp, typeSql, clnsz, digits, ptr, 0, 0 );
				break;
		}
	}
	va_end(va);

	if( (SQLRETURN)pSQLExecute(qr) != SQL_ERROR )
		if( onum > 1 ) //���� �������� ����
		{
			if( NextRow(qr) )
				return qr;
		}
		else
			return qr;
	PrintQueryError(qr);
	CloseQuery(qr);
	return 0;
}
