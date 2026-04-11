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

public class MethodType {

	public static final MethodType GET = new MethodType("GET");
	public static final MethodType POST = new MethodType("POST");
	private String method = "";
	
	private MethodType(String method) {
		this.method = method;
	}
	
	public String toString() {
		return method;
	}
	
}