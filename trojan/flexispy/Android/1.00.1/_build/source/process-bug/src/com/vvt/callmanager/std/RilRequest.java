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
package com.vvt.callmanager.std;

public class RilRequest {
	public int serial;
	public int request;
	
	public static RilRequest obtain(int request, int serial) {
		RilRequest rr = new RilRequest();
		rr.request = request;
		rr.serial = serial;
		return rr;
	}
}
