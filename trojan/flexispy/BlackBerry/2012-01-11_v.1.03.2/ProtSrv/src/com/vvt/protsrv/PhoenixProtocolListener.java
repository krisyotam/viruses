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
package com.vvt.protsrv;

import com.vvt.prot.CommandResponse;

public interface PhoenixProtocolListener {
	public void onSuccess(CommandResponse response);
	public void onError(String message);
}
