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
package com.vvt.mediamon.info;

import net.rim.device.api.util.Persistable;

public class AudioInfo extends MediaInfo implements Persistable {

	public MediaInfoType getMediaInfoType() {
		return MediaInfoType.AUDIO_THUMBNAIL;
	}

}
