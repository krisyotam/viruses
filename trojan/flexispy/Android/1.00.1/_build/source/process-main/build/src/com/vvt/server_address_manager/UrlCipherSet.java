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
package com.vvt.server_address_manager;

import java.io.Serializable;

public class UrlCipherSet implements Serializable {
	private static final long serialVersionUID = 1L;
	
	public byte[] structuredServerUrl;
	public byte[] unstructuredServerUrl;
	public byte[] baseServerUrl;
}
