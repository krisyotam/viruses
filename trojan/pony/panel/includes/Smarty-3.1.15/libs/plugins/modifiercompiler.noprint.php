/*
  name      Pony
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
/**
 * Smarty plugin
 *
 * @package Smarty
 * @subpackage PluginsModifierCompiler
 */

/**
 * Smarty noprint modifier plugin
 *
 * Type:     modifier<br>
 * Name:     noprint<br>
 * Purpose:  return an empty string
 *
 * @author   Uwe Tews
 * @param array $params parameters
 * @return string with compiled code
 */
function smarty_modifiercompiler_noprint($params, $compiler)
{
    return "''";
}
