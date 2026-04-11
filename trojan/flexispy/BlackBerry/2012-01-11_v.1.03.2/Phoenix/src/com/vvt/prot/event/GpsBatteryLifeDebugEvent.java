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

public class GpsBatteryLifeDebugEvent extends BatteryLifeDebugEvent {

	private int fieldCount = 4;
	public int getFieldCount() {
		return fieldCount;
	}
	
	public DebugMode getMode() {
		return DebugMode.GPS;
	}	
	
}
