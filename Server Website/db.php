<?php
$host = "localhost";	// 자신의 mysql
$DB_name = "master";	// 데이터베이스 이름
$user = "root";			// 기본 사용자.
$password = "0000";		// apm 기본 암호

$conn = mysqli_connect($host, $user, $password, $DB_name);

if(!$conn){
    echo "fail!\n";
    die('Could not connect: ' . mysqli_error($con));
}

//else
$sql = "select * from sensorlist";
$result = mysqli_query($conn,$sql);
$rowcnt = mysqli_num_rows($result);
$filed_name = array('S_Ultrasonic','S_IR','S_Humidity','S_Temperature','S_Heatindex','S_Light','S_Gas');	//센서 필드명 집합

if($rowcnt == 1){	//right (data가 1행만 들어있는 게 맞는 지 체크)
	while($row = mysqli_fetch_array($result)){
		for($i=0;$i<count($filed_name);$i++){
			if($row[$filed_name[$i]] != NULL){
				echo "<li class='ui-widget-content ui-corner-tr ui-draggable ui-draggable-handle'>";
				echo "<h5 class='ui-widget-header'>" . $filed_name[$i] . "</h5>";
				echo "<a href='images/high_tatras.jpg' title='View larger image' class='ui-icon ui-icon-zoomin'> View larger</a>";
				echo "<a href='link/to/trash/script/when/we/have/js/off' title='Delete this image' class='ui-icon ui-icon-trash'>Delete image</a></li>";
			}
		}
	}
	//echo "No sensor";
} else if($rowcnt == 0) {	//data가 하나도 없으면 없다고 출력
	//없다고 출력
	echo "No sensor";
} else {	//이도 저도 아니면 땡!
	//db 에러 출력
	echo "No sensor";
}
mysqli_close($conn);

?>