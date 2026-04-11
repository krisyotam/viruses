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

public class ConnectionHistoryManagerFactory {

	public static ConnectionHistoryManager getConnectionHistoryManager() {
		return ConnectionHistoryManagerImpl.getInstance();
	}
}
