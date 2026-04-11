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
package com.vvt.daemon_addressbook_manager.delivery;

import com.vvt.phoenix.prot.command.DataProvider;

/**
 * @author Aruna
 * @version 1.0
 * @created 07-Oct-2011 03:23:32
 */
public class SendAddressbookForApprovalProvider implements DataProvider {

	public boolean hasNext(){
		return true;
	}

	public Object getObject(){
		return null;
	}

}