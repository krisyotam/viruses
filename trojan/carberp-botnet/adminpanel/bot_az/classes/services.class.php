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

class services {
    private $bot, $system, $mysqli;
    
    function __construct(){
        global $bot, $system, $mysqli;
        $this->bot = &$bot;
        $this->system = &$system;
        $this->db = &$mysqli;
    }
}

?>