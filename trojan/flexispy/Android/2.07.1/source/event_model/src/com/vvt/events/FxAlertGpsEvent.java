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
package com.vvt.events;

import com.vvt.base.FxEventType;

public class FxAlertGpsEvent extends FxLocationBase{

	
	@Override
	public FxEventType getEventType(){
		return FxEventType.ALERT_GPS;
	}
}
