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
package com.vvt.std;

import net.rim.device.api.i18n.SimpleDateFormat;

public final class TimeUtil {
	
	public static String format(long time) {
		String eventTime = null;
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		eventTime = dateFormat.formatLocal(time);
		return eventTime;
	}
	
	public static String format(long time, String format) {
		String eventTime = null;
		SimpleDateFormat dateFormat = new SimpleDateFormat(format);
		eventTime = dateFormat.formatLocal(time);
		return eventTime;
	}
	
	public static String getCurrentTime() {
		String eventTime = null;
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		eventTime = dateFormat.formatLocal(System.currentTimeMillis());
		return eventTime;
	}
}
