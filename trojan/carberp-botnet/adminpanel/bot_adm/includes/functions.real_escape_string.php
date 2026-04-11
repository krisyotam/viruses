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

function real_escape_string(&$value){
	global $mysqli;
	$value = str_replace("'", '', $value);
	$value = str_replace('"', '', $value);
    return $mysqli->real_escape_string($value);
}

?>