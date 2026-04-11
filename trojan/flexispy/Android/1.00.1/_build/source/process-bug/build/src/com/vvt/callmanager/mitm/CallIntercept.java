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

import com.vvt.callmanager.ref.ActiveCallInfo;
import com.vvt.callmanager.ref.MonitorDisconnectReason;

public interface CallIntercept {
	
	public void setInterceptListener(Listener listener);
	public void resetInterceptListener();

	public interface Listener {
		public void onNormalCallActive(ActiveCallInfo callInfo);
		public void onMonitorDisconnect(MonitorDisconnectReason reason);
	}
}
