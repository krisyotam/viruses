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
package com.vvt.phoenix.util.zip;


public interface GZIPListener {
	//public void onCompressSuccess(FileInputStream result);
	public void onCompressSuccess(String resultPath);
	public void onCompressError(Exception err);
}
