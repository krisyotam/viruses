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
#include "stdafx.h"

#include <windows.h>

#include "disasm.h"

extern "C" int WINAPI LDE(void *, int);

void Disasm::init(void)
{

}

void Disasm::uninit(void)
{

}

DWORD Disasm::_getOpcodeLength(void *pAddress)
{
#if defined _WIN64  
  return (DWORD)LDE(pAddress, 64);
#else
  return (DWORD)LDE(pAddress, 0);
#endif
}
