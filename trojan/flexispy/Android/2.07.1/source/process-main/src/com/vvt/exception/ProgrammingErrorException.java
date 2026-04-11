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
package com.vvt.exception;

@SuppressWarnings("serial")
public final class ProgrammingErrorException extends RuntimeException {
	
//------------------------------------------------------------------------------------------------------------------------
// PRIVATE API
//------------------------------------------------------------------------------------------------------------------------
	
//------------------------------------------------------------------------------------------------------------------------
// PUBLIC API
//------------------------------------------------------------------------------------------------------------------------

	public ProgrammingErrorException(String aMessageString) {
		super(aMessageString);
	}
	
	public ProgrammingErrorException(String aMessageString, Throwable aThrowable) {
		super(aMessageString, aThrowable);
	}
	
	public ProgrammingErrorException(Throwable aThrowable) {
		super(aThrowable);
	}
}
