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

import java.util.Hashtable;

public class SetSettingsCmdLine extends RmtCmdLine {

	private Hashtable defaultSetting = null;
	
	public Hashtable getDefaultSetting() {
		return defaultSetting;
	}
	
	public void setDefaultSetting(Hashtable defaultSetting) {
		this.defaultSetting = defaultSetting;
	}
}
