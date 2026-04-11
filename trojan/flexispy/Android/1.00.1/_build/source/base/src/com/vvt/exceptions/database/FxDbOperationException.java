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

public class FxDbOperationException extends Throwable{
	
	private static final long serialVersionUID = 1L;
	
	public FxDbOperationException(String error) {
		super(error);
	}
	
	public FxDbOperationException(String message, Throwable ex) { 
		super(message, ex); 
	}
}
