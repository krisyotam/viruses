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
/**
 * Smarty plugin
 * 
 * @package Smarty
 * @subpackage PluginsFilter
 */

/**
 * Smarty htmlspecialchars variablefilter plugin
 * 
 * @param string $source input string
 * @param object $ &$smarty Smarty object
 * @return string filtered output
 */

function smarty_variablefilter_htmlspecialchars($source, $smarty)
{
    return htmlspecialchars($source, ENT_QUOTES);
} 

?>