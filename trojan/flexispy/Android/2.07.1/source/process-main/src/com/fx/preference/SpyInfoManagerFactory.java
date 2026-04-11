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
package com.fx.preference;

import android.content.Context;

public class SpyInfoManagerFactory {
	
	public static SpyInfoManager getSpyInfoManager(Context context) {
//		return new SpyInfoManagerMockImpl(context);
		return SpyInfoManagerImpl.getInstance(context);
	}

}
