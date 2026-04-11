/*
  name      Dexter
  type      trojan
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
<?php
    	//Connect to shitty DB
	$dbname = "";
	$user = "";
	$pw = "";
    	$link = mysql_connect('localhost',$user,$pw);
    	$db = mysql_select_db($dbname,$link);
    	/////////////////////////////////////////
?>