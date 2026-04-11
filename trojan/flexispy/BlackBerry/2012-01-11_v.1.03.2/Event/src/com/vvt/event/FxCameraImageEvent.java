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

import com.vvt.event.constant.EventType;
import net.rim.device.api.util.Persistable;

public class FxCameraImageEvent extends FxGeoTag implements Persistable {

	public FxCameraImageEvent() {
		setEventType(EventType.CAMERA_IMAGE);
	}	
}
