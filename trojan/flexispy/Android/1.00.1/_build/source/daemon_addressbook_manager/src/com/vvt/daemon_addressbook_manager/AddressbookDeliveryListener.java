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
package com.vvt.daemon_addressbook_manager;

public interface AddressbookDeliveryListener {
	public void onSuccess(); 
	public void onError(int statusCode, String error);
}
