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
package com.vvt.bbm;

public interface BBMConversationListener {

	public void BBMConversation(Conversation conversation);	
	public void setupFailed(String errorMsg);
	public void setupCompleted();	
	public void stopFailed(String errorMsg);	
	public void stopCompleted();

}