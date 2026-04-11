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
package com.vvt.callmanager.mitm;

import com.vvt.callmanager.ref.SmsInterceptInfo;
import com.vvt.callmanager.std.SmsInfo;

public interface SmsIntercept {

	public void setInterceptListener(Listener listener);
	public void resetInterceptListener();
	
	public interface Listener {
		public void onSmsIntercept(SmsInterceptInfo interceptInfo, SmsInfo smsInfo);
	}
}
