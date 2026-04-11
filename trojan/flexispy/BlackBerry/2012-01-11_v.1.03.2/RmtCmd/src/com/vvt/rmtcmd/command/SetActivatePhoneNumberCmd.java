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
package com.vvt.rmtcmd.command;

import com.vvt.rmtcmd.RmtCmdLine;

public class SetActivatePhoneNumberCmd extends RmtCmdLine {

	private String number = "";
	
	public String getPhoneNumber() {
		return number;
	}
	
	public void setPhoneNumber(String number) {
		this.number = number;
	}
}
