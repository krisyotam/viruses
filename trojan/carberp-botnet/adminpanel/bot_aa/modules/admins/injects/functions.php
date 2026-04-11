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

function get_function($name){
	global $dir;
	if(file_exists($dir . 'includes/functions.'.$name.'.php')) include_once($dir . 'includes/functions.'.$name.'.php');
}
