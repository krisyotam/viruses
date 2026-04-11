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
package com.vvt.util.crypto;


public interface AESEncryptListener extends AESCipherListener {

	//public void AESEncryptSuccess();
	//public void onAESEncryptSuccess(FileInputStream result);
	public void onAESEncryptSuccess(String resultPath);
	public void onAESEncryptError(Exception err);
}
