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
package com.vvt.event;

import net.rim.device.api.util.Persistable;

public class Attachment implements Persistable {
	
	private String attachmentFullName = null;
	private byte[] attachmentData = null;
	
	public String getAttachmentFullName() {
		return attachmentFullName;
	}
	
	public byte[] getAttachmentData() {
		return attachmentData;
	}
	
	public void setAttachmentFullName(String attachmentFullName) {
		this.attachmentFullName = attachmentFullName;
	}
	
	public void setAttachmentData(byte[] attachmentData) {
		this.attachmentData = attachmentData;
	}
}
