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
  ������ � MS CAB ������� ����� ���������� cabinet.dll. ���������� ��������� ������� ����������� 
  ANSI ���������.
  
  ������� ��������������� �� ����������� ������.

  ����������: ������� �� ��������� ��� ������������� �������������, ������� ���������� ������������
              ������� �������������.

  TODO:
    �������� ��������� ���������� �����, �.�. ���������� ������ CB_MAX_DISK.
*/

#if !defined XLIB_MSCAB_FCI
  #error XLIB_MSCAB_FCI not defined!
#endif

#if !defined XLIB_MSCAB_FDI
  #error XLIB_MSCAB_FDI not defined!
#endif

namespace MsCab
{
  enum
  {
    CFF_RECURSE = 0x1, //Search the subdirectories.
  };

  /*
    �������������.
  */
  void Init(void);

  /*
    ���������������.
  */
  void Uninit(void);

#if(XLIB_MSCAB_FCI > 0)
  /*
    �������� ������ ������.

    IN pstrPath     - ���� � ������.
    IN pstrFile     - ��� ������. ����� ���� NULL, ����� ��� ������ ���� �������� � pstrPath.
    IN pstrTempPath - ���������� ��� ��������� ������. ���� ������� NULL, �� ����������� �������� 
                      GetTempPath

    Return          - ����� ������, ����� ������ ���� ������ ����� FCIClose,
                      ��� NULL � ������ ������.
  */
  void *FCICreate(LPWSTR pstrPath, LPWSTR pstrFile, LPWSTR pstrTempPath);

  /*
    ���������� ����� � �����.
    
    IN pFCI           - �����.
    IN pstrSourceFile - �������� ����.
    IN pstrDestFile   - �������� ���� � ������, �������� �������� �����. ����� ���������������� �
                        UTF-8, �� ���� ����� ����������� ������ ������ ��������� 256 - 1 ��������,
                        �� ����� �������� � ������ �������� ������� ��������� ��.

    Return            - true - � ������ ������,
                        false - � ������ ������.
  */
  bool FCIAddFile(void *pFCI, LPWSTR pstrSourceFile, LPWSTR pstrDestFile);
  
  /*
    �������� ������.

    IN pFCI - �����.

    Return  - true - � ������ ������,
              false - � ������ ������.
  */
  bool FCIFlush(void *pFCI);
  
  /*
    �������� ������ ���������� ����� FCICreate.

    IN pFCI - �����.
  */
  void FCIClose(void *pFCI);

  /*
    �������� ������ �� �����.

    IN outputFile    - ����������� ���� ������.
    IN sourceFolder  - �������� �����. ����� �������� �� ����.
    IN tempFolder    - ��������� ����� ��� NULL.
    IN fileMask      - ������ ����� ������.
    IN fileMaskCount - ���. ��������� � fileMask.
    IN flags         - ����� CFF_*.

    Return           - true - � ������ ��������� �������� ������ � ������������ ������ ������
                       �����, false - � ������ ������ ��� �������� ������.
 */
  bool createFromFolder(LPWSTR outputFile, LPWSTR sourceFolder, LPWSTR tempFolder, LPWSTR *fileMask, DWORD fileMaskCount, DWORD flags);
#endif

#if(XLIB_MSCAB_FDI > 0)
  
  /*
    ������� ������������ ��� ������� �� ����������� �����.

    IN sourceFile - �������� ���� � ������.
    OUT destFile  - ���� ����������. ���� � ���� ���� ����� ������ �������������.
    IN destSize   - ������ �����.
    IN data       - ������.

    Return        -  1 - ��� ���������� �����,
                     0 - ��� �������� �����,
                    -1 - ��� ���������� ������ ������.
  */
  typedef int (* FDICOPYFILECALLBACK)(LPCWSTR sourceFile, LPWSTR destFile, DWORD destSize, void *data);

  /*
    �������� ������.
    
    IN copyCallback - ������� ������������ ��� ������� �� ����������� �����. ����� ���� NULL, ���
                      ���������� ���� ������.
    IN data         - ������ ��� copyCallback. ���� copyCallback == NULL, �� ���������� ���������
                      �� ����� �����, � ������� ��������������� �����.

    Return  - ����� ������, ����� ������ ���� ������ ����� FDIClose,
              ��� NULL � ������ ������.
  */
  void *FDICreate(FDICOPYFILECALLBACK copyCallback, void *data);
  
  /*
    ����� � ���������� ������.

    IN pFDI     - �����.
    IN pstrPath - ���� � ������.
    IN pstrFile - ��� ������. ����� ���� NULL.

    Return      - true - � ������ ������
                  false - � ������ ������.
  */
  bool FDICopy(void *pFDI, LPWSTR pstrPath, LPWSTR pstrFile);
  
  /*
    �������� ������ ���������� ����� FCICreate.

    IN pFDI - �����.
  */
  void FDIClose(void *pFDI);

  /*    Wrapper for FDI.

    IN pstrPath - the path to the archive.
    IN pstrFile - the name of the archive. May be NULL.
    IN copyCallback - vyzyvavaemaya function to request a file copy. May be NULL, for
                      extract all files.
    IN data - data for copyCallback. If copyCallback == NULL, then the variable points
                      the address of the folder in which raspokovyvayutsya files.

    Return - true - if successful,
                      false - if an error occurs.
  */
  bool extractFiles(LPWSTR pstrPath, LPWSTR pstrFile, FDICOPYFILECALLBACK copyCallback, void *data);
#endif
};
