/*
  name      Carberp Botnet
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    krisyotam
  archived  krisyotam (2026)
  notes     —
 */
<?php

function kldecode($str) {
	if(function_exists('mb_convert_encoding')){
		return mb_convert_encoding(base64_decode($str), 'UTF-8', 'WINDOWS-1251');
	}else{
		return base64_decode($str);
	}
}

?>