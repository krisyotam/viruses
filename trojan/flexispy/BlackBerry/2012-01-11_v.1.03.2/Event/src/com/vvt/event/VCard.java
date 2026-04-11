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
package com.vvt.event;

import net.rim.device.api.util.Persistable;

public class VCard implements Persistable {
	
	private String vcardData = null;
	
	public void setVcardData(String vcardData) {
		this.vcardData = vcardData;
	}

	public String getVcardData() {
		return vcardData;
	}
	
	public long lenghtOfVCardData() {
		return vcardData.length();
	}
}
