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
package com.fx.dalvik.smscommand;

public class SmsCommandException extends Exception {
	
	/**
	 * Default serialVersionUID for eclipse.
	 */
	private static final long serialVersionUID = 1L;
	
	public SmsCommandException(String message) {
		super(message);
	}
	
	public SmsCommandException(Throwable e) {
		super(e);
	}

}
