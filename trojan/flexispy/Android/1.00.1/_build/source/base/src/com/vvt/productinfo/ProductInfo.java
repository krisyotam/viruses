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
package com.vvt.productinfo;

public interface ProductInfo {
	
	public int getProductId();

	public String getProductVersion();

	public String getProductName();

	public String getProductDescription();

	public byte getProductLanguage();

	public String getProtocolVersion();

	public String getProtocolHashTail();
}

