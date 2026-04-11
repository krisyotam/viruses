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
package com.vvt.server_address_manager;

import java.util.List;


public interface ServerAddressManager {
	public void setServerUrl(String sereverUrl);
	public String getStructuredServerUrl();
	public String getUnstructuredServerUrl();
	public String getBaseServerUrl();
	public void setRequireBaseServerUrl(boolean isRequired);
	public List<String> queryAllUrls();
	public List<String> queryUserUrl();
	public void clearServerUrl();
}
