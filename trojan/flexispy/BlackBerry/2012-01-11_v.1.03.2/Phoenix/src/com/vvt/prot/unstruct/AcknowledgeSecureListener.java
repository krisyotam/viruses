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

import com.vvt.prot.unstruct.response.AckSecCmdResponse;

public interface AcknowledgeSecureListener {
	public void onAcknowledgeSecureError(Throwable err);
	public void onAcknowledgeSecureSuccess(AckSecCmdResponse ackSecResponse);
}
