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

function smarty_modifier_items($value = 0)
{
	$reminder = $value % 10;
	if ($value === null || $reminder == 0 || $value == 0 || ($reminder >= 5 && $reminder <= 9) )
		return '�������';

	if ($reminder == 1)
		return '������';

	if ($reminder == 2 || $reminder == 3 || $reminder == 4)
		return '������';

	return '�������';
}

?>