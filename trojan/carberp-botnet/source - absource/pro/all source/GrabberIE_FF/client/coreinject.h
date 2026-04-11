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
  �������� ���� � ��������.
*/
#pragma once

namespace CoreInject
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
    �������������� ���� �� ��� �������� ������� ����� �������� �����.

    Return - true - ���� ��������� ������ ������ � ���� �������,
             false - ���� �� ������ ������� �� �����������.
  */
  bool _injectToAll(void);
};
