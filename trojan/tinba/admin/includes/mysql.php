/*
  name      Tinba
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

	$mysqlhost = "localhost";
	$mysqlname = "hunt";
	$mysqlpass = "pass";
	$mysqlbase = "hunt";

	mysql_connect($mysqlhost, $mysqlname, $mysqlpass) or die("Could not connect to database: " . mysql_error());
	mysql_select_db($mysqlbase) or die("Could not select database : " . mysql_error());

?>