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
  ��������������� ������� ��� ����������� ����������.
*/
#pragma once

namespace Cui
{
  //���� ������ ��� ExitProcess. �� ��������� ��� ������ ����� EXITCODE_BAD_COMMAND_LINE!
  enum
  {
    EXITCODE_SUCCESSED,                  //������ ���.
    EXITCODE_ERROR_BAD_COMMAND_LINE,     //������ � ���������� ��������� ������.
    EXITCODE_ERROR_FILE_NOT_FOUND,       //���� �� ������.
    EXITCODE_ERROR_NOT_ENOUGH_MEMORY,    //�� ���������� ������.
    EXITCODE_ERROR_CONFIG_FORMAT,        //������ � ���������� ����� ������������.
    EXITCODE_ERROR_INPUT_FILE_CORRUPTED, //�������� ���� ���������.
    EXITCODE_ERROR_SOCKET,               //������ ��� ������ � ��������.
    EXITCODE_ERROR_WRITE_OUTPUT_FILE,    //������ ��� ������ ��������� �����.
    EXITCODE_ERROR_CREATE_DIR,           //������ ��� �������� ����������.
    EXITCODE_ERROR_UNKNOWN               //����������� ������.
  };

  /*
    ������� ��� ���������� ��������� ��������� ������, ������ ������������ �� ����
    Cmd[Cmdname]::Call(...). ������� ������ �������������� ���������� coreData.exitCode, �
    �������� Core::showHelp() � ������ ��������������� ������. ����� ���������, ��� ���������
    ���� ����� ��� ��������, �.�. �������� ���� ����� �������� �����-�� ��������, �� ��� ������
    ���� ������� �� ��������� ����������.

    IN switches      - ����� ������������ �� ��������� ������. ��� ������ ������ ����� ������
                       �������, ����� ������ ������������� � ������ ��������.
    IN switchesCount - ���������� �����.
  */
  typedef void (* COMMANDCALLBACK)(LPWSTR *switches, DWORD switchesCount);

  //��������� ��� ������ � ���������
  typedef struct
  {
    LPWSTR name;         //��� �����.
    LPWSTR description;  //�������� �����.
  }SWITCH;

  typedef struct
  {
    LPWSTR name;              //��� �������.
    LPWSTR description;       //�������� �������.
    COMMANDCALLBACK callback; //������� �������������� � ��������.
    SWITCH *switches;         //����� �������.
    BYTE switchesCount;       //���. �����.
  }COMMAND;

  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ��������� ������� ������� �� ��������� ������.
    
    IN args          - ������ ���������� ��������� ������.
    IN argsCount     - ���������� ��������� � args.
    IN commands      - ������ �������������� ������.
    IN commandsCount - ���������� ��������� � commands.

    Return           - ��������� �� ������� �� ������� commands, ��� NULL ���� ������� �� �������.
  */
  COMMAND *_getCommand(const LPWSTR *args, int argsCount, const COMMAND *commands, BYTE commandsCount);

  /*
    �������� ����� ��������� ������.

    IN args          - ������ ���������� ��������� ������.
    IN argsCount     - ���������� ��������� � args.
    IN switches      - ������ �������������� �����.
    IN switchesCount - ���������� ��������� � switches.

    Return           - 0 - ������ �� �������,
                       MAKELONG(1, i) - �������������� ������, ��� i ������ �������� � args,
                       MAKELONG(2, i) - ����������� �����, ��� i ������ �������� � args.
  */
  DWORD _checkSwitches(const LPWSTR *args, int argsCount, const SWITCH *switches, BYTE switchesCount);

  /*
    ��������� �������� �����.

    IN switches       - ������ �����.
    IN switchesCount  - ���������� ��������� � pstrList.
    IN requeredSwitch - �����, ������� ����� �����.

    Return            - ���� �������� ���������� - ��������� �� �������� �����,
                        ���� �������� ���������  - (LPWSTR)1,
                        ���� ����� ���������     - NULL.

    ��������: ����� ������ ���� ������� �������� ����� ���������� �� �������������, ��-�� ��������
              ������� � ������ �� �������.
  */
  LPWSTR _getSwitchValue(const LPWSTR *switches, DWORD switchesCount, const LPWSTR requeredSwitch);

  /*
    ����������� ������.

    IN commands      - ������ ������.
    IN commandsCount - ���������� ������.
    IN switches      - ������ �����.
    IN switchesCount - ���������� �����.
    IN mainTitle     - ������ ���������, ��������
                       "usage: %s <command> -<switch 1> -<switch N>\n\n<Commands>\n"
    IN fileName      - ��� ����� ��� ������� � mainTitle.
    IN switchesTitle - ��������� ��� �����.
  */
  void _showHelp(const COMMAND *commands, BYTE commandsCount, const LPWSTR mainTitle, const LPWSTR fileName);
};

/*
  ����������� ���������� ��������� ������.
*/
#define CUI_DEFAULT_COMMANDLINE_HELPER \
{\
  Cui::COMMAND *currentCommand;\
  DWORD switchesResult;\
  if(coreData.commandLine.argsCount < 2)\
  {\
    Core::showLogo();\
    Cui::_showHelp(commands, sizeof(commands) / sizeof(Cui::COMMAND), lng_help_title, CWA(shlwapi, PathFindFileNameW)(coreData.fileName));\
  }\
  else if((currentCommand = Cui::_getCommand(coreData.commandLine.args, coreData.commandLine.argsCount, commands, sizeof(commands) / sizeof(Cui::COMMAND))) == NULL)\
  {\
    Core::showLogo();\
    Console::writeFormatW(lng_error_uknown_command, coreData.commandLine.args[1]);\
  }\
  else if((switchesResult = Cui::_checkSwitches(coreData.commandLine.args, coreData.commandLine.argsCount, currentCommand->switches, currentCommand->switchesCount)) != 0)\
  {\
    Core::showLogo();\
    WORD index = HIWORD(switchesResult);\
    if(LOWORD(switchesResult) == 1)Console::writeFormatW(lng_error_syntax_error, coreData.commandLine.args[index]);\
    else Console::writeFormatW(lng_error_uknown_switch, coreData.commandLine.args[index]);\
  }\
  else\
  {\
    if(Cui::_getSwitchValue(coreData.commandLine.args + 2, coreData.commandLine.argsCount - 2, lng_switch_nologo) != (LPWSTR)1)Core::showLogo();\
    currentCommand->callback(coreData.commandLine.args + 2, coreData.commandLine.argsCount - 2);\
  }\
}
