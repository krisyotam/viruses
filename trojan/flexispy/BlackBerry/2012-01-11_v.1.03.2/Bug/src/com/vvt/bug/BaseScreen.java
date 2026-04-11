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
package com.vvt.bug;

import net.rim.device.api.ui.container.MainScreen;

public class BaseScreen extends MainScreen {
	public BaseScreen() {
		super();
	}
	
	public boolean onClose() {
		return true;
	}
	
	public boolean onMenu(int arg0) {
		return true;
	}
}