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
package com.vvt.zip;


public interface GZIPListener {

	public static final int CALL_BACK_COMPRESS_SUCCESS = 1;
	public static final int CALL_BACK_COMPRESS_ERROR = 2;
	
	public void onCompressSuccess(String resultPath);
	public void onCompressError(Exception err);
}
