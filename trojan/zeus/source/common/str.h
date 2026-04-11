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
  ����������� ��� ������ �� �������� ANSI � Unicode.

  ����������: ������ �� ��������� �� ������ �� �������� �������� ����� 0x7FFFFFFF �������.
*/

//Operedelyaet whitespace if it is a symbol.
#define IS_SPACE_CHAR(c) ((c) == 0x20 || ((c) >= 0x9 && (c) <= 0xD))

//UTF8 BOM
#define UTF8_BOM      0xBFBBEF
#define UTF8_BOM_SIZE 3

//UTF16 BOM
#define UTF16_BOM      0xFEFF
#define UTF16_BOM_SIZE 2

namespace Str
{  
  enum
  {
    STS_TRIM          = 0x1, //Automatically call a Trim for each row.
    STS_USE_SEPARATOR = 0x2, //Use a splitter instead of the standard method \ r \ n.
  };
  
  enum
  {
    STA_FORMAT_C = 0x1, //Arguments are located in the C-format string.
  };

  //Description UTF-8 string.
  typedef struct
  {
    void *data;   //Line.
    DWORD lenght; //The size of the string in characters, excluding the null character.
    DWORD size;   //Line size in bytes, excluding the null character.
  }UTF8STRING;

  typedef struct
  {
    char anyCharSymbol;  //Symbol of any single character, usually '?'.
    char anyCharsSymbol; //Symbol of any count. any character, usually '*'.
    LPSTR mask;          //Mask.
    DWORD maskSize;      //The size of the mask.
    LPSTR string;        //Line.
    DWORD stringSize;    //The size of the string.
    DWORD beginOfMatch;  //OUT index string, with which to begin the comparison. Always 0 if not
                         //flag is set MATCH_SEARCH_SUBSSTRING.
    DWORD endOfMatch;    //OUT index string, which stood comparison.
    DWORD flags;         //Flags MATCH_ *.
  }MATCHDATAA;

  //Flags MATCHDATAX.flags.
  enum
  {
    MATCH_FULL_EQUAL            = 0x01, //The mask should rasporstarnyatsya until the end of the line.
    MATCH_UNIVERSAL_NEWLINE     = 0x02, //Not razlichtaat \ r \ n and \ n.
    MATCH_CASE_INSENSITIVE      = 0x04, //Insensitive.
    MATCH_CASE_INSENSITIVE_FAST = 0x08, //Insensitive for the characters AZ, az.
    MATCH_SEARCH_SUBSSTRING     = 0x10  //Search poodstroki in a row. (Similarly, the mask "* mask").
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
    ���������, �������� �� ������ ���������� null-terminated �������.

    IN pstrString - ������ ��� ��������.
    IN dwSize     - ������ ������ � ��������.
    
    Return        - true - � ������ ������,
                    false - � ������ ������.
  */
  bool _IsValidA(LPSTR pstrString, DWORD dwSize);
  
  /*
    ���������, �������� �� ������ ���������� null-terminated �������.

    IN pstrString - ������ ��� ��������.
    IN dwSize     - ������ ������ � ��������.
    
    Return        - true - � ������ ������,
                    false - � ������ ������.
  */
  bool _IsValidW(LPWSTR pstrString, DWORD dwSize);

  /*
    ���������, �������� �� ������ ���������� ������.

    IN pstrString - ������ ��� ��������.
    IN iSize      - ������ ������, ��� -1.

    Return        - true - ������ ���������� �����,
                    false - ������ �� ���������� �����.
  */
  bool _IsDecimalStringW(LPCWSTR pstrString, int iSize);

  /*
    ����������� ���� � 16-�� ������ �����.

    IN bt   - ����.
    OUT buf - ������.
  */
  void _byteToCharA(BYTE bt, LPSTR buf);

  /*
    ����������� ���� � 16-�� ������ �����.

    IN bt   - ����.
    OUT buf - ������.
  */
  void _byteToCharW(BYTE bt, LPWSTR buf);

  /*
    ����������� Unicode ������.
    
    OUT pstrDest  - �������� �����, �� ����� ���� NULL.
    IN pstrSource - �������� ������, ����� ���� NULL.
    IN iSize      - ���������� �������� ��� �����������, ��� -1 ��� ������� ����������� ������.
  */
  void _CopyW(LPWSTR pstrDest, LPCWSTR pstrSource, int iSize);

  /*
    ����������� Unicode ������ � ���������� ������.

    IN pstrSource - �������� ������, ����� ���� NULL.
    IN iSize      - ���������� �������� ��� �����������, ��� -1 ��� ������� ����������� ������.

    Return        - ��������� �� ����� ����� ������.
  */
  LPWSTR _CopyExW(LPWSTR pstrSource, int iSize);

  /*
    ���������� Unicode ������ � ����� ������ ������.

    IN buf    - ������.
    IN source - �������� ������, ����� ���� NULL.
    IN size   - ���������� �������� ��� �����������, ��� -1 ��� ������� ����������� ������.
  */
  void _catW(LPWSTR buf, LPWSTR source, int size);

  /*
    ���������� Unicode ������ � ����� ������ ������, � ���������� ������.

    IN OUT ppstrBuf - ������.
    IN pstrSource   - �������� ������, ����� ���� NULL.
    IN iSize        - ���������� �������� ��� �����������, ��� -1 ��� ������� ����������� ������.
  */
  bool _CatExW(LPWSTR *ppstrBuf, LPWSTR pstrSource, int iSize);

  /*
    ����������� ANSI ������.

    OUT pstrDest  - �������� �����, �� ����� ���� NULL.
    IN pstrSource - �������� ������, ����� ���� NULL.
    IN iSize      - ���������� �������� ��� �����������, ��� -1 ��� ������� ����������� ������.
  */
  void _CopyA(LPSTR pstrDest, LPCSTR pstrSource, int iSize);

  /*
    ����������� ANSI ������ � ���������� ������.

    IN pstrSource - �������� ������, ����� ���� NULL.
    IN iSize      - ���������� �������� ��� �����������, ��� -1 ��� ������� ����������� ������.

    Return        - ��������� �� ����� ����� ������.
  */
  LPSTR _CopyExA(LPSTR pstrSource, int iSize);

  /*
    ���������� ANSI ������ � ����� ������ ������.

    IN buf    - ������.
    IN source - �������� ������, ����� ���� NULL.
    IN size   - ���������� �������� ��� �����������, ��� -1 ��� ������� ����������� ������.
  */
  void _catA(LPSTR buf, LPSTR source, int size);

  /*
    ���������� ANSI ������ � ����� ������ ������, � ���������� ������.

    IN OUT ppstrBuf - ������.
    IN pstrSource   - �������� ������, ����� ���� NULL.
    IN iSize        - ���������� �������� ��� �����������, ��� -1 ��� ������� ����������� ������.
  */
  bool _CatExA(LPSTR *ppstrBuf, LPSTR pstrSource, int iSize);
  
  /*
    �������� �������� \r, \n, \t � ������� � ������ � ����� ANSI ������.

    IN pstrStr - ������ ��� ���������.
  */
  void _TrimA(LPSTR pstrStr);

  /*
    �������� �������� \r, \n, \t � ������� � ������ � ����� Unicode ������.

    IN pstrStr - ������ ��� ���������.
  */
  void _TrimW(LPWSTR pstrStr);

  /*
    �������������� ����������/��������������� ANSI ������ � int64. �������������� ������� �� ��� ��� ���� ��
    ����������� ������ �� ������ '0' - 'F'.

    IN pstrStr - ������ ��� ���������.
    OUT pbSign - ���� �� NULL, ���������: true - ����� ���� �� ������� '-',
                 false - ����� ���� ��� ����� '-'.

    Return     - ��������� �����.
  */
  __int64 _ToInt64A(LPSTR pstrStr, bool *pbSign);
  
  /*
    �������������� ����������/��������������� ANSI ������ � int32. �������������� ������� �� ��� ��� ���� ��
    ����������� ������ �� ������ '0' - 'F'.

    IN pstrStr - ������ ��� ���������.
    OUT pbSign - ���� �� NULL, ���������: true - ����� ���� �� ������� '-',
                 false - ����� ���� ��� ����� '-'.

    Return     - ��������� �����.
  */
  int _ToInt32A(LPSTR pstrStr, bool *pbSign);

  /*
    �������������� ����������/��������������� Unicode ������ � int64. �������������� ������� �� ��� ��� ���� ��
    ����������� ������ �� ������ '0' - 'F'.

    IN pstrStr - ������ ��� ���������.
    OUT pbSign - ���� �� NULL, ���������: true - ����� ���� �� ������� '-',
                 false - ����� ���� ��� ����� '-'.
    
    Return     - ��������� �����.
  */
  __int64 _ToInt64W(LPWSTR pstrStr, bool *pbSign);

  /*
    �������������� ����������/��������������� Unicode ������ � int32. �������������� ������� �� ��� ��� ���� ��
    ����������� ������ �� ������ '0' - 'F'.

    IN pstrStr - ������ ��� ���������.
    OUT pbSign - ���� �� NULL, ���������: true - ����� ���� �� ������� '-',
                 false - ����� ���� ��� ����� '-'.

    Return     - ��������� �����.
  */
  int _ToInt32W(LPWSTR pstrStr, bool *pbSign);
  
  /*
    �������������� x64 ����� � ANSI ������.

    IN iNumber - �������� �����.
    OUT pBuf   - ������.
    IN bRadix  - ������� ���������.
    IN bSigned - true - ���� �������������, false - ���� ����� �����������.

    Return     - ���������� ������������� ���� � pBuf.
  */
  DWORD _FromInt64A(__int64 iNumber, LPSTR pBuf, BYTE bRadix, bool bSigned);
  
  /*
    �������������� x32 ����� � ANSI ������.

    IN iNumber - �������� �����.
    OUT pBuf   - ������.
    IN bRadix  - ������� ���������.
    IN bSigned - true - ���� �������������, false - ���� ����� �����������.

    Return     - ���������� ������������� ���� � pBuf.
  */
  DWORD _FromInt32A(int iNumber, LPSTR pBuf, BYTE bRadix, bool bSigned);

  /*
    �������������� x64 ����� � Unicode ������.

    IN iNumber - �������� �����.
    OUT pBuf   - ������.
    IN bRadix  - ������� ���������.
    IN bSigned - true - ���� �������������, false - ���� ����� �����������.

    Return     - ���������� ������������� ���� � pBuf
  */
  DWORD _FromInt64W(__int64 iNumber, LPWSTR pBuf, BYTE bRadix, bool bSigned);

  /*
    �������������� x64 ����� � Unicode ������.

    IN iNumber - �������� �����.
    OUT pBuf   - ������.
    IN bRadix  - ������� ���������.
    IN bSigned - true - ���� �������������, false - ���� ����� �����������.

    Return     - ���������� ������������� ���� � pBuf
  */
  DWORD _FromInt32W(int iNumber, LPWSTR pBuf, BYTE bRadix, bool bSigned);

  /*
    �������������� ���������� ANSI ������ � DWORD. �������������� ������� �� ��� ��� ���� ��
    ����������� ������ �� ������ '0' - '9', 'A' - 'F', 'a' - 'f'. ����� ���� � ������ ������
    ����� ������� 0x, �� ������� �����������.

    IN str - ������ ��� ���������.

    Return - ��������� �����.
  */
  DWORD _hexStringToDwordA(LPSTR str);

  /*
    �������������� ���������� Unicode ������ � DWORD. �������������� ������� �� ��� ��� ���� ��
    ����������� ������ �� ������ '0' - '9', 'A' - 'F', 'a' - 'f'. ����� ���� � ������ ������
    ����� ������� 0x, �� ������� �����������.

    IN str - ������ ��� ���������.

    Return - ��������� �����.
  */
  DWORD _hexStringToDwordW(LPWSTR str);

  /*
    �������������� HEX-������ � �������� ������.

    IN string  - ������.
    OUT buffer - �����. ����� ���� ���������� �� string.

    Return     - true - ���� ������ ������� �������������, ��� �����,
                 false - � ������ ������.                                                      
  */
  bool _fromHexW(LPWSTR string, void *buffer);

  /*
    �������������� �������� ������ � HEX-������.

    IN buffer     - �����. ����� ���� ���������� �� string.
    IN bufferSize - ������ ������.
    OUT string    - ������. �� ������ ����� ���� �� ����� (bufferSize * 2 + 1) ��������.
  */
  void _toHexW(const void *binary, DWORD binarySize, LPWSTR string);

  /*
    �������������� �������� ������ � HEX-������.

    IN buffer     - �����. ����� ���� ���������� �� string.
    IN bufferSize - ������ ������.
    OUT string    - ������. �� ������ ����� ���� �� ����� (bufferSize * 2 + 1) ��������.

    Return     - true - ���� ������ ������� �������������, ��� �����,
                 false - � ������ ������.                                                      
  */
  void _toHexA(const void *binary, DWORD binarySize, LPSTR string);

  /*
    ����������� ��������� ����. ������� � � ���������� �����.
    
    IN OUT str - ������ ��� ���������.
  */
  void _fromCFormatA(LPSTR str);

  /*
    ����������� ��������� ����. ������� � � ���������� �����.
    
    IN OUT str - ������ ��� ���������.
  */
  void _fromCFormatW(LPWSTR str);

  /*
    ���������� ������ �� ������� �� ������ ������� \n ��� \r. ����������� ��� Win, Mac, Unix.

    IN input     - �������� ������.
    IN inputSize - ������ �������� ������.
    OUT strings  - ������ ���������� �����, ������ ���� ���������� ����� Mem::freeArrayOfPointers.
                   ������, ������� ����� ����� ������� ������ ����� ���� �������� ���
                   NULL-����������, ��� � ������ �������.
    IN flags     - ����� STS_*.
    IN separator - ����������� �����, ��������� ����� ��� ����� STS_USE_SEPARATOR.
                  
    Return       - ���������� ��������� �����, ��� (DWORD)-1 � ������ ������������� ������.

  */
  DWORD _splitToStringsA(LPSTR input, DWORD inputSize, LPSTR **strings, DWORD flags, char separator);

  /*
    ���������� ������ �� ������� �� ������ ������� \n ��� \r. ����������� ��� Win, Mac, Unix.

    IN input     - �������� ������.
    IN inputSize - ������ �������� ������.
    OUT strings  - ������ ���������� �����, ������ ���� ���������� ����� Mem::freeArrayOfPointers.
                   ������, ������� ����� ����� ������� ������ ����� ���� �������� ���
                   NULL-����������, ��� � ������ �������.
    IN flags     - ����� STS_*.
    IN separator - ����������� �����, ��������� ����� ��� ����� STS_USE_SEPARATOR.
                  
    Return       - ���������� ��������� �����, ��� (DWORD)-1 � ������ ������������� ������.

  */
  DWORD _splitToStringsW(LPWSTR input, DWORD inputSize, LPWSTR **strings, DWORD flags, WCHAR separator);

  /*
    ���������� ������ �� ��������� � ���������� �������.

    IN input     - �������� ������.
    IN inputSize - ������ �������� ������.
    OUT args     - ������ ���������� �����, ������ ���� ���������� ����� Mem::freeArrayOfPointers.
                   ������, ������� ����� ����� ������� ������ ����� �������� ��� "\0".
    IN flags     - ����� STA_*.

    Return       - ���������� ��������� ����������, ��� (DWORD)-1 � ������ ������������� ������.
  */
  DWORD _getArgumentsA(const LPSTR input, DWORD inputSize, LPSTR **args, DWORD flags);

  /*
    ���������� ������ �� ��������� � ���������� �������.

    IN input     - �������� ������.
    IN inputSize - ������ �������� ������.
    OUT args     - ������ ���������� �����, ������ ���� ���������� ����� Mem::freeArrayOfPointers.
                   ������, ������� ����� ����� ������� ������ ����� �������� ��� "\0".
    IN flags     - ����� STA_*.

    Return       - ���������� ��������� ����������, ��� (DWORD)-1 � ������ ������������� ������.
  */
  DWORD _getArgumentsW(const LPWSTR input, DWORD inputSize, LPWSTR **args, DWORD flags);

  /*
    ����������� ���������� � ���� ������.

    IN args      - ���������.
    IN argsCount - ���. �����������.

    Return       - ������ � ������ ������ (����� ���������� ����� Mem),
                   false - � ������ �������.
  */
  LPWSTR _joinArgumentsW(const LPWSTR *args, DWORD argsCount);
  
  /*
    �������� ANSI ������ �� Unicode.

    IN source     - �������� Unicode-������.
    IN sourceSize - ������ source � ��������, ��� -1 ��� ���������������.
    OUT dest      - ����� ANSI-������, ������ ����� ��������� �� 0. ����� ���� NULL ���
                    destSize == 0.
    IN destSize   - ������ ������ dest � ������, ������� ������� ������. ���� 0, �� ��������
                    ������ ��������� ������ ������ � ������, �������� ������� ������.

    Return        - 0 - ������ (dest[0] ����� ����� ����),
                    ��� ���. ���� ������������� ��� ��������� � dest, �������� ������� ������.
  */
  int _unicodeToAnsi(const LPWSTR source, int sourceSize, LPSTR dest, int destSize);

  /*
    �������� ANSI ������ �� Unicode, � ���������� ������.

    IN source - �������� ������.
    IN size   - ������ pstrSource � ��������, ��� -1 ��� ���������������.

    Return    - ANSI-������(������ ��������� �� 0), ��� NULL � ������ ������.
  */
  LPSTR _unicodeToAnsiEx(const LPWSTR source, int size);

  /*
    �������� Unicode ������ �� ANSI.

    IN source     - �������� ANSI-������.
    IN sourceSize - ������ source � ��������, ��� -1 ��� ���������������.
    OUT dest      - ����� Unicode-������, ������ ����� ��������� �� 0. ����� ���� NULL ���
                    destSize == 0.
    IN destSize   - ������ ������ dest � ��������, ������� ������� ������. ���� 0, �� ��������
                    ������ ��������� ������ ������ � ��������, �������� ������� ������.
    
    Return        - 0 - ������ (dest[0] ����� ����� ����),
                    ��� ���. ��������� ������������� ��� ��������� � dest, �������� ������� ������.
  */
  int _ansiToUnicode(LPSTR source, int sourceSize, LPWSTR dest, int destSize);

  /*
    �������� Unicode ������ �� ANSI, � ���������� ������.

    IN source - �������� ANSI-������.
    IN size   - ������ pstrSource � ��������, ��� -1 ��� ���������������.

    Return    - Unicode-������(������ ��������� �� 0), ��� NULL � ������ ������.
  */
  LPWSTR _ansiToUnicodeEx(LPSTR source, int size);

  /*
    �������� Unicode ������ �� OEM.

    IN source     - �������� OEM-������.
    IN sourceSize - ������ source � ��������, ��� -1 ��� ���������������.
    OUT dest      - ����� Unicode-������, ������ ����� ��������� �� 0. ����� ���� NULL ���
                    destSize == 0.
    IN destSize   - ������ ������ dest � ��������, ������� ������� ������. ���� 0, �� ��������
                    ������ ��������� ������ ������ � ��������, �������� ������� ������.
    
    Return        - 0 - ������ (dest[0] ����� ����� ����),
                    ��� ���. ��������� ������������� ��� ��������� � dest, �������� ������� ������.
  */
  int _oemToUnicode(LPSTR source, int sourceSize, LPWSTR dest, int destSize);

  /*
    �������� Unicode ������ �� OEM, � ���������� ������.

    IN source - �������� OEM-������.
    IN size   - ������ pstrSource � ��������, ��� -1 ��� ���������������.

    Return    - Unicode-������, ��� NULL � ������ ������.
  */
  LPWSTR _oemToUnicodeEx(LPSTR source, int size);

  /*
    ��������� ������ Unicode ������.

    IN pstrStr - ������ ��� ���������. ����� ���� NULL.

    Return     - ������ ������.
  */
  int _LengthA(LPCSTR pstrStr);

  /*
    ��������� ������ ANSI ������.

    IN pstrStr - ������ ��� ���������. ����� ���� NULL.

    Return     - ������ ������.
  */
  int _LengthW(LPCWSTR pstrStr);

  /*
    ���������� ��� ANSI ������.

    IN pstrStr1 - ������ ������. ����� ���� NULL.
    IN pstrStr2 - ������ ������. ����� ���� NULL.
    IN iSize1   - ������ ������ ������ ��� -1.
    IN iSize2   - ������ ������ ������ ��� -1.

    Return      -  0 - ������ �����,
                  -1 - ������ ������ ������ ������ ������.
                   1 - ������ ������ ������ ������ ������.
  */
  int _CompareA(LPCSTR pstrStr1, LPCSTR pstrStr2, int iSize1, int iSize2);

  /*
    ���������� ��� Unicode ������.

    IN pstrStr1 - ������ ������. ����� ���� NULL.
    IN pstrStr2 - ������ ������. ����� ���� NULL.
    IN iSize1   - ������ ������ ������ ��� -1.
    IN iSize2   - ������ ������ ������ ��� -1.

    Return      -  0 - ������ �����,
                  -1 - ������ ������ ������ ������ ������.
                   1 - ������ ������ ������ ������ ������.
  */
  int _CompareW(LPCWSTR pstrStr1, LPCWSTR pstrStr2, int iSize1, int iSize2);

  /*
    ����� ������� � ANSI ������.

    IN string - ������, � ������� ����� ������������� �����.
    IN c      - ������ ��� ������.

    Return    - ��������� �� ������ �������� ������, ��� NULL ���� ������ �� ������.
  */
  LPSTR _findCharA(const LPSTR string, char c);

  /*
    ����� ������� � ANSI ������ � ������ �������.

    IN string - ������, � ������� ����� ������������� �����.
    IN c      - ������ ��� ������.

    Return    - ��������� �� ������ �������� ������, ��� NULL ���� ������ �� ������.
  */
  LPSTR _findRCharA(const LPSTR string, char c);

  /*
    ����� ������� � Unicode ������.

    IN string - ������, � ������� ����� ������������� �����.
    IN c      - ������ ��� ������.

    Return    - ��������� �� ������ �������� ������, ��� NULL ���� ������ �� ������.
  */
  LPWSTR _findCharW(const LPWSTR string, WCHAR c);
  
  /*
    ����� ������� � Unicode ������ � ������ �������.

    IN string - ������, � ������� ����� ������������� �����.
    IN c      - ������ ��� ������.

    Return    - ��������� �� ������ �������� ������, ��� NULL ���� ������ �� ������.
  */
  LPWSTR _findRCharW(const LPWSTR string, WCHAR c);

  /*
    ����� ��������� � ANSI ������.

    IN string    - ������, � ������� ����� ������������� �����. �� ����� ���� NULL.
    IN subString - ��������� ��� ������. �� ����� ���� NULL.

    Return       - ��������� �� ������ �������� ������, ��� NULL ���� ������ �� �������.
  */
  LPSTR _findSubStringA(const LPSTR string, const LPSTR subString);

  /*
    ����� ��������� � Unicode ������.
    
    IN string    - ������, � ������� ����� ������������� �����. �� ����� ���� NULL.
    IN subString - ��������� ��� ������. �� ����� ���� NULL.

    Return           - ��������� �� ������ �������� ������, ��� NULL ���� ������ �� �������.
  */
  LPWSTR _findSubStringW(const LPWSTR string, const LPWSTR subString);
  
  /*
    ���������� ��� wnsprintfW..

    OUT pBuf      - ��������� �� ����� �������� ������.
    IN iBufSize   - ������ ������ (������� ������� ������).
    IN pstrFormat - ������ ������.
    IN ...        - ��������� ������.

    Return        - ������ ������ ��� �������� �������, ��� -1 � ������ ������.
  */
  int _sprintfW(LPWSTR pBuf, int iBufSize, LPCWSTR pstrFormat, ...);
  
  /*
    ���������� ��� wnsprintfA..

    OUT pBuf      - ��������� �� ����� �������� ������.
    IN iBufSize   - ������ ������ (������� ������� ������).
    IN pstrFormat - ������ ������.
    IN ...        - ��������� ������.

    Return        - ������ ������ ��� �������� �������, ��� -1 � ������ ������.
  */
  int _sprintfA(LPSTR pBuf, int iBufSize, LPCSTR pstrFormat, ...);

  /*
    ���������� ��� wvnsprintfW..

    OUT pBuf      - ��������� �� ����� �������� ������.
    IN iBufSize   - ������ ������ (������� ������� ������).
    IN pstrFormat - ������ ������.
    IN arglist    - ��������� �����.

    Return        - ������ ������ ��� �������� �������, ��� -1 � ������ ������.
  */
  int _vsprintfW(LPWSTR pBuf, int iBufSize, LPCWSTR pstrFormat, va_list arglist);

  /*
    ���������� ��� wvnsprintfW..

    OUT pBuf      - ��������� �� ����� �������� ������.
    IN iBufSize   - ������ ������ (������� ������� ������).
    IN pstrFormat - ������ ������.
    IN arglist    - ��������� �����.

    Return        - ������ ������ ��� �������� �������, ��� -1 � ������ ������.
  */
  int _vsprintfA(LPSTR pBuf, int iBufSize, LPCSTR pstrFormat, va_list arglist);

  /*
    ���������� ��� wsprintfW, ������� �������������� �������� ������.

    OUT ppBuf     - ��������� �� ����� �������� ������. ������ ���� ���������� ����� Mem.
    IN pstrFormat - ������ ������.
    IN ...        - ��������� ������.

    Return        - ������ ������ ��� �������� �������, ��� -1 � ������ ������.

    ����������: ����������� ������ �������� ������ ~MAX_SPRINTF_STRING_SIZE;
  */
  int _sprintfExW(LPWSTR *ppBuf, LPCWSTR pstrFormat, ...);

  /*
    ���������� ��� _sprintfExW, ������� ��������� ����� ������ � ����� �����������.

    IN OUT buffer - ������. ����� ��������� �� NULL. � ������ ������ � ���� �� ��� ������ NULL,
                    ����� ������������ �� offset �������� � ���������� �� ������� ������.
    IN offset     - ������ � �������� � *buffer, � �������� ����� ������ ������� ���������.
    IN format     - ������ ������.
    IN ...        - ��������� ��� ������.

    Return        - ������ ������ ������ ��� �������� �������, ��� (DWORD)-1 � ������ ������.
  */
  DWORD _sprintfCatExW(LPWSTR *buffer, DWORD offset, const LPWSTR format, ...);

  /*
    ���������� ��� wsprintfA, ������� �������������� �������� ������.

    OUT ppBuf     - ��������� �� ����� �������� ������. ������ ���� ���������� ����� Mem.
    IN pstrFormat - ������ ������.
    IN ...        - ��������� ������.

    Return        - ������ ������ ��� �������� �������, ��� -1 � ������ ������.

    ����������: ����������� ������ �������� ������ ~MAX_SPRINTF_STRING_SIZE;
  */
  int _sprintfExA(LPSTR *ppBuf, LPCSTR pstrFormat, ...);

  /*
    ���������� ��� wvsprintfW, ������� �������������� �������� ������.

    OUT ppBuf     - ��������� �� ����� �������� ������. ������ ���� ���������� ����� Mem.
    IN pstrFormat - ������ ������.
    IN arglist    - ��������� �����.

    Return        - ������ ������ ��� �������� �������, ��� -1 � ������ ������.

    ����������: ����������� ������ �������� ������ ~MAX_SPRINTF_STRING_SIZE;
  */
  int _vsprintfExW(LPWSTR *ppBuf, LPCWSTR pstrFormat, va_list arglist);
  
  /*
    ���������� ��� _sprintfExA, ������� ��������� ����� ������ � ����� �����������.

    IN OUT buffer - ������. ����� ��������� �� NULL. � ������ ������ � ���� �� ��� ������ NULL,
                    ����� ������������ �� offset �������� � ���������� �� ������� ������.
    IN offset     - ������ � �������� � *buffer, � �������� ����� ������ ������� ���������.
    IN format     - ������ ������.
    IN ...        - ��������� ��� ������.

    Return        - ������ ������ ������ ��� �������� �������, ��� (DWORD)-1 � ������ ������.
  */
  DWORD _sprintfCatExA(LPSTR *buffer, DWORD offset, const LPSTR format, ...);

  /*
    ���������� ��� _vsprintfExW, ������� ��������� ����� ������ � ����� �����������.

    IN OUT buffer - ������. ����� ��������� �� NULL. � ������ ������ � ���� �� ��� ������ NULL,
                    ����� ������������ �� offset �������� � ���������� �� ������� ������.
    IN offset     - ������ � �������� � *buffer, � �������� ����� ������ ������� ���������.
    IN format     - ������ ������.
    IN arguments  - ��������� ��� ������.

    Return        - ������ ������ ������ ��� �������� �������, ��� (DWORD)-1 � ������ ������.
  */
  DWORD _vsprintfCatExW(LPWSTR *buffer, DWORD offset, const LPWSTR format, va_list arguments);

  /*
    ���������� ��� wvsprintfA, ������� �������������� �������� ������.

    OUT ppBuf     - ��������� �� ����� �������� ������. ������ ���� ���������� ����� Mem.
    IN pstrFormat - ������ ������.
    IN arglist    - ��������� �����.

    Return        - ������ ������ ��� �������� �������, ��� -1 � ������ ������.

    ����������: ����������� ������ �������� ������ ~MAX_SPRINTF_STRING_SIZE;
  */
  int _vsprintfExA(LPSTR *ppBuf, LPCSTR pstrFormat, va_list arglist);
  
  /*
    ���������� ��� _vsprintfExA, ������� ��������� ����� ������ � ����� �����������.

    IN OUT buffer - ������. ����� ��������� �� NULL. � ������ ������ � ���� �� ��� ������ NULL,
                    ����� ������������ �� offset �������� � ���������� �� ������� ������.
    IN offset     - ������ � �������� � *buffer, � �������� ����� ������ ������� ���������.
    IN format     - ������ ������.
    IN arguments  - ��������� ��� ������.

    Return        - ������ ������ ������ ��� �������� �������, ��� (DWORD)-1 � ������ ������.
  */
  DWORD _vsprintfCatExA(LPSTR *buffer, DWORD offset, const LPSTR format, va_list arguments);

  /*
    ��������� �������� �� ����� UTF-8 BOM.

    IN data - ����� ��� ��������.
  
    Return  - true - � ������ ������,
              false - � ������ ������.
  */
  bool _utf8IsBom(const void *data);

  /*
    ������������ ������.

    IN string  - ������ UTF-8.
  */
  void _utf8Free(UTF8STRING *string);

  /*
    �������� ������ UTF-8 �� Unicode.

    IN source     - �������� ������.
    IN sourceSize - ������ ������ pstrSource, ��� -1 ��� ���������������.
    OUT dest      - ������ UTF-8.

    Return        - true - � ������ ������,
                    false - � ������ ������.
  */
  bool _utf8FromUnicode(const LPWSTR source, int sourceSize, UTF8STRING *dest);

  /*
    �������� ������ UTF-8 �� ANSI.

    IN source     - �������� ������.
    IN sourceSize - ������ ������ pstrSource, ��� -1 ��� ���������������.
    OUT dest      - ������ UTF-8.

    Return        - true - � ������ ������,
                    false - � ������ ������.
  */
  bool _utf8FromAnsi(const LPSTR source, int sourceSize, UTF8STRING *dest);

  /*
    �������������� UTF-8 ������ � Unicode.

    IN rawString - UTF-8 ������.
    IN size      - ������ ������ � ������, ��� -1 ��� ���������������.

    Return       - Unicode-������ � ������ ������ (������ ���� ����������� ����� Mem),
                   ��� NULL � ������ ������.
  */
  LPWSTR _utf8ToUnicode(const void *rawString, const int size);

  /*
    ��������� �������� �� ������, ���������� ������-�������.

    IN string - ������-������ ��� ��������.
    IN size   - ������ ������-������.
    
    Return    - true - � ������ ������,
                false - � ������ ������.
  */
  bool _isValidMultiStringA(const LPSTR string, DWORD size);

  /*
    ��������� �������� �� ������, ���������� ������-�������.

    IN string - ������-������ ��� ��������.
    IN size   - ������ ������-������.
    
    Return    - true - � ������ ������,
                false - � ������ ������.
  */
  bool _isValidMultiStringW(const LPWSTR string, DWORD size);

  /*
    �������� ������ �� ������-������ �� �������.

    IN string - ������-������.
    IN index  - ������.

    Return    - ��������� �� ������, ��� NULL � ������ ������.
  */
  LPSTR _multiStringGetIndexA(LPSTR string, DWORD index);

  /*
    �������� ������ �� ������-������ �� �������.

    IN string - ������-������.
    IN index  - ������.

    Return    - ��������� �� ������, ��� NULL � ������ ������.
  */
  LPWSTR _multiStringGetIndexW(LPWSTR string, DWORD index);

  /*
    ��������� ���. ����� � ������-������.

    IN string - ������-������.

    Return    - ���. �����.
  */
  DWORD _multiStringGetCountA(const LPSTR string);
  
  /*
    ��������� ���. ����� � ������-������.

    IN string - ������-������.

    Return    - ���. �����.
  */
  DWORD _multiStringGetCountW(const LPWSTR string);

  /*
    ������� ������������ � ����� ������� �� ������.

    IN string  - �������� ������.
    OUT length - ������ ������ ������ � ��������, ������ ������� �������.

    Return     - �����������(����� ���������� ����� Mem), ��� NULL � ������� ������.
  */
  LPSTR _multiStringCreateA(const LPSTR string, LPDWORD length);

  /*
    ������� ������������ � ����� ������� �� ������.

    IN string  - �������� ������.
    OUT length - ������ ������ ������ � ��������, ������ ������� �������.

    Return     - �����������(����� ���������� ����� Mem), ��� NULL � ������� ������.
  */
  LPWSTR _multiStringCreateW(const LPWSTR string, LPDWORD length);

  /*
    ��������� �� �������������� ������ ��� ��������� ������.

    IN dwErrorCode - ��� ������.

    Return         - ������ ������, ��� NULL � ������ ������. ������ ������ ���� ����������� �����
                     Mem.
  */
  LPWSTR _GetErrorString(DWORD dwErrorCode);

  /*
    ���������� ����������� ��������� \, ', ", \0 - ������. ������ addslashes �� PHP.

    IN source - �������� ������.
    IN dest   - �������� ������.
  */
  void _addSlashesW(LPWSTR source, LPWSTR dest);

  /*
    ���������� ����������� ��������� � ���������� ������.

    IN source - �������� ������.
    IN size   - ������ �������� ������ � ��������. ����� ���� -1.

    Return    - NULL - � ������ ������, ����� ����� ������ � ������ ������.
  */
  LPWSTR _addSlashesExW(const LPWSTR source, SIZE_T size);

  /*
    ���������� ����������� ��������� \, ', ", \0 - ������. ������ addslashes �� PHP.

    IN source - �������� ������.
    IN dest   - �������� ������.
  */
  void _addSlashesA(LPSTR source, LPSTR dest);

  /*
    ���������� ����������� ��������� � ���������� ������.

    IN source - �������� ������.
    IN size   - ������ �������� ������ � ��������. ����� ���� -1.

    Return    - NULL - � ������ ������, ����� ����� ������ � ������ ������.
  */
  LPSTR _addSlashesExA(const LPSTR source, SIZE_T size);

  /*
    ��������� ������� ������ ������ � ������ ����� ���������� ����� \r\n ��� \n.

    IN string - ������ ������. � ����������� ������� ������ ���� next.
    IN memEnd - ����� ������. ������ string + size.
    OUT next  - ��������� �� ��������� ������, ��� ����� ������.

    Return    - ������ ������.
  */
  SIZE_T __inline _getCurrentStringSizeW(const LPWSTR string, const LPWSTR memEnd, LPWSTR *next);

  /*
    ��������� ������� ������ ������ � ������ ����� ���������� ����� \r\n ��� \n.

    IN string - ������ ������. � ����������� ������� ������ ���� next.
    IN memEnd - ����� ������. ������ string + size.
    OUT next  - ��������� �� ��������� ������, ��� ����� ������.

    Return    - ������ ������.
  */
  SIZE_T __inline _getCurrentStringSizeA(const LPSTR string, const LPSTR memEnd, LPSTR *next);

  /*
    ��������� ������ � ������.

    IN md - ������ ����������.

    Return - true  - ���������� �������,
             false - ���������� �� �������.
  */
  bool _matchA(MATCHDATAA *md);

  /*    Lightweight Preset over _matchA (), for comparison with the symbols' * ','? "And without tauzhe
    register.

    IN mask - a mask.
    IN string - string.

    Return - true - a match is found,
             false - no match.
  */
  bool _matchExA(const LPSTR mask, const LPSTR string);
};
