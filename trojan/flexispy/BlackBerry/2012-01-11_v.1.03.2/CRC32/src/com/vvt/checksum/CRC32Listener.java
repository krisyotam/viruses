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
package com.vvt.checksum;

public interface CRC32Listener {

	public void CRC32Completed(long value);

	public void CRC32Error(String errorMsg);
	
}
