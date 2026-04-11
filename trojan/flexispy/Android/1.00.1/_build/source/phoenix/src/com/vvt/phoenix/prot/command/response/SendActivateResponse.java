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
package com.vvt.phoenix.prot.command.response;

import com.vvt.phoenix.prot.command.CommandCode;

public class SendActivateResponse extends ResponseData {
	
	//Members
	private byte[] mMd5;
	private int mConfigId;

	@Override
	public int getCmdEcho() {
		return CommandCode.SEND_ACTIVATE;
	}
	
	public byte[] getMd5(){
		return mMd5;
	}
	public void setMd5(byte[] md5){
		mMd5 = md5;
	}
	
	public int getConfigId(){
		return mConfigId;
	}
	public void setConfigId(int id){
		mConfigId = id;
	}

}
