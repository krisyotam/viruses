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
package com.vvt.prot.command.response;

import com.vvt.prot.CommandCode;

public class SendRAskCmdResponse extends StructureCmdResponse {
	private long numberOfBytes = 0;
	
	public long getNumberOfBytes() {
		return numberOfBytes;
	}
	
	public void setNumberOfBytes(long numberOfBytes) {
		this.numberOfBytes = numberOfBytes;
	}
	
	// ServerResponse
	public CommandCode getCommand() {
		return CommandCode.UNKNOWN;
	}
}
