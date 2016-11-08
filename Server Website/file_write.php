<?php

	require_once('lib/FirePHPCore/FirePHP.class.php');
	require_once('code_strings.php');
	$firephp = FirePHP::getInstance(true);

	//$recieved_json = $_POST;
	$sensor = $_POST['sensor'];
	$act = $_POST['actuator'];
	$act_ip = $_POST['ip'];

// 	$firephp->log($sensor,'sensor');
// 	$firephp->log($act,'actuator');
	$firephp->log($act_ip,'actuator ip');
	
// 	$sensor_names = ['S_Ultrasonic','S_Humidity','S_Temperature','S_Heatindex','S_Light','S_Gas','S_IR'];
// 	$act_names = ['A_Fan','A_Servo','A_Buzzer'];	
	
	//수정되어야 하는 코드 (ip를 선택된 actuator ip로 수정)
	$s_mod = 'server_addr.sin_addr.s_addr = inet_addr("'.$act_ip.'");';
	
	$a_code_full = $a_header . $a_front . $a_while;	//full = 수정부분 + a_while2	
	$s_code_full = $s_header . $s_front . $s_mod . $s_end;		//piSensor.c 코드
	
	//file open
	$piSensorFile = fopen("../Pi with Pi/src/piSensor.c", "w");
	$piActFile = fopen("../Pi with Pi/src/piActuator.c", "w");
	if(!$piSensorFile) die("piSensor.c 파일을 열 수 없습니다.");
	if(!$piActFile) die("piActuator.c 파일을 열 수 없습니다.");
	
	//sensor file write
	fwrite($piSensorFile, $s_code_full);		//piSensor.c 생성	
	
	//sensor
	if($sensor === null) $firephp->info('no sensor condition');
	$a_mod = "";
	foreach($sensor as $items){
		foreach($items as $s_name=>$s_val){
			$firephp->info($s_name,'sensor name');

			switch($s_name){
				case 'S_Ultrasonic': $selected = 'sensor.ultrasonic'; break;
				case 'S_Humidity': $selected = 'sensor.humidity'; break;
				case 'S_Temperature': $selected = 'sensor.temperature'; break;
				case 'S_Heatindex': $selected = 'sensor.heatindex'; break; //temperature과 같음
				case 'S_Light': $selected = 'sensor.light'; break;
				case 'S_Gas': $selected = 'sensor.gas'; break;
				case 'S_IR': $selected = 'sensor.ir'; break;
			} //switch			
			
			if($s_name != 'S_IR'){	//장애물 센서 빼고 range 값 분할
				$range = explode(',', $s_val);
				$r1 = $range[0];
				$r2 = $range[1];
				$firephp->info($r1.":".$r2,'sensor value');
				$gap = ($r2-$r1)/3;
				$gap = ceil($gap);
				$for_if = [];
				$for_if[0] = $r1;
				//array_push($for_if,$r1);
				for($i = 1;$i<4;$i++){
					$for_if[$i] = $for_if[$i-1]+$gap; 
				}
				$firephp->info($gap,'sensor value gap');
				$firephp->info($for_if,'sensor value interval');
				
				
				$level = 4;
				for($j=count($for_if)-1;$j>=0;$j--){
					if($level == 4)	$a_mod .= 'if('.$selected.' > '.$for_if[$j].'){ 
						strcpy(level,"'.($level--).'");
			}'."\n\t\t\t\t";
				else $a_mod .= 'else if('.$selected.' > '.$for_if[$j].'){ 
						strcpy(level,"'.($level--).'");
			}'."\n\t\t\t\t";
				} //for				
				$a_mod .= 'else { strcpy(level,"'.($level).'");}'."\n\n";
			} else{ //장애물 센서일 경우
				$firephp->info($s_val,'sensor value');
				$a_mod .= $selected.' = "'.$s_val.'";';
			}
		}
	}	
	
	//actuator
	if($act === null) $firephp->info('no actuator condition');
	foreach($act as $items){
		foreach($items as $a_name=>$a_val){
			$firephp->info($a_name,'actuator name');
			$firephp->info($a_val,'actuator value');
			
			switch($a_name){
				case 'A_Fan': break;
				case 'A_Servo': break;
				case 'A_Buzzer': break;
			}
		}
	}
	
	$a_code_full .= $a_mod . $a_end;
	
	//actuator file write
	fwrite($piActFile, $a_code_full);		//piActuator.c 생성	
	
	//file close
	fclose($piSensorFile);
	fclose($piActFile);
	
	echo true;
?>