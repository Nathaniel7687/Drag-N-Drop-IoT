<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->

    <title>Title</title>

    <!-- Bootstrap core CSS -->
    <link href="style/bootstrap.min.css" rel="stylesheet">
    <link href="style/jquery-ui.css" rel="stylesheet">

    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <link href="style/ie10-viewport-bug-workaround.css" rel="stylesheet">

    <style type="text/css" media="screen">
      /* Move down content because we have a fixed navbar that is 50px tall */
      body {
        padding-top: 50px;
        padding-bottom: 20px;
        max-height: 1200px;
        max-width: 2000px;
        min-width:1000px;
        min-height: 600px;
      }
      .top_margin{ margin-top:20px; }
      .top_padding{ padding-top: 17px; }
      .height-set{
        min-height:600px;
        max-height:1200px;
      }
      /* #ul-sensor-list li, #ul-act-list li{
        float:left;
        width:100%;
        min-height: 70px;
        padding:0.4em;
        margin:0 auto 0.4em auto;
        text-align: center;
      }
      #ul-sensor-list li h5, #ul-act-list li h5{
        margin:0 0 0.4em;
      } */
      ul li, ul li{
        float:left;
        width:100%;
        padding:0.4em;
        margin:0 auto 0.4em auto;
        text-align: center;
      }
      ul li h5, ul li h5{
        margin:0 0 0.4em;
      }
      th{
        text-align: center;
      }
      .table{
        font-size: 13px;
        margin-bottom: 0px;
      }
      td{
        width:50%;
      }
      .list-placeholder{
        border: 1px dotted gray;
        background-color: #E8E4E4;
        margin: 0 1em 1em 0;
        height: 50px;
      }
      
      .slider-selection{
       	background: #337ab7; 
	}
	.slider.slider-horizontal{
		width:100%;
		
	}
	#select{
		margin-left:15px;
		width:25%;
	}
	/* #sliders{
		margin-left:30px;
		width:65%;
	} */
	.slider-track-high, .slider-track-low{
		background-color:lightgray;
	}
    </style>
</head>

<body>
    <!-- Navigation Bar -->
    <nav class="navbar navbar-inverse navbar-fixed-top">
      <div class="container" style="margin-left: 20px">
        <div class="navbar-header">
          <a class="navbar-brand text-left" style="margin: 0 0 0 0px" href="#">IoT Drag &amp; Drop Project</a>
        </div>
      </div>
    </nav>

    <div class="container-fluid">
      <div class="row top_margin">
        <!-- Sensor List -->
        <div id="div-sensor-list" class="col-md-2" style="border-right: 2px solid lightgray">
          <h3 class="text-center">센서 목록</h3>
          <hr style="border-bottom: 1px solid lightgray">

          <ul id="ul-sensor-list" class="sensor list-unstyled height-set">
            <!-- Will be added by php ajax -->
          </ul>
        </div>


        <div class="col-md-8">
          <div class="row">
            <!-- Selected Sensor -->
            <div id="div-selected-sensor" class="col-md-3">
            <!-- Title part -->
              <h3 class="text-center">센서</h3>
              <hr style="border-bottom: 1px solid lightgray;">

              <ul id="selected-sensor" class="sensor list-unstyled height-set">
              <!-- Droppable -->
              </ul>

            </div>
            <div id="div-condition" class="col-md-6">
            <!-- Title part -->
              <h3 class="text-center">조건</h3>
              <hr style="border-bottom: 1px solid lightgray;">
              
              <!-- 조건 추가 버튼들 -->
              <div class="btn-group btn-group-justified" role="group" aria-label="add buttons">
              	<div class="btn-group btn-group-lg" role="group" >
	              	<button type="button" class="btn btn-default" aria-label="Add Sensor Conditions" 
	              			value="sensor-add" onclick="condition_btn(this.value)">
	                  <span class="glyphicon glyphicon-plus" aria-hidden="true"></span>&nbsp;&nbsp;&nbsp;센서 조건
	                </button>
                </div>
                <div class="btn-group btn-group-lg" role="group">
	              	<button type="button" class="btn btn-default" aria-label="Add Actuator Conditions"
	              			value="actuator-add" onclick="condition_btn(this.value)">
	                  <span class="glyphicon glyphicon-plus" aria-hidden="true"></span>&nbsp;&nbsp;&nbsp;액추에이터 조건
	                </button>
                </div>
              </div> <!-- div .btn-group-justified -->

				<hr>
				
			<!-- 조건부 양식 list  -->			
			<form id="form-condition" class="form-horizontal" role="form">
				<div class="row">
					<select class="col-md-3 form-control" id="select">
						<option>센서 선택</option>
						<option>초음파 센서</option>
						<option>장애물 감지 센서</option>
						<option>습도 센서</option>						
					</select>
					<div hidden class="col-md-8" style="float:right; margin-top:5px;">
						<input id="single-slider" type="text"
								data-slider-id='single-slider' 
								data-slider-min="0" 
								data-slider-max="4" 
								data-slider-step="1" 
								data-slider-value="0"/>
					</div>
					<div hidden class="col-md-8" style="float:right; margin-top:5px;">
						<input id="range-slider" type="text" value=""
								data-slider-min="0" 
								data-slider-max="100" 
								data-slider-step="5" 
								data-slider-value="[30,70]"/>
					</div>
					<div class="col-md-8" style="float:right;">
						<div class="form-group" style="margin-left:50px;">
							<label class="radio-inline">
							  <input type="radio" name="inlineRadioOptions" id="inlineRadio1" value="option1"> true
							</label>
							<label class="radio-inline" style="margin-left:50px;">
							  <input type="radio" name="inlineRadioOptions" id="inlineRadio2" value="option2"> false
							</label>
						</div>
					</div>
				</div>
				<hr>
				<!-- row 계속 추가 -->
			</form>
              

              <hr>
              
              <!-- 빌드/리셋 버튼 -->
			<div class="btn-group btn-group-justified" role="group" aria-label="build, reset buttons">
              	<div class="btn-group btn-group-lg" role="group" >
	              	<button type="button" class="btn btn-success" aria-label="Add Sensor Conditions" >
	                  <span class="glyphicon glyphicon-ok" aria-hidden="true"></span>&nbsp;&nbsp;&nbsp;완료
	                </button>
                </div>
                <div class="btn-group btn-group-lg" role="group">
	              	<button type="button" class="btn btn-danger" aria-label="Add Actuator Conditions">
	                  <span class="glyphicon glyphicon-repeat" aria-hidden="true"></span>&nbsp;&nbsp;&nbsp;초기화
	                </button>
                </div>
              </div> <!-- div .btn-group-justified -->

              
              <!-- 빌드 후 메세지 -->
              <div class="alert alert-warning alert-dismissible top_margin" role="alert">
				  <button type="button" class="close" data-dismiss="alert" aria-label="Close"><span aria-hidden="true">&times;</span></button>
				  <strong>Warning!</strong> Better check yourself, you're not looking too good.
				</div>
				
              
            </div>


            <div id="div-selected-actuator" class="col-md-3">
            <!-- Title part -->
              <h3 class="text-center">기기</h3>
              <hr style="border-bottom: 1px solid lightgray; ">

              <ul id="selected-actuator" class="actuator list-unstyled height-set">
              </ul>
            </div>

          </div>
       </div>


        <div id="div-actuator-list" class="col-md-2" style="border-left: 2px solid lightgray">
        <!-- Title part -->
          <h3 class="text-center" >기기 목록</h3>
          <hr style="border: 1px solid lightgray">

          <ul id="ul-act-list" class="actuator list-unstyled height-set">
            <!-- Will be added by php ajax -->
          </ul>
        </div>
      </div>

      <hr>

      <footer>
        <p>&copy; Footer</p>
      </footer>
    </div> <!-- /container -->

    <!-- JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="script/jquery-1.12.4.js" type="text/javascript"></script>
    <script src="script/bootstrap.min.js" type="text/javascript"></script>
    <script src="script/jquery-ui.js" type="text/javascript"></script>

    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <script src="script/ie10-viewport-bug-workaround.js" type="text/javascript"></script>

    <script>
        setInterval(function monitor() {
            var sensorList = [
            	"192.168.0.1",
                "192.168.0.2",
                "192.168.0.3",
                "192.168.0.4"];
            var actuatorList = [
            	"192.168.0.6",
                "192.168.0.7",
                "192.168.0.8",
                "192.168.0.9"
                ];

            $.ajax({
                type: 'POST',
                url: 'monitor.php',
                data: {
                    Init: 'sensor',
                    Sensors: JSON.stringify(sensorList)
                },
                datatype: 'json',
                success: function(result) {
                    console.log(result);
                    var array = JSON.parse(result);

                    $.each(array, function(state, arr){
                        //console.log(state);
                        if(state == "exist" && arr.length != 0) exist(arr,"sensor");
                        else if(state == "add" && arr.length != 0) add(arr,"sensor");
                        else if(state == "delete" && arr.length != 0) del(arr,"sensor");
                        //else alert("state: "+state+" Error: Wrong Value!!");
                    });
                },
                error: function(result) {
                    alert('Sensor 항목을 갱신하지 못했습니다.');
                }
            });

            $.ajax({
                type: 'POST',
                url: 'monitor.php',
                data: {
                    Init: 'actuator',
                    Actuators: JSON.stringify(actuatorList)
                },
                datatype: 'json',
                success: function(result) {
                    var array = JSON.parse(result);
                    
                    $.each(array, function(state, arr){
                        if(state == "exist" && arr.length != 0) exist(arr,"actuator");
                        else if(state == "add" && arr.length != 0) add(arr,"actuator");
                        else if(state == "delete" && arr.length != 0) del(arr,"actuator");
                        //else alert("Error: Wrong Value!!");
                    });
                },
                error: function(result) {
                    alert('Actuator 항목을 갱신하지 못했습니다.');
                }
            });
        }, 1000);

        var li_tag = "<li class='sensor ui-widget-content ui-corner-tr ui-state-default'>";
        var h5_tag = "<h5 class='ui-widget-header'>IP: ";
        var table_tag = "</h5><table class='table table-hover table-condensed table-bordered'><tbody>";
		var sensor_field_name = ["","S_Ultrasonic","S_IR","S_Humidity","S_Temperature","S_Heatindex","S_Light","S_Gas"];
		var actuator_field_name = ["","A_Fan","A_Servo","A_Buzzer"];
		var closing_tag = "</tbody></table></li>";
        
        function add(arr, whichList){
        	var length = arr.length;
            switch(whichList){		//sensor인지 actuator인지 구분
            case "sensor":                
            	for(var i=0; i<length; i++){
            		var full_tag = li_tag + h5_tag + arr[i].IP + table_tag;         		
                	for(var j=1;j<sensor_field_name.length;j++){
                    	if(arr[i][j] !== null) {
                        	full_tag += "<tr><td>"+sensor_field_name[j]+"</td>";
                        	full_tag += "<td>"+arr[i][j]+"</td></tr>";
                    	}
                        	//console.log(sensor_field_name[j]+": "+arr[i][j]);
						//full_tag += arr[i][j];
                    }
                	full_tag += closing_tag;
        			$('#ul-sensor-list').append(full_tag); 
        			//console.log("full tag: "+full_tag); 
    			}
    			//console.log("break");
    			
    			sort();
                break;
            case "actuator": 
            	for(var i=0; i<length; i++){
            		var full_tag = li_tag + h5_tag + arr[i].IP + table_tag;         		
                	for(var j=1;j<actuator_field_name.length;j++){
                    	if(arr[i][j] !== null) {
                        	full_tag += "<tr><td>"+actuator_field_name[j]+"</td>";
                        	full_tag += "<td>"+arr[i][j]+"</td></tr>";
                    	}
                        	//console.log(sensor_field_name[j]+": "+arr[i][j]);
						//full_tag += arr[i][j];
                    }
                    //console.log("next");
                	//$('#ul-sensor-list').append(full_tag);  
                	full_tag += closing_tag;
        			$('#ul-act-list').append(full_tag); 
        			//console.log("full tag: "+full_tag); 
    			}
    			//console.log("break");
    			
    			sort();
                break;
            default: alert("Error at classifying!!");
            }		
        }

        function exist(arr, whichList){
        	var length = arr.length;
            switch(whichList){		//sensor인지 actuator인지 구분
            case "sensor": 
            	for(var i=0; i<length; i++){
    			}
                break;
            case "actuator": 
            	for(var i=0; i<length; i++){
    			}
                break;
            default: alert("Error at classifying!!");
            }	
        }

        function del(arr, whichList){
        	var length = arr.length;
            switch(whichList){		//sensor인지 actuator인지 구분
            case "sensor": 
            	for(var i=0; i<length; i++){
    			}
                break;
            case "actuator": 
            	for(var i=0; i<length; i++){
    			}
                break;
            default: alert("Error at classifying!!");
            }	
        }

        function sort() { //sortable (drag&drop)
            var $ul_sensor_list = $("#ul-sensor-list");
            var $ul_act_list = $("#ul-act-list");
            var $selected_sensor = $("#selected-sensor");
            var $selected_act = $("#selected-actuator");

            $("#ul-sensor-list, #selected-sensor").sortable({
                connectWith: ".sensor",
                placeholder: "list-placeholder ui-corner-all"
            }).disableSelection();

            $("#ul-act-list, #selected-actuator").sortable({
                connectWith: ".actuator",
                placeholder: "list-placeholder ui-corner-all"
            }).disableSelection();
        }
    </script>
</body>

</html>