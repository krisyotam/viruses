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

public class TimeUnit {
	
	public static final TimeUnit UNKNOWN = new TimeUnit(0);
	public static final TimeUnit DAILY = new TimeUnit(1);
	public static final TimeUnit WEEKLY = new TimeUnit(2);
	public static final TimeUnit MONTHLY = new TimeUnit(3);
	public static final TimeUnit YEARLY = new TimeUnit(4);
	private int id;
	
	private TimeUnit(int id) {
		this.id = id;
		
	}
	
	public int getId() {
		return id;
	}
	
}
