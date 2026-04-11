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
//---------------------------------------------------------------------------
//  ��������� ������� ��� ��������� ���� �������� ����������
//---------------------------------------------------------------------------

#ifndef IECacheUtilsH
#define IECacheUtilsH
//---------------------------------------------------------------------------

#include "Requests.h"

namespace IECache
{
	bool Initialize(PRequestList Requests);

    void AddMask(PCHAR Mask);
}

//---------------------------------------------------------------------------
#endif
