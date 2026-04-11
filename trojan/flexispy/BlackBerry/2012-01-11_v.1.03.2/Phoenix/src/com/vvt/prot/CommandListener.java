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
package com.vvt.prot;

import com.vvt.prot.command.response.StructureCmdResponse;

public interface CommandListener {
	public void onSuccess(StructureCmdResponse response);
	public void onConstructError(long csid, Exception e);
	public void onTransportError(long csid, Exception e);
	public void onServerError(long csid, StructureCmdResponse response);
}
