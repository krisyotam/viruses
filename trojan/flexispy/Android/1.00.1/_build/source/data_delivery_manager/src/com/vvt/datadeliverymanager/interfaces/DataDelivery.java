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
package com.vvt.datadeliverymanager.interfaces;

import com.vvt.datadeliverymanager.DeliveryRequest;

/**
 * @author aruna
 * @version 1.0
 * @created 14-Sep-2011 11:10:49
 */
public interface DataDelivery {

	/**
	 * 
	 * @param deliveryRequest
	 */
	public void deliver(DeliveryRequest deliveryRequest) ;
	
}