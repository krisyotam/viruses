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
package com.vvt.gpsc;

public interface GPSPositionListener {
	
	public void locationUpdate(double latitude, double longitude);
	
	public void locationError();
	
}
