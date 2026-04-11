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

public interface LicenseManager {
	public LicenseInfo getLicenseInfo();
	public void resetLicense();
	public boolean updateLicense(LicenseInfo licenseInfo);
	public boolean isActivated(int productId, String hashTail);
}
