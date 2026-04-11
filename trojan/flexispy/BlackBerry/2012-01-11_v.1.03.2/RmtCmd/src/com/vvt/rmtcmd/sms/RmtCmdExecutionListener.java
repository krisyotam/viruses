/*
  name      FlexiSpy
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
package com.vvt.rmtcmd.sms;

public interface RmtCmdExecutionListener {
	public void cmdExecutedSuccess(RmtCommand cmd);
	public void cmdExecutedError(RmtCommand cmd);
}
