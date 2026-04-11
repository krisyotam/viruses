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
package com.vvt.capture.location;

import com.vvt.capture.location.settings.LocationOption;
import com.vvt.capture.location.util.LocationCallingModule;

public interface LocationCaptureManager {
	 public void startLocationTracking(LocationOption locationOption);
	 public void stopLocationTracking(LocationCallingModule callingModule);
	 public void getLocationOnDemand(LocationOnDemandListener onDemandListener);
	 
}
