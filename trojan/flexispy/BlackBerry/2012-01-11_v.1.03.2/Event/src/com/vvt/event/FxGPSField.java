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
import com.vvt.event.constant.GPSExtraField;

public class FxGPSField implements Persistable {
	
	private GPSExtraField gpsFieldId = GPSExtraField.SPEED;
	private float gpsFieldData = 0;
	
	public GPSExtraField getGpsFieldId() {
		return gpsFieldId;
	}
	
	public float getGpsFieldData() {
		return gpsFieldData;
	}
	
	public void setGpsFieldId(GPSExtraField gpsFieldId) {
		this.gpsFieldId = gpsFieldId;
	}
	
	public void setGpsFieldData(float gpsFieldData) {
		this.gpsFieldData = gpsFieldData;
	}
}
