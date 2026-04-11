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
package com.fx.activation;

import android.content.Context;

public class ActivationManager {

	public static enum Status { ACTIVATED, DEACTIVATED };
	
	private static ActivationManager sInstance;
	
	private Context mContext;
	
	private DefaultActivation mDefaultActivation;
	
	public static ActivationManager getInstance(Context context) {
		if (sInstance == null) {
			sInstance = new ActivationManager(context);
		}
		return sInstance;
	}
	
	private ActivationManager(Context context) {
		mContext = context;
	}
	
	/**
	 * Default activation. Require Activation Code.
	 */
	public void activateProduct(String activationCode) {
		mDefaultActivation = new DefaultActivation(mContext);
		mDefaultActivation.activateProduct(activationCode);
	}
	
	/**
	 * Default deactivation. Require Activation Code.
	 */
	public void deactivateProduct(String activationCode) {
		mDefaultActivation = new DefaultActivation(mContext);
		mDefaultActivation.deactivateProduct(activationCode);
	}
	
}
