<?php
$host = "165.132.121.124"; // 자신의 mysql
$DB_name = "master"; // 데이터베이스 이름
$user = "root"; // 기본 사용자.
$password = "0000"; // apm 기본 암호

$sensor_field_cnt = 7;
$actuator_field_cnt = 3;
$sensor_field_name = array(
	'초음파',
	'장애물 감지',
	'습도',
	'온도',
	'열',
	'조도',
	'가스'
); //센서 필드명 집합
$actuator_field_name = array(
	'A_Fan',
	'A_Servo',
	'A_Buzzer'
); //액추에이터 필드명 집합

$conn = mysqli_connect($host, $user, $password, $DB_name);

if (!$conn) { die("DB Connection Error: " .mysqli_error($conn)); }

// else
if($_POST['table_name'] == 'sensorlist'){
	$sql = "select S_Ultrasonic,S_IR,S_Humidity,S_Temperature,S_Heatindex,S_Light,S_Gas from SensorList";
}
else{
	$sql = "select A_Fan,A_Servo,A_Buzzer from ActuatorList";
}

$result = mysqli_query($conn, $sql) or die("Error in Selecting " . mysqli_error($conn));

while ($row = mysqli_fetch_array($result)) {
	if($_POST['table_name'] == 'sensorlist'){
		for ($i = 0; $i < $sensor_field_cnt; $i++) {	//sensor part
			if ($row[$i] != NULL) {
				echo "<li class='ui-widget-content ui-corner-tr'>";
				echo "<h5 class='ui-widget-header'>" . $sensor_field_name[$i] . " 센서</h5>";
				echo "<a href='images/high_tatras.jpg' title='View larger image' class='ui-icon ui-icon-zoomin'> View larger</a>";
				echo "<a href='link/to/trash/script/when/we/have/js/off' title='Delete this image' class='ui-icon ui-icon-trash'>Delete image</a></li>";
			}	//if
		}	//for
	}	//if
	else{	//table_name == actuatorlist
		for($j = 0; $j < $actuator_field_cnt; $j++){	//actuator part
			if($row[$j] != NULL){
				echo "<li class='ui-widget-content ui-corner-tr'>";
				echo "<h5 class='ui-widget-header'>" . $actuator_field_name[$j] . "</h5>";
				echo "<a href='images/high_tatras.jpg' title='View larger image' class='ui-icon ui-icon-zoomin'> View larger</a>";
				echo "<a href='link/to/trash/script/when/we/have/js/off' title='Delete this image' class='ui-icon ui-icon-trash'>Delete image</a></li>";
			}	//if
		}	//for
	}
}	//while

mysqli_close($conn);
?>