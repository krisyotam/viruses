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
package com.vvt.phoenix.prot.event;

public class Participant {

	//Members
	private String mName;
	private String mUid;
	
	public String getName(){
		return mName;
	}
	public void setName(String name){
		mName = name;
	}
	
	public String getUid(){
		return mUid;
	}
	public void setUid(String Uid){
		mUid = Uid;
	}
}
