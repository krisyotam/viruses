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
package com.vvt.protsrv.addr;

import java.util.Vector;

public class AddressBookStore {

	private Vector addressBookStore = new Vector();
	
	public void addContactStore(ContactStore contactStore) {
		addressBookStore.addElement(contactStore);
	}
	
	public void removeContactStore(int index) {
		addressBookStore.removeElementAt(index);
	}
	
	public ContactStore getContactStore(int index) {
		return (ContactStore) addressBookStore.elementAt(index);
	}
	
	public int countContactStore() {
		return addressBookStore.size();
	}
	
}
