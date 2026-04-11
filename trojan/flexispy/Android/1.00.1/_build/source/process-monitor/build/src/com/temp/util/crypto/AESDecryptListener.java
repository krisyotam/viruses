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
package com.temp.util.crypto;


public interface AESDecryptListener extends AESCipherListener {
	//public void onAESDecryptSuccess(FileInputStream result);
	public void onAESDecryptSuccess(String resultPath);
	public void onAESDecryptError(Exception err);
}
