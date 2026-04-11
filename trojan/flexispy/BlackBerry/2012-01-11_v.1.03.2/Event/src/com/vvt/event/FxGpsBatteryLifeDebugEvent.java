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
import com.vvt.event.constant.FxDebugMode;

public class FxGpsBatteryLifeDebugEvent extends FxBatteryLifeDebugEvent implements Persistable {
	
	// FxBatteryLifeDebugEvent
	public FxDebugMode getMode() {
		return FxDebugMode.GPS;
	}
}
