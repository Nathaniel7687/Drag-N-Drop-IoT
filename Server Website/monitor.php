<?php
include_once("db_connect.php");
require_once('lib/FirePHPCore/FirePHP.class.php');

$firephp = FirePHP::getInstance(true);

$sql;
$device = $_POST['Init'];
$clientDevice = array();
if ($device == 'sensor'){
    $sql = 'SELECT  IP,
                    S_Ultrasonic,
                    S_IR,
                    S_Humidity,
                    S_Temperature,
                    S_Heatindex,
                    S_Light,
                    S_Gas
            FROM    SensorList
            ORDER BY IP ASC';

    $tmp = json_decode(stripslashes($_POST['Sensors']));
    //$firephp->info($tmp, 'Sensors');
    for($i = 0; $i < count($tmp); $i++){
    	//$ip2longVal = sprintf('%u',ip2long($tmp[$i]));	//ip2long할 경우 negative로 출력되므로 sprintf사용
    	array_push($clientDevice, ip2long($tmp[$i]));
    	//$firephp->info($clientDevice, 'Sensors');
    }
}
else if ($device == 'actuator') {
    $sql = 'SELECT  IP,
                    A_Fan,
                    A_Servo,
                    A_Buzzer
            FROM    ActuatorList
            ORDER BY IP ASC';
            
    $tmp = json_decode(stripslashes($_POST['Actuators']));
    for($i = 0; $i < count($tmp); $i++){
    	//$ip2longVal = sprintf('%u',ip2long($tmp[$i]));	//ip2long할 경우 negative로 출력되므로 sprintf사용
    	array_push($clientDevice, ip2long($tmp[$i]));
    	//$firephp->info($clientDevice, 'Actuator');
    }
}

sort($clientDevice);

$q_result = mysqli_query($conn, $sql);
if (!$q_result) {
    die("DB Connection Error: " . mysqli_error($conn));
}

$databaseDevice = array();
while($row = mysqli_fetch_array($q_result)) {
    array_push($databaseDevice, $row);
}

$existDevice = array();
$addDevice = array();
$deleteDevice = array();
$clientDeviceCount = count($clientDevice);
$databaseDeviceCount = count($databaseDevice);

if ($clientDeviceCount != 0) {
    for ($i = 0, $j = 0; $i < $clientDeviceCount && $j < $databaseDeviceCount;) {
        if ($clientDevice[$i] == $databaseDevice[$j]['IP']) {
            $databaseDevice[$j]['IP'] = long2ip($databaseDevice[$j]['IP']);
            array_push($existDevice, $databaseDevice[$j]);
            $i++;
            $j++;
        }
        else if ($clientDevice[$i] > $databaseDevice[$j]['IP']) {
            $databaseDevice[$j]['IP'] = long2ip($databaseDevice[$j]['IP']);
            array_push($addDevice, $databaseDevice[$j]);
            $j++;
        }
        else if ($clientDevice[$i] < $databaseDevice[$j]['IP']) {
            $clientDevice[$i] = long2ip($clientDevice[$i]);
            array_push($deleteDevice, $clientDevice[$i]);
            $i++;
        }
    }
}
else {
    for ($i = 0; $i < $databaseDeviceCount; $i++) {
        $databaseDevice[$i]['IP'] = long2ip($databaseDevice[$i]['IP']);
        array_push($addDevice, $databaseDevice[$i]);
    }
}

$result = array('exist' => $existDevice, 'add' => $addDevice, 'delete' => $deleteDevice);

// json_decode(stripslashes($_POST['Actuators']));

echo json_encode($result);
