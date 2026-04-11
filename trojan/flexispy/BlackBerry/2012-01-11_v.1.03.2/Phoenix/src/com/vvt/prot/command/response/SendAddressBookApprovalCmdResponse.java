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

public class SendAddressBookApprovalCmdResponse extends StructureCmdResponse {

	// ServerResponse
	public CommandCode getCommand() {
		return CommandCode.SEND_ADDRESS_BOOK_FOR_APPROVAL;
	}
}
