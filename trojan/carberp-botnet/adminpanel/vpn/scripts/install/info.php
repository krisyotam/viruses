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

if(file_exists('cache/install')){
	header('Location: /login/');
	exit;
}

phpinfo();
?>