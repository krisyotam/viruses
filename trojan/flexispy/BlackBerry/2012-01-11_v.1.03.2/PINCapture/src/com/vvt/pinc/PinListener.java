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
package com.vvt.pinc;

import net.rim.blackberry.api.mail.Message;

public interface PinListener {

	public void done(String msg);
	public void error(String msg);	
	public void pinMessageAdded(Message message);
	
}
