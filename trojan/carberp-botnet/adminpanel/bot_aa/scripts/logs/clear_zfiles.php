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

ini_set('max_execution_time', 0);
$dir = realpath('.');
$count = 0;
$files = $mysqli->query('SELECT id,file,size FROM bf_files');
foreach($files as $file){
	if(strpos('/', $file->file) !== '/') $file->file = '/' . $file->file;
	$file->file = str_replace('//', '/', $file->file);
	if(!file_exists($dir . '/logs' . $file->file)){
		echo $dir . '/logs' . $file->file . "<br>";
		$mysqli->query('delete from bf_files where (id = \''.$file->id.'\')');
		$count++;
	}
}
echo $count;
?>