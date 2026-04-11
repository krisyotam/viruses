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
package com.vvt.encryption;

public class DataTooLongForRSAEncryptionException extends Exception {

	String value="DataIsTooLongForRSAEncryptionException";

    DataTooLongForRSAEncryptionException(String v) 
    {
        value = v;
    }
    
    public String toString() 
    {
        return "RSAEncryption Exception: " + value;
    }
	
    public String getMessage()	{
    	return this.toString();
    }
}
