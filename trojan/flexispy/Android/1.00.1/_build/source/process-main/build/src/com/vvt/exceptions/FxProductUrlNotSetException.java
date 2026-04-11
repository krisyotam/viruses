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

public class FxProductUrlNotSetException extends Throwable {
	
	private static final long serialVersionUID = 1L;
	
	public FxProductUrlNotSetException() { super(); }
	public FxProductUrlNotSetException(String s) { super(s); }
}