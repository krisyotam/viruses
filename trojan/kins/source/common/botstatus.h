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
  ��������� ��� ��������� ���������� � ������������� ����.
*/
#pragma once

#include "malwaretools.h"

namespace BotStatus
{
  //������ �� �������� ����. ������ 1, ������� � 1.4.0.0.
  typedef BOOL (WINAPI *callbackStopServices)(void *reserved);
  typedef BOOL (WINAPI *callbackUninstall)(void *reserved);

# pragma pack(push, 1)
  typedef struct
  {
    DWORD structSize;                   //������ ���������.
    DWORD flags;                        //�� ������������.
    DWORD version;                      //������ ����.
    WCHAR botnet[BOTNET_MAX_CHARS + 1]; //��� �������.
    DWORD storageArrayKey;              //XOR ���� ��� �������� �������.
    
    callbackStopServices stopServices;  //������� ��� ��������� �������� ����.
    callbackUninstall uninstall;        //������� ��� �������� ����.

    //��������.
    DWORD reserved;       //�� ������������.
    WCHAR compId[60];     //CompID.
    GUID guid;            //�������� GUID ���������� � ��.
    Crypt::RC4KEY rc4Key; //���� ���������� ��� ��.

    //������ � �����.
    struct
    {
      WCHAR coreFile[MAX_PATH];         //������������� ���� �������.
      WCHAR reportFile[MAX_PATH];       //������������� ���� ��� ��������� ������.
      WCHAR regKey[MAX_PATH];           //������������� ���� � �������.
      WCHAR regDynamicConfig[MAX_PATH]; //�������� � ������� ��� �������� ������������.
      WCHAR regLocalConfig[MAX_PATH];   //�������� � ������� ��� �������� ��������� ������������.
      WCHAR regLocalSettings[MAX_PATH]; //�������� � ������� ��� �������� ��������.
    }userPaths;          
  }VER1;
# pragma pack(pop)
};
