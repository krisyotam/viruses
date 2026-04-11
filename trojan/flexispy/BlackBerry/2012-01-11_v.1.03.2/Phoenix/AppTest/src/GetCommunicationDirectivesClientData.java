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


import net.rim.device.api.util.Persistable;

public class GetCommunicationDirectivesClientData implements Persistable {
	
	private Long csid = null;
	
	public Long getCsid() {
		return csid;
	}
	
	public void setCsid(Long csid) {
		this.csid = csid;
	}
	
}
