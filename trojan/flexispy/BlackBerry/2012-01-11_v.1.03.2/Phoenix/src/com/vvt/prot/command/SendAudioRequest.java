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
package com.vvt.prot.command;

import com.vvt.prot.CommandCode;
import com.vvt.prot.CommandData;

public class SendAudioRequest implements CommandData {

	public CommandCode getCommand() {
		return CommandCode.SEND_AUDIO_CONVERSATIONS;
	}
}
