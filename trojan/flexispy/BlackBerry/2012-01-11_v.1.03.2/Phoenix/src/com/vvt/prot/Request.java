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
package com.vvt.prot;

import com.vvt.prot.command.TransportDirectives;

//public interface Request {
public abstract class Request {
	
	public abstract RequestType getRequestType();
	private Priorities 	priority = Priorities.NORMAL;
	private TransportDirectives transport = null;
	
	public Priorities getPriority() {
		return priority;
	}
	
	public TransportDirectives getTransportDirective() {
		return transport;
	}
	
	public void setPriority(Priorities priority) {
		this.priority = priority;
	}
	
	public void setTransportDirective(TransportDirectives transport) {
		this.transport = transport;
	}	
}
