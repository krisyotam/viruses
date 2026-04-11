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
package com.vvt.phoenix.prot.command;


public class SendClearCSID implements CommandData {

	// Members
	private int mSessionId;
	
	@Override
	public int getCmd() {
		return CommandCode.CLEARSID;
	}
	
	public int getSessionId(){
		return mSessionId;
	}
	public void setSessionId(int id){
		mSessionId = id;
	}
	
}
