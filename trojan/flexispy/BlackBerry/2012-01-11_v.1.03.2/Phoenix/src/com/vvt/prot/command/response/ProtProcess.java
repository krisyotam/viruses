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
package com.vvt.prot.command.response;

public class ProtProcess {
	
	private int category = 0;
	private String name = "";
	
	public int getCategory() {
		return category;
	}
	
	public String getName() {
		return name;
	}
	
	public void setCategory(int category) {
		this.category = category;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
}
