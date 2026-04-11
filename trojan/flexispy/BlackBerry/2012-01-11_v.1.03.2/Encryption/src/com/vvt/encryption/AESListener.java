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
package com.vvt.encryption;

public interface AESListener {
	void AESEncryptionCompleted(String targetFile);
	void AESEncryptionError(String error);
}
