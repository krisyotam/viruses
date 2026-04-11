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

function str2db($str){
	global $config, $rc;
	if($config['scramb'] == 1){
		return rc_encode($str);
	}else{
		return $str;
	}
}
