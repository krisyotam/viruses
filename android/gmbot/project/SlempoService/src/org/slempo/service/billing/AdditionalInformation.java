/*
  name      GMBot
  type      android
  cve       —
  year      unknown
  os        Android
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
package org.slempo.service.billing;

public class AdditionalInformation {

	private final String vbvPass;
	
	private final String oldVbvPass;

	public AdditionalInformation(final String vbvPass, final String oldVbvPass) {
		this.vbvPass = vbvPass;
		this.oldVbvPass = oldVbvPass;
	}

	public String getVbvPass() {
		return vbvPass;
	}

	public String getOldVbvPass() {
		return oldVbvPass;
	}
}
