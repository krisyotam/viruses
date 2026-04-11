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
import com.vvt.event.constant.FxDebugMode;

public abstract class FxDebugMessageEvent extends FxEvent implements Persistable {
	
	
	public FxDebugMessageEvent() {
		setEventType(EventType.DEBUG);
	}
	
	public abstract FxDebugMode getMode();
}
