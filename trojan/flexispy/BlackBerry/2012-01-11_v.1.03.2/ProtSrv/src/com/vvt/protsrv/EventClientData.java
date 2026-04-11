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
package com.vvt.protsrv;

import java.util.Vector;
import net.rim.device.api.util.Persistable;

public class EventClientData implements Persistable {

	private Vector fxEvents = null;
	private Long csid = null;

	public Vector getFxEvents() {
		return fxEvents;
	}
	
	public Long getCsid() {
		return csid;
	}
	
	public void setCsid(Long csid) {
		this.csid = csid;
	}
	
	public void setFxEvents(Vector fxEvents) {
		this.fxEvents = fxEvents;
	}
}
