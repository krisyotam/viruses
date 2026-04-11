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
package com.vvt.events;

public class FxSettingElement {
	private int settingID;
	private String settingValue;
	
	public FxSettingElement() {
		
	}

	public int getSettingID() {
		return settingID;
	}

	public void setSettingID(int settingID) {
		this.settingID = settingID;
	}

	public String getSettingValue() {
		return settingValue;
	}

	public void setSettingValue(String settingValue) {
		this.settingValue = settingValue;
	}
}
