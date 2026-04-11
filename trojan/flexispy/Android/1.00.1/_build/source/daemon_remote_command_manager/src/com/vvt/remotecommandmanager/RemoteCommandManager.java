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
package com.vvt.remotecommandmanager;

import java.util.List;

import com.vvt.phoenix.prot.command.response.PCC;


public interface RemoteCommandManager {

	public void processPccCommand(List<PCC> pccCommand);
	public void processSmsCommand(SmsCommand smsCommand);
	
}
