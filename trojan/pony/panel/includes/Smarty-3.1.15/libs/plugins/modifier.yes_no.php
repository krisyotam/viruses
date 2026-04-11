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
function smarty_modifier_yes_no($value = 0)
{
	if ($value === null)
		return "����������";
	if ($value)
		return '��';
	else
		return '���';
}
?>