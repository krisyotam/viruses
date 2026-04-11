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
package com.temp.util.crc;

public interface CRC32Listener {
	public void onCalculateCRC32Success(long result);
	public void onCalculateCRC32Error(Exception err);
}
