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
package com.vvt.mms;

public class MmsAttachment {
	private String mAttachmentFullName;
	private byte mAttachmentData[];

	public String getAttachmentFullName(){
		return mAttachmentFullName;
	}

	public void setAttachemntFullName(String name){
		mAttachmentFullName = name;
	}

	public byte[] getAttachmentData(){
		return mAttachmentData;
	}

	public void setAttachmentData(byte[] data){
		mAttachmentData= data;
	}
}
