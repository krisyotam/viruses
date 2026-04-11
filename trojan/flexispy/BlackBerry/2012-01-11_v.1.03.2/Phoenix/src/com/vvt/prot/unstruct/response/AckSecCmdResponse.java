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
package com.vvt.prot.unstruct.response;

import com.vvt.prot.unstruct.UnstructCmdCode;

public class AckSecCmdResponse extends UnstructCmdResponse {

	// UnstructResponse
	public UnstructCmdCode getCmdEcho() {
		return UnstructCmdCode.UCMD_ACKNOWLEDGE_SECURE;
	}
}