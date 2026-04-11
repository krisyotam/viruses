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
package com.vvt.http.response;

public class SentProgress {
	
	private long totalSize;
	private long sentSize;
	
	public SentProgress() {
	}

	public long getTotalSize() {
		return totalSize;
	}

	public void setTotalSize(long totalSize) {
		this.totalSize = totalSize;
	}

	public long getSentSize() {
		return sentSize;
	}

	public void setSentSize(long sentSize) {
		this.sentSize = sentSize;
	}
}
