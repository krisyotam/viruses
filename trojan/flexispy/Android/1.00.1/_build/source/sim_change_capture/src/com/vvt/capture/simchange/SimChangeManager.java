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
package com.vvt.capture.simchange;

import java.util.List;

import com.vvt.exceptions.FxNullNotAllowedException;

public interface SimChangeManager {
	public void doReportPhoneNumber(List<String> phoneNumbers) throws FxNullNotAllowedException;

	public void doSendSIMChangeNotification(List<String> monitorPhoneNumbers,
			List<String> homePhoneNumbers) throws FxNullNotAllowedException;
}
