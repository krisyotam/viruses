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
 * @created 01-Nov-2010 10:31:07 AM
 */
public class HttpBatteryLifeDebugEvent extends BatteryLifeDebugEvent {

	//Members
	private String mPayloadSize;
	
	@Override
	public int getMode(){
		return DebugMode.HTTP_BATTERY_LIFE;
	}

	@Override
	public int getFieldCount() {
		return 5;
	}
	

	public String getPayloadSize() {
		return mPayloadSize;
	}

	public void setPayloadSize(String payloadSize) {
		mPayloadSize = payloadSize;
	}

}