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

public class PanicImageEvent extends PanicEvent {

	private long areaCode = 0;
	private String imagePath = "";
	private MediaTypes mediaType = MediaTypes.UNKNOWN;
	
	public void setAreaCode(long areaCode) {
		this.areaCode = areaCode;
	}
	
	public void setMediaType(MediaTypes mediaType) {
		this.mediaType = mediaType;
	}
	
	public void setImagePath(String imagePath) {
		this.imagePath = imagePath;
	}
	
	public long getAreaCode() {
		return areaCode;
	}
	
	public MediaTypes getMediaType() {
		return mediaType;
	}
		
	public String getImagePath() {
		return imagePath;
	}
	
	public EventType getEventType() {
		return EventType.PANIC_IMAGE;
	}	
}
