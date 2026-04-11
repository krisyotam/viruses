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

if(isset($_POST['edit_submit'])){
	file_put_contents('templates/modules/main/text.tpl', $_POST['html']);
	header('Location: /main/');
	exit;
}else{
	$_POST['html'] = file_get_contents('templates/modules/main/text.tpl');
}

?>