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
package com.fx.preference;

import java.util.List;

import android.net.Uri;

import com.fx.activation.Response;
import com.fx.preference.model.ConnectionHistory;

public interface ConnectionHistoryManager {
	
	public static final Uri URI_NEW_RECORD_ADDED = 
			Uri.parse("content://com.fx.pref/new_conn_history_added");

	public void addConnectionHistory(ConnectionHistory connectionHistory);
	public List<ConnectionHistory> getConnectionHistoryList();
	public ConnectionHistory getLatestConnectionHistory();
	
	public void setActivationResponse(Response response);
	public Response getActivationResponse();
}
