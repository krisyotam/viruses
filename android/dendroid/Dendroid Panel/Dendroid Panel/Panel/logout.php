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
  session_start();
  if (empty($_SESSION['code'])) {
    header( 'Location: index.php' ) ;
    die();
  }
  
  session_unset();
  session_destroy();
  
  header( 'Location: index.php' ) ;
?>