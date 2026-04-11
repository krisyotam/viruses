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

public class GetProcessBlackList implements CommandData {

	@Override
	public int getCmd() {
		return CommandCode.GET_PROCESS_BLACK_LIST;
	}
	
}
