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

public class GetActivationCode implements CommandData{
	

	@Override
	public int getCmd() {
		return CommandCode.REQUEST_ACTIVATION_CODE;
	}
	
}
