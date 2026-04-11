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
package com.vvt.prot.event;

public class Thumbnail {
	private byte[] imageData;
	
	public void setImageData(byte[] imageData) {
		this.imageData = imageData;
	}
	
	public byte[] getImageData() {
		return imageData;
	}
}
