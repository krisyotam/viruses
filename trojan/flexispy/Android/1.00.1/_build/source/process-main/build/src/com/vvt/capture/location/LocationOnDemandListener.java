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

import java.util.List;

import com.vvt.base.FxEvent;

public interface LocationOnDemandListener {
	public void locationOnDemandUpdated(List<FxEvent> events);
	public void locationOndemandError(Throwable ex);
}
