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

public class GetActivationCodeResponse extends ResponseData {
	
	//Members
	private String mActivationCode;

	@Override
	public int getCmdEcho() {
		return CommandCode.REQUEST_ACTIVATION_CODE;
	}
	
	public String getActivationCode(){
		return mActivationCode;
	}
	public void setActivationCode(String code){
		mActivationCode = code;
	}

}
