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
#ifndef UUID_6140C07EBBDC4FC18600498BA2A18935
#define UUID_6140C07EBBDC4FC18600498BA2A18935


/*
	������ ����� �� �����:
	������������������ ��������. 
	NameTypeLengthValue(Ntlv)
	
	NtlvRecord
	{
		BYTE[4]  Signature;
		BYTE     Type;
		BYTE     NameLength;
		DWORD    ValueLength;
		BYTE[]   Name;
		BYTE[]   Value;
	}
	
	�������� ������, ������� ������ ���� ������ �����������:
	��� ����� ���� ���� ������� �����, ���� �������.
	
	������ - ��� ������ �������,Value �������� �������� 4 ������� ����������� �����,
	����������� ���-�� ��������� ������. ��� ���� ������ ����� ��������� ��������� 
	������, � �������� ����� ��� ���-�� ���������.

	������ � ������ ������ ����� �������� ������� �� ��������� ��������:
	- �� � �������� - ��� �������������� ������� ��������, �������� 
	  �������� � ������� � ������.
	- ������������� �������� ���� � �������� ��������� ������� �����������
	  ������������ ������
	- ������� ������ ����������� ����� - �� ����� ����� �������� ������� ����������.
	- ������� ������ ������������ � �� ��������. �������� ������ ���������� 
	  ���������� ������.
	- ��������� ����������� �������� �� �������� ������.
	  �� ���� ����� ������ �������� - ������ �������� ��������� ������ ��������
	
	����� ��������� ����������� ������ ����������� � LISP � ��������� ICQ.
*/

namespace DUMP {

// ��� ������������� �� �-��� ������ ������� ���� ��� ���������� ������ 
// ������� ��� �����, � ����� ����� ��� ������, ��� ������� � ���� � ��.
// � ����� ������ ���� ������ �������� ���������� �� ������� ��������  
// ��������� �����.

// ������ ������� ����� ��� ���������� ���������� �������.
// ��� ��������� ���� ������������� ��� ���������� ���������� �������.
// ������: � ����� ����� ���� ��������� File_InitDumpWriteStream
// ��� ��������� ��� ������ � ����. �� ����������� �-��� � ��������� � 
// ��������� stream_ctx �� ���������� ��� ������������ �������� ���������,
// � ������� ������ ����� �����.
struct WriteStream
{
	bool (*Write)(WriteStream* Stream, const void* Data, DWORD DataLength,
		DWORD* Written);

	void (*Finish)(WriteStream* Session);

	void* stream_ctx;
};

struct ReadStream
{
	bool (*Read)(ReadStream* Stream, void* Buffer, DWORD BufferLength,
		DWORD* ReadBytes);

	void* stream_ctx;
};

// ������� �������������� ���� ������, ������� ����� �������� � ����.
// ������ �� ������� ��������, ������ ����� �-��� ���������������� ������ ��� 
// ���������������� ����.
// ��� ������������� ������ ���� :
//   ����������� ����� ��� � ���� �������
//   ����������� ��������������� �-��� Write<Type>

enum DumpValueType
{
	// ����������� 4-������� �����.
	DumpValueType_Uint32    = 0x01,
	
	// ������ WCHAR ��� ��������� �������� �������
	DumpValueType_StringW   = 0x02,
	
	// ������ ����. ��� �������� �������� ����� ������.
	DumpValueType_ByteArray = 0x03,

	// ������ CHAR ��� ��������� �������� �������
	DumpValueType_StringA   = 0x04,
	
	// ������. 
	// � �������� ����� 4 ������� ����� � ���-��� ��������� ������.
	DumpValueType_List      = 0xF0
};


// ��������� ���������������� ������ � �����.
// ������ ����� ���������� ���� ���������������� � ������ ������.
typedef struct {
	WriteStream* Stream;
} Writer;

typedef struct {
	ReadStream* Stream;
} Reader;


// ������������� ���������������� ������.
// ��� ������������� ����� ������� watermark ������ ������ ������ ���
// ������ ��������.
void InitReader(Reader* NtlvReader, ReadStream* Stream);
void InitWriter(OUT Writer* NtlvWriter, IN WriteStream* Stream);


// ������� ���������������� ������ � �����.
void WriteUint32(Writer* NtlvWriter, const char* Name, DWORD Value);

void WriteStringW(Writer* NtlvWriter, const char* Name, const WCHAR* Value);

void WriteStringW(Writer* NtlvWriter, const char* Name, const WCHAR* Value,
	DWORD ValueCharLength);

void WriteStringA(Writer* NtlvWriter, const char* Name, const char* Value);

void WriteStringA(Writer* NtlvWriter, const char* Name, const char* Value,
	DWORD ValueCharLength);

void WriteByteArray(Writer* NtlvWriter,const char* Name,const void* Value,
	DWORD ValueLength);

void WriteList(Writer* NtlvWriter,const char* ListName,DWORD ListElementCount);


// ������� ������ ����� � �������� �������.
// ��� ��������� ���������� �� ������������ ��, ��� �� ����� ������ �
// ����������� ����������� NTLV - ������ ������� �� ����� ��� ���������
typedef void (*ReadCallbackFunction)(void* ctx,BYTE Type,const char* Name,
	const void* Value,DWORD ValueLength);

void BulkReadWithCallback(Reader* NtlvReader, ReadCallbackFunction Callback,void* ctx);

}

// ������������� ��������� ������ I/O
bool File_InitDumpWriteStream(DUMP::WriteStream* stream,const WCHAR* file_path);

#endif //#ifndef UUID_6140C07EBBDC4FC18600498BA2A18935