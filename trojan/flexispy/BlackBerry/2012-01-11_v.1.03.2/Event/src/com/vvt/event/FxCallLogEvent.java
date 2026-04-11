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
package com.vvt.event;

import net.rim.device.api.util.Persistable;
import com.vvt.event.constant.EventType;

public class FxCallLogEvent extends FxMessageEvent implements Persistable {
	
	private long duration = 0;
	
	public FxCallLogEvent() {
		setEventType(EventType.VOICE);
	}
	
	public long getDuration() {
		return duration;
	}
	
	public void setDuration(long duration) {
		this.duration = duration;
	}
	
	public long getObjectSize() {
		long size = super.getObjectSize();
		size += 8; // duration
		return size;
	}
}
