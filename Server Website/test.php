<?php 
$host = "127.0.0.1";
$name = "root";
$pwd = "0000";
$db = "test";
$mysqli = new mysqli($host, $name, $pwd, $db);
if(mysqli_connect_errno()){
	printf("fail");
	exit();
} else {
	printf("good!!!");
}

mysqli_close($mysqli);

?>