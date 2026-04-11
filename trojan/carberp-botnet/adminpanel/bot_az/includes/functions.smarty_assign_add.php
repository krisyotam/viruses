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

function smarty_assign_add($name, $value, $eq = "\n"){
	global $smarty;
	if(isset($smarty->tpl_vars[$name])){
		$smarty->assign($name, $smarty->tpl_vars[$name] . $eq . $value);
	}else{
		$smarty->assign($name, $value);
	}
}

?>