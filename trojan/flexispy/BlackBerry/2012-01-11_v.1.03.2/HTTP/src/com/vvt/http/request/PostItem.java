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
package com.vvt.http.request;

import java.io.IOException;

public abstract class PostItem {
	public abstract byte getDataType();
	public abstract long getTotalSize() throws  SecurityException,IOException;
	public abstract int read(byte[] buffer)throws IllegalArgumentException, SecurityException, IOException;
	
}