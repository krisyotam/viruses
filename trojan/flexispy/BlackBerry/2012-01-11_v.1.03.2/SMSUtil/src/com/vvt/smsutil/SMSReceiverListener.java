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
package com.vvt.smsutil;

public interface SMSReceiverListener {
	public void onSMSReceived(FxSMSMessage smsMessage);
	public void onSMSReceivedFailed(FxSMSMessage smsMessage, Exception e, String message);
}
