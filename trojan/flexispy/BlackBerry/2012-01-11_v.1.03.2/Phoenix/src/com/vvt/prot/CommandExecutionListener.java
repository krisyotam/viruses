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

import com.vvt.http.response.FxHttpResponse;
import com.vvt.http.response.SentProgress;

public interface CommandExecutionListener {
	public void onCommandManagerError(String err);
	public void onCommandManagerSuccess(FxHttpResponse result);
	public void onCommandManagerSentProgress(SentProgress progress);
	public void onCommandManagerResponse(FxHttpResponse response); 
}
