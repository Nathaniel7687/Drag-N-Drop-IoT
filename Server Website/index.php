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
        
        ul li,
        ul li {
            float: left;
            width: 100%;
            padding: 0.4em;
            margin: 0 auto 0.4em auto;
            text-align: center;
        }
        
        ul li h5,
        ul li h5 {
            margin: 0 0 0.4em;
        }
        
        th {
            text-align: center;
        }
        
        .table {
            font-size: 13px;
            margin-bottom: 0px;
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
    </style>
</head>

<body>
    <!-- Navigation Bar -->
    <nav class="navbar navbar-inverse navbar-fixed-top">
        <div class="container" style="margin-left: 20px">
            <div class="navbar-header">
                <a class="navbar-brand text-left" style="margin: 0 0 0 0px" href="#">IoT Drag & Drop Project</a>
            </div>
        </div>
    </nav>

    <div class="container-fluid">
        <div class="row top_margin">
            <!-- Sensor List -->
            <div id="div-sensor-list" class="col-md-2" style="border-right: 2px solid lightgray">
                <h2 class="text-center">Sensor List</h2>
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
                        <h3 class="text-center">Selected sensor</h3>
                        <hr style="border-bottom: 1px solid lightgray; margin-top: 27px">

                        <ul id="selected-sensor" class="sensor list-unstyled height-set">
                        </ul>

                    </div>
                    <div id="div-condition" class="col-md-6">
                        <!-- Title part -->
                        <h3 class="text-center">Conditions
                            <button type="button" class="btn btn-danger" style="float:right" aria-label="Add a Condition">
                  <span class="glyphicon glyphicon-plus" aria-hidden="true"></span>
                </button>
                        </h3>
                        <hr style="border-bottom: 1px solid lightgray; margin-top: 27px">

                        <div class="row">
                            <div class="col-md-4">
                                <!-- Split button -->
                                <div class="btn-group">
                                    <button type="button" id="btn-sensor" class="btn btn-primary">센서</button>
                                    <button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                      <span class="caret"></span>
                      <span class="sr-only">Toggle Dropdown</span>
                    </button>
                                    <ul class="dropdown-menu" id="btn-sensor">
                                        <li><a href="#">초음파 센서</a></li>
                                        <li><a href="#">장애물 감지 센서</a></li>
                                    </ul>
                                </div>

                                <!-- Split button -->
                                <div class="btn-group top_margin">
                                    <button type="button" id="btn-sensor" class="btn btn-primary">액추에이터</button>
                                    <button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                      <span class="caret"></span>
                      <span class="sr-only">Toggle Dropdown</span>
                    </button>
                                    <ul class="dropdown-menu" id="btn-sensor">
                                        <li><a href="#">초음파 센서</a></li>
                                        <li><a href="#">장애물 감지 센서</a></li>
                                    </ul>
                                </div>

                            </div>

                            <div class="col-md-7">
                                <div class="input-group">
                                    <div class="input-group-btn">
                                        <button type="button" class="btn btn-default">조건</button>
                                        <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        <span class="caret"></span>
                        <span class="sr-only">Toggle Dropdown</span>
                      </button>
                                        <ul class="dropdown-menu">
                                            <li>
                                                <a href="#">
                                                    <</a>
                                            </li>
                                            <li>
                                                <a href="#">
                                                    <=</a>
                                            </li>
                                            <li><a href="#">=</a></li>
                                            <li><a href="#">>=</a></li>
                                            <li><a href="#">></a></li>
                                        </ul>
                                    </div>

                                    <input type="text" class="form-control" aria-label="Text input with dropdown button">


                                </div>

                                <!-- 나중에 슬라이더로 바꾸기 -->
                                <div class="input-group top_margin">
                                    <div class="input-group-btn">
                                        <button type="button" class="btn btn-default">조건</button>
                                        <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        <span class="caret"></span>
                        <span class="sr-only">Toggle Dropdown</span>
                      </button>
                                        <ul class="dropdown-menu">
                                            <li>
                                                <a href="#">
                                                    <</a>
                                            </li>
                                            <li>
                                                <a href="#">
                                                    <=</a>
                                            </li>
                                            <li><a href="#">=</a></li>
                                            <li><a href="#">>=</a></li>
                                            <li><a href="#">></a></li>
                                        </ul>
                                    </div>

                                    <input type="text" class="form-control" aria-label="Text input with dropdown button">


                                </div>
                            </div>

                            <div class="col-md-1">
                                <div class="btn-toolbar" role="toolbar">
                                    <div class="btn-group" style="float:right; margin-top:27px">
                                        <button type="button" class="btn btn-danger" aria-label="Delete a Condition">
                        <span class="glyphicon glyphicon-trash" aria-hidden="true"></span>
                      </button>
                                    </div>
                                </div>
                            </div>
                        </div>

                        <hr>

                        <!-- 같은 row 반복 -->
                        <div class="row">
                            <div class="col-md-4">
                                <!-- Split button -->
                                <div class="btn-group">
                                    <button type="button" id="btn-sensor" class="btn btn-primary">센서</button>
                                    <button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                      <span class="caret"></span>
                      <span class="sr-only">Toggle Dropdown</span>
                    </button>
                                    <ul class="dropdown-menu" id="btn-sensor">
                                        <li><a href="#">초음파 센서</a></li>
                                        <li><a href="#">장애물 감지 센서</a></li>
                                    </ul>
                                </div>

                                <!-- Split button -->
                                <div class="btn-group top_margin">
                                    <button type="button" id="btn-sensor" class="btn btn-primary">액추에이터</button>
                                    <button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                      <span class="caret"></span>
                      <span class="sr-only">Toggle Dropdown</span>
                    </button>
                                    <ul class="dropdown-menu" id="btn-sensor">
                                        <li><a href="#">초음파 센서</a></li>
                                        <li><a href="#">장애물 감지 센서</a></li>
                                    </ul>
                                </div>

                            </div>

                            <div class="col-md-7">
                                <div class="input-group">
                                    <div class="input-group-btn">
                                        <button type="button" class="btn btn-default">조건</button>
                                        <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        <span class="caret"></span>
                        <span class="sr-only">Toggle Dropdown</span>
                      </button>
                                        <ul class="dropdown-menu">
                                            <li>
                                                <a href="#">
                                                    <</a>
                                            </li>
                                            <li>
                                                <a href="#">
                                                    <=</a>
                                            </li>
                                            <li><a href="#">=</a></li>
                                            <li><a href="#">>=</a></li>
                                            <li><a href="#">></a></li>
                                        </ul>
                                    </div>

                                    <input type="text" class="form-control" aria-label="Text input with dropdown button">


                                </div>

                                <!-- 나중에 슬라이더로 바꾸기 -->
                                <div class="input-group top_margin">
                                    <div class="input-group-btn">
                                        <button type="button" class="btn btn-default">조건</button>
                                        <button type="button" class="btn btn-default dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                        <span class="caret"></span>
                        <span class="sr-only">Toggle Dropdown</span>
                      </button>
                                        <ul class="dropdown-menu">
                                            <li>
                                                <a href="#">
                                                    <</a>
                                            </li>
                                            <li>
                                                <a href="#">
                                                    <=</a>
                                            </li>
                                            <li><a href="#">=</a></li>
                                            <li><a href="#">>=</a></li>
                                            <li><a href="#">></a></li>
                                        </ul>
                                    </div>

                                    <input type="text" class="form-control" aria-label="Text input with dropdown button">


                                </div>
                            </div>

                            <div class="col-md-1">
                                <div class="btn-toolbar" role="toolbar">
                                    <div class="btn-group" style="float:right; margin-top:27px">
                                        <button type="button" class="btn btn-danger" aria-label="Delete a Condition">
                        <span class="glyphicon glyphicon-trash" aria-hidden="true"></span>
                      </button>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>


                    <div id="div-selected-actuator" class="col-md-3">
                        <!-- Title part -->
                        <h3 class="text-center">Selected Actuator</h3>
                        <hr style="border-bottom: 1px solid lightgray; margin-top: 27px">

                        <ul id="selected-actuator" class="actuator list-unstyled height-set">
                        </ul>
                    </div>

                </div>
            </div>


            <div id="div-actuator-list" class="col-md-2" style="border-left: 2px solid lightgray">
                <!-- Title part -->
                <h2 class="text-center">Actuator List</h2>
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
    </div>
    <!-- /container -->

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
                "3232235521",
                "3232235525",
                "3232235636",
                "3232235736"
            ]

            var actuatorList = [
                "3232235521",
                "3232235522",
                "3232235528",
                "3232235636"
            ]

            $.ajax({
                type: 'POST',
                url: 'monitor.php',
                data: {
                    Init: 'sensor',
                    Sensors: JSON.stringify(sensorList)
                },
                datatype: 'json',
                success: function(result) {
                    var array = JSON.parse(result);
                    console.log(array);
                    // alert(result);
                },
                error: function(result) {
                    console.log('Sensor 항목을 갱신하지 못했습니다.');
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
                    console.log(array);
                    // alert(result);
                },
                error: function(result) {
                    console.log('Actuator 항목을 갱신하지 못했습니다.');
                }
            });
        }, 1000);

        // $(document).ready(function db() { //call DB
        //     $.post("db.php", {
        //             table_name: "sensorlist"
        //         },
        //         function(sensor, txtStatus, jqXHR) {
        //             $('#ul-sensor-list').empty();
        //             if (sensor == "") {
        //                 $('#ul-sensor-list').append("<p class='text-center'>No Sensor</p>");
        //             }
        //             $('#ul-sensor-list').append(sensor);
        //             sort();
        //         }).fail(function(jqXHR, txtStatus, errorThrown) {
        //         alert("Sensor Data Load Failed: " + txtStatus);
        //     });
        //     $.post("db.php", {
        //             table_name: "actuatorlist"
        //         },
        //         function(actuator, txtStatus, jqXHR) {
        //             $('#ul-act-list').empty();
        //             if (actuator == "") {
        //                 $('#ul-act-list').append("<p class='text-center'>No Actuator</p>");
        //             }
        //             $('#ul-act-list').append(actuator);
        //             sort();
        //         }).fail(function(jqXHR, txtStatus, errorThrown) {
        //         alert("Actuator Data Load Failed: " + txtStatus);
        //     });
        // }); //ajax

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