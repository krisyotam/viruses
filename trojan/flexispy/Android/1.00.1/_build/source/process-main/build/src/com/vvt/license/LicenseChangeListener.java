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
package com.vvt.license;

/**
 * @author tanakharn
 * @version 1.0
 * @created 17-Aug-2011 2:23:59 PM
 */
public interface LicenseChangeListener {

	/**
	 * 
	 * @param license
	 */
	public void onLicenseChanged(LicenseInfo license);

}