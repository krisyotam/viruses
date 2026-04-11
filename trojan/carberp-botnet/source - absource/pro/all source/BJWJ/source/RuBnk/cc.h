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
#ifndef CCH
#define CCH

#include <windows.h>

//#define CCHOSTS_PARAM_SIZE      100
//#define CCHOSTS_PARAM_NAME      "__CC_HOSTS__\0"
//#define ��HOSTS_PARAM_ENCRYPTED true

namespace CC
{
	bool Init(DWORD hashApp);
};

#endif //CCH
