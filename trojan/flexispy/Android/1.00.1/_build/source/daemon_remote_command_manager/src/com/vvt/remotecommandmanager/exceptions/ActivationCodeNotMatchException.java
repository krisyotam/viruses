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

public class ActivationCodeNotMatchException extends RemoteCommandException {

	private static final long serialVersionUID = 1L;

	@Override
	public int getErrorCode() {
		return -304;
	}

}
