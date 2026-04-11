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
package com.vvt.remotecommandmanager.exceptions;


public abstract class RemoteCommandException extends Exception {

	private static final long serialVersionUID = 1L;

	public abstract int getErrorCode();

}
