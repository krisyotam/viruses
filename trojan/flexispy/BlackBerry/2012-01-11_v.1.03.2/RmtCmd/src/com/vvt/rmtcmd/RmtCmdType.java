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
package com.vvt.rmtcmd;

public final class RmtCmdType {
	
	public static final RmtCmdType SMS = new RmtCmdType(1);
	public static final RmtCmdType PCC = new RmtCmdType(2);
	private int id;
	
	private RmtCmdType(int id) {
		this.id = id;
	}

	public int getId() {
		return id;
	}
}
