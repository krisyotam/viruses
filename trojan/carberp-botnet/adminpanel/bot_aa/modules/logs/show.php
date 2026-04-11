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

$smarty->assign('rand_name', mt_rand(0000000000, 9999999999));

if(!empty($Cur['str'])){
	print('Уникальных ботов: ' .  $mysqli->query_name('SELECT COUNT(DISTINCT(concat(prefix, uid))) count FROM bf_filter_'.$Cur['str']));
	exit;
}


?>