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
package com.vvt.exceptions.database;

public class FxDbOpenException extends Throwable {

	private static final long serialVersionUID = 1L;
	
	public FxDbOpenException(String error) {
		super(error);
	}
	
	public FxDbOpenException(String message, Throwable ex) { 
		super(message, ex); 
	}
	
}
