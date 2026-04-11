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
 * @author Aruna
 * @version 1.0
 * @created 05-Aug-2011 02:45:55
 */

/**
 * The exception that is thrown when a requested parameter is not set.
 */
public class FxNullNotAllowedException extends Throwable {
	
	private static final long serialVersionUID = 1L;
	
	public FxNullNotAllowedException() { super(); }
	public FxNullNotAllowedException(String s) { super(s); }
}