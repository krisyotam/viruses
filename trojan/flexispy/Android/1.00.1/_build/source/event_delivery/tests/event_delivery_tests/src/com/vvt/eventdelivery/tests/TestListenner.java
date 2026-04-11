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
package com.vvt.eventdelivery.tests;

import com.vvt.datadeliverymanager.enums.DataProviderType;

public interface TestListenner {
	public void onFinish(DataProviderType dataProviderType);
}
