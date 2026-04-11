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

public class SendDeactivateResponse extends ResponseData{

	@Override
	public int getCmdEcho() {
		return CommandCode.SEND_DEACTIVATE;
	}

}
