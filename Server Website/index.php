<!DOCTYPE html>
<html lang="en">

<head>
	<meta charset="utf-8">
	<meta content="IE=edge" http-equiv="X-UA-Compatible">
	<meta content="width=device-width, initial-scale=1" name="viewport">
	<!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->

	<title>Title</title>

	<!-- Bootstrap core CSS -->
	<link href="style/bootstrap.min.css" rel="stylesheet">
	<link href="style/jquery-ui.css" rel="stylesheet">
	<link href="style/bootstrap-slider.min.css" rel="stylesheet">

	<!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
	<link href="style/ie10-viewport-bug-workaround.css" rel="stylesheet">

	<style media="screen" type="text/css">
		/* Move down content because we have a fixed navbar that is 50px tall */
		
		body {
			padding-top: 50px;
			padding-bottom: 20px;
			max-height: 1200px;
			max-width: 2000px;
			min-width: 1000px;
			min-height: 600px;
		}
		
		.top_margin {
			margin-top: 20px;
		}
		
		.top_padding {
			padding-top: 17px;
		}
		
		.height-set {
			min-height: 600px;
			max-height: 1200px;
		}
		
		ul li,
		ul li {
			float: left;
			width: 100%;
			padding: 0.4em;
			margin: 0 auto 0.4em;
			text-align: center;
		}
		
		ul li h5,
		ul li h5 {
			margin: 0 0 0.4em;
		}
		
		option,
		select,
		th {
			text-align: center;
		}
		
		.table {
			font-size: 13px;
			margin-bottom: 0;
		}
		
		td {
			width: 50%;
		}
		
		.list-placeholder {
			border: 1px dotted gray;
			background-color: #E8E4E4;
			margin: 0 1em 1em 0;
			height: 50px;
		}
		
		.slider-selection {
			background: #337ab7;
		}
		
		.slider.slider-horizontal {
			width: 100%;
		}
		
		#select {
			margin-left: 15px;
			width: 25%;
		}
		
		#form-condition,
		.cond {
			margin-bottom: 15px;
		}
		
		.slider-track-high,
		.slider-track-low {
			background-color: lightgray;
		}
		
		.form-control {
			width: 25%;
			margin-left: 15px;
		}
	</style>
</head>

<body>
	<!-- Navigation Bar -->
	<nav class="navbar navbar-inverse navbar-fixed-top">
		<div class="container" style="margin-left: 20px">
			<div class="navbar-header">
				<a class="navbar-brand text-left" href="#" style="margin: 0 0 0 0px">IoT Drag &amp; Drop Project</a>
			</div>
		</div>
	</nav>

	<div class="container-fluid">
		<div class="row top_margin">
			<!-- Sensor List -->
			<div class="col-md-2" id="div-sensor-list" style="border-right: 2px solid lightgray">
				<h3 class="text-center">센서 목록</h3>
				<hr style="border-bottom: 1px solid lightgray">

				<ul class="sensorDevices list-unstyled height-set" id="ul-sensor-list">
					<!-- Will be added by php ajax -->
				</ul>
			</div>

			<div class="col-md-8">
				<div class="row">
					<!-- Selected Sensor -->
					<div class="col-md-3" id="div-selected-sensor">
						<!-- Title part -->
						<h3 class="text-center">센서</h3>
						<hr style="border-bottom: 1px solid lightgray;">

						<ul class="sensorDevices selected list-unstyled height-set " id="selected-sensor">
							<!-- Droppable -->
						</ul>

					</div>
					<div class="col-md-6" id="div-condition">
						<!-- Title part -->
						<h3 class="text-center">조건</h3>
						<hr style="border-bottom: 1px solid lightgray;">

						<!-- 조건 추가 버튼들 -->
						<div aria-label="add buttons" class="btn-group btn-group-justified" role="group">
							<div class="btn-group btn-group-lg" role="group">
								<button aria-label="Add Sensor Conditions" class="btn btn-default" onclick="btn_action('sensor')" type="button" value="sensor-add">
                                        <span aria-hidden="true" class="glyphicon glyphicon-plus"></span>&nbsp;&nbsp;&nbsp;센서 조건
                                    </button>
							</div>
							<div class="btn-group btn-group-lg" role="group">
								<button aria-label="Add Actuator Conditions" class="btn btn-default" onclick="btn_action('actuator')" type="button" value="actuator-add">
                                        <span aria-hidden="true" class="glyphicon glyphicon-plus"></span>&nbsp;&nbsp;&nbsp;기기 조건
                                    </button>
							</div>
						</div>
						<!-- div .btn-group-justified -->

						<hr>

						<!-- 조건부 양식 list  -->
						<form class="form-horizontal" id="form-condition" role="form"></form>

						<!-- 빌드/리셋 버튼 -->
						<div aria-label="build, reset buttons" class="btn-group btn-group-justified" role="group" style="margin-top:30px;">
							<div class="btn-group btn-group-lg" role="group">
								<button aria-label="Add Sensor Conditions" class="btn btn-success" onclick="btn_action('build')" type="button">
                                        <span aria-hidden="true" class="glyphicon glyphicon-ok"></span>&nbsp;&nbsp;&nbsp;완료
                                    </button>
							</div>
							<div class="btn-group btn-group-lg" role="group">
								<button aria-label="Add Actuator Conditions" class="btn btn-danger" onclick="btn_action('reset')" type="button reset">
                                        <span aria-hidden="true" class="glyphicon glyphicon-repeat"></span>&nbsp;&nbsp;&nbsp;초기화
                                    </button>
							</div>
						</div>
						<!-- div .btn-group-justified -->

						<!-- 빌드 후 메세지 -->
						<div class="alert alert-warning alert-dismissible top_margin" hidden="hidden" role="alert">
							<button aria-label="Close" class="close" data-dismiss="alert" type="button">
                                    <span aria-hidden="true">&times;</span>
                                </button>
							<strong>Warning!</strong> Better check yourself, you're not looking too good.
						</div>

					</div>

					<div class="col-md-3" id="div-selected-actuator">
						<!-- Title part -->
						<h3 class="text-center">기기</h3>
						<hr style="border-bottom: 1px solid lightgray; ">

						<ul class="actuatorDevices selected list-unstyled height-set" id="selected-actuator"></ul>
					</div>

				</div>
			</div>

			<div class="col-md-2" id="div-actuator-list" style="border-left: 2px solid lightgray">
				<!-- Title part -->
				<h3 class="text-center">기기 목록</h3>
				<hr style="border: 1px solid lightgray">

				<ul class="actuatorDevices list-unstyled height-set" id="ul-act-list">
					<!-- Will be added by php ajax -->
				</ul>
			</div>
		</div>

		<hr>

		<footer>
			<p>&copy; Footer</p>
		</footer>
	</div>
	<!-- /container -->

	<!-- JavaScript
    ================================================== -->
	<!-- Placed at the end of the document so the pages load faster -->
	<script src="script/jquery-1.12.4.js" type="text/javascript"></script>
	<script src="script/bootstrap.min.js" type="text/javascript"></script>
	<script src="script/jquery-ui.js" type="text/javascript"></script>
	<script src="script/bootstrap-slider.min.js" type="text/javascript"></script>

	<!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
	<script src="script/ie10-viewport-bug-workaround.js" type="text/javascript"></script>

	<!-- bootstrap slider -->
	<script>
		var range_slider_ids = [];
		
		
		function slider_setting(num, opt) {
			//console.info("slider setting");
			if (opt == "single") {
				$('#single-slider').bootstrapSlider({
					formatter: function(value) {
						return '레벨: ' + value;
					},
					id: "single-slider",
					max: 4,
					min: 0,
					step: 1,
					value: 0
				});
			} else {
				var slider_id = num+"-"+opt + "-slider";
				var empty=[];
				var min, max, range, step;

				if(opt.match("S_Ultrasonic")){ min=2; max=400; range="["+min+", 30]"; step=1;}
				else if(opt.match("S_Humidity")){ min=20; max=90; range="["+min+", 45]"; step=5;}
				else if(opt.match("S_Temperature")){ min=0; max=50; range="["+min+", 20]"; step=1;}
				else if(opt.match("S_Light")){ min=0; max=1000; range="["+min+", 50]"; step=10;}
				else if(opt.match("S_Gas")){ min=300; max=10000; range="["+min+", 350]"; step=10;}

				if($.inArray(slider_id, range_slider_ids) === -1) {	//중복 값이 없을 경우		
					for(var i=0;i<range_slider_ids.length;i++){
						if(range_slider_ids[i].match(num)){ //같은 select box에서 선택된 경우 새로 선택된 걸로 replace
							//console.log("match value: "+range_slider_ids[i]);
							console.log("id변경 from "+range_slider_ids[i]+" to "+slider_id);
							$('#'+range_slider_ids[i]).attr("id",slider_id);
							$('#sensor-cond-'+num+' > #range_slider > #range-slider').bootstrapSlider("setAttribute","min",min);
							$('#sensor-cond-'+num+' > #range_slider > #range-slider').bootstrapSlider("setAttribute","max",max);
							$('#sensor-cond-'+num+' > #range_slider > #range-slider').bootstrapSlider("setAttribute","step",step);
							$('#sensor-cond-'+num+' > #range_slider > #range-slider').bootstrapSlider("setValue",[min, min+20]);
							//slider.refresh();
							range_slider_ids.pop(range_slider_ids[i]);
						}
					}
					//console.log("push : "+slider_id);
					range_slider_ids.push(slider_id); 

					//console.log("range slider push: ");
					//console.info(range_slider_ids.join(','));
				}

				
				
				$('#sensor-cond-' + num + ' > #range_slider > #range-slider').bootstrapSlider({
					id: slider_id,
					max: max,
					min: min,
					range: true,
					tooltip:'always',
					step: step,
					value: [min, min+20]
				});
			}
		}

		// Slider Event
		$('#single-slider').on("slide", function(e){
			var act_value = e.value;
			//console.info("single slider value: "+act_value);
		});
	</script>

	<script>
		var sensor_field_name = [
			"",
			"S_Ultrasonic",
			"S_IR",
			"S_Humidity",
			"S_Temperature",
			"S_Heatindex",
			"S_Light",
			"S_Gas"
		];
		var actuator_field_name = ["", "A_Fan", "A_Servo", "A_Buzzer"];
		var single_slider = "<div class='col-md-8' id='single_slider' style='float:right;v  margin-top:5px; dis" +
			"play:none'><input id='single-slider' type='text'/></div>";
		var range_slider = "<div class='conds col-md-8' id='range_slider' style='float:right; margin-top:5px" +
			"; display:none'><input id='range-slider' type='text'/></div>";
		var radio_form = "<div class='conds col-md-8' id='radio_form' style='float:right; display:none'><l" +
			"abel class='radio-inline' style='margin-left:50px;'> <input type='radio' name='i" +
			"nlineRadioOptions' id='inlineRadio1' value='option1'> true </label><label class=" +
			"'radio-inline' style='margin-left:50px;'> <input type='radio' name='inlineRadioO" +
			"ptions' id='inlineRadio2' value='option2'> false </label></div></div>";
		var sensor_cond_cnt = 0;
		var act_cond_cnt = 0;

		function switch_names(name) {
			var switched = "";
			switch (name) {
				case "S_Ultrasonic": switched = "초음파센서"; break;
				case "S_IR": switched = "장애물센서"; break;
				case "S_Humidity": switched = "습도센서"; break;
				case "S_Temperature": switched = "온도센서"; break;
				case "S_Heatindex": switched = "열센서"; break;
				case "S_Light": switched = "조도센서"; break;
				case "S_Gas": switched = "가스센서"; break;
				case "A_Fan": switched = "팬"; break;
				case "A_Servo": switched = "서보모터"; break;
				case "A_Buzzer": switched = "부저"; break;
			}
			return switched;
		}

		// $('select').change(function(){             $(this)
		// .siblings('select')                 .children('option[value='+this.value+']')
		// .attr('disabled',true)                 .siblings().removeAttr('disabled');
		// }); select box 값 선택될 때마다 출력

		function select_box(option, id) {
			console.info("changed");
			id = '#' + id;
			var data_s_num = $(id).attr('data-sensor-num');

			if (data_s_num > 0) {
				for (var i = 0; i < data_s_num; i++) {
					var box_id = '#dropdown_sensor_' + i;
					var value = $(box_id + ' option:selected').val();
					var select_tags = $('select');
					select_tags
						.children('option[value=' + value + ']')
						.attr('disabled', true);
				}
			}

			var show_sensor_num = "sensor-cond-" + data_s_num;
			var hide_child = $('#' + show_sensor_num + ' > .conds');
			hide_child.hide();
			var show_child;

			switch (option) {
				case "S_IR":
					show_child = $('#' + show_sensor_num + ' > #radio_form');
					show_child.show();
					break;
				case "A_Fan":
				case "A_Servo":
				case "A_Buzzer":
					$('#single_slider').show();
					slider_setting(0,"single");
					break;
				case "init":
					break;
				default:
					show_child = $('#' + show_sensor_num + ' > #range_slider');
					show_child.show();
					slider_setting(data_s_num,option);
			}
		}

		// $('#dropdown_sensor').change(function(){             $('#dropdown_sensor
		// option:selected').each(function(){                 console.log("changed");
		// });         }).change(); 버튼 클릭 이벤트
		function btn_action(whichDevice) {
			var form_id = document.getElementById("form-condition");

			switch (whichDevice) {
				case 'sensor':
					//sensor dropdown select form tag
					var frm_sensor_dd_tag = "<select class='col-md-3 form-control' id=dropdown_sensor_" + sensor_cond_cnt +
						" data-sensor-num=" + sensor_cond_cnt +
						" onchange='select_box(this.value, this.id)'><option selected='selected' value='init'>센서 선택</option>";
					var noOfSelectedSensor = $('.selected >.sensor').length;
					if (noOfSelectedSensor == 0) alert("센서를 먼저 선택해 주세요!"); //선택한 센서 없을 때 알림
					else { //있으면
						//select 태그에 들어갈 센서들 가져오기
						var selected_s = document
							.getElementById('selected-sensor')
							.getElementsByTagName('tr');
						if (sensor_cond_cnt == selected_s.length) {
							alert("센서 조건은 센서당 하나씩만 설정해주세요!");
							break;
						}

						for (var i = 0; i < selected_s.length; i++) {
							var kor_s_name = switch_names(selected_s[i].className);
							frm_sensor_dd_tag += "<option value='" + selected_s[i].className + "'>" + kor_s_name + "</option>";
						}
						frm_sensor_dd_tag += "</select>";

						var sensor_cond_tag = frm_sensor_dd_tag + range_slider + radio_form;

						var add_sensor_row = document.createElement("div"); //div 생성
						add_sensor_row.id = "sensor-cond-" + sensor_cond_cnt;
						add_sensor_row.className = "row cond";
						add_sensor_row.setAttribute('data-sensor-num', sensor_cond_cnt);
						add_sensor_row.innerHTML = sensor_cond_tag;
						var conds = add_sensor_row.getElementsByClassName('conds');
						for (var i = 0; i < conds.length; i++) {
							conds[i].setAttribute('data-sensor-num', sensor_cond_cnt);
						}
						form_id.appendChild(add_sensor_row);

						select_box("init", "dropdown_sensor_" + sensor_cond_cnt);

						sensor_cond_cnt++;
					}
					break;
				case 'actuator':
					var frm_act_dd_tag = "<select class='col-md-3 form-control' id='dropdown_act'>"; //actuator dropdown select form tag
					var noOfSelectedAct = $('.selected >.actuator').length;
					if (noOfSelectedAct == 0) alert("기기를 먼저 선택해 주세요!"); //선택한 기기 없을 때 알림
					else { //있으면
						//select 태그에 들어갈 센서들 가져오기
						var selected_a = document
							.getElementById('selected-actuator')
							.getElementsByTagName('tr');
						if (act_cond_cnt == selected_a.length) {
							alert("기기 조건은 하나만 설정해주세요!");
							break;
						}

						for (var i = 0; i < selected_a.length; i++) {
							var kor_a_name = switch_names(selected_a[i].className);
							frm_act_dd_tag += "<option value='" + selected_a[i].className + "' selected='selected'>" + kor_a_name + "</option>";
						}
						frm_act_dd_tag += "</select>";

						var act_cond_tag = frm_act_dd_tag + single_slider + "</div>";

						var add_act_row = document.createElement("div"); //div 생성
						add_act_row.id = "act-cond-" + act_cond_cnt;
						add_act_row.className = "row cond";
						add_act_row.innerHTML = act_cond_tag;
						form_id.appendChild(add_act_row);

						select_box($('#dropdown_act option:selected').val(), "");

						act_cond_cnt++;
					}
					break;
				case 'build':
					break;
				case 'reset': //조건 리스트 모두 삭제
					$("#form-condition").empty();
					act_cond_cnt = 0;
					sensor_cond_cnt = 0;
					range_slider_ids=[];
					break;
			}
		}

		//List monitoring
		setInterval(function monitor() {
			var sensorList = [];
			var actuatorList = [];

			$('.sensor').each(function() {
				sensorList.push(this.id);
			});

			$('.actuator').each(function() {
				actuatorList.push(this.id);
			});

			$.ajax({
				async: false,
				data: {
					Init: 'sensor',
					Sensors: JSON.stringify(sensorList)
				},
				datatype: 'json',
				error: function(result) {
					alert('Sensor 항목을 갱신하지 못했습니다.');
				},
				success: function(result) {
					var array = JSON.parse(result);

					$.each(array, function(state, arr) {
						if (state == "exist" && arr.length != 0)
							exist(arr, "sensor");
						else if (state == "add" && arr.length != 0)
							add(arr, "sensor");
						else if (state == "delete" && arr.length != 0)
							del(arr);
					});
				},
				type: 'POST',
				url: 'monitor.php'
			});

			$.ajax({
				async: false,
				data: {
					Actuators: JSON.stringify(actuatorList),
					Init: 'actuator'
				},
				datatype: 'json',
				error: function(result) {
					alert('Actuator 항목을 갱신하지 못했습니다.');
				},
				success: function(result) {
					var array = JSON.parse(result);

					$.each(array, function(state, arr) {
						if (state == "exist" && arr.length != 0)
							exist(arr, "actuator");
						else if (state == "add" && arr.length != 0)
							add(arr, "actuator");
						else if (state == "delete" && arr.length != 0)
							del(arr);
					});
				},
				type: 'POST',
				url: 'monitor.php'
			});
		}, 1000);

		function add(arr, whichList) {
			var length = arr.length;

			var li_tag_start = "<li ";
			var li_tag_id;
			var li_tag_class;
			var li_tag_end = ">";
			var h5_tag = "<h5 class='ui-widget-header'>IP: ";
			var table_tag = "</h5><table class='table table-hover table-condensed table-bordered'><tbody>";
			var closing_tag = "</tbody></table></li>";

			switch (whichList) { //sensor인지 actuator인지 구분
				case "sensor":
					for (var i = 0; i < length; i++) {
						li_tag_id = 'id="' + arr[i].IP + '" ';
						li_tag_class = "class='sensor ui-widget-content ui-corner-tr ui-state-default'";

						var full_tag = li_tag_start + li_tag_id + li_tag_class + li_tag_end + h5_tag + arr[i].IP + table_tag;
						for (var j = 1; j < sensor_field_name.length; j++) {
							if (arr[i][j] !== null) {
								full_tag += "<tr class=" + sensor_field_name[j] + "><td>" + switch_names(sensor_field_name[j]) + "</td>";
								full_tag += "<td class='data'>" + arr[i][j] + "</td></tr>";
							}
						}
						full_tag += closing_tag;
						$('#ul-sensor-list').append(full_tag);
					}

					sort();
					break;
				case "actuator":
					for (var i = 0; i < length; i++) {
						li_tag_id = 'id="' + arr[i].IP + '" ';
						li_tag_class = "class='actuator ui-widget-content ui-corner-tr ui-state-default'";

						var full_tag = li_tag_start + li_tag_id + li_tag_class + li_tag_end + h5_tag + arr[i].IP + table_tag;
						for (var j = 1; j < actuator_field_name.length; j++) {
							if (arr[i][j] !== null) {
								full_tag += "<tr class=" + actuator_field_name[j] + "><td>" + switch_names(actuator_field_name[j]) + "</td>";
								full_tag += "<td class='data'>" + arr[i][j] + "</td></tr>";
							}
						}
						full_tag += closing_tag;
						$('#ul-act-list').append(full_tag);
					}

					sort();
					break;
				default:
					alert("Error at classifying!!");
			}
		}

		function exist(arr, whichList) {
			var length = arr.length;

			switch (whichList) { //sensor인지 actuator인지 구분
				case "sensor":
					for (var i = 0; i < length; i++) {
						var id_tmp = '#' + arr[i]['IP']
							.split('.')
							.join('\\.');
						for (var j = 0; j < sensor_field_name.length; j++) {
							if (arr[i][sensor_field_name[j]] != null) {
								$(id_tmp + " ." + sensor_field_name[j] + " .data").text(arr[i][sensor_field_name[j]]);
							}
						}
					}

					break;
				case "actuator":
					for (var i = 0; i < length; i++) {
						var id_tmp = '#' + arr[i]['IP']
							.split('.')
							.join('\\.');
						for (var j = 0; j < actuator_field_name.length; j++) {
							if (arr[i][actuator_field_name[j]] != null) {
								$(id_tmp + "." + actuator_field_name[j] + ".data").text(arr[i][actuator_field_name[j]]);
							}
						}
					}

					break;
			}
		}

		function del(arr) {
			var length = arr.length;

			for (var i = 0; i < length; i++) {
				$('#' + arr[i].split('.').join('\\.')).remove();
			}
		}

		function sort() { //sortable (drag&drop)
			var $ul_sensor_list = $("#ul-sensor-list");
			var $ul_act_list = $("#ul-act-list");
			var $selected_sensor = $("#selected-sensor");
			var $selected_act = $("#selected-actuator");
			var flag = 0;

			$(".sensorDevices")
				.sortable({
					connectWith: ".sensorDevices",
					placeholder: "list-placeholder ui-corner-all",
					revert: 200,
					scroll: false
				})
				.disableSelection();

			$(".actuatorDevices")
				.sortable({
					connectWith: ".actuatorDevices",
					placeholder: "list-placeholder ui-corner-all",
					revert: 200,
					scroll: false
				})
				.disableSelection();

			$selected_sensor.on("sortreceive", function(event, ui) {
				var $list = $(this);

				if ($list.children().length > 1) {
					$(ui.sender).sortable('cancel');
					alert("한 개의 센서만 선택해주세요!");
				}
			});

			$selected_act.on("sortreceive", function(event, ui) {
				var $list = $(this);

				if ($list.children().length > 1) {
					$(ui.sender).sortable('cancel');
					alert("한 개의 기기만 선택해주세요!");
				}
			});
		}
	</script>
</body>

</html>