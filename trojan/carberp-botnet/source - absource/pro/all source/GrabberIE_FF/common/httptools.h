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
  ����������� ��� ��������� ������ HTTP.
*/
#pragma once

namespace HttpTools
{
  enum
  {
    GMH_HTTP_METHOD,                                      //��� HTTP-�������.
    GMH_HTTP_URI,                                         //HTTP-URI
    GMH_REQUEST_HTTP_VERSION,                             //HTTP-������.
    GMH_RESPONSE_HTTP_VERSION = GMH_HTTP_METHOD,          //HTTP-������.
    GMH_RESPONSE_STATUS       = GMH_HTTP_URI,             //HTTP-������.
    GMH_RESPONSE_STATUSTEXT   = GMH_REQUEST_HTTP_VERSION, //��������� HTTP-������.
    GMH_DATA,                                             //������ ������ ����� ����������.
    GMH_COUNT
  };

  //��� ���������� ��� URLDATA.
  enum
  {
    UDS_UNKNOWN,
    UDS_HTTP,
    UDS_HTTPS
  };

  //�������� URL.
  typedef struct
  {
    LPSTR host;           //����.
    LPSTR uri;            //URI. ������ ����� ���������� � '/'.
    DWORD uriExtraOffset; //������� ������ �� ������ � uri. (? ��� #).
    WORD port;            //����.
    BYTE scheme;          //��� UDS_*.
  }URLDATA;

  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ��������� �������� ���������� �� "x-www-form-urlencoded" ��� URI (�������� �� ? �� ����������).

    IN list     - ������ ����������.
    IN listSize - ������ ������ � ������
    IN varable  - ���������� ��� ������, � URL-���������.
    OUT valSize - ������ �������� ��������� � ������..

    Return      - ����� ����������, ��� NULL ���� ���������� �� �������.
  */
  LPSTR _findValueInUrlEncoded(const void *list, DWORD listSize, const LPSTR varable, LPDWORD valSize);
  
  /*
    ������� URL. ����� ������������� ���������� ���������� ����� _freeUrlData().

    IN url - URL ������ ��� ��������.
    OUT ud - ��������� �������.

    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool _parseUrl(const LPSTR url, URLDATA *ud);

  /*
    ������������ URLDATA.

    IN ud - URLDATA ��� ������������.
  */
  void _freeUrlData(URLDATA *ud);

  /*
    ��������� ����� ����� �� URL � ��������������� %XX � ������������� �� UTF8.

    IN url - URL.

    Return - NULL - � ������ ������,
             ��� ����� � ������ ������ (����� ���������� ����� Mem).
  */
  LPWSTR _getFileNameFromUrl(const LPSTR url);

  /*
    ���������� ��� ���� �� �������. 

    IN tag     - ��� ���� ��� ����������.
    IN tagSize - ������ pTag.
    IN string  - ������ ��� ���������. ������ ����� ���������� ��� � ������� '<' ��� '</', ��� �
                 ����� � ����� ����.

    Return    - true - ���� ��� ��������� �� �������.
                false - ���� ��� �� ��������� �� �������.
  */
  bool _compareTagNameA(const LPSTR tag, DWORD tagSize, const LPSTR string);

  /*
    ������� ���� �� ������.

    IN OUT string - ����� ��� ���������.
    IN size       - ������ ������.

    Return        - ���������� ���� ����������� � ������, �������� �������� ������ '\0'. 
  */
  DWORD _removeTagsA(LPSTR string, DWORD size);
  
  /*
    FIXME:UrlUnescape
    �������� ������ �������� URL ���������.

    IN input     - ������ ��� �����������.
    IN inputSize - ������ ������ ��� �����������.
                     �������� '\0'.
    OUT output   - ����� ��� ����������� ������, ������ ������ ������ ���� �� �����
                   (dwInputSize * 3) + 1, ��� �������������� ������������.

    Return: ���������� ���� ������������� � output, �������� �������� ������ '\0'.
  */
  DWORD _urlEncodeA(LPSTR input, DWORD inputSize, LPSTR output);

  /*
    �������� ������ �������� URL ���������.

    IN input     - ������ ��� �����������.
    IN inputSize - ������ ������ ��� �����������.
                     �������� '\0'.
    OUT output   - ����� ��� ����������� ������, ������ ������ ������ ���� �� �����
                   (dwInputSize * 3) + 1, ��� �������������� ������������.

    Return: ���������� ���� ������������� � output, �������� �������� ������ '\0'.
  */
  DWORD _urlEncodeW(LPWSTR input, DWORD inputSize, LPWSTR output);

  /*
    �������� ������ �������� URL ���������, �������� URLEncodeA.

    IN input     - ������ ��� �����������.
    IN inputSize - ������ ������ ��� �����������.

    Return: ������������ ������ (����� ������������� ����� Mem::free()),
            NULL - � ������ ������.
  */
  LPSTR _urlEncodeExA(LPSTR input, DWORD inputSize);

  /*
    FIXME:UrlUnescape
    �������� ������ �������� URL ���������, �������� URLEncodeW.

    IN input     - ������ ��� �����������.
    IN inputSize - ������ ������ ��� �����������.

    Return: ������������ ������ (����� ������������� ����� Mem::free()),
            NULL - � ������ ������.
  */
  LPWSTR _urlEncodeExW(LPWSTR input, DWORD inputSize);

  /*
    ������ Mime-����������.

    IN mimeData - ������ � Mime-����������.
    IN mimeSize - ������ mimeData.
    IN header   - �������� ��� ���������, ����� ��������� �������� GMH_*.
    OUT size    - ������ ����������� ��������, ����� ���� 0, ���� ���������� �� ����������.

    Return      - ���������� ��� pstrHeader, �� ������ ����� NULL, ���� �������� �� ���������
                  ��� ��������� ������ (*pdwSize ����� ����� ����� 0).
  */
  LPSTR _getMimeHeader(const void *mimeData, DWORD mimeSize, const LPSTR header, SIZE_T *size);

  /*
    �������� ��������� �� MIME-���������.
    
    IN OUT mimeData - ������ � Mime-����������.
    IN mimeSize     - ������ mimeData.
    IN header       - �������� ��� ���������, �� ����� ���� GMH_*.

    Return          - ����� ������ MIME-���������.(������ ������ ����� \r\n\r\n �����������.)
  */
  DWORD _removeMimeHeader(void *mimeData, DWORD mimeSize, LPSTR header);

  /*
    ����������� ���������.

    IN OUT mimeData - ������ � Mime-����������.
    IN mimeSize     - ������ mimeData.
    IN header       - �������� ��� ���������, �� ����� ���� GMH_*.
    IN context      - �������� ��������. ����� ���� NULL.
    
    Return          - ����� ������ MIME-���������.(������ ������ ����� \r\n\r\n �����������.)
  */
  DWORD _modifyMimeHeader(void *mimeData, DWORD mimeSize, const LPSTR header, const LPSTR context);

  /*
    ������ ������ chunk-�����.

    IN data             - ������ �����.
    IN dataSize         - ������ ��������� ����.
    OUT chunkedData     - ������ ������. NULL - ���� ������ �������� �� ���������.
    OUT chunkedDataSize - ������ ������.

    Return              - NULL - ������ � �������,
                          ��������� �� ��������� ���� ����� ��������� chunk'�.
  */
  void *_readChunkedData(const void *data, DWORD dataSize, void **chunkedData, LPDWORD chunkedDataSize);

  /*
    ���������� URL-���������� � ������� URL.

    IN source - �������� URL, ��������� ������� ����� �����������.
    IN dest   - �������� URL, � ����� ������� ��������� ����� ���������. (��������� ����� ���
                ������������).
    
    Return    - ����� URL (����� ���������� ����� Mem), ��� NULL � ������ ������.
  */
  LPSTR _catExtraInfoFromUrlToUrlA(const LPSTR source, const LPSTR dest);

  /*
    ������������� ������ HTTP-�����������.

    IN source     - �������� ������.
    IN sourceSize - ������ source.
    OUT userName  - ��� ������������, ����� ���������� ����� Mem.
    OUT password  - ������, ����� ���������� ����� Mem.

    Return        - true - � ������ ��������� ������������,
                    false - � ������ ������.
  */
  bool _parseAuthorization(const LPSTR source, DWORD sourceSize, LPWSTR *userName, LPWSTR *password);
};
