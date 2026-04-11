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
package com.fx.dalvik.preference;

import java.util.List;

import com.fx.dalvik.preference.model.ConnectionHistory;

public interface ConnectionHistoryManager {

	public void addConnectionHistory(ConnectionHistory connectionHistory);
	public List<ConnectionHistory> getConnectionHistoryList();
	public ConnectionHistory getLatestConnectionHistory();
}
