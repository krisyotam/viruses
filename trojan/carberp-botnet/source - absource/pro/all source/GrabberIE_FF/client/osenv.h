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
  ������ OC.
*/
#pragma once

namespace OsEnv
{
  //������ OS.
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
  
  //������� ���������� �� OC.
# pragma pack(push, 1)
  typedef struct
  {
    BYTE version;      //VERSION_*.
    BYTE sp;           //Service Pack.
    WORD build;        //����� �����.
    WORD architecture; //����������� ����������.
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

    Return - VERSION_*.
  */
  DWORD _getVersion(void);

  /*
    ��������� ������� ������ Windows.

    OUT oi - ������ Windows.
  */
  void _getVersionEx(OSINFO *oi);

  /*
    ��������� ���������� ������� ������������ �� SID.

    IN sid     - SID.
    OUT buffer - ����� ��� ����, ������ ���� �� ����� MAX_PATH.

    Return     - true - ���� ������ �������,
                 false - ���� �� �������.
  */
  bool _getUserProfileDirectoryhBySid(PSID sid, LPWSTR buffer);
};
