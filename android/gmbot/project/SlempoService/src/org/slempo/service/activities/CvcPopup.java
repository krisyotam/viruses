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
package org.slempo.service.activities;

import org.slempo.service.R;

import android.app.Activity;
import android.os.Bundle;

public class CvcPopup extends Activity {
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.billing_addcreditcard_cvc_popup);
	}
}
